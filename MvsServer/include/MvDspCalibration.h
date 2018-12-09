
#ifndef _MV_DSP_CALIBRATION_
#define _MV_DSP_CALIBRATION_

#include "cxcore.h"
#include "highgui.h"
#include "cv.h"

class MvDspCalibration
{
public:
	//���캯����ʼ��
	MvDspCalibration();
	
	//��������
	~MvDspCalibration();
	
	//����ͼ�����굽��������ĵ�ת������
    void FindHomography();

	//�������ͼ�����꣬��������������
	CvPoint2D64f GetWorldCoordinate( const CvPoint& pt );

	//��������������꣬������ͼ������
	CvPoint GetImageCoordinate( const CvPoint2D64f& wordPt );

public:
	double m_image_coordinate[12];       //�������ͼ������
	double m_world_coordinate[12];       //���������������
	double m_homographyMatrix[3][3];  //ͼ�����굽���������ת������
};

#endif