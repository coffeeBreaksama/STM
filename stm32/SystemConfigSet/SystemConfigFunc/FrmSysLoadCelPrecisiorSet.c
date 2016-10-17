#include  "includes.h"
#include  "app.h"

#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0      (GUI_ID_USER + 0x01)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x04)
#define ID_BUTTON_UP      (GUI_ID_USER + 0x07)
#define ID_BUTTON_DOWN      (GUI_ID_USER + 0x08)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x09)
#define ID_TEXT_PRE    (GUI_ID_USER + 0x0A)
#define ID_EDIT_PRE    (GUI_ID_USER + 0x0B)

extern CONFIG_DATA_S __configDataS;
extern CONFIG_DATA_U __configDataU;
extern SENSOR_CONFIG __sensorConfig;
extern EM_CONFIG __emConfig;

static const char* prStringArray[][3] ={
	{"设置/精度设置","设置/精度设置","Prec Set"},
	{"","",""},
	{"滤波系数","滤波系数","Filter Col"},
	{"","",""},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"上","上","UP"},
	{"下","下","DOWN"},
	{"下一步","下一步","NEXT"},
	NULL
} ;
static GUI_ConstString _apListBox0[] = {
	"5000",  
	"10000",
	"20000",
	"50000",
	"100000",
	"200000",
	 NULL
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect,  &__strBuf[0][0], ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect,  &__strBuf[1][0], ID_LISTBOX_0, 80, 50, 500, 250, 0, 0x0, 0 },
  { TEXT_CreateIndirect,  &__strBuf[2][0], ID_TEXT_PRE, 80, 330, 160, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect,  &__strBuf[3][0], ID_EDIT_PRE, 250, 330, 160, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[4][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[5][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[6][0], ID_BUTTON_UP, 650, 120, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[7][0], ID_BUTTON_DOWN, 650, 260, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,  &__strBuf[8][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  static char strBuffer[20],strBuffer2[20];
  static char listSel = 0;
  unsigned int tempInt;



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

	UI_SetListBoxTextByLgvg(hItem,_apListBox0,_apListBox0,_apListBox0);
	LISTBOX_SetSel(hItem,__configDataS.scaleIndex);

	sprintf(strBuffer,"%d",__configDataS.filterCol);
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PRE),strBuffer);

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
      case ID_EDIT_PRE: // Notifications sent by 'Edit3'
		switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				 KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PRE),1);
			break;
      }
      break;
	
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
		  Sys_Set_scaleIndex(listSel);
		  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PRE), strBuffer, 30);
		  tempInt = atoi(strBuffer);
		  Sys_Set_filterCol(tempInt); 
		  UI_RtLoadMenuSaveSuc(pMsg);
        break;
      }
    break;
    
	case ID_BUTTON_CANCEL: // Notifications sent by 'Cancel'
      switch(NCode) {
		case WM_NOTIFICATION_RELEASED:
			UI_CloseWindows(pMsg->hWin);
			RunFrmSysCalLoadIconView();
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

	case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
				Encoder_Set_encodeCoe(listSel,1);
				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_PRE), strBuffer, 30);
				tempInt = atoi(strBuffer);
				Sys_Set_filterCol(tempInt);
			
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
*
*/
static WM_HWIN PreSetConfig(void) {

	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}
 
unsigned int RunFrmSysLoadPrecisiorSet(void)
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_PRECISIORSET)].FrmHandle = PreSetConfig();
	return 0xFF;
	
}
