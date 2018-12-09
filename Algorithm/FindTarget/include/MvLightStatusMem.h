#ifndef MV_LIGHT_STATUS_H
#define MV_LIGHT_STATUS_H

#include <list>
#include <map>
#include "MvChannelSignalHistory.h"

//using namespace std;

/*
 ��סÿһ֡��ÿ��ͨ����ǰ���������ҵĺ���źŵ�һ���ࡣ
*/
class MvLightStatusMem
{
public:

	// lstChannelsIndex�洢��ϵͳ������ͨ���������š�
	MvLightStatusMem(int nMemFrames, const std::list<int> &lstChannelsIndex);

	// ��������
	~MvLightStatusMem();

	// ��ȡĳ֡ĳͨ���ĺ��״̬
	bool GetLightStatus(unsigned int uFrameSeq, int nChannelIndex, MvChannelFrameSignalStatus &ret);

	// ����ĳ֡��ͨ���ĺ��״̬��
	void AddLightStatus(const std::list<MvChannelFrameSignalStatus> &ls);

	// ����cfss������Ϣ��ǵĳ���c��֡��f������d������f֡��c����d����Ϊ��ƣ��ҳ��ú��һ�������֡�š�
	bool FindFirstRedLightFrameSeq(const MvChannelFrameSignalStatus &cfss, unsigned int &uRet);

	bool FindFirstRedLightFrameSeq(int nRoadIndex, unsigned int uFrameSeq, int nDir, unsigned int &uRet);

private:

	// ͨ������źż����֡����
	// �������֡���ͻᱻɾ����
	int m_nMemFrames;


	// ͨ�����->ͨ������״̬��Ϣ��¼��ӳ���
 	std::map<int, MvChannelSignalHistory*> mapChnIndex2ChnHistory;

};


#endif
