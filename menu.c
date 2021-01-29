#include "menu.h"
#include "file.h"
#include "PieChart.h"
Combine* cop;
extern struct PieChart*   PieChartHead;
extern struct histogram* HistogramHead;
extern struct LineChart* LineChartHead;
extern int state;
extern bool isWarning;
extern bool isForcast;


void DrawBranch()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	static char lable_1[] = "Please Make a Choice";
	static char lable_2[] = "Histogram or LineChart";
	static char lable_3[] = "PieChart";
	SetPenColor("Brown");
	drawRectangle(0.3*x, 0.5*y, boxwidth, boxheight, 0);
	MovePen(0.3*x+0.5*(boxwidth -TextStringWidth(lable_1)), 0.5*y + 0.67*boxheight);
	DrawTextString(lable_1);
	if (button(GenUIID(0), 0.3*x+ 0.5*(boxwidth - 1.2*TextStringWidth(lable_2)), 0.5*y + 0.4*boxheight, 1.2*TextStringWidth(lable_2), buttonheight, lable_2))
	{
		isQuest_1 = TRUE;
		isBranch = FALSE;
	}
	if (button(GenUIID(0), 0.3*x + 0.5*(boxwidth - 1.2*TextStringWidth(lable_2)), 0.5*y + 0.25*boxheight, 1.2*TextStringWidth(lable_2), buttonheight, lable_3))
	{
		isQuest_2 = TRUE;
		isBranch = FALSE;
	}
}

void DrawQuest_1()
{
	static char text_1[100] = "";
	static char text_2[100] = "";
	static char text_3[10] = "";
	static char *lable_1 = "Start Date:";
	static char *lable_2 = "End Date:";
	static char *lable_3 = "Forcast Days:";
	setTextBoxColors("Brown", "Brown", "Dark Gray", "Dark Gray", 0);
	double x = GetWindowWidth()/3;
	double y = GetWindowHeight()/2;
	if (!cop)
		cop = (Combine*)malloc(sizeof(Combine));
	drawRectangle(x - 0.95*boxwidth, y, boxwidth, boxheight, 0);
	SetPenColor("Brown");
	MovePen(x- 0.9*boxwidth, y + 0.6*boxheight);
	DrawTextString(lable_1);
	textbox(GenUIID(0), x - 0.25*(2*boxwidth + buttonwidth), y + 0.6*boxheight, 1.5*buttonwidth, buttonheight, text_1, sizeof(text_1));
	MovePen(x - 0.9*boxwidth, y + 0.6*boxheight - 2*buttonheight);
	DrawTextString(lable_2);
	textbox(GenUIID(0), x - 0.25*(2*boxwidth + buttonwidth) , y + 0.6*boxheight - 2*buttonheight, 1.5*buttonwidth, buttonheight, text_2, sizeof(text_2));
	if (isForcast)
	{
		MovePen(x - 0.9*boxwidth, y + 0.6*boxheight - 4 * buttonheight);
		DrawTextString(lable_3);
		textbox(GenUIID(0), x - 0.25*(2 * boxwidth + buttonwidth), y + 0.6*boxheight - 4 * buttonheight, 1.5*buttonwidth, buttonheight, text_3, sizeof(text_3));
	}
	if (button(GenUIID(0),x - 0.5*boxwidth, y + 0.2*boxheight, buttonwidth, buttonheight, "Done"))
	{
		if (strcmp(text_1, "") && strcmp(text_2, ""))
		{
//			isQuest_1 = FALSE;
			if (isForcast == FALSE)
			{
				showButton_1 = TRUE;
				isStateButton = TRUE;
				cop = (ReadSeries(text_1, text_2));
				memset(text_1, 0, sizeof(text_1));
				memset(text_2, 0, sizeof(text_2));
			}
			else {
				showButton_1 = TRUE;
				isStateButton = TRUE;
				Forcast(text_1, text_2, text_3);
//				cop = ReadSeries(text_2, text_1);
				memset(text_1, 0, sizeof(text_1));
				memset(text_2, 0, sizeof(text_2));
			}

		}
	}
	
}

void DrawQuest_2()
{
	static char text_3[100] = "";
	static char lable_3[] = "Which day do you want to view?";
	double x = GetWindowWidth()/3;
	double y = GetWindowHeight()/2;
	setTextBoxColors("Brown", "Brown", "Dark Gray", "Dark Gray", 0);
	if (!cop)
		cop = (Combine*)malloc(sizeof(Combine));
	drawBox(x - boxwidth, y, boxwidth, boxheight, 0, lable_3, 'c', "Brown");
	MovePen(x - 0.75*boxwidth, y + boxheight * 0.7);
	DrawTextString("Format i.e: 01-26");
	textbox(GenUIID(0), x + 0.75*boxwidth - boxwidth*1.55, y + 0.3*boxheight, 0.5*boxwidth, 1.2*buttonheight, text_3, sizeof(text_3));
	if (button(GenUIID(0), x + 0.65*(1.3*boxwidth) - boxwidth*1.5, y + 0.1*boxheight, buttonwidth, buttonheight, "Done"))
	{
		if (strcmp(text_3, ""))
		{
//			isQuest_2 = FALSE;
			strcpy_s(cop->date, sizeof(cop->date), text_3);
			cop = ReadData(text_3);
			memset(text_3, 0, sizeof(text_3));
			showButton_2 = TRUE;
			isPieChart = TRUE;
			isStateButton = TRUE;
		}
	}
}

void DrawButton_1()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.5*(x - 2 * buttonwidth), 0.75*y, buttonwidth, buttonheight, "����ͼ"))
	{
		isHistogram = TRUE;
		isPieChart = FALSE;
		isLineChart = FALSE;
	}
	if (button(GenUIID(0), 0.5*(x + 2 * buttonwidth), 0.75*y, buttonwidth, buttonheight, "����ͼ"))
	{
		isLineChart = TRUE;
		isPieChart = FALSE;
		isHistogram = FALSE;
	}

}

void DrawButton_2()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.5*(x - 4 * buttonwidth), 0.75*y, 2 * buttonwidth, buttonheight, "�������������"))
	{
		isHubei = TRUE;
		if (PieChartHead != NULL)
		{
			free(PieChartHead);
			PieChartHead = NULL;
		}
	}
	if (button(GenUIID(0), 0.5*(x + 4 * buttonwidth), 0.75*y, 2 * buttonwidth, buttonheight, "��������"))
	{
		isHubei = FALSE;
		if (PieChartHead != NULL)
		{
			free(PieChartHead);
			PieChartHead = NULL;
		}
	}

}

void DrawStateButton()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.8 * x, 0.7 * y, 1.5*buttonwidth, 1.2*buttonheight, "Confirmed"))
	{
		state = CONFIRM;
		FreeHead();
	}
	if (isForcast!=TRUE&&button(GenUIID(0), 0.8*x, 0.7*y - 2*buttonheight, 1.5*buttonwidth, 1.2*buttonheight, "Deaths"))
	{
		state = DEATH;
		FreeHead();
	}
	if (button(GenUIID(0), 0.8*x, 0.7*y - 4 * buttonheight, 1.5*buttonwidth, 1.2*buttonheight, "Recovered"))
	{
		state = RECOVERED;
		FreeHead();
	}
}

void DrawEdit()
{

	double x = GetWindowWidth();
	double y = GetWindowHeight();
	static char text_1[50], text_2[50], text_3[50], text_4[50], text_5[50], text_6[50], text_7[50];
	static char *lable_1 = "Which day do you want to edit?";
	static char *lable_2 = "What do you want to do?";
	static char *lable_3 = "Update Data";
	static char *lable_4 = "Delete Data";
	static char *lable_5 = "Add Data";
	Data *tar, *upd;
	tar = (Data*)malloc(sizeof(Data));
	upd = (Data*)malloc(sizeof(Data));
	tar->next = upd;
	upd->next = NULL;
	drawRectangle(0.5*(x - 2 * boxwidth), 0.5*(y - 1.5*boxheight), 2 * boxwidth, 1.5*boxheight, 0);
	setTextBoxColors("Brown", "Black", "Dark Gray", "Dark Gray", 0);
	MovePen(0.5*(x - TextStringWidth(lable_1)), 0.5*(y + boxheight));
	DrawTextString(lable_1);
	textbox(GenUIID(0), 0.5*(x - 3 * buttonwidth), 0.5*(y + 0.7*boxheight), 3 * buttonwidth, 1.3*buttonheight, text_1, sizeof(text_1));
	MovePen(0.5*(x - TextStringWidth(lable_2)), 0.5*y - 0.45*boxheight);
	DrawTextString(lable_2);

	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 0.7*buttonheight);
	DrawTextString("Target Province:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 2.2*buttonheight);
	DrawTextString("Target Country:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 3.7 * buttonheight);
	DrawTextString("Update Time:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 5.2*buttonheight);
	DrawTextString("Confirmed Number:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 6.7* buttonheight);
	DrawTextString("Deaths Number:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 8.2*buttonheight);
	DrawTextString("Recovered Number:");

	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_2, sizeof(text_2));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 2.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_3, sizeof(text_3));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 4 * buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_4, sizeof(text_4));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 5.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_5, sizeof(text_5));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 7 * buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_6, sizeof(text_6));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 8.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_7, sizeof(text_7));


	if (button(GenUIID(0), 0.5*x - 2.5*buttonwidth-0.1, 0.5*y - 9 * buttonheight, 1.5*buttonwidth+0.2, 1.5*buttonheight, lable_3))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
		strcpy(upd->column[UPDATE_TIME], text_4);
		if (text_5)
			upd->figure[CONFIRM] = atoi(text_5);
		if (text_6)
			upd->figure[DEATH] = atoi(text_6);
		if (text_7)
			upd->figure[RECOVERED] = atoi(text_7);
				UpdateData(text_1, tar);
		isUpdate = TRUE;
		isEdit = FALSE;
	}

	if (button(GenUIID(0), 0.5*x - 0.75*buttonwidth, 0.5*y - 9 * buttonheight, 1.5*buttonwidth, 1.5*buttonheight, lable_5))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
		strcpy(tar->column[UPDATE_TIME], text_4);
		if (text_5)
			tar->figure[CONFIRM] = atoi(text_5);
		if (text_6)
			tar->figure[DEATH] = atoi(text_6);
		if (text_7)
			tar->figure[RECOVERED] = atoi(text_7);
		AddData(text_1, tar);
		isAdd = TRUE;
		isEdit = FALSE;
	}	
	if (button(GenUIID(0), 0.5*x + buttonwidth-0.1, 0.5*y - 9 * buttonheight, 1.5*buttonwidth+0.2, 1.5*buttonheight, lable_4))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
				DeleteData(text_1, tar);
		isDelete = TRUE;
		isEdit = FALSE;
	}

}

void DrawForcast()
{
	DrawQuest_1();
}

void DrawSuccess()
{
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	static char *lable_1 = "Update Data Successfully!";
	static char *lable_2 = "Delete Data Successfully!";
	static char *lable_3 = "Add Data Successfully!";
	if(isUpdate)
		drawBox(x, y, boxwidth, boxheight, 0, lable_1, 'C', "Dark Gray");
	else if(isDelete)
		drawBox(x, y, boxwidth, boxheight, 0, lable_2, 'C', "Dark Gray");
	else if (isAdd)
		drawBox(x, y, boxwidth, boxheight, 0, lable_3, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "Got it"))
	{
		isSuccess = FALSE;
		isUpdate = isDelete = isAdd = FALSE;
	}
}

void FreeHead()
{
	struct PieChart *p1;
	struct histogram *p2;
	struct LineChart *p3
	while(PieChartHead != NULL)
	{
		p1 = PieChartHead;
		PieChartHead = PieChartHead->NextItem;
		free(p1);
		p1 = NULL;
	}
	while(HistogramHead != NULL)
	{
		p2 = HistogramHead;
		HistogramHead = HistogramHead->NextItem;
		free(p2);
		p2 = NULL;
	}
	while(LineChartHead != NULL)
	{
		p3 = LineChartHead;
		LineChartHead = LineChartHead->NextItem;
		free(p3);
		p3 = NULL;
	}
}

void DrawWarning()
{
	char lable[] = "File Not Found! Please Retry";
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	drawBox(x, y, boxwidth, boxheight, 0, lable, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "Got it"))
		isWarning = FALSE;
}

void DrawHelp()
{
	char lable[500] = "/0";
	double x = 0.1;
	double y = 0.1;
	drawBox(x, y, GetWindowWidth()-0.2, GetWindowHeight()-0.5, 0, lable, 'C', "Dark Gray");
	if(button(GenUIID(0), x+0.1, y+0.1, buttonwidth, buttonheight, "Got it"))
		showHelp = FALSE;
	SetPenColor("Black");
	MovePen(0.2, GetWindowHeight() - 0.6);
	strcpy(lable, "File        ѡ��Ҫ���еĲ�����");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - GetFontHeight()*1.5);
	strcpy(lable, "1.NewFile����ݼ�Ctrl+N��        �����µ�ͼ��");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 2 * GetFontHeight() * 1.5);
	strcpy(lable, "ѡ��Histogram or LineChart��������ͼ������ͼ����Start date���뿪ʼ����,��End date");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 3 * GetFontHeight() * 1.5);
	strcpy(lable, "�����ֹ���ڣ�����Done����ѡ��   ����ͼ   ����   ����ͼ   �ֱ��������ͼ������ͼ��");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 4 * GetFontHeight() * 1.5);
	strcpy(lable, "ѡ��Confirmed�ɲ鿴ȷ��������ѡ��Deaths�ɲ鿴����������ѡ��Recovered��ѡ�񿵸�");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 5 * GetFontHeight() * 1.5);
	strcpy(lable, "������");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 6 * GetFontHeight() * 1.5);
	strcpy(lable, "ѡ��PieChart���ֱ�״ͼ��������鿴�����ڣ�����Done,��ѡ��鿴�������ߺ�������");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 7 * GetFontHeight() * 1.5);
	strcpy(lable, "�ı�״ͼ��ѡ��Confirmed�ɲ鿴ȷ��������ѡ��Deaths�ɲ鿴����������ѡ��Recovered");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 8 * GetFontHeight() * 1.5);
	strcpy(lable, "��ѡ�񿵸�������");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 9 * GetFontHeight() * 1.5);
	strcpy(lable, "2.Edit����ݼ�Ctrl+E��        �༭����Which day do you want to edit ��������༭�����ڣ���");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 10 * GetFontHeight() * 1.5);
	strcpy(lable, "Target Province�Ҳ�ѡ��ʡ�ݣ���Target country�Ҳ�ѡ����ң���Update time�Ҳ�����¼");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 11 * GetFontHeight() * 1.5);
	strcpy(lable, "�����ݵ�����ʱ�䣬��Confirmed Number�Ҳ�ѡ��ȷ����������Deaths Numberѡ������");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 12 * GetFontHeight() * 1.5);
	strcpy(lable, "��������Recovered Number�Ҳ�ѡ������������ѡ��Update Data �������ݣ�ѡ��Add Data");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 13 * GetFontHeight() * 1.5);
	strcpy(lable, "������ݣ�ѡ��Delete Dataɾ�����ݡ�");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 14 * GetFontHeight() * 1.5);
	strcpy(lable, "3.Forecast(��ݼ�Ctrl+F)        �����ݽ���Ԥ�⣬��Start date���뿪ʼ����,��End date�����");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 15 * GetFontHeight() * 1.5);
	strcpy(lable, "ֹ���ڣ���Forcast days������Ԥ�������������Done����ѡ��   ����ͼ   ����   ����ͼ   ");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 16 * GetFontHeight() * 1.5);
	strcpy(lable, "�ֱ��������ͼ������ͼ��ѡ��Confirmed�ɲ鿴ȷ��������ѡ��Recovered�ɲ鿴������");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 17 * GetFontHeight() * 1.5);
	strcpy(lable, "����");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 18 * GetFontHeight() * 1.5);
	strcpy(lable, "4.Close����ݼ�Ctrl+C��        �رյ�ǰ���еĴ��ڡ�");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 19 * GetFontHeight() * 1.5);
	strcpy(lable, "5.Exit        �رձ�����");
	DrawTextString(lable);
}

void DrawAbout()
{
	char about[] = "Pandemic 1.0";
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	drawBox(x, y, boxwidth, boxheight, 0, about, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "Got it"))
		showAbout = FALSE;
}

void DrawMenu()
{
	static char *main_menu[] =
	{
		"File",
		"NewFile  | Ctrl-N",
		"Edit     | Ctrl-E",
		"Forcast  | Ctrl-F",
		"Close    | Ctrl-C",
		"Exit",
	};

	static char *help[] =
	{
		"Help",
		"Read Help | Ctrl-H",
		"About"
	};

	double x, y, w, h, wlist, n;
	h = GetFontHeight() * 1.5;
	w = 0.5;
	x = 0;
	y = GetWindowHeight();
	wlist = TextStringWidth(main_menu[0]) * 4;
	w = TextStringWidth(main_menu[0]) * 1.5;
	n = 4;
	int choice;
	setMenuColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	setTextBoxColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	setButtonColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	choice = menuList(GenUIID(0), x, y-h, w, wlist*1.5, h, main_menu, sizeof(main_menu)/sizeof(main_menu[0]));
	switch (choice)
	{
	case 1:
		RefreshAll();
		isBranch = TRUE;
		break;
	case 2:
		RefreshAll();
		isEdit = TRUE;
		break;
	case 3:
		RefreshAll();
		isForcast = TRUE;
		break;
	case 4:
		RefreshAll();
		break;
	case 5:
		exit(-1);
		break;
	}

	choice = menuList(GenUIID(0), x + w, y-h, w*1.2, wlist*1.5, h, help, sizeof(help) / sizeof(help[0]));
	switch (choice)
	{ 
	case 1:
		showHelp = TRUE;
		break;
	case 2:
		showAbout = TRUE;
		break;
	}
}

void RefreshAll()
{
	showButton_1 = FALSE;
	showButton_2 = FALSE;
	isHistogram = FALSE;
	isPieChart = FALSE;
	isLineChart = FALSE;
	isStateButton = FALSE;
	isBranch = FALSE;
	isQuest_1 = FALSE;
	isQuest_2 = FALSE;
	isEdit = FALSE;
	isUpdate = FALSE;
	isDelete = FALSE;
	isSuccess = FALSE;
	isForcast = FALSE;
	free(cop);
	cop = NULL;
	DisplayClear();
}