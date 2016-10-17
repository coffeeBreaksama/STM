#include "includes.h"
#include "app.h"
#include "F20HZK.h"
#include "F20HZKF.h"
/*
*********************************************************************************************************
*                                         宏定义 
*********************************************************************************************************
*/
#define ICONVIEW_Width      70  /* 控件ICONVIEW的宽                         */  
#define ICONVIEW_Height     70  /* 控件ICONVIEW的高，包括图标的Y方向间距    */  
#define ICONVIEW_XSpace     30  /* 控件ICONVIEW的X方向间距                  */ 
#define ICONVIEW_YSpace     40  /* 控件ICONVIEW的Y方向间距                  */ 
#define ICONVIEW_XPos       10  /* 控件ICONVIEW的X方向调整距离              */
#define BOTWIN_YSpace       60  /* 屏幕下方部分窗口Y方向间距                */
#define MIDWIN_yPos         40  /* 中间窗口Y方向起始位置即顶部文字可用高度  */
#define MIDWIN_xPos          0  /* 中间窗口Y方向起始位置                    */

/*
*********************************************************************************************************
*                                      变量
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
static WIN_PARA _MainIconWinPara;	//用户使用的窗口额外数据
static WM_HWIN _mainIcon;//主菜单句柄
extern void UI_InitSkin(void);

static const char*  prStringArray[][3] ={
	{"试验主界面","试验主界面","Main Test"},
	{"试样","试验","Sample"},
	{"用户设置","用户设置","User Set"},
	{"系统设置","系统设置","System Set"},
	{"打印","打印","Print"},
	{"关于","关于","About"},
	{"Null","Null","Null"},
	{"Null","Null","Null"}
} ;

/* 用于桌面ICONVIEW0图标的创建 */
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
		/* 重绘消息*/
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
*	函 数 名: _cbMidWin
*	功能说明: 
*	形    参：WM_MESSAGE * pMsg
*	返 回 值: 无
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
				/* ICON控件点击消息 */
				case WM_NOTIFICATION_CLICKED:
				break;
						
				/* ICON控件释放消息 */
				case WM_NOTIFICATION_RELEASED: 							
				/* 打开相应选项 */
					iconSel = ICONVIEW_GetSel(pMsg->hWinSrc);
					if(iconSel >= 0) RunNextFrom(_IconIdArray[iconSel]);
				break;	
				}
			break;
			}
		break;
			
		/* 重绘消息*/
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
  * @brief  CreateTopWin，创建顶部的窗口
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* 顶部的 "wildfire"文本 */
	hText = TEXT_CreateEx(0, 2, 200 , 30, HDTWIN, WM_CF_SHOW|WM_CF_MEMDEV, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "");
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
	TEXT_SetText(hText,"BRK-TEST");
	TEXT_SetTextColor(hText,GUI_WHITE);
	

	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD/2-50,2,100,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,"11:56:00");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_20B_ASCII);
  
	/* 状态栏的时间显示文本 */
	hText = TEXT_CreateEx(_MainIconWinPara.xSizeLCD-200,2,200,30,HDTWIN,WM_CF_SHOW|WM_CF_MEMDEV,GUI_TA_RIGHT|TEXT_CF_VCENTER,GUI_ID_TEXT2,"CPU: 10%");
	TEXT_SetTextColor(hText,GUI_WHITE);
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);
}
/**
  * @brief  CreateMidWin，创建中间的窗口
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
					/*在指定位置创建指定尺寸的ICONVIEW1 小工具*/
					MIDWIN=ICONVIEW_CreateEx(
											 ICONVIEW_XPos, 					          /* 小工具的最左像素（在父坐标中）*/
											 0, 								                /* 小工具的最上像素（在父坐标中）*/
											 _MainIconWinPara.xSizeLCD-ICONVIEW_XPos,	  /* 小工具的水平尺寸（单位：像素）*/
											 3*(_MainIconWinPara.ySizeBM+35), 			      /* 小工具的垂直尺寸（单位：像素）*/
											 _MainIconWinPara.hWinMid, 				          /* 父窗口的句柄。如果为0 ，则新小工具将成为桌面（顶级窗口）的子窗口 */
											 WM_CF_SHOW|WM_CF_HASTRANS,         /* 窗口创建标记。为使小工具立即可见，通常使用 WM_CF_SHOW */ 
											 0,                                 //ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* 默认是0，如果不够现实可设置增减垂直滚动条 */
											 GUI_ID_ICONVIEW0, 			            /* 小工具的窗口ID */
											 ICONVIEW_Width, 				            /* 图标的水平尺寸 */
											 ICONVIEW_Height+20);				        /* 图标的垂直尺寸 */
											 
		/* 向ICONVIEW 小工具添加新图标 */
		for (i = 0; i < GUI_COUNTOF(_aBitmapItem); i++) {
			ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem[i].pBitmap,_aBitmapItem[i].pText);
			ICONVIEW_SetTextColor(MIDWIN,i,GUI_WHITE);
		}	
		/* 设置小工具的背景色 32 位颜色值的前8 位可用于alpha混合处理效果*/
		ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, 0xffffc0 | 0x80000000);
		/* 设置图标字体 */
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
		/* 设置初始选择的图标为 -1 (表示尚未选择)*/
		ICONVIEW_SetSel(MIDWIN,-1);
		/* 设置图标在x 或y 方向上的间距。*/
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
		/* 设置对齐方式 在5.22版本中最新加入的 */
		ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
		/*将MIDWIN的句柄赋给全局变量*/
		_mainIcon = MIDWIN;

		return _MainIconWinPara.hWinMid;
}	
/*-------------------------------------------------------------------------------------*/

/*
*********************************************************************************************************
*	函 数 名: emWinMainApp
*	功能说明: GUI主函数 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
unsigned int FrmRunAppMenu(void)
{
	//准备建立3个窗口，以下是使用到的用户定义参数，方便在回调函数中使用
	_MainIconWinPara.xSizeLCD = 800;			            //LCD屏幕尺寸
	_MainIconWinPara.ySizeLCD = 400;				            //LCD屏幕尺寸
	_MainIconWinPara.xSizeBM  = ICONVIEW_Width;				            //图标宽度
	_MainIconWinPara.ySizeBM  = ICONVIEW_Height;				            //图标高度
	_MainIconWinPara.xPosWin	 = MIDWIN_xPos;							          //窗口的起始位置
	_MainIconWinPara.yPosWin  = MIDWIN_yPos;							          //窗口的起始位置
	_MainIconWinPara.xSizeWin = _MainIconWinPara.xSizeLCD;						      //窗口尺寸
	_MainIconWinPara.ySizeWin = _MainIconWinPara.ySizeLCD-_MainIconWinPara.yPosWin;	//窗口尺寸
  
	/* 创建三个窗口 状态栏、控制栏、主窗口*/
	__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_APPMENU)].FrmHandle = CreateMidWin();
	CreateTopWin();
	return 0xFF;
}

void emWinMainApp(void)
{

	////////////////初始化////////////////////
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
