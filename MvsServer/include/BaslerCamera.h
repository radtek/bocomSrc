#ifdef BASLER_CAMERA
#ifndef BASLER_CAMERA_H
#define BASLER_CAMERA_H

#include"AbstractCamera.h"
#include <pylon/PylonIncludes.h>
#include <iostream>
using namespace Pylon;
using namespace GenApi;
using namespace GenICam;

#define GAIN_DB_UNIT 51
#define GAIN_MAX 1023
#define GAIN_MIN 0
#define INFINITE	0xFFFFFFFF


class BaslerCamera :public AbstractCamera
{
public:
	BaslerCamera(int nCameraType);
	~BaslerCamera();

	//����Ƶ
	virtual bool Open();
	virtual bool Close();
	//���ļ�
	//�ֶ�����
	virtual int ManualControl(CAMERA_CONFIG cfg);
	//�Զ�����
	virtual int  AutoControl(unsigned int uTimeStamp,float fRate,float fIncrement,bool bDetectCarnum,int nIris,int nEn);
	//��ȡ
	virtual int ReadCameraSetting(CAMERA_CONFIG& cfg,bool bConvert = true);
	//���´�
	virtual bool ReOpen();
	//�л�������ʽ
	virtual bool ChangeMode();
	//��ȡ���Ĭ��ģ��
	virtual void GetDefaultCameraModel(CAMERA_CONFIG& cfg);
	virtual void ConvertCameraParameter(CAMERA_CONFIG& cfg,bool bReverseConvert,bool bFirstLoad = false);

	//�������
	void ControlCamera(CAMERA_CONFIG cfg);
	//�ƿ���
	int   LightControl(bool bInit = false);

	//������Ƶ��
	void RecvVideoStream();

private:
	CTlFactory* m_TlFactory;
	IPylonDevice* m_Camera;
	BYTE* m_Buffer;

	DeviceInfoList_t m_Devices;
	IStreamGrabber* m_StreamGrabber;
	INodeMap* m_CameraNodeMap;

	StreamBufferHandle m_hBuffer;
	static WaitObjectEx m_WaitObjectEx;

	pthread_t m_pthreadId;

	bool m_bStopCamera;

	int m_uMaxPE;
	int m_uMaxGain;
	int m_uMaxGamma;
};
#endif
#endif

