#ifndef MV_CHANNEL_SIGNAL_HISTORY_H
#define MV_CHANNEL_SIGNAL_HISTORY_H


#include "MvChannelFrameSignalStatus.h"

/*
 ��¼һ��������֡���״̬���ࡣ
*/
class MvChannelSignalHistory
{
public:

	// ���캯����nKeepFrames��������źż����֡����
	MvChannelSignalHistory(int nKeepFrames = 2500);

	// ��������
	~MvChannelSignalHistory();

	// ��ȡuFrameSeq֡�����ĺ��״̬��
	bool GetFrameSignalStatus(unsigned int uFrameSeq, MvChannelFrameSignalStatus &ret);

	// ��¼��һ֡���״̬��
	void AddFrameSignalStatus(const MvChannelFrameSignalStatus &css);

private:
	MvChannelFrameSignalStatus *buffer;
	unsigned int m_uKeepFrames;

};



#endif
