// ������ͨ��Ƶ����ʶ������� V1.0
// Mimax Intelligent Transport Video Recognition & Detection Software V1.0
// ��Ȩ���� 2008 �Ͼ�������Ѷ�Ƽ����޹�˾
// Copyright 2008 Nanjing Mimax Vision Technologies Ltd
// ������Ѷ��˾����  Mimax Vision Confidential Proprietary
//
#ifndef _V4L2_STRUCTDEF_H
#define _V4L2_STRUCTDEF_H

#include <stdio.h>
#include <sys/time.h>
#include <linux/types.h>
#include <pthread.h>
#include <inttypes.h>
//vedio for linux 2
#include <linux/videodev2.h>
#include <string.h>


//�豸������ֵ
#define	LINUX_VIDEO_MAX	16
//���������ݼ�
#define LINUX_V4L2_BUFFERS 32
//���ɼ���Ŀ
#define LINUX_V4L2_MAX_INPUT   16

//#define MAX_NORM    16
#define LINUX_V4L2_MAX_FORMAT  32	//��ʽ

#define LINUX_V4L2_MAX_CTRL    32	//��������

#define LINUX_V4L2_UNSET		-1	//��Чֵ

#define VIDEO_NONE           0
#define VIDEO_RGB08          1  /* bt848 dithered */
#define VIDEO_GRAY           2
#define VIDEO_RGB15_LE       3  /* 15 bpp little endian */
#define VIDEO_RGB16_LE       4  /* 16 bpp little endian */
#define VIDEO_RGB15_BE       5  /* 15 bpp big endian */
#define VIDEO_RGB16_BE       6  /* 16 bpp big endian */
#define VIDEO_BGR24          7  /* bgrbgrbgrbgr (LE) */
#define VIDEO_BGR32          8  /* bgr-bgr-bgr- (LE) */
#define VIDEO_RGB24          9  /* rgbrgbrgbrgb (BE) */
#define VIDEO_RGB32         10  /* -rgb-rgb-rgb (BE) */
#define VIDEO_LUT2          11  /* lookup-table 2 byte depth */
#define VIDEO_LUT4          12  /* lookup-table 4 byte depth */
#define VIDEO_YUYV			13  /* 4:2:2 */
#define VIDEO_YUV422P       14  /* YUV 4:2:2 (planar) */
#define VIDEO_YUV420P	    15  /* YUV 4:2:0 (planar) */
#define VIDEO_MJPEG	    16  /* MJPEG (AVI) */
#define VIDEO_JPEG	    17  /* JPEG (JFIF) */
#define VIDEO_UYVY	    18  /* 4:2:2 */
#define VIDEO_FMT_COUNT	    19



struct v4l2_video_fmt {
    unsigned int   fmtid;         /* VIDEO_* */
    unsigned int   width;
    unsigned int   height;
    unsigned int   bytesperline;  /* zero for compressed formats */
};


struct v4l2_video_buf {
    struct v4l2_video_fmt  fmt;
    size_t               size;
    unsigned char        *data;

	/* meta info for frame */
    struct {
	int64_t          ts;      /* time stamp */
	int              seq;
	int              twice;
    } info;

	//������ʶ
	int	refcount;
    pthread_mutex_t	lock;
    pthread_cond_t	cond;
	void                 (*release)(struct v4l2_video_buf *buf);
};




//�������ݽṹ
struct v4l2_handle {

    int	fd;	//�豸���
    
	//�豸���������Ϣ
    struct v4l2_capability	cap;

    //stream ������������ɶ�õģ�
	struct v4l2_streamparm	streamparm;
    //�豸INPUTS����ɶ�õģ�
	int	ninputs;
	struct v4l2_input		inp[LINUX_V4L2_MAX_INPUT];
    //	struct v4l2_standard      	std[MAX_NORM];
	//�豸��ʽ����
	int nfmts;
    struct v4l2_fmtdesc		fmt[LINUX_V4L2_MAX_FORMAT];
	//��������[���ȡ��Աȶȡ����Ͷ�......]��V4L2��׼����ʹ��˽������
	struct v4l2_queryctrl	ctl[LINUX_V4L2_MAX_CTRL];

    //����
    //int                         nattr;
    //struct ng_attribute         *attr;

    //��׽����
    int	fps;	//֡��
	int	first;
    //long long                      start;
    //v4l2��ʽ
	struct v4l2_format             fmt_v4l2;
	//�ڲ�ʹ�ø�ʽ,��¼��Ƶ����
	struct v4l2_video_fmt		   fmt_me;
	//��������
    struct v4l2_requestbuffers     reqbufs;
	//����������
    struct v4l2_buffer             buf_v4l2[LINUX_V4L2_BUFFERS];
    //����������
	struct v4l2_video_buf          buf_me[LINUX_V4L2_BUFFERS];

    unsigned int	queue;		//����
	unsigned int	waiton;		//ȡ�����ݼ���

    /* overlay */
    //struct v4l2_framebuffer        ov_fb;
    //struct v4l2_format             ov_win;
    //struct v4l2_clip               ov_clips[256];
    //int                            ov_error;
    //int                            ov_enabled;
    //int                            ov_on;
};



#endif//_V4L2_STRUCTDEF_H
