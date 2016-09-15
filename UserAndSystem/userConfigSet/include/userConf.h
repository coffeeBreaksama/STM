#ifndef __userConf_h__
#define __userConf_h__
//0:�����ص㣬���š� 1�����ص㸺�� char     2��ֻ���ص�        3��ֻ���ظ��� float 
typedef struct {
	unsigned char testMethodLaOrYa;
	unsigned char ctrlMethod;
	float fTestSpeed;//�����ٶ�
	float fFastSpeed;//�����ٶ�
	float fSlowSpeed;//�����ٶ�
	
	float fLoadKeeping;//��������
	unsigned char chiSuPrecent;  //����ϵ��
	unsigned char loadKeepPrec;	//�������־���
	unsigned int fTimeLoadKeep;//��������ʱ�䣬sΪ��λ
	
	unsigned short fJudgeBreakBegin[6];//�����ƻ���ʼ�ٷֱ�
	unsigned char breakJudgePrecent[6];//�����ƻ��ٷֱ�
	float fLoadStop;//ָ��ͣ����ʽ
	float fDispStop;
	float fTimeStop;


	unsigned char overLoadPre;//���ذٷֱ�

	int loadProtect;
	int dispProtect;//λ�Ʊ���
	char fTimeProtect;//ʱ�䱣��

	unsigned char whichLoadCell;//ѡ���ĸ����������� ����Ԫ
	unsigned char whichElongCell;
	
	unsigned char loadUion;//��λ
	unsigned char elongUion;
	unsigned char stressUion;
	unsigned char languageSel;
	
	unsigned char curveSel; //ѡ������
	float fYujinli;	//Ԥ����
	unsigned char yujinClrFlagLoad; //Ԥ�������־
	unsigned char yujinClrFlagDisp;
	unsigned char autoReturn;//�Զ�����
	unsigned char printerType;//��ӡ������
	unsigned char printerIntensity;//��ӡǿ��
	
	unsigned short speedBegin;//����ٿ�ʼ
	unsigned char aCol;//���ٶ�ϵ��
	unsigned char dispFrom;//λ����Դ
	float dnLimitClampDisp;//����λ�о�֮��ľ���
	float testClampDisp;//����λ�о�֮��ľ���


} CONFIG_DATA_U; //�û�������������

typedef struct {
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} DT;

void USER_Set_testMethodLaOrYa (unsigned char data);
void USER_Set_ctrlMethod (unsigned char data);
void USER_Set_fTestSpeed (float data);
void USER_Set_fFastSpeed (float data);		
void USER_Set_fSlowSpeed (float data);
void USER_Set_fLoadKeeping (float data);
void USER_Set_chiSuPrecent (unsigned char data);
void USER_Set_loadKeepPrec (unsigned char data);
void USER_Set_fJudgeBreakBegin(unsigned char data);
void USER_Set_overLoadPre (unsigned char data);
void USER_Set_loadProtect (int data);
void USER_Set_dispProtect (int data);
void USER_Set_whichLoadCell (unsigned char data);
void USER_Set_whichElongCell (unsigned char data);
void USER_Set_loadUion (unsigned char data);
void USER_Set_elongUion (unsigned char data);
void USER_Set_stressUion (unsigned char data);
void USER_Set_languageSel (unsigned char data);
void USER_Set_curveSel (unsigned char data);
void USER_Set_fYujinli (float data);
void USER_Set_yujinClrFlagLoad (unsigned char data);
void USER_Set_yujinClrFlagDisp (unsigned char data);

void USER_Set_breakJudgePrecent (unsigned char data);
void USER_Set_printerType (unsigned char data);
void USER_Set_speedBegin (unsigned char data);
void USER_Set_aCol (unsigned char data);
void USER_Set_dispFrom (unsigned char data);
void USER_Set_dnLimitClampDisp (float data);
void USER_Set_testClampDisp (float data);
void USER_Set_fTimeProtect (char data);
void USER_Set_m_fLoadSpeed (char data);
void USER_Set_bClosed (float data);
void USER_Set_fTimeLoadKeep (unsigned int data);
void USER_Set_autoReturn (unsigned char data);
void USER_Set_printerIntensity(unsigned char data);

void USER_Set_fTimeStop (float data);
void USER_Set_fLoadStop (float data);
void USER_Set_fDispStop (float data);

void SYS_Set_year(unsigned short data);
void SYS_Set_month(unsigned char data);
void SYS_Set_day(unsigned char data);
void SYS_Set_hour(unsigned char data);
void SYS_Set_minute(unsigned char data);
void SYS_Set_second(unsigned char data);
#endif