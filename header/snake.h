/*
 * =====================================================================================
 *
 *       Filename:  snake.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年08月03日 11时07分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Cloogo. (bft), wang691234@gmail.com
 *        Company:  South China Agricultural University
 *
 * =====================================================================================
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_
#include    "map.h"
#define BODY_LENGTH 255//实际蛇身长为BODY_LENGTH-1
#define HEAD_SYMBOL 'O'
#define BODY_SYMBOL '2'

typedef struct snake_node_tag Snake_node;
typedef struct snake_tag Snake;
/*
 * 蛇节点位置信息
 */
struct snake_node_tag{
	int x;
	int y;
};

/*
 * 蛇整体构造
 */
struct snake_tag{
	Snake_node body[BODY_LENGTH];//蛇身
	int head;//蛇尾
	int tail;//蛇头
};

/*
 * 蛇移动方向
 */
enum snake_direct_tag{
	UP,DOWN,LEFT,RIGHT
};

typedef enum snake_direct_tag Snake_direct;
/*
 * 初始化蛇长
 */
extern void do_initial_snake();
/*
 * 蛇的移动
 */
extern void move_forward(Snake_direct direct,map_collision_status_ptr map_collision_status);
/*
 * 绘制蛇
 */
extern void draw_snake();
/*
 * 获得蛇长,以便判断是否取得胜利
 */
extern int get_snake_length();
/*
 * 设置蛇等级
 * 用途：地图绘制与碰撞检测
 */
extern void set_level(int level);
extern int get_level();
/*
 * 获得／设置碰撞状态，用于计算生命值
 * 返回值：
 * 0:不碰撞
 * 1:碰撞
 */
extern int get_collision_status();
extern void set_collision_status();
/*
 * 设置碰撞边界
 * 合法边界：蛇可移动到边界
 * x1:左边界
 * y1:上边界
 * x2:右边界
 * y2:下边界
 */
extern void set_boundary(int x1,int y1,int x2,int y2);
/*
 * 设置食物位置,方便设置食物状态
 */
extern void set_food_pos(int x,int y);
/*
 * 获得食物状态
 * 返回值：
 * 0:食物未被吃掉
 * 1:食物已被吃掉
 */
extern int get_food_status();
/*
 * 设置颜色支持
 * supported:
 * 1:支持
 * 0:不支持
 */
extern void set_color_status(int supported);
#endif
