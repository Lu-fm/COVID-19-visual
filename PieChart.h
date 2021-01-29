#pragma once
#include"graphics.h"
#include"extgraph.h"
#include"diagram.h"
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define PI 3.1415926
/*
*结构名：PieChart
*作用：记录饼状图的信息
*成员：	name：小扇形的名称
		ColorName：小扇形颜色名
		fraction：小扇形数据（%）
		StartAngle, EndAngle：小扇形绘制信息：起始及终止角度
		NextItem：下一节点
*/
struct PieChart
{
	char name[20];
	char ColorName[20];
	double fraction;
	double StartAngle, EndAngle;
	struct PieChart* NextItem;
};
//-------------------------------------------------------
/*
*函数名：CreatePieChart
*形参类型：int n：数据个数
		  int state: 确诊, 死亡, 或恢复
*返回值类型：struct PieChart*
*功能：创建饼状图链表
*/
struct PieChart* CreatePieChart(int n);
/*
*函数名：forward
*形参类型：	double distance：移动量
			double cur_angle：移动方向
*返回值类型：无返回值
*功能：向指定方向画指定长度的线段
*/
void forward(double distance, double cur_angle);
/*
*函数名：move
*形参类型：	double distance：移动量
			double cur_angle：移动方向
*返回值类型：无返回值
*功能：画笔向指定方向移动指定长度
*/
void move(double distance, double cur_angle);
/*
*函数名：DrawPieChartItem
*形参类型：struct PieChart*
*返回值类型：无返回值
*功能：在指定区域绘制一个小扇形
*/
void DrawPieChartItem(struct PieChart* p);
/*
*函数名：move
*形参类型：无形参
*返回值类型：无返回值
*功能：在指定区域绘制饼状图（创建链表）
*/
void DrawPieChart(void);
/*
*函数名：FindPie
*形参类型：	double x：光标横坐标
			double y：光标纵坐标
*返回值类型：struct PieChart*
*返回值意义：	空指针：未找到
			指针：成功找到
*功能：寻找光标所在的小扇形
*/
struct PieChart* FindPie(double x, double y);
/*
*函数名：PutPie
*形参类型：struct PieChart*
*返回值类型：无返回值
*功能：将指定的小扇形变为亮灰色
*/
void PutPie(struct PieChart* p);
/*
*函数名：distance
*形参类型：	double x1：点A横坐标
			double y1：点A纵坐标
			double x2：点B横坐标
			double y2：点B纵坐标
*返回值类型：double
*功能：计算两点间距离
*/
double distance(double x1, double y1, double x2, double y2);
/*
*函数名：RefreshPieChart
*形参类型：无形参
*返回值类型：无返回值
*功能：刷新饼状图
*/
void RefreshPieChart(void);