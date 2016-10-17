#include "userConf.h"
#include "includes.h"
#include "app.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_ZEROP       (GUI_ID_USER + 0x01)
#define ID_TEXT_NUM			(GUI_ID_USER + 0x03)
#define ID_TEXT_NUM2		(GUI_ID_USER + 0x04)
#define ID_EDIT_AMP		 (GUI_ID_USER + 0x05)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x07)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x08)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x09)
#define ID_BUTTON_DECLINE	(GUI_ID_USER + 0x0A)

#define WM_UPDATA    (WM_USER + 0)

extern CONFIG_DATA_S __configDataS;
extern CONFIG_DATA_U __configDataU;
extern SENSOR_CONFIG __sensorConfig;
extern unsigned int __curFrmIconIndex; 

static unsigned char _ampIndex;

static const char* prStringArray[][3] ={
	{"设置/增益系数","设置/增益系数","AmplifierCoe"},
	{"增益系数","增益系数","AmplifierCoe"},
	{"333.3","333.3","333.3"},	
	{"444.4","444.4","444.4"},	
	{"下降","下降","DOWN"},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },  
  { TEXT_CreateIndirect,&__strBuf[1][0], ID_TEXT_ZEROP, 80, 60, 150, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,&__strBuf[2][0], ID_TEXT_NUM, 130, 180, 240, 60, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_NUM2, 130, 250, 240, 60, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect, " ", ID_EDIT_AMP, 300, 60, 80, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, &__strBuf[4][0], ID_BUTTON_DECLINE, 400, 160, 120, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[6][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[7][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
};


static void changeTextNum(WM_MESSAGE *pMsg, int Id, float num)
{
	WM_HWIN  hItem;
	char _strBuffer[30];
	static char unitBuffer[5];
	if(num > 1000)
	{
		num = 0;
	}

	hItem = WM_GetDialogItem(pMsg ->hWin,Id);
	sprintf(_strBuffer,"%s %s",num,unitBuffer);
	TEXT_SetText(hItem,_strBuffer);
}

static float GetNum()
{
	return 123.11;
}


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  unsigned int tempInt;
  WM_MESSAGE Msg;
  Msg.MsgId = WM_UPDATA;

  switch (pMsg->MsgId) {
   case WM_UPDATA:
    hItem = pMsg->hWin;
	changeTextNum(pMsg, ID_TEXT_NUM, GetNum());
   break;
  
   case WM_INIT_DIALOG:
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 32);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);	
	sprintf(strBuffer,"%s %d",&__strBuf[0][0],__curFrmIconIndex - 3);
	FRAMEWIN_SetText(hItem,strBuffer);	

	sprintf(strBuffer,"%d",__sensorConfig.softAmplify[_ampIndex]);
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_AMP),strBuffer);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_NUM);
	TEXT_SetTextColor(hItem,GUI_GREEN);
	TEXT_SetFont(hItem, GUI_FONT_32B_1);
	TEXT_SetBkColor(hItem,GUI_BLACK);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_NUM2);
	TEXT_SetTextColor(hItem,GUI_GREEN);
	TEXT_SetFont(hItem, GUI_FONT_32B_1);
	TEXT_SetBkColor(hItem,GUI_BLACK);
    break;

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_AMP: // Notifications sent by 'Edit1'
      switch(NCode) {
        case WM_NOTIFICATION_CLICKED:
			KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_AMP),1);	
        break;
      }
    break;
	
	case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
      switch(NCode) {
		case WM_NOTIFICATION_RELEASED: 
		  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_AMP), strBuffer, 30);
		  tempInt = atoi(strBuffer);
		  Sensor_Set_softAmplify(tempInt,0);

		  UI_RtLoadMenuSaveSuc(pMsg);
        break;
      }
    break;

    case ID_BUTTON_CANCEL: // Notifications sent by 'CANCEL'
      switch(NCode) {
		case WM_NOTIFICATION_RELEASED:
			UI_CloseWindows(pMsg->hWin);
			RunFrmSysCalLoadIconView();
        break;
      }
    break;
    
	case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
      switch(NCode) {
	    case WM_NOTIFICATION_RELEASED:
		  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_AMP), strBuffer, 30);
		  tempInt = atoi(strBuffer);
		  Sensor_Set_softAmplify(tempInt,_ampIndex);

		  UI_RunLoadNextSaveSuc(pMsg);
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
*       AmplifierCoe1
*/

static WM_HWIN AmplifierCoe1(void) {
	WM_HWIN hWin;
 	int i;
	_ampIndex = __curFrmIconIndex - 4;
	if(_ampIndex > 3) _ampIndex = 0;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
	return hWin;

}

unsigned int RunFrmSysLoadCalAmplifierCoe1(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_AMP1)].FrmHandle = AmplifierCoe1();
	return 0xFF;
}
