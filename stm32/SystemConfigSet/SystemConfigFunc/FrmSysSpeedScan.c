#include "DIALOG.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "includes.h"
#include "app.h"


#define ID_FRAMEWIN_0      (GUI_ID_USER + 0x00)
#define ID_TEXT_SPEED      (GUI_ID_USER + 0x01)
#define ID_EDIT_SPEED      (GUI_ID_USER + 0x02)
#define ID_BUTTON_SAVE      (GUI_ID_USER + 0x03)
#define ID_BUTTON_CANCEL      (GUI_ID_USER + 0x04)
#define ID_BUTTON_NEXT      (GUI_ID_USER + 0x05)


extern CONFIG_DATA_S __configDataS;
extern CONFIG_DATA_U __configDataU;
extern EM_CONFIG __emConfig;
extern unsigned char __SpeedCelSelIndex;
extern float swpArray[20];//TODO Unknow Define

static const char* prStringArray[][3] ={
	{"设置/输入速度系数","设置/输入速度系数","Input Speed Pre"},
	{"当前选择：","当前选择:","Now Choose:"},
	{"","",""},
	{"保存","保存","SAVE"},
	{"取消","取消","CANCEL"},
	{"下一步","下一步","NEXT"},
	NULL,
} ;

static GUI_ConstString _apListBox[] = {
	"500",  
	"400",
	"300", 
	"200",
	"150",
	"100",
	"50",
	"20",
	"10",
	"5",
	"2",
	"1",
	NULL
};
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, &__strBuf[0][0], ID_FRAMEWIN_0,  0, 0, 800, 480, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { TEXT_CreateIndirect,	 &__strBuf[1][0], ID_TEXT_SPEED, 170, 60, 140, 30, GUI_TA_HCENTER | GUI_TA_VCENTER, 0x0, 0 },
  { EDIT_CreateIndirect,	    NULL        , ID_EDIT_SPEED, 300, 60, 80, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, &__strBuf[3][0], ID_BUTTON_SAVE, 0, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[4][0], ID_BUTTON_CANCEL, 266, 368, 266, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, &__strBuf[5][0], ID_BUTTON_NEXT, 532, 368, 266, 80, 0, 0x0, 0 },
  
};


static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char strBuffer[30];
  unsigned int tempInt, temp;


  switch (pMsg->MsgId) {
	  case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 32);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	
		
		if(__configDataS.motorType == 0||__configDataS.motorType == 3){
			sprintf(strBuffer,"%s %s",&__strBuf[1][0],_apListBox[__SpeedCelSelIndex]);
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_SPEED),strBuffer);

			sprintf(strBuffer,"%d",__emConfig.speedCoe[__SpeedCelSelIndex]);
			EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED),strBuffer);
		}
		else {
			temp = floor(50.0/(swpArray[12-__SpeedCelSelIndex])*(__emConfig.speedCoe2[1]+1) - 1+0.5);
			//因为swpArray是随便定义的，所以计算出来的temp会有错误
			if(temp <=0 ) temp = 0;
			sprintf(strBuffer,"%s Temp %s",&__strBuf[1][0],_apListBox[__SpeedCelSelIndex]);
			TEXT_SetText(WM_GetDialogItem(pMsg->hWin, ID_TEXT_SPEED),strBuffer);

			sprintf(strBuffer,"%d",temp);
			EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED),strBuffer);
		}
		break;
	  
	  case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
		case ID_EDIT_SPEED: // Notifications sent by 'Edit2'
		  switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
				KeyPad_Interface(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED),1);
			break;
		  }
		break;
		
		case ID_BUTTON_SAVE: // Notifications sent by 'SAVE'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				if(__configDataS.motorType == 0||__configDataS.motorType == 3){
					  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
					  tempInt = atoi(strBuffer);
					  Encoder_Set_speedCoe(tempInt,__SpeedCelSelIndex);
				}
				else {
					  unsigned int temp;
					  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
					  temp = atoi(strBuffer);
					  tempInt = floor((swpArray[12-__SpeedCelSelIndex])/50.0*(temp+1) - 1+0.5);
					  //因为swpArray定义为空，不知道初始化为什么值，所以计算出来的tempInt会有错误
					  Encoder_Set_speedCoe2(tempInt,1);
		 		}			  
				UI_RtSysMenuSaveSuc(pMsg);
			break;
		  }
		break;
		
		case ID_BUTTON_CANCEL: // Notifications sent by 'CANCEL'
		  switch(NCode) {
			case WM_NOTIFICATION_RELEASED:
				UI_CloseWindows(pMsg->hWin);
				RunNextFrom(FORMID_SYSTEMSET);
			break;
		  }
		  break;
		
		case ID_BUTTON_NEXT: // Notifications sent by 'NextStep'
		  switch(NCode) {
		  case WM_NOTIFICATION_RELEASED:
			if(__configDataS.motorType == 0||__configDataS.motorType == 3){
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
				  tempInt = atoi(strBuffer);
				  Encoder_Set_speedCoe(tempInt,__SpeedCelSelIndex);
			}
			else {
				  unsigned int temp;
				  EDIT_GetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_SPEED), strBuffer, 30);
				  temp = atoi(strBuffer);
				  tempInt = floor((swpArray[12-__SpeedCelSelIndex])/50.0*(temp+1) - 1+0.5);;
				  Encoder_Set_speedCoe2(tempInt,1);
		 	}	  
			UI_RunSysNextSaveSuc(pMsg);
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
*       SpeedScanf
*/

static WM_HWIN SpeedScanf(void) {
	WM_HWIN hWin;
 	int i;
	for(i=0;i < GUI_COUNTOF(prStringArray) - 1;i++)strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);	
  return hWin;
}

unsigned int RunFrmSysSpeedScanf(void)
{

	__WindowsInfo[UI_GetWindowInfoIndexId(RORMID_SYSSPEEDSCANF)].FrmHandle = SpeedScanf();
	return 0xFF;

	
}
