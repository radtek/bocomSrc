#ifndef _HIKVISIONCOMMUNICATION_H_
#define _HIKVISIONCOMMUNICATION_H_

#include "Common.h"
#ifdef HIKVISIONCAMERA

#include "platform.h"
//using namespace Platform;

class CHikvisionCommunication
{
public:
	CHikvisionCommunication();
	~CHikvisionCommunication();

	bool Init();
	bool UnInit();

	bool UserLogOnServer();

	void LoginHikServer();
	
	int GetLoginHandle()
	{
		return m_Userhandle;
	};
	int GetInit()
	{
		return m_nInit;
	}

private:

	int m_Userhandle;//��½���صľ��
	int m_nInit;//��ʼ������ֵ
	bool m_bLogOnServer;

	//�߳�ID
	pthread_t m_nThreadId;
};

extern CHikvisionCommunication g_HikvisionCommunication;

#endif
#endif