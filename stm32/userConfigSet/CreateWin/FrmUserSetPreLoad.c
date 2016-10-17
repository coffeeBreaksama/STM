#include "DIALOG.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_PreLoad      (GUI_ID_USER + 0x01)
#define ID_EDIT_PreLoad      (GUI_ID_USER + 0x02)
#define ID_TEXT_UPreLoad      (GUI_ID_USER + 0x03)
#define ID_CHECKBOX_LOADCLEAR      (GUI_ID_USER + 0x04)
#define ID_CHECKBOX_DISPCLEAR      (GUI_ID_USER + 0x05)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x06)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x07)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x08)

extern CONFIG_DATA_U __configDataU;

static const char* prStringArray[][3] ={
	{"设置/预紧力","设置/预紧力","Pre Load"},
	{"预紧力量","预紧力量","Pre Load"},
	{"力量清零","力量清零","Force Clr Zero"},
	{"位移清零","位移清零","Displ Clr Zero"},
	{"KN","KN","KN"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,&__strBuf[1][0], ID_TEXT_PreLoad, 130, 60, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { CHECKBOX_CreateIndirect, &__strBuf[2][0], ID_CHECKBOX_LOADCLEAR, 300, 140, 150, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { CHECKBOX_CreateIndirect, &__strBuf[3][0], ID_CHECKBOX_DISPCLEAR, 300, 220, 150, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_PreLoad, 300, 60, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_UPreLoad, 380, 60, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[6][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[7][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  float tempFloat;
  char forceClr,dispClr;

  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		sprintf(strBuffer,"%.2f",__configDataU.fYujinli);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PreLoad),strBuffer);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_LOADCLEAR);
		CHECKBOX_SetText(hItem, &__strBuf[2][0]);
		CHECKBOX_SetState(hItem,__configDataU.yujinClrFlagLoad);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_DISPCLEAR);
		CHECKBOX_SetText(hItem,&__strBuf[3][0]);
		CHECKBOX_SetState(hItem,__configDataU.yujinClrFlagDisp);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_PreLoad: // Notifications sent by 'Edit0'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PreLoad),3);
			break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PreLoad), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fYujinli(tempFloat);

			  CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_LOADCLEAR));
			  forceClr = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_LOADCLEAR));
			  dispClr = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_DISPCLEAR)); 
			  User_Set_yujinClrFlagLoad(forceClr);
			  User_Set_yujinClrFlagDisp(dispClr);

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
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PreLoad), strBuffer, 30);
			  tempFloat = atof(strBuffer);
			  User_Set_fYujinli(tempFloat);

			  CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_LOADCLEAR));
			  forceClr = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_LOADCLEAR));
			  dispClr = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_DISPCLEAR)); 
			  User_Set_yujinClrFlagLoad(forceClr);
			  User_Set_yujinClrFlagDisp(dispClr);


		
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
*       Protect
*/

static WM_HWIN Protect(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}


unsigned int RunFrmUserSetProLoad(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_PRELOAD)].FrmHandle = Protect();
	return 0xFF;

	
}
