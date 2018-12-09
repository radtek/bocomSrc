#ifndef ROAD_DETECT_DHCAMERA_H
#define ROAD_DETECT_DHCAMERA_H
/*************************
�󻪸�����汾ͣ���Ϲ�
*************************/

#include <sys/time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "cv.h"
#include "cxcore.h"
#include "Common.h"
#include <string>
using namespace std;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (unsigned int)(~0)
#endif

#ifndef Roadmax
#define Roadmax(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef Roadmin
#define Roadmin(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifdef CAMERAAUTOCTRL
#include "CameraAutoCtrl.h"
#include "CamCtrlComCalc.h"
#include "OnvifCameraCtrl.h"
#endif

struct AutoCameraDHPtzTrack
{
	int nTaken;
	int nPanTiltX;
	int nPanTiltY;
	int nPanTiltZoom;
	int nBeginTime;
};

class CRoadDetectDHCamera
{
public:
	CRoadDetectDHCamera();
	~CRoadDetectDHCamera(void);
	//���������һЩ������������ʼ��ʱ����һ�Σ�
	void SetCameraVar(
		float fCCD_w,        //���룺CCD�Ŀ�� 
		float fCCD_h,        //���룺CCD�ĸ߶�
		float fMinFocus,     //���룺��С����
		float fMaxFocus,     //���룺��󽹾�
		int   nMultiPlicate  //���룺����ı���
		);
	//���ü�⳵��λ������
	void DetectRegionRect(int Camerawidth,int Cameraheight,int xPos,int yPos,int width,int height);
	//��ʼ������̨�ƶ�����������
	int DealTrackAutoRect(string frame,int nCarId,int nSaveProcess);
	/*����Ԥ��λ����*/
	bool GotoPreset(int uiPresetNum);
	int InputCameraAddr(const char *pCameraHost,int pCameraPort);

private:
	/*��ȡ��ǰʱ��*/
	int GetTimeT();
	/*�жϵ�ǰĿ���Ƿ��������������ģ���������1/20����֮��*/
	bool IsCentreRectResemble(CvRect rectNew);
	/*�жϵ�ǰ�����Ƿ��ƶ�*/
	bool IsRectResemble(CvRect rectOld,CvRect rectNew);
	// ����ֵ 0��ʾ����Ŵ� 1��ʾ���Լ����Ŵ� 2��ʾΪ���Լ����Ŵ󲢼��복�Ƽ�⹦��
	int CalculateRectPtzZoomEX(CvRect rectNew,float &fRectArea,float &fZoomValue);
	/*
	�����������ǰĿ��λ�� false��ʾ��ǰΪˮƽ�ƶ���true��ʾ��ǰΪ�Ŵ����
	��Ŀǰ����Ϊˮƽ�ƶ�ʱ���жϵ�ǰĿ������ĵ���뻭������ĵ��С��
	��С��1/20ʱ��������������������ڻ����1/4ʱ���ƶ���ʱ��С��1/4ʱ���ƶ�Сʱ��
	*/
	bool CalculateRectAndMovePtzOrZoom(CvRect rectNew,int m_nCarId,int m_nSaveProcess,bool bPTZMove = true);

	int CalculateRectPtzEX(CvRect rectNew,float &fPanTiltX,float &fPanTiltY);

	int TrackAutoCtrl(int nCarId,int nSaveProcess);
	//��������ƶ��켣
	int SaveCameraMoveTrack(int nCarID,int nX,int nY,int nZ);

private:
	CvRect m_RectInput;
	int m_CameraWidth;
	int m_Cameraheight;
	int m_iBeginAdjustRect; //����Ŀǰ��ˮƽ�ƶ����ǷŴ���С����
	bool m_nbMoveOperate; //����Ŀǰ��ˮƽ�ƶ����ǷŴ���С����
	int m_iMarkTime;
	bool m_bBeginDetect;
	bool m_bFristMark;
	IplImage *m_pImgSrc;     //����ͣ���㷨�е�ͼƬ
#ifdef CAMERAAUTOCTRL
	CMvCameraAutoCtrl *m_pMvCameraAutoCtrl;
	MvCalcCamMvScale  *m_pMvCalcCamMvScale;
	COnvifCameraCtrl  *m_pOnvifCameraCtrl;
#endif
	int m_iCameraMoveTime;

	int m_nErrCount; //Ŀ�궪ʧ��������40����Ϊ�˴ζ�λʧ��
	int m_nDetectNum; //0��ʾΪ��һ�ηŴ� 1��ʾΪ�ڶ���
	int  m_nCameraMoveCount;//��̨�ƶ����� ����Ϊ4��
	float m_fScaleRealZoom;  //��Ҫ�䱶�Ĵ�С

	typedef list<AutoCameraDHPtzTrack> listPtzTrack;
	typedef map<int,listPtzTrack> mapAutoCameraPtzTrack;
	mapAutoCameraPtzTrack m_AutoCameraPtzTrack;
	char szAddrIP[50];
	int  szAddrPort;

};
#endif
