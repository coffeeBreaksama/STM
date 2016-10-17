#ifndef __SystemConf_h__
#define __SystemConf_h__


#include "app.h"
typedef struct {
	unsigned char vh;
	unsigned char vm;
	unsigned char vl;
} VESION_INFO;

typedef struct {
	VESION_INFO vInfo;//版本号
//	unsigned char controlerType;//控制器类型

	unsigned char motorType;//电机类型
	unsigned char machineDirType;//机器方向类型，上拉下压

	unsigned char dispFrom;//位移来源
	unsigned char zeroStableCol;//零点稳定系数
	unsigned char controlerType;//控制器类型
	unsigned char showOpenPic;//是否显示开机画面
	unsigned char filterCol;//滤波系数
	unsigned char scaleIndex;//

} CONFIG_DATA_S; //系统仪器本身固有数据

typedef struct {
	unsigned char sensorType;//荷重元类型
	unsigned short maxFS;//最大量程
	unsigned char  unitType;//单位类型
	short zero;//零点
	short softAmplify[7];//软件放大系数	
} SENSOR_CONFIG; //传感器参数

typedef struct {
	float encodeCoe[3];//系数
	unsigned short int speedCoe[12];//speed	
	unsigned  int speedCoe2[2];	
} EM_CONFIG;    //enoder and moto speed config

unsigned char RunSysSetNextStep(void);
unsigned char RunLoadSetNextStep(void);

void Sys_Set_controlerType (unsigned char data);
void Sys_Set_motorType (unsigned char data);
void Sys_Set_machineDirType (unsigned char data);
void Sys_Set_dispFrom (int data);
void Sys_Set_zeroStableCol (int data);
void Sys_Set_showOpenPic (unsigned char data);
void Sys_Set_filterCol (int data);
void Sys_Set_scaleIndex (unsigned char data);

void Sensor_Set_sensorType (unsigned char data);
void Sensor_Set_maxFS (int data);
void Sensor_Set_unitType (unsigned char data);
void Sensor_Set_zero (int data);
void Sensor_Set_softAmplify (int data, unsigned char index);

void Encoder_Set_encodeCoe(float data,unsigned char index);
void Encoder_Set_speedCoe(int data,unsigned char index);
void Encoder_Set_speedCoe2(int data,unsigned char index);

#endif