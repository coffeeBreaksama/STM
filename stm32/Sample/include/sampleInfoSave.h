#ifndef __SAMPLE_SAVE_INFO_H__
#define __SAMPLE_SAVE_INFO_H__

typedef struct{

	float square[6];
	//float duanHouMianJi;
	float fWidthLoaded[6];
	float StandartLen;
	//float duanHouBiaoJu;
	float g;//����
	unsigned int timeWillUsed;

}SAMPLE_SAVE_INFO; //�����������Ҫ���������

void SAMPLE_Set_square(float fData);
void SAMPLE_Set_fWidthLoaded(float fData);
void SAMPLE_Set_StandartLen(float fData);
void SAMPLE_Set_g(float fData);
void SAMPLE_Set_timeWillUsed(unsigned int fData);



#endif