#ifndef ManageClient_H
#define ManageClient_H

#include "ThreadLock.h"
#include "dspUnit.h"
#include "structdef.h"


class CDspUnit;
using namespace BASE;

class CManageClient{
public:
	CManageClient();
	~CManageClient();

	// ����һ��DSP����
	bool AddDspClient(const DspSocketFd dspSocket);

	// ɾ��һ��Dsp����
	bool MoveDspClient(const DspSocketFd dspSocket);
	

	// ��ӡ��ǰDsp������Ϣ
	int BeginRealRunInfoThread();
	static threadfunc_t STDPREFIX BeginInfoFunc(threadparam_t lpParam);
	void InfoFunc();
	bool CleanMap();

	//�Ͽ�ָ��socket����
	bool DisConnectClient(const DspSocketFd &dspSocket );

	//�ر��׽���
	bool CloseDspUnitFd(CDspUnit* lp);

	bool GetDspList(DSP_LIST &dsplist);

private:
	CDspUnit* IsExistDspClient(char* szAddress);
	void PrintDspClientInfo();

private:
	ThreadLock m_DspClientMapLock;

	map<string, CDspUnit*> m_DspClientMap;
	static int               m_exit;//�����˳���ʶ

	bool m_bPrintThStart;
};

//ȫ�ֵ���
//extern CManageClient g_ManageClients;

#endif