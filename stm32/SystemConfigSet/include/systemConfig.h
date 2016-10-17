#ifndef __SystemConf_h__
#define __SystemConf_h__


#include "app.h"
typedef struct {
	unsigned char vh;
	unsigned char vm;
	unsigned char vl;
} VESION_INFO;

typedef struct {
	VESION_INFO vInfo;//�汾��
//	unsigned char controlerType;//����������

	unsigned char motorType;//�������
	unsigned char machineDirType;//�����������ͣ�������ѹ

	unsigned char dispFrom;//λ����Դ
	unsigned char zeroStableCol;//����ȶ�ϵ��
	unsigned char controlerType;//����������
	unsigned char showOpenPic;//�Ƿ���ʾ��������
	unsigned char filterCol;//�˲�ϵ��
	unsigned char scaleIndex;//

} CONFIG_DATA_S; //ϵͳ���������������

typedef struct {
	unsigned char sensorType;//����Ԫ����
	unsigned short maxFS;//�������
	unsigned char  unitType;//��λ����
	short zero;//���
	short softAmplify[7];//����Ŵ�ϵ��	
} SENSOR_CONFIG; //����������

typedef struct {
	float encodeCoe[3];//ϵ��
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