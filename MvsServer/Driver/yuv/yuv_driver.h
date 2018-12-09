// ������ͨ��Ƶ����ʶ������� V1.0
// Mimax Intelligent Transport Video Recognition & Detection Software V1.0
// ��Ȩ���� 2008 �Ͼ�������Ѷ�Ƽ����޹�˾
// Copyright 2008 Nanjing Mimax Vision Technologies Ltd
// ������Ѷ��˾����  Mimax Vision Confidential Proprietary
//
#ifndef _YUV_DRIVER_H
#define _YUV_DRIVER_H


#include <linux/types.h>
#include <sys/time.h>
#include <time.h>


//DEBUG���
//#define _DEBUG


typedef struct _yuv_video_header
{
	unsigned char cSynchron[4];     //ͬ��ͷ
    unsigned char cType[4];     //��������
	unsigned short nWidth; //ˮƽ�ֱ���
	unsigned short nHeight; //��ֱ�ֱ���
	unsigned short nFrameRate; //֡��
	unsigned short nFieldSeq;  //�����
	unsigned int nSize;     //��������
    unsigned char cReserved[8];  //Ԥ��
}yuv_video_header;

typedef struct _yuv_video_buf {
    unsigned int   width;			//��
    unsigned int   height;			//��
    unsigned int   size;		//��С
	unsigned long  nSeq;        //֡��
	int64_t          ts;       //ʱ���(���㿪ʼ�����ʱ��)
	unsigned int   uTimestamp;  //ϵͳʵ��ʱ��
    unsigned char  *data;		//����
}yuv_video_buf;







#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif
//���豸,����socket
int yuv_open(const char* host,int port,const char* user,const char* pass);
//�ر��豸
int yuv_close (int fd);

//��������
int yuv_nextframe(int fd,yuv_video_buf** pBuf);

//�ͷ��ڴ�
int yuv_release_buf();
//ʱ���
int64_t yuv_to_timestamp(struct timeval *tv);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif	//_YUV_DRIVER_H
