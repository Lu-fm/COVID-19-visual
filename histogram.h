#pragma once
#include"graphics.h"
#include"stdlib.h"
#include"extgraph.h"
#include"diagram.h"
#include<string.h>
/*
*�ṹ����histogram
*���ã���¼��״ͼ����Ϣ
*��Ա��	ItemDate���ڵ���������
		ItemDiscription��������Ϣ����
		NextItem����һ�ڵ�
*/
struct histogram//��״ͼ��ʼ����
{
	char date[40];
	struct discription* ItemDiscription;
	struct histogram* NextItem;
};
//-------------------------------------------------------
/*
*��������CreateHistogram
*�β����ͣ����β�
*����ֵ���ͣ�struct histogram*
*���ܣ�������״ͼ����
*/
struct histogram* CreateHistogram(void);
/*
*��������DrawFilledRec
*�β����ͣ�struct discription*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��λ�û����ض�ɫ�����ľ���
*/
void DrawFilledRec(struct discription* dp);
/*
*��������DrawHistogramItem
*�β����ͣ�struct histogram*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��λ�û�����״ͼ��һ��
*/
void DrawHistogramItem(struct histogram* p);
/*
*��������DrawHistogram
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ��λ�û�����״ͼ������������
*/
void DrawHistogram(void);
/*
*��������FindRec
*�β����ͣ�	double x����������
			double y�����������
*����ֵ���ͣ�struct discription*
*����ֵ���壺	��ָ�룺δ�ҵ�
			ָ�룺�ɹ��ҵ�
*���ܣ�Ѱ�ҹ�����ڵ�С��ɫ���ο�
*/
struct discription* FindRec(double x, double y);
/*
*��������PutRec
*�β����ͣ�struct discription*
*����ֵ���ͣ��޷���ֵ
*���ܣ���ָ����С��ɫ���ο��Ϊ����ɫ
*/
void PutRec(struct discription* dp);
/*
*��������RefreshHistogram
*�β����ͣ����β�
*����ֵ���ͣ��޷���ֵ
*���ܣ�ˢ����״ͼ
*/
void RefreshHistogram();