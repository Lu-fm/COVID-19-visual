#pragma once
#include<string.h>
#include"graphics.h"
#include"extgraph.h"
#include<ctype.h>
#include<math.h>
/*
*�ṹ����position
*���ã���¼�������
*/
struct position
{
	double x, y;
};
/*
*�ṹ����area
*���ã���¼���������������ʼ�������Ϳ�ȡ�����
*/
struct area
{
	double x, y, width, height;
};
/*
*�ṹ����discription
*���ã���¼��״ͼ������ͼÿһ�������ϵ�ÿһ�����ݵ���Ϣ
*��Ա��	num��������Ϣ
		ColorName����ɫ����
		ItemPosition��	��״ͼ��С����ɫ�����Ͻǵ������
						����ͼ���������
		NextDiscription��������һ�ڵ�
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
*��������DrawAxis
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ����ݻ�ͼ������Ϣ��ͼ��ԭ����Ϣ����������
*/
void DrawAxis(void);
/*
*��������inGraphicArea
*�β����ͣ�	double x����굱ǰx����
			double y����굱ǰy����
*����ֵ���ͣ� int��0/1
*����ֵ���壺	0����겻�ڻ�ͼ����
			1������ڻ�ͼ����
*���ܣ����ݻ�ͼ������Ϣ��ͼ��ԭ����Ϣ����������
*/
int isinArea(double x, double y);
/*
*��������RemoveDiagram
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ������ǰ��ͼ����
*/
void RemoveDiagram(void);
char* ChooseColors(int i);
void initialize(void);
void DrawBaseline(void);
void DrawRecPoint(double x, double y);
void DrawHaulArea(void);
void RemoveHaulArea(void);
void CalHaulArea(void);