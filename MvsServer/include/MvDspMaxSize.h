
#ifndef _MV_DSP_MAXSIZE_
#define _MV_DSP_MAXSIZE_

#include "MvDspCalibration.h"

class MvDspMaxSize
{
public:

	//���캯����ʼ��
	MvDspMaxSize();

	//��������
	~MvDspMaxSize();

	//��ȡ�������ĵ�����������ͼ���г����Ŀ�Ⱥ͸߶�
	void GetWorldCoordinateAndCarSize();

public:
	
	int m_nWidth;
	int m_nHeight;

	IplImage* m_wldx_image;           //�������ĵ��X������������ͼ��
	IplImage* m_wldy_image;           //�������ĵ��Y������������ͼ��
	IplImage* m_carwidth_image;       //��ͼ�������г����Ŀ��ͼ��
	IplImage* m_carheight_image;      //��ͼ�������г����ĸ߶�ͼ��
	double m_image_coordinate[12];    //��֪��4�����ͼ������
	double m_world_coordinate[12];    //��֪��4�������������
	double m_homographyMatrix[3][3];  //ͼ�����굽���������ת������
	MvDspCalibration m_pCalib;        //����궨����
};

#endif