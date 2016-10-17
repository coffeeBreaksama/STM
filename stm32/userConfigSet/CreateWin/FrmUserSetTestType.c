#include  "includes.h"
#include  "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0      (GUI_ID_USER + 0x01)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x04)
#define ID_BUTTON_UP      (GUI_ID_USER + 0x07)
#define ID_BUTTON_DOWN      (GUI_ID_USER + 0x08)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x09)

extern CONFIG_DATA_U __configDataU;
extern CONFIG_DATA_S __configDataS;


static const char* prStringArray[][3] ={
	{"设置/试验模式","设置/试验模式","Auto Return"},
	{"","",""},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"上","上","UP"},
	{"下","下","DOWN"},
	{"下一步","下一步","NEXT"},
	NULL
} ;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, &__strBuf[1][0], ID_LISTBOX_0, 80, 50, 500, 300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[2][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[4][0], ID_BUTTON_UP, 650, 120, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_DOWN, 650, 260, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[6][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};
static GUI_ConstString _testTypeDis0_0[] = {
	"剥离",  
	"拉力",
	"压力", 
	"堆码",
	"撕裂",
	"纸品抗张",
	 NULL
};
static GUI_ConstString _testTypeDis0_1[] = {
	"剥离",  
	"拉力",
	"压力", 
	"堆码",
	"撕裂",
	"纸品抗张",
	 NULL
};

static GUI_ConstString _testTypeDis0_2[] = {
	"Peel",  
	"Tensile",
	"Compression", 
	"Load Keep",
	"Tearing",
	"Paper Pull",
	 NULL
};
static GUI_ConstString _testTypeDis1_0[] = {
	"抗压",
	"平压",	
	"边压",
	"粘合",
	"环压",
	NULL
};
static GUI_ConstString _testTypeDis1_1[] = {
	"抗压",
	"平压",	
	"边压",
	"粘合",
	"环压",
	NULL
};

static GUI_ConstString _testTypeDis1_2[] = {
	"Compress",	
	"Flat Crush",  
	"Edge Crush",
	"Pin adhesion",
	"Ring Crush",
	 NULL
};
static GUI_ConstString _testTypeDis2_0[] = {
		"耐破度",
		"原纸耐破度",
		 NULL
	};
static GUI_ConstString _testTypeDis2_1[] = {
		"耐破度",
		"原纸耐破度",
		 NULL
	};
static GUI_ConstString _testTypeDis2_2[] = {
		"Bursting",  
		"Paper Bursting",  
		 NULL
	};
static GUI_ConstString _testTypeDis3_0[] = {
		"抗压最大力",
		"堆码",
		 NULL
	};
static GUI_ConstString _testTypeDis3_1[] = {
		"抗压最大力",
		"堆码",
		 NULL
	};
static GUI_ConstString _testTypeDis3_2[] = {
		"Max Compress",
		"Keeping Compress",  
		NULL
	};



static void _setListTextOfTestType(WM_HWIN hList){
	
	switch(__configDataS.controlerType){
		case 0:UI_SetListBoxTextByLgvg(hList,_testTypeDis0_0,_testTypeDis0_1,_testTypeDis0_2);break;
		case 1:UI_SetListBoxTextByLgvg(hList,_testTypeDis1_0,_testTypeDis1_1,_testTypeDis1_2);break;
		case 2:UI_SetListBoxTextByLgvg(hList,_testTypeDis2_0,_testTypeDis2_1,_testTypeDis2_2);break;
		case 3:UI_SetListBoxTextByLgvg(hList,_testTypeDis3_0,_testTypeDis3_1,_testTypeDis3_2);break;
		default: break;
	}
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
 static char strBuffer[20],strBuffer2[20];
 unsigned char listSel = 0;

  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetTitleHeight(hItem,32);
		FRAMEWIN_SetTextColor(hItem, 0x00FFFFFF);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
		LISTBOX_SetItemSpacing(hItem,50);
		LISTBOX_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTBOX_SetAutoScrollV(hItem,1);
		LISTBOX_SetScrollbarWidth(hItem,50);

		_setListTextOfTestType(hItem);
		LISTBOX_SetSel(hItem,__configDataU.testMethodLaOrYa);
	  break;
  
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTBOX_0: // Notifications sent by 'Listbox'
      switch(NCode) {
        case WM_NOTIFICATION_SEL_CHANGED:
		  listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
		  LISTBOX_GetItemText(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0),listSel,strBuffer2,20);
        break;
      }
    break;
    
	case ID_BUTTON_SAVE: // Notifications sent by 'Save'
      switch(NCode) {
		case WM_NOTIFICATION_RELEASED:
			listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
			User_Set_testMethodLaOrYa(listSel);
			UI_RtUserMenuSaveSuc(pMsg);
        break;
      }
    break;
    
	case ID_BUTTON_CANCEL: // Notifications sent by 'Cancel'
      switch(NCode) {
		case WM_NOTIFICATION_RELEASED:
			UI_CloseWindows(pMsg->hWin);
			RunFrmUserSetIconView();
		break;
      }
    break;
    
	case ID_BUTTON_UP: // Notifications sent by 'Up'
      switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
		  UI_MoveUpListBoxSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0),1);
        break;
      }
    break;
    
	case ID_BUTTON_DOWN: // Notifications sent by 'Down'
	  switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
		  UI_MoveDownListBoxSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0),1);
        break;
		}
	break;

	case ID_BUTTON_NEXT: // Notifications sent by 'Down'
	  switch(NCode) {
		case WM_NOTIFICATION_CLICKED:
			listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
			User_Set_testMethodLaOrYa(listSel);			
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
*       Create SettingTestType
*/
static WM_HWIN TestTypeSet(void) {

  WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) 
		strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}




 
unsigned int RunFrmUserSetTestType(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_TESTTYPE)].FrmHandle = TestTypeSet();
	return 0xFF;

	
}



