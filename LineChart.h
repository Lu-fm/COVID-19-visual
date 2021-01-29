#pragma once
#include"graphics.h"
#include"diagram.h"
#include<stdlib.h>
#include<string.h>
#include"extgraph.h"
#include<Windows.h>
/*
*�ṹ����LineChart
*���ã���¼����ͼ����Ϣ
*��Ա��	ItemDate���ڵ���������
		ItemDiscription��������Ϣ����
		NextItem����һ�ڵ�
*/
struct LineChart
{
	char date[20];
	struct discription* ItemDiscription;
	struct LineChart* NextItem;
};
//-------------------------------------------------------
/*
*��������CreateLineChart
*�β����ͣ����β�
*����ֵ���ͣ�struct LineChart*
*���ܣ���������ͼ����
*/
struct LineChart* CreateLineChart(void);
/*
*��������DrawLineChartItem
*�β����ͣ�struct LineChart*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��λ����㣨����ͼһ�������ϵ����ݵ㣩
*/
void DrawLineChartItem(struct LineChart* p);
/*
*��������DrawInnerLine
*�β����ͣ�struct LineChart*
*����ֵ���ͣ��޷���ֵ
*���ܣ������������ڼ�Ĳ�ɫ�߶�
*/
void DrawInnerLine(struct LineChart* p1, struct LineChart* p2);
/*
*��������DrawLineChart
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��λ�û�������ͼ������������
*/
void DrawLineChart(void);
/*
*��������FindLine
*�β����ͣ�	double x����������
			double y�����������
*����ֵ���ͣ�char*
*����ֵ���壺	��ָ�룺δ�ҵ�
			ָ�룺�ɹ��ҵ�
*���ܣ�Ѱ�ҹ�����ڵ��߶�
*/
char* FindLine(double x, double y);
/*
*��������PutLine
*�β����ͣ�char* color����ɫ��
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ����ɫ�����߱�Ϊ����ɫ
*/
void PutLine(char* color, struct discription* dp0);
/*
*��������RefreshHistogram
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ�ˢ������ͼ
*/
void RefreshLineChart(void);
/*
*��������FindLinePoint
*�β����ͣ�	double x����������
			double y�����������
*����ֵ���ͣ�struct discription*
*����ֵ���壺	��ָ�룺δ�ҵ�
			ָ�룺�ɹ��ҵ�
*���ܣ�Ѱ�ҹ���������߶˵�
*/
struct discription* FindLinePoint(double x, double y);