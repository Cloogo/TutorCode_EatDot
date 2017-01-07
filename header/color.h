/*
 * =====================================================================================
 *
 *       Filename:  color.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月06日 13时23分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#ifndef _COLOR_H_
#define _COLOR_H_


#include	<ncursesw/ncurses.h>

extern int check_color_system();
extern void init_color_manager();

enum color_index_tag{
	INVALID,
	BORDER,
	ATTR_NAME,
	ATTR_VALUE,
	WALL,
	FOOD,
	SNAKE_HEAD,
	SNAKE_BODY,
	SCORE,
	LEVEL_UP,
	WARNING,
	OPERATE_INFO
};

#endif
