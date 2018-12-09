
#ifndef YIHUALUCENTER_H
#define YIHUALUCENTER_H
#define TIMER_INTERAL (5*60)

#include "structdef.h"
#include "FtpCommunication.h"
#include "BocomServerManage.h"
#include "Common.h"
#include "CSeekpaiDB.h"
#include "RoadChannelCenter.h"

class CYiHuaLuCenter:public mvCSocketBase
{
public:
	CYiHuaLuCenter();
	~CYiHuaLuCenter();

	//����
	bool Init();

	//�ͷ�
	bool UnInit();

	/*���̵߳��ýӿ�*/
	void mvConnOrLinkTest();

	//��¼�����߳�
	static void *ThreadSendResult(void *pArg);

   //����һ������
	void DealStatusResult();

	//��������
	bool OnResult(std::string &strMsg);
	
	//�������Ķ�
	bool mvConnectToCS();

	//���ͼ�¼�����Ķ�
	bool mvSendRecordToCS(const std::string &strMsg);

	/*���鲢������Ϣ*/
	bool mvRebMsgAndSend(int& nSocket, const std::string &strMsg);

	int getTime();


	//��ȡͨ������
	int GetChannelCount();

	//���͹����������״̬
	int SendCameraStatusOfGJMode(std::string strCameraID,CameraState state);
private:

	int m_nSendSocket;

	//�����߳�ID
	pthread_t m_nThreadId;
    bool m_bEndThread;

	bool m_bCenterLink;
	
};
extern CYiHuaLuCenter g_YiHuaLuCenter;

#endif




