#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_IN      (GUI_ID_USER + 0x01)
#define ID_TEXT_OUT      (GUI_ID_USER + 0x02)
#define ID_EDIT_IN      (GUI_ID_USER + 0x03)
#define ID_EDIT_OUT      (GUI_ID_USER + 0x04)
#define ID_TEXT_UIN      (GUI_ID_USER + 0x05)
#define ID_TEXT_UOUT      (GUI_ID_USER + 0x06)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x07)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x08)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x09)


extern CONFIG_DATA_U __configDataU;


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const char* prStringArray[][3] ={
	{"设置/气缸时序","设置/气缸时序","Gas Set"},
	{"进气时间","进气时间","Gas-entrapping Time"},
	{"放气时间","放气时间","Gas-bleeding Time"},
	{"S","S","S"},
	{"S","S","S"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_IN, 130, 60, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_OUT, 130, 140, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_IN, 300, 60, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_OUT, 300, 140, 80, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect,  &__strBuf[3][0], ID_TEXT_UIN, 380, 60, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect,  &__strBuf[4][0], ID_TEXT_UOUT, 380, 140, 80, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[6][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[7][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};



/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  int tempInt;

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		sprintf(strBuffer,"%d",__configDataU.gasInTime);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_IN),strBuffer);

		sprintf(strBuffer,"%d",__configDataU.gasOutTime);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_OUT),strBuffer);

	  break;
  
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_IN: // Notifications sent by 'Edit0'
		  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_IN),1);
			  break;
		  }
		break;
		
		case ID_EDIT_OUT: // Notifications sent by 'Edit1'
		  switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
			KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_OUT),1);	
		  break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
			  case WM_NOTIFICATION_RELEASED:
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_IN), strBuffer, 30);
				  tempInt = atoi(strBuffer);
				  User_Set_gasInTime (tempInt);
			  
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_OUT), strBuffer, 30);
				  tempInt = atoi(strBuffer);
				  User_Set_gasOutTime(tempInt);
		 
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
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_IN), strBuffer, 30);
				  tempInt = atoi(strBuffer);
				  User_Set_gasInTime (tempInt);
			  
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_OUT), strBuffer, 30);
				  tempInt = atoi(strBuffer);
				  User_Set_gasOutTime(tempInt);
		 
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
*       GasSet
*/

static WM_HWIN GasSet(void) {
  WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

  return hWin;
}

unsigned int RunFrmUserSetGasSet(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_GASSET)].FrmHandle = GasSet();
	return 0xFF;

	
}
