// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef _HKCAMERA_H_
#define _HKCAMERA_H_

//#define HKCAMERA

#ifdef HKCAMERA

#include"AbstractCamera.h"
#ifdef H264_DECODE
#include "RoadDecode.h"
#endif
#include "StrmCore.h"
//#include "H264RtspRevDecode.h"

typedef struct _HK_VIDEO_HEADER
{
	unsigned short uVersion;
	unsigned short uSeq;
	unsigned int uTimeStamp;
	unsigned char chReserved[44];

}HK_VIDEO_HEADER;

class CHKCamera:public AbstractCamera
{
public:
	CHKCamera(int nCameraType);
	~CHKCamera();

	void BeginThread();

	virtual bool Open();
	virtual bool Close();
	//���ļ�
	virtual bool OpenFile(const char* strFileName);

	//�ֶ�����
	virtual int ManualControl(CAMERA_CONFIG cfg);

	//�Զ�����
	virtual int  AutoControl(unsigned int uTimeStamp,float fRate,float fIncrement,bool bDetectCarnum,int nIris,int nEn);

	//��ȡ
	virtual int ReadCameraSetting(CAMERA_CONFIG& cfg,bool bConvert = true);
	virtual bool ReOpen();
	//��ȡ��Ƶ��
	virtual void PullStream();

	//�����豸���
	virtual void SetDeviceID(int nDeviceID);

	//h264ͼ��ɼ�
	void CaptureFrame();
	//h264����
	void DecodeFrame();
	//rtcp
	void DealRtcp();

	//ֱ��ͨ��rtsp��ȡ��Ƶ
	void RecvRTSP();

private:
	//��ʼ��
	void Init();

	//�������
	bool Control(CAMERA_CONFIG cfg);

	//�����������
	void SetCaMeraPara();
	
	//����UDP����
	bool connect_udp(int nPort);
	//�ر�udp����
	void close_udp();

	//����UDP����
	bool connect_rtcp(int nPort);
	//�ر�udp����
	void close_rtcp();

	//��ȡ����˿�
	int GetRandPort();

	//�鲥��ʽ�������
	bool Connect_Multicast();
	
	
	//��ȡReceive report and source Description
	string GetRRSD(int nType = 0);

	//��ȡSSRC
	unsigned int GetRandSSRC();

	void SetPlace(std::string strPlace);

private:

#ifdef H264_DECODE
	RoadDecode m_Decoder;
#endif

	//H264RtspRevDecode m_H264RtspRev;

	//������
	int m_nDeviceId;
	
	struct sockaddr_in m_s_addr;
	int m_udp_fd;

	//h264֡�б�
	list<string> m_listImage;

	//��ȡ����
	pthread_mutex_t m_ImageMutex;
	 //�߳�ID
	 pthread_t m_nImageThreadId;
	
	 struct sockaddr_in m_rtcp_addr;
	 int m_rtcp_fd;
	  //�߳�ID
	 pthread_t m_nRtcpThreadId;

	 unsigned int m_uRandSSrc;

	 unsigned int m_uSendSSrc;

	 unsigned short m_uSendSeq;

	unsigned int m_uLatSRT;

	bool m_bRtspMode;
	//�Ƿ��鲥��ʽ
	bool m_bMulticast;

	CStrmParser m_StreamParser; //������֡��

	string m_strPlace;
};
#endif
#endif
