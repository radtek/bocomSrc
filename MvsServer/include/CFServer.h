// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef _CFSERVER_H_
#define _CFSERVER_H_


#ifdef CFCAMERA


class CCFCommunication
{
public:
	CCFCommunication();
	~CCFCommunication();

	bool Init();
	bool UnInit();
	
	void LoginCFServer();

	unsigned int GetLoginId() {return m_loginID;}

private:

	unsigned int m_loginID;
};
extern CCFCommunication g_CFCommunication;
#endif
#endif
