// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2014 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2014 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#ifndef _ROADTEMP_CAPTURE_H
#define _ROADTEMP_CAPTURE_H

/**
    �ļ���RoadTempCapture.h
    ���ܣ�����¼����
	˵��: 1���ӻ���һ���ļ�,ѭ��ʹ��,¼��·��,��ʽ:.//video/temp/00-01~59.mp4 [Hour-ChannelID]
    ���ߣ�yuwenxian
    ʱ�䣺2014-2-25
**/

#include "global.h"

#define MAX_TEMP_VIDEO_SIZE 40 //��󻺴�����

class CRoadTempCapture
{
public:
	CRoadTempCapture();
	~CRoadTempCapture();

public:
	//��ʼ��
	void Init(int nChannelId, int nWidth, int nHeight);
	//����ʼ��
	void Unit();

	//����¼���߳�
	bool StartThread();
	//�˳��߳�
	void CloseThread();

	//¼����ѭ��
	void RunRecorder();
	//����1֡¼��
	void CaptureVideo();

	//���1֡����
	void AddFrame(unsigned char * pBuffer, Image_header_dsp &header);
	//����1֡����
	int PopFrame(unsigned char ** ppBuffer);

	//����֡�����֡��������
	void DecreaseSize();
	//��ȡ¼���ļ�·��
	std::string GetEncodeFileName(){return m_strH264FileName;}

private:
	
	pthread_mutex_t m_video_Mutex;//�źŻ���	
	pthread_t m_nThreadId;//�߳�ID
	
	int m_nChannelId;//ͨ�����	
	bool m_bEndCapture;//����¼��	
	int64_t m_uBeginTime;//��ʼʱ��	
	int64_t m_uEndTime;//����ʱ��
	
	unsigned char *m_FrameList[MAX_TEMP_VIDEO_SIZE];//����������	
	unsigned char *m_pFrameBuffer;//֡���ջ�����
	int m_nCurIndex;   //�ɴ���ڴ�����
	int m_nFirstIndex;//��ȡ���ڴ�����
	int m_nFrameSize ;//�Ѿ��洢���ڴ�����
	
	int m_uWidth;//¼���
	int m_uHeight;//¼���
	
	std::string m_strH264FileName;//��ǰ¼���ļ�����
	FILE *m_fpOut;//¼���ļ�ָ��
};

#endif