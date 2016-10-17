
#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_LOAD      (GUI_ID_USER + 0x01)
#define ID_TEXT_SPEED      (GUI_ID_USER + 0x02)
#define ID_TEXT_PREC      (GUI_ID_USER + 0x03)
#define ID_TEXT_TIME      (GUI_ID_USER + 0x04)
#define ID_EDIT_LOAD      (GUI_ID_USER + 0x05)
#define ID_EDIT_SPEED      (GUI_ID_USER + 0x06)
#define ID_EDIT_PREC      (GUI_ID_USER + 0x07)
#define ID_EDIT_Hour		 (GUI_ID_USER + 0x08)
#define ID_EDIT_Minute      (GUI_ID_USER + 0x09)
#define ID_EDIT_Second       (GUI_ID_USER + 0x0A)
#define ID_TEXT_ULoad      (GUI_ID_USER + 0x0B)
#define ID_TEXT_USpeed      (GUI_ID_USER + 0x0C)
#define ID_TEXT_UPrec      (GUI_ID_USER + 0x0D)
#define ID_TEXT_UHour      (GUI_ID_USER + 0x0E)
#define ID_TEXT_UMinute       (GUI_ID_USER +  0x0F)
#define ID_TEXT_USecond       (GUI_ID_USER +  0x10)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x11)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x12)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x13)


extern CONFIG_DATA_U __configDataU;

static const char* prStringArray[][3] ={
	{"设置/力量保持","设置/力量保持","LoadKeep"},
	{"保持力量","保持力量","Load Keep"},
	{"保持系数","保持系数","Speed Keep"},
	{"保持精度","保持精度","Prec Keep"},
	{"时间","时间","Time Stop"},
	{"时","时","H"},
	{"分","分","M"},
	{"秒","秒","S"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_LOAD, 130, 60, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_SPEED, 130, 140, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_PREC, 130, 220, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_TIME, 130, 300, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_LOAD, 300, 60, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_SPEED, 300, 140, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_PREC, 300, 220, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit3", ID_EDIT_Hour, 300, 300, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit4", ID_EDIT_Minute, 380, 300, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit5", ID_EDIT_Second, 460, 300, 35, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "KN", ID_TEXT_ULoad, 380, 60, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, "%", ID_TEXT_USpeed, 380, 140, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, "%", ID_TEXT_UPrec, 380, 220, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect,&__strBuf[5][0], ID_TEXT_UHour, 340, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[6][0], ID_TEXT_UMinute, 420, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[7][0], ID_TEXT_USecond, 500, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[8][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[9][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[10][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  float tempFloat;
  int tempInt;
  char hour,min,sec;

  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		sprintf(strBuffer,"%.2f",__configDataU.fLoadKeeping);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD),strBuffer);

		sprintf(strBuffer,"%d",__configDataU.chiSuPrecent);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED),strBuffer);

		sprintf(strBuffer,"%d",__configDataU.loadKeepPrec);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PREC),strBuffer);

		hour = __configDataU.fTimeLoadKeep / 3600;
		min = (__configDataU.fTimeLoadKeep - hour*3600) / 60;
		sec = __configDataU.fTimeLoadKeep - hour*3600 - min*60;

		sprintf(strBuffer,"%d",hour);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Hour),strBuffer);

		sprintf(strBuffer,"%d",min);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute),strBuffer);
	
		sprintf(strBuffer,"%d",sec);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second),strBuffer);
    break;

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_LOAD: // Notifications sent by 'Edit0'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD),3);
			break;
		  }
		break;
		
		case ID_EDIT_SPEED: // Notifications sent by 'Edit1'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED),1);	
			break;
		  }
		  break;
		
		case ID_EDIT_PREC: // Notifications sent by 'Edit2'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PREC),1);
			break;
		  }
		break;
		
		case ID_EDIT_Hour: // Notifications sent by 'Edit3'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Hour),1);
			break;
		  }
		break;
		
		case ID_EDIT_Minute: // Notifications sent by 'Edit3'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute),1);
			break;
		  }
		break;
		
		case ID_EDIT_Second: // Notifications sent by 'Edit3'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second),1);
			break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fLoadKeeping (tempFloat);
			  
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_chiSuPrecent(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PREC), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_loadKeepPrec(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Hour), strBuffer, 30);
			  hour = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute), strBuffer, 30);
			  min = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second), strBuffer, 30);
			  sec = atoi(strBuffer);
			  tempInt = hour*3600 + min*60 + sec;
			  User_Set_fTimeLoadKeep(tempInt);
		 
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
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_LOAD), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fLoadKeeping (tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_chiSuPrecent(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PREC), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  User_Set_loadKeepPrec(tempInt);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Hour), strBuffer, 30);
			  hour = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Minute), strBuffer, 30);
			  min = atoi(strBuffer);
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Second), strBuffer, 30);
			  sec = atoi(strBuffer);
			  tempInt = hour*3600 + min*60 + sec;
			  User_Set_fTimeLoadKeep(tempInt);
		 

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

unsigned int RunFrmUserSetLoadKeep(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_LOADKEEP)].FrmHandle = LoadKeeping();
	return 0xFF;

	
}
