#include "bdef.h"
#include "testutil.h"
#define GUI_KEY_BACKSPACE         8         /* ASCII: BACKSPACE Crtl-H */
#define GUI_KEY_TAB               9         /* ASCII: TAB       Crtl-I */
#define GUI_KEY_ENTER             13        /* ASCII: ENTER     Crtl-M */
#define GUI_KEY_LEFT              16
#define GUI_KEY_UP                17
#define GUI_KEY_RIGHT             18
#define GUI_KEY_DOWN              19
#define GUI_KEY_HOME              23
#define GUI_KEY_END               24
#define GUI_KEY_SHIFT             25
#define GUI_KEY_CONTROL           26
#define GUI_KEY_ESCAPE            27        /* ASCII: ESCAPE    0x1b   */
#define GUI_KEY_INSERT            29
#define GUI_KEY_DELETE            30

#define GUI_KEY_F01				(0x70)
#define GUI_KEY_F02				(0x71)
#define GUI_KEY_F03				(0x72)
#define GUI_KEY_F04				(0x73)
#define GUI_KEY_F05				(0x74)
#define GUI_KEY_F06				(0x75)
#define GUI_KEY_F07				(0x76)
#define GUI_KEY_F08				(0x77)
#define GUI_KEY_F09				(0x78)
#define GUI_KEY_F10				(0x79)
#define GUI_KEY_F11				(0x7A)

const unsigned char _VkKey[9] = {
GUI_KEY_F01,
GUI_KEY_F02,
GUI_KEY_F03,
GUI_KEY_F04,
GUI_KEY_F05,
GUI_KEY_F06,	   //	06
GUI_KEY_F07,
GUI_KEY_F08,
GUI_KEY_F09		   //09
};


const float swpArray[] = {0,1.0,2.0,5.0,10,20,50,100,150,200,300,400,500};//0.1,0.2,0.5,
//速度字符串指针数组
const char * _suduArray[13] = {
							"0.0",
						   	"1.0",
							"2.0",
							"5.0",
							"10 ",
							"20 ",
							"50 ",
							"100",
							"150"
							"200",
							"300",
							"400"
							"500"
							};
const char * UsedStandard[] = {
"GB/T50081-2002",
"GB/T17671-1999",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10"
};
const char _scaleDev[]= {1,2,5,10,20,50,100};

const char * __LoadUnit[] = {
"N",       	//1
"gf",		//0.0098
"Lbf",		//4.45
"kgf",		//9.8
"kN",		//1000
NULL
};
const float __LoadUnitCol[] = {
1,
0.00981,
4.4452,
9.81,
1000,
};


const char * __ElongUnit[] = {
"mm",	//1
"cm",	//10
"in",     //25.4
NULL
};

const float __ElongUnitCol[] = {
0.001,	//1
0.01,	//10
0.0254,     //25.4
};
    const char * __SqareUnit[] = {
    "mm2",	//1
    "cm2",	//10
    "in2",     //25.4
    NULL
    };

    const float __SqareUnitCol[] = {
    0.000001,
    0.0001,
    0.00064516
    };

    const char * __stressUnit[] = {
    "Pa",
    "kPa",		//1000
    "Lbf/in2",   //6897.5
    "kgf/cm2",  //98000
    "MPa",
	"kN/m2",
    NULL
    };

    const float __stressUnitCol[] = {
    1,
    1000,		//1000
    6890.0738,   //6897.5
    98100,  //98000
    1000000,
	1000,		//1000
    };
    const char * __stressUnit2[] = {
        "N/m",//1
        "N/cm",	//100
        "N/mm",//1000
        "Lbf/in",   //175.126
        "Kgf/cm",  //980
		"kN/m",
        NULL
    };
    const float __stressUnitCol2[] = {
        1,
        100,		//1000
        1000,   //6897.5
        175.0079,  //98000
        981,
		1000
    };

	const char * __testMoveDirTypeDis[]= {
        "Pull-Up,Press-Down",//拉上，压下
        "Pull-Down,Press-Up",	//拉下，压上
        "Pull-Up,Press-Up",//拉上，压上
        "Pull-Down,Press-Down",   //拉下，压下
        "Pull-Up",  //拉上，没有压
		"Press-Up",  //980
        "Pull-Down",  //980
		"Press-Down",  //980
        NULL
    };
	const short __testMoveDirType[][2]= {
        {1,-1},//拉上，压下
        {-1,1},	//拉下，压上
        {1,1},//拉上，压上
        {-1,-1},   //拉下，压下
        {1,0},  //拉上，没有压
		{0,1},  //980
        {-1,0},  //980
		{0,-1},  //980
    };
