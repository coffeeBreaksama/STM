#include "includes.h"
#include "app.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0        (GUI_ID_USER + 0x00)
#define ID_TEXT_SQUARE       (GUI_ID_USER + 0x01)
#define ID_TEXT_fWLOAD       (GUI_ID_USER + 0x02)
#define ID_TEXT_STDLEN       (GUI_ID_USER + 0x03)
#define ID_TEXT_G            (GUI_ID_USER + 0x04)
#define ID_TEXT_TIMEUSE      (GUI_ID_USER + 0x05)
#define ID_EDIT_SQUARE		 (GUI_ID_USER + 0x06)
#define ID_EDIT_fWLOAD       (GUI_ID_USER + 0x07)
#define ID_EDIT_STDLEN       (GUI_ID_USER + 0x08) 
#define ID_EDIT_G			 (GUI_ID_USER + 0x09)
#define ID_EDIT_TIMEUSE		 (GUI_ID_USER + 0x0A)
#define ID_TEXT_USQUARE      (GUI_ID_USER + 0x0E)
#define ID_TEXT_UfWLOAD      (GUI_ID_USER + 0x0F)
#define ID_TEXT_USTDLEN      (GUI_ID_USER + 0x10)
#define ID_TEXT_UG			 (GUI_ID_USER + 0x11)
#define ID_TEXT_UTIMEUSE     (GUI_ID_USER + 0x12)
#define ID_BUTTON_SAVE       (GUI_ID_USER + 0x14)
#define ID_BUTTON_CANCEL     (GUI_ID_USER + 0x15)
#define ID_BUTTON_NEXT       (GUI_ID_USER + 0x16)




extern CONFIG_DATA_U __configDataU;
extern SAMPLE_SAVE_INFO __sampleInfo;

static const char* prStringArray[][3] ={
	{"试样信息","试样信息","Sample Info"},
	{"面积","面积","Square"},
	{"力量宽度","力量宽度","Width Loaded"},	
	{"标距","标距","Standart Lenth"},	
	{"克重","克重","g"},
	{"时间","时间","Time"},
	{"mm^2","mm^2","mm^2"},
	{"mm","mm","mm"},
	{"N","N","N"},
	{"G","G","G"},
	{"s","s","s"},
	{"保存","保存","Save"},
	{"取消","取消","Cancel"},
	{"下一步","下一步","Next"},
	NULL
} ;


static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  
  { TEXT_CreateIndirect, &__strBuf[1][0], ID_TEXT_SQUARE, 130, 60, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[2][0], ID_TEXT_fWLOAD, 130, 120, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[3][0], ID_TEXT_STDLEN, 130, 180, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[4][0], ID_TEXT_G, 130, 240, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[5][0], ID_TEXT_TIMEUSE, 130, 300, 120, 30, GUI_TA_RIGHT | GUI_TA_VCENTER, 0x0, 0 },
 
  { EDIT_CreateIndirect, "Edit4", ID_EDIT_SQUARE, 300, 60, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit0", ID_EDIT_fWLOAD, 300, 120, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_STDLEN, 300, 180, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_G, 300, 240, 80, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit3", ID_EDIT_TIMEUSE, 300, 300, 35, 30, 0, 0x64, 0 },

  
  { TEXT_CreateIndirect, &__strBuf[6][0], ID_TEXT_USQUARE, 380, 60, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[7][0], ID_TEXT_UfWLOAD, 380, 120, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[8][0], ID_TEXT_USTDLEN, 380, 180, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect, &__strBuf[9][0], ID_TEXT_UG, 380, 240, 120, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { TEXT_CreateIndirect,&__strBuf[10][0], ID_TEXT_UTIMEUSE, 340, 300, 20, 30, GUI_TA_LEFT | GUI_TA_TOP, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[11][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[12][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[13][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
};

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  float tempFloat;
  unsigned int tempInt;
  unsigned char testType;


  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);	
		FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,5);

		testType = 	__configDataU.testMethodLaOrYa;

		sprintf(strBuffer,"%.2f",__sampleInfo.square[testType]);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SQUARE),strBuffer);

		sprintf(strBuffer,"%.2f",__sampleInfo.fWidthLoaded[testType]);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_fWLOAD),strBuffer);

		sprintf(strBuffer,"%.2f",__sampleInfo.StandartLen);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_STDLEN),strBuffer);

		sprintf(strBuffer,"%.2f",__sampleInfo.g);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_G),strBuffer);

		sprintf(strBuffer,"%d",__sampleInfo.timeWillUsed);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_TIMEUSE),strBuffer);


	   break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		case ID_EDIT_fWLOAD: // Notifications sent by 'Edit0'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_fWLOAD),3);
			break;
		  }
		break;
		
		case ID_EDIT_STDLEN: // Notifications sent by 'Edit1'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_STDLEN),3);	
			break;
		  }
		break;
		
		case ID_EDIT_G: // Notifications sent by 'Edit2'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_G),3);
			break;
		  }
		break;
		
		case ID_EDIT_TIMEUSE: // Notifications sent by 'Edit3'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_TIMEUSE),1);
			break;
		  }
		break;
		
		case ID_EDIT_SQUARE: // Notifications sent by 'Edit4'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SQUARE),3);
			break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SQUARE), strBuffer, 30);
				tempFloat = atof(strBuffer);
				SAMPLE_Set_square(tempFloat);

				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_fWLOAD), strBuffer, 30);
				tempFloat = atof(strBuffer);
				SAMPLE_Set_fWidthLoaded(tempFloat);

				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_STDLEN), strBuffer, 30);
				tempFloat = atof(strBuffer);
				SAMPLE_Set_StandartLen(tempFloat);

				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_G), strBuffer, 30);
				tempFloat = atof(strBuffer);
				SAMPLE_Set_g(tempFloat);

				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_TIMEUSE), strBuffer, 30);
				tempInt = atoi(strBuffer);
				SAMPLE_Set_timeWillUsed(tempInt);
				
				UI_CloseWindows(pMsg->hWin);

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
				//TODO 试样信息的下一步
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
*       SampleInfo
*/

static WM_HWIN SampleInfo(void)
{
  WM_HWIN hWin;
  int i;
  for(i=0;i<GUI_COUNTOF(prStringArray) - 1;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

	return hWin;
}

unsigned int RunFrmSampleInfo(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_SAMPLEINFO)].FrmHandle = SampleInfo();
	return 0xFF;
}
