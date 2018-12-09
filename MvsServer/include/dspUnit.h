#ifndef DSP_UNIT_H
#define DSP_UNIT_H
#include "SendThreadPool.h"
#include "DspClient.h"
#include "DspDealData.h"

typedef enum _EnumDspType
{
	tpTcpServer = 1,
	tpTcpClient,
	tpDealData
}EnumDspType;


class CSendThreadPool;
class CDspClient;


class CDspUnit{
public:
	CDspUnit();
	virtual ~CDspUnit();

	// ��ʼ��Dsp�����ȡdata
	int StartGetDataFromDsp(DspSocketFd dspSocket, EnumDspType emType = tpTcpClient);

	// ����һ��Dsp���ݴ���
	bool AddDspDealData();

public:
	static CSendThreadPool*  m_gpThreadPool;

	CDspClient* m_pDspClient;

private:
	
	list<CDspDealData*>* m_pDspDealList;		//һ��Dsp��Ӧ�Ĵ���
};
#endif
