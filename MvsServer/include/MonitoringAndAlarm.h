#ifndef MONITORINGANDALARM_H
#define MONITORINGANDALARM_H

#include <stdio.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <linux/kd.h> 
#include <pthread.h>
#include "XmlParaUtil.h"
#include "AbstractSerial.h"
#include "Common.h"




extern int isChoiceAlarm;

class MonitoringAndAlarm :public AbstractSerial
{
public:
	int m_freq;			/* �������������Ƶ��Hz */ 
	int m_length;		    /* �����ĳ��ȣ���΢��Ϊ��λ*/ 
	int m_reps;           /* �ظ��Ĵ���*/ 
	int m_delay;          /* ���η����ļ����΢��Ϊ��λu*/ 

	//int fd_com;
	int m_fd_alarm;

	pthread_t m_nThreadId ;

	MonitoringAndAlarm(int freq = 440, int length = 200, int reps = 1, int delay = 100 );
	~MonitoringAndAlarm();

	int OpenDev();    // ��ʼ�������豸

	int beginAlarm();  // ��ʼ����

	int endAlarm();    // ��������

	int sendPack();    // ���Ͱ�

	char *pack(char buffer[]);     // ���жԷ�������Ĵ��

	char checkSum(char *sData);    // �Է��������У��ͽ��м���

	char strHex(char temp);        // 

	bool iniAlarmThread();          // �����������߳�


	//���մ�����Ϣ
	void RecData();



protected:

private:

};

void * ThreadMonitoringAndAlarm(void * arg);

extern MonitoringAndAlarm g_AlarmSerial;
#endif
