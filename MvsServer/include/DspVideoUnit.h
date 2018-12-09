#ifndef DSP_VIDEO_UNIT_H
#define DSP_VIDEO_UNIT_H

#include "global.h"
#include "CSocketBase.h"

class CDspVideoUnit;

typedef struct _DspClassAndFd
{
	CDspVideoUnit *p;
	Client_Fd cfd;
	pthread_t id;

	_DspClassAndFd()
	{
		p = NULL;
		id = 0;
	}

}DspClassAndFd;

class CDspVideoUnit
{
public:
	CDspVideoUnit();
	~CDspVideoUnit();

public:
	bool InitTcp(bool bEndCapture, bool bH264Capture);
	//void StartGetDataFromDsp();
	//bool Seth264RecFd(int& fd, UINT32 uId);
	bool Seth264RecFd(DspClassAndFd classfd);

	//TCP ��������
	void RecvH264Fd();
	//����h264���ݰ�
	bool SafeRecvh264Fd(Client_Fd& cfd,char*pBuf, int nLen, int &nRecvSize);

	//�ɼ����ݴ�¼��
	void CaptureVideoFrame(const int64_t &tick, const std::string &response, const UINT32 uId, const int nSock, const std::string strIp);

	//��ȡ¼��·��
	//bool GetPathInfoById(const UINT32 uId, VIDEO_PATH_INFO &pathInfo);

	void CloseFd();

	bool GetCaptureState() 
	{ 
		return	 m_bEndCapture; 
	}

	void RefreshId(const UINT32 uId);

	//void SetClassCfd(const DspClassAndFd classCfd);
	bool UnInit();

	UINT32 GetId() { return m_classCfd.cfd.uCameraId; }

	bool GetUnitStatus();

	//����DSP�ظ�������
	bool SendToDspLinkFd(const Client_Fd& cfd);
private:
	VIDEO_PATH_INFO m_pathInfo;

	bool m_bEndCapture;
	int m_nChannelId;
	//�Ƿ����H264����
	bool m_bH264Capture;

	DspClassAndFd m_classCfd;
	int m_nRecvNodataCounts;
};

#endif