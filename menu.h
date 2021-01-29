#ifndef MENU_H_
#define MENU_H_

//#include "file.h"
#include "imgui.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>

#define REFRESH_WINDOW 1
#define buttonwidth 0.5
#define buttonheight 0.2
#define boxwidth 3
#define boxheight 2.8

extern showHelp;
extern showAbout;
extern isNew;
extern showButton;
extern isHistogram;
extern isPieChart;
extern isLineChart;
extern bool isBranch;
extern bool isQuest_1;
extern bool isQuest_2;
extern bool showButton_1;
extern bool showButton_2;
extern bool isConfirm;
extern bool isDeath;
extern bool isRecovered;
extern bool isHubei;
extern bool isOutsideHubei;
extern bool isStateButton;
extern bool isEdit;
extern bool isUpdate;
extern bool isDelete;
extern bool isSuccess;
extern bool isWarning;
extern bool isAdd;
extern bool isForcast;

void DrawMenu();
void DrawAbout();
void DrawHelp();
void Display();
void DrawBranch();
void DrawQuest_1();
void DrawQuest_2();
void DrawButton_1();
void DrawButton_2();
void DrawStateButton();
void FreeHead();
void RefreshAll();
void DrawEdit();
void DrawSuccess();
void DrawForcast();
#endif