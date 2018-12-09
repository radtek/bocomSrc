#ifndef MATCH_PLATE_H
#define MATCH_PLATE_H

#include "structdef.h"
#include "CommonHeader.h"
#include "Thread.h"
#include "DspDataProcess.h"

class CDspDataProcess;
class CMatchPlate
{
public:
	CMatchPlate();
	~CMatchPlate();

public:
	// ��������߳�
	int InitMatchPlate();
	static threadfunc_t STDPREFIX BeginCheckPlate(threadparam_t lpParam);
	void CheckPlate();

	// ����ǰ�ż������list
	void PushFrontPlate(int nChannel, RECORD_PLATE_DSP_MATCH data);
	// ������ż�����������List
	void PushBackPlate(RECORD_PLATE_DSP_MATCH data);

private:
	void DealPlate(RECORD_PLATE_DSP_MATCH record_plate);
	// ����ֵ��-1:û���ҵ���0:�ҵ���1���ҵ������г���
	int SearchFrontPlate1(RECORD_PLATE_DSP_MATCH record_plate, RECORD_PLATE_DSP_MATCH& foundRecord);
	// ����ֵ��-1:û���ҵ���0:�ҵ���1���ҵ������г���
	int SearchFrontPlate2(RECORD_PLATE_DSP_MATCH record_plate, RECORD_PLATE_DSP_MATCH& foundRecord);	
	void OutPutPlate(RECORD_PLATE_DSP_MATCH record_plate, RECORD_PLATE_DSP_MATCH foundRecord);
	void SendResult(RECORD_PLATE& plate,unsigned int uSeq);

	//����15sǰ�ĳ��Ƽ�¼ɾ��
	bool IsLastPlate(UINT32 uPlateTime);

private:
	static int               m_exit;//�����˳���ʶ

	std::list<RECORD_PLATE_DSP_MATCH> m_FrontPlateList1; //����1,ǰ�ż����
	std::list<RECORD_PLATE_DSP_MATCH> m_FrontPlateList2; //����2,ǰ�ż����

	std::list<RECORD_PLATE_DSP_MATCH> m_BackPlateList;	// ���ż����

	pthread_mutex_t m_FrontPlate1_Mutex;
	pthread_mutex_t m_FrontPlate2_Mutex;
	pthread_mutex_t m_BackPlate_Mutex;

	CDspDataProcess* m_pDataProc200W;
	CDspDataProcess* m_pDataProc500W;
};

extern CMatchPlate g_matchPlate;

#endif
