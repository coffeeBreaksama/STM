#include "DIALOG.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "includes.h"
#include "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_Test      (GUI_ID_USER + 0x01)
#define ID_TEXT_Slow      (GUI_ID_USER + 0x02)
#define ID_TEXT_Fast      (GUI_ID_USER + 0x03)
#define ID_EDIT_Test      (GUI_ID_USER + 0x04)
#define ID_EDIT_Slow      (GUI_ID_USER + 0x05)
#define ID_EDIT_Fast      (GUI_ID_USER + 0x06)
#define ID_TEXT_UTest      (GUI_ID_USER + 0x07)
#define ID_TEXT_USlow      (GUI_ID_USER + 0x08)
#define ID_TEXT_UFast      (GUI_ID_USER + 0x09)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x0A)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x0B)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x0C)

extern CONFIG_DATA_U __configDataU;

static const char* prStringArray[][3] ={
	{"设置/速度","设置/速度","Speed"},
	{"试验速度","试验速度","Test Speed"},
	{"慢速速度","慢速速度","Slow Speed"},
	{"快速速度","快速速度","Fast Speed"},
	{"mm/min","mm/min","mm/min"},
	{"mm/min","mm/min","mm/min"},
	{"mm/min","mm/min","mm/min"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_Test, 130, 60, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_Slow, 130, 140, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_Fast, 130, 220, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_Test, 300, 60, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_Slow, 300, 140, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_Fast, 300, 220, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_UTest, 385, 60, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[5][0], ID_TEXT_USlow, 385, 140, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[6][0], ID_TEXT_UFast, 385, 220, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[7][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[8][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[9][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  float tempFloat;

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	
		sprintf(strBuffer,"%.2f",__configDataU.fTestSpeed);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Test),strBuffer);

		sprintf(strBuffer,"%.2f",__configDataU.fSlowSpeed);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Slow),strBuffer);

		sprintf(strBuffer,"%.2f",__configDataU.fFastSpeed);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Fast),strBuffer);
	  break;
	  
	  case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
		case ID_EDIT_Test: // Notifications sent by 'Edit0'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Test),3);
			break;
		  }
		break;
		
		case ID_EDIT_Slow: // Notifications sent by 'Edit1'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Slow),3);	
			break;
		  }
		break;
		
		case ID_EDIT_Fast: // Notifications sent by 'Edit2'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Fast),3);
			break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Test), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fTestSpeed (tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Slow), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fSlowSpeed(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Fast), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fFastSpeed(tempFloat);

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
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Test), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fTestSpeed (tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Slow), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fSlowSpeed(tempFloat);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_Fast), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fFastSpeed(tempFloat);

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
*       SpeedSetting
*/

static WM_HWIN SpeedSetting(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}

unsigned int RunFrmUserSetSpeed(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_SPEEDSET)].FrmHandle = SpeedSetting();
	return 0xFF;

	
}
