
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


//prStringArrayAndFormId�����������ֻ��IconIdOfTestType��ʹ��
#define STRID_CONTROLTYPE_RETURN				0  
#define STRID_CONTROLTYPE_TESTTYPE				1
#define STRID_CONTROLTYPE_TESTMODULE			2
#define STRID_CONTROLTYPE_LOADKEEP				3
#define STRID_CONTROLTYPE_FORCEUNIT				4
#define STRID_CONTROLTYPE_ELONGUNIT				5
#define STRID_CONTROLTYPE_STRESSUNIT			6
#define STRID_CONTROLTYPE_SENSORSELECT			7
#define STRID_CONTROLTYPE_BREAKTYPE				8
#define STRID_CONTROLTYPE_SPEEDSET				9
#define STRID_CONTROLTYPE_SOFTACCELE			10
#define STRID_CONTROLTYPE_PROTECT				11
#define STRID_CONTROLTYPE_PRELOAD				12
#define STRID_CONTROLTYPE_AOTURETURN			13
#define STRID_CONTROLTYPE_CLAMPSET				14
#define STRID_CONTROLTYPE_PRINTER				15
#define STRID_CONTROLTYPE_LANGUAGE				16
#define STRID_CONTROLTYPE_TIME					17
#define STRID_CONTROLTYPE_DISCODE				18
#define STRID_CONTROLTYPE_GASSET				19


//ͼƬ��������
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

//����������������
extern CONFIG_DATA_U __configDataU;
extern CONFIG_DATA_S __configDataS;

static  STRING_2_FORM  prStringArrayAndFormId[] ={
	{{"����","����","Return"},0xFF}, //0
	{{"��������","��������","Test Type"}, FORMID_TESTTYPE},	//1   
	{{"����ģʽ","����ģʽ","Control Mode"}, FORMID_TESTMODULE},	//2
	{{"��������","��������","Load keep"}, FORMID_LOADKEEP},//3
	{{"������λ","������λ","Force unit"}, FORMID_FORCEUNIT},//4
	{{"λ�Ƶ�λ","λ��","Elong Unit"}, FORMID_ELONGUNIT},//5
	{{"ǿ�ȵ�λ","ǿ�ȵ�λ","Stress Unit"}, FORMID_STRESSUNIT},//6
	{{"����Ԫѡ��","����Ԫѡ��","Sensor Select"}, FORMID_SENSORSELECT},//7
	{{"ͣ����ʽ","ͣ����ʽ","break Type"}, FORMID_BREAKTYPE},//8
	{{"�ٶ�","�ٶ�","Speed Setting"}, FORMID_SPEEDSET},//9
	{{"���ٶ�","���ٶ�","Soft Acceleration"}, FORMID_SOFTACCELE},//10
	{{"����","����","Protect"}, FORMID_PROTECT},//11
	{{"Ԥ����","Ԥ����","Pre Load"}, FORMID_PRELOAD},//12
	{{"�Զ���λ","�Զ���λ","Auto Return"}, FORMID_AOTURETURN},//13
	{{"�г־���","�г־���","Clamp Set"}, FORMID_CLAMPSET},//14
	{{"��ӡ��","��ӡ��","Printer"}, FORMID_PRINTER},//15
	{{"����","����","Language"},FORMID_LANGUAGE },//16
	{{"ʱ��","ʱ��","Time"}, FORMID_TIME},//17
	{{"System Discoder","System Discoder","System Discoder"}, FORMID_DISCODE},//18
	{{"����ʱ��","����ʱ��","Gas Set"}, FORMID_GASSET},//19 ����ʱ��
	{{NULL,NULL,NULL},0xFF },//20
} ;

//0xff: the flag of the icon end
static const unsigned char IconIdOfTestType[4][20] = {
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_GASSET,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
	{
		STRID_CONTROLTYPE_RETURN,
		STRID_CONTROLTYPE_TESTTYPE,
		STRID_CONTROLTYPE_TESTMODULE,
		STRID_CONTROLTYPE_LOADKEEP,
		STRID_CONTROLTYPE_FORCEUNIT,
		STRID_CONTROLTYPE_ELONGUNIT,
		STRID_CONTROLTYPE_STRESSUNIT,
		STRID_CONTROLTYPE_SENSORSELECT,
		STRID_CONTROLTYPE_BREAKTYPE,
		STRID_CONTROLTYPE_SPEEDSET,
		STRID_CONTROLTYPE_SOFTACCELE,
		STRID_CONTROLTYPE_PROTECT,
		STRID_CONTROLTYPE_PRELOAD,
		STRID_CONTROLTYPE_AOTURETURN,
		STRID_CONTROLTYPE_CLAMPSET,
		STRID_CONTROLTYPE_PRINTER,
		STRID_CONTROLTYPE_LANGUAGE,
		STRID_CONTROLTYPE_TIME,
		STRID_CONTROLTYPE_DISCODE,
		0xFF
	},
};


//�������ɹ��������ϼ��˵��������׳������Ҳ�����
unsigned char UI_RtUserMenuSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunNextFrom(FORMID_USERSET);
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}

}


static unsigned int __curFrmIconIndex = 0xFF;//���Iconview�Ժ��icon����
static unsigned char RunUserSetNextStep(void)
{
	int nowIdInStringIcon; 
	int frmId = 0xFF;
	if(__SaveDataSuccess == 1){
		if(IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex] != 0xFF){
			if(IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex+1] != 0xFF){
				__curFrmIconIndex++;
				nowIdInStringIcon = IconIdOfTestType[__configDataS.controlerType][__curFrmIconIndex];
				frmId = prStringArrayAndFormId[nowIdInStringIcon].formId;
				RunNextFrom(frmId);
			}
		}
		return 1;
	}
	else return 0;
}

//����������ݳɹ���������һ�����棬�����׳�����
unsigned char UI_RunUserNextSaveSuc(WM_MESSAGE * pMsg)
{
	if(__SaveDataSuccess == 1){	
		UI_CloseWindows(pMsg->hWin);
		RunUserSetNextStep();
		return 1;
	}
	else{ 
		ERR_ThrowError(0);
		__SaveDataSuccess = 1;

		return 0;
	}
	return 0;
}

static WIN_PARA WinParaOfUserConfig;			


static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmArrows,              &__strBuf[0][0]},//0����
	{&bmArrows,    	         &__strBuf[1][0]},//1��������
	{&bmArrows,              &__strBuf[2][0]},//2����ģʽ
	{&bmArrows,     	     &__strBuf[3][0]},//3��������
  
    {&bmArrows,				 &__strBuf[4][0]},//4������λ
	{&bmArrows,              &__strBuf[5][0]},//5λ�Ƶ�λ
	{&bmArrows, 		     &__strBuf[6][0]},//6ǿ�ȵ�λ
    {&bmArrows,    	         &__strBuf[7][0]},//7����Ԫѡ��
  
	{&bmArrows,  	 	     &__strBuf[8][0]},//8ͣ����ʽ   
	{&bmArrows,  	 	     &__strBuf[9][0]},//9�ٶ�
    {&bmArrows,   	         &__strBuf[10][0]},//10���ٶ�
	{&bmArrows,  	         &__strBuf[11][0]},//11���� 	
	
	{&bmArrows,              &__strBuf[12][0]},//12Ԥ����
	{&bmArrows,              &__strBuf[13][0]},//13�Զ���λ
	{&bmArrows,              &__strBuf[14][0]},//14�г־���
	{&bmArrows,              &__strBuf[15][0]},//15��ӡ��
	
	{&bmArrows,              &__strBuf[16][0]},//16����
	{&bmArrows,              &__strBuf[17][0]},//17ʱ��
	{&bmArrows,              &__strBuf[18][0]},//18 System Discoder
	{&bmArrows,              &__strBuf[19][0]},//19����ʱ��
	NULL,
};



void _cbSetIconviewSetting(WM_MESSAGE * pMsg) 
{

	int NCode, Id, iconSel;
	int testType;
	testType = __configDataS.controlerType;
	if(testType>3) testType = 0;
	switch (pMsg->MsgId) {
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) {
				case GUI_ID_ICONVIEW0:
					switch (NCode) 
					{
						case WM_NOTIFICATION_RELEASED: 							
							/* ����Ӧѡ�� */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel >= 0){
								__curFrmIconIndex = iconSel;
								RunNextFrom(prStringArrayAndFormId[IconIdOfTestType[testType][iconSel]].formId);
								UI_CloseWindows(WinParaOfUserConfig.hWinMid);
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


static WM_HWIN CreateUserSetIconview(void)
{	
	WM_HWIN SetIconview,TITTLE;
	int i, testType;
	testType = __configDataS.controlerType;
	if(testType>2) testType = 0;
	
	for(i=0;i<GUI_COUNTOF(prStringArrayAndFormId) - 1;i++) strcpy(&__strBuf[i][0],prStringArrayAndFormId[i].pstr[__configDataU.languageSel]);
	
	WinParaOfUserConfig.hWinMid= WM_CreateWindowAsChild(0,0,800,480,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,_cbSetIconviewSetting,sizeof(WIN_PARA *));

	TITTLE = TEXT_CreateEx(0, 5, 800 , 30, WinParaOfUserConfig.hWinMid, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT0, "Setting");	
	TEXT_SetFont(TITTLE, GUI_FONT_32B_1);	
											
	SetIconview=ICONVIEW_CreateEx( 0,25,800,455,WinParaOfUserConfig.hWinMid,WM_CF_SHOW|WM_CF_HASTRANS,
								ICONVIEW_CF_AUTOSCROLLBAR_V,GUI_ID_ICONVIEW0,ICONVIEW_Width,ICONVIEW_Height+20);				      
		
	for (i = 0; i < GUI_COUNTOF(prStringArrayAndFormId); i++) {		
		if(IconIdOfTestType[testType][i] != 0xFF){
			ICONVIEW_AddBitmapItem(SetIconview, _aBitmapItem[IconIdOfTestType[testType][i]].pBitmap,_aBitmapItem[IconIdOfTestType[testType][i]].pText);
			ICONVIEW_SetTextColor(SetIconview,i,GUI_WHITE);
		}
		else break;
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
	return WinParaOfUserConfig.hWinMid;

}



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

static unsigned int nextFormIn = 0xFF;
unsigned int RunFrmUserSetIconView(void) 
{
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_USERSET)].FrmHandle = CreateUserSetIconview();
	return nextFormIn;
}


