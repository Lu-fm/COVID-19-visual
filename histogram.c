#include"histogram.h"
#include "file.h"
extern struct position DiagramOrigin;//柱状图和折线图原点位置
extern double XLength;//x轴长度
extern double YLength;//y轴长度
static int DateNum;//日期数量
static int GroupNum;//每个日期下的数据个数
struct histogram* HistogramHead;//柱状图链表头指针
static double RecWidth;//小彩色矩形块宽度
static double gap;//横坐标之间的距离
extern int max;
extern int state;
extern Combine*  cop;
void DrawHistogram(void)
{
	initialize();
	struct histogram* p;
	DateNum = cop->line, GroupNum = 3;
	gap = XLength * 1.0 / (DateNum + 1);
	RecWidth = 0.5 * gap / GroupNum;
	max = cop->max[state];
	DrawAxis();
	HistogramHead = CreateHistogram();
	p = HistogramHead;
	while (p != NULL)
	{
		DrawHistogramItem(p);
		p = p->NextItem;
	}
}
struct histogram* CreateHistogram(void)
{
	DateNum = cop->line;
	struct histogram* head, * tail, * p;
	struct discription* dhead, * dtail, * dp;
	Data *dpp[3] = {NULL};
	for (int i = 0; i < 3; i++)
		dpp[i] = cop->dp[i];
	head = tail = NULL;
	for (int i = 0; i < DateNum; i++) {
		p = (struct histogram*)malloc(sizeof(struct histogram));
		strcpy(p->date, dpp[0]->column[UPDATE_TIME]);
		dhead = dtail = NULL;
		for (int j = 0; j < GroupNum; j++)
		{
			dp = (struct discription*)malloc(sizeof(struct discription));
			dp->num = dpp[j]->figure[state];
			if (j == GroupNum - 1)
				strcpy(dp->name, dpp[j]->column[COU_RIG]);
			else
				strcpy(dp->name, dpp[j]->column[PRO_STA]);
			strcpy(dp->ColorName, ChooseColors(j + 1));
			dp->ItemPosition.x = DiagramOrigin.x + (i + 1) * gap + j * RecWidth;
			dp->ItemPosition.y = DiagramOrigin.y + YLength * (dpp[j]->figure[state] * 1.0 / max);
			dp->NextDiscription = NULL;
			if (dhead == NULL)
				dhead = dp;
			else
				dtail->NextDiscription = dp;
			dtail = dp;
			dpp[j] = dpp[j]->next;
		}
		p->ItemDiscription = dhead;
		p->NextItem = NULL;
		if (head == NULL)
			head = p;
		else
			tail->NextItem = p;
		tail = p;
	}
	return head;
}
void DrawHistogramItem(struct histogram* p)
{
	struct discription* dp;
	dp = p->ItemDiscription;
	MovePen(dp->ItemPosition.x, DiagramOrigin.y - GetFontHeight());
	DrawTextString(p->date);
	while (dp != NULL)
	{
		DrawFilledRec(dp);
		dp = dp->NextDiscription;
	}
}
void DrawFilledRec(struct discription* dp)
{
	MovePen(dp->ItemPosition.x, dp->ItemPosition.y);
	SetPenColor(dp->ColorName);
	StartFilledRegion(1);
	DrawLine(0, -dp->ItemPosition.y + DiagramOrigin.y);
	DrawLine(RecWidth, 0);
	DrawLine(0, dp->ItemPosition.y - DiagramOrigin.y);
	DrawLine(-RecWidth, 0);
	EndFilledRegion();
	SetPenColor("BLACK");
}
struct discription* FindRec(double x, double y)
{
	struct histogram* p;
	struct discription* dp;
	p = HistogramHead;
	while (p != NULL)
	{
		dp = p->ItemDiscription;
		while (dp != NULL)
		{
			if (x >= dp->ItemPosition.x && x <= dp->ItemPosition.x + RecWidth && y >= DiagramOrigin.y && y <= dp->ItemPosition.y)
				return dp;
			dp = dp->NextDiscription;
		}
		p = p->NextItem;
	}
	return NULL;
}
void PutRec(struct discription* dp)
{
	if (dp != NULL)
	{
		char str1[100],str2[100];
		strcpy(dp->ColorName, "Light Gray");
		DrawFilledRec(dp);
		strcpy(str1, dp->name);
		sprintf(str2, "    Number:%d", dp->num);
		strcat(str1, str2);
		MovePen(0.5 * GetWindowWidth() - 0.5 * TextStringWidth(str1), DiagramOrigin.y - 2 * GetFontHeight());
		DrawTextString(str1);
	}
}
void RefreshHistogram(void)
{
	RemoveDiagram();
	DrawAxis();
	struct histogram* p = HistogramHead;
	struct discription* dp;
	int i = 0;
	gap = XLength * 1.0 / (DateNum + 1);
	RecWidth = 0.5 * gap / GroupNum;
	while (p != NULL)
	{
		dp = p->ItemDiscription;
		for (int j = 0; dp != NULL; j++, dp = dp->NextDiscription)
		{
			strcpy(dp->ColorName, ChooseColors(j + 1));
			dp->ItemPosition.x = DiagramOrigin.x + (i + 1) * gap + j * RecWidth;
		}
		p = p->NextItem;
		i++;
	}
	p = HistogramHead;
	while (p != NULL)
	{
		DrawHistogramItem(p);
		p = p->NextItem;
	}
}