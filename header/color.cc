/*
 * =====================================================================================
 *
 *       Filename:  color.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月06日 13时33分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#include	"color.h"

int
check_color_system(){
	if(has_colors()){
		start_color();
		return 1;
	}
	return 0;
}

void
init_color_manager(){
	init_pair(BORDER,COLOR_RED,COLOR_RED);
	init_pair(ATTR_NAME,COLOR_GREEN,COLOR_BLACK);
	init_pair(ATTR_VALUE,COLOR_YELLOW,COLOR_WHITE);
	init_pair(SNAKE_HEAD,COLOR_YELLOW,COLOR_GREEN);
	init_pair(SNAKE_BODY,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(LEVEL_UP,COLOR_BLUE,COLOR_GREEN);
	init_pair(WARNING,COLOR_RED,COLOR_BLACK);
	init_pair(WALL,COLOR_BLUE,COLOR_BLUE);
	init_pair(FOOD,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(OPERATE_INFO,COLOR_WHITE,COLOR_BLACK);
	init_pair(SCORE,COLOR_YELLOW,COLOR_BLACK);
}
