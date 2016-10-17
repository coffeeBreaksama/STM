
#include "includes.h"
#include "app.h"

extern CONFIG_DATA_U __configDataU;
unsigned char __SaveDataSuccess = 1;
char  __strBuf[30][30];



/*typedef struct {
	char*  Name;
	unsigned char frmId;
	WM_HWIN FrmHandle;
	unsigned char Type;//Icon 0,Freamwin 1,
	unsigned int (* creatFrmFunc)(void);
}INFO_WINDOW;*/


INFO_WINDOW __WindowsInfo[] = {
	{"MainTest",FORMID_MAINTEST,NULL,1,RunFrmMainTest},
	{"UserSet",FORMID_USERSET,NULL,0,RunFrmUserSetIconView},
	{"SystemSet",FORMID_SYSTEMSET,NULL,0,RunFrmSystemSetIconView},
	{"SampleInfo",FORMID_SAMPLEINFO,NULL,1,RunFrmSampleInfo},
	{"PrintResult",FORMID_PRINTRESULT,NULL,1,RunFrmPrintResult},
	{"About",FORMID_ABOUT,NULL,0,RunFrmAboutInfo},

	{"TestType",FORMID_TESTTYPE,NULL,1,RunFrmUserSetTestType},
	{"CtrlMode",FORMID_TESTMODULE,NULL,1,RunFrmUserSetTestCtrlMode},
	{"LoadKeep",FORMID_LOADKEEP,NULL,1,RunFrmUserSetLoadKeep},
	{"ForceUnit",FORMID_FORCEUNIT,NULL,1,RunFrmUserSetForceUnit},
	{"ElongUnit",FORMID_ELONGUNIT,NULL,1,RunFrmUserSetElongUnit},
	{"StressUnit",FORMID_STRESSUNIT,NULL,1,RunFrmUserSetStressUnit},
	{"SensorSel",FORMID_SENSORSELECT,NULL,1,RunFrmUserSetSensorSel},
	{"TestStopType",FORMID_BREAKTYPE,NULL,1,RunFrmUserSetTestStopType},
	{"UserSpeed",FORMID_SPEEDSET,NULL,1,RunFrmUserSetSpeed},
	{"SoftA",FORMID_SOFTACCELE,NULL,1,RunFrmUserSetSoftA},
	{"SoftProtect",FORMID_PROTECT,NULL,1,RunFrmUserSetSoftProtect},
	{"ProLoad",FORMID_PRELOAD,NULL,1,RunFrmUserSetProLoad},
	{"AutoReturn",FORMID_AOTURETURN,NULL,1,RunFrmUserSetAutoReturn},
	{"ClampDistence",FORMID_CLAMPSET,NULL,1,RunFrmUserSetClampDistence},
	{"PrintType",FORMID_PRINTER,NULL,1,RunFrmUserSetPrintType},
	{"Language",FORMID_LANGUAGE,NULL,1,RunFrmUserSetLanguage},
	{"SetTime",FORMID_TIME,NULL,1,RunFrmUserSetTime},
	{"Discoder",FORMID_DISCODE,NULL,1,RunFrmSysDiscoder},
	
	{"MachineDir",FORMID_MACHINEDIRECT,NULL,1,RunFrmSysSetMachineDir},
	{"MotorType",FORMID_MOTORTYPE,NULL,1,RunFrmSysSetMotorType},
	{"CelSel",FORMID_SPEEDCEL,NULL,1,RunFrmSysSpeedCelSel},
	{"ControlerType",FORMID_SELCONTROLTYPE,NULL,1,RunFrmSysSetControlerType},
	{"DispFrom",FORMID_DISPFORM,NULL,1,RunFrmSysSetDispFrom},
	{"ElongOrDisp",FORMID_CALELONGDISP,NULL,1,RunFrmSysCelElongOrDisp},
	{"CalLoadIcon",FORMID_CALLOADICON,NULL,0,RunFrmSysCalLoadIconView},
	{"PrecisiorSet",FORMID_PRECISIORSET,NULL,1,RunFrmSysLoadPrecisiorSet},
	{"SensorCfg",FORMID_SELSENSORCONF,NULL,1,RunFrmSysLoadCelSensorCfg},
	{"ZeroPoint",FORMID_ZEROPOINT,NULL,1,RunFrmSysLoadCelZeroPoint},
	{"AmplifierCoe1",FORMID_AMP1,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	{"AmplifierCoe2",FORMID_AMP2,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	{"AmplifierCoe3",FORMID_AMP3,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	{"AmplifierCoe4",FORMID_AMP4,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	{"AmplifierCoe5",FORMID_AMP5,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	{"AmplifierCoe6",FORMID_AMP6,NULL,1,RunFrmSysLoadCalAmplifierCoe1},
	
	{"SysSpeedScanf",RORMID_SYSSPEEDSCANF,NULL,1,RunFrmSysSpeedScanf},
	{"AppMenu",FORMID_APPMENU,NULL,0,FrmRunAppMenu},
	{"SysPassword",FORMID_SYSPASSWORD,NULL,1,RunFrmSysPassword},
	{"GasSet",FORMID_GASSET,NULL,1,RunFrmUserSetGasSet},
	{"Keyboard",FORMID_KEYBOARD,NULL,1,NULL},//键盘函数不允许runNextForm调用


};



unsigned char UI_GetWidgetType(WM_HWIN handle)
{	
		WM_CALLBACK *pCb = WM_GetCallback(handle);
		if(*pCb == BUTTON_Callback) return 0;
		else if(*pCb == LISTBOX_Callback) return 1;
		else if(*pCb == EDIT_Callback) return 2;
		else if(*pCb == CHECKBOX_Callback) return 3;
		else if(*pCb == FRAMEWIN_Callback) return 4;
		else if(*pCb == ICONVIEW_Callback) return 5;
		else if(*pCb == TEXT_Callback) return 6;
		else return 0xff;
}

/*WIDGET_INFO __widgetInfo[0x20] = {
	NULL,

};
unsigned char UI_updataWidInfo(WM_MESSAGE *pMsg)
{
	int i,index,j = 0;
	for(i = 0; i < GUI_COUNTOF(__WindowsInfo);i ++)
	{
		if(__WindowsInfo[i].frmId == __FormIdOfRunning&&__WindowsInfo[i].FrmHandle != NULL)
		index = i;
	}	
	for (i = GUI_ID_USER; i < GUI_ID_USER + 0x20; i++)
	{
		__widgetInfo[j].handle = WM_GetDialogItem(pMsg->hWin, i);
		__widgetInfo[j].fatherFrmId = __FormIdOfRunning;
		__widgetInfo[j].type = UI_GetWidgetType(__widgetInfo[j].handle);
		//__widgetInfo[j].saveFunction = 
		__widgetInfo[j].GuiId = i;
		//TODO 未完成功能，留待以后使用的：每个窗口下的小工具句柄资源表
	}
	return 0;

}*/

unsigned char UI_GetWindowInfoIndexId(unsigned char FrmId)
{
	int i,index,j = 0;
	for(i = 0; i < GUI_COUNTOF(__WindowsInfo);i ++){
		if(__WindowsInfo[i].frmId == FrmId){
			index = i;
			return index;
		}
	}
	return 0xFF;
}
unsigned int RunNextFrom(int nextFrmId)
{
	int nextIndex = UI_GetWindowInfoIndexId(nextFrmId);
	do{
		if(nextIndex < 50){
			__FormIdOfRunning = nextFrmId;
			nextIndex = (* __WindowsInfo[nextIndex].creatFrmFunc)();
		}
	}while(nextIndex != 0xFF);
	return 0xFF;
}

void UI_MoveUpListBoxSel(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) - time;
	if(listSel < 0) listSel = numOfList;
	LISTBOX_SetSel(hList,listSel);
};

void UI_MoveDownListBoxSel(WM_HWIN hList,int time){
	
	char listSel;
	char numOfList = LISTBOX_GetNumItems(hList);
	listSel = LISTBOX_GetSel(hList) + time;
	if(listSel > numOfList - 1) listSel = 0;
	LISTBOX_SetSel(hList,listSel);
};


void UI_SetListBoxTextByLgvg(WM_HWIN hItem,GUI_ConstString *str1,GUI_ConstString *str2,GUI_ConstString *str3)
{	
	if(__configDataU.languageSel == 0) LISTBOX_SetText(hItem, str1);
	else if(__configDataU.languageSel == 1) LISTBOX_SetText(hItem, str2);
    else LISTBOX_SetText(hItem, str3); 
}

unsigned int GetNextFrom(int nextId)
{
	return 0xff;
}
unsigned int UI_GetWindowInfoIndexHandle(WM_HWIN handle){
	int i,index,j = 0;
	for(i = 0; i < GUI_COUNTOF(__WindowsInfo);i ++){
		if(__WindowsInfo[i].FrmHandle == handle){
			index = i;
			return index;
		}
	}
	return 0xFF;

}

void UI_CloseWindows(WM_HWIN handle)//关闭当前打开的设置窗口
{
	__WindowsInfo[UI_GetWindowInfoIndexHandle(handle)].FrmHandle = NULL;	
	WM_DeleteWindow(handle);
	if(keypadflag == 1){
		WM_DeleteWindow(hkeypad);
		__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_KEYBOARD)].FrmHandle = NULL;
		keypadflag = 0;
	}

}
void UI_InitSkin(void)
{
	FRAMEWIN_SKINFLEX_PROPS FRAMEWIN_pProps;
	RADIO_SKINFLEX_PROPS    RADIO_pProps;

	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
  
  /***************************定制皮肤*****************************/
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
			case 1:
				TEXT_SetDefaultFont(&GUI_Font20HZKF);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZKF);
				EDIT_SetDefaultFont(&GUI_Font20HZKF);
				LISTBOX_SetDefaultFont(&GUI_Font20HZKF);
				BUTTON_SetDefaultFont(&GUI_Font20HZKF);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZKF);
			break;
			case 0:
			default:
				TEXT_SetDefaultFont(&GUI_Font20HZK);
				FRAMEWIN_SetDefaultFont(&GUI_Font20HZK);
				EDIT_SetDefaultFont(&GUI_Font20HZK);
				LISTBOX_SetDefaultFont(&GUI_Font20HZK);
				BUTTON_SetDefaultFont(&GUI_Font20HZK);
				CHECKBOX_SetDefaultFont(&GUI_Font20HZK);
			break;
		}
}
