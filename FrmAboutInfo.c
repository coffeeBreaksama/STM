#include  "includes.h"
#include  "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_MULTIEDIT_0      (GUI_ID_USER + 0x01)
#define ID_BUTTON_SURE      (GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x04)
#define ID_BUTTON_UP      (GUI_ID_USER + 0x07)

extern CONFIG_DATA_S __configDataS;
extern CONFIG_DATA_U __configDataU;
extern SENSOR_CONFIG __sensorConfig;
extern DT __systemDt;
extern MID_TIME __midTime;

char  aboutStrBuffer[4000];
int _trailIndex = 0;
extern char fmtBuf1[100],fmtBuf2[100],fmtBuf3[100];

static const char* prStringArray[][3] ={
	{"关于","关于","About"},
	{"","",""},
	{"打印","打印","PRINT"},
	{"退出","退出","Exit"},
	{"更改","更改","CHANGE"},
	NULL
} ;

/*********************************************************************
*
*       _aDialogCreate
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect, &__strBuf[1][0], ID_MULTIEDIT_0, 30, 50, 650, 300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[2][0], ID_BUTTON_SURE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[4][0], ID_BUTTON_UP, 700, 120, 80, 50, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void AddStrToBuffer(char* str){
	int len = strlen(str);
	if(len >= 0 && (_trailIndex+len) < 3998) {
		memcpy(aboutStrBuffer +_trailIndex,str,len);
		_trailIndex += len;
		*(aboutStrBuffer + _trailIndex) = '\0';
	}
}

static int MIN(int a, int b){
	if(a > b)return b;
	else return a;

}

static void SetAboutText(void){
	aboutStrBuffer[0]= '\0';
	_trailIndex = 0;
	if(__configDataU.languageSel<=1){
		AddStrToBuffer("      关于\n");
		__systemDt.year = MIN(__systemDt.year,2099); __systemDt.month = MIN(__systemDt.month,12);__systemDt.day = MIN(__systemDt.day,31);
		__systemDt.hour = MIN(__systemDt.hour,24); __systemDt.minute = MIN(__systemDt.minute,59);__systemDt.second = MIN(__systemDt.second,59);
		sprintf(fmtBuf1,"序列号:%u  类型:%u\n",__CardSnDes,__CardTypeDes);
		AddStrToBuffer(fmtBuf1);
		sprintf(fmtBuf1,"使用次数:%d/%d\n",__midTime.hourUsed,__midTime.hourAllow);
		AddStrToBuffer(fmtBuf1);
		
		sprintf(fmtBuf1,"版本号:%d.%d.%d\n",VESION_HIGH,VESION_MID,VESION_LOW);
		AddStrToBuffer(fmtBuf1);

		sprintf(fmtBuf1,"控制器类型:530  \n");
		AddStrToBuffer(fmtBuf1);

		sprintf(fmtBuf1,"日期:%4d年%2d月%2d日",__systemDt.year,__systemDt.month,__systemDt.day);			
		AddStrToBuffer(fmtBuf1);
	}
	else {
		AddStrToBuffer("       About Info\n");
		
		sprintf(fmtBuf1,"SN:%u  Type:%u\n",__CardSnDes,__CardTypeDes);
		AddStrToBuffer(fmtBuf1);
		sprintf(fmtBuf1,"Used time %d/%d\n",__midTime.hourUsed,__midTime.hourAllow);
		AddStrToBuffer(fmtBuf1);
		
		sprintf(fmtBuf1,"VISION:%d.%d.%d\n",VESION_HIGH,VESION_MID,VESION_LOW);
		AddStrToBuffer(fmtBuf1);

		sprintf(fmtBuf1,"ControlerType:310 and 330  \n");
		AddStrToBuffer(fmtBuf1);

		sprintf(fmtBuf1,"Date:%4dYear%2dMonth%2dDay",__systemDt.year,__systemDt.month,__systemDt.day);			
		AddStrToBuffer(fmtBuf1);

	}
}

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
        //
        // Initialization of 'Setting Test Module'
        //
        hItem = pMsg->hWin;
        FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetTitleHeight(hItem,32);
        FRAMEWIN_SetTextColor(hItem, 0x00FFFFFF);
        //
        // Initialization of 'Listbox'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
		MULTIEDIT_SetAutoScrollV(hItem,1);
		if(__configDataU.languageSel<=1)MULTIEDIT_SetFont(hItem,&GUI_Font20HZK);
		else MULTIEDIT_SetFont(hItem,GUI_FONT_24_ASCII);
		SetAboutText();
		MULTIEDIT_SetText(hItem,aboutStrBuffer);

    case WM_NOTIFY_PARENT:
        Id      = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
			case ID_MULTIEDIT_0: // Notifications sent by 'Listbox'
				switch(NCode) {
					case WM_NOTIFICATION_SEL_CHANGED:
					break;
				}
			break;
			
			case ID_BUTTON_SURE: // Notifications sent by 'Save'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						UI_CloseWindows(pMsg->hWin);
						//TODO  关于信息窗口下的打印/确定/保存按钮动作
					break;
				}
			break;
			
			case ID_BUTTON_CANCEL: // Notifications sent by 'Cancel'
				switch(NCode) {
					case WM_NOTIFICATION_RELEASED:
						UI_CloseWindows(pMsg->hWin);
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

static WM_HWIN About(void) {

	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
	return hWin;
}

unsigned int RunFrmAboutInfo(void)
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_ABOUT)].FrmHandle = About();
	return 0xFF;
}


/*************************** End of file ****************************/
