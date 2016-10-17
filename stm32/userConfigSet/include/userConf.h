#ifndef __userConf_h__
#define __userConf_h__

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

	unsigned int gasInTime;//����ʱ��
	unsigned int gasOutTime;//����ʱ��

} CONFIG_DATA_U; //�û�������������

typedef struct {
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}DT;



void User_Set_testMethodLaOrYa (unsigned char data);
void User_Set_ctrlMode (unsigned char data);
void User_Set_fTestSpeed (float data);
void User_Set_fFastSpeed (float data);		
void User_Set_fSlowSpeed (float data);
void User_Set_fLoadKeeping (float data);
void User_Set_chiSuPrecent (int data);
void User_Set_loadKeepPrec (int data);
void User_Set_fJudgeBreakBegin(int data);
void User_Set_overLoadPre (int data);
void User_Set_loadProtect (int data);
void User_Set_dispProtect (int data);
void User_Set_whichLoadCell (unsigned char data);
void User_Set_whichElongCell (unsigned char data);
void User_Set_loadUion (unsigned char data);
void User_Set_elongUion (unsigned char data);
void User_Set_stressUion (unsigned char data);
void User_Set_languageSel (unsigned char data);
void User_Set_curveSel (unsigned char data);
void User_Set_fYujinli (float data);
void User_Set_yujinClrFlagLoad (unsigned char data);
void User_Set_yujinClrFlagDisp (unsigned char data);

void User_Set_breakJudgePrecent (int data);
void User_Set_printerType (unsigned char data);
void User_Set_speedBegin (int data);
void User_Set_aCol (int data);
void User_Set_dispFrom (unsigned char data);
void User_Set_dnLimitClampDisp (float data);
void User_Set_testClampDisp (float data);
void User_Set_fTimeProtect (int data);
void User_Set_bClosed (float data);
void User_Set_fTimeLoadKeep (int data);
void User_Set_autoReturn (unsigned char data);
void User_Set_printerIntensity(unsigned char data);

void User_Set_fTimeStop (float data);
void User_Set_fLoadStop (float data);
void User_Set_fDispStop (float data);

void SYS_Set_year(int data);
void SYS_Set_month(int data);
void SYS_Set_day(int data);
void SYS_Set_hour(int data);
void SYS_Set_minute(int data);
void SYS_Set_second(int data);

void User_Set_gasInTime (int data);
void User_Set_gasOutTime (int data);
#endif