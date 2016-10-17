#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_DATA      (GUI_ID_USER + 0x01)
#define ID_TEXT_TIME      (GUI_ID_USER + 0x02)
#define ID_TEXT_UYEAR      (GUI_ID_USER + 0x03)
#define ID_TEXT_UMONTH      (GUI_ID_USER + 0x04)
#define ID_EDIT_YEAR      (GUI_ID_USER + 0x05)
#define ID_EDIT_MONTH      (GUI_ID_USER + 0x06)
#define ID_EDIT_DAY      (GUI_ID_USER + 0x07)
#define ID_EDIT_HOUR		 (GUI_ID_USER + 0x08)
#define ID_EDIT_MIN      (GUI_ID_USER + 0x09)
#define ID_EDIT_SEC       (GUI_ID_USER + 0x0A)
#define ID_TEXT_UDAY      (GUI_ID_USER + 0x0B)
#define ID_TEXT_UHOUR     (GUI_ID_USER + 0x0C)
#define ID_TEXT_UMinute      (GUI_ID_USER + 0x0D)
#define ID_TEXT_USecond      (GUI_ID_USER + 0x0E)
#define ID_BUTTON_UP      (GUI_ID_USER + 0x11)
#define ID_BUTTON_DOWN      (GUI_ID_USER + 0x12)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x13)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x14)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x15)

extern CONFIG_DATA_U __configDataU;
extern DT __systemDt;

static const char* prStringArray[][3] ={
	{"设置/时间设置","设置/时间设置","Data　Setting"},
	{"日期","日期","Data"},
	{"时间","时间","Time"},	
	{"年","年","Year"},
	{"月","月","Month"},
	{"日","日","Day"},
	{"时","时","Hour"},
	{"分","分","Min"},
	{"秒","秒","Sec"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect,&__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,&__strBuf[1][0], ID_TEXT_DATA, 130, 100, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_TIME, 130, 200, 80, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_YEAR, 300, 100, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_MONTH, 380, 100, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_DAY, 460, 100, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit3", ID_EDIT_HOUR, 300, 200, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit4", ID_EDIT_MIN, 380, 200, 35, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit5", ID_EDIT_SEC, 460, 200, 35, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_UYEAR, 340, 100, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_UMONTH, 420, 100, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[5][0], ID_TEXT_UDAY, 500, 100, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[6][0], ID_TEXT_UHOUR, 340, 200, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[7][0], ID_TEXT_UMinute, 420, 200, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[8][0], ID_TEXT_USecond, 500, 200, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[9][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[10][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[11][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  unsigned int year;
  char hour,min,sec,month,day;

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

		sprintf(strBuffer,"%d",__systemDt.year);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR),strBuffer);

		sprintf(strBuffer,"%d",__systemDt.month);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH),strBuffer);

		sprintf(strBuffer,"%d",__systemDt.day);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY),strBuffer);

		sprintf(strBuffer,"%d",__systemDt.hour);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR),strBuffer);

		sprintf(strBuffer,"%d",__systemDt.minute);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MIN),strBuffer);

		sprintf(strBuffer,"%d",__systemDt.second);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SEC),strBuffer);
      break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_YEAR: // Notifications sent by 'Edit0'
		  switch(NCode) {
		    case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR),1);
			break;
		  }
		break;
		
		case ID_EDIT_MONTH: // Notifications sent by 'Edit1'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH),1);	
			break;
		  }
		break;
		
		case ID_EDIT_DAY: // Notifications sent by 'Edit2'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY),1);
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
		
		case ID_EDIT_MIN: // Notifications sent by 'Edit4'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MIN),1);
			break;
		  }
		break;
		
		case ID_EDIT_SEC: // Notifications sent by 'Edit5'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SEC),1);
			break;
		  }
		  break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR), strBuffer, 30);
			  year = atoi(strBuffer);
			  SYS_Set_year(year);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH), strBuffer, 30);
			  month = atoi(strBuffer);
			  SYS_Set_month(month);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY), strBuffer, 30);
			  day = atoi(strBuffer);
			  SYS_Set_day(day);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR), strBuffer, 30);
			  hour = atoi(strBuffer);
			  SYS_Set_hour(hour);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MIN), strBuffer, 30);
			  min = atoi(strBuffer);
			  SYS_Set_minute(min);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SEC), strBuffer, 30);
			  sec = atoi(strBuffer);
			  SYS_Set_second(sec);

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
			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_YEAR), strBuffer, 30);
			  year = atoi(strBuffer);
			  SYS_Set_year(year);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MONTH), strBuffer, 30);
			  month = atoi(strBuffer);
			  SYS_Set_month(month);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_DAY), strBuffer, 30);
			  day = atoi(strBuffer);
			  SYS_Set_day(day);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_HOUR), strBuffer, 30);
			  hour = atoi(strBuffer);
			  SYS_Set_hour(hour);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_MIN), strBuffer, 30);
			  min = atoi(strBuffer);
			  SYS_Set_minute(min);

			  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SEC), strBuffer, 30);
			  sec = atoi(strBuffer);
			  SYS_Set_second(sec);			
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
*       TimeSet
*/

static WM_HWIN TimeSet(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
	
	return hWin;
}

unsigned int RunFrmUserSetTime(void)
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_TIME)].FrmHandle = TimeSet();
	
	return 0xFF;
}
