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
static WIN_PARA _MainIconWinPara;	//�û�ʹ�õĴ��ڶ�������
static WM_HWIN _mainIcon;//���˵����
extern void UI_InitSkin(void);

static const char*  prStringArray[][3] ={
	{"����������","����������","Main Test"},
	{"����","����","Sample"},
	{"�û�����","�û�����","User Set"},
	{"ϵͳ����","ϵͳ����","System Set"},
	{"��ӡ","��ӡ","Print"},
	{"����","����","About"},
	{"Null","Null","Null"},
	{"Null","Null","Null"}
} ;

/* ��������ICONVIEW0ͼ��Ĵ��� */
static const BITMAP_ITEM _aBitmapItem[] = 
{
	{&bmimsodiao,           &__strBuf[0][0]},
	{&bmMusic,    	        &__strBuf[1][0]},
	{&bmSiri,				&__strBuf[2][0]},
	{&bmWeather,     	    &__strBuf[3][0]}, 
  
	{&bmCompass,          &__strBuf[4][0]}, 
	{&bmClock,              &__strBuf[5][0]},
	/*{&bmSafari, 		       "Null"}, 
	{&bmCamera,    	       "Null"}, 
  
	{&bmPhone,  	 	        "Null"},    
	{&bmMessages,  	 	   "Null"},
	{&bmPhotos,   	      "Null"},		
	{&bmUSB,  	              "Null"},   	
	{&bmArrows,            "Null"}, 
	{&bmSetting,            "Null"},*/
};


static unsigned int _IconIdArray[] ={
	FORMID_MAINTEST,
	FORMID_SAMPLEINFO,
	FORMID_USERSET,
	FORMID_SYSPASSWORD,
	FORMID_PRINTRESULT,
	FORMID_ABOUT,
	0xFF
};

void UpdataDesktopLanguage(void)
{		
	unsigned char i;
	for(i=0;i<=4;i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
	switch(__configDataU.languageSel){
	case 1:
		ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZKF);
	break;
	case 0:
	default:
		ICONVIEW_SetFont(_mainIcon,&GUI_Font20HZK);
	break;
	}
	for(i=0;i<=4;i++) ICONVIEW_SetItemText(_mainIcon,i,&__strBuf[i][0]);
}


static void _cbBkWindow(WM_MESSAGE * pMsg) 
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
					if(iconSel >= 0) RunNextFrom(_IconIdArray[iconSel]);
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
	TEXT_SetText(hText,"BRK-TEST");
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
static WM_HWIN CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	for(i=0;i < GUI_COUNTOF(prStringArray);i++) strcpy(&__strBuf[i][0],prStringArray[i][__configDataU.languageSel]);
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
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) {
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

		return _MainIconWinPara.hWinMid;
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
unsigned int FrmRunAppMenu(void)
{
	//׼������3�����ڣ�������ʹ�õ����û���������������ڻص�������ʹ��
	_MainIconWinPara.xSizeLCD = 800;			            //LCD��Ļ�ߴ�
	_MainIconWinPara.ySizeLCD = 400;				            //LCD��Ļ�ߴ�
	_MainIconWinPara.xSizeBM  = ICONVIEW_Width;				            //ͼ����
	_MainIconWinPara.ySizeBM  = ICONVIEW_Height;				            //ͼ��߶�
	_MainIconWinPara.xPosWin	 = MIDWIN_xPos;							          //���ڵ���ʼλ��
	_MainIconWinPara.yPosWin  = MIDWIN_yPos;							          //���ڵ���ʼλ��
	_MainIconWinPara.xSizeWin = _MainIconWinPara.xSizeLCD;						      //���ڳߴ�
	_MainIconWinPara.ySizeWin = _MainIconWinPara.ySizeLCD-_MainIconWinPara.yPosWin;	//���ڳߴ�
  
	/* ������������ ״̬������������������*/
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_APPMENU)].FrmHandle = CreateMidWin();
	CreateTopWin();
	return 0xFF;
}

void emWinMainApp(void)
{

	////////////////��ʼ��////////////////////
	UI_InitSkin();
	WM_SetCallback(HDTWIN, _cbBkWindow);
	WM_CreateTimer(HDTWIN, 0, 1000, 0);
	FrmRunAppMenu();
	while(1)
	{	
		GUI_Delay(10);
	}

}
/*************************** End of file ****************************/
