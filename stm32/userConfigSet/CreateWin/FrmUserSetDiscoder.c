
#include "DIALOG.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "includes.h"
#include "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_PASSWORD      (GUI_ID_USER + 0x01)
#define ID_TEXT_MACNUM      (GUI_ID_USER + 0x02)
#define ID_EDIT_DISCODER      (GUI_ID_USER + 0x03)
#define ID_BUTTON_DISCODE      (GUI_ID_USER + 0x04)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x05)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x06)


extern CONFIG_DATA_S __configDataS;
extern CONFIG_DATA_U __configDataU;
extern EM_CONFIG __emConfig;


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const char* prStringArray[][3] ={
	{"设置/Discoder","设置/Discoder","Discoder"},
	{"密码","密码:","Password:"},
	{"机器号","机器号","Machine Number"},
	{"解码","解码","Discoder"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL,
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,	 &__strBuf[1][0], ID_TEXT_PASSWORD, 170, 100, 140, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,	 &__strBuf[2][0], ID_TEXT_MACNUM, 170, 60, 140, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect,	    NULL        , ID_EDIT_DISCODER, 300, 100, 120, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_DISCODE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[4][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
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
  unsigned int tempInt;

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	
		//TODO  discoder 初始化
	  break;
	  
case WM_NOTIFY_PARENT:
	Id    = WM_GetId(pMsg->hWinSrc);
	NCode = pMsg->Data.v;
	switch(Id) {
	    case ID_EDIT_DISCODER: // Notifications sent by 'Edit2'
		 switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
			  KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISCODER),1);
			break;
		  }
	    break;
		
		case ID_BUTTON_DISCODE: // Notifications sent by 'SAVE'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			   EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISCODER), strBuffer, 30);
			   tempInt = atoi(strBuffer);
			   //TODO  解码按钮按下后的动作，tempInt为获取到的输入
			   UI_RtSysMenuSaveSuc(pMsg);
			break;
		  }
		break;
		
		case ID_BUTTON_CANCEL: // Notifications sent by 'CANCEL'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				UI_CloseWindows(pMsg->hWin);
				RunNextFrom(FORMID_USERSET);
			break;
		  }
		break;
		
		case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DISCODER), strBuffer, 30);
			  tempInt = atoi(strBuffer);
			  //Encoder_Set_speedCoe(tempInt,__SpeedCelSelIndex);
			  //UI_RunSysNextSaveSuc(pMsg);
			  //TODO  解码界面点击下一步后的动作,tempInt为获取到的输入
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
*       SpeedScanf
*/

static WM_HWIN Discoder(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i < GUI_COUNTOF(prStringArray) - 1;i++)strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}

unsigned int RunFrmSysDiscoder(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_DISCODE)].FrmHandle = Discoder();
	return 0xFF;

	
}
