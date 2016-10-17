#include "userConf.h"
#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_DESCRIPTION       (GUI_ID_USER + 0x01)
#define ID_TEXT_DESCRIPTION2      (GUI_ID_USER + 0x02)
#define ID_BUTTON_SURE      (GUI_ID_USER + 0x3)

extern CONFIG_DATA_U __configDataU;


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/



static const char* prStringArray[][3] ={
	{"警告","警告","Warning"},
	{"输入值非法1！","输入值非法1！","Illegality Number1!"},
	{"请检查","请检查","Check and make sure"},
	{"确定","确定","OK"},


	{"警告","警告","Warning"},
	{"未知的错误！","未知的错误！","Unknow Error!"},
	{"请重启","请重启","Please restart"},
	{"确定","确定","OK"},

	{"警告","警告","Warning"},
	{"密码错误！","密码错误！","Error Password"},
	{"请检查","请检查","Check and make sure"},
	{"确定","确定","OK"},
	NULL
} ;
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  300, 200, 200, 160, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_DESCRIPTION, 0, 0, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_DESCRIPTION2, 0, 40, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[3][0], ID_BUTTON_SURE, 60, 90, 80, 20, 0, 0x0, 0 },
};


/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_FRAMEWIN_0);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetClientColor(hItem,GUI_BLACK);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SURE);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DESCRIPTION);
		TEXT_SetTextColor(hItem,GUI_RED);
	  break;
	  
	  case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		if(NCode==WM_NOTIFICATION_RELEASED)
		{
		  switch(Id)
		  {
			case ID_BUTTON_SURE: // Notifications sent by 'CLOSE'
			  WM_DeleteWindow(pMsg->hWin);
			  break;
		  }
		}    
		break;
	  
	  case WM_PAINT:
		  GUI_SetColor(GUI_RED);
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
static WM_HWIN ERR_creatWindow(void) {
    WM_HWIN hWin;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	WM_MakeModal(hWin);
	WM_SetStayOnTop(hWin, 1);
  return hWin;
}

unsigned int ERR_ThrowError(unsigned char ErrorId)
{	
	int i;
		for(i = 0; i < 4; i++){
			strcpy(&__strBuf[i][0],prStringArray[ErrorId*4 + i][__configDataU.languageSel]);
		}
		ERR_creatWindow();
	return 0xFF;
}
