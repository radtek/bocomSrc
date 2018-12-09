//���⿪�ŵĲ���
#ifndef __OPEN_CONFIG_PARAMETER_H
#define __OPEN_CONFIG_PARAMETER_H
	
#include "libHeader.h"

//�¼�ͳ�ƺͱ������ò������Ķ���
#define MAX_CFG_PARA_FILE_CNT 30  //���Ĳ��������ļ���
enum DET_CFG_PARM_ENUM  //��Ҫ����MAX_CFG_PARA_FILE_CNT
{
	QUEUE_LEN_STAT_PC = 0,   //���г���ͳ��
	JAM_ALERT_PC,			 //����ӵ�±���
	ACCIDENT_STOP_ALERT_PC,   //�¹�ͣ������
	VEHICLE_STOP_ALERT_PC,    //ͣ������
	AGAINST_MOVE_ALERT_PC,    //���б���
	FAST_MOVE_ALERT_PC,		  //���ٱ���
	CHANGE_ALERT_PC,		  //�������
	CROSS_MOVE_ALERT_PC,	  //�ᴩ����
	SAMEPOINT_MAX_OFFSET_PC   //ͬһ������ƫ����
};

#define MAX_DET_PARA_CNT 10  //������õļ�������Ŀ


//---------part1----------//
typedef struct StruDetectParameterCfg
{
public:
	StruDetectParameterCfg( );

	bool mvInitDetectParaCfg(
			int nChannelIdx,    //ͨ�������
			int nPresetIdx,     //Ԥ��λ�����
			char *cTxtFileName  //�ļ�������
		);

	float* mvGetCfgPara( int &nParaCnt );

private:
	bool m_bInit;         //�Ƿ��ʼ��
	bool m_bReadSucc;     //�Ƿ������

	char m_cFileName[104];  //��д���ļ�����

	int m_nChannelIdx;      //ͨ�������
	int m_nPresetIdx;       //Ԥ��λ�����

	int   m_nCfgDataCnt;				  //����������ݵ��ܸ���
	float m_fACfgData[MAX_DET_PARA_CNT];  //������õľ�������

private:
	void mvInitCfgParaVar( );


	//��������д���ļ�
	bool mvWriteCfgParaToFile( );

	//���ļ��ж��������
	bool mvReadCfgParaFromFile( );  

}AnDetectParameterCfg;


//---------part2----------//

//���г���
struct StructQueueLenStaCfgPara
{
public:
	bool m_bMontionConstrain4QL;  //�Ƿ��˶�Լ��,Ĭ��false

	StructQueueLenStaCfgPara( );
	void mvInitVar( );
};

//ӵ�¼��
struct StructJamAlertCfgPara
{
public:
	bool m_bMontionConstrain4Jam;  //�Ƿ��˶�Լ��,Ĭ��false

	StructJamAlertCfgPara( );
	void mvInitVar( );
};

//�¹�ͣ�����
struct StructAccidentStopAlertCfgPara
{
public:
	bool m_bDetAccidentStop;  //�Ƿ���Լ���¹�ͣ��
	
	StructAccidentStopAlertCfgPara( );
	void mvInitVar( );
};

//ͣ�����
struct StructVehicleStopAlertCfgPara
{
public:
	bool m_bStrictObjType;   //�Ƿ����Ŀ��������ϸ�Ҫ��,Ĭ��true
	bool m_bConfirmObjExist; //�Ƿ���Դ���Ŀ�����ȷ��,Ĭ��false

	StructVehicleStopAlertCfgPara( );
	void mvInitVar( );
};

//���м��
struct StructAgainstMoveCfgPara
{
public:
	bool m_bDetectSmallObject;   //�Ƿ����СĿ��������,Ĭ��true
	bool m_bJugeObjIsLight;		 //�Ƿ��ж�Ŀ��Ϊ�ƹ�,Ĭ��Ϊfalse

	StructAgainstMoveCfgPara( );
	void mvInitVar( );
};

//���ټ��
struct StructFastMoveCfgPara
{
public:
	bool m_bJugeFastObjIsLight;		 //�Ƿ��ж�Ŀ��Ϊ�ƹ�,Ĭ��Ϊfalse

	StructFastMoveCfgPara( );
	void mvInitVar( );
};

//������
struct StructChangeCfgPara
{
public:
	bool m_bUseEasyMode;		 //�Ƿ�ʹ�ÿ���ģʽ���,Ĭ��Ϊtrue
	bool m_bDetectInBottom;      //�Ƿ��ͼ��������б����⣬Ĭ��Ϊtrue
	StructChangeCfgPara( );
	void mvInitVar( );
};

//�ᴩ���
struct StructCrossMoveCfgPara
{
public:
	bool m_bUseWorldDist;		 //�Ƿ�ʹ����������Լ�����,Ĭ��Ϊtrue

	StructCrossMoveCfgPara( );
	void mvInitVar( );
};

//ͬһ���ƫ��
struct StructSamePtOffsetCfgPara
{
public:
	float m_fOffRateWidth;	   //��ȷ�������ƫ�Ʊ���,Ĭ��Ϊ0.002
	float m_fOffRateHeight;    //�߶ȷ�������ƫ�Ʊ���,Ĭ��Ϊ0.002

	StructSamePtOffsetCfgPara( );
	void mvInitVar( );
};

//���ڴ˼�����������ĸ������ͳ�Ƶ����ò�������
//----add here----


//����ͳ�Ʋ���������
struct StructDetStaParaConfiger
{
public:
	StructQueueLenStaCfgPara		m_QueueLenStaCfgPara;
	StructJamAlertCfgPara			m_JamAlertCfgPara;
	StructAccidentStopAlertCfgPara  m_AccidentStopAlertCfgPara;
	StructVehicleStopAlertCfgPara   m_VehiclStopAlertCfgPara;
	StructAgainstMoveCfgPara		m_AgainstMoveCfgPara;
	StructFastMoveCfgPara			m_FastMoveCfgPara;
	StructChangeCfgPara				m_ChangeCfgPara;
	StructCrossMoveCfgPara			m_CrossMoveCfgPara;
	StructSamePtOffsetCfgPara       m_SamePtOffsetCfgPara;

	StructDetStaParaConfiger( );
	void mvSetDefaultValue( );

	bool mvCvtData2Cfg( const DET_CFG_PARM_ENUM nEnumMod,
						int nParaCnt, float *fData );
};

//---------part3----------//
typedef struct StructEventDetStatCfgParaReader
{
public:
	StructEventDetStatCfgParaReader( );
	bool mvReadAllFiles( int nChannelIdx, int nPresetIdx );
	void mvResetToInitVar( );

	StructDetStaParaConfiger m_DetStaParaConfiger;	//����ͳ�Ʋ���������

private:
	void mvInitVar( );
	bool mvReadOneFile( const DET_CFG_PARM_ENUM nEnumMod );

	//����������ݽ���ת��
	bool mvConvertData( );

private:
	bool m_bInit;

	int m_nChannelIdx;      //ͨ�������
	int m_nPresetIdx;       //Ԥ��λ�����

	//����ͬ����ļ�����������
	StruDetectParameterCfg  m_DetCfgParaA[MAX_CFG_PARA_FILE_CNT];  
	char  m_cDetCfgParaFileName[MAX_CFG_PARA_FILE_CNT][40];  

}AnEventDSCfgParaReader;



//--------------------------------

#endif