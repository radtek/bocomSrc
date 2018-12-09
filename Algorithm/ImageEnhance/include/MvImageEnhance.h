// ��������
// Bocom Intelligent 

//��ģ��ʵ��ͼ����ǿ�㷨

#pragma once


#include "math.h"
#include <deque>
//opencv�������ͷ�ļ�
#include "cxcore.h"
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"
#include "ml.h"
#include <vector>
#include "ipp.h"
#include <iostream>
#include <fstream>

using std::deque;
using std::vector;
using namespace std;
//���峣��
#define PI 3.1415926f //piֵ
#define mvMin(x,y) x<=y? x : y
#define mvMax(x,y) x>=y? x : y

//��������
float ThresholdOtsu(IplImage* grayim, CvRect rect, IplImage *mask); //ostu��ֵ�ָ�

//ͼ����ǿ���
class MvImgEnhance_HandOver
{
public:	
	MvImgEnhance_HandOver();
	~MvImgEnhance_HandOver();

	//ͼ����ǿ�Ľ�������
	//�ӿ�
	void mvImgEnhance(IplImage *pImage, CvRect rectImg, bool bDay);
	
	//ͼ������
	void mvWeibullParam(IplImage *image, double *gama, double *beta, IplImage *imageMask);
	void mvImgCastF();//��ɫ����
	void mvImgMoment(IplImage *Pimage, CvRect *rect, CvPoint2D32f *centerNow);
	void mvLightF();//��������
	void mvImgColorF();//�ʶ�����
	void Process1(IplImage * src, IplImage* dst);//ȥ��
	void LocalFilter(IplImage*dst, IplImage *src,int r);
	//ͼ����ǿ
	void mvImgEnhanceProcess(IplImage *pImage, CvRect rectImg);
	
	//algorithm test
	void mvImgFogRemove(IplImage *src);//DCP
	
private:
	IplImage *pImgResize;
	IplImage *Lab;//Ҳ����hsl
	
	IplImage *pImgResizeGray;
	IplImage *pA;//����s
	IplImage *pB;
	IplImage *pResizeMask;
	
	IplImage *pImgResizeGray32;
	
	IplImage *pImgGW32;
	//ͼ���������
	CvSize sizeOri;//ͼ��ԭʼ��С
	CvSize sizeRe;//���ź�Ĵ�С
	//����ͼ������
	double gama;
	double beta;
	float fTh;//ostu�ָ���ֵ
	bool bCastYN;//�Ƿ�ƫɫ
	int nMethod;//��ƽ�ⷽ��
	CvPoint2D32f abMove;//labƽ������
	CvScalar sGWvector;//gray world��ϵ��
	float fGammaLUT[256];//gammaУ����LUT
	float fColorLUT[256];//�ʶ�У����LUT
	float fLight;
	float fFog;
	

};