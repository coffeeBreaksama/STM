#include "includes.h"
#include "app.h"

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

static WIN_PARA _WinParaOfSystemConfig;			

static STRING_2_FORM  prStringArrayAndFormId[] ={
	{{"����","����","Return"},0xFF},
	{{"��������","��������","Machine Direct"},FORMID_MACHINEDIRECT},
	{{"�������","�������","Motor Yype"},FORMID_MOTORTYPE},
	{{"�ٶ�","�ٶ�","speedCel"},FORMID_SPEEDCEL},
	{{"������","������","SelectControlType"},FORMID_SELCONTROLTYPE},
	{{"��ӡ����","��ӡ����","Print Argu"},FORMID_PRINTRESULT},
	{{"λ����Դ","λ����Դ","Disp Form"},FORMID_DISPFORM},
	{{"λ��","λ��","CalElongDisp"},FORMID_CALELONGDISP},
	{{"�������˵���","�������˵���","CalLoad Iconview"},FORMID_CALLOADICON},
	{{NULL,NULL,NULL},0xFF },
} ;

//�������ɹ��������ϼ��˵��������׳������Ҳ�����
unsigned char UI_RtSysMenuSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunNextFrom(FORMID_SYSTEMSET);
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}
}


static unsigned int __curFrmIconIndex = 0xFF; //���Iconview�Ժ��icon����
static unsigned char RunSysSetNextStep(void)
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
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}
}
//�������ɹ���������һ�����ڣ������׳������Ҳ�����
unsigned char UI_RunSysNextSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunSysSetNextStep();
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;
		return 0;
	}
}

static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmMusic, 		      &__strBuf[0][0]},
	{&bmMusic,             &__strBuf[1][0]},
	{&bmMusic,    	        &__strBuf[2][0]},
	{&bmMusic,              &__strBuf[3][0]},
	{&bmMusic,               &__strBuf[4][0]},
	{&bmMusic,     	      &__strBuf[5][0]}, 
  
    {&bmMusic,				&__strBuf[6][0]},  
	{&bmMusic,               &__strBuf[7][0]},
	{&bmMusic,     	      &__strBuf[8][0]},
};




void _cbSystemConfigSet(WM_MESSAGE * pMsg) 
{
	int NCode, Id, iconSel;
	switch (pMsg->MsgId) {
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) {
				case GUI_ID_ICONVIEW0:
					switch (NCode) {
						case WM_NOTIFICATION_RELEASED: 							
							/* ����Ӧѡ�� */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel >= 0){
								__curFrmIconIndex = iconSel;
								RunNextFrom(prStringArrayAndFormId[iconSel].formId);
								UI_CloseWindows(_WinParaOfSystemConfig.hWinMid);
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


static WM_HWIN CreateSystemSetIconView(void)
{
	char i=0;
	WM_HWIN SetIconview,TITTLE;

	for(i=0;i<GUI_COUNTOF(prStringArrayAndFormId) - 1;i++) strcpy(&__strBuf[i][0],prStringArrayAndFormId[i].pstr[__configDataU.languageSel]);
	_WinParaOfSystemConfig.hWinMid = WM_CreateWindowAsChild(0,0,800,480,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,_cbSystemConfigSet,sizeof(WIN_PARA *));

	TITTLE = TEXT_CreateEx(0, 5, 800 , 30, _WinParaOfSystemConfig.hWinMid, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT0, "Setting");	
	TEXT_SetFont(TITTLE, GUI_FONT_32B_1);	
											
	SetIconview=ICONVIEW_CreateEx(0,25,800,455,_WinParaOfSystemConfig.hWinMid,WM_CF_SHOW|WM_CF_HASTRANS,
								ICONVIEW_CF_AUTOSCROLLBAR_V,GUI_ID_ICONVIEW0,ICONVIEW_Width,ICONVIEW_Height+20);
											 
	for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) {
		ICONVIEW_AddBitmapItem(SetIconview, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
		ICONVIEW_SetTextColor(SetIconview,i,GUI_WHITE);
	}	
	
	ICONVIEW_SetBkColor(SetIconview, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
	switch(__configDataU.languageSel){
		case 0:	ICONVIEW_SetFont(SetIconview,&GUI_Font20HZK);break;
		case 1:ICONVIEW_SetFont(SetIconview,&GUI_Font20HZKF);break;
		default:ICONVIEW_SetFont(SetIconview,GUI_FONT_16B_1);break;
	}

	ICONVIEW_SetSel(SetIconview,-1);
	ICONVIEW_SetSpace(SetIconview, GUI_COORD_X, ICONVIEW_XSpace);
	ICONVIEW_SetSpace(SetIconview, GUI_COORD_Y, ICONVIEW_YSpace);
	ICONVIEW_SetIconAlign(SetIconview, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
	return _WinParaOfSystemConfig.hWinMid;

}



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

static unsigned int nextFormIn = 0xFF;
unsigned int RunFrmSystemSetIconView(void) 
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_SYSTEMSET)].FrmHandle = CreateSystemSetIconView();
	return nextFormIn;
}


/*************************** End of file ****************************/
