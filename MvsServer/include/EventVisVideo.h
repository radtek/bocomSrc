#ifndef ROAD_EVENT_VIS_VIDEO_H
#define ROAD_EVENT_VIS_VIDEO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <list>
#include <string>
using namespace std;

#include "Common.h"

// #ifndef UINT8
// typedef unsigned char	UINT8
// #endif

#ifndef ROADEVENT_UPLOAD_FTP
#define ROADEVENT_UPLOAD_FTP 0x11
#endif

#ifndef ROADEVENT_HEART_BEAT
#define ROADEVENT_HEART_BEAT 0x13
#endif

typedef struct tagstrEventVisVidoe 
{
	int dwBeginTime;   //������Ƶ�Ŀ�ʼʱ��
	int dwEntTime;     //������Ƶ�Ľ���ʱ��
	char szDeviceId[30];    //�豸���
	int dwDir;         //����
	char szEventTime[30];        //�¼������¼�
	int dwSendTime;    //��ʼ������Ƶ��ʱ��
	int dwResult;      //��Ƶ������      // 0 ��ʾδ���ͣ� 1����ʾ���ڷ��� 
}strEventVisVidoe;

struct strVisMsgHead
{
	 unsigned char bHead1;     // Э��ͷ 0xDF
	 unsigned char bHead2;     // Э��ͷ 0xDF
	 unsigned char bVersion;   //Э��汾 Ox01
	 unsigned char bMsgType;   //��Ϣ���� ���eBcmMsgType
	 unsigned char bLength;    //��Ϣ���� ��������Ϣͷ����
	 unsigned char bChecksum;  //У��λ ��������ֽ�֮�� & 0xFF
};

typedef struct tagReqUploadVideo
{
	unsigned long long  ubiSessionId;	//����ţ������ۼӣ����ڱ�ʶ��ǰ���� ����������
	unsigned long long ubiCameraId;	//�������� VISϵͳ�е�����������
	int uiStartTime;	//��Ƶ��ʼʱ�� VISϵͳ�е�ʱ���ʽ
	int uiEndTime;		//��Ƶ����ʱ�� VISϵͳ�е�ʱ���ʽ
	char szFtpUserName[20];	//FTP �û���
	char szFtpPassword[20];	//FTP ����
	char szDeviceCode[20];	//�豸����
	char szDriveDir[10];	//��ʻ�������
	char szLaneFlag[10];	//������ʶ��
	char szDataTime[20];	//���ں�ʱ�� ��λ��ʾ�����+��λ��ʾ���·�+��λ��ʾ�����ڣ���λ��ʾ��Сʱ��+��λ��ʾ�ķ�����+��λ��ʾ������+��λ��ʾ�ĺ�����
}REQUPLOADVIDEO;

class CEventVisVideo
{
public:
	CEventVisVideo();
	~CEventVisVideo();
	/*************************************
	��  �ܣ�����VIS������
	��  ����szVisIp    -- ��������ַ
			dwVisPort  -- �������˿�
			dwCameraID -- ��������
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int SetVisInfo(const char* szFtpUserName,const char* szFtpPwd,const char *szVisIp,int dwVisPort,char* szCameraID);
	/*************************************
	��  �ܣ����������Ƶ��Ϣ
	��  ����dwEventBeginTime -- ��ʼʱ��
			dwEventEndTime   -- ����ʱ��
			dwVideoNo        -- ¼����
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int AddEventVideoReq(int dwEventBeginTime,int dwEventEndTime,const char* szDeviceId,int dwDir,int dwEventTime);
	/*************************************
	��  �ܣ����������Ƶҵ�� �������������ɾ����������
	��  ����
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int DealEventVideo();

private:
	int SentHeartBeat();
	int DealEvent();
private:
	/*************************************
	��  �ܣ�����VIS������
	��  ����szVisIp    -- ��������ַ
			dwVisPort  -- �������˿�
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int ConnectToVis(char *szVisIp,int dwVisPort);

	/*************************************
	��  �ܣ���������
	��  ����szMsg    -- ��������
			uiMsgLen -- �������ݳ���
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int SendMsg(char* szMsg,int uiMsgLen);
	/*************************************
	��  �ܣ���������
	��  ����
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int RecvMsg();
	/*************************************
	��  �ܣ���������
	��  ����dwSocketFd socket���
			fTimeout   ��ʱʱ��
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int WaitRecv(int dwSocketFd, float fTimeout);
	/*************************************
	��  �ܣ���������
	��  ����dwSocketFd socket���
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int CloseSocket(int &dwSocketFd);
	/*************************************
	��  �ܣ���ȡ��ǰʱ��
	��  ����
	����ֵ���ɹ�����0��ʧ�ܷ��ش�����
	*****************************************/
	int GetTimeT();
	/*************************************
	��  �ܣ����ַ���ת��Ϊunsigned long long
	��  ����szID  �ַ���
	����ֵ���ɹ�����0��
	*****************************************/
	unsigned long long  roadatoull(const char* szID); 

private:
	//socket���
	int m_ClientSocket;
	typedef std::list<strEventVisVidoe> listEvent;  
	listEvent m_listEvent;//�����б�
	//vis ip
	char m_szFtpUserName[50];
	char m_szFtpPwd[50];
	char m_szVisIp[50];
	int  m_dwVisPort;
	unsigned long long  m_dwCameraID;       //VIS��������
	int  m_dwHeartBeatTime;  //�ϴη���������ʱ��
};

#endif