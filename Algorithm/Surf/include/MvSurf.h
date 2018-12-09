// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary

#ifndef __MV_SURF_H
#define __MV_SURF_H
#pragma once

#include <cv.h>
#include <vector>
#include "fasthessian.h"

using namespace std;


//-------------------------------------------------------

class MvSurf
{
public:
	MvSurf(void);
	~MvSurf(void);

	float mvGetMatchPoints(IplImage *pImg1,IplImage *pImg2,CvRect rtROI,IpPairVec &matches);
	float mvGetMatchPoints(IplImage *pImg1,IplImage *pImg2,CvRect rtROI,IpPairVec &matches,IpVec &ipts1,IpVec &ipts2);
	float mvGetROIMatchPoints(IplImage *pImg1,IplImage *pImg2,CvRect rtROI,IpPairVec &matches,IpVec &ipts1,IpVec &ipts2);
	
	float mvGetMatchPoints(IplImage *pImg1, IplImage *pImg2, vector<CvRect> vecROI, vector<IpPairVec> &matches,const float fCoff=1.0f);
	float mvGetEXMatchPoints(IplImage *pImg1, IplImage *pImg2, vector<CvRect> vecROI, vector<IpPairVec> &matches,
		const float fCoff1=1.0f,const float fCoff2=1.0f);
	float mvGetMatchPoints(IplImage *pImg1, IplImage *pImg2, vector<CvRect> vecROI, vector<IpPairVec> &matches,
		vector<CvRect>vecROIExt,vector<IpPairVec>&matchesExt, const float fCoff=1.0f);
	/*
 *����˵����pImg1, pImg2�ֱ�Ϊƥ��ͼ�ʹ�ƥ��ͼ��
 *          vecROI1, vecROI2�ֱ��ӦpImg1, pImg2����ͼ�ϵ�ƥ������������Ϊ�������ǰ�Ĵ�ͼ��
 *          fCoff1, fCoff2�ֱ�ΪpImg1, pImg2���Ե����ű�����
 *          matchΪ���ص�ƥ����У�������Ϊ�������ǰ�Ĵ�ͼ��
 */
float mvGetMatchPoints(IplImage *pImg1, IplImage *pImg2, vector<CvRect> vecROI1, 
	vector<CvRect> vecROI2, vector<IpPairVec> &matches, const float fCoff1 = 1.0f, const float fCoff2 = 1.0f);
	
	//�ҵ�������
	void mvDetDes(IplImage *img,  /* image to find Ipoints in */
		std::vector<Ipoint> &ipts, /* reference to vector of Ipoints */
		bool upright = false, /* run in rotation invariant mode? */
		int octaves = OCTAVES, /* number of octaves to calculate */
		int intervals = INTERVALS, /* number of intervals per octave */
		int init_sample = INIT_SAMPLE, /* initial sampling step */
		float thres = THRES /* blob response threshold */);
	void mvGetMatches(IpVec &ipts1, IpVec &ipts2, IpPairVec &matches);//����ƥ��

private:
	void mvGetROIMatches(IpVec &ipts1, IpVec &ipts2, IpPairVec &matches,CvRect rtROI);
	void mvGetROIMatches(IpVec &ipts1, IpVec &ipts2, IpPairVec &matches,CvRect rtROI1,
		CvRect rtROI2);

	IplImage *getGray(const IplImage *img);
	IplImage *Integral(IplImage *source);

};

#endif