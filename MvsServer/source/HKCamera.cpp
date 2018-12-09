// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//
#include "HKCamera.h"
#include "Common.h"
#include <iostream>
#include "HK_SipService.h"
#include <dirent.h>
#include <sys/stat.h>
#include "CSeekpaiDB.h"
#include "CRtspClient.h"
#ifdef H3_PRESET_SERVER
#include "PreSetCommunication.h"
#endif
#ifdef HKCAMERA
#include "AnalyzeDataNewInterface.h"

//H264�ɼ��߳�
void* ThreadHKH264Capture(void* pArg)
{
	//ȡ��ָ��
	CHKCamera* pHDIPCamera = (CHKCamera*)pArg;
	if(pHDIPCamera == NULL)
		return pArg;

	pHDIPCamera->CaptureFrame();

	pthread_exit((void *)0);
	return pArg;
}

//H264�����߳�
void* ThreadHKH264Decode(void* pArg)
{
	//ȡ��ָ��
	CHKCamera* pHDIPCamera = (CHKCamera*)pArg;
	if(pHDIPCamera == NULL)
		return pArg;

	pHDIPCamera->DecodeFrame();
	pthread_exit((void *)0);
	return pArg;
}

//rtcpͨѶ�߳�
void* ThreadHKRtcp(void* pArg)
{
	//ȡ��ָ��
	CHKCamera* pHDIPCamera = (CHKCamera*)pArg;
	if(pHDIPCamera == NULL)
		return pArg;

	pHDIPCamera->DealRtcp();
	pthread_exit((void *)0);
	return pArg;
}

CHKCamera::CHKCamera(int nCameraType)
{
	m_nCameraType = nCameraType;

	m_nWidth = 0;
	m_nHeight = 0;

	m_nMarginX = 0;
	m_nMarginY = 0;
	m_pFrameBuffer = NULL;

	m_nMaxBufferSize = 20;
	m_nDeviceId = 1;
	m_udp_fd = -1;
	m_rtcp_fd = -1;

	m_bRtspMode = 0;
	m_bMulticast = 0;

	pthread_mutex_init(&m_ImageMutex,NULL);
}

CHKCamera::~CHKCamera()
{
	pthread_mutex_destroy(&m_ImageMutex);
}

void CHKCamera::BeginThread()
{
	//�߳�ID
	m_nThreadId = 0;
	//�߳�����
	pthread_attr_t   attr;
	//��ʼ��
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	int nret=pthread_create(&m_nThreadId,NULL,ThreadHKH264Capture,this);
	
	{
		m_nImageThreadId = 0;
		nret=pthread_create(&m_nImageThreadId,NULL,ThreadHKH264Decode,this);

		if(nret!=0)
		{
			Close();
			//ʧ��
			LogError("����h264�ɼ��߳�ʧ��,�޷����вɼ���\r\n");
		}
		
		m_nRtcpThreadId = 0;

			nret=pthread_create(&m_nRtcpThreadId,NULL,ThreadHKRtcp,this);

			if(nret!=0)
			{
				Close();
				//ʧ��
				LogError("����h264�ɼ��߳�ʧ��,�޷����вɼ���\r\n");
			}
	}

	pthread_attr_destroy(&attr);
}

void CHKCamera::Init()
{
	for(int i=0; i< m_nMaxBufferSize; i++)
	{
		m_FrameList[i] = (unsigned char*)calloc(sizeof(yuv_video_buf)+m_nWidth * m_nHeight*3,sizeof(unsigned char));
	}
	m_uSeq = 0;
	m_nPreFieldSeq  = 0;
	m_nCurIndex = 0;
	m_nFirstIndex = 0;
	m_nFrameSize=0;
	m_pFrameBuffer = m_FrameList[0];

	#ifdef H264_DECODE
		LogTrace("mvs.log","m_nWidth = %d, m_nHeight = %d!\n",m_nWidth, m_nHeight);
		m_Decoder.SetVideoSize(m_nWidth, m_nHeight);
		m_Decoder.SetVideoCodeID(0);
		m_Decoder.InitDecode(NULL);
	#endif
#ifdef H3_PRESET_SERVER
		/*char chDevId[10] = {};
		sprintf(chDevId, "%d", m_nDeviceId);
		std::string strDevId(chDevId);*/
		/*if(!g_PreSetCommunication.SendLoginMsgToServer(strDevId))
		{
			LogTrace("H3Preset.log","=========SendLoginMsgToServer fail!\n");
		}
		else
		{
			LogTrace("H3Preset.log","=========SendLoginMsgToServer sucess!\n");
		}*/
		if(!g_PreSetCommunication.SendCodeInfoToServer(m_strPlace))
		{
			LogTrace("H3Preset.log","=========SendCodeInfoToServer fail!\n");
		}
		else
		{
			LogTrace("H3Preset.log","=========SendCodeInfoToServer sucess!\n");
		}

#endif
	
}


bool CHKCamera::Open()
{
	m_bEndCapture = false;
	m_listImage.clear();

	m_uSendSSrc = 0;
	m_uLatSRT = 0;
	m_uRandSSrc = GetRandSSRC();
	m_uSendSeq = 0;

	 m_StreamParser.ClearBuf();

	BeginThread();
	//Init();

	return true;
}

bool CHKCamera::Close()
{
	m_bEndCapture = true;

	close_udp();

	if (m_nThreadId != 0)
	{
		pthread_join(m_nThreadId, NULL);
		m_nThreadId = 0;
	}
	
	close_rtcp();

	if (m_nImageThreadId != 0)
	{
		pthread_join(m_nImageThreadId, NULL);
		m_nImageThreadId = 0;
	}

	if (m_nRtcpThreadId != 0)
	{
		pthread_join(m_nRtcpThreadId, NULL);
		m_nRtcpThreadId = 0;
	}

	pthread_mutex_lock(&m_ImageMutex);
	m_listImage.clear();
	pthread_mutex_unlock(&m_ImageMutex);
	
	string strDestTelNumber = g_skpDB.GetPlaceByCamID(m_nDeviceId);//��ʱ�õص��ʾ������
	g_hk_sipService.TerminateOneCall(strDestTelNumber);

	//����
	pthread_mutex_lock(&m_FrameMutex);
	//�ͷ��ڴ�
	for (int i=0; i<MAX_SIZE; i++)
	{
		if(m_FrameList[i] != NULL)
		{
			free(m_FrameList[i]);
			m_FrameList[i] = NULL;
		}
		m_nFrameSize = 0;
		m_pFrameBuffer = NULL;
	}
	//����
	pthread_mutex_unlock(&m_FrameMutex);

	m_nWidth = 0;
	m_nHeight = 0;

	return true;
}

//���ļ�
bool CHKCamera::OpenFile(const char* strFileName)
{
	m_listImage.clear();

	m_bEndCapture = false;
	
	BeginThread();
	//Init();

	return true;
}


//�������
bool CHKCamera::Control(CAMERA_CONFIG cfg)
{
	
	return false;
}

//�ֶ�����
int CHKCamera::ManualControl(CAMERA_CONFIG  cfg)
{
	return 0;
}

//�Զ�����
int CHKCamera::AutoControl(unsigned int uTimeStamp,float fRate,float fIncrement,bool bDetectCarnum,int nIris,int nEn)
{
	return true;
}

//��ȡ
int CHKCamera::ReadCameraSetting(CAMERA_CONFIG& cfg,bool bConvert)
{
	return true;
}

//reconnect the camera
bool CHKCamera::ReOpen()
{

	if(g_nLoginState != 1)
	{
		return false;
	}

	Close();
	
	if(m_bReadFile)
	{
		OpenFile("");
	}
	else
	{
		Open();
	}

	PullStream();

	LogNormal("CHKCamera::ReOpen");

	return true;
}

//rtcp
void CHKCamera::DealRtcp()
{
	socklen_t addr_len = sizeof(m_rtcp_addr);
	char buf[4096] = {0};	
	while(!m_bEndCapture)
	{
		int nBytes = 0;
		nBytes = recvfrom(m_rtcp_fd,(void*)buf,sizeof(buf),MSG_NOSIGNAL,(struct sockaddr *) &m_rtcp_addr, &addr_len);

		if(nBytes > 0)
		{
			printf("recvfrom rtcp nBytes=%d,%x-%x-%x-%x-%x-%x\n",nBytes,buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
			
			m_uSendSSrc = ntohl(*((unsigned int*)(buf+4)));
			m_uLatSRT = ntohl(*((unsigned int*)(buf+10)));

			//��������
			string strRRSDMsg = GetRRSD();
			
			nBytes = 0;
			nBytes = sendto(m_rtcp_fd,(void*)strRRSDMsg.c_str(),strRRSDMsg.size(),MSG_NOSIGNAL,(struct sockaddr *) &m_rtcp_addr,sizeof(m_rtcp_addr));

			if(nBytes > 0)
			{
				printf("sendto rtcp nBytes=%d,%x-%x-%x-%x-%x-%x\n",nBytes,*(strRRSDMsg.c_str()),*(strRRSDMsg.c_str()+1),*(strRRSDMsg.c_str()+2),*(strRRSDMsg.c_str()+3),*(strRRSDMsg.c_str()+4),*(strRRSDMsg.c_str()+5));
			}
		}

		usleep(1000*1);
	}
}

//��ȡReceive report and source Description
string CHKCamera::GetRRSD(int nType)
{
	string strMsg("");

	char buf[52] = {0};

	////////////////////������Receive report
	buf[0] = 0x81;
	buf[1] = 0xc9;
	buf[2] = 0x00;
	buf[3] = 0x07;
	//ssrc(ÿ�λ滰����Ҫ�ı�)
	memcpy(&buf[4],&m_uRandSSrc,4);

	//sender ssrc(��Ҫ�ӷ��Ͷ��л�ȡ)
	unsigned int uSSrc = htonl(m_uSendSSrc);
	memcpy(&buf[8],&uSSrc,4);
	printf("======buf[8]=%x,buf[9]=%x,buf[10]=%x,buf[11]=%x\n",buf[8],buf[9],buf[10],buf[11]);

	//fraction lost
	buf[12] = 0x0;
	//number of packets lost
	buf[13] = 0x0;
	buf[14] = 0x0;
	buf[15] = 0x0;

	// ���յ�����չ��������к�
	buf[16] = 0x00;
	buf[17] = 0x00;
	
	unsigned short uSeq = htons(m_uSendSeq);
	printf("======uSeq=%d\n",uSeq);
	memcpy(&buf[18],&uSeq,2);

	//����������
	buf[20] = 0x00;
	buf[21] = 0x00;
	buf[22] = 0x00;
	buf[23] = 0x00;
	
	if(nType == 0)
	{
		//���յ�������ԴSSRC_n������RTCP�����߱���(SR)��64λNTPʱ���־���м�32λ������û�н��յ�SR������ֵΪ��
		unsigned int uLatSRT = htonl(m_uLatSRT);
		memcpy(&buf[24],&uLatSRT,4);
		printf("======buf[24]=%x,buf[25]=%x,buf[26]=%x,buf[27]=%x\n",buf[24],buf[25],buf[26],buf[27]);

		//���յ�����SSRC_n��SR�������ʹ˽��ձ����֮�����ʱ����1/65536��Ϊ��λ������δ�յ�����SSRC_n��SR��������ֵΪ��
		unsigned int uDLSR = htonl(6554);
		if(m_uLatSRT <= 0)
		{
			uDLSR = 0;
		}
		memcpy(&buf[28],&uDLSR,4);

		////////////////////������source Description
		buf[32] = 0x81;
		buf[33] = 0xca;
		buf[34] = 0x00;
		buf[35] = 0x04;

		//ssrc(ÿ�λ滰����Ҫ�ı�)
		memcpy(&buf[36],&m_uRandSSrc,4);
		//sdes items
		buf[40] = 0x1;
		buf[41] = 0x6;
		buf[42] = 'b';
		buf[43] = 'o';
		buf[44] = 'c';
		buf[45] = 'o';
		buf[46] = 'm';
		buf[47] = '1';

		strMsg.append(buf,52);
	}
	else
	{
		//����bye����
		buf[32] = 0x81;
		buf[33] = 0xcb;
		buf[34] = 0x00;
		buf[35] = 0x01;
		//ssrc(ÿ�λ滰����Ҫ�ı�)
		memcpy(&buf[36],&m_uRandSSrc,4);

		strMsg.append(buf,40);
	}

	return strMsg;
}

//��ȡSSRC
unsigned int CHKCamera::GetRandSSRC()
{
	srand( (unsigned)time( NULL ) );
	//getpid();
	int nRandCode = 1800 + (int)(1000.0*rand()/(RAND_MAX+1.0));
	return nRandCode;
}

//ֱ��ͨ��rtsp��ȡ��Ƶ
void CHKCamera::RecvRTSP()
{		

}


//h264����
void CHKCamera::DecodeFrame()
{
	bool bFindKeyFrame = false; 

	bool isOk = false;

	while(!m_bEndCapture)
	{
		string strImage("");

		pthread_mutex_lock(&m_ImageMutex);
		  if(m_listImage.size() > 0)
		  {
				strImage = *(m_listImage.begin());
				m_listImage.pop_front();
		  }
		  pthread_mutex_unlock(&m_ImageMutex);

		 if(strImage.size() > 0)
		 { 
			m_StreamParser.InputData((unsigned char*)strImage.c_str(),strImage.size());
		 }

		/*if(!isOk)
		{
			//��ȡ�����Ŀ��
			sStrmInfo si;
			if(m_StreamParser.StrmInfo(si) == 0)
			{
				LogNormal("si.uWidth=%d,si.uHeight=%d,Format=%d\n",si.uWidth,si.uHeight,(int)si.eFormat);

				//��ȡ��Ƶ�����Ϣ
				if(m_nWidth == 0 || m_nHeight == 0)
				{
					m_nWidth = si.uWidth;
					m_nHeight = si.uHeight;

					Init();			
				}

				isOk = true;
			}
			else
			{
				usleep(10*1000);
				continue;
			}
		}*/

		sMediaSample *pMs = NULL;//��ȡ��֡�������
		int iErr = m_StreamParser.NextFrame(&pMs);
		

		string m_strImage("");
		  if(BM_ERR_OK == iErr && pMs)
		  {			
				{
					string strFrame("");
					{
						strFrame.append((char*)pMs->pData,pMs->iDataLen);
						LogTrace("mvs.log", "DecodeFrame strFrame.size=%d,%x-%x-%x-%x-%x\n",strFrame.size(),*((unsigned char*)(strFrame.c_str())),*((unsigned char*)(strFrame.c_str()+1)),*((unsigned char*)(strFrame.c_str()+2)),*((unsigned char*)(strFrame.c_str()+3)),*((unsigned char*)(strFrame.c_str()+4)));
						//LogTrace("HKCamera.log","DecodeFrame strFrame.size=%d,%x-%x-%x-%x-%x\n",strFrame.size(),*((unsigned char*)(strFrame.c_str())),*((unsigned char*)(strFrame.c_str()+1)),*((unsigned char*)(strFrame.c_str()+2)),*((unsigned char*)(strFrame.c_str()+3)),*((unsigned char*)(strFrame.c_str()+4)));

						//if( *((unsigned char*)(strFrame.c_str())) == 0x0  && *((unsigned char*)(strFrame.c_str()+1)) == 0x0 && *((unsigned char*)(strFrame.c_str()+2)) == 0x0 && *((unsigned char*)(strFrame.c_str()+3)) == 0x1)
						{
							int nSize = 0;
							bool bRet = false;
					
			#ifdef H264_DECODE	
							LogTrace("mvs.log", "----------Before DecodeFrame\n");
							bRet = m_Decoder.DecodeFrame((unsigned char*)strFrame.c_str(),strFrame.size(),m_pFrameBuffer+sizeof(yuv_video_buf),nSize);
			#endif
							int nRet = 0;
							if (bRet)
								nRet = 1;
							else
								nRet = 0;
							LogTrace("mvs.log", "=================DecodeFrame size = %d, bRet = %d\n", nSize, nRet);
							if(bRet&& nSize > 0)
							{
									yuv_video_buf header;
									struct timeval tv;
									gettimeofday(&tv,NULL);
									header.ts = tv.tv_sec*1000000+tv.tv_usec;//(int64_t)pts*1000*1000;
									header.uTimestamp = tv.tv_sec;
									header.nFrameRate = 25;
									header.width = m_nWidth;
									header.height = m_nHeight;
									header.nSeq = m_uSeq;
									header.size = nSize;

									memcpy(m_pFrameBuffer,&header,sizeof(yuv_video_buf));

									printf("===============CaptureFrame timenow =%lld,%lld, m_uSeq=%u\n",tv.tv_sec,tv.tv_usec,m_uSeq);
									LogTrace("HKCamera.log","===============CaptureFrame timenow =%lld,%lld, m_uSeq=%u\n",tv.tv_sec,tv.tv_usec,m_uSeq);

									AddFrame(1);
									m_uSeq++;
							}
						}
					}
				}

				m_StreamParser.ReleaseMediaSample(pMs);
		  }
		usleep(1000*1);
	}

	#ifdef H264_DECODE
	m_Decoder.UinitDecode();
	#endif
}

//h264ͼ��ɼ�
void CHKCamera::CaptureFrame()
{
	unsigned char buffer[9000] = {0};
	int nLen = 0;
	socklen_t addr_len = sizeof(m_s_addr);
	
	//FILE* fp = fopen("test.avi","wb");

	//h264ͼ��
	string strImage("");

	bool isOk = false;

	unsigned short uPreSendSeq = 0;

	while(!m_bEndCapture)
	{
			if(m_udp_fd <= 0)
			{
				usleep(1000*1);
				continue;
			}

			 nLen = recvfrom(m_udp_fd, buffer, sizeof(buffer), MSG_NOSIGNAL,(struct sockaddr *) &m_s_addr, &addr_len);

			 if(nLen <= 0)
			 {
				 //usleep(100*1);
				 continue;
			 }

			//printf("CaptureFrame nLen=%d,%x-%x-%x-%x,%x-%x-%x-%x-%x\n",nLen,buffer[0],buffer[1],buffer[2],buffer[3],buffer[12],buffer[13],buffer[14],buffer[15],buffer[16]);
			
			 {
				if( (int) nLen > 12 )
				{	
					//fwrite(buffer+12,1,nLen-12,fp);

					m_uSendSeq = ntohs(*((unsigned short*)(buffer+2)));

					//printf("*****************m_uSendSeq=%lld\n",m_uSendSeq);

					if(uPreSendSeq > 0 && (m_uSendSeq > uPreSendSeq+1))
					{
						//LogError("lost uPreSendSeq=%lld,m_uSendSeq=%lld\n",uPreSendSeq,m_uSendSeq);
					}

					uPreSendSeq =  m_uSendSeq;

					

					if(!isOk)
					{
						m_StreamParser.InputData((unsigned char*)(buffer+12),nLen-12);

						//��ȡ�����Ŀ��
						sStrmInfo si;
						if(m_StreamParser.StrmInfo(si) == 0)
						{
							LogNormal("si.uWidth=%d,si.uHeight=%d,Format=%d\n",si.uWidth,si.uHeight,(int)si.eFormat);

							//��ȡ��Ƶ�����Ϣ
							if(m_nWidth == 0 || m_nHeight == 0)
							{
								m_nWidth = si.uWidth;
								m_nHeight = si.uHeight;
								LogTrace("mvs.log","================m_nWidth = %d, m_nHeight = %d, thread=%lld!\n", m_nWidth, m_nHeight, pthread_self());
								Init();			
							}

							isOk = true;
						}
					}
					else
					{
						strImage.clear();
						strImage.append((char*)(buffer+12),nLen-12);

						pthread_mutex_lock(&m_ImageMutex);
						m_listImage.push_back(strImage);
						pthread_mutex_unlock(&m_ImageMutex);
					}
					
					
				}
			 }
			//usleep(100*1);
	}
		//fclose(fp);

}

//�����豸���
void CHKCamera::SetDeviceID(int nDeviceID)
{
	m_nDeviceId = nDeviceID;

	LogNormal("m_nDeviceId=%d,%d\n",m_nDeviceId,htonl(m_nDeviceId));
}

void CHKCamera::SetPlace(std::string strPlace)
{
	m_strPlace = strPlace;
}

//�鲥��ʽ�������
bool CHKCamera::Connect_Multicast()
{
	close_udp();
	LogNormal("ip=%s,port=%d",m_strCameraIP.c_str(),m_nCameraPort);
    //YUV����
	 struct sockaddr_in addr;
     struct ip_mreq mreq;
	 int nLen = 8192000; //���ջ�������С(8M)

     /* create what looks like an ordinary UDP socket */
     if ((m_udp_fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	 {
	   return false;
     }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(m_nCameraPort);

     int on = 1;
    if(setsockopt(m_udp_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(int)) == -1)
    {
        close_udp();
        perror("setsockopt");
        return false;
    }

    //���ý��ջ�������С
	 if (setsockopt(m_udp_fd,SOL_SOCKET,SO_RCVBUF,&nLen,sizeof(int)) < 0)
	 {
	    close_udp();
	   return false;
     }

    /* use setsockopt() to request that the kernel join a multicast group */
     mreq.imr_multiaddr.s_addr=inet_addr(m_strCameraIP.c_str());
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(m_udp_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0)
	 {
	     close_udp();
	     LogError("�����鲥��ַʧ��!\r\n");
	    return false;
     }

     /* bind to receive address */
     if (bind(m_udp_fd,(struct sockaddr *)&addr,sizeof(addr)) < 0)
	 {
	     close_udp();
		 LogError("YUV��Ƶ�����յ�ַ�޷���!\r\n");
	     return false;
     }

     return true;
}

//UDP ����
bool CHKCamera::connect_udp(int nPort)
{
	close_udp();

	/* connect */
	struct sockaddr_in udp_addr;
	bzero(&udp_addr,sizeof(udp_addr));
	udp_addr.sin_family=AF_INET;
	udp_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	udp_addr.sin_port=htons(nPort);

	// socket
	if ((m_udp_fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		return false;

	}

	int nLen = 8192000; //���ջ�������С(8M)
	//���ý��ջ�������С
	if (setsockopt(m_udp_fd,SOL_SOCKET,SO_RCVBUF,&nLen,sizeof(int)) < 0)
	{
		close_udp();
		return false;
	}

	int on = 1;
	if(setsockopt(m_udp_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(int)) == -1)
	{
		close_udp();
		perror("setsockopt");
		return false;
	}

	if(bind(m_udp_fd, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) == -1)
	{
		close_udp();
		LogError("H264��Ƶ�����յ�ַ�޷���!\r\n");
		return false;
	}
	printf("start receive date\n");
	return true;
}

//�ر�udp����
void CHKCamera::close_udp()
{
	if(m_udp_fd!=-1)
	{
		shutdown(m_udp_fd,2);
		close(m_udp_fd);
		m_udp_fd = -1;
	}
}


//UDP ����
bool CHKCamera::connect_rtcp(int nPort)
{
	close_rtcp();

	/* connect */
	struct sockaddr_in udp_addr;
	bzero(&udp_addr,sizeof(udp_addr));
	udp_addr.sin_family=AF_INET;
	udp_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	udp_addr.sin_port=htons(nPort);

	// socket
	if ((m_rtcp_fd=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		return false;

	}

	int nLen = 8192000; //���ջ�������С(8M)
	//���ý��ջ�������С
	if (setsockopt(m_rtcp_fd,SOL_SOCKET,SO_RCVBUF,&nLen,sizeof(int)) < 0)
	{
		close_rtcp();
		return false;
	}

	int on = 1;
	if(setsockopt(m_rtcp_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(int)) == -1)
	{
		close_rtcp();
		perror("setsockopt");
		return false;
	}

	if(bind(m_rtcp_fd, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) == -1)
	{
		close_rtcp();
		LogError("H264��Ƶ�����յ�ַ�޷���!\r\n");
		return false;
	}
	return true;
}

//�ر�udp����
void CHKCamera::close_rtcp()
{
	if(m_rtcp_fd!=-1)
	{
		string strMsg = GetRRSD(1);
		sendto(m_rtcp_fd,(void*)strMsg.c_str(),strMsg.size(),MSG_NOSIGNAL,(struct sockaddr *) &m_rtcp_addr,sizeof(m_rtcp_addr));

		shutdown(m_rtcp_fd,2);
		close(m_rtcp_fd);
		m_rtcp_fd = -1;
	}
}


//��ȡ��Ƶ��
void CHKCamera::PullStream()
{
	pthread_mutex_lock(&m_ImageMutex);
	m_listImage.clear();
	pthread_mutex_unlock(&m_ImageMutex);

	//ѭ���ȴ���Ӧ
	int sport = 0;
	string strHost("");
	int nCount = 0;

	//����˿�
	string strDestTelNumber = g_skpDB.GetPlaceByCamID(m_nDeviceId);//��ʱ�õص��ʾ������
	
	LogNormal("strDestTelNumber=%s",strDestTelNumber.c_str());

	int dport = GetRandPort();

	if(m_nVideoType == 0)
	{
		m_uRandSSrc = GetRandSSRC();
		g_hk_sipService.CreateInviteCall(strDestTelNumber,dport,m_uRandSSrc);
		
		while( ((strHost.size() <= 0) || (sport <= 0)) &&(!m_bEndCapture) )
		{
			sport = g_hk_sipService.GetSPortBasedOnCameraCode(strDestTelNumber);
			strHost = g_hk_sipService.GetHostBaseOnCameraCode(strDestTelNumber);
			LogTrace("mvs.log","sport = %d, strHost = %s\n", sport, strHost.c_str());
			if (sport == 0 || strHost.size() == 0)
			{
				if (nCount == 5)
				{
					cerr<<"1111111111111111five second over strDestTelNumber:"<<strDestTelNumber<<endl;
					dport++;
					m_uRandSSrc++;
					LogNormal("repeat CreateInviteCall dport=%d\n",dport);
					g_hk_sipService.CreateInviteCall(strDestTelNumber,dport,m_uRandSSrc);
					nCount = 0;
				}
				
			}

			sleep(1);
			nCount += 1;
		}
	}
	else
	{
		g_hk_sipService.CreateHistoryInviteCall(strDestTelNumber,dport,m_vod_info.uBeginTime,m_vod_info.uEndTime);


		while( ((strHost.size() <= 0) || (sport <= 0)) &&(!m_bEndCapture) )
		{
			sport = g_hk_sipService.GetSPortBasedOnCameraCode(strDestTelNumber);
			strHost = g_hk_sipService.GetHostBaseOnCameraCode(strDestTelNumber);

			if (sport == 0 || strHost.size() == 0)
			{
				if (nCount == 5)
				{
					cerr<<"1111111111111111five second over strDestTelNumber:"<<strDestTelNumber<<endl;
					g_hk_sipService.CreateHistoryInviteCall(strDestTelNumber,dport,m_vod_info.uBeginTime,m_vod_info.uEndTime);
					nCount = 0;
				}
				
			}

			sleep(1);
			nCount += 1;
		}
	}

	LogNormal("strHost.c_str()=%s,sport=%d,dport=%d",strHost.c_str(),sport,dport);
		
	cerr<<"PullStream strDestTelNumber"<<strDestTelNumber.c_str()<<endl;
	cerr<<"PullStream strHost"<<strHost.c_str()<<endl;
	cerr<<"PullStream sport"<<sport<<endl;
	cerr<<"PullStream dport"<<dport<<endl;

	/* ���öԷ���ַ�Ͷ˿���Ϣ */
	m_s_addr.sin_family = AF_INET;
	m_s_addr.sin_port = htons(sport);
	m_s_addr.sin_addr.s_addr = inet_addr(strHost.c_str());

	if(!connect_udp(dport))
	{
		LogError("�޷����������udp����\r\n");
	}
	
	m_rtcp_addr.sin_family = AF_INET;
	m_rtcp_addr.sin_port = htons(sport+1);
	m_rtcp_addr.sin_addr.s_addr = inet_addr(strHost.c_str());
	if(!connect_rtcp(dport+1))
	{
		LogError("�޷����������udp����\r\n");
	}
}

//��ȡ����˿�
int CHKCamera::GetRandPort()
{
	//srand( (unsigned)time( NULL ) );
	getpid();
	int nRandCode = 1800 + (int)(1000.0*rand()/(RAND_MAX+1.0));
	return nRandCode;
}

#endif
