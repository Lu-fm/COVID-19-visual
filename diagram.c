#include"diagram.h"
struct area GraphicArea;//绘图区域
struct area HaulArea;
char HaulAreaColor[20];
struct position DiagramOrigin;//柱状图和折线图原点位置
double XLength;//x轴长度
double YLength;//y轴长度
struct position CenterPosition;//饼状图中心位置
double radius;//饼状图半径
double PointLength = 0.05;//小方点边长
double k;//拖动条放大系数
int max;//最大数据值
void DrawAxis(void)
{
	char str[10];
	MovePen(DiagramOrigin.x, DiagramOrigin.y);
	DrawLine(XLength, 0);
	sprintf(str, "Date");
	DrawTextString(str);
	MovePen(DiagramOrigin.x, DiagramOrigin.y);
	DrawLine(0, YLength);
	sprintf(str, "Number");
	MovePen(GetCurrentX() - TextStringWidth(str), GetCurrentY());
	DrawTextString(str);
	DrawBaseline();
	SetPenColor("Black");
}
int isinArea(double x, double y)
{
	if (x >= GraphicArea.x && x <= GraphicArea.x + GraphicArea.width && y >= GraphicArea.y && y <= GraphicArea.y + GraphicArea.height)
		return 1;
	else if (x >= HaulArea.x && x <= HaulArea.x + HaulArea.width && y >= HaulArea.y && y <= HaulArea.y + HaulArea.height)
		return 2;
	else
		return 0;
}
void RemoveDiagram(void)
{
	SetEraseMode(TRUE);
	StartFilledRegion(1);
	MovePen(GraphicArea.x, GraphicArea.y);
	DrawLine(GraphicArea.width, 0);
	DrawLine(0, GraphicArea.height);
	DrawLine(-GraphicArea.width, 0);
	DrawLine(0, -GraphicArea.height);
	EndFilledRegion();
	SetEraseMode(FALSE);
}
char* ChooseColors(int i)
{
	static char str[20];
	switch (i%15)
	{
	case 1:strcpy(str, "Red"); break;
	case 2:strcpy(str, "Green"); break;
	case 3:strcpy(str, "Blue"); break;
	case 4:strcpy(str, "Violet"); break;
	case 5:strcpy(str, "Magenta"); break;
	case 6:strcpy(str, "Cyan"); break;
	case 7:strcpy(str, "Brown"); break;
	case 8:strcpy(str, "Red1"); break;
	case 9:strcpy(str, "Pink1"); break;
	case 10:strcpy(str, "Flesh1"); break;
	case 11:strcpy(str, "Green1"); break;
	case 12:strcpy(str, "Blue1"); break;
	case 13:strcpy(str, "Wine1"); break;
	default:strcpy(str, "Black"); break;
	}
	return str;
}
void initialize(void)
{
	GraphicArea.x =  0;//绘图区域可以放到交互函数中
	GraphicArea.y = 0.5;
	GraphicArea.height = 0.5 * GetWindowHeight()- GraphicArea.y;
	GraphicArea.width = GetWindowWidth();
	XLength = 3 * GraphicArea.width / 4;
	YLength = 0.75 * GraphicArea.height;
	CenterPosition.x = 0.5 * GraphicArea.width + GraphicArea.x;
	CenterPosition.y = 0.5 * GraphicArea.height + GraphicArea.y;
	radius = 0.5 * GraphicArea.height * 0.8;
	DiagramOrigin.x = GraphicArea.width / 8 + GraphicArea.x;
	DiagramOrigin.y = GraphicArea.height / 8 + GraphicArea.y;
	HaulArea.x = HaulArea.y = 0;
	HaulArea.width = GetWindowWidth();
	HaulArea.height = 0.25;
	k = XLength / GetWindowWidth();
	strcpy(HaulAreaColor, "Dark Gray");
}
void DrawBaseline(void)
{
	char buffer[20],str[20];
	itoa(max, buffer, 10);
	int cnt,num_gap,num;
	cnt = strlen(buffer);
	num_gap = pow(10, cnt - 1);
	if (max / num_gap + 1 <= 3)
	{
		num_gap = 5 * pow(10, cnt - 2);
	}
	for (num = num_gap; num <= max; num += num_gap)
	{
		SetPenColor("Black");
		sprintf(str, "%d", num);
		MovePen(DiagramOrigin.x - TextStringWidth(str) - 0.05, DiagramOrigin.y + num * 1.0 / max * YLength - 0.5 * GetFontHeight());
		DrawTextString(str);
		SetPenColor("Light Gray");
		MovePen(DiagramOrigin.x, DiagramOrigin.y + num * 1.0 / max * YLength);
		DrawLine(XLength, 0);
		SetPenColor("Black");
	}
}
void DrawRecPoint(double x, double y)
{
	MovePen(x - 0.5 * PointLength, y + 0.5 * PointLength);
	DrawLine(PointLength, 0);
	DrawLine(0, -PointLength);
	DrawLine(-PointLength, 0);
	DrawLine(0, PointLength);
}
void DrawHaulArea(void)
{
	char str[200];
	SetPenColor("Light Gray");
	StartFilledRegion(1);
	MovePen(0,0);
	DrawLine(GetWindowWidth(), 0);
	DrawLine(0, HaulArea.height);
	DrawLine(-GetWindowWidth(), 0);
	DrawLine(0, -HaulArea.height);
	EndFilledRegion();
	SetPenColor(HaulAreaColor);
	StartFilledRegion(1);
	MovePen(HaulArea.x, HaulArea.y);
	DrawLine(HaulArea.width, 0);
	DrawLine(0, HaulArea.height);
	DrawLine(-HaulArea.width, 0);
	DrawLine(0, -HaulArea.height);
	EndFilledRegion();
	SetPenColor("White");
	sprintf(str, "CurrentPosition:%.2f", HaulArea.x+0.5*HaulArea.width);
	MovePen(HaulArea.x+ 0.5 * HaulArea.width-0.5*TextStringWidth(str), HaulArea.y);
	DrawTextString(str);
	SetPenColor("Black");
}
void RemoveHaulArea(void)
{
	SetEraseMode(TRUE);
	StartFilledRegion(1);
	MovePen(HaulArea.x, HaulArea.y);
	DrawLine(HaulArea.width, 0);
	DrawLine(0, HaulArea.height);
	DrawLine(-HaulArea.width, 0);
	DrawLine(0, -HaulArea.height);
	EndFilledRegion();
	SetEraseMode(FALSE);
}
void CalHaulArea(void)
{
	HaulArea.width = (3 * pow(GetWindowWidth(), 2)) / (4 * XLength);
	k = XLength / GetWindowWidth();
	HaulArea.x = (GetWindowWidth() - 8 * DiagramOrigin.x) / (8 * k);
}