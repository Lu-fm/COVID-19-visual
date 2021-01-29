#pragma once
#include<string.h>
#include"graphics.h"
#include"extgraph.h"
#include<ctype.h>
#include<math.h>
/*
*结构名：position
*作用：记录点的坐标
*/
struct position
{
	double x, y;
};
/*
*结构名：area
*作用：记录矩形区域的左下起始点的坐标和宽度、长度
*/
struct area
{
	double x, y, width, height;
};
/*
*结构名：discription
*作用：记录柱状图和折线图每一个日期上的每一个数据的信息
*成员：	num：数量信息
		ColorName：颜色名称
		ItemPosition：	柱状图：小矩形色块左上角点的坐标
						折线图：点的坐标
		NextDiscription：链表下一节点
*/
struct discription
{
	int num;
	char name[20];
	char ColorName[20];
	struct position ItemPosition;
	struct discription* NextDiscription;
};
//-------------------------------------------------------
/*
*函数名：DrawAxis
*形参类型：无形参
*返回值类型：无返回值
*功能：根据绘图区域信息及图表原点信息绘制坐标轴
*/
void DrawAxis(void);
/*
*函数名：inGraphicArea
*形参类型：	double x：光标当前x坐标
			double y：光标当前y坐标
*返回值类型： int：0/1
*返回值意义：	0：光标不在绘图区域
			1：光标在绘图区域
*功能：根据绘图区域信息及图表原点信息绘制坐标轴
*/
int isinArea(double x, double y);
/*
*函数名：RemoveDiagram
*形参类型：无形参
*返回值类型：无返回值
*功能：清除当前绘图区域
*/
void RemoveDiagram(void);
char* ChooseColors(int i);
void initialize(void);
void DrawBaseline(void);
void DrawRecPoint(double x, double y);
void DrawHaulArea(void);
void RemoveHaulArea(void);
void CalHaulArea(void);