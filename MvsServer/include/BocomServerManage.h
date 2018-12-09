// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2014 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2014 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef BOCOM_SERVER_MANAGE_H
#define BOCOM_SERVER_MANAGE_H

#include "BocomServer.h"

//�˿ں�,Bocom���Ķ�ָ��,ӳ��
typedef std::map<int, CBocomServer *> BocomServerPtrMap;

/******************************************************************************/
//	����:BOCOM���Ķ�ͨѶ����ģ��
//	����:yuwx
//	����:2014-6-6
/******************************************************************************/
class CBocomServerManage
{
public:
	CBocomServerManage();
	~CBocomServerManage();

	//��ʼ��,��ʼ��������
	bool Init();
	//����ʼ��,�ͷ���Դ
	bool UnInit();

	//���BocomServer
	bool AddBocomServer(int nPort, int nId);

	//���һ������
	bool AddResult(std::string& strResult);

	//����һ������
	bool mvOnDealOneMsg();
	//�ַ����ڼ�¼
	//�ַ��¼���¼
	
	//��ȡĳ��server�豸״̬
	bool GetServerDeviceStatus();
private:
	BocomServerPtrMap m_pBocomServerMap;
};

//ͨѶ����
extern CBocomServerManage g_BocomServerManage;

#endif