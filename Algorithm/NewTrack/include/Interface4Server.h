//�����˵Ľӿ�
#ifndef __INTERFACE_4SERVER_H
#define __INTERFACE_4SERVER_H
	//Զ��Ԥ��λ��ͼ�Ľṹ��
	typedef struct StruSaveRemotePic
	{
	public:
		StruSaveRemotePic( );
		void mvInitVar( );

		//����Զ��Ԥ��λ��ͼ����
		void mvSetRemotePicCount(int nCount = 3);

		//����Զ��Ԥ��λ��ͼʱ����
		void mvSetRemotePicInterval(int nTimeInterval = 60);//��λΪ��

	public:
		int m_nSavePicCnt;        //ͼ�񱣴������
		int m_nSavePicInterval;   //ͼ�񱣴��ʱ����

	}CfgSaveRemotePic;


	//Զ������Ԥ��λ��ϴ�ͼ�Ľṹ��
	typedef struct StruRemoteNearCombPic
	{
	public:
		StruRemoteNearCombPic( );
		void mvInitVar( );

		//����Զ������Ԥ��λ��ϴ�ͼ����
		void mvSetRemoteNearCombPicCount(int nCount = 2);

		//����Զ������Ԥ��λ��ϴ�ͼʱ����
		void mvSetRemoteNearCombInterval(int nTimeInterval = 120);//��λΪ��

	public:
		int m_nSaveComPicCnt;        //���ͼ�񱣴������
		int m_nSaveComPicInterval;   //���ͼ�񱣴��ʱ����

	}CfgSaveRemoteNearCombPic;


	//�����˽ӿڵĽṹ��
	typedef struct StruInterface4Server
	{
	public:
		StruInterface4Server( );
		void mvInitVar( );

	public:
		StruSaveRemotePic	   m_cfgSaveRemotePic;
		StruRemoteNearCombPic  m_cfgSaveRemoteNearCombPic;
	}CfgInterface4Server;

#endif