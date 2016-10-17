#include "includes.h"
#include "app.h"
/*
*********************************************************************************************************
*                                         �궨�� 
*********************************************************************************************************
*/ 

#define COLOR_BORDER           0xBD814F
#define COLOR_KEYPAD0          0xA8D403
#define COLOR_KEYPAD1          0xBF5C00
#define ID_BUTTON              (GUI_ID_USER + 0)

#define BUTTON_WHITH           75
#define BUTTON_HIGHT           37
#define BUTTON_SpaceX          (4+BUTTON_WHITH) 
#define BUTTON_SpaceY          (2+BUTTON_HIGHT)

/*
*********************************************************************************************************
*                                      ����
*********************************************************************************************************
*/ 
WM_HWIN hkeypad=NULL;
uint8_t keypadflag=0;//�����Ƿ���ʹ�ã�1��ʹ���У�0:��Ч��

static WM_HWIN hEdit;//Ҫ�����EDIT��
static char strBuffer[50];
static unsigned char _keyboardModule = 0;//0:�����ص㣬���š� 1�����ص㸺��      2��ֻ���ص�        3��ֻ���ظ���     4:PasswordModule  


typedef struct {
  int          xPos;
  int          yPos;
  int          xSize;
  int          ySize;
  const char * acLabel;//��ť��Ӧ��Сд�ַ� 
  WM_HWIN     hButton;
  unsigned char disFlag;//��ť�Ƿ���ʾ�ı�׼
  unsigned int   Id;
} BUTTON_DATA;

static  BUTTON_DATA _aButtonData[] = 
{

  {5, 12, 80, 60, "1",NULL,1,NULL},
  {90, 12, 80, 60, "2",NULL,1,NULL},
  {175, 12, 80, 60, "3",NULL,1,NULL},
  {5, 84, 80, 60, "4",NULL,1,NULL},
  {90, 84, 80, 60, "5",NULL,1,NULL},
  {175, 84, 80, 60, "6",NULL,1,NULL},
  {5, 156, 80, 60, "7",NULL,1,NULL},
  {90, 156, 80, 60, "8",NULL,1,NULL},
  {175, 156, 80, 60, "9",NULL,1,NULL},
  {5, 228, 80, 60, ".",NULL,1,NULL},
  {90, 228, 80, 60, "0",NULL,1,NULL},
  {175, 228, 80, 60, "-",NULL,1,NULL},
  {5, 300,125,60,"Back",NULL,1,NULL},
  {130, 300,125,60,"OK",NULL,1,NULL}
};

//���մ����ģʽ���Ĳ�ͬ�ļ�������
static void  _changeKeyboard(int module){
	switch(module){
		case 0: _aButtonData[9].disFlag = 1;
				_aButtonData[11].disFlag = 1;
				break;
		case 1:_aButtonData[9].disFlag = 0;
				_aButtonData[11].disFlag = 0;	
				break;
		case 2:_aButtonData[9].disFlag = 0;
				_aButtonData[11].disFlag = 1;
				break;
		case 3:_aButtonData[9].disFlag = 1;
				_aButtonData[11].disFlag = 0;
				break;
		case 4:_aButtonData[9].disFlag = 0;
				_aButtonData[11].disFlag = 0;;
				break;
		default: break;
	}


}
//ʶ����̱����µİ�ť�����뵽EDIT��
static void  _keyboardInput(int Id){
	int i;
	
	for(i = ID_BUTTON; i < ID_BUTTON + 12; i++){
		if(Id == i){
			if(_keyboardModule == 4)MULTIEDIT_GetText(hEdit,strBuffer,30);
			else EDIT_GetText(hEdit,strBuffer,30);
			
			if(_keyboardModule == 0) sprintf(strBuffer,"%s%s",strBuffer,_aButtonData[i - ID_BUTTON].acLabel);
			else sprintf(strBuffer,"%s%s",strBuffer,_aButtonData[i - ID_BUTTON].acLabel);
			
			if(_keyboardModule == 4)MULTIEDIT_SetText(hEdit,strBuffer);
			else EDIT_SetText(hEdit,strBuffer);
			
		}
	}
		if(Id == ID_BUTTON + 12){
			if(_keyboardModule == 4)MULTIEDIT_AddKey(hEdit,GUI_KEY_BACKSPACE);
			else EDIT_AddKey(hEdit,GUI_KEY_BACKSPACE);	
		}
		if(Id == ID_BUTTON + 13){
			WM_DeleteWindow(hkeypad);
			keypadflag = 0;
		}
}
//�������̴��ں���
static void  _creatKeyboard(WM_MESSAGE * pMsg){
	WM_HWIN    hWin = pMsg->hWin;
	WM_HWIN    hButton;
	int i;
	for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) 
			{
				if(_aButtonData[i].disFlag == 1){
					_aButtonData[i].hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize,
																_aButtonData[i].ySize, hWin, WM_CF_SHOW, 0, ID_BUTTON + i);
					_aButtonData[i].Id = ID_BUTTON + i;
					hButton = _aButtonData[i].hButton;
					BUTTON_SetFont(hButton, GUI_FONT_32B_ASCII);
					BUTTON_SetText(hButton, _aButtonData[i].acLabel);
					BUTTON_SetTextAlign(hButton,GUI_TA_HCENTER|GUI_TA_VCENTER);
					BUTTON_SetFocussable(hButton, 0);
					}
			}
	keypadflag = 1;
}
//�ص�����
static void _cbKeyPad(WM_MESSAGE * pMsg) 
{
	WM_HWIN    hWin;
	int        NCode;
	int        xSize;
	int        ySize;
	int  Id, i;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
		case WM_CREATE:
			_creatKeyboard(pMsg);
			break;
		
		case WM_DELETE:
			hkeypad = NULL;
			keypadflag = 0;
			for(i = 0; i < GUI_COUNTOF(_aButtonData);i++){
				_aButtonData[i].hButton = NULL;
				_aButtonData[i].Id = NULL;
			}
		break;
	
		case WM_PAINT:	
			xSize = WM_GetWindowSizeX(hWin);
			ySize = WM_GetWindowSizeY(hWin);
			GUI_SetColor(COLOR_BORDER);
			GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
			GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
			break;
		

		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch (NCode) 
			{
			case WM_NOTIFICATION_RELEASED:
				_keyboardInput(Id);
				break;
			}
			break;
	}
}
//�����ⲿ���õĻ�����̺���������ΪEDIT����ͼ���ģʽ
void KeyPad_Interface(uint16_t hwin,uint8_t module)
{	
	_changeKeyboard(module);
	 if(keypadflag==0)
	  {
		_keyboardModule = module;
		keypadflag=1;
		hkeypad=WM_CreateWindowAsChild(540, 35, 266, 370, HDTWIN, WM_CF_SHOW | WM_CF_STAYONTOP|WM_CF_MEMDEV, _cbKeyPad, 0);
		__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_KEYBOARD)].FrmHandle = hkeypad;
	 }else if(keypadflag==1 && hkeypad != NULL && _keyboardModule != module)
	 {	
		WM_DeleteWindow(hkeypad);
		_keyboardModule = module;
		keypadflag=1;
		hkeypad=WM_CreateWindowAsChild(540, 35, 266, 370, HDTWIN, WM_CF_SHOW | WM_CF_STAYONTOP|WM_CF_MEMDEV, _cbKeyPad, 0);
		__WindowsInfo[UI_GetWindowInfoIndexId(FORMID_KEYBOARD)].FrmHandle = hkeypad;
	 }
  		
	 
	WM_BringToTop(hkeypad);
	GUI_Delay(10);
	hEdit = hwin;
  
	WM_SetFocus(hEdit);
}
