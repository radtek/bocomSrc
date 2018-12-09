// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include "mvGetBGLight.h"
#include "mvGetCameraControlPara.h"
//#include "Camerakinds.h"
//#include "DetectSmear.h"

#ifndef USE_DSP_CODE
//#define USE_DSP_CODE
#endif

#define DAY_MEAN_DIM (3)
#define NIGHT_MEAN_DIM (15)

class CameraParametter
{

public:
	CameraParametter(void);

	~CameraParametter(void);

	void cameraControl_Init(void);

	void cameraControl_Destroy(void);

	void mvGetBGLight( IplImage* image, CvRect detectRect,
					carnum_context* vehicle_Information, int nCarNumResult, int &lightTypes, int isDayByTime=C_DAY, bool bIsFaceCrt=false );

	void GetCameraControl_Para( UINT32 uTimeStamp, UINT32 m_detect_time, int interval, bool bDetectCarnum,
								CAMERA_PARA &camPara, float &fRate, float &fIncrement, int &nIris, int &isDayByLight, int &nEn );

#ifdef USE_DSP_CODE
	void mv_SetYdatetoIplImage( unsigned char *pYdate, int nWidth, int nHeight );
	IplImage *pYimage;	
#endif

protected:
	void mvComputePoliceLightMean(const int &nDim, const unsigned int &nCounts, bg_info *bgInfoHist,
									region_context &context, int &nNotZeroCounts);

	void mvCtrlLEDLight(const region_context &context, const CAMERA_PARA &camPara, const int &isDayByLight, 
		const int &isDayBytime, float &fRate, float &fIncrement, int &nEn);

private:
	BGLight m_Bglight; //��

	//DetectSmear m_SmearDetect; //��

	CameraPara controlPara;

	int m_width;

	bool m_iSInvokeBgLight;

	region_context m_context;

	region_context m_precontext;

	int m_carnum_count;

	int m_camKinds;

	bool m_bSmearNum;

	int m_IsBackOrInfront;

	bool m_bIsCloud;

	int m_colorMode; //��ɫͨ��˳��

	bg_info *m_dayCarMeanInfo; //����ĳ�������ֱ��ͼ

	bg_info *m_nightCarMeanInfo; //���ϵĳ�������ֱ��ͼ

	unsigned short m_nightInterval; //���ϵ���������ƴ���

	unsigned short m_dayInterval; //�������������ƴ���

	float m_preRate; //ǰһ֡�Ŀ���ϵ��

	float m_preIncrement; //ǰһ֡������ϵ��

	int m_preDN; //ǰһ֡�İ����������

	unsigned short m_isDayCounts; //����ֱ��ͼ�����������

	unsigned short m_isNightCounts; //����ֱ��ͼ����������

	int m_nCount; //����ͳ���������һ��ֵ�Ĵ���

	bool m_bFirst; //��һ�ε����������
	
	float m_preNotZeroRate; //ÿ���������ѭ���ڲ���0�Ŀ��ŵ���

	float m_preNotZeroInment; //ÿ���������ѭ���ڲ���0���������

	bool m_bIsFaceCrt; //�Ƿ�����������������
};











#endif