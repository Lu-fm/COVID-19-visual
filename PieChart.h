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
*�ṹ����PieChart
*���ã���¼��״ͼ����Ϣ
*��Ա��	name��С���ε�����
		ColorName��С������ɫ��
		fraction��С�������ݣ�%��
		StartAngle, EndAngle��С���λ�����Ϣ����ʼ����ֹ�Ƕ�
		NextItem����һ�ڵ�
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
*��������CreatePieChart
*�β����ͣ�int n�����ݸ���
		  int state: ȷ��, ����, ��ָ�
*����ֵ���ͣ�struct PieChart*
*���ܣ�������״ͼ����
*/
struct PieChart* CreatePieChart(int n);
/*
*��������forward
*�β����ͣ�	double distance���ƶ���
			double cur_angle���ƶ�����
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ������ָ�����ȵ��߶�
*/
void forward(double distance, double cur_angle);
/*
*��������move
*�β����ͣ�	double distance���ƶ���
			double cur_angle���ƶ�����
*����ֵ���ͣ��޷���ֵ
*���ܣ�������ָ�������ƶ�ָ������
*/
void move(double distance, double cur_angle);
/*
*��������DrawPieChartItem
*�β����ͣ�struct PieChart*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ���������һ��С����
*/
void DrawPieChartItem(struct PieChart* p);
/*
*��������move
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��������Ʊ�״ͼ����������
*/
void DrawPieChart(void);
/*
*��������FindPie
*�β����ͣ�	double x����������
			double y�����������
*����ֵ���ͣ�struct PieChart*
*����ֵ���壺	��ָ�룺δ�ҵ�
			ָ�룺�ɹ��ҵ�
*���ܣ�Ѱ�ҹ�����ڵ�С����
*/
struct PieChart* FindPie(double x, double y);
/*
*��������PutPie
*�β����ͣ�struct PieChart*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ����С���α�Ϊ����ɫ
*/
void PutPie(struct PieChart* p);
/*
*��������distance
*�β����ͣ�	double x1����A������
			double y1����A������
			double x2����B������
			double y2����B������
*����ֵ���ͣ�double
*���ܣ�������������
*/
double distance(double x1, double y1, double x2, double y2);
/*
*��������RefreshPieChart
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ�ˢ�±�״ͼ
*/
void RefreshPieChart(void);