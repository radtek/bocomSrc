// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef _HIKVISION_H_
#define _HIKVISION_H_


#ifdef HIKVISIONCAMERA

#include"AbstractCamera.h"
//#include "PlayM4.h"
#ifdef H264_DECODE
#include "RoadDecode.h"
#endif
#include "HikvisionCommunication.h"


class CHikvision:public AbstractCamera
{
public:
	CHikvision(int nCameraType);
	~CHikvision();

	virtual bool Open();
	virtual bool Close();
	//���ļ�
	virtual bool OpenFile(const char* strFileName);

	virtual bool ReOpen();
	//��ȡ��Ƶ��
	virtual void PullStream();

	//�ֶ�����
	virtual int ManualControl(CAMERA_CONFIG cfg);
	
	//h264ͼ��ɼ�
	void CaptureFrame(char* pBuffer ,unsigned int BufferSize);

	static void fCallback(int handle,const char* data,int size,void *pUser,int iDataType);

	//h264����
	void DecodeFrame();

private:
	//��ʼ��
	void Init();

private:

#ifdef H264_DECODE
	RoadDecode m_Decoder;
#endif

	const char *m_pURL;//Ԥ�����صĲ���·��
	int m_hStream;//PlayVideo����ֵ
	
	//string m_strData;

	list<string> m_listStrData;//��������

	void* m_hAnalyze;
};
#endif
#endif
