#pragma once

#define MAX_CHANNEL_SIZE 64
enum eDOWNLOAD_CTRL
{
	DOWNLOAD_PAUSE = 1,
	DOWNLOAD_START,
};

enum ePTZ_CTRL
{

};

typedef struct tagChannel
{

}sChannel;


typedef struct tagDeviceStatus
{

}sDeviceStatus;

typedef struct tagDeviceInfo
{

}sDeviceInfo;

typedef struct tagBM_TIME
{
	int iYear;
	int iMon;
	int iDay;
	int iHour;
	int iMin;
	int iSec;
}sBM_TIME;

typedef struct tagQueryFileCond
{
	long lEvent;			// ָ���¼����Ͳ�ѯ
	sBM_TIME tStart;		// ָ����ѯʱ���
	sBM_TIME tStop;
	long lFileSize;			// �ļ���С
	long lRes;              // �����ֶ�
}sQueryFileCond;

typedef struct tagPlaybackFile
{
	char szFile[256];
	char szRes[64];
}sPlaybackFile;

typedef struct tagPlaybackTime
{
	sBM_TIME tStart;
	sBM_TIME tStop;
	char szRes[64];
}sPlaybackTime;

typedef struct tagStrmFile
{

}sStrmFile;

typedef struct tagCodecParam
{

}sCodecParam;

typedef struct tagOsd 
{
	int iX;					// ��ʾ����λ��
	int iY;
	char szOsd[128];
	char szRes[64];			// �����ֶ�
}sOsd;

