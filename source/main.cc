/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *    编译:gcc snake.c main.c -lncursesw -std=gnu99
 *    解决中文问题：
 *    main.c添加:
 *    #include<locale.h>
 *    初始化屏幕前需添加:
 *    setlocale(LC_ALL,"");
 *
 *        Version:  1.0
 *        Created:  2016年08月03日 12时17分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#include	"../header/snake.h"
#include	<unistd.h>
#include	<stdlib.h>
#include	<time.h>
#define FOOD_SYMBOL '*'
#define ESC 27
#define STOP 's'
/*
 * 终端设置
 */
void initial_basic_settings();
/*
 * 游戏参数设置
 */
void initial_game_attr();
/*
 * 是否开始游戏
 */
void start_game();
/*
 * 响应键盘事件
 */
void keypress_event(int ch);
/*
 * 绘制蛇属性以及游戏中的提示信息
 */
void draw_info();
/*
 * 更新蛇属性以及游戏信息
 */
void update_info();
/*
 * 游戏引擎
 */
void game_engine();
/*
 * 重新开始游戏
 */
void restart_game();
/*
 * 游戏结束
 */
void end_game();
/*
 * 生成食物
 */
void generate_food();
WINDOW *win;
/*
 * 窗口高宽
 */
int nrows,ncols;
/*
 * 剩余生命
 * 等级
 * 已吃食物
 */
int nlife,nlevel,nfood;
/*
 * 生命，等级，已吃食物信息窗口坐标
 */
int nlife_pos,nlevel_pos,nfood_pos;
/*
 * 生成的食物坐标
 */
int food_x,food_y;
/*
 * 蛇移动速度
 */
int snake_speed=1;
/*
 * 蛇头朝向
 */
Snake_direct direction;
/*
 * 绘图函数指针
 */
draw_map map_graphic;
/*
 * 地图碰撞检测函数指针
 */
map_collision_status_ptrs map_collision_status;

int
main(){
	initial_basic_settings();
	do_init_map(map_graphic,map_collision_status);
	start_game();
	initial_game_attr();
	game_engine();
}

void 
initial_basic_settings(){
	win=initscr();
	/*
	 * 隐藏关标
	 */
	curs_set(0);
#if 0
	/*
	 * 输入无需回车
	 */
	cbreak();
#endif
	/*
	 * snake_speed*0.1s内如无输入,
	 * getch()返回ERR
	 */
	halfdelay(snake_speed);
	/*
	 * 关闭回显
	 */
	noecho();
	/*
	 * 中断立即响应
	 */
	intrflush(win,TRUE);
	/*
	 * 取得窗口宽高
	 */
	getmaxyx(win,nrows,ncols);
	/*
	 * 允许使用方向键
	 */
	keypad(win,TRUE);
	/*
	 * 检测是否启动颜色机制
	 */
	check_color_system();
	init_color_manager();
	/*
	 * 刷新屏幕
	 */
	refresh();
}

void
game_engine(){
	do_initial_snake();
	generate_food();
	set_food_pos(food_x,food_y);
	int ch;
	while(1){
		while((ch=getch())==ERR){
            draw_snake();
            attron(COLOR_PAIR(FOOD));
            mvprintw(food_y,food_x,"%c",FOOD_SYMBOL);
            attroff(COLOR_PAIR(FOOD));
            (*map_graphic[nlevel])();
            draw_info();
            move_forward(direction,map_collision_status[nlevel]);
            update_info();
            restart_game();
            usleep(300);
        }
        keypress_event(ch);
	}
}

void
initial_game_attr(){
	srand(time(0));
	nlife=3;
	nlevel=0;
	nfood=0;
	nlife_pos=2;
	nlevel_pos=10;
	nfood_pos=20;
	set_boundary(1,5,ncols-2,nrows-2);
	set_collision_status();
	direction=RIGHT;
}

void
keypress_event(int ch){
		switch(ch){
			case KEY_LEFT:
				if(direction!=RIGHT){
					direction=LEFT;
				}
				break;
			case KEY_RIGHT:
				if(direction!=LEFT){
					direction=RIGHT;
				}
				break;
			case KEY_UP:
				if(direction!=DOWN){
					direction=UP;
				}
				break;
			case KEY_DOWN:
				if(direction!=UP){
					direction=DOWN;
				}
				break;
			case ESC:
				end_game();
				break;
			case STOP:
				while(getch()!='r');
				break;
		}
}

void
draw_info(){
	box(win,'|','-');
	attron(BORDER);
	for(int i=1;i<ncols-1;i++){
		mvprintw(4,i,"%c",'-');
	}
	attroff(BORDER);
	attron(A_BOLD|COLOR_PAIR(ATTR_NAME));
	mvprintw(2,nlife_pos,"life:%d",nlife);
	mvprintw(2,nlevel_pos,"level:%d",nlevel);
	mvprintw(2,nfood_pos,"food:%d",nfood);
	attroff(A_BOLD|COLOR_PAIR(ATTR_NAME));
	attron(COLOR_PAIR(OPERATE_INFO));
	mvprintw(2,ncols-30,"%s","|esc:exit|s:stop|r:resume|");
	attroff(COLOR_PAIR(OPERATE_INFO));
	refresh();
}

void
update_info(){
	if(get_collision_status()==1){
		nlife--;
		if(nlife>0){
			attron(A_BOLD|COLOR_PAIR(WARNING));
			mvprintw(LINES/2,COLS/2-5,"%s","Oh,my god!");
			attroff(A_BOLD|COLOR_PAIR(WARNING));
			refresh();
			for(int i=0;i<3;i++)flash();
			sleep(1);
			mvprintw(LINES/2,COLS/2-5,"%s","          ");
			refresh();
		}
		set_collision_status();
	}
	if(get_food_status()){
		generate_food();
		set_food_pos(food_x,food_y);
		nfood++;
		if(nfood==10){
			nlevel++;
			nfood=0;
			direction=RIGHT;
			attron(A_BOLD|COLOR_PAIR(LEVEL_UP));
			mvprintw(LINES/2,COLS/2-5,"%s","Level up!");
			attroff(A_BOLD|COLOR_PAIR(LEVEL_UP));
			refresh();
			do_initial_snake();
			sleep(1);
		}
	}
}

void 
generate_food(){
label:
find_food:
	while((food_x=rand()%(ncols-1))==1);
	while((food_y=rand()%(nrows-1))<=5);
	while((*map_collision_status[nlevel])(food_x,food_y))
		goto find_food;
}


void
restart_game(){
	if(nlife<=0){
		clear();
		for(int i=0;i<10;i++)
			flash();
		attron(A_REVERSE|A_BOLD);
		mvprintw(LINES/2,COLS/2-10,"%s","Game over!");
		attroff(A_REVERSE|A_BOLD);
		attron(COLOR_PAIR(SCORE));
		mvprintw(LINES/2+1,COLS/2-10,"Level:%d",nlevel);
		mvprintw(LINES/2+2,COLS/2-10,"Score:%d",nlevel*110+nfood*9);
		attroff(COLOR_PAIR(SCORE));
		attron(COLOR_PAIR(OPERATE_INFO));
		mvprintw(LINES/2+3,COLS/2-10,"Press esc to replay the game");
		mvprintw(LINES/2+4,COLS/2-10,"or press q to quit the game.");
		attroff(COLOR_PAIR(OPERATE_INFO));
		refresh();
		int ch;
label:
query:
		ch=getch();
		if(ch=='q'){
			end_game();
		}else if(ch==ESC){
            int cur_level=nlevel;
            initial_game_attr();
            nlevel=cur_level;
            game_engine();
		}else{
			goto query;
		}
	}
}

void
start_game(){
	int ch;
	do{
        attron(A_BOLD|COLOR_PAIR(OPERATE_INFO));
        mvaddstr(LINES/2,COLS/2-10,"Press esc to start the game.");
        attroff(A_BOLD|COLOR_PAIR(OPERATE_INFO));
        refresh();
	}while((ch=getch())!=ESC);
}

void
end_game(){
	endwin();
	exit(0);
}
