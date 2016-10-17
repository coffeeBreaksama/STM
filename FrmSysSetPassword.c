#include "DIALOG.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "includes.h"
#include "app.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0			(GUI_ID_USER + 0x00)
#define ID_TEXT_WARNING			(GUI_ID_USER + 0x01)
#define ID_TEXT_PASSWORD		(GUI_ID_USER + 0x02)
#define ID_MULTIEDIT_PASSWORD   (GUI_ID_USER + 0x03)
#define ID_BUTTON_SURE			(GUI_ID_USER + 0x04)
#define ID_BUTTON_CANCEL		(GUI_ID_USER + 0x05)
#define ID_BUTTON_NEXT			(GUI_ID_USER + 0x06)


extern CONFIG_DATA_U __configDataU;
unsigned char __allowSysSet = 0;
static const char* prStringArray[][3] ={
	{"警告","警告","WARNING"},
	{"非专业人士，谨慎使用此功能!","非专业人士，谨慎使用此功能!","Non-Professional,use those Functions carefully "},
	{"密码","密码","Password"},
	{"确定","确定","Password"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL,
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,	 &__strBuf[1][0], ID_TEXT_WARNING, 20, 100, 500, 60, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,	 &__strBuf[2][0], ID_TEXT_PASSWORD, 170, 200, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { MULTIEDIT_CreateIndirect,	    NULL        , ID_MULTIEDIT_PASSWORD, 300, 200, 80, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_SURE, 0, 368, 266, 80, 0, 0x0, 0 },
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
  char strBuffer[10];
  unsigned int psdInt;
  
  switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_PASSWORD);
		MULTIEDIT_SetPasswordMode(hItem,1);
	break;
	  
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
			case ID_MULTIEDIT_PASSWORD: // Notifications sent by 'Edit2'
				switch(NCode) {
					case WM_NOTIFICATION_CLICKED:
						KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_PASSWORD),4);
					break;
				}
			break;
		
			case ID_BUTTON_SURE: // Notifications sent by 'SAVE'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						MULTIEDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_PASSWORD), strBuffer, 30);
						psdInt = atoi(strBuffer);
						if(psdInt == 1199){
							UI_CloseWindows(pMsg->hWin);
							__allowSysSet = 1;
							RunNextFrom(FORMID_SYSTEMSET);
						}
						else ERR_ThrowError(2);
					break;
				}
			break;
		
			case ID_BUTTON_CANCEL: // Notifications sent by 'CANCEL'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						UI_CloseWindows(pMsg->hWin);
					break;
				}
			break;
		
			case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						MULTIEDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_PASSWORD), strBuffer, 30);
						psdInt = atoi(strBuffer);
						if(psdInt == 1199){
							UI_CloseWindows(pMsg->hWin);
							RunNextFrom(FORMID_SYSTEMSET);
							__allowSysSet = 1;
							//UI_RtSysMenuSaveSuc(pMsg);
						}
						else ERR_ThrowError(2);
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

static WM_HWIN SysPassword(void) 
{
	WM_HWIN hWin;
 	int i;
	for(i=0;i < GUI_COUNTOF(prStringArray) - 1;i++)	strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
	return hWin;
}

unsigned int RunFrmSysPassword(void)
{
	if(__allowSysSet == 0)
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_SYSPASSWORD)].FrmHandle = SysPassword();
	else RunNextFrom(FORMID_SYSTEMSET);
	return 0xFF;
}
