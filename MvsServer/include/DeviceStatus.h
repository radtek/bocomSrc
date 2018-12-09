#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include "AbstractSerial.h"
#include "Common.h"
#include "CSeekpaiDB.h"
#include <fcntl.h> 
#include <stdlib.h> 
#include <string> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <linux/kd.h> 
#include <stdio.h>
#include <sys/vfs.h>

using namespace std;

/*
	�ļ�  Devicestatus.h
	���ܣ�����豸���е�״̬�����Ұ��豸��״̬���浽  DEVICE_STATUS ����
	���ߣ�ţ��ɽ
	ʱ�䣺20121115
*/


class DeviceStatus
{
public:

	DeviceStatus();                            // ���캯��

	~DeviceStatus();

	void Init();    // �����߳� 

	int GetMessageAndSave();                  //�õ�һЩ���� Ȼ�����Щ���ݱ��浽 DEVICE_STATUS�������

	int ProgramStart();                       //����ո�������ʱ�� �������һ��

	int OneHourCheckDisk();                   // ��һСʱ��ʱ������´���ʣ��״̬

	int GetDiskFree();                        // �õ�Ӳ�̵�ʣ��ռ�

	int DeleMessage();                        // ֻ����һ���µ�����    
	
	string  Dispose(string &str );            // ��ʽ��ip��ַΪ�ƶ��ĸ�ʽ
		
		
	static int m_saitci_ch_ok;                // ���Ǹ���̬�ı��� 0 ntp Уʱʧ�ܣ� 1 ntp Уʱ�ɹ���

	string m_idAddr;       // ip��ַ�Ƿ����仯
	int m_changeIsok;      // ntp Уʱ�ǳɹ�û�� 
	int m_diskSurplus;       // ���̿ռ�ʣ��


protected:

private:

};

void *  ThreadCheckupDeviceStatus();

extern DeviceStatus g_CheckupDeviceStatus;

#endif