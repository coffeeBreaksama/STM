#include "includes.h"
#include  "app.h"

#define ID_FRAMEWIN_TESTMAIN		(GUI_ID_USER + 0x00)
#define ID_LISTVIEW_SAMPLEINFO      (GUI_ID_USER + 0x01)
#define ID_LISTVIEW_RESULT			(GUI_ID_USER + 0x02)
#define ID_TEXT_LOAD				(GUI_ID_USER + 0x03)
#define ID_TEXT_ELONG				(GUI_ID_USER + 0x04)
#define ID_TEXT_DISP				(GUI_ID_USER + 0x05)
#define ID_TEXT_LOADNUM				(GUI_ID_USER + 0x06)
#define ID_TEXT_ELONGNUM			(GUI_ID_USER + 0x07)
#define ID_TEXT_DISPNUM				(GUI_ID_USER + 0x08)
#define ID_TEXT_LOADUNIT			(GUI_ID_USER + 0x09)
#define ID_TEXT_ELONGUNIT			(GUI_ID_USER + 0x0A)
#define ID_TEXT_DISPUNIT			(GUI_ID_USER + 0x0B)
#define ID_TEXT_STATE				(GUI_ID_USER + 0x0C)
#define ID_TEXT_SAMPLEINFO			(GUI_ID_USER + 0x0D)
#define ID_TEXT_RESULT				(GUI_ID_USER + 0x0E)
#define ID_GRAPH_0					(GUI_ID_USER + 0x0F)
#define ID_BUTTON_CLEARZ			(GUI_ID_USER + 0x10)
#define ID_BUTTON_DELETE			(GUI_ID_USER + 0x11)
#define ID_BUTTON_PRINT				(GUI_ID_USER + 0x12)

GRAPH_SCALE_Handle _hScaleV,_hScaleH;
extern CONFIG_DATA_U __configDataU ;
extern CONFIG_DATA_S __configDataS;
extern SENSOR_CONFIG __sensorConfig;

static const char * _aTable_1[][3] = {
  { "1", "100-A", "Item AAA" },
  { "2", "100-B", "Item BBB" },
  { "3", "100-C", "Item CCC" },
  { "4", "100-D", "Item DDD" },
  { "5", "100-E", "Item EEE" },
  { "6", "100-F", "Item FFF" },
  { "7", "100-G", "Item GGG" },
  { "8", "100-H", "Item HHH" }
};

static const char* _loadUnit[] = {"N","gf","Lbf","kgf","KN",NULL};
static const char* _elongUnit[] = {"mm","cm","in",NULL};
static const char* _stressUnit[] = {"N/m","N/cm","N/mm","Lbf/in","kgf/cm",NULL};

static const char* prStringArray[][3] ={
	{"试验主界面","试验主界面","Main Test"},
	{"试样信息","试样信息","Sample Information"},
	{"结果","结果","Result"},	
	{"力量","力量","Load"},	
	{"力量单位","力量单位","LoadUnit"},
	{"位移","位移","Elong"},
	{"位移单位","位移单位","ElongUnit"},
	{"变形","变形","Disp"},
	{"变形单位","变形单位","DispUnit"},
	{"178.99","178.99","178.99"},
	{"66.66","66.66","66.66"},
	{"230.25","230.25","230.25"},
	{"测试状态","测试状态","Testing State"},
	{"清零","清零","Clear Zero"},
	{"删除","删除","Delete"},
	{"打印","打印","Print"},
	NULL
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_TESTMAIN,             0,0, 800, 480, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
	{ LISTVIEW_CreateIndirect, NULL, ID_LISTVIEW_SAMPLEINFO,                              569, 152, 214, 200, 0, 0x0, 0 },
	{ LISTVIEW_CreateIndirect, NULL, ID_LISTVIEW_RESULT,                              569, 44, 214, 90, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_SAMPLEINFO,                            575, 28, 198, 20, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_RESULT,                                        575, 135, 198, 20, 0, 0x0, 0 },
  
	{ TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_LOAD,                                          5, 5, 90, 50, GUI_TA_LEFT | GUI_TA_VCENTER, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[4][0],ID_TEXT_LOADUNIT,                                       95, 5, 90, 50, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
	
	{ TEXT_CreateIndirect, &__strBuf[5][0],ID_TEXT_ELONG,                                          190, 5, 90, 50, GUI_TA_LEFT | GUI_TA_VCENTER, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[6][0],ID_TEXT_ELONGUNIT,                                      280, 5, 90, 50, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  
	{ TEXT_CreateIndirect, &__strBuf[7][0],ID_TEXT_DISP,                                           375, 5, 90, 50, GUI_TA_LEFT | GUI_TA_VCENTER, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[8][0],ID_TEXT_DISPUNIT,                                       465, 5, 90, 50, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
 
	{ TEXT_CreateIndirect, &__strBuf[9][0],ID_TEXT_LOADNUM,                                          5, 55, 180, 50, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[10][0],ID_TEXT_ELONGNUM,                                      		190, 55, 180, 50, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
	{ TEXT_CreateIndirect, &__strBuf[11][0],ID_TEXT_DISPNUM,                                       	375, 55, 180, 50, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
	
	{	TEXT_CreateIndirect, &__strBuf[12][0],ID_TEXT_STATE,                                  576, 0, 199, 29, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
   

	{ BUTTON_CreateIndirect, &__strBuf[13][0],ID_BUTTON_CLEARZ,                                 569, 359, 70, 70, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, &__strBuf[14][0],ID_BUTTON_DELETE,                                     641, 359, 70, 70, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, &__strBuf[15][0],ID_BUTTON_PRINT,                                      713, 358, 70, 70, 0, 0x0, 0 },
	{ GRAPH_CreateIndirect, NULL,ID_GRAPH_0,                                        5, 120, 555, 320, 0, 0x0, 0 },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
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
	sprintf(_strBuffer,"%.2f %s",num,unitBuffer);
	TEXT_SetText(hItem,_strBuffer);
}


/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) 
{
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int i = 0;
  static char unitBuffer[5];

  switch (pMsg->MsgId) {
	case WM_DELETE:
		WM_DeleteWindow(hkeypad);
	break;
  
	case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetTitleHeight(hItem,32);
		FRAMEWIN_SetTextColor(hItem, 0x00FFFFFF);
		FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,5);

		//
		// Initialization of 'Graph'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_SetBorder(hItem, 50, 0, 0, 20);
		_hScaleV = GRAPH_SCALE_Create( 20, GUI_TA_LEFT, GRAPH_SCALE_CF_VERTICAL, 25);
		GRAPH_SCALE_SetOff(_hScaleV, 0);
		GRAPH_SCALE_SetFactor(_hScaleV, 0.04f);
		GRAPH_SCALE_SetTextColor(_hScaleV, GUI_RED);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_AttachScale(hItem, _hScaleV);
		GRAPH_SetBorder(hItem, 50, 0, 0, 20);

		_hScaleH = GRAPH_SCALE_Create( 270, GUI_TA_HCENTER,GRAPH_SCALE_CF_HORIZONTAL, 25);
		GRAPH_SCALE_SetOff(_hScaleH, 0);
		GRAPH_SCALE_SetFactor(_hScaleH, 0.4f);
		GRAPH_SCALE_SetTextColor(_hScaleH, GUI_RED);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_AttachScale(hItem, _hScaleH);
		GRAPH_SetBorder(hItem, 50, 0, 0, 20);

		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetColor(hItem,GUI_WHITE,GRAPH_CI_BK);

		//
		// Initialization of 'Listview'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_SAMPLEINFO);
		LISTVIEW_SetAutoScrollV(hItem,1);
		LISTVIEW_AddColumn(hItem, 53, "NO", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 53, "Load", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 53, "Elong", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_AddColumn(hItem, 53, "Disp", GUI_TA_HCENTER | GUI_TA_VCENTER);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_RESULT);
		LISTVIEW_AddColumn(hItem, 71, "NO", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 71, "Load", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 71, "Disp", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_SetGridVis(hItem, 1);

		for(i = ID_TEXT_LOAD;i <= ID_TEXT_DISP;i++){
			hItem = WM_GetDialogItem(pMsg->hWin, i);
			TEXT_SetTextColor(hItem,GUI_GREEN);
			TEXT_SetFont(hItem, &GUI_Font20HZK);
			TEXT_SetBkColor(hItem,GUI_BLACK);
		}
		//
		// Initialization of 'Unit'
		//
		TEXT_SetText(WM_GetDialogItem(pMsg->hWin,ID_TEXT_LOADUNIT),_loadUnit[__configDataU.loadUion]);
		TEXT_SetText(WM_GetDialogItem(pMsg->hWin,ID_TEXT_ELONGUNIT),_elongUnit[__configDataU.elongUion]);
		TEXT_SetText(WM_GetDialogItem(pMsg->hWin,ID_TEXT_DISPUNIT),_stressUnit[__configDataU.stressUion]);	
		for(i = ID_TEXT_LOADUNIT;i <= ID_TEXT_DISPUNIT; i++){
		hItem = WM_GetDialogItem(pMsg->hWin, i);
		TEXT_SetTextColor(hItem,GUI_GREEN);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		TEXT_SetBkColor(hItem,GUI_BLACK);
		}
   		//
		// Initialization of 'Num'
		//
		for(i = ID_TEXT_LOADNUM; i<= ID_TEXT_DISPNUM;i++){
			hItem = WM_GetDialogItem(pMsg->hWin, i);
			TEXT_SetTextColor(hItem,GUI_RED);
			TEXT_SetFont(hItem, GUI_FONT_D32);
			TEXT_SetBkColor(hItem,GUI_BLACK);
		}


		for(i = ID_TEXT_STATE; i<= ID_TEXT_STATE;i++){
			hItem = WM_GetDialogItem(pMsg->hWin, i);
			TEXT_SetTextColor(hItem,GUI_RED);
			TEXT_SetBkColor(hItem,GUI_BLACK);
		}
	break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_BUTTON_CLEARZ: // Notifications sent by 'Clear Zero'
		  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				  LISTVIEW_AddRow(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_SAMPLEINFO), _aTable_1[i]);
				  i++;
				  if(i > 7)i = 0;
				  for(Id = ID_TEXT_LOADNUM;Id < ID_TEXT_LOADUNIT;Id ++) {
					  changeTextNum(pMsg,Id,888.88);
				  }
				break;
			  }
		break;
		
		case ID_BUTTON_DELETE: // Notifications sent by 'Delete'
		  switch(NCode) {
			  case WM_NOTIFICATION_RELEASED:
				  LISTVIEW_DeleteRow(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_SAMPLEINFO),0);
				 //TODO 删除按钮
			  break;
		  }
		break;
		
		case ID_BUTTON_PRINT: // Notifications sent by 'Print'
		  switch(NCode) {
			  case WM_NOTIFICATION_RELEASED:
					//TODO 打印按钮
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

static WM_HWIN CreateMainTestInterface(void) {
  WM_HWIN hWin;
   	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

unsigned int  RunFrmMainTest(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_MAINTEST)].FrmHandle = CreateMainTestInterface();
	return 0xFF;//next form ID
	
}

/*************************** End of file ****************************/
