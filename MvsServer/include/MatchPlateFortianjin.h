#ifndef FB_MATCH_PLATE_H
#define FB_MATCH_PLATE_H
//#ifdef FBMATCHPLATE

#include "structdef.h"
#include "CommonHeader.h"
#include "Thread.h"
#include "DspDataProcess.h"

//#ifdef MATCH_LIU_YANG
	#include "MvFBMatch2.h"
//#else
//	#include "MvFBMatch.h"
//#endif


//ƥ�������
typedef struct __MatchPlate
{
	RECORD_PLATE_DSP_MATCH A;
	RECORD_PLATE_DSP_MATCH B;
}MatchPlate;

class CMatchPlateFortianjin
{
public:
	CMatchPlateFortianjin();
	~CMatchPlateFortianjin();

public:
	int InitMatchPlate();

	// ����ȡ�öԱȳ��Ƽ���߳�
	int CheckMatchPlate();
	static threadfunc_t STDPREFIX BeginCheckPlate(threadparam_t lpParam);
	void CheckPlate();

	// ��������Աȳ��Ƽ���߳�
	int DealMatchPlate();
	static threadfunc_t STDPREFIX BeginDealPlate(threadparam_t lpParam);
	void DealPlate();

	//
	static void* DoDealPlate(void* lpParam);
	static void* DoDealNoMatchPlate(void* lpParam);
	// ���뿨�����ݸ��Աȴ���
	void mvInput(RECORD_PLATE_DSP_MATCH &plate);

	//����¼����ָ��
	void SetTempRecord(CRoadRecordTemp &recordTemp) { m_pRecordTemp = &recordTemp; }

	//���Υ��ǰ����ƥ��¼��,����¼��·��
	std::string DealOutPutMachVideo(RECORD_PLATE &plateA, RECORD_PLATE &plateB);

	//����ǰ���Ʋ�ƥ���¼�
	void SetMatchEvent(const std::string &strVideoPath, const RECORD_PLATE &plate, const bool &bVideoFlag, std::string &strEvent);

	//��ȡ¼��·��
	std::string GetVideoSavePath(RECORD_PLATE& plate);

	//
	bool PopMatchData(MatchPlate & sMatchPlate);
private:
	void DoDealPlateFunc(RECORD_PLATE_DSP_MATCH &A, RECORD_PLATE_DSP_MATCH &B);
	void DoDealNoMatchPlateFunc(RECORD_PLATE_DSP_MATCH &plate);
private:
	static int               m_exit;//�����˳���ʶ
	vector<MatchPlate> m_vcMatchList;
	pthread_mutex_t m_MatchList_Mutex;

	CDspDataProcess* m_pDataProc200W[4];
	CDspDataProcess* m_pDataProc500W[4];

//#ifdef MATCH_LIU_YANG
//	MvFBMatch2* m_mvMatch2;
//#else
//	MvFBMatch* m_mvMatch;
//#endif

	CRoadRecordTemp* m_pRecordTemp;
};

extern CMatchPlateFortianjin g_matchPlateFortianjin;
//#endif //FBMATCHPLATE
#endif //FB_MATCH_PLATE_H
