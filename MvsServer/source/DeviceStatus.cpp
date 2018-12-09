#include "DeviceStatus.h"

DeviceStatus g_CheckupDeviceStatus;


void * ThreadCheckupDeviceStatus(void *)
{
	g_CheckupDeviceStatus.GetMessageAndSave();
}

// ���캯��
DeviceStatus::DeviceStatus()
{

}

//��������
DeviceStatus::~DeviceStatus()
{

}
int DeviceStatus::m_saitci_ch_ok = 0;

// ����һ���߳� 
void DeviceStatus::Init()
{
	pthread_t id;
	//�߳�����
	pthread_attr_t   attr;
	//��ʼ��
	pthread_attr_init(&attr);
	//�����߳�
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	// ������¼�����߳�
	int nret = pthread_create(&id, &attr, ThreadCheckupDeviceStatus, NULL);

}

// �õ�һЩ���� Ȼ�����Щ���ݱ��浽 DEVICE_STATUS�������
int DeviceStatus::GetMessageAndSave()
{

	ProgramStart();                  //��������е�ʱ��ִ����� 
	int iClock = 0;

	string jxdm(Dispose(g_ServerHost));               //�������
	string date = GetTimeCurrent();                   // ʱ��

	char chSql_jxcq[256] = {0};      // ��������  
	sprintf(chSql_jxcq, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'JQCQ', 1, ' '); ", jxdm.c_str(), date.c_str());    // ��������
	g_skpDB.execSQL(string(chSql_jxcq));

	while(!g_bEndThread)                       //  ���״̬�����仯�� ��¼�������仯�򲻼�¼
	{
		
		iClock++;

		if (m_saitci_ch_ok != m_changeIsok)
		{
			char chSql_ntp[256] = {0};
			if (m_changeIsok != 0)
			{
				sprintf(chSql_ntp, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'NTP', 0, ' ');", jxdm.c_str(), date.c_str());
			}
			else
			{
				sprintf(chSql_ntp, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'NTP', 1, ' ');", jxdm.c_str(), date.c_str());
			}
			printf("sql dev -------\%s \n", chSql_ntp);
			g_skpDB.execSQL(string(chSql_ntp));
			m_changeIsok = m_saitci_ch_ok;
		}

		sleep(1);
		if (iClock >= 3600)
		{
			iClock = 0;
			OneHourCheckDisk();
		}
	}
	return 1;
}

int DeviceStatus::OneHourCheckDisk()
{

	if (GetDiskFree() != m_diskSurplus)
	{
		string jxdm;
		jxdm = Dispose(g_ServerHost);                    //�������
		string date = GetTimeCurrent();                  // ʱ��
		char chSql_ypsykl[256] = {0};
		sprintf(chSql_ypsykl, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'YPSYKJ', %d, ' '); ", jxdm.c_str(), date.c_str(), GetDiskFree()); //Ӳ��ʣ��ռ�
		printf("sql dev -------\%s \n", chSql_ypsykl);
		g_skpDB.execSQL(string(chSql_ypsykl));
	}
	
	//ɾ��һ����ǰ�ļ�¼  // ֻ����һ���µļ�¼
	DeleMessage();       
	
	return 1;
}

int DeviceStatus::ProgramStart()
{

	int ntpChangeIsOk;
	string jxdm;
	jxdm = Dispose(g_ServerHost);              //�������
	m_idAddr = jxdm;
	
	m_diskSurplus = GetDiskFree();

	string date = GetTimeCurrent();            // ʱ��

	string spcjk;                              //��Ƶ�ɼ���

	if (g_nClockMode == 0 )                    // ����� ntpУʱ
	{
		ntpChangeIsOk = m_saitci_ch_ok;
	}
	else 
	{
		ntpChangeIsOk = 0;
	}

	
	char  chSql_spcjk[256] = {0};    
	char  chSql_ypsykl[256] = {0};
	char  chSql_jxcq[256] = {0};
	char  chSql_ntp[256] = {0};
	int ntp = 0;
	if (ntpChangeIsOk ==0)
	{
		ntp = 0;
	}
	else
		ntp = 1;

	m_changeIsok = m_saitci_ch_ok ;
	sprintf(chSql_spcjk, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'SPCJK', 1, ' '); ", jxdm.c_str(),date.c_str());  // ��Ƶ�ɼ���
	sprintf(chSql_ypsykl,"INSERT INTO DEVICE_STATUS values('%s', '%s', 'YPSYKJ', %d, ' '); ", jxdm.c_str(), date.c_str(), GetDiskFree()); //Ӳ��ʣ��ռ�
	sprintf(chSql_jxcq, "INSERT INTO DEVICE_STATUS values('%s', '%s', 'JQCQ', 1,  ' '); ", jxdm.c_str(), date.c_str());    // ��������
	sprintf(chSql_ntp,  "INSERT INTO DEVICE_STATUS values('%s', '%s', 'NTP', %d,  ' ');", jxdm.c_str(), date.c_str(),ntp);   //ntpУʱ

	printf("sql dev -------\%s \n", chSql_spcjk);
	printf("sql dev -------\%s \n", chSql_ypsykl);
	printf("sql dev -------\%s \n", chSql_jxcq);
	printf("sql dev -------\%s \n", chSql_ntp);
	g_skpDB.execSQL(string(chSql_spcjk));      
	g_skpDB.execSQL(string(chSql_ypsykl));
	g_skpDB.execSQL(string(chSql_jxcq));
	g_skpDB.execSQL(string(chSql_ntp));


	//ɾ��һ����ǰ�ļ�¼  // ֻ����һ���µļ�¼
	DeleMessage();       
	return 1;
}

int DeviceStatus::DeleMessage()
{
	long ltime = time((time_t *)NULL);
	ltime = ltime - 60*60*24*30;
	string tempTime = GetTime(ltime);
	char delsql[256] = {0};
	sprintf(delsql, "delete from DEVICE_STATUS where JCSJ < '%s' ;", GetTime(ltime).c_str());
	printf("\n del message-------------%s \n", delsql);
	g_skpDB.execSQL(string(delsql));

	return 1;
}

int DeviceStatus::GetDiskFree()
{

	int have =g_sysInfo_ex.fTotalDisk  * (100 - g_sysInfo.fDisk)/100;

	return have;
}

string  DeviceStatus::Dispose(string &str )
{
	int index = str.find(".");                            // 1
	string str1 = str.substr(0, index);                
  
	int end = str.find(".", index+1);                     // 2
	string str2 = str.substr(index+1, end-index-1);  

	index = end;                                        // 3
	end = str.find(".", index+1);
	string str3 = str.substr(index+1, end-index-1);

	string str4 = str.substr(end+1, str.length()-end);      // 4

	printf("%s----%s----%s----%s---- \n",str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());

	int i1 = atoi(str1.c_str());
	int i2 = atoi(str2.c_str());
	int i3 = atoi(str3.c_str());
	int i4 = atoi(str4.c_str()); 
	char buf[30] = {0};
	sprintf(buf, "%03d%03d%03d%03d", i1, i2, i3, i4);
	printf("%s\n", buf);
	return string(buf);
}