#include"histogram.h"
#include"diagram.h"
#include"PieChart.h"
#include"LineChart.h"
#include "file.h"
#include "imgui.h"
#include "menu.h"

bool showHelp = FALSE;
bool showAbout = FALSE;
bool isNew = FALSE;
bool showButton = FALSE;
bool isHistogram = FALSE;
bool isPieChart = FALSE;
bool isLineChart = FALSE;
bool isBranch = FALSE;
bool isQuest_1 = FALSE;
bool isQuest_2 = FALSE;
bool showButton_1 = FALSE;
bool showButton_2 = FALSE;
bool isHubei = TRUE;
bool isConfirm = FALSE;
bool isDeath = FALSE;
bool isRecovered = FALSE;
bool isStateButton = FALSE;
bool isWarning = FALSE;
bool isEdit = FALSE;
bool isUpdate = FALSE;
bool isDelete = FALSE;
bool isSuccess = FALSE;
bool isAdd = FALSE;
bool isForcast = FALSE;
int state = CONFIRM;
static double mx, my;
extern struct position DiagramOrigin;
extern double XLength;
extern struct area HaulArea;
extern double k;
extern struct area GraphicArea;
extern char HaulAreaColor[20];


void MouseEventProcess(int x, int y, int button, int event)
{
	static bool isButtonDown = FALSE;
	struct PieChart* p;
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	uiGetMouse(x, y, button, event);
	static double ix;
	switch (event)
	{
	case MOUSEMOVE:
	{
		if (isinArea(mx, my) == 2)
		{
			strcpy(HaulAreaColor, "Gray");
			if (isButtonDown)
			{
				RemoveDiagram();
				RemoveHaulArea();
				if (mx - ix >= 0 && HaulArea.x + HaulArea.width >= GetWindowWidth())
				{
					;
				}
				else if (mx - ix <= 0 && HaulArea.x <= 0)
				{
					;
				}
				else
				{
					HaulArea.x += (mx - ix);
					DiagramOrigin.x -= k * (mx - ix);
				}
				if (isHistogram == TRUE)
					RefreshHistogram();
				else if (isLineChart == TRUE)
					RefreshLineChart();
				DrawHaulArea();
				ix = mx;
			}
		}
		else
		{
			strcpy(HaulAreaColor, "Dark Gray");
		}
	}
	break;
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)
		{
			if (isinArea(mx, my) == 1)
			{
				XLength *= 1.5;
				RemoveDiagram();
				RemoveHaulArea();
				CalHaulArea();
				if (isHistogram == TRUE)
					RefreshHistogram();
				else if (isLineChart == TRUE)
					RefreshLineChart();
				DrawHaulArea();
			}
		}
		else if (button == RIGHT_BUTTON)
		{
			if (isinArea(mx, my) == 1)
			{
				XLength /= 1.5;
				RemoveDiagram();
				RemoveHaulArea();
				CalHaulArea();
				if (isHistogram == TRUE)
					RefreshHistogram();
				else if (isLineChart == TRUE)
					RefreshLineChart();
				DrawHaulArea();
			}
		}
		isButtonDown = TRUE;
		if (isinArea(mx, my) == 2)
			ix = mx;
		break;
	case BUTTON_UP:
		isButtonDown = FALSE;
		break;
	}
	Display();
}

void showHistogram()
{
	struct discription* dp;
	extern struct histogram* HistogramHead;
	RemoveDiagram();
	if (HistogramHead == NULL)
	{
		DrawHistogram();
		DrawHaulArea();
	}
	else
	{
		DrawHaulArea();
	}
	dp = FindRec(mx, my);
	if (dp == NULL)
	{
		RefreshHistogram();
	}
	else
	{
		RefreshHistogram();
		PutRec(dp);
	}
}

void showLineChart()
{
	char colorname[20];
	extern struct LineChart* LineChartHead;
	struct discription* dp;
	RemoveDiagram();
	if (LineChartHead == NULL)
	{
		DrawLineChart();
		DrawHaulArea();
	}
	else
	{
		DrawHaulArea();
	}
	strcpy(colorname, FindLine(mx, my));
	if (strcmp("WHITE", colorname) == 0)
	{
		RefreshLineChart();
	}
	else
	{
		dp = FindLinePoint(mx, my);
		if (dp != NULL)
			strcpy(colorname, dp->ColorName);
		PutLine(colorname, dp);
	}

}

void showPieChart()
{
	struct PieChart* p;
	extern struct PieChart* PieChartHead;
	RemoveDiagram();
	if (PieChartHead == NULL)
	{
		DrawPieChart();
	}
	p = FindPie(mx, my);
	if (p == NULL)
	{
		RefreshPieChart();
	}
	else
	{
		RefreshPieChart();
		PutPie(p);
	}
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	Display();
}

void CharEventProcess(char ch)
{
	uiGetChar(ch);
	Display();
}

void TimerEventProcess(int timerid)
{
	if (timerid == REFRESH_WINDOW)
		Display();
}

void Display()
{
	DisplayClear();
	DrawMenu();
	if (showHelp) DrawHelp();
	if (showAbout) DrawAbout();
	if (isHistogram)   showHistogram();
	if (isLineChart)   showLineChart();
	if (isPieChart)    showPieChart();
	if (isBranch)      DrawBranch();
	if (isQuest_1)     DrawQuest_1();
	if (isQuest_2)	   DrawQuest_2();
	if (showButton_1)  DrawButton_1();
	if (showButton_2)  DrawButton_2();
	if (isStateButton) DrawStateButton();
	if (isEdit)        DrawEdit();
	if (isSuccess  && !isForcast)	   DrawSuccess();
	if (isForcast)	   DrawForcast();
}

void Main()
{
	InitGraphics();
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	startTimer(1, 50);
}
