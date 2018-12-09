// ������ͨ��Ƶ����ʶ������� V1.0
// Mimax Intelligent Transport Video Recognition & Detection Software V1.0
// ��Ȩ���� 2008 �Ͼ�������Ѷ�Ƽ����޹�˾
// Copyright 2008 Nanjing Mimax Vision Technologies Ltd
// ������Ѷ��˾����  Mimax Vision Confidential Proprietary
//
#ifndef _V4L2_DRIVER_H
#define _V4L2_DRIVER_H

#include "v4l2_structdef.h"

//DEBUG���
//#define _DEBUG

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"{
#endif
//���豸
void *v4l2_open (char *device);
//�ر��豸
int v4l2_close (void *handle);

//��׽��Ƶ
//�豸��Ƶ����
int v4l2_setformat (void *handle, struct v4l2_video_fmt *fmt);
//��ʼ��׽
int v4l2_startvideo (void *handle, int fps, unsigned int buffers);
//ֹͣ��׽
void v4l2_stopvideo (void *handle);
//��׽��һ֡
struct v4l2_video_buf *v4l2_nextframe (void *handle);
//�ͷ�ʹ�õ�����
int v4l2_release_video_buf(struct v4l2_video_buf *buf);

//������Ƶ����
//��������
int v4l2_setbrightness(void *handle,unsigned int uBrightness);
//���öԱȶ�
int v4l2_setcontrast(void *handle,unsigned int uContrast);
//���ñ��Ͷ�
int v4l2_setsaturation(void *handle,unsigned int uSaturation);	
//����ɫ��
int v4l2_sethue(void *handle,unsigned int uHue);					
//������ƵԴ
int v4l2_setsource(void *handle,unsigned int uSource);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif	//_V4L2_DRIVER_H
