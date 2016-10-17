#include "userConf.h"
#include "includes.h"
#include "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_BEGIR       (GUI_ID_USER + 0x01)
#define ID_TEXT_JUDGE      (GUI_ID_USER + 0x02)
#define ID_TEXT_LOAD      (GUI_ID_USER + 0x03)
#define ID_TEXT_DISP      (GUI_ID_USER + 0x04)
#define ID_TEXT_TIME      (GUI_ID_USER + 0x05)
#define ID_EDIT_BEGIR		 (GUI_ID_USER + 0x06)
#define ID_EDIT_JUDGE      (GUI_ID_USER + 0x07)
#define ID_EDIT_LOAD       (GUI_ID_USER + 0x08) 
#define ID_EDIT_DISP      (GUI_ID_USER + 0x09)
#define ID_EDIT_HOUR		 (GUI_ID_USER + 0x0A)
#define ID_EDIT_Minute      (GUI_ID_USER + 0x0B)
#define ID_EDIT_Second       (GUI_ID_USER + 0x0C)
#define ID_TEXT_BEGIRUNIT       (GUI_ID_USER + 0x0D)
#define ID_TEXT_UBEGIR      (GUI_ID_USER + 0x0E)
#define ID_TEXT_UJUDGE      (GUI_ID_USER + 0x0F)
#define ID_TEXT_ULOAD      (GUI_ID_USER + 0x10)
#define ID_TEXT_UDISP      (GUI_ID_USER + 0x11)
#define ID_TEXT_UMinute       (GUI_ID_USER +  0x12)
#define ID_TEXT_USecond       (GUI_ID_USER +  0x13)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x14)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x15)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x16)

extern CONFIG_DATA_U __configDataU;

static const char* prStringArray[][3] ={
	{"设置/停机方式","设置/停机方式","Break Type"},
	{"判断力量","判断力量","Break Begir"},
	{"断裂百分比","断裂百分比","Break Judge"},
	{"指定力值","指定力值","Load Stop"},
	{"位移","位移","Disp Stop"},
	{"时间","时间","Time Stop"},
	{"时","时","H"},
	{"分","分","M"},
	{"秒","秒","S"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_BEGIR, 130, 60, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_JUDGE, 130, 120, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_LOAD, 130, 180, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_DISP, 130, 240, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[5][0], ID_TEXT_TIME, 130, 300, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
 
  { EDIT_CreateIndirect, "Edit4", ID_EDIT_BEGIR, 300, 60, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_JUDGE, 300, 120, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_LOAD, 300, 180, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_DISP, 300, 240, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit3", ID_EDIT_HOUR, 300, 300, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit4", ID_EDIT_Minute, 380, 300, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit5", ID_EDIT_Second, 460, 300, 35, 30, 0, 0x64, 0 },
  
  { TEXT_CreateIndirect, "KN", ID_TEXT_BEGIRUNIT, 380, 60, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, "%", ID_TEXT_UBEGIR, 380, 120, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, "%", ID_TEXT_UJUDGE, 380, 180, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, "cm", ID_TEXT_ULOAD, 380, 240, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[6][0], ID_TEXT_UDISP, 340, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[7][0], ID_TEXT_UMinute, 420, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[8][0], ID_TEXT_USecond, 500, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[9][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[10][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[11][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
};

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  unsigned int tempInt;
  float tempFloat;
  char hour,min,sec;
  unsigned char testType;

  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);	
		////Loading and setting old data;
		testType = 	__configDataU.testMethodLaOrYa;

		sprintf(strBuffer,"%d",__configDataU.fJudgeBreakBegin[testType]);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_BEGIR),strBuffer);

		sprintf(strBuffer,"%d",__configDataU.breakJudgePrecent[testType]);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_JUDGE),strBuffer);

		sprintf(strBuffer,"%.2f",__configDataU.fLoadStop);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD),strBuffer);

		sprintf(strBuffer,"%.2f",__configDataU.fDispStop);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISP),strBuffer);

		hour = __configDataU.fTimeStop / 3600;
		min = (__configDataU.fTimeStop - hour*3600) / 60;
		sec = __configDataU.fTimeStop - hour*3600 - min*60;

		sprintf(strBuffer,"%d",hour);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR),strBuffer);

		sprintf(strBuffer,"%d",min);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute),strBuffer);
	
		sprintf(strBuffer,"%d",sec);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second),strBuffer);
    break;

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_JUDGE: // Notifications sent by 'Edit0'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_JUDGE),1);
			break;
		 }
		break;
		
		case ID_EDIT_LOAD: // Notifications sent by 'Edit1'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD),3);	
			break;
		  }
		break;
		
		case ID_EDIT_DISP: // Notifications sent by 'Edit2'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISP),3);
			break;
		  }
		break;
		
		case ID_EDIT_HOUR: // Notifications sent by 'Edit3'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR),1);
			break;
		  }
		break;
		
		case ID_EDIT_Minute: // Notifications sent by 'EditMinute'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute),1);
			break;
		  }
		break;
		
		case ID_EDIT_Second: // Notifications sent by 'EditSecond'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second),1);
			break;
		  }
		break;
		 
		case ID_EDIT_BEGIR: // Notifications sent by 'Edit4'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_BEGIR),1);
			break;
		  }
		break;
		
		 case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_BEGIR), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_fJudgeBreakBegin(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_JUDGE), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_breakJudgePrecent(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fLoadStop(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISP), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fDispStop(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR), strBuffer, 30);
			  hour = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute), strBuffer, 30);
			  min = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second), strBuffer, 30);
			  sec = atoi(strBuffer);
			  tempInt = hour*3600 + min*60 + sec;
			  User_Set_fTimeStop(tempInt);

			  UI_RtUserMenuSaveSuc(pMsg);
			break;
		  }
		break;
		
		case ID_BUTTON_CANCEL: // Notifications sent by 'CANCEL'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				UI_CloseWindows(pMsg->hWin);
				RunFrmUserSetIconView();
			break;
		  }
		break;
		
		case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_BEGIR), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_fJudgeBreakBegin(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_JUDGE), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_breakJudgePrecent(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fLoadStop(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISP), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fDispStop(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR), strBuffer, 30);
			  hour = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute), strBuffer, 30);
			  min = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second), strBuffer, 30);
			  sec = atoi(strBuffer);
			  tempInt = hour*3600 + min*60 + sec;
			  User_Set_fTimeStop(tempInt);		
			  UI_RunUserNextSaveSuc(pMsg);
			break;
		  }
		break;
	}
    break;
  default:
    WM_DefaultProc(pMsg); 
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LoadKeeping
*/

static WM_HWIN LoadKeeping(void) {
  WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

  return hWin;
}

unsigned int RunFrmUserSetTestStopType(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_BREAKTYPE)].FrmHandle = LoadKeeping();
	return 0xFF;

	
}
