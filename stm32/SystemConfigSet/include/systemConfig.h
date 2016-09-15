#ifndef __SystemConf_h__
#define __SystemConf_h__

typedef struct {
	unsigned char vh;
	unsigned char vm;
	unsigned char vl;
} VESION_INFO;

typedef struct {
	VESION_INFO vInfo;//�汾��
	unsigned char softAppType;//����������

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
	float encodeCoe[3];//xishu
	unsigned short int speedCoe[12];//speed	
	unsigned  int speedCoe2[2];	
} EM_CONFIG;    //enoder and moto speed config



void SYSTEM_Set_softAppType (unsigned char data);
void SYSTEM_Set_motorType (unsigned char data);
void SYSTEM_Set_machineDirType (unsigned char data);
void SYSTEM_Set_dispFrom (unsigned char data);
void SYSTEM_Set_zeroStableCol (unsigned char data);
void SYSTEM_Set_showOpenPic (unsigned char data);
void SYSTEM_Set_filterCol (unsigned char data);


void SENSOR_Set_sensorType (unsigned char data);
void SENSOR_Set_maxFS (unsigned short data);
void SENSOR_Set_unitType (unsigned char data);
void SENSOR_Set_zero (short data);
void SENSOR_Set_softAmplify (unsigned char data);

void EMCONFIG_Set_encodeCoe(float data);
void EMCONFIG_Set_speedCoe(float data);
void EMCONFIG_Set_speedCoe2(unsigned  int data);

#endif