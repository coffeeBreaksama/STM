
#include "systemConfig.h"
#include "userConf.h"
#include <stdint.h>
#include "app.h"

extern CONFIG_DATA_U __configDataU;
extern CONFIG_DATA_S __configDataS;

CONFIG_DATA_S __configDataS = {
	{200,300,400},
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
void Sys_Set_controlerType (unsigned char data)
{
	if(0 <= data && data <= 3){
		switch(data){
			case 0:
				__configDataU.testMethodLaOrYa = 0;
				__configDataS.machineDirType = 0;
			break;
		
			case 1:
				__configDataU.testMethodLaOrYa = 0;
				__configDataS.machineDirType = 1;
				__configDataS.motorType = 3;
			break;

			case 2:
				__configDataU.testMethodLaOrYa = 0;
				__configDataS.machineDirType = 1;
				__configDataS.motorType = 3;
				__configDataU.chiSuPrecent = 3;   //TODO
				__configDataU.loadKeepPrec = 1;   //耐破模式下用不到这些了，应该改成气缸时序的？！
				__configDataU.fTimeProtect = 9;
			break;

			case 3:
				__configDataU.testMethodLaOrYa = 0;
				__configDataS.machineDirType = 0;
			break;	
		}
		__configDataS.controlerType = data;
	}
	else __SaveDataSuccess = 0;		
}

void Sys_Set_motorType (unsigned char data)
{
	if(data >= 0  && data <= 3)
	__configDataS.motorType = data;
	else __SaveDataSuccess = 0;		
}

void Sys_Set_machineDirType (unsigned char data)
{
	if(0 <= data && data <= 3)
	__configDataS.filterCol = data;
	else __SaveDataSuccess = 0;		__configDataS.machineDirType = data;
}

void Sys_Set_dispFrom (int data)
{
	if(0 <= data && data <= 1)
	__configDataS.dispFrom = data;
	else __SaveDataSuccess = 0;	
}

void Sys_Set_zeroStableCol (int data)
{
	if(0 <= data&&data <= 100){
		__configDataS.zeroStableCol = data;
	}
	else {
		__SaveDataSuccess = 0;
	}	
}
void Sys_Set_showOpenPic (unsigned char data)
{
	if(0 <= data && data <= 1)
	__configDataS.showOpenPic = data;
	else __SaveDataSuccess = 0;		
}
void Sys_Set_filterCol (int data)
{
	if(1 <= data && data <= 5)
	__configDataS.filterCol = data;
	else __SaveDataSuccess = 0;	
}

void Sys_Set_scaleIndex (unsigned char data)
{
	if(0 <= data && data <= 5)
	__configDataS.scaleIndex = data;
	else __SaveDataSuccess = 0;		
}

void Sensor_Set_sensorType (unsigned char data)
{
	//if(0 <= data && data <= 4)
	__sensorConfig.sensorType = data;
	//else __SaveDataSuccess = 0;		
}

void Sensor_Set_maxFS (int data)
{
	if(1 <= data && data <= 10000)
	__sensorConfig.maxFS = data;
	else __SaveDataSuccess = 0;		
}

void Sensor_Set_unitType (unsigned char data)
{
	if(0 <= data && data <= 4)
	__sensorConfig.unitType = data;
	else __SaveDataSuccess = 0;		
}

void Sensor_Set_zero (int data)
{
	//TODO 定义问题
	if(-90000 <= data&&data <= 90000){
		__sensorConfig.zero = data;
	}
	else {
		__SaveDataSuccess = 0;
	}
}

void Sensor_Set_softAmplify (int data, unsigned char index)
{
	if(index == 0){
		if(2000 <= data&&data <= 10000){
			__sensorConfig.softAmplify[index] = data;
		}
		else {
			__SaveDataSuccess = 0;
		}
	}else{
		if(-1000 <= data&&data <= 1000){
			__sensorConfig.softAmplify[index] = data;
		}
		else {
			__SaveDataSuccess = 0;
		}
	}
}

void Encoder_Set_encodeCoe(float data, unsigned char index)
{	
	if((__configDataS.motorType == 0||__configDataS.motorType == 3)&&(0 <= data&&data <= 100)){
		__emConfig.encodeCoe[index] = data;}
		else __SaveDataSuccess = 0;
		
}

void Encoder_Set_speedCoe(int data, unsigned char index)
{	
	
	if( (__configDataS.motorType == 0||__configDataS.motorType == 3)&&(0 <= data&&data <= 400)) { 
			__emConfig.speedCoe[index] = data;}
		else { 
			__SaveDataSuccess = 0;
		}
	
}

void Encoder_Set_speedCoe2(int data,unsigned char index)
{	
	if(0 <= data && data <= 100)
	__emConfig.speedCoe2[index] = data;
	else __SaveDataSuccess = 0;	
}

