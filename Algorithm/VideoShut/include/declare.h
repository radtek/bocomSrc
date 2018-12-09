
#ifndef _DECLARE_H_
#define _DECLARE_H_


#define SIFT_DESC_DIMENTION 128
#define MAX_CORNERS_PER_FRAME 100       //ÿ֡�м��������Ľǵ�����
#define MAX_CORNERS_OF_NONMAX 1024

#define MAX_TRACKS_PER_FRAME  64      //ÿ֡�����Ĺ켣����		
#define MAX_CORNERS_PER_TRACK 40       //ÿ���켣���Ľǵ�����	

#define MAX_GROUPS_PER_FRAME 128        //ÿ֡��Group���������ֵ
#define MAX_TRACKS_PER_GROUP 16        //ÿ��Group�а�����Track���������ֵ

//#define MAX_IMG_HEIGHT 10000  //���㷨�ڲ����㣩
//#define MAX_IMG_WIDTH  10000 //���㷨�ڲ����㣩


#include "stdio.h"
#include "cv.h"
#include "highgui.h"



typedef struct   _Mv_INPUT_DATA
{
	unsigned char *sqrtData;
	unsigned char *stdData;
} MvInputData;


#endif
