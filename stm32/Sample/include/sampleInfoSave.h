#ifndef __SAMPLE_SAVE_INFO_H__
#define __SAMPLE_SAVE_INFO_H__



#define SMPL_INFO_SQUARE 0x01
#define SMPL_INFO_WIDTH  0x02
#define SMPL_INFO_STD_LEN  0x04
#define SMPL_INFO_KEZHONG 0x08


typedef struct{

	float square[6];
	//float duanHouMianJi;
	float fWidthLoaded[6];
	float StandartLen;
	//float duanHouBiaoJu;
	float g;//克重
	unsigned int timeWillUsed;

}SAMPLE_SAVE_INFO; //试验结束后需要保存的数据

void SAMPLE_Set_square(float fData);
void SAMPLE_Set_fWidthLoaded(float fData);
void SAMPLE_Set_StandartLen(float fData);
void SAMPLE_Set_g(float fData);
void SAMPLE_Set_timeWillUsed(unsigned int fData);



#endif