// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef _COPYTOUSB_H_
#define _COPYTOUSB_H_

#include "Common.h"
#include "global.h"
#include "MysqlTransitionSqliteCyToUSB.h"
#include <sys/stat.h>
#include <sys/mount.h>

#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <linux/kd.h> 


typedef struct { 

	int freq; /* �������������Ƶ�ʣ���λΪHz */ 

	int length;  /* �������ȣ���΢��Ϊ��λ*/ 

	int reps;      /* �ظ��Ĵ���*/ 

	int delay;      /* ���η����������΢��Ϊ��λ*/ 

} beep_parms_t;

//usb������ʶλ
extern volatile bool g_bEndToUsb;

class CopyToUSB
{
public:
	CopyToUSB();
	~CopyToUSB();
	bool Init();
	void RunToCopy();

	int CopyFile(char *copyfrom, char *copyto,UINT32 isize);

	
	bool GetPlatePic();
	
	bool GetVideo();
	bool Close();
	int GetRandCode();

	int CopySql();     //copy ���ݿ�ģ�
	void cpfile(char *spathname,char *tpathname);    // ��һ���ļ����Ƶ���һ��Ŀ¼����

	int CheckDataOutOfDate();
	int ProcDataOutOfLimitDate(int nLimitDays);
	int GetDayTimeSpan(int nCheckDay, struct tm *nowTime, struct tm *oldTime, unsigned long & ulStart, unsigned long & ulEnd);
	//UINT32 GetSpeed(int nChannel,int nRoadId);

	UINT32 GetHaveCopy_Sql();

	//���¼�¼״̬
	bool UpdateRecordStatus(unsigned int uID);
	//���¼�¼״̬
	bool UpdateRecordStatus(unsigned int uMinID,unsigned int uMaxID);
	bool HasUsb();
	bool MountUsb();
	bool IsExistUsb();
	void CopyLog();
protected:
	string strPicPath;
	string strVideoPath;
	UINT32 uPicSize;
	UINT32 uSmallPicSize;
	UINT32 uPicWidth;
	UINT32 uPicHeight;
	UINT32 uViolationType;
	//�߳�ID
	pthread_t m_nThreadId;
	pthread_t m_nThreadLogId;
	pthread_t m_nThread; //�����߳�
	
	#ifdef SQLITE_OK
	MysqlTransitionSqlteCyToUSB * sqlteCp;
	#endif
	
	//��������ֵӳ��
	map<UINT32,UINT32> m_MapSpeed;

	UINT32 haveCopy_sql;
	struct tm m_nCheckTm;

};

//USB����
extern CopyToUSB g_copyToUSB;

#endif

