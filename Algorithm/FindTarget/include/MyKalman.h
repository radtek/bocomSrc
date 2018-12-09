// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   15:05
	filename: 	e:\BocomProjects\find_target_lib\include\MyKalman.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	MyKalman
	file ext:	h
	author:		Durong
	
	purpose:	û��ʹ��
*********************************************************************/


#ifndef MV_MY_KALMAN_H

#define MV_MY_KALMAN_H



#include "cxcore.h"
#include "cv.h"
#include "highgui.h"

class MyKalman
{
private:

	CvRandState rng;
	CvKalman* kalman;
	CvMat* x_k;//״̬
	CvMat* w_k;//��������
	CvMat* z_k;//�۲�ֵ

public:
	
	MyKalman();
	~MyKalman();

	CvPoint2D32f Predict(float dt);

	void Correct(float dt, CvPoint2D32f measur);

};



#endif