#pragma once
#include"graphics.h"
#include"stdlib.h"
#include"extgraph.h"
#include"diagram.h"
#include<string.h>
/*
*结构名：histogram
*作用：记录柱状图的信息
*成员：	ItemDate：节点数据日期
		ItemDiscription：数据信息链表
		NextItem：下一节点
*/
struct histogram//柱状图初始链表
{
	char date[40];
	struct discription* ItemDiscription;
	struct histogram* NextItem;
};
//-------------------------------------------------------
/*
*函数名：CreateHistogram
*形参类型：无形参
*返回值类型：struct histogram*
*功能：创建柱状图链表
*/
struct histogram* CreateHistogram(void);
/*
*函数名：DrawFilledRec
*形参类型：struct discription*
*返回值类型：无返回值
*功能：在指定位置绘制特定色彩填充的矩形
*/
void DrawFilledRec(struct discription* dp);
/*
*函数名：DrawHistogramItem
*形参类型：struct histogram*
*返回值类型：无返回值
*功能：在指定位置绘制柱状图的一项
*/
void DrawHistogramItem(struct histogram* p);
/*
*函数名：DrawHistogram
*形参类型：无形参
*返回值类型：无返回值
*功能：在指定位置绘制柱状图（创建新链表）
*/
void DrawHistogram(void);
/*
*函数名：FindRec
*形参类型：	double x：光标横坐标
			double y：光标纵坐标
*返回值类型：struct discription*
*返回值意义：	空指针：未找到
			指针：成功找到
*功能：寻找光标所在的小彩色矩形块
*/
struct discription* FindRec(double x, double y);
/*
*函数名：PutRec
*形参类型：struct discription*
*返回值类型：无返回值
*功能：将指定的小彩色矩形块变为亮灰色
*/
void PutRec(struct discription* dp);
/*
*函数名：RefreshHistogram
*形参类型：无形参
*返回值类型：无返回值
*功能：刷新柱状图
*/
void RefreshHistogram();