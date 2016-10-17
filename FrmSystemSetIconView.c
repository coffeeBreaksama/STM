#include "includes.h"
#include "app.h"

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

static WIN_PARA _WinParaOfSystemConfig;			

static STRING_2_FORM  prStringArrayAndFormId[] ={
	{{"返回","返回","Return"},0xFF},
	{{"机器方向","机器方向","Machine Direct"},FORMID_MACHINEDIRECT},
	{{"电机类型","电机类型","Motor Yype"},FORMID_MOTORTYPE},
	{{"速度","速度","speedCel"},FORMID_SPEEDCEL},
	{{"控制器","控制器","SelectControlType"},FORMID_SELCONTROLTYPE},
	{{"打印参数","打印参数","Print Argu"},FORMID_PRINTRESULT},
	{{"位移来源","位移来源","Disp Form"},FORMID_DISPFORM},
	{{"位移","位移","CalElongDisp"},FORMID_CALELONGDISP},
	{{"力量（菜单）","力量（菜单）","CalLoad Iconview"},FORMID_CALLOADICON},
	{{NULL,NULL,NULL},0xFF },
} ;

//如果保存成功，返回上级菜单，否则抛出错误且不返回
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


static unsigned int __curFrmIconIndex = 0xFF; //点击Iconview以后的icon索引
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
//如果保存成功，运行下一步窗口，否则抛出错误且不运行
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
							/* 打开相应选项 */
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
