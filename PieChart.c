#include"PieChart.h"
#include "menu.h"
#include "file.h"
extern struct area GraphicArea;//»æÍ¼ÇøÓò
extern struct position CenterPosition;//±ý×´Í¼ÖÐÐÄÎ»ÖÃ
extern double radius;//±ý×´Í¼°ë¾¶
struct PieChart* PieChartHead;//±ý×´Í¼Á´±íÍ·Ö¸Õë
char date[100];//Í¼ÐÎÈÕÆÚ
extern Combine*  cop;
extern int state;

void forward(double distance, double cur_angle)
{
	DrawLine(distance * cos(cur_angle / 180 * PI), distance * sin(cur_angle / 180 * PI));
}
void move(double distance, double cur_angle)
{
	double x = GetCurrentX(), y = GetCurrentY();
	MovePen(x + distance * cos(cur_angle / 180 * PI), y + distance * sin(cur_angle / 180 * PI));
}
double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void DrawPieChart(void)
{
	initialize();
	struct PieChart* p_a  = NULL;
	p_a = (struct PieChart*)malloc(sizeof(struct PieChart));
	int n;
	if(isHubei)
		n = 2;
	else n = cop->line - 2;
	PieChartHead = CreatePieChart(n);
	p_a = PieChartHead;         
	for (int i = 1; p_a!=NULL && i <= n; i++)
	{
		DrawPieChartItem(p_a);
		p_a = p_a->NextItem;
	}
	MovePen(GraphicArea.x, GraphicArea.y);
	DrawTextString(cop->date);
}
struct PieChart* CreatePieChart(int n)
{
	double frac = 0;
	static char *lable[] = { "Hubei", "OutsideHubei" };
	struct PieChart* head, * tail, * p;
	Data *dpp, *pp, *ppp;
	dpp = cop->head;
	pp = Search("OtherProvince", dpp, PRO_STA);
	ppp = Search("Hubei", dpp, PRO_STA);
	head = tail = NULL;
	if (isHubei)
	{
		for (int i = 0; i < n; i++)
		{
			p = (struct PieChart*)malloc(sizeof(struct PieChart));
			strcpy(p->name, lable[i]);
			strcpy(p->ColorName, ChooseColors(i+1));
			if (i == 0)
				p->fraction = 1.0*ppp->figure[state] /( pp->figure[state] + ppp->figure[state]);
			else p->fraction = 1.0*pp->figure[state] / ( pp->figure[state] + ppp->figure[state]);
			p->StartAngle = frac * 360;
			p->EndAngle = (frac + p->fraction) * 360;
			p->NextItem = NULL;
			frac += p->fraction;
			if (!head)
				head = p;
			else tail->NextItem = p;
			tail = p;
		}

	}
	else
	{
		for (int i = 0; dpp != NULL && i < n; i++)
		{
			
			if (strcmp(dpp->column[PRO_STA], "Hubei") == 0)
			{
				dpp = dpp->next;
				continue;
			}
			p = (struct PieChart*)malloc(sizeof(struct PieChart));
			strcpy(p->name, dpp->column[PRO_STA]);
			if (i + 1 == n && n % 5 == 1)
				i++;
			strcpy(p->ColorName, ChooseColors(i + 1));
			if (i == n)
				i--;
			p->fraction = dpp->fraction[state];
			p->StartAngle = frac * 360;
			p->EndAngle = (frac + dpp->fraction[state]) * 360;
			frac += dpp->fraction[state];
			p->NextItem = NULL;
			if (head == NULL)
				head = p;
			else
				tail->NextItem = p;
			tail = p;
			dpp = dpp->next;
		}
	}
	return head;
}
void DrawPieChartItem(struct PieChart* p)
{
	MovePen(CenterPosition.x, CenterPosition.y);
	SetPenColor(p->ColorName);
	StartFilledRegion(1);
	forward(radius, p->StartAngle);
	DrawArc(radius, p->StartAngle, p->fraction * 360);
	EndFilledRegion();
	SetPenColor("BLACK");
	MovePen(CenterPosition.x, CenterPosition.y);
}
struct PieChart* FindPie(double x, double y)
{
	double d = distance(x, y, CenterPosition.x, CenterPosition.y);
	if (d <= radius)
	{
		double angle;
		if (x >= CenterPosition.x)
		{
			angle = asin((y - CenterPosition.y) / d) / PI * 180;
			if (angle < 0)
				angle += 360;
		}
		else
		{
			angle = asin((y - CenterPosition.y) / d) / PI * 180;
			angle = 180 - angle;
		}
		struct PieChart* p;
		p = PieChartHead;
		while (p != NULL)
		{
			if (angle >= p->StartAngle && angle <= p->EndAngle)
				return p;
			p = p->NextItem;
		}
	}
	return NULL;
}
void PutPie(struct PieChart* p)
{
	if (p != NULL)
	{
		strcpy(p->ColorName, "Light Gray");
		DrawPieChartItem(p);
		char str[100];
		sprintf(str, "Name:%s,Fraction:%%%.2f", p->name, p->fraction * 100);
		MovePen(0.5 * GetWindowWidth() - 0.5 * TextStringWidth(str), 0.05);
		DrawTextString(str);
	}
}
void RefreshPieChart(void)
{
	RemoveDiagram();
	struct PieChart* p = PieChartHead;
	for (int i = 0; p != NULL; i++, p = p->NextItem)
	{
		if (p->NextItem == NULL && (i + 1) % 15 == 1)
			i++;
		strcpy(p->ColorName, ChooseColors(i + 1));
	}
	p = PieChartHead;
	while (p != NULL)
	{
		DrawPieChartItem(p);
		p = p->NextItem;
	}
	MovePen(GraphicArea.x, GraphicArea.y);
	DrawTextString(date);
}