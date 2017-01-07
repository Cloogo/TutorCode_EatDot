/*
 * =====================================================================================
 *
 *       Filename:  snake.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月03日 11时12分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#include	<assert.h>
#include	"snake.h"


static void init_snake();
/*
 * 更新蛇头
 */
static void add_snake_node(int x,int y);
/*
 * 删除蛇尾
 */
static void del_snake_node();
/*
 * 判断蛇长是否为满,为空
 */
static int is_full();
static int is_empty();
/*
 * 取得蛇头信息
 */
static void get_tail();
/*
 * 检测是否碰撞
 * 蛇头三种碰撞类型：
 * 1:与边界碰撞
 * 2:与蛇身碰撞
 * 3:与食物碰撞
 */
static int check_collision();
/*
 * 设置为已吃食物状态
 */
static void set_food_status();

/*
 * 蛇
 */
static Snake snake;
/*
 * 临时蛇节点
 */
static Snake_node snake_node;
/*
 * 蛇头节点
 */
static Snake_node snake_tail;
/*
 * 碰撞标记
 * 0:不碰撞
 * 1:碰撞
 */
static int collision=0;
/*
 * 边界值
 */
static int x1_bound,y1_bound,x2_bound,y2_bound;
/*
 * 食物坐标
 */
static int food_x,food_y;
/*
 * 食物状态
 * 0:未被吃
 * 1:已吃
 */
static int is_eaten=0;
static int snake_level;
static int color_supported;

static void
init_snake(){
	snake.head=0;
	snake.tail=0;
	for(int x=COLS/2-3;x<COLS/2+3;x++){
		add_snake_node(x,LINES-2);
	}
	clear();
	int cur;
	/*
	 * 绘制蛇身
	 * 方法：遍历队列
	 */
	attron(COLOR_PAIR(SNAKE_BODY));
	for(cur=(snake.head+1)%BODY_LENGTH;cur!=snake.tail;cur=(cur+1)%BODY_LENGTH){
		mvprintw(snake.body[cur].y,snake.body[cur].x,"%c",BODY_SYMBOL);
	}
	attroff(COLOR_PAIR(SNAKE_BODY));
	/*
	 * 绘制蛇头
	 */
	attron(COLOR_PAIR(SNAKE_HEAD));
	mvprintw(snake.body[cur].y,snake.body[cur].x,"%c",HEAD_SYMBOL);
	attroff(COLOR_PAIR(SNAKE_HEAD));
}

static void
add_snake_node(int x,int y){
	assert(is_full()==0);
	snake_node.x=x;
	snake_node.y=y;
	snake.tail=(++snake.tail)%BODY_LENGTH;
	snake.body[snake.tail]=snake_node;
}

static void
del_snake_node(){
	snake.head=(++snake.head)%BODY_LENGTH;
}

static void
get_tail(){
	snake_tail=snake.body[snake.tail];
}

static int
is_full(){
	return ((snake.tail+1)%BODY_LENGTH==snake.head);
}

static int
is_empty(){
	return snake.head==snake.tail;
}

/*
 * 返回值：
 * 0:未碰撞
 * 1:与边界碰撞
 * 2:与蛇身碰撞
 * 3:与食物碰撞
 */
static int
check_collision(int x,int y,map_collision_status_ptr map_collision_status){
	/*
	 * 食物初始化为未被吃
	 */
	is_eaten=0;
	if(x==food_x&&y==food_y){
		add_snake_node(food_x,food_y);
		set_food_status();
		return 3;
	}else{
		if(x<x1_bound||x>x2_bound||y<y1_bound||y>y2_bound){
		collision=1;
		return 1;
		}
		for(int cur=(snake.head+1)%BODY_LENGTH;cur!=snake.tail;cur=(cur+1)%BODY_LENGTH){
			if(snake.body[cur].x==x&&snake.body[cur].y==y){
				collision=1;
				return 2;
			}	
		}
		if((*map_collision_status)(x,y)){
			collision=1;
			return 1;
		}
	}
	return 0;
}

void
set_boundary(int x1,int y1,int x2,int y2){
	x1_bound=x1;
	y1_bound=y1;
	x2_bound=x2;
	y2_bound=y2;
}

void 
set_food_pos(int x,int y){
	food_x=x;
	food_y=y;
}

void
move_forward(Snake_direct direct,map_collision_status_ptr map_collision_status){
	get_tail();
	int tmpx,tmpy;
	switch(direct){
		case UP:
			tmpx=snake_tail.x;
			tmpy=snake_tail.y-1;
			break;
		case DOWN:
			tmpx=snake_tail.x;
			tmpy=snake_tail.y+1;
			break;
		case LEFT:
			tmpx=snake_tail.x-1;
			tmpy=snake_tail.y;
			break;
		case RIGHT:
			tmpx=snake_tail.x+1;
			tmpy=snake_tail.y;
			break;
	}
	if(check_collision(tmpx,tmpy,map_collision_status)==0){
		add_snake_node(tmpx,tmpy);
		del_snake_node();
	}
}

void 
do_initial_snake(){
	init_snake();
}

void
draw_snake(){
#if 0
	int cur;
	/*
	 * 绘制蛇身
	 * 方法：遍历队列
	 */
	attron(COLOR_PAIR(SNAKE_BODY));
	for(cur=(snake.head+1)%BODY_LENGTH;cur!=snake.tail;cur=(cur+1)%BODY_LENGTH){
		mvprintw(snake.body[cur].y,snake.body[cur].x,"%c",BODY_SYMBOL);
	}
	attroff(COLOR_PAIR(SNAKE_BODY));
	/*
	 * 绘制蛇头
	 */
	attron(COLOR_PAIR(SNAKE_HEAD));
	mvprintw(snake.body[cur].y,snake.body[cur].x,"%c",HEAD_SYMBOL);
	attroff(COLOR_PAIR(SNAKE_HEAD));
	refresh();
#endif

	/*
	 * 删除蛇尾符号
	 */
	mvprintw(snake.body[snake.head].y,snake.body[snake.head].x,"%c",' ');
	/*
	 * 更新蛇头符号
	 */
	attron(COLOR_PAIR(SNAKE_HEAD));
	mvprintw(snake.body[snake.tail].y,snake.body[snake.tail].x,"%c",HEAD_SYMBOL);
	attroff(COLOR_PAIR(SNAKE_HEAD));
	attron(COLOR_PAIR(SNAKE_BODY));
	mvprintw(snake.body[snake.tail-1].y,snake.body[snake.tail-1].x,"%c",BODY_SYMBOL);
	attroff(COLOR_PAIR(SNAKE_BODY));
	refresh();
}

int
get_level(){
	return snake_level;
}

void
set_level(int level){
	snake_level=level;
}

int
get_snake_length(){
	return (snake.tail-snake.head+BODY_LENGTH)%BODY_LENGTH;
}

int
get_collision_status(){
	return collision;
}

void
set_collision_status(){
	collision=0;
}

static void
set_food_status(){
	is_eaten=1;
}

int 
get_food_status(){
	return is_eaten;
}

void
set_color_status(int supported){
	color_supported=supported;
}
