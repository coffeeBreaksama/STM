/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.5.1�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "includes.h"
#include "app.h"
#include "F20HZK.h"
#include "F20HZKF.h"
/*
*********************************************************************************************************
*                                         �궨�� 
*********************************************************************************************************
*/
#define ICONVIEW_Width      70  /* �ؼ�ICONVIEW�Ŀ�                         */  
#define ICONVIEW_Height     70  /* �ؼ�ICONVIEW�ĸߣ�����ͼ���Y������    */  
#define ICONVIEW_XSpace     30  /* �ؼ�ICONVIEW��X������                  */ 
#define ICONVIEW_YSpace     40  /* �ؼ�ICONVIEW��Y������                  */ 
#define ICONVIEW_XPos       10  /* �ؼ�ICONVIEW��X�����������              */
#define BOTWIN_YSpace       60  /* ��Ļ�·����ִ���Y������                */
#define MIDWIN_yPos         40  /* �м䴰��Y������ʼλ�ü��������ֿ��ø߶�  */
#define MIDWIN_xPos          0  /* �м䴰��Y������ʼλ��                    */

/*
*********************************************************************************************************
*                                      ����
*********************************************************************************************************
*/ 
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

char  __strBuf[14][30];
static WIN_PARA _MainIconWinPara;			//�û�ʹ�õĴ��ڶ�������
WM_HWIN _mainIcon;//���˵����

static const char*  prStringArray[][3] ={
	{"����������","����������","Main Test"},
	{"�û�����","�û�����","User Set"},
	{"ϵͳ����","ϵͳ����","System Set"},
	{"����","����","Sample"},
	{"δ��","δ��","Null"},
	{"Null","Null","Null"},
	{"Null","Null","Null"},
	{"Null","Null","Null"}
} ;
int __GetValueType(void* value)
{
	char type;
	if(sizeof(value) > 4) type = 10;
	else if(sizeof(value) == 4) type = 4;
	else if(sizeof(value) == 2 ) type = 2;
	else if(sizeof(value) == 1)  type = 1;
	return type;
}
/* ��������ICONVIEW0ͼ��Ĵ��� */
static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmimsodiao,           &__strBuf[0][0]},
	{&bmMusic,    	        &__strBuf[1][0]},
	{&bmSiri,				&__strBuf[2][0]},
	{&bmWeather,     	    &__strBuf[3][0]}, 
  
	{&bmCompass,          "Null"},  
	{&bmClock,              "Null"},
	{&bmSafari, 		       "Null"}, 
	{&bmCamera,    	       "Null"}, 
  
	{&bmPhone,  	 	        "Null"},    
	{&bmMessages,  	 	   "Null"},
	{&bmPhotos,   	      "Null"},		
	{&bmUSB,  	              "Null"},   	
	{&bmArrows,            "Null"}, 
	{&bmSetting,            "Null"},
};

/**********************************************************************************************************
/**	�� �� ��: _cbBkWindow
*	����˵��: ���洰�ڵĻص����� 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/

static unsigned int _nextWindow0[] ={
	FORMID_MAINTEST,
	FORMID_USERSET,
	FORMID_SYSTEMSET,
	FORMID_SAMPLEINFO,
	FORMID_PRINTRESULT,
};

unsigned int (* FormFuncIdArray[])(void) = {
	FUN_ICON0Clicked,//Main Test                        0
	FUN_ICON1Clicked,//Set User Config Icon List		1
	FUN_ICON2Clicked,//Set System config Icon List		2
	FUN_ICON3Clicked,// SampleInfo                      3
	FUN_ICON4Clicked,// PrintResult (TODO)              4
	
	SETUSER_ICON1Clicked,//Test Type					5
	SETUSER_ICON2Clicked,//Test Module					6
	SETUSER_ICON3Clicked,//Load keep					7

	SETUSER_ICON4Clicked,//Force unit					8
	SETUSER_ICON5Clicked,//Elong Unit					9
	SETUSER_ICON6Clicked,//Stress Unit					10
	SETUSER_ICON7Clicked,//Sensor Select				11
	SETUSER_ICON8Clicked,//break Type					12

	SETUSER_ICON9Clicked,//Speed Setting				13
	SETUSER_ICON10Clicked,//Soft Acceleration			14
	SETUSER_ICON11Clicked,//Protece						15
	SETUSER_ICON12Clicked,//Pre Load					16
	SETUSER_ICON13Clicked,//Auto Return					17

	SETUSER_ICON14Clicked,//Clamp Set					18
	SETUSER_ICON15Clicked,//Printer						19
	SETUSER_ICON16Clicked,//Language					20
	SETUSER_ICON17Clicked,//Time						21
	SETUSER_ICON17Clicked,//System discode(TODO)		22

	SETSYS_ICON1Clicked,//Machine Direct				23
	SETSYS_ICON2Clicked,//Motor Yype					24
	SETSYS_ICON3Clicked,//speedCel						25
	SETSYS_ICON4Clicked,//SelectControlType				26
	SETSYS_ICON5Clicked,//Disp Form						27
	SETSYS_ICON6Clicked,//CalElongDisp					28
	SETSYS_ICON7Clicked,//CalLoad Iconview				29
	SETSYS_ICON8Clicked,//Precisior Set					30
	SETSYS_ICON9Clicked,//Sensor Config cel				31
	SETSYS_ICON10Clicked,//Zero Point					32
	SETSYS_ICON11Clicked,//AmplifierCoe 1               33
	SETSYS_ICON12Clicked,//AmplifierCoe 2				34
	SETSYS_ICON13Clicked,//AmplifierCoe 3				35
	SETSYS_ICON14Clicked,//AmplifierCoe 4				36
	SETSYS_ICON15Clicked,//AmplifierCoe 5				37
	SETSYS_ICON16Clicked,//AmplifierCoe 6				38
};



unsigned int RunNextFrom(int nextId)
{
	do{
		if(nextId < 50){
			nextId = (* FormFuncIdArray[nextId])();}
	}while(nextId != 0xFF);
	return 0xFF;
}

void __moveListSelUp(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) - time;
	if(listSel < 0) listSel = numOfList;
	LISTBOX_SetSel(hList,listSel);
};

void __moveListSelDown(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) + time;
	if(listSel > numOfList - 1) listSel = 0;
	LISTBOX_SetSel(hList,listSel);
};

unsigned char __runNextStep(int nowId)
{
	static unsigned char nextIdTestType[][30] = {
		{1,2,3,4},
		{1,2,3,4,5},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
		{17,18,19,20},
	};

	
	int i;
	for(i = 0; i <= 30; i++){
		if(nowId == nextIdTestType[__configDataU.testMethodLaOrYa][i]){
			RunNextFrom(nextIdTestType[__configDataU.testMethodLaOrYa][i+1]);
			break;
		}
	}

	return 0;
}

void __SetListBoxTextAll(WM_HWIN hItem,GUI_ConstString *str1,GUI_ConstString *str2,GUI_ConstString *str3)
{	
	    if(__configDataU.languageSel == 0) LISTBOX_SetText(hItem, str1);
		else if(__configDataU.languageSel == 1) LISTBOX_SetText(hItem, str2);
        else LISTBOX_SetText(hItem, str3); 

}
/*void __SetListBoxTextAllTest(WM_HWIN hItem,const char*  *ppstr)
{		GUI_ConstString *pList;
		int i = 0;
		int sizeOfArray = GUI_COUNTOF(ppstr);
		int a = sizeof(ppstr[0]);
		char *b;
		for(i = 0 + __configDataU.languageSel * a;;i += sizeOfArray){
			if(*(ppstr+i) != NULL) {
				LISTBOX_AddString(hItem, *(ppstr+i));}
			else break;
		}
}*/

unsigned int GetNextFrom(int nextId)
{
	return 0xff;
}

void __CloseWindows(WM_MESSAGE * pMsg)//�رյ�ǰ�򿪵����ô���
{
	WM_DeleteWindow(pMsg->hWin);
	if(keypadflag == 1){
		WM_DeleteWindow(hkeypad);
		keypadflag = 0;
	  }
	//RunNextFrom(GetNextFrom());
}
void UpdataDesktopLanguage(void)
{		
		unsigned char i;
		for(i=0;i<=4;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
		switch(__configDataU.languageSel){
			case 0:	
				ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZK);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
				break;
			case 1:
				ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZKF);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
			break;
			default:
				ICONVIEW_SetFont(_mainIcon,GUI_FONT_16B_1);
				for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
				break;
		}
}


void _cbBkWindow(WM_MESSAGE * pMsg) 
{

  char text_buffer[20]={0};
	switch (pMsg->MsgId) 
	{
		/* �ػ���Ϣ*/
		case WM_PAINT:		
#if   LCD_NUM_LAYERS == 1 
				GUI_SetBkColor(DTCOLOR);
#elif LCD_NUM_LAYERS == 2
          GUI_SetBkColor(GUI_TRANSPARENT);
#endif
		GUI_Clear();	
        ICONVIEW_SetSel(WM_GetDialogItem(_MainIconWinPara.hWinMid, GUI_ID_ICONVIEW0),-1);
		break;
    case WM_TIMER:
      
      break;
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: _cbMidWin
*	����˵��: 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void _cbMidWin(WM_MESSAGE * pMsg) 
{
	int NCode, Id,iconSel;
	switch (pMsg->MsgId) 
	{
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) 
			{
				case GUI_ID_ICONVIEW0:
					switch (NCode) 
					{
						/* ICON�ؼ������Ϣ */
						case WM_NOTIFICATION_CLICKED:
							break;
						
						/* ICON�ؼ��ͷ���Ϣ */
						case WM_NOTIFICATION_RELEASED: 							
							/* ����Ӧѡ�� */
							iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
							if(iconSel > -1)
							RunNextFrom(_nextWindow0[ICONVIEW_GetSel(pMsg->hWinSrc)]);
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
  * @brief  CreateTopWin�����������Ĵ���
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* ������ "wildfire"�ı� */
	hText = TEXT_CreateEx(0, 2, 200 , 30, HDTWIN, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "");
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
	TEXT_SetText(hText,"BH-STM32F429");
	TEXT_SetTextColor(hText,GUI_WHITE);
	

	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD/2-50,2,100,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,"11:56:00");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_20B_ASCII);
  
  	/* ״̬����ʱ����ʾ�ı� */
	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD-200,2,200,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_RIGHT|TEXT_CF_VCENTER,GUI_ID_TEXT2,"CPU: 10%");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
}
/**
  * @brief  CreateMidWin�������м�Ĵ���
  * @param  none
  * @retval none
  */
static void CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	for(i=0;i<=4;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	_MainIconWinPara.hWinMid= WM_CreateWindowAsChild(
											_MainIconWinPara.xPosWin,											
											_MainIconWinPara.yPosWin,
											_MainIconWinPara.xSizeWin,
											_MainIconWinPara.ySizeWin,	
											HDTWIN, 
											WM_CF_SHOW|WM_CF_MEMDEV,
											_cbMidWin, 
											sizeof(WIN_PARA *)
											);
/*-------------------------------------------------------------------------------------*/
					/*��ָ��λ�ô���ָ���ߴ��ICONVIEW1 С����*/
					MIDWIN=ICONVIEW_CreateEx(
											 ICONVIEW_XPos, 					          /* С���ߵ��������أ��ڸ������У�*/
											 0, 								                /* С���ߵ��������أ��ڸ������У�*/
											 _MainIconWinPara.xSizeLCD-ICONVIEW_XPos,	  /* С���ߵ�ˮƽ�ߴ磨��λ�����أ�*/
											 3*(_MainIconWinPara.ySizeBM+35), 			      /* С���ߵĴ�ֱ�ߴ磨��λ�����أ�*/
											 _MainIconWinPara.hWinMid, 				          /* �����ڵľ�������Ϊ0 ������С���߽���Ϊ���棨�������ڣ����Ӵ��� */
											 WM_CF_SHOW|WM_CF_HASTRANS,         /* ���ڴ�����ǡ�ΪʹС���������ɼ���ͨ��ʹ�� WM_CF_SHOW */ 
											 0,                                 //ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* Ĭ����0�����������ʵ������������ֱ������ */
											 GUI_ID_ICONVIEW0, 			            /* С���ߵĴ���ID */
											 ICONVIEW_Width, 				            /* ͼ���ˮƽ�ߴ� */
											 ICONVIEW_Height+20);				        /* ͼ��Ĵ�ֱ�ߴ� */
											 
		/* ��ICONVIEW С���������ͼ�� */
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) 
		{
			ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
			ICONVIEW_SetTextColor(MIDWIN,i,GUI_WHITE);
		}	
		/* ����С���ߵı���ɫ 32 λ��ɫֵ��ǰ8 λ������alpha��ϴ���Ч��*/
		ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
		/* ����ͼ������ */
		switch(__configDataU.languageSel){
			case 0:	
				ICONVIEW_SetFont(MIDWIN,&GUI_Font20HZK);
				break;
			case 1:
				ICONVIEW_SetFont(MIDWIN,&GUI_Font20HZKF);
			break;
			default:
				ICONVIEW_SetFont(MIDWIN,GUI_FONT_16B_1);
				break;
		}
		/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
		ICONVIEW_SetSel(MIDWIN,-1);
		/* ����ͼ����x ��y �����ϵļ�ࡣ*/
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
		/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
		ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		/*��MIDWIN�ľ������ȫ�ֱ���*/
		_mainIcon = MIDWIN;
}	
/*-------------------------------------------------------------------------------------*/

/*
*********************************************************************************************************
*	�� �� ��: emWinMainApp
*	����˵��: GUI������ 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void emWinMainApp(void)
{
  FRAMEWIN_SKINFLEX_PROPS FRAMEWIN_pProps;
  RADIO_SKINFLEX_PROPS    RADIO_pProps;



  
	//׼������3�����ڣ�������ʹ�õ����û���������������ڻص�������ʹ��
	_MainIconWinPara.xSizeLCD = 800;			            //LCD��Ļ�ߴ�
	_MainIconWinPara.ySizeLCD = 400;				            //LCD��Ļ�ߴ�
	_MainIconWinPara.xSizeBM  = ICONVIEW_Width;				            //ͼ����
	_MainIconWinPara.ySizeBM  = ICONVIEW_Height;				            //ͼ��߶�
	_MainIconWinPara.xPosWin	 = MIDWIN_xPos;							          //���ڵ���ʼλ��
	_MainIconWinPara.yPosWin  = MIDWIN_yPos;							          //���ڵ���ʼλ��
	_MainIconWinPara.xSizeWin = _MainIconWinPara.xSizeLCD;						      //���ڳߴ�
	_MainIconWinPara.ySizeWin = _MainIconWinPara.ySizeLCD-_MainIconWinPara.yPosWin;	//���ڳߴ�
  
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	//FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
  
  /***************************����Ƥ��*****************************/
  FRAMEWIN_GetSkinFlexProps(&FRAMEWIN_pProps,FRAMEWIN_SKINFLEX_PI_ACTIVE);
  FRAMEWIN_pProps.aColorFrame[0]=GUI_BLACK;
  FRAMEWIN_pProps.aColorFrame[1]=GUI_BLACK;
  FRAMEWIN_pProps.aColorFrame[2]=GUI_BLACK;
  FRAMEWIN_pProps.Radius=0;
  FRAMEWIN_pProps.aColorTitle[0]=GUI_BLACK;
  FRAMEWIN_pProps.aColorTitle[1]=GUI_BLACK;
  FRAMEWIN_SetSkinFlexProps(&FRAMEWIN_pProps,FRAMEWIN_SKINFLEX_PI_ACTIVE);
  FRAMEWIN_SetDefaultClientColor(APPBKCOLOR);

  FRAMEWIN_SetDefaultTextColor(1,TEXTCOLOR);
  FRAMEWIN_SetDefaultTitleHeight(30);
  FRAMEWIN_SetDefaultTextAlign(GUI_TA_LEFT | GUI_TA_VCENTER);

  WINDOW_SetDefaultBkColor(APPBKCOLOR);
  
  EDIT_SetDefaultBkColor(EDIT_CI_ENABLED,APPBKCOLOR);
  EDIT_SetDefaultTextColor(EDIT_CI_ENABLED,TEXTCOLOR);
  
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_UNSEL,APPBKCOLOR);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_SEL,GUI_BLUE);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_SELFOCUS,GUI_BLUE);
  LISTBOX_SetDefaultBkColor(LISTBOX_CI_DISABLED,APPBKCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_UNSEL,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_SEL,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_SELFOCUS,TEXTCOLOR);
  LISTBOX_SetDefaultTextColor(LISTBOX_CI_DISABLED,TEXTCOLOR);
  
  TEXT_SetDefaultTextColor(TEXTCOLOR);
  
  RADIO_SetDefaultTextColor(TEXTCOLOR);
  RADIO_GetSkinFlexProps(&RADIO_pProps,0);
  RADIO_pProps.aColorButton[3]=GUI_YELLOW;
  RADIO_SetSkinFlexProps(&RADIO_pProps,0);
  
  CHECKBOX_SetDefaultTextColor(TEXTCOLOR);
  ////////////////////Language Init////////////////////////////////
		switch(__configDataU.languageSel){
			case 0:	
				TEXT_SetDefaultFont(&GUI_Font20HZK);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZK);
				EDIT_SetDefaultFont(&GUI_Font20HZK);
				LISTBOX_SetDefaultFont(&GUI_Font20HZK);
				BUTTON_SetDefaultFont(&GUI_Font20HZK);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZK);
				break;
			case 1:
				TEXT_SetDefaultFont(&GUI_Font20HZKF);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZKF);
				EDIT_SetDefaultFont(&GUI_Font20HZKF);
				LISTBOX_SetDefaultFont(&GUI_Font20HZKF);
				BUTTON_SetDefaultFont(&GUI_Font20HZKF);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZKF);
			break;
			default:
				FRAMEWIN_SetDefaultFont(GUI_FONT_16B_1);
				BUTTON_SetDefaultFont(GUI_FONT_16B_1);
				LISTBOX_SetDefaultFont(GUI_FONT_32B_1);
				CHECKBOX_SetDefaultFont(GUI_FONT_32B_1);
				CHECKBOX_SetDefaultFont(GUI_FONT_32B_1);
				break;
		}
  
	/*************************************************************************/
	WM_SetCallback(HDTWIN, _cbBkWindow);
	WM_CreateTimer(HDTWIN, 0, 1000, 0);
	/* ������������ ״̬������������������*/
	CreateMidWin();
	CreateTopWin();
	while(1)
	{	
		GUI_Delay(10);
	}
}
/*************************** End of file ****************************/
