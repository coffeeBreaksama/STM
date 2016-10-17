
#include "includes.h"
#include "app.h"

// USER END

#define ICONVIEW_Width      70  /* 控件ICONVIEW的宽                         */  
#define ICONVIEW_Height     70  /* 控件ICONVIEW的高，包括图标的Y方向间距    */  
#define ICONVIEW_XSpace     30  /* 控件ICONVIEW的X方向间距                  */ 
#define ICONVIEW_YSpace     40  /* 控件ICONVIEW的Y方向间距                  */ 
#define ICONVIEW_XPos       10  /* 控件ICONVIEW的X方向调整距离              */
#define BOTWIN_YSpace       60  /* 屏幕下方部分窗口Y方向间距                */
#define SetIconview_yPos         40  /* 中间窗口Y方向起始位置即顶部文字可用高度  */
#define SetIconview_xPos          0  /* 中间窗口Y方向起始位置                    */



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
	{{"返回","返回","Return"},0xFF},
	{{"精度设置","精度设置","PrecSet"},FORMID_PRECISIORSET},
	{{"荷重元配置","荷重元配置","SensorConfig"},FORMID_SELSENSORCONF},
	{{"零点","零点","Zero Point"},FORMID_ZEROPOINT},
	{{"增益系数1","增益系数1","1st amplifier coe"},FORMID_AMP1},
	{{"增益系数2","增益系数2","2st amplifier coe"},FORMID_AMP2},
	{{"增益系数3","增益系数3","3st amplifier coe"},FORMID_AMP3},
	{{"增益系数4","增益系数4","4st amplifier coe"},FORMID_AMP4},
	{{"增益系数5","增益系数5","5st amplifier coe"},FORMID_AMP5},
	{{"增益系数6","增益系数6","6st amplifier coe"},FORMID_AMP6},
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


unsigned char UI_RtLoadMenuSaveSuc(WM_MESSAGE * pMsg)///////////////如果保存成功，返回上级菜单，否则抛出错误且不返回
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

unsigned char UI_RunLoadNextSaveSuc(WM_MESSAGE * pMsg)///////////////如果保存成功，进入下一级界面，否则抛出错误
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
						/* ICON控件点击消息 */
						case WM_NOTIFICATION_CLICKED:
							break;
						
						/* ICON控件释放消息 */
						case WM_NOTIFICATION_RELEASED: 							
							/* 打开相应选项 */
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
  * @brief  CreatCalLoadIconview，创建中间的窗口
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
		/* 设置初始选择的图标为 -1 (表示尚未选择)*/
		ICONVIEW_SetSel(SetIconview,-1);
		/* 设置图标在x 或y 方向上的间距。*/
		ICONVIEW_SetSpace(SetIconview, GUI_COORD_X, ICONVIEW_XSpace);
		ICONVIEW_SetSpace(SetIconview, GUI_COORD_Y, ICONVIEW_YSpace);
		/* 设置对齐方式 在5.22版本中最新加入的 */
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
