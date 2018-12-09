#include "GpsChangeTimeSerial.h"

GpsChangeTimeSerial g_GpsChangeTime; 

void * ThreadGpsChanageTimeSerial(void *)
{
	g_GpsChangeTime.RecData();
}
GpsChangeTimeSerial::GpsChangeTimeSerial()
{
	fd_com = -1;
}
GpsChangeTimeSerial::~GpsChangeTimeSerial()
{

}

bool GpsChangeTimeSerial::OpenDev()
{
	fd_com = open_port(g_GpsComSetting.nComPort, g_GpsComSetting.nBaud, g_GpsComSetting.nDataBits, g_GpsComSetting.nStopBits, g_GpsComSetting.nParity);

	//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++gps\n");
	if(fd_com == -1)
	{
		return false;
	}
	else
	{
		BeginThread();
		return true;
	}
}

void GpsChangeTimeSerial::BeginThread()
{
	//printf("===========CGpsSerial::BeginThread()=========\n");

	//线程id
	pthread_t id;
	//线程属性
	pthread_attr_t   attr;
	//初始化
	pthread_attr_init(&attr);
	//分离线程
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	//启动记录发送线程

	int nret=pthread_create(&id,&attr,ThreadGpsChanageTimeSerial,NULL);
	if(nret!=0) //失败
	{
		printf("启动串口发送线程失败!\r\n");
	}
	else
	{
		printf("启动串口发送线程成功!\r\n");
	}
	pthread_attr_destroy(&attr);
}

void GpsChangeTimeSerial::RecData()
{

	int count_i = 0;
	while (!g_bEndThread)
	{
		char ch;
		char buff[10] = {0};
		char timeHead[7] = "GPRMC,";
		char strHaveTime[1024] = {0};
		while(1)                             // 进入循环 不断的接受发过来的信息   
		{
			int r_size = read(fd_com, &ch, 1);
			if (r_size == 0)                //如果没有读到 结束本次循环进行下次循环
			{
				usleep(100);
				continue;
			}

			char beginMatching[7] = {0};

			if (ch == 0x24 )          // 如果读到 $ 符号的时候
			{
				//printf("---------------------------$-----------------\n");
				int index = 0;
				while(1)                   // 在读6个字符  
				{
					r_size = read(fd_com, &ch, 1);
					if (r_size == 0)
					{
						continue;
					}
					beginMatching[index++] = ch;
					if ( index == 6 )
					{
						//printf("读到的6个字符是%s\n",beginMatching);
						break;
					}
				}

				if ( strcmp(timeHead, beginMatching) == 0)   // 如果是 "GPRMC," 
				{
					count_i++;
					//printf("比较相同\n");
					memset(strHaveTime, '\0', sizeof strHaveTime);
					int index = 0;
					while(1)
					{
						r_size = read(fd_com, &ch, 1);
						if (r_size == 0)
						{
							continue;
						}
						if (ch == 0xA)                 // 如果有回车 都结束
						{

						//	printf("%s\n", strHaveTime);
							if (count_i == 120)
							{
								long timeSec  = gettimefromString(strHaveTime, strlen(strHaveTime));
								count_i = 0;
							}
							
							break; 
						}
						strHaveTime[index++] = ch;

					}
				}
			}
			 
		}
		
	}
}

long GpsChangeTimeSerial::gettimefromString(char str[], int l)
{

	char hour[3]  = {0};
	char minute[3] = {0};
	char second[3] = {0};
	char day[3]    = {0};
	char month[3]  = {0};
	char year[5]   = {0};
	int num = 0;
	for (int a = 0; a < l; a++)
	{
		if (a == 0)
		{
			hour[0]  = str[a++];
			hour[1]  = str[a++];
			minute[0] = str[a++];
			minute[1] = str[a++];
			second[0] = str[a++];
			second[1] = str[a++];
		}
		if (str[a] == ',')
		{ 
			num++;
		}
		if (num == 8)
		{
			a++;
			day[0] = str[a++];
			day[1] = str[a++];
			month[0] = str[a++];
			month[1] = str[a++];
			year[0] = '2';
			year[1] = '0';
			year[2] = str[a++];
			year[3] = str[a++];
			break;
		}
	}
	
	if (atoi(year) > 2025 || atoi(year) < 2012 )
	{
		return 0;
	}
	struct tm newTime;
	newTime.tm_year = atoi(year) - 1900;
	newTime.tm_mon =  atoi(month) -1;
	newTime.tm_mday = atoi(day);
	newTime.tm_hour = atoi(hour);
	newTime.tm_min =  atoi(minute);
	newTime.tm_sec =  atoi(second);

	long uTime = mktime(&newTime);
	uTime += 8*60*60;

	string strDataPath;
	strDataPath = "/home/road/dzjc/";
	if (IsDataDisk())
	{
		strDataPath = "/detectdata/dzjc/";
	}

	if(access(strDataPath.c_str(),0) != 0) //目录不存在
	{
		mkdir(strDataPath.c_str(),S_IRWXU|S_IRGRP|S_IROTH|S_IXOTH);
	}

	strDataPath += "tsyn/";

	if(access(strDataPath.c_str(),0) != 0) //目录不存在
	{
		mkdir(strDataPath.c_str(),S_IRWXU|S_IRGRP|S_IROTH|S_IXOTH);
	}

	FILE* pf = NULL;
	char strFileName[256] = {0};
	std::string strNowTime = GetTimeCurrent();
	sprintf(strFileName,"%s/%s_GPS_%s%s.txt",strDataPath.c_str(),g_strDetectorID.c_str(),GetTime(MakeTime(strNowTime),9).c_str(),GetTime(MakeTime(strNowTime),14).c_str());

	char strFileBuf[1024] = {0};
	sprintf(strFileBuf,"LocalTime\t\tFlag\tGPSTime\t\t\tGPSLocal\t\tOffSet\n");
	bool bFirst = false;
	if(access(strFileName,F_OK) != 0)
	{
		pf = fopen(strFileName,"a+");
		fwrite(strFileBuf,1,strlen(strFileBuf),pf);
		fclose(pf);
		bFirst = true;
	}
	std::string strLocalTime = GetTimeCurrent();
	pf = fopen(strFileName,"a+");

	timeval timer;
	timer.tv_sec = uTime;
	timer.tv_usec = 0;
	if (settimeofday(&timer, NULL) == 0)
	{
		std::string strGpsTime = GetTime(uTime,0);
		printf("change time ok \n");

		std::string strTime = GetTime(uTime);
		sprintf(strFileBuf,"%s\ttrue\t%s\t%s\t%d\n",strLocalTime.c_str(),strGpsTime.c_str(),strTime.c_str(),MakeTime(strLocalTime)-MakeTime(strGpsTime));

		LogNormal("通过GPS校时成功%s",strTime.c_str());
		system("hwclock --systohc");
	}
	else
	{
		sprintf(strFileBuf,"%s\tfalse\n",strLocalTime.c_str());
	}
	if (pf)
	{
		string strHour = GetTime(MakeTime(strLocalTime),5);
		if (m_nHour.compare(strHour.c_str()) != 0 || bFirst == true)
		{
			m_nHour = strHour;
			fwrite(strFileBuf,1,strlen(strFileBuf),pf);
		}
		fclose(pf);
	}

	return uTime;
}