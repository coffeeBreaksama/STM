#include  "includes.h"
#include  "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_MULTIEDIT_0      (GUI_ID_USER + 0x01)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x04)
#define ID_BUTTON_CHANGE      (GUI_ID_USER + 0x05)

extern CONFIG_DATA_U __configDataU;

static const char* prStringArray[][3] ={
	{"打印结果","打印结果","PrintResult"},
	{"","",""},
	{"打印","打印","PRINT"},
	{"取消","取消","CANCEL"},
	{"更改","更改","CHANGE"},
	NULL
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect, &__strBuf[1][0], ID_MULTIEDIT_0, 30, 50, 650, 300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[2][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[4][0], ID_BUTTON_CHANGE, 532, 368, 266, 80, 0, 0x0, 0 },
};




/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
    WM_HWIN hItem;
    int       NCode;
    int     Id;
    static char strBuffer[20],strBuffer2[20];


    switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
        hItem = pMsg->hWin;
        FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetTitleHeight(hItem,32);
        FRAMEWIN_SetTextColor(hItem, 0x00FFFFFF);

        hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
		MULTIEDIT_SetAutoScrollV(hItem,1);

    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
			case ID_MULTIEDIT_0: // Notifications sent by 'MULTIEDIT'
				switch(NCode) {
					case WM_NOTIFICATION_SEL_CHANGED:
					break;
				}
			break;
			
			case ID_BUTTON_SAVE: // Notifications sent by 'Save'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						RunFrmUserSetIconView();
					break;
				}
			break;
			
			case ID_BUTTON_CANCEL: // Notifications sent by 'Cancel'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						UI_CloseWindows(pMsg->hWin);
						RunFrmSystemSetIconView();
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
*
*/

static WM_HWIN PrintResult(void) {

	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
	return hWin;
}

 
unsigned int RunFrmPrintResult(void)
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_PRINTRESULT)].FrmHandle = PrintResult();
	return 0xFF;
}


/*************************** End of file ****************************/
