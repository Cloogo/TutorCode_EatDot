/*
 * =====================================================================================
 *
 *       Filename:  map.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月04日 20时07分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#include	"map.h"
static void draw_map0();
static void draw_map1();
static void draw_map2();
static void draw_map3();
static void draw_map4();
static void draw_map5();
static void draw_map6();
static void draw_map7();
static void draw_map8();
static void draw_map9();
static int map0_collision_status(int x,int y);
static int map1_collision_status(int x,int y);
static int map2_collision_status(int x,int y);
static int map3_collision_status(int x,int y);
static int map4_collision_status(int x,int y);
static int map5_collision_status(int x,int y);
static int map6_collision_status(int x,int y);
static int map7_collision_status(int x,int y);
static int map8_collision_status(int x,int y);
static int map9_collision_status(int x,int y);
static Tile tile1;
static Tile tile2;
static Tile tile3;
static Tile tile4;
static Tile tile5;
static Tile tile6;
static Tile tile7;
static Tile tile8;
static Tile tile9;
static Tile tile10;
static Tile tile11;
static Tile tile12;
static Tile tile13;
static Tile tile14;
static Tile tile15;
static Tile tile16;
static Tile tile17;
static Tile tile18;
static Tile tile19;
static Tile tile20;
static Tile tile21;
static Tile tile22;
static Tile tile23;
static Tile tile24;
/*
 * 产生垂直线贴块:tile
 * x:垂直线横坐标
 * start_y:垂直线起始纵坐标
 * height:线长
 */
static void
generate_vertical_line(Tile &tile,int x,int start_y,int height){
	for(int i=start_y;i<start_y+height;i++){
		tile.pointer_set[tile.n_pointer].x=x;
		tile.pointer_set[tile.n_pointer].y=i;
		tile.n_pointer++;
	}
}

/*
 * 产生水平线贴块:tile
 * y:水平线纵坐标
 * start_x:水平线起始横坐标
 * width:线长
 */
static void
generate_horizontal_line(Tile &tile,int y,int start_x,int width){
	for(int i=start_x;i<start_x+width;i++){
		tile.pointer_set[tile.n_pointer].x=i;
		tile.pointer_set[tile.n_pointer].y=y;
		tile.n_pointer++;
	}
}

/*
 * 产生具有水平线或垂直线的贴块:tile
 * type:
 * 0:产生垂直线
 * 1:产生水平线
 */
static void
generator_one(Tile &tile,int yx,int start_xy,int wh,int type){
	tile.n_pointer=0;
	if(type==1){
		generate_horizontal_line(tile,yx,start_xy,wh);
	}else
		generate_vertical_line(tile,yx,start_xy,wh);
}

/*
 * 产生具有水平线和垂直线的贴块:tile
 * 其余参数与generate_vertical_line以及generate_horizontal_line参数对应
 */
static void
generator_two(Tile &tile,int y,int start_x,int width,int x,int start_y,int height){
	tile.n_pointer=0;
	generate_vertical_line(tile,x,start_y,height);
	generate_horizontal_line(tile,y,start_x,width);
}

/*
 * 生成用于组成地图的基本贴块
 */
static void
generate_tile1(){
	generator_two(tile1,LINES/6,COLS/6,COLS/6,COLS/6,LINES/6+1,LINES/6);
}

static void
generate_tile2(){
	generator_two(tile2,LINES/6,COLS/6*5-COLS/6,COLS/6,COLS/6*5,LINES/6,LINES/6);
}

static void
generate_tile3(){
	generator_two(tile3,LINES/6*5,COLS/6,COLS/6,COLS/6,LINES/6*5-LINES/6,LINES/6);
}

static void
generate_tile4(){
	generator_two(tile4,LINES/6*5,COLS/6*5-COLS/6,COLS/6,COLS/6*5,LINES/6*5-LINES/6,LINES/6+1);
}

static void
generate_tile5(){
	generator_one(tile5,LINES/7*2,COLS/2-COLS/12,COLS/6,1);
}

static void
generate_tile6(){
	generator_one(tile6,LINES/7*5,COLS/2-COLS/12,COLS/6,1);
}

static void
generate_tile7(){
	generator_one(tile7,COLS/6*2,LINES/2-LINES/12,LINES/6,0);
}

static void
generate_tile8(){
	generator_one(tile8,COLS/6*4,LINES/2-LINES/12,LINES/6,0);
}

static void
generate_tile9(){
	generator_one(tile9,LINES/6*5-2-LINES/5-1,COLS/6+3+2-COLS/5,COLS/5*2,1);
}

static void
generate_tile10(){
	generator_one(tile10,LINES/6*5-2,COLS/6+3+2,COLS/5,1);
}

static void
generate_tile11(){
	generator_one(tile11,COLS/6+2,(LINES/6*5-2-LINES/5+LINES/6*5-2)/2-LINES/12,LINES/6,0);
}

static void
generate_tile12(){
	generator_one(tile12,COLS/6+3+2+COLS/5+1,(LINES/6*5-2-LINES/5+LINES/6*5-2)/2-LINES/12,LINES/6,0);
}

static void
generate_tile13(){
	generator_one(tile13,LINES/6+2,COLS/6*5-2-COLS/5+1,COLS/5-2,1);
}

static void
generate_tile14(){
	generator_one(tile14,LINES/6+2+LINES/5,COLS/6*5-2-COLS/5-2+1,COLS/5+COLS/5,1);
}

static void
generate_tile15(){
	generator_one(tile15,COLS/6*5-2-COLS/5-1,(LINES/6+2+LINES/5+LINES/6+2)/2-LINES/12,LINES/6,0);
}

static void
generate_tile16(){
	generator_one(tile16,COLS/6*5-2,(LINES/6+2+LINES/5+LINES/6+2)/2-LINES/12,LINES/6,0);
}

static void
generate_tile17(){
	generator_two(tile17,LINES/2+LINES/10,COLS/4,COLS/6,COLS/4,LINES/2-LINES/10,LINES/5);
}

static void
generate_tile18(){
	generator_two(tile18,LINES/2-LINES/10,COLS/4*3-COLS/6,COLS/6,COLS/4*3,LINES/2-LINES/10,LINES/5);
}

static void
generate_tile19(){
	generator_two(tile19,LINES/8*7,COLS/4,COLS/5+COLS/5,COLS/4+COLS/5-2,LINES/8*7-LINES/5,LINES/5);
}

static void
generate_tile20(){
	generator_two(tile20,LINES/6*4,COLS/4*2,COLS/5,COLS/4*2,LINES/6*4-LINES/4,LINES/4+LINES/5-1);
}

static void
generate_tile21(){
	generator_two(tile21,LINES/6+2,COLS/6+2,COLS/4,COLS/6+2+COLS/4-3,LINES/6+2,LINES/5);
}

static void
generate_tile22(){
	generator_two(tile22,LINES/6+2,COLS/2-COLS/6,COLS/4,COLS/2-COLS/6+COLS/4-1,LINES/6+2,LINES/5);
}

static void
generate_tile23(){
	generator_two(tile23,LINES/6-2,COLS/4,COLS/2,COLS/6-2,LINES/4,LINES/2);
}

static void
generate_tile24(){
	generator_two(tile24,LINES/6*5+2,COLS/4,COLS/2,COLS/6*5+2,LINES/4,LINES/2);
}

static void
draw_tile(Tile tile){
	attron(COLOR_PAIR(WALL));
	for(int i=0;i<tile.n_pointer;i++){
		mvprintw(tile.pointer_set[i].y,tile.pointer_set[i].x,"%c",MAP_SYMBOL);
	}
	attroff(COLOR_PAIR(WALL));
}

static void
init_map(draw_map &map_graphic,map_collision_status_ptrs &map_collision_status){
	generate_tile1();
	generate_tile2();
	generate_tile3();
	generate_tile4();
	generate_tile5();
	generate_tile6();
	generate_tile7();
	generate_tile8();
	generate_tile9();
	generate_tile10();
	generate_tile11();
	generate_tile12();
	generate_tile13();
	generate_tile14();
	generate_tile15();
	generate_tile16();
	generate_tile17();
	generate_tile18();
	generate_tile19();
	generate_tile20();
	generate_tile21();
	generate_tile22();
	generate_tile23();
	generate_tile24();
	map_graphic[0]=draw_map0;
	map_graphic[1]=draw_map1;
	map_graphic[2]=draw_map2;
	map_graphic[3]=draw_map3;
	map_graphic[4]=draw_map4;
	map_graphic[5]=draw_map5;
	map_graphic[6]=draw_map6;
	map_graphic[7]=draw_map7;
	map_graphic[8]=draw_map8;
	map_graphic[9]=draw_map9;
	map_collision_status[0]=map0_collision_status;
	map_collision_status[1]=map1_collision_status;
	map_collision_status[2]=map2_collision_status;
	map_collision_status[3]=map3_collision_status;
	map_collision_status[4]=map4_collision_status;
	map_collision_status[5]=map5_collision_status;
	map_collision_status[6]=map6_collision_status;
	map_collision_status[7]=map7_collision_status;
	map_collision_status[8]=map8_collision_status;
	map_collision_status[9]=map9_collision_status;
}

void
do_init_map(draw_map &map_graphic,map_collision_status_ptrs &map_collision_status){
	init_map(map_graphic,map_collision_status);
}

/*
 * 地图0贴块:
 * tile1
 * tile4
 */
static void
draw_map0(){
	draw_tile(tile1);
	draw_tile(tile4);
}

/*
 * 地图1贴块:
 * tile1~tile4
 */
static void
draw_map1(){
	draw_tile(tile2);
	draw_tile(tile3);
	draw_map0();
}

/*地图2贴块:
 * tile1~tile6
 */
static void
draw_map2(){
	draw_tile(tile5);
	draw_tile(tile6);
	draw_map1();
}

/*地图3贴块:
 * tile1~tile8
 */
static void
draw_map3(){
	draw_tile(tile7);
	draw_tile(tile8);
	draw_map2();
}

/*地图4贴块:
 *tile1
 *tile2
 *tile10~tile16
 */
static void
draw_map4(){
	draw_tile(tile9);
	draw_tile(tile10);
	draw_tile(tile11);
	draw_tile(tile12);
	draw_tile(tile13);
	draw_tile(tile14);
	draw_tile(tile15);
	draw_tile(tile16);
	draw_map0();
}

/*地图5贴块：
 * tile1~tile4
 * tile10~tile16
 */
static void
draw_map5(){
	draw_tile(tile9);
	draw_tile(tile10);
	draw_tile(tile11);
	draw_tile(tile12);
	draw_tile(tile13);
	draw_tile(tile14);
	draw_tile(tile15);
	draw_tile(tile16);
	draw_map1();
}

/*地图6贴块：
 * tile1~tile4
 * tile10~tile16
 * tile23~tile24
 */
static void
draw_map6(){
	draw_tile(tile23);
	draw_tile(tile24);
	draw_map5();
}

/*地图7贴块：
 * tile1~4
 * tile10~16
 * tile21~24
 */
static void
draw_map7(){
	draw_tile(tile21);
	draw_tile(tile22);
	draw_map6();
}

/*地图8贴块：
 * tile1~4
 * tile17~22
 */
static void
draw_map8(){
	draw_tile(tile17);
	draw_tile(tile18);
	draw_tile(tile19);
	draw_tile(tile20);
	draw_tile(tile21);
	draw_tile(tile22);
	draw_map1();
}

/*地图9贴块：
 * tile1~4
 * tile17~24
 */
static void
draw_map9(){
	draw_tile(tile23);
	draw_tile(tile24);
	draw_map8();
}

/*
 * 检测(x,y)是否与贴块tile碰撞
 * 0：不碰撞
 * 1：碰撞
 */
static int
tile_collision_status(Tile tile,int x,int y){
	for(int i=0;i<tile.n_pointer;i++){
		if(tile.pointer_set[i].x==x&&tile.pointer_set[i].y==y){
			return 1;
		}
	}
	return 0;
}

static int 
map0_collision_status(int x,int y){
	if(tile_collision_status(tile1,x,y)||tile_collision_status(tile4,x,y)){
		return 1;
	}
	return 0;
}

static int
map1_collision_status(int x,int y){
	if(map0_collision_status(x,y)||tile_collision_status(tile2,x,y)||tile_collision_status(tile3,x,y)){
		return 1;
	}
	return 0;
}

static int 
map2_collision_status(int x,int y){
	if(map1_collision_status(x,y)||tile_collision_status(tile5,x,y)||tile_collision_status(tile6,x,y)){
		return 1;
	}
	return 0;
}

static int
map3_collision_status(int x,int y){
	if(map2_collision_status(x,y)||tile_collision_status(tile7,x,y)||tile_collision_status(tile8,x,y)){
		return 1;
	}
	return 0;
}

static int
map4_collision_status(int x,int y){
	if(map0_collision_status(x,y)\
			||tile_collision_status(tile9,x,y)||tile_collision_status(tile10,x,y)\
			||tile_collision_status(tile11,x,y)||tile_collision_status(tile12,x,y)\
			||tile_collision_status(tile13,x,y)||tile_collision_status(tile14,x,y)\
			||tile_collision_status(tile15,x,y)||tile_collision_status(tile16,x,y)){
		return 1;
	}
	return 0;
}

static int
map5_collision_status(int x,int y){
	if(map4_collision_status(x,y)||tile_collision_status(tile2,x,y)||tile_collision_status(tile3,x,y)){
		return 1;
	}
	return 0;
}

static int
map6_collision_status(int x,int y){
	if(map5_collision_status(x,y)||tile_collision_status(tile23,x,y)||tile_collision_status(tile24,x,y)){
		return 1;
	}
	return 0;
}

static int
map7_collision_status(int x,int y){
	if(map6_collision_status(x,y)||tile_collision_status(tile21,x,y)||tile_collision_status(tile22,x,y)){
		return 1;
	}
	return 0;
}

static int
map8_collision_status(int x,int y){
	if(map1_collision_status(x,y)\
			||tile_collision_status(tile17,x,y)||tile_collision_status(tile18,x,y)\
			||tile_collision_status(tile19,x,y)||tile_collision_status(tile20,x,y)\
			||tile_collision_status(tile21,x,y)||tile_collision_status(tile22,x,y)){
		return 1;
	}
	return 0;
}

static int
map9_collision_status(int x,int y){
	if(map8_collision_status(x,y)||tile_collision_status(tile23,x,y)||tile_collision_status(tile24,x,y)){
		return 1;
	}
	return 0;
}
