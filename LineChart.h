#pragma once
#include"graphics.h"
#include"diagram.h"
#include<stdlib.h>
#include<string.h>
#include"extgraph.h"
#include<Windows.h>
/*
*结构名：LineChart
*作用：记录折线图的信息
*成员：	ItemDate：节点数据日期
		ItemDiscription：数据信息链表
		NextItem：下一节点
*/
struct LineChart
{
	char date[20];
	struct discription* ItemDiscription;
	struct LineChart* NextItem;
};
//-------------------------------------------------------
/*
*函数名：CreateLineChart
*形参类型：无形参
*返回值类型：struct LineChart*
*功能：创建折线图链表
*/
struct LineChart* CreateLineChart(void);
/*
*函数名：DrawLineChartItem
*形参类型：struct LineChart*
*返回值类型：无返回值
*功能：在指定位置描点（折线图一个日期上的数据点）
*/
void DrawLineChartItem(struct LineChart* p);
/*
*函数名：DrawInnerLine
*形参类型：struct LineChart*
*返回值类型：无返回值
*功能：绘制两个日期间的彩色线段
*/
void DrawInnerLine(struct LineChart* p1, struct LineChart* p2);
/*
*函数名：DrawLineChart
*形参类型：无形参
*返回值类型：无返回值
*功能：在指定位置绘制折线图（创建新链表）
*/
void DrawLineChart(void);
/*
*函数名：FindLine
*形参类型：	double x：光标横坐标
			double y：光标纵坐标
*返回值类型：char*
*返回值意义：	空指针：未找到
			指针：成功找到
*功能：寻找光标所在的线段
*/
char* FindLine(double x, double y);
/*
*函数名：PutLine
*形参类型：char* color：颜色名
*返回值类型：无返回值
*功能：将指定颜色的折线变为亮灰色
*/
void PutLine(char* color, struct discription* dp0);
/*
*函数名：RefreshHistogram
*形参类型：无形参
*返回值类型：无返回值
*功能：刷新折线图
*/
void RefreshLineChart(void);
/*
*函数名：FindLinePoint
*形参类型：	double x：光标横坐标
			double y：光标纵坐标
*返回值类型：struct discription*
*返回值意义：	空指针：未找到
			指针：成功找到
*功能：寻找光标所在折线端点
*/
struct discription* FindLinePoint(double x, double y);