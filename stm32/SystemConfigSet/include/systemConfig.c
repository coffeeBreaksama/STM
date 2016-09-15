
#include "systemConfig.h"

CONFIG_DATA_S __configDataS = {
	{200,200,200},
	1,
	
	1,
	1,
	
	1,
	1,
	1,
	1,
	1
};

SENSOR_CONFIG __sensorConfig = {
	1,
	1,
	1,
	123,
	{12,43,14,25,56,17,55},
};
EM_CONFIG __emConfig = {
	{1.1,1.2,1.3},
	{1,2,3,3,4,5,6,7,8,9,10,11},
	{8}
};
void SYSTEM_Set_softAppType (unsigned char data)
{
	__configDataS.softAppType = data;
}

void SYSTEM_Set_motorType (unsigned char data)
{
	__configDataS.motorType = data;
}

void SYSTEM_Set_machineDirType (unsigned char data)
{
	__configDataS.machineDirType = data;
}

void SYSTEM_Set_dispFrom (unsigned char data)
{
	__configDataS.dispFrom = data;
}

void SYSTEM_Set_zeroStableCol (unsigned char data)
{
	__configDataS.zeroStableCol = data;
}
void SYSTEM_Set_showOpenPic (unsigned char data)
{
	__configDataS.showOpenPic = data;
}
void SYSTEM_Set_filterCol (unsigned char data)
{
	__configDataS.filterCol = data;
}

void SENSOR_Set_sensorType (unsigned char data)
{
	__sensorConfig.sensorType = data;
}

void SENSOR_Set_maxFS (unsigned char data)
{
	__sensorConfig.maxFS = data;
}

void SENSOR_Set_unitType (unsigned char data)
{
	__sensorConfig.unitType = data;
}

void SENSOR_Set_zero (unsigned char data)
{
	__sensorConfig.zero = data;
}

void SENSOR_Set_softAmplify (unsigned char data)
{
	__sensorConfig.softAmplify[0] = data;
}

void EMCONFIG_Set_encodeCoe(float data)
{	
	__emConfig.encodeCoe[0] = data;
}

void EMCONFIG_Set_speedCoe(unsigned short int data)
{	
	__emConfig.speedCoe[0] = data;
}

void EMCONFIG_Set_speedCoe2(unsigned  int data)
{	
	__emConfig.speedCoe2[0] = data;
}

