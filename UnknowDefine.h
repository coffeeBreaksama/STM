#ifndef __UNKNOWDEFINE_H__
#define __UNKNOWDEFINE_H__
 typedef const char*	CONSTPCHAR;
 typedef const unsigned short*	CONSTUINT16;


 ////////////////定义未明 //TODO///////////////////////////////////////////////
float __loadMfs;
int _adaDataInt,_adbDataInt;
char fmtBuf1[100],fmtBuf2[100],fmtBuf3[100];
unsigned char __CardSnDes,__CardTypeDes;



#define VESION_HIGH    9
#define VESION_MID     5
#define VESION_LOW     2


typedef union{
	unsigned int b32;
	struct {
		unsigned char b4;
		unsigned char b3;
		unsigned char b2;
		unsigned char b1;
	}b8x4;
} LCD_DATA;


#define TEST_TYPE_PRESS				0
#define TEST_TYPE_O_SHOW			1		//万能显示
#define TEST_TYPE_O_CTRL			2		//万能控制
#define TEST_TYPE_O_PRE_AL2_BE2 	3		//万能宝大AL2 BE2  A通道2路力 B通道2路变形
#define TEST_TYPE_O_PRE_AL1_BL1		4		//万能控制AL1 BL1

typedef struct{
	unsigned char ctrlEn;//有控制
	unsigned char motorType;//可以使用的电机类型
	unsigned char laEn;
	unsigned char yaEn;
	unsigned char sensorUnitType;//可以使用的载荷传感器单位类型  0 力     1 压强
	unsigned char elongExist;
	unsigned char dispExist;
	unsigned char stressNeadCaculate;
	unsigned char strainNeadCaculate;
	unsigned char resultPrintFunc;
	unsigned char returnAfterTest;
}SYS_FUNC;




typedef struct {
	unsigned char mod;
	float fLoad2Disp[10];			//GP ＝ get point
	float fDisp2Load[10];			//GP ＝ get point
} AUTOGP; 

typedef struct {
	int zeroPos[2];
	long zeroWeiyi;
	int loadZYWT[7];
	int ysjZYWT[7];
	float encodeWT;
	float suduWT;
} SETTING_DATA;


typedef struct {
	float loadCUL[7];
	float ysjCUL[7];
} CALCULATE_DATA;





typedef struct{
	float li;
	float bianxing;
	float weiyi;
} SAVE_NODE;
typedef struct{
	unsigned char what2Printer;
	unsigned char printerType;
} PRINT_CONFIG;

typedef struct{
	unsigned short int midMB;//unsigned short int
	unsigned short int midCB;
	unsigned short int midCBMB;
	unsigned short int hourAllow;
	unsigned short int hourUsed;
} MID_TIME;

typedef union{
	struct dp{
		unsigned int __recCounte;
		unsigned char __recBuffer[512];
		
		unsigned int __sendBufLen;
		unsigned char __sendBuffer[512];
		
		int __framBuflen;
		unsigned char __frameSendBuffer[1024];
	} a;
	char _printerBuf[4000];
} PD_DPD;







typedef struct {
	int sensorDir;//1 or -1
	unsigned int sampleInfoMask;
} SENSOR_DIR_SMPL_INFO;

#define MOVEDIR_LEFT_RIGHT 0


		#if(AD_CTRL_CARD==1)
		/***********************厂家信息***********************/
			#define FOR_LIDE_APP
		#else 

			//#define FOR_BAODA_APP
			//#define FOR_BAODABOSS_APP

			//#define FOR_KEJIAN_APP
			//#define FOR_HAIDA_APP

			//#define FOR_BAODABOSS_APP
			//#define FOR_YUHONG_APP
			//#define FOR_GAOTAI_CUSTOMER

			
			//#define FOR_XIONGDA_USER
			//#define FOR_DINGNUO_USER
			//#define FOR_PORUISI_USER
			//#define FOR_CHANGCHENG_USER
			//#define FOR_USER_HUAHAN

			//#define FOR_USER_ZHONGYE		 //中野
		 	//#define FOR_BOLAIDE_APP			   //博莱德		
			//#define FOR_USER_HUAHAN

			//#define FOR_USER_PUSAITE		 //普赛特

			#define FOR_ELSE_CUSTOMER
		#endif
	
	
	#ifdef FOR_LIDE_APP
		#define CUSTER_NAME_USED 0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmlidehuanyaBmp
		
		#define CONTECT_NAME {"Break Software CO.,LTD","博睿科仪器有线公司","博睿科仪器有线公司"},
		#define CONTECT_TEL {"TEl:+86-571-28992855","电话:+86-571-28992855","电话:+86-571-28992855"},
		#define CONTECT_FAX {"FAX:+86-571-28992856","传真:+86-571-28992856","传真:+86-571-28992856"},
	#endif

	#ifdef FOR_BAODA_APP
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmbaodalaliBmp
		
		#define CONTECT_NAME {"Perfect Instrument CO.,LTD","宝大仪器有限公司","宝大仪器有限公司"},
		#define CONTECT_TEL {"TEl:+86-769-85818235","电话:+86-769-85818235","电话:+86-769-85818235"},
		#define CONTECT_FAX {"FAX:+86-769-85818236","传真:+86-769-85818236","传真:+86-769-85818236"},
	#endif
	#ifdef FOR_BAODABOSS_APP
		//#define CUSTER_NAME_HAVE_DEF  1
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmBaodaBossPT680
		
		#define CONTECT_NAME {"Baoda secience","Baoda secience","Baoda secience"},
		#define CONTECT_TEL {"TEl:029-88325050","电话:029-88325050","电话:029-88325050"},
		#define CONTECT_FAX {"FAX:029-88325959","传真:029-88325959","传真:029-88325959"},
	#endif

	#ifdef FOR_KEJIAN_APP
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1

		#define OPEN_MACHINE_BMP bmkejianlaliBmp
		#define CONTECT_NAME {"Kejian Instrument","东莞科建仪器","东莞科建仪器"},
		#define CONTECT_TEL {"TEl:0769-22853286","电话:0769-22853286","电话:0769-22853286"},
		#define CONTECT_FAX {"FAX:0769-22853692","传真:0769-22853692","传真:0769-22853692"},			
	#endif

	#ifdef FOR_HAIDA_APP
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1

		#define OPEN_MACHINE_BMP bmHaidaBmp
		#define CONTECT_NAME {"Haida Instrument","东莞市海达仪器","东莞市海达仪器"},
		#define CONTECT_TEL {"TEl:0769-89280808","电话:0769-89280808","电话:0769-89280808"},
		#define CONTECT_FAX {"FAX:0769-89280809","传真:0769-89280809","传真:0769-89280809"},
	#endif

	#ifdef FOR_YUHONG_APP
		#define CUSTER_NAME_USED  0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmyuHongBmp
	#endif


	#ifdef FOR_GAOTAI_CUSTOMER
	#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 0
		#define OPEN_MACHINE_BMP bmgaotai
		#define CONTECT_NAME {"Qualites Instrument","东莞高泰检测仪器","东莞高泰检测仪器"},
		#define CONTECT_TEL {"TEl:0769-85815199","电话:0769-85815199","电话:0769-85815199"},
		#define CONTECT_FAX {"FAX:0769-89032658","传真:0769-89032658","传真:0769-89032658"},
	#endif

	#ifdef FOR_DINGNUO_USER
		#define CUSTER_NAME_USED  0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmDinNuoBmp
	#endif
	
	#ifdef FOR_BOLAIDE_APP
		#define CUSTER_NAME_USED  0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmdqBmp
		#define CONTECT_NAME {"Dongguan Bolaide Instrument","东莞博莱德仪器有限公司","东莞博莱德仪器有限公司"},
		#define CONTECT_TEL {"TEl:0769-22651006","电话:0769-22651006","电话:0769-22651006"},
		#define CONTECT_FAX {"FAX:0769-89026602","传真:0769-89026602","传真:0769-89026602"},
	#endif
	
	#ifdef FOR_PORUISI_USER
		#define CUSTER_NAME_USED 1
		#define SHOW_OPEN_BMP 0
		#define OPEN_MACHINE_BMP bmlidehuanyaBmp
	#endif
	
	#ifdef FOR_CHANGCHENG_USER
		#define CUSTER_NAME_USED 0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmChangChengBmp
		#define CONTECT_NAME {"","",""},
		#define CONTECT_TEL {"TEl:","电话:","电话:"},
		#define CONTECT_FAX {"FAX:","传真:","传真:"},
	#endif

	#ifdef FOR_USER_HUAHAN
		#define CUSTER_NAME_USED 0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmHuanHanBmp
		#define CONTECT_NAME {"Hangzhou Huahan Instrument","杭州华翰造纸检测仪器设备公司","杭州华翰造纸检测仪器设备公司"},
		#define CONTECT_TEL {"TEl:+86-571-82662306","电话:+86-571-82662306","电话:+86-571-82662306"},
		#define CONTECT_FAX {"FAX:+86-571-82662253","传真:+86-571-82662253","传真:+86-571-82662253"},
	#endif	

	#ifdef FOR_HANGZHOU_HUAHAN
		#define CUSTER_NAME_USED 0
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmHuanHanBmp
		#define CONTECT_NAME {"Hangzhou Huahan Instrument","杭州华翰造纸检测仪器设备公司","杭州华翰造纸检测仪器设备公司"},
		#define CONTECT_TEL {"TEl:+86-571-82662306","电话:+86-571-82662306","电话:+86-571-82662306"},
		#define CONTECT_FAX {"FAX:+86-571-82662253","传真:+86-571-82662253","传真:+86-571-82662253"},
	#endif	


	#ifdef FOR_USER_ZHONGYE
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmZhongyeBmp
		#define CONTECT_NAME {"Zhongye Jinke Tech Co.,Ltd","东莞市中野精科仪器有限公司","东莞市中野精科仪器有限公司"},
		#define CONTECT_TEL {"Tel:+86-769-33258998","电话:+86-769-33258998","电话:+86-769-33258998"},
		#define CONTECT_FAX {"FAX:+86-769-33259991","传真:+86-769-88750565","传真:+86-769-88750565"},
	#endif

	#ifdef FOR_USER_PUSAITE
		#define CUSTER_NAME_USED  1
		#define SHOW_OPEN_BMP 1
		#define OPEN_MACHINE_BMP bmpusaite17Bmp
		#define CONTECT_NAME {"Dongguan Pu Sai Te Instrument Co.,Ltd","东莞市普赛特检测设备有限公司","东莞市普赛特检测设备有限公司"},
		#define CONTECT_TEL {"Tel:+86-769-89003369","电话:+86-769-89003369","电话:+86-769-89003369"},
		#define CONTECT_FAX {"Websize:www.precise-test.com","Websize:www.precise-test.com","Websize:www.precise-test.com"},
	#endif
	
	#ifdef FOR_ELSE_CUSTOMER
		#define CUSTER_NAME_USED  0
		#define SHOW_OPEN_BMP 0
		#define OPEN_MACHINE_BMP bmdqBmp
		#define CONTECT_NAME {"","",""},
		#define CONTECT_TEL {"","",""},
		#define CONTECT_FAX {"","",""},
	#endif
	
	#ifndef CONTECT_NAME
		#define CONTECT_NAME {"Break Software CO.,LTD","博睿科仪器有线公司","博睿科仪器有线公司"},

	#endif
	#ifndef CONTECT_TEL
		#define CONTECT_TEL {"TEl:+86-571-28992855","电话:+86-571-28992855","电话:+86-571-28992855"},

	#endif	
	#ifndef CONTECT_FAX	
		#define CONTECT_FAX {"FAX:+86-571-28992856","传真:+86-571-28992856","传真:+86-571-28992856"},	
	#endif	
#define ALL_IN_ONE_530      (4)
	#define ALL_IN_ONE_330		(5)
	#define CARD_530_2      	(6)
	#define CARD_430_3      	(7)

	#define ALL_IN_ONE_331		(8)

	#define HARDWARE_USE_TYPE		ALL_IN_ONE_530
	
	#define PC_CNCT_AD_FRZ 500

	//应用信息
	/***********************应用信息***********************/
	#define LA_LI_APP 0
	#define HUAN_YA_APP 1 
	#define BAO_PO_APP 2
	

	
	#define USER_SUPPORT_TOUCH  (0)	

#endif	//__UNKNOWDEFINE_H__

