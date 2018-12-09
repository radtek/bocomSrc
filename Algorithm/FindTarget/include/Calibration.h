// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef MYCALIBRATION_H
#define MYCALIBRATION_H


//#define USE_TSAI



#include <highgui.h>
#include <cxcore.h>
#include <algorithm>

#ifdef SPEED_UP
#undef USE_TSAI
#endif

#undef USE_TSAI

#ifdef USE_TSAI
  #include "cal_main.h"
#endif

#include "StdAfx.h"







PRJ_NAMESPACE_BEGIN



/**
	�๦�ܣ�����궨�࣬�ɼ���ͼ�����������������ת������
	ָ��ת�����󣬽���ͼ����������������Ļ�ת��
*/
class MyCalibration
{
public:

	// ��������������꣬������ͼ������
	static CvPoint        GetImageCoordinate(const CvPoint2D64f &wordPt, const double homograhy[3][3]);

	
	
	// �������ͼ�����꣬��������������
	static CvPoint2D64f   GetWorldCoordinate(const CvPoint &pt,const double homography[3][3]);
	static CvPoint2D64f   GetWorldCoordinate(const CvPoint2D64f &pt,const double homography[3][3]);


	// ����ͼ����������ĵ�ת����֤
	static void           FindHomography(const double *image, const double *world, double homography_image_to_world[3][3]);

public:

	
	/*
	����ԭʼͼ���С��nImageWidth�� nImageHeight������ԭʼͼ���ϱ궨���ͼ�����꼰���������ꡣ
	���㰴dScaleX��dScaleY��С���ͼ���ϱ궨��
	*/
	MyCalibration(int nImageWidth, int nImageHeight, const double *image, const double *world, 
					int nCount, double dScaleX, double dScaleY);


	/*
	����ͼ���С����ͼ���ϱ궨���λ���Լ����������꣬���б궨��
	*/
	MyCalibration(int nImageWidth, int nImageHeight, const double *image, const double *world, int nCount);


	//MyCalibration();


	// ��������
	~MyCalibration();


	// �������ͼ�����꣬��������������
	CvPoint2D64f   GetWorldCoordinate(const CvPoint &pt) const;




	// ����������������ϵ�е�λ��(x,y,z),�������ͼ���е����ꡣ
	CvPoint        GetImageCoordinate(const CvPoint3D64f &wordPt);


	// ����ͼ����ĳ�㣬�������õ�����������ϵ�е�zֵ�������������ꡣ
	CvPoint3D64f   GetWorldCoordinate(const CvPoint &ptImage, float zw);


	// ��������������꣬������ͼ������
	CvPoint        GetImageCoordinate(const CvPoint2D64f &wordPt) const;

	// ��ת������
	void           GetHomography(double homography_image_to_world[3][3]) const;



	//void SetHomography(const double homography_image_to_world[3][3]);



	// ����һ�����ڲ��Ա궨�Ƿ���ȷ��ͼƬ���洢�ڳ���ִ��Ŀ¼�¡�
	void           TestCalibration(int nWidth, int nHeight, char *strCalibName);



private:

	// ���ƹ��캯��
	MyCalibration(const MyCalibration &calib);

	// 
	MyCalibration & operator = (const MyCalibration &calib);

private:

	//ͼ�����굽���������ת������
	double m_homographyMatrix[3][3];

	//ͼ�����굽���������ת������
	CvMat *m_pHomoMat;

	//�������굽ͼ�������ת������
	CvMat *m_pHomoMatInv;


	#ifdef USE_TSAI
		cal *camTsai;
	#endif

};

PRJ_NAMESPACE_END


#endif
