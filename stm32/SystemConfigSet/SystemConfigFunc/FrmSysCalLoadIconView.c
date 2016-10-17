
#include "includes.h"
#include "app.h"

// USER END

#define ICONVIEW_Width      70  /* �ؼ�ICONVIEW�Ŀ�                         */  
#define ICONVIEW_Height     70  /* �ؼ�ICONVIEW�ĸߣ�����ͼ���Y������    */  
#define ICONVIEW_XSpace     30  /* �ؼ�ICONVIEW��X������                  */ 
#define ICONVIEW_YSpace     40  /* �ؼ�ICONVIEW��Y������                  */ 
#define ICONVIEW_XPos       10  /* �ؼ�ICONVIEW��X�����������              */
#define BOTWIN_YSpace       60  /* ��Ļ�·����ִ���Y������                */
#define SetIconview_yPos         40  /* �м䴰��Y������ʼλ�ü��������ֿ��ø߶�  */
#define SetIconview_xPos          0  /* �м䴰��Y������ʼλ��                    */



extern GUI_CONST_STORAGE GUI_BITMAP bmIdea;
extern GUI_CONST_STORAGE GUI_BITMAP bmArrows;
extern GUI_CONST_STORAGE GUI_BITMAP bmClock;
extern GUI_CONST_STORAGE GUI_BITMAP bmCompass;
extern GUI_CONST_STORAGE GUI_BITMAP bmMessages;
extern GUI_CONST_STORAGE GUI_BITMAP bmMusic;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhone;
extern GUI_CONST_STORAGE GUI_BITMAP bmPhotos;
extern GUI_CONST_STORAGE GUI_BITMAP bmVideos;
extern GUI_CONST_STORAGE GUI_BITMAP bmSafari;
extern GUI_CONST_STORAGE GUI_BITMAP bmWeather;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmSiri;
extern GUI_CONST_STORAGE GUI_BITMAP bmCamera;
extern GUI_CONST_STORAGE GUI_BITMAP bmUSB;
extern GUI_CONST_STORAGE GUI_BITMAP bmSetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmimsodiao;

extern CONFIG_DATA_U __configDataU;
extern CONFIG_DATA_S __configDataS;


static WIN_PARA WinParaOfCelLoad;			



static STRING_2_FORM  prStringArrayAndFormId[] ={
	{{"����","����","Return"},0xFF},
	{{"��������","��������","PrecSet"},FORMID_PRECISIORSET},
	{{"����Ԫ����","����Ԫ����","SensorConfig"},FORMID_SELSENSORCONF},
	{{"���","���","Zero Point"},FORMID_ZEROPOINT},
	{{"����ϵ��1","����ϵ��1","1st amplifier coe"},FORMID_AMP1},
	{{"����ϵ��2","����ϵ��2","2st amplifier coe"},FORMID_AMP2},
	{{"����ϵ��3","����ϵ��3","3st amplifier coe"},FORMID_AMP3},
	{{"����ϵ��4","����ϵ��4","4st amplifier coe"},FORMID_AMP4},
	{{"����ϵ��5","����ϵ��5","5st amplifier coe"},FORMID_AMP5},
	{{"����ϵ��6","����ϵ��6","6st amplifier coe"},FORMID_AMP6},
	NULL,
} ;

static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmUSB, 		      &__strBuf[0][0]},
	{&bmUSB,             &__strBuf[1][0]},
	{&bmUSB,    	        &__strBuf[2][0]},
	{&bmUSB,              &__strBuf[3][0]},
	{&bmUSB,               &__strBuf[4][0]},
	{&bmUSB,     	      &__strBuf[5][0]}, 
  
    {&bmUSB,				&__strBuf[6][0]},  
	{&bmUSB,               &__strBuf[7][0]},
	{&bmUSB,               &__strBuf[8][0]},
	{&bmUSB,               &__strBuf[9][0]},
	NULL,
};


unsigned char UI_RtLoadMenuSaveSuc(WM_MESSAGE * pMsg)///////////////�������ɹ��������ϼ��˵��������׳������Ҳ�����
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunNextFrom(FORMID_CALLOADICON);
		return 1;
	}else {
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;
		return 0;
	}
}


unsigned int __curFrmIconIndex = 0xFF; 
unsigned char RunLoadSetNextStep(void)
{
	int nowIdInStringIcon; 
	int frmId = 0xFF;
	if(__SaveDataSuccess == 1){
		if(prStringArrayAndFormId[__curFrmIconIndex].formId != 0xFF){
			if(prStringArrayAndFormId[__curFrmIconIndex].formId + 1 != 0xFF){
				__curFrmIconIndex++;
				nowIdInStringIcon = __curFrmIconIndex;
				frmId = prStringArrayAndFormId[nowIdInStringIcon].formId;
				RunNextFrom(frmId);
			}
		}
		return 1;
	}
	else return 0;
}

unsigned char UI_RunLoadNextSaveSuc(WM_MESSAGE * pMsg)///////////////�������ɹ���������һ�����棬�����׳�����
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunLoadSetNextStep();
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;
		return 0;
	}
}


static unsigned int nextFormIn = 0xFF;

void _cbCelLoadIconview(WM_MESSAGE * pMsg) 
{
	int NCode, Id, iconSel;
	switch (pMsg->MsgId) {
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) {
				case GUI_ID_ICONVIEW0:
					switch (NCode) {
						/* ICON�ؼ������Ϣ */
						case WM_NOTIFICATION_CLICKED:
							break;
						
						/* ICON�ؼ��ͷ���Ϣ */
						case WM_NOTIFICATION_RELEASED: 							
							/* ����Ӧѡ�� */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel >= 0){
								__curFrmIconIndex = iconSel;
								RunNextFrom(prStringArrayAndFormId[iconSel].formId);
								UI_CloseWindows(WinParaOfCelLoad.hWinMid);
							}
							break;
							
					}
				break;
			}
		break;
			
		/* �ػ���Ϣ*/
		case WM_PAINT:
			{	
				#if   LCD_NUM_LAYERS == 1 
					GUI_SetBkColor(DTCOLOR);
				#elif LCD_NUM_LAYERS == 2
					GUI_SetBkColor(GUI_TRANSPARENT);
				#endif
				GUI_Clear();
			}			
		break;			
		default:
			WM_DefaultProc(pMsg);
		break;
	}
}


/**
  * @brief  CreatCalLoadIconview�������м�Ĵ���
  * @param  none
  * @retval none
  */
static WM_HWIN CreatCalLoadIconview(void)
{
	char i=0;
	WM_HWIN SetIconview,TITTLE;

	for(i=0;i<GUI_COUNTOF(prStringArrayAndFormId) - 1;i++) strcpy(&__strBuf[i][0],prStringArrayAndFormId[i].pstr[__configDataU.languageSel]);
	WinParaOfCelLoad.hWinMid= WM_CreateWindowAsChild(
											0,											
											0,
											800,
											480,	
											HDTWIN, 
											WM_CF_SHOW|WM_CF_MEMDEV,
											_cbCelLoadIconview, 
											sizeof(WIN_PARA *)
											);

	TITTLE = TEXT_CreateEx(0, 5, 800 , 30, WinParaOfCelLoad.hWinMid, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT0, "Setting");	
	TEXT_SetFont(TITTLE, GUI_FONT_32B_1);	
											
	SetIconview=ICONVIEW_CreateEx(0,25,800,455,WinParaOfCelLoad.hWinMid, WM_CF_SHOW|WM_CF_HASTRANS,ICONVIEW_CF_AUTOSCROLLBAR_V, GUI_ID_ICONVIEW0,ICONVIEW_Width,ICONVIEW_Height+20);
											
	for (i = 0; i < GUI_COUNTOF(prStringArrayAndFormId) - 1; i++) {
		ICONVIEW_AddBitmapItem(SetIconview, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
		ICONVIEW_SetTextColor(SetIconview,i,GUI_WHITE);
	}	
	ICONVIEW_SetBkColor(SetIconview, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
	switch(__configDataU.languageSel){
		case 0:	ICONVIEW_SetFont(SetIconview,&GUI_Font20HZK);break;
		case 1:ICONVIEW_SetFont(SetIconview,&GUI_Font20HZKF);break;
		default:ICONVIEW_SetFont(SetIconview,GUI_FONT_16B_1);break;
		}
		/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
		ICONVIEW_SetSel(SetIconview,-1);
		/* ����ͼ����x ��y �����ϵļ�ࡣ*/
		ICONVIEW_SetSpace(SetIconview, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(SetIconview, GUI_COORD_Y, ICONVIEW_YSpace);
		/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
		ICONVIEW_SetIconAlign(SetIconview, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		
		return WinParaOfCelLoad.hWinMid;
/*-------------------------------------------------------------------------------------*/
}



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       Createmusic
*/
unsigned int RunFrmSysCalLoadIconView(void) 
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_CALLOADICON)].FrmHandle = CreatCalLoadIconview();
	return nextFormIn;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
