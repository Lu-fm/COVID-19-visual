#include"LineChart.h"
#include"file.h"
extern struct position DiagramOrigin;//柱状图和折线图原点位置
extern double XLength;//x轴长度
extern double YLength;//y轴长度
extern double PointLength;
struct LineChart* LineChartHead;//折线图头指针
static double gap;//日期之间距离
static int DateNum;//日期数量
static int GroupNum = 3;//每个日期下的数据个数
extern int max;
extern int state;
extern Combine* cop;
void DrawLineChart(void)
{
	max = cop->max[state];
	initialize();
	struct LineChart* p;
	DateNum = cop->line;
	gap = XLength * 1.0 / (DateNum + 1);
	LineChartHead = CreateLineChart();
	DrawAxis();
	p = LineChartHead;
	while (p != NULL)
	{
		DrawLineChartItem(p);
		if (p->NextItem != NULL)
			DrawInnerLine(p, p->NextItem);
		p = p->NextItem;
	}
}
struct LineChart* CreateLineChart(void)
{
	DateNum = cop->line;
	struct LineChart* head, * tail, * p;
	struct discription* dhead, * dtail, * dp;
	Data* dpp[3] = { NULL };
	for (int i = 0; i < 3; i++)
		dpp[i] = cop->dp[i];
	head = tail = NULL;
	for (int i = 0; i < DateNum; i++)
	{
		p = (struct LineChart*)malloc(sizeof(struct LineChart));

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
			dp->ItemPosition.x = DiagramOrigin.x + (i + 1) * gap;
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
void DrawLineChartItem(struct LineChart* p)
{
	struct discription* dp;
	dp = p->ItemDiscription;
	MovePen(dp->ItemPosition.x - 0.5 * TextStringWidth(p->date), DiagramOrigin.y - GetFontHeight());
	DrawTextString(p->date);
	while (dp != NULL)
	{
		SetPenColor(dp->ColorName);
		if (strcmp(dp->ColorName, "Light Gray") == 0)
			PointLength *= 1.25;
		StartFilledRegion(1);
		SetPenColor(dp->ColorName);
		DrawRecPoint(dp->ItemPosition.x, dp->ItemPosition.y);
		EndFilledRegion();
		if (strcmp(dp->ColorName, "Light Gray") == 0)
			PointLength /= 1.25;
		dp = dp->NextDiscription;
	}
	SetPenColor("BLACK");
}
void DrawInnerLine(struct LineChart* p1, struct LineChart* p2)
{
	struct discription* dp1, * dp2;
	dp1 = p1->ItemDiscription;
	dp2 = p2->ItemDiscription;
	while (dp1 != NULL)
	{
		MovePen(dp1->ItemPosition.x, dp1->ItemPosition.y);
		SetPenColor(dp1->ColorName);
		DrawLine(dp2->ItemPosition.x - dp1->ItemPosition.x, dp2->ItemPosition.y - dp1->ItemPosition.y);
		dp1 = dp1->NextDiscription;
		dp2 = dp2->NextDiscription;
	}
	SetPenColor("BLACK");
}
char* FindLine(double x, double y)
{
	struct LineChart* p;
	p = LineChartHead;
	struct discription* dp1, * dp2;
	double LineFunctionY;
	static char str[20];
	while (p->NextItem != NULL)
	{
		if (x >= p->ItemDiscription->ItemPosition.x && x <= p->NextItem->ItemDiscription->ItemPosition.x)
		{
			dp1 = p->ItemDiscription;
			dp2 = p->NextItem->ItemDiscription;
			while (dp1 != NULL)
			{
				LineFunctionY = dp1->ItemPosition.y + (dp2->ItemPosition.y - dp1->ItemPosition.y) * (x - dp1->ItemPosition.x) / (dp2->ItemPosition.x - dp1->ItemPosition.x);
				if (y >= LineFunctionY - PointLength && y <= LineFunctionY + PointLength)
				{
					strcpy(str, dp1->ColorName);
					return str;
				}
				dp1 = dp1->NextDiscription;
				dp2 = dp2->NextDiscription;
			}
		}
		p = p->NextItem;
	}
	strcpy(str, "WHITE");
	return str;
}
void PutLine(char* color, struct discription* dp0)
{
	if (strcmp(color, "WHITE") != 0)
	{
		struct LineChart* p;
		struct discription* dp;
		char str[20] = { '\0' };
		p = LineChartHead;
		while (p != NULL)
		{
			dp = p->ItemDiscription;
			while (dp != NULL)
			{
				if (strcmp(dp->ColorName, color) == 0)
				{
					strcpy(dp->ColorName, "Light Gray");
					if (str[0] == '\0')
					{
						strcpy(str, dp->name);
					}
					break;
				}
				dp = dp->NextDiscription;
			}
			p = p->NextItem;
		}
		p = LineChartHead;
		while (p != NULL)
		{
			DrawLineChartItem(p);
			if (p->NextItem != NULL)
				DrawInnerLine(p, p->NextItem);
			p = p->NextItem;
		}
		if (dp0 == NULL)
		{
			MovePen(0.5 * GetWindowWidth() - 0.5 * TextStringWidth(str), DiagramOrigin.y - 2 * GetFontHeight());
			DrawTextString(str);
		}
		else
		{
			char str1[100], str2[100];
			strcpy(str1, dp0->name);
			sprintf(str2, "   Number:%d", dp0->num);
			strcat(str1, str2);
			MovePen(0.5 * GetWindowWidth() - 0.5 * TextStringWidth(str1), DiagramOrigin.y - 2 * GetFontHeight());
			DrawTextString(str1);
		}
		DrawAxis();
	}
}
struct discription* FindLinePoint(double x, double y)
{
	struct LineChart* p = LineChartHead;
	struct discription* dp;
	while (p != NULL)
	{
		dp = p->ItemDiscription;
		while (dp != NULL)
		{
			if (x >= dp->ItemPosition.x - 0.5 * PointLength && x <= dp->ItemPosition.x + 0.5 * PointLength
				&& y >= dp->ItemPosition.y - 0.5 * PointLength && y <= dp->ItemPosition.y + 0.5 * PointLength)
				return dp;
			dp = dp->NextDiscription;
		}
		p = p->NextItem;
	}
	return NULL;
}
void RefreshLineChart()
{
	RemoveDiagram();
	DrawAxis();
	gap = XLength * 1.0 / (DateNum + 1);
	struct LineChart* p = LineChartHead;
	struct discription* dp;
	int i = 0;
	while (p != NULL)
	{
		dp = p->ItemDiscription;
		for (int j = 0; dp != NULL; j++, dp = dp->NextDiscription)
		{
			strcpy(dp->ColorName, ChooseColors(j + 1));
			dp->ItemPosition.x = DiagramOrigin.x + (i + 1) * gap;
		}
		p = p->NextItem;
		i++;
	}
	p = LineChartHead;
	while (p != NULL)
	{
		DrawLineChartItem(p);
		if (p->NextItem != NULL)
			DrawInnerLine(p, p->NextItem);
		p = p->NextItem;
	}
}