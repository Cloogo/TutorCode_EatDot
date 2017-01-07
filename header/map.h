/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月04日 19时58分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#ifndef _MAP_H_
#define _MAP_H_
#include	"color.h"
#define MAX_CAPACITY 128
#define MAP_SYMBOL 'x'
typedef struct pointer_tag Pointer;
typedef struct tile_tag Tile;
typedef void (*draw_map[10])();
typedef int (*map_collision_status_ptrs[10])(int x,int y);
typedef int (*map_collision_status_ptr)(int x,int y);

struct pointer_tag{
	int x;
	int y;
};

struct tile_tag{
	Pointer pointer_set[MAX_CAPACITY];
	int n_pointer;
};
/*
 * 初始化地图绘制函数指针和碰撞检测函数指针
 */
extern void do_init_map(draw_map &,map_collision_status_ptrs &);
#endif
