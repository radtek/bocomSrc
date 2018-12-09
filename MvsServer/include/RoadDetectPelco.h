#ifndef ROAD_DETECT_PELCO_H
#define ROAD_DETECT_PELCO_H
/*************************
pelco�汾ͣ���Ϲܼ�⼰���Ʋ���
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
#include "cv.h"
#include "cxcore.h"
#include "Common.h"
#include <string>
using namespace std;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (unsigned int)(~0)
#endif

#ifndef PELCO_ZOOM_TIME
#define PELCO_ZOOM_TIME 250000
#endif

#ifndef PELCO_PANTILT_TIME_LANG
#define PELCO_PANTILT_TIME_LANG 3000000
#endif 

#ifndef PELCO_PANTILT_TIME_SHORT
#define PELCO_PANTILT_TIME_SHORT 1000000
#endif 


#ifdef CAMERAAUTOCTRL
#include "CameraAutoCtrl.h"
#endif

class CRoadDetectPelco
{
public:
	CRoadDetectPelco();
	~CRoadDetectPelco(void);
	//���ü�⳵��λ������
	void DetectRegionRect(int Camerawidth,int Cameraheight,int xPos,int yPos,int width,int height);
	//��ʼ������̨�ƶ�����������
	int DealTrackAutoRect(string frame);
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
	int CalculateRectPtzZoomEX(CvRect rectNew);
	/*
	�����������ǰĿ��λ�� false��ʾ��ǰΪˮƽ�ƶ���true��ʾ��ǰΪ�Ŵ����
	��Ŀǰ����Ϊˮƽ�ƶ�ʱ���жϵ�ǰĿ������ĵ���뻭������ĵ��С��
	��С��1/20ʱ��������������������ڻ����1/4ʱ���ƶ���ʱ��С��1/4ʱ���ƶ�Сʱ��
	*/
	bool CalculateRectAndMovePtzOrZoom(CvRect rectNew,bool bZoom = false);
	/*ʹ��pelcoЭ�������ƶ���̨*/
	bool PTZMoveToPanTiltUp();
	/*ʹ��pelcoЭ�������ƶ���̨*/
	bool PTZMoveToPanTiltDown();
	/*ʹ��pelcoЭ�������ƶ���̨*/
	bool PTZMoveToPanTiltLeft();
	/*ʹ��pelcoЭ�������ƶ���̨*/
	bool PTZMoveToPanTiltRight();
	/*ʹ��pelcoЭ�����������ʷŴ����*/
	bool PTZMoveToZoom();
	/*ʹ��pelcoЭ��ֹͣ���в���*/
	bool PTZMoveToStop();

	int WaitConnect(int nSocket, float fTimeout);
	int CloseSocket(int& fd);//���ظ�����

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
#endif
	int m_uiResponse;
	int m_iCameraMoveTime;

	// 0��ʾ����Ҫ�ƶ� 1��ʾ��Ҫ
	int m_uiTiltUpOrDown;
	int m_uiPanLeftOrRight;

	int m_nErrCount; //Ŀ�궪ʧ��������40����Ϊ�˴ζ�λʧ��
	char szAddrIP[50];
	int  szAddrPort;


};
#endif
