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
extern void UpdataDesktopLanguage(void);


static const char* prStringArray[][3] ={
	{"设置/语言选择","设置/语言选择","Language"},
	{"","",""},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"上","上","UP"},
	{"下","下","DOWN"},
	{"下一步","下一步","NEXT"},
	{"简体中文","简体中文","简体中文"},
	{"繁体中文","繁体中文","繁体中文"},
	{"English","English","English"},
	NULL
} ;

static GUI_ConstString _apListBox0[] = {
	"简体中文",  
	"繁体中文",
	"English", 
	 NULL
};
static GUI_ConstString _apListBox1[] = {
	"简体中文",  
	"繁体中文",
	"English", 
	 NULL
};

static GUI_ConstString _apListBox2[] = {
	"简体中文",  
	"繁体中文",
	"English", 
	 NULL
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { LISTBOX_CreateIndirect, &__strBuf[1][0], ID_LISTBOX_0, 80, 50, 500, 300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[2][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,&__strBuf[4][0], ID_BUTTON_UP, 650, 120, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_DOWN, 650, 260, 80, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[6][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};

static void _changeLanguage()
{
	switch(__configDataU.languageSel){
		case 1:
			TEXT_SetDefaultFont(&GUI_Font20HZKF);
			FRAMEWIN_SetDefaultFont(&GUI_Font20HZKF);
			EDIT_SetDefaultFont(&GUI_Font20HZKF);
			LISTBOX_SetDefaultFont(&GUI_Font20HZKF);
			BUTTON_SetDefaultFont(&GUI_Font20HZKF);
			CHECKBOX_SetDefaultFont(&GUI_Font20HZKF);
		break;
		
		case 2:
			TEXT_SetDefaultFont(&GUI_Font20HZKF);
			FRAMEWIN_SetDefaultFont(&GUI_Font20HZKF);
			EDIT_SetDefaultFont(&GUI_Font20HZKF);
			LISTBOX_SetDefaultFont(&GUI_Font20HZKF);
			BUTTON_SetDefaultFont(&GUI_Font20HZKF);
			CHECKBOX_SetDefaultFont(&GUI_Font20HZKF);
		break;
		
		default:
			TEXT_SetDefaultFont(&GUI_Font20HZK);
			FRAMEWIN_SetDefaultFont(&GUI_Font20HZK);
			EDIT_SetDefaultFont(&GUI_Font20HZK);
			LISTBOX_SetDefaultFont(&GUI_Font20HZK);
			BUTTON_SetDefaultFont(&GUI_Font20HZK);
			CHECKBOX_SetDefaultFont(&GUI_Font20HZK);
		break;
	}
	UpdataDesktopLanguage();

}


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
	
		LISTBOX_SetFont(hItem,&GUI_Font20HZK);
		UI_SetListBoxTextByLgvg(hItem,_apListBox0,_apListBox1,_apListBox2);
		LISTBOX_SetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0),__configDataU.languageSel);
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
		    case WM_NOTIFICATION_CLICKED:
				listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
				User_Set_languageSel(listSel);
				_changeLanguage();
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
		
		case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
		  switch(NCode) {
		    case WM_NOTIFICATION_RELEASED:
				listSel = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0));
				User_Set_languageSel(listSel);
				_changeLanguage();
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
*
*/
static WM_HWIN LanguageSel(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}

 
unsigned int RunFrmUserSetLanguage(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_LANGUAGE)].FrmHandle = LanguageSel();
	return 0xFF;

	
}



