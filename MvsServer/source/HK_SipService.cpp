// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#ifdef HK_SIP_SERVICE_OPEN

#include "Common.h"
#include "HK_SipService.h"
#include "XmlParser.h"
#include <iostream>


#define BUFSIZE 4096

#define MSG_IS_DO(msg)      (MSG_IS_REQUEST(msg) && \
	0==strcmp((msg)->sip_method,"DO"))

//ͨѶ����
CHKSipService g_hk_sipService;


typedef struct _ClassAndEvent
{
	CHKSipService* hk;
	eXosip_event_t* je;
	_ClassAndEvent()
	{
		hk = NULL;
		je = NULL;
	}
}ClassAndEvent;



//����
CHKSipService::CHKSipService()
{
	m_bregFlag = false;
	m_sourceCall = "";
	m_destCall = "";
	m_destIP = "";
	m_server = "";
	m_destTelNumber = "";
	m_InviteCount = 0;

	//m_failReqCount = 0; //������������ʧ�ܴ���
	m_cid = 0;
	m_did = 0;
	m_registerId = -1;

	m_sipserverTelNumber = "";

	m_serverCall = "";

	m_EndThread = false;

	string m_destRtspIP = "";//�Է�Rtsp��������IP
	string m_transport = ""; //����������Э��
	string m_destRtspPort = "";//���������Ķ˿� 
	m_bLogOnServer = false;

	m_CamerCodeAndListFileMap.clear();
	pthread_mutex_init(&m_CamerCodeAndListFileMap_mutex,NULL);

	m_CameraCodeAndHisUrlMap.clear();
	pthread_mutex_init(&m_CameraCodeAndHisUrlMap_mutex,NULL);

	pthread_mutex_init(&m_map_mutex,NULL);
	pthread_mutex_init(&m_mapIpPortID_mutex,NULL);
}

//����
CHKSipService::~CHKSipService()
{
	pthread_mutex_destroy(&m_map_mutex);
	pthread_mutex_destroy(&m_mapIpPortID_mutex);
	pthread_mutex_destroy(&m_CamerCodeAndListFileMap_mutex);
	pthread_mutex_destroy(&m_CameraCodeAndHisUrlMap_mutex);
}


//��������DO��Ϣ�岢����
void CHKSipService::CreateDORequest()
{
	if (g_nLoginState != 1)
	{
		cerr<<"CreateDORequest m_registerId < 0"<<endl;
		return;
	}
	////////////////////
	cerr<<"aaaaaaaaaaaa"<<endl;
	osip_message_t *message = NULL;
	eXosip_message_build_request (&message, "DO",m_serverCall.c_str(), m_sourceCall.c_str(), NULL);
	char buf[BUFSIZE] = {0};
	snprintf (buf, BUFSIZE,"<?xml version=\"1.0\"?>\r\n" 
		"<Action>\r\n" 
		"<Notify>\r\n" 
		"\t<Variable>KeepAlive</Variable>\r\n" 
		"</Notify>\r\n" 
		"</Action>\r\n");
	osip_message_set_content_type (message, "Application/DDCP");
	osip_message_set_body (message, buf, strlen (buf));

	eXosip_message_send_request (message);

	cerr<<"bbbbbbbbbbbbbbbb"<<endl;
	//////////////////
}

void* ThreadKeepAlive(void* pArg)
{
	CHKSipService* hk = (CHKSipService*)pArg;
	while(!g_bEndThread)
	{
		if(hk->m_bLogOnServer)
		{
			sleep(30);

			//////////////////
			hk->CreateDORequest();
			////////////////////
			//hk->CreateKeepAliveInviteCall();
			continue;

		}
		usleep(100);
	}
	pthread_exit((void *)0);
	return pArg;
}

void* ThreadLoginHKServer(void* pArg)
{
	//ȡ��ָ��
	CHKSipService* phk = (CHKSipService*)pArg;
	if(phk == NULL) return 0;

	phk->LoginHKServer();

	pthread_exit((void *)0);
	return pArg;
}

void* ListenMessage(void* pArg)
{
	CHKSipService* hk = (CHKSipService*)pArg;
	while(!g_bEndThread)
	{
		hk->sipService();
		usleep(100);
	}
	pthread_exit((void *)0);
	return pArg;
}


bool CHKSipService::CreateListenMessageThread()//����������Ϣ�߳�
{
	//�߳�id
	pthread_t id;
	//�߳�����
	pthread_attr_t   attr;
	//��ʼ��
	pthread_attr_init(&attr);
	//�����߳�
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//������Ϣ����߳�
	int nret=pthread_create(&id,&attr,ListenMessage,this);
	//�ɹ�
	if(nret!=0)
	{
		//ʧ��
		cerr<<"CreateListenMessageThread error"<<endl;
		LogError("������Ϣ����߳�ʧ��,�����޷�����!\r\n");
		g_bEndThread = true;
		return false;
	}
	cerr<<"CreateListenMessageThread success333333333"<<endl;
	/*nret=pthread_create(&id,&attr,ThreadLoginHKServer,this);
	//�ɹ�
	if(nret!=0)
	{
		//ʧ��
		cerr<<"ThreadLoginHKServer error"<<endl;
		LogError("������½�߳�ʧ��,�����޷�����!\r\n");
		g_bEndThread = true;
		return false;
	}*/
	//nret = pthread_create(&id,&attr,ThreadKeepAlive,this);
	//if(nret!=0)
	//{
	//	//ʧ��
	//	cerr<<"ThreadLoginHKServer error"<<endl;
	//	LogError("�������������߳�ʧ��,�����޷�����!\r\n");
	//	g_bEndThread = true;
	//	return false;
	//}
	pthread_attr_destroy(&attr);

	return true;
}

//ָ����ַ���������ʷͼ���ļ��б�Ȳ�ѯ��������������Ϣ�巢�ͣ��Ի�ȡ��ʷͼ���ļ��б�
void CHKSipService::CreateQueryDoMsg(string nStrDestTelNumber,long HisBeginTime,long HisEndTime)
{
	cerr<<"in CreateQueryDoMsg nStrDestTelNumber:"<<nStrDestTelNumber<<endl;
	osip_message_t *message = NULL;
	char buf[BUFSIZE] = {0};
	int i;

	string strHisBeginTime = "";
	string strHisEndTime = "";

	ChangTimeFormat(strHisBeginTime,HisBeginTime);
	ChangTimeFormat(strHisEndTime,HisEndTime);

	int nPort = 7100;

	if(g_monitorHostInfo.uMonitorPort > 0)
	{
		nPort = g_monitorHostInfo.uMonitorPort;
	}

	char bufTmp[256] = {0};
	sprintf(bufTmp,":%d",nPort);
	string strPort(bufTmp);

	string nDestCall("");

	nDestCall = "sip:" + nStrDestTelNumber + "@" + m_strSipServerIp + strPort;

	eXosip_lock ();
	//i = eXosip_call_build_request (did,"DO", &mdo);
	i = eXosip_message_build_request(&message, "DO",nDestCall.c_str(), m_sourceCall.c_str(), NULL);

	cerr<<"123432 i:"<<i<<endl;
	if (i == 0)
	{
		string PriTmp = "%00%02";
		snprintf (buf, BUFSIZE, "<?xml version=\"1.0\"?>\r\n" 
			"<Action>\r\n" 
			"<Query>\r\n"
			"\t<Variable>FileList</Variable>\r\n" 
			"\t<Privilege>%s</Privilege>\r\n"
			"\t< FileType >1</ FileType >\r\n"
			"\t<FromIndex>1</FromIndex>\r\n" 
			"\t<ToIndex>10</ToIndex>\r\n" 
			"\t<BeginTime>%s</BeginTime>\r\n" 
			"\t<EndTime>%s</EndTime>\r\n"
			"</Query>\r\n" 
			"</Action>\rn",PriTmp.c_str(),strHisBeginTime.c_str(),strHisEndTime.c_str());//Queryһ���е����ж�δ֪��PrivilegeȨ�޹�����
		osip_message_set_content_type (message, "Application/DDCP");
		osip_message_set_body (message, buf, strlen (buf));
		i = eXosip_message_send_request (message);

		cerr<<"12312321111 i:"<<i<<endl;
	}
	eXosip_unlock ();
}

//������ʱ��ת����ʽ
void CHKSipService::ChangTimeFormat(string& mTime,long ltime)
{
	char buf[128];
	memset(buf, 0, sizeof(buf));
	struct tm *newTime,timenow;
	newTime = &timenow;
	localtime_r( &ltime,newTime );

	sprintf(buf, "%4d%02d%02dT%02d%02d%02dZ", newTime->tm_year+1900, newTime->tm_mon+1, newTime->tm_mday, newTime->tm_hour, newTime->tm_min, newTime->tm_sec);
	cerr<<"buftime:"<<buf<<endl;
	mTime = buf;
	return;
}

//����Do��Ϣ�岢���ͣ������Է��Ļ�����Ϣ����URL
void CHKSipService::CreateGetUrlDoMsg(string nStrDestTelNumber,long HisBeginTime,long HisEndTime,string fileName)
{
	cerr<<"in CreateGetUrlDoMsg nStrDestTelNumber:"<<nStrDestTelNumber<<endl;
	osip_message_t *message = NULL;
	char buf[BUFSIZE] = {0};
	int i;

	string strHisBeginTime = "";
	string strHisEndTime = "";

	ChangTimeFormat(strHisBeginTime,HisBeginTime);
	ChangTimeFormat(strHisEndTime,HisEndTime);

	int nPort = 7100;

	if(g_monitorHostInfo.uMonitorPort > 0)
	{
		nPort = g_monitorHostInfo.uMonitorPort;
	}

	char bufTmp[256] = {0};
	sprintf(bufTmp,":%d",nPort);
	string strPort(bufTmp);

	string nDestCall("");

	nDestCall = "sip:" + nStrDestTelNumber + "@" + m_strSipServerIp + strPort;


	eXosip_lock ();
	i = eXosip_message_build_request(&message, "DO",nDestCall.c_str(), m_sourceCall.c_str(), NULL);

	cerr<<"1444 i:"<<i<<endl;
	if (i == 0)
	{
		string PriTmp = "%00%02";
		snprintf (buf, BUFSIZE, "<?xml version=\"1.0\"?>\r\n" 
				"<Action>\r\n" 
				"\t<Variable>VODByRTSP</Variable>\r\n" 
				"\t<Privilege>%s</Privilege>\r\n" 
				"\t<FileType>2</FileType>\r\n" 
				"\t<Name>%s</Name>\r\n" 
				"\t<BeginTime>%s </BeginTime>\r\n" 
				"\t<EndTime>%s </EndTime>\r\n" 
				"\t<MaxBitrate>100</MaxBitrate>\r\n"     
				"</Action>\r\n",PriTmp.c_str(),fileName.c_str(),strHisBeginTime.c_str(),strHisEndTime.c_str()); 
		osip_message_set_content_type (message, "Application/DDCP");
		osip_message_set_body (message, buf, strlen (buf));
		i = eXosip_message_send_request (message);

		cerr<<"1555 i:"<<i<<endl;
	}
	eXosip_unlock ();
}

//��������DO��Ϣ�岢����
void CHKSipService::CreateKeepAliveDoMsg(int did,osip_message_t *mdo)
{
	char buf[BUFSIZE] = {0};
	int i;
	eXosip_lock ();
	i = eXosip_call_build_request (did,"DO", &mdo);

	cerr<<"1444 i:"<<i<<endl;
	if (i == 0)
	{
		snprintf (buf, BUFSIZE, "<?xml version=\"1.0\"?>\r\n" 
			"<Action>\r\n" 
			"<Notify>\r\n" 
			"\t<Variable>KeepAlive</Variable>\r\n" 
			"</Notify>\r\n" 
			"</Action>\r\n" ); 
		osip_message_set_content_type (mdo, "Application/DDCP");
		osip_message_set_body (mdo, buf, strlen (buf));
		i = eXosip_call_send_request (did, mdo);

		cerr<<"1555 i:"<<i<<endl;
	}
	eXosip_unlock ();
}

//ע���ʼ��
bool CHKSipService::Init()
{
	m_mapSipID.clear();
	m_mapIpPortID.clear();
	cerr<<"in CHKSipService::Init "<<endl;
	/*if(loadSipCfg() == false)
	{
		LogError("����SIP���������ļ�ʧ��!\n");
		cerr<<"Sip: LoadCfg error!"<<endl;
		return false;
	}*/

	// ��ʼ�� sip
	int ret = eXosip_init ();
	if (ret != 0)
	{
		cerr << "\n\t--> Can't initialize eXosip!\n"; 
		return false;
	}
	else
	{
		cerr << "\n\t--> eXosip_init successfully!\n"; 
	}

	int nPort = 7100;
	

	if(g_monitorHostInfo.uMonitorPort > 0)
	{
		nPort = g_monitorHostInfo.uMonitorPort;
	}

	//����sip
	ret = eXosip_listen_addr (IPPROTO_UDP, NULL, 5060, AF_INET, 0); 
	if (ret != 0) 
	{
		eXosip_quit ();
		cerr << "\n\t--> eXosip_listen_addr error! Couldn't initialize transport layer!\n";
		return false;
	}

	string strSourcTelNumber(g_monitorHostInfo.chSipClientCode);
	m_sourcTelNumber = strSourcTelNumber;

	string strSipServerIp(g_monitorHostInfo.chMonitorHost);
	m_strSipServerIp =  strSipServerIp;

	string strServerTelNumber(g_monitorHostInfo.chSipServerCode);
	m_sipserverTelNumber = strServerTelNumber;

	char buf[256] = {0};
	sprintf(buf,":%d",nPort);
	string strPort(buf);

	m_sourceCall = "sip:" + m_sourcTelNumber + "@" + g_ServerHost + ":5060";
	m_server = "sip:" + m_strSipServerIp /*+ strPort*/;
	//m_destCall = "sip:" + m_destTelNumber + "@" + m_strSipServerIp + strPort;
	m_serverCall = "sip:" + m_sipserverTelNumber + "@" + m_strSipServerIp + strPort;
	
	cerr<<"======Init() m_sourceCall:"<<m_sourceCall.c_str()<<endl;
	cerr<<"=========Init() m_serverCall:"<<m_serverCall.c_str()<<endl;

	////�߳�id
	//pthread_t id;
	////�߳�����
	//pthread_attr_t   attr;
	////��ʼ��
	//pthread_attr_init(&attr);
	////�����߳�
	//pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//int nret = pthread_create(&id,&attr,ThreadLoginHKServer,this);
	////�ɹ�
	//if(nret!=0)
	//{
	//	//ʧ��
	//	cerr<<"ThreadLoginHKServer error"<<endl;
	//	LogError("������½�߳�ʧ��,�����޷�����!\r\n");
	//	g_bEndThread = true;
	//	return false;
	//}

	return CreateListenMessageThread();
}

//�ͷ�
bool CHKSipService::UnInit()
{
	
	//ע��SIP����
	TerminateCall();
	eXosip_lock ();

	eXosip_quit ();
	eXosip_unlock ();

	m_EndThread = true;
	return true;
}


//���������ļ�
bool CHKSipService::loadSipCfg()
{
	cerr<<"loadSipCfg() in"<<endl;

	XMLNode xml, setting, subSetting, temp;
	string xmlFile = "./HKSipServiceCfg.xml";

	//�ж�xml�ļ��Ƿ����
	/*if(access(xmlFile.c_str(),F_OK) != 0)//������
	{
		cerr<<10<<endl;

		xml = XMLNode::createXMLTopNode("Setting");
		setting = xml.addChild("SipServerSeting");

		temp = setting.addChild("SipServerIp");
		temp.addText("");

		temp = setting.addChild("SipServerTelNumber");
		temp.addText("");


		temp = setting.addChild("SourceTelNumber");
		temp.addText("");

		temp = setting.addChild("TelPassword");
		temp.addText("");

		temp = setting.addChild("DestIP");
		temp.addText("");

		temp = setting.addChild("DestTelNumber");
		temp.addText("");


		
		if(!xml.writeToFile(xmlFile.c_str()))
		{
			LogError("���������ļ�ģ��ʧ��!\r\n");
		}
		else
		{
			LogError("û�������ļ�! ����Ĭ�������ļ�./HKSipServiceCfg.xml\n");
		}
		cerr<<12<<endl;
		return false;
	}
	else*/
	{
		cerr<<20<<endl;
		xml = XMLNode::parseFile(xmlFile.c_str());
		setting = xml.getChildNode("Setting");
		if (!setting.isEmpty())
		{
			cerr<<21<<endl;
			subSetting = setting.getChildNode("SipServerSeting");
			if (!subSetting.isEmpty())
			{
				cerr<<22<<endl;
				temp = subSetting.getChildNode("SipServerTelNumber");
				if (!temp.isEmpty())
				{
					m_sipserverTelNumber = temp.getText();
					cerr<<"in loadSipCfg() m_sipserverTelNumber:"<<m_sipserverTelNumber<<endl;
				}
				else
				{
					cerr<<"in loadSipCfg() m_sipserverTelNumber is Nothing"<<endl;
					return false;
				}

				temp = subSetting.getChildNode("SipServerIp");
				if (!temp.isEmpty())
				{
					m_strSipServerIp = temp.getText();
					cerr<<"in loadSipCfg() m_strSipServerIp:"<<m_strSipServerIp<<endl;
				}
				else
				{
					cerr<<"in loadSipCfg() m_strSipServerIp is Nothing"<<endl;
					return false;
				}

				temp = subSetting.getChildNode("SourceTelNumber");
				if (!temp.isEmpty())
				{	
					m_sourcTelNumber = temp.getText();
					cerr<<"in loadSipCfg() m_sourcTelNumber:"<<m_sourcTelNumber<<endl;
				}
				else
				{
					cerr<<"in loadSipCfg() m_sourcTelNumber is Nothing"<<endl;
					return false;
				}
				temp = subSetting.getChildNode("TelPassword");
				if (!temp.isEmpty() && temp.getText()!=NULL)
				{
					m_strPassword = temp.getText();
					cerr<<"in loadSipCfg() m_strPassword:"<<m_strPassword<<endl;
				}
				else
				{
					m_strPassword = "";
					cerr<<"in loadSipCfg() m_strPassword is Nothing"<<endl;
				}
				temp = subSetting.getChildNode("DestIP");
				if (!temp.isEmpty())
				{
					m_destIP = temp.getText();
					cerr<<"in loadSipCfg() m_destIP:"<<m_destIP<<endl;
				}
				else
				{
					cerr<<"in loadSipCfg() m_destIP is Nothing"<<endl;
					return false;
				}
				temp = subSetting.getChildNode("DestTelNumber");
				if (!temp.isEmpty())
				{
					m_destTelNumber = temp.getText();
					cerr<<"in loadSipCfg() m_destTelNumber:"<<m_destTelNumber<<endl;
				}
				else
				{
					cerr<<"in loadSipCfg() m_destTelNumber is Nothing"<<endl;
					return false;
				}
				cerr<<23<<endl;
			}
			else
			{
				cerr<<"in loadSipCfg() SipServerSeting is Nothing"<<endl;
				return false;
			}
		}
		else
		{
			cerr<<"in loadSipCfg() Setting is Nothing"<<endl;
			return false;
		}
	}
	cerr<<"loadSipCfg() out"<<endl;
	return true;
}

//�Խ��յ���Ϣ��������Ӧ�Ĵ���
void CHKSipService::sipService()
{
    eXosip_event_t *je = NULL; 
    osip_message_t *invite = NULL; 
    osip_message_t *answer = NULL; 
	osip_message_t *ack = NULL; 

	osip_message_t *message = NULL;
	
	char buf[BUFSIZE] = {0}; 
	int i;

	//�����������Ƿ�����Ϣ���� 
	je = eXosip_event_wait (0, 50);


	// Э��ջ���д����,��������δ֪ 
	eXosip_lock (); 
	eXosip_default_action (je); 
	eXosip_automatic_refresh (); 
	eXosip_unlock ();

	//osip_event_t *et = osip_new_outgoing_sipmessage(m_reg);
	//cerr<<"eXosip_default_action return="<<eXosip_default_action(et);
	/*cerr<<endl;
	cerr<<"tid="<<et->tid<<endl;
	cerr<<"did="<<et->did<<endl;*/

	//cerr<<"je->cid:"<<je->cid;
	//cerr<<"je->did:"<<je->did;
	//cerr<<"je->tid:"<<je->tid;
	//int ret;
	//eXosip_lock ();
	//eXosip_unlock ();
	
	if (je == NULL) // û�н��յ���Ϣ������ 
	{ 
		return; 
	} 

	cerr<<"\n-->je->type:"<<je->type<<endl;
	switch (je->type) 
	{
	case EXOSIP_MESSAGE_NEW:
		 cerr<<"EXOSIP_MESSAGE_NEW"<<endl;
		 //////////
		 if (MSG_IS_REGISTER (je->request))
		 {
			 eXosip_lock ();
			 i = eXosip_message_build_answer (je->tid, 200, &answer);
			 cerr<<"EXOSIP_MESSAGE_NEW i = "<<i<<endl;
			 i = eXosip_message_send_answer (je->tid, 200, answer);
			 cerr<<"EXOSIP_MESSAGE_NEW 1111 i = "<<i<<endl;
			 g_nLoginState = 1;
			 //if (m_RecvRegisterCount == 1)
			 //{
				//osip_message_t *message = NULL;
				//i = eXosip_message_build_request(&message,"MESSAGE",m_serverCall.c_str(),m_sourceCall.c_str(),NULL);
				//if (i != 0)
				//{
				//	cerr<<"eXosip_message_build_request i="<<i<<endl;
				//	break;
				//}
				//else
				//{
				//	
				//	 char buf[BUFSIZE] = {0};
				//	 // ���չ�����Ҫ�ظ� OK ��Ϣ
				//	 eXosip_message_build_answer (je->tid, 200, &answer);
				//	 snprintf (buf, BUFSIZE, "<?xml version=\"1.0\"?>\r\n" 
				//		 "<Query>\r\n" 
				//		 "<CmdType>Catalog</CmdType>\r\n" 
				//		 "<SN>21</SN>\r\n" 
				//		 "<DeviceID>%s</DeviceID>\r\n" 
				//		 "</Query>\r\n",g_monitorHostInfo.chSipServerCode); 
				//	 osip_message_set_content_type (answer, "Application/MANSCDP+xml");
				//	 osip_message_set_body (answer, buf, strlen (buf));
				//	i = eXosip_message_send_request(message);
				//	if (i != 0)
				//	{
				//		cerr<<"eXosip_message_send_request i="<<i<<endl;
				//		break;
				//	}
				//}
				//

			 //}
			 eXosip_unlock ();
			 break;
		 }
		 

		 if(MSG_IS_NOTIFY(je->request))
		 {
			 //g_nLoginState = 1;
			 printf("==========================================receive one NOTIFY MSG\n");
			 {
				 osip_body_t *body;
				 osip_message_get_body (je->request, 0, &body); 
		//		 cerr << "EXOSIP_MESSAGE_NEW I get the msg is: " << body->body << endl;
			}
			if (g_nLoginState == 1)
			{
				char buf[BUFSIZE] = {0};
				eXosip_lock ();
				// ���չ�����Ҫ�ظ� OK ��Ϣ
				eXosip_message_build_answer (je->tid, 200, &answer);
				snprintf (buf, BUFSIZE, "<?xml version=\"1.0\"?>\r\n" 
					"<Response>\r\n" 
					"<Variable>Catalog</Variable>\r\n" 
					"<Result>0</Result>\r\n" 
					"</Response>\r\n"); 
				osip_message_set_content_type (answer, "Application/DDCP");
				osip_message_set_body (answer, buf, strlen (buf));
				eXosip_message_send_answer (je->tid, 200, answer);

				eXosip_unlock ();
				cerr<<"+++++++++++++++++NOTIFY"<<endl;
			}
			break;
		 }

		 if (MSG_IS_MESSAGE(je->request))
		 {
			 if (g_nLoginState == 1)
			 {
				 eXosip_lock ();
				 cerr<<"+++++++++++++++++MSG_IS_MESSAGE"<<endl;
				 i = eXosip_message_build_answer (je->tid, 200, &answer);
				 cerr<<"+++++++++++++++++MSG_IS_MESSAGE eXosip_message_build_answer i = "<<i<<endl;
				 i = eXosip_message_send_answer (je->tid, 200, answer);
				 cerr<<"+++++++++++++++++MSG_IS_MESSAGE eXosip_message_send_answer i = "<<i<<endl;
				 eXosip_unlock ();
			 }
			 break;
		 }



	case EXOSIP_CALL_PROCEEDING:
		 cerr<<"proceeding"<<endl;
		 break;

	//case EXOSIP_CALL_ANSWERED:
	case EXOSIP_CALL_ANSWERED:
		CreateInviteProcThread(je);
		break;

	case EXOSIP_MESSAGE_ANSWERED:
		cerr<<"EXOSIP_MESSAGE_ANSWERED"<<endl;
		/*eXosip_lock ();
		osip_cseq_t* ncseq = NULL;
		if (osip_cseq_init(&ncseq) != 0)
		{
			cerr<<"EXOSIP_MESSAGE_ANSWERED=====osip_cseq_init error"<<endl;
		}
		else
		{
			cerr<<"EXOSIP_MESSAGE_ANSWERED1111111111"<<endl;
			ncseq = osip_message_get_cseq (je->response);
			cerr<<"EXOSIP_MESSAGE_ANSWERED2222222222222"<<endl;
			string strMethod("");
			strMethod = osip_cseq_get_method (ncseq);
			if (strMethod.size() <= 0)
			{
				cerr<<"EXOSIP_MESSAGE_ANSWERED Get No method"<<endl;
			}
			else
			{
				cerr<<"++++++++++++++++++++++EXOSIP_MESSAGE_ANSWERED method:"<<strMethod<<endl;
				if (strcmp(strMethod.c_str(),"MESSAGE") == 0)
				{
					int i = eXosip_message_build_answer(je->tid,200,&answer);
					if (i != 0)
					{
						cerr<<"EXOSIP_MESSAGE_ANSWERED MESSAGE eXosip_message_build_answer error i:%d"<<i<<endl;
					}
					else
					{
						i = eXosip_message_send_answer(je->tid,200,answer);
						if (i != 0)
						{
							cerr<<"EXOSIP_MESSAGE_ANSWERED MESSAGE eXosip_message_send_answer error i:%d"<<i<<endl;
						}
					}
				}
				else
				{
					
				}
			}
		}
		if (ncseq != NULL)
		{
			osip_cseq_free(ncseq);
			ncseq = NULL;
		}
		eXosip_unlock ();*/
		//osip_body_t *body;
		//osip_message_get_body (je->response, 0, &body);
		////osip_message_get_body (je->request, 0, &body);
		//if(body != NULL)
		//{	
		//	if(body->body != NULL)
		//	{
		//		cout << "000000000the body is " << body->body << endl;

		//		if(strstr(body->body,"<Variable>FileList") != NULL)
		//		{
		//			cerr<<"URL To CameraCode:"<<je->response->to->url->username<<endl;
		//			string nStrCameraCode = je->response->to->url->username;
		//			GetFileList(nStrCameraCode,body);

		//			break;

		//		}
		//		else
		//		{
		//			cerr<<"not found <Variable>FileList"<<endl;
		//		}

		//		if(strstr(body->body,"<Variable>VODByRTSP") != NULL)
		//		{
		//			cerr<<"1111URL To CameraCode:"<<je->response->to->url->username<<endl;
		//			string nStrCameraCode = je->response->to->url->username;
		//			GetHisVideoUrl(nStrCameraCode,body);
		//			break;
		//		}
		//		else
		//		{
		//			cerr<<"not found <Variable>VODByRTSP"<<endl;
		//		}
		//	}
		//	else
		//	{
		//		cerr<<"EXOSIP_MESSAGE_ANSWERED body->body is NULL"<<endl;
		//		break;
		//	}
		//	
		//}
		//else
		//{
		//	cerr<<"EXOSIP_MESSAGE_ANSWERED body is NULL"<<endl;
		//}
		//
		
		

		break;

	case EXOSIP_CALL_REQUESTFAILURE:
		cerr<<"\n\t EXOSIP_CALL_REQUESTFAILURE je->response->status_code="<<je->response->status_code<<endl;
		break;

	case EXOSIP_CALL_MESSAGE_ANSWERED:
		cerr<<"EXOSIP_CALL_MESSAGE_ANSWERED"<<endl;
		break;
	case EXOSIP_CALL_RELEASED:
		cerr<<"EXOSIP_CALL_RELEASED"<<endl;
		break;

	default: 
		cerr << "\n\t--> Received unknown msg! Code= " <<je->type<< endl; 
	}

	//cerr<<"CHKSipService::sipService() out"<<endl;
}


//�����������ļ��ŵ��ڴ�
void CHKSipService::SaveFileToMemory(char* tmp,FileList* tmpFile,int i,int& j,std::list<FileList>& nListFile)
{
	cerr<<"in SaveFileToMemory"<<endl;
	if(tmp == NULL || tmpFile == NULL || i == 0)
	{
		cerr<<"1111111 out of SaveFileToMemory"<<endl;
		return;
	}
	else
	{

		char* Tmp;

		Tmp =strstr(tmp,"</Item>");

		cerr<<"Tmp %d:"<<j<<Tmp;
		char *tmp1 = NULL;
		tmp1 = strstr(tmp,"<Item>");
		if(tmp1 == NULL)
		{
			cerr<<"SaveFileToMemory tmp NULL"<<endl;
			return;
		}
		else
		{
			cerr<<"SaveFileToMemory tmp1"<<tmp1<<endl;
			tmp1 = tmp1 + 6;
			char *tmp2 = NULL;
			tmp2 = strstr(tmp1,"<Name>");

			char *tmp3 = NULL;
			tmp3 = strstr(tmp1,"<BeginTime>");

			char *tmp4 = NULL;
			tmp4 = strstr(tmp1,"<EndTime>");

			char *tmp5 = NULL;
			tmp5 = strstr(tmp1,"<FileSize>");



			tmp2 = tmp2 + 6;;
			tmpFile[j].FileName = strtok(tmp2,"<");
			cerr<<j<<"tmpFile.FileName"<<tmpFile[j].FileName<<endl;
			cerr<<"11111111"<<endl;

			tmp3 = tmp3 + 11;
			cerr<<"22222222"<<endl;
			tmpFile[j].FileBeginTime = strtok(tmp3,"<");
			cerr<<j<<"tmpFile.FileBeginTime "<<tmpFile[j].FileBeginTime<<endl;


			tmp4 = tmp4 + 9;
			tmpFile[j].FileEndTime = strtok(tmp4,"<");
			cerr<<j<<"tmpFile.FileEndTime "<<tmpFile[j].FileEndTime<<endl;


			tmp5 = tmp5 + 10;
			tmpFile[j].FileSize = strtok(tmp5,"<");
			cerr<<j<<"tmpFile.FileSize "<<tmpFile[j].FileSize<<endl;
			
			nListFile.push_back(tmpFile[j]);
			cerr<<"nListFile.size()"<<nListFile.size()<<endl;



			tmp1 = NULL;
			tmp2 = NULL;
			tmp3 = NULL;
			tmp4 = NULL;
			tmp5 = NULL;
			tmp = Tmp;

			j += 1;

			SaveFileToMemory(tmp,tmpFile,i-1,j,nListFile);

		}
		cerr<<"2222222 out of SaveFileToMemory"<<endl;
		return;
	}
}


//����Ϣ���л�ȡ�ļ��б�
void CHKSipService::GetFileList(string nStrCameraCode,osip_body_t *body)
{
	if(body->body != NULL)
	{
		char *tmp1 = NULL;
		string fileNum = "";
		//int FileNum = 0;
		int i;
		tmp1 = strstr(body->body,"<RealFileNum>");//�ҵ���<RealFileNum>��ʼ���ַ���
		cerr<<"tmp1:"<<tmp1<<endl;
		if(tmp1 != NULL)
		{


			char *tmp2 = NULL;
			tmp2 = tmp1 + 13;
			cerr<<"tmp2:"<<tmp2<<endl;

			char *tmp3 = NULL;
			tmp3 = strstr(body->body,"<Item>");
			if(tmp3 == NULL)
			{
				cerr<<"GetFileList <Item> NULL"<<endl;
				return;
			}

			if(tmp2 != NULL)
			{
				fileNum = strtok(tmp2,"<");
				if(fileNum.size() > 0)
				{
					cerr<<"fileNum:"<<fileNum<<endl;
					//FileNum = atoi(fileNum.c_str());
					int nFileNumber = 0;
					nFileNumber = atoi(fileNum.c_str());
					//m_FileNumber = atoi(fileNum.c_str());
					cerr<<"The Number of files in the FileList gained is "<<nFileNumber<<endl;

					FileList* nfileList = NULL;

					nfileList = new FileList[nFileNumber];

					if(nfileList != NULL)
					{
						int j = 0;
						std::list<FileList> nListFile;
						nListFile.clear();
						SaveFileToMemory(tmp3,nfileList,nFileNumber,j,nListFile);
						pthread_mutex_lock(&m_CamerCodeAndListFileMap_mutex);
						m_CamerCodeAndListFileMap.insert(make_pair(nStrCameraCode,nListFile));
						pthread_mutex_unlock(&m_CamerCodeAndListFileMap_mutex);
					}
					else
					{
						cerr<<"malloc nfileList error"<<endl;
					}
					
					if (nfileList != NULL)
					{
						delete [] nfileList;
					}



				}
				else
				{
					cerr<<"fileNum unkown:"<<endl;
					return;

				}
			}

			return;


		}
		else
		{
			cerr<<"not Found <RealFileNum>"<<endl;
			return;
		}
	}
	else
	{
		cerr<<"osip_body nothing\n"<<endl;
		return;
	}
}


//�ӻ�õ���Ϣ���н�����ʷ��Ƶ�ļ���URL
void CHKSipService::GetHisVideoUrl(string nStrCamerCode,osip_body_t *body)
{
	cerr<<"in GetHisVideoUrl CamerCode:"<<nStrCamerCode<<endl;
	if(body->body != NULL)
	{
		char *tmp = NULL;
		tmp = strstr(body->body,"<Playurl>");
		if(tmp != NULL)
		{
			char *tmp1 = NULL;
			tmp1 = tmp + 9;

			string nHkHisVideoUrl("");

			nHkHisVideoUrl = strtok(tmp1,"<");
			cerr<<"CameraCode"<<nStrCamerCode<<"nHkHisVideoUrl:"<<nHkHisVideoUrl<<endl;

			pthread_mutex_lock(&m_CameraCodeAndHisUrlMap_mutex);
			m_CameraCodeAndHisUrlMap.insert(make_pair(nStrCamerCode,nHkHisVideoUrl));
			pthread_mutex_unlock(&m_CameraCodeAndHisUrlMap_mutex);

		}
		else
		{
			cerr<<"GetHisVideoUrl tmp is NULL"<<endl;
			return;
		}
	}
	else
	{
		cerr<<"GetHisVideoUrl osip_body_t get nothing"<<endl;
		return;
	}
}

void CHKSipService::TerminateCall()//�������лỰ
{
	eXosip_lock (); 
	pthread_mutex_lock(&m_map_mutex);
	mapSipID::iterator it = m_mapSipID.begin();
	for(;it != m_mapSipID.end();)
	{
		eXosip_call_terminate((it->second).cid, (it->second).did);
		m_mapSipID.erase(it++);
	}
	pthread_mutex_unlock(&m_map_mutex);

	eXosip_unlock ();
}

void CHKSipService::TerminateOneCall(string CameraAddressCode)//��������ĵ�ַ��������Ự
{
	pthread_mutex_lock(&m_map_mutex);
	mapSipID::iterator it = m_mapSipID.find(CameraAddressCode);
	if(it == m_mapSipID.end())
	{
		cerr<<"in TerminateOneCall not found CameraAddressCode"<<CameraAddressCode<<endl;
	}
	else
	{
		if((it->second).cid > 0 && (it->second).did >0)
		{
			eXosip_lock();
			eXosip_call_terminate((it->second).cid,(it->second).did);

			(it->second).VideoServerIp = "";
			(it->second).Port = "";
			
			cerr<<"EEEEEEE"<<endl;
			eXosip_unlock();
		}
	}
	pthread_mutex_unlock(&m_map_mutex);
}

int CHKSipService::AddSipIDtoMap(char* CameraAddressCode,int cid,int did)
{
	if(CameraAddressCode == NULL)
	{
		cerr<<"CameraAddressCode is NULL"<<endl;
		return 0;
	}
	cerr<<"in AddSipIDtoMap CameraAddressCode:"<<CameraAddressCode<<endl;
	cerr<<"in AddSipIDtoMap cid:"<<cid<<endl;
	cerr<<"in AddSipIDtoMap did:"<<did<<endl;
	string strDestTelNumber = CameraAddressCode;
	pthread_mutex_lock(&m_map_mutex);
	mapSipID::iterator it = m_mapSipID.find(strDestTelNumber);
	if(it == m_mapSipID.end())
	{
		cerr<<"not found "<<CameraAddressCode<<" in m_mapSipID"<<endl;
		pthread_mutex_unlock(&m_map_mutex);
		return 0;
		//SipID idSip;
		//m_mapSipID.insert(mapSipID::value_type(strDestTelNumber,idSip));
	}
	else
	{
		cerr<<"before change (it->second).cid"<<(it->second).cid<<endl;
		cerr<<"before change (it->second).did"<<(it->second).did<<endl;
		(it->second).cid = cid;
		(it->second).did = did;
		pthread_mutex_unlock(&m_map_mutex);
		return 1;
	}

}

void CHKSipService::ProcForInvite200OK(eXosip_event_t *je)
{
	osip_message_t *ack = NULL;
	cerr<<"connect established"<<endl;
	sdp_message_t *remote_sdp = NULL;

	if (MSG_IS_INVITE (je->request))
	{

		/////////////2011-6-11
		cerr<<"MSG_IS_INVITE"<<endl;
		cerr<<"0000000000"<<endl;
		//cerr<<"url->string:"<<je->response->from->url->string<<endl;
		cerr<<"url->scheme:"<<je->response->from->url->scheme<<endl;
		////cerr<<"displayname:"<<je->response->from->displayname<<endl;
		cerr<<"111111111"<<endl;
		cerr<<"url->username:"<<je->response->to->url->username<<endl;
		cerr<<"je->cid:"<<je->cid<<endl;
		cerr<<"je->did:"<<je->did<<endl;
		cerr<<"2222222222"<<endl;
		this->AddSipIDtoMap(je->response->to->url->username,je->cid,je->did);
		
		remote_sdp = eXosip_get_remote_sdp (je->did);
		//osip_message_get_body (je->response, 0, &body);

		eXosip_lock (); 
		cerr<<"EXOSIP_CALL_ANSWERED 33333333"<<endl;
		this->GetRtspIPandPort(je->response->to->url->username,remote_sdp);
		eXosip_call_build_ack (je->did, &ack); 

		cerr<<"ack->req_uri->host:"<<ack->req_uri->host<<endl;
		cerr<<"ack->sip_method:"<<ack->sip_method<<endl;
		cerr<<"je->response->to->url->host"<<je->response->to->url->host<<endl;
		string SipServerIp = je->response->to->url->host;
		memset(ack->req_uri->host,0,strlen(ack->req_uri->host));
		memcpy(ack->req_uri->host,SipServerIp.c_str(),SipServerIp.size());

		cerr<<"ack->req_uri->host:"<<ack->req_uri->host<<endl;

		eXosip_call_send_ack (je->did, ack);
		eXosip_unlock ();

	}
	
	return;

}

bool CHKSipService::CreateInviteProcThread(eXosip_event_t *je)//Invite���󷢳����յ�200OK�󴴽��̡߳�
{

	this->ProcForInvite200OK(je);

	return true;

}

int CHKSipService::CallTerminate(int cid, int did)//�����Ự
{
	return 0;
}

////�Խ��յ���Ϣ��������Ӧ�Ĵ���
//bool CHKSipService::mvConnOrLinkTest()
//{
//    if (!g_bEndThread)
//    {
//		sipService();
//    }
//
//    return true;
//}

//��INVITE����Ϣ��ת����Xml��ʽ
void CHKSipService::CreateInviteToXml(string& xmlstr)
{
		cerr<<"CreateInviteToXml() in"<<endl;

		XMLNode xml, temp;

		cerr<<10<<endl;
		xml = XMLNode::createXMLTopNode("Action");

		temp = xml.addChild("Variable");
		temp.addText("RealMedia");//ʵʱ���ͼ��

		temp = xml.addChild("Privilege");
		temp.addText("");//�����û���Ȩ�޹�����δ֪����

		temp = xml.addChild("Format");
		temp.addText("4CIF CIF QCIF");//Դ������Ԫ֧�ֵ�������ʽ

		temp = xml.addChild("Video");
		temp.addText("H.264 MPEG-4");//��Ƶ��������

		temp = xml.addChild("Audio");
		temp.addText("G.711");//��Ƶ��������

		temp = xml.addChild("MaxBitrate");
		temp.addText("800");//�������

		temp = xml.addChild("Socket");
		string strTmp = g_ServerHost + " UDP" + " 2350";//�˿�δ֪
		temp.addText(strTmp.c_str());//��Ƶ���յ��û���IP��ַ+����Э��+�˿ں�

		//xmlstr = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
		xmlstr = "<?xml version=\"1.0\"?>\n";
		int nSize;
		XMLSTR strData = xml.createXMLString(1, &nSize);
		xmlstr.append(strData, nSize);

	
		cerr<<"CreateInviteToXml() out"<<endl;
		return;
}

//��Ŀ��������Ԫ����INVITE������ʷ��Ƶ
bool CHKSipService::CreateHistoryInviteCall(string strDestTelNumber,int dport,UINT32 uBeginTime,UINT32 uEndTime)
{
	cerr<<"in CreateHistoryInviteCall strDestTelNumber:"<<strDestTelNumber<<",myRecvport:"<<dport<<endl;
	pthread_mutex_lock(&m_map_mutex);
	mapSipID::iterator it = m_mapSipID.find(strDestTelNumber);
	if(it == m_mapSipID.end())
	{
		SipID idSip;
		m_mapSipID.insert(mapSipID::value_type(strDestTelNumber,idSip));
	}
	pthread_mutex_unlock(&m_map_mutex);

	int nPort = 7100;

	if(g_monitorHostInfo.uMonitorPort > 0)
	{
		nPort = g_monitorHostInfo.uMonitorPort;
	}

	char buf[256] = {0};
	sprintf(buf,":%d",nPort);
	string strPort(buf);


	string nStrDestCall("");
	nStrDestCall = "sip:" + strDestTelNumber + "@" + m_strSipServerIp + strPort;

	TerminateOneCall(strDestTelNumber);
	
	{

		m_destRtspIP = "";
		m_destRtspPort = "";

		osip_message_t *invite = NULL;
		int i;
		char chSubjectBuf[128] = {0};
		sprintf(chSubjectBuf,"%s:11001,%s:1000",strDestTelNumber.c_str(),g_monitorHostInfo.chSipClientCode);
		i = eXosip_call_build_initial_invite(&invite,nStrDestCall.c_str(),m_sourceCall.c_str(),NULL,chSubjectBuf); 
		if (i != 0) 
		{ 
			cerr << "\n --> Intial INVITE failed! <-- \n"<<endl; 
			return false;
		}

		char buf[BUFSIZE];
		snprintf (buf, BUFSIZE,
			"v=0\n"
			"o=%s 0 0 IN IP4 %s\n"
			"s=Playback\n"
			"u=%s:3"
			"c=IN IP4 %s\n"
			"t=%u %u\n"
			"m=video %d RTP/AVP 96\n"
			"a=recvonly\n"
			"a=rtpmap:96 PS/90000\n",g_monitorHostInfo.chSipClientCode, g_ServerHost.c_str(), strDestTelNumber.c_str(),g_ServerHost.c_str(),uBeginTime,uEndTime,dport);
	
		osip_message_set_body (invite, buf, strlen(buf)); 
		osip_message_set_content_type (invite, "application/sdp");
		eXosip_lock (); 
		i = eXosip_call_send_initial_invite (invite); 
		cerr<<"CreateHistoryInviteCall after eXosip_call_send_initial_invite i="<<i<<endl;
		eXosip_unlock ();
		return true;

	}
}

//��Ŀ��������Ԫ����INVITE����
bool CHKSipService::CreateInviteCall(string strDestTelNumber,int dport,unsigned int uRandSSrc)
{
	cerr<<"in CreateInviteCall strDestTelNumber:"<<strDestTelNumber<<",myRecvport:"<<dport<<endl;
	pthread_mutex_lock(&m_map_mutex);
	mapSipID::iterator it = m_mapSipID.find(strDestTelNumber);
	if(it == m_mapSipID.end())
	{
		SipID idSip;
		m_mapSipID.insert(mapSipID::value_type(strDestTelNumber,idSip));
	}
	pthread_mutex_unlock(&m_map_mutex);

	int nPort = 7100;

	if(g_monitorHostInfo.uMonitorPort > 0)
	{
		nPort = g_monitorHostInfo.uMonitorPort;
	}

	char buf[256] = {0};
	sprintf(buf,":%d",nPort);
	string strPort(buf);

	//m_destTelNumber = strDestTelNumber;

	string nStrDestCall("");
	nStrDestCall = "sip:" + strDestTelNumber + "@" + m_strSipServerIp + strPort;

	/////////////
	TerminateOneCall(strDestTelNumber);
	/////////////
	//TerminateCall();
	//if(!m_bregFlag)
	//{
	//	cerr<<"not register success\n"<<endl;
	//	return false;
	//}
	//else
	{

		m_destRtspIP = "";
		m_destRtspPort = "";

		osip_message_t *invite = NULL;
		int i;
		char chSubjectBuf[128] = {0};
		sprintf(chSubjectBuf,"%s:01001,%s:1000",strDestTelNumber.c_str(),g_monitorHostInfo.chSipClientCode);
		i = eXosip_call_build_initial_invite(&invite,nStrDestCall.c_str(),m_sourceCall.c_str(),NULL,chSubjectBuf); 
		if (i != 0) 
		{ 
			cerr << "\n --> Intial INVITE failed! <-- \n"<<endl; 
			return false;
		}

		/*string strSubjectName = "Subject";
		char subjectBuf[256] = {0};
		sprintf(subjectBuf,"%s:%s,%s:%s",strDestTelNumber.c_str(),g_strSenderMediaCode,g_monitorHostInfo.chSipClientCode,g_strRecverMediaCode.c_str());
		i = osip_uri_param_add(invite->req_uri->url_params,strSubjectName.c_str(),subjectBuf);
		if (i != 0)
		{
			cerr<<"CreateInviteCall===set Subject error,strDestTelNumber:"<<strDestTelNumber.c_str()<<" SendMediaCode:"<<g_strSenderMediaCode.c_str()<<endl;
			cerr<<"SourceTelNumber:"<<g_monitorHostInfo.chSipClientCode<<" RecevierCode:"<<g_strRecverMediaCode.c_str()<<endl;
			return false;
		}*/
		char buf[BUFSIZE];
		string str_Value_F;
		str_Value_F = "v//2//4//25//1//a//1//8//1";
		snprintf (buf, BUFSIZE,
			"v=0\n"
			"o=%s 0 0 IN IP4 %s\n"
			"s=Play\n"
			"c=IN IP4 %s\n"
			"t=0 0\n"
			"m=video %d RTP/AVP 96\n"
			"a=recvonly\n"
			"a=rtpmap:96 PS/90000\n"
			"y=%u\n"
			"f=%s\n",g_monitorHostInfo.chSipClientCode, g_ServerHost.c_str(), g_ServerHost.c_str(),dport,uRandSSrc,str_Value_F.c_str());
	
		osip_message_set_body (invite, buf, strlen(buf)); 
		osip_message_set_content_type (invite, "application/sdp");
		/////////////////
		eXosip_lock (); 
		i = eXosip_call_send_initial_invite (invite); 
		cerr<<"after eXosip_call_send_initial_invite i="<<i<<endl;
		eXosip_unlock ();
		return true;

	}
}

bool CHKSipService::CreateKeepAliveInviteCall() //��������������������

{
	
	/*if(!m_bregFlag)
	{
		cerr<<"not register success\n"<<endl;
		return false;
	}
	else*/
	{

		m_destRtspIP = "";
		m_destRtspPort = "";

		osip_message_t *invite = NULL;
		int i;
		i = eXosip_call_build_initial_invite(&invite,m_serverCall.c_str(),m_sourceCall.c_str(),NULL,"This is a call for a KeepAlive conversation"); 
		if (i != 0) 
		{ 
			cerr << "\n --> CreateKeepAliveInviteCall Intial INVITE failed! <-- \n"<<endl; 
			return false;
		}

		////////////////
		eXosip_lock (); 
		i = eXosip_call_send_initial_invite (invite); 
		eXosip_unlock ();

		


		return true;

	}

}


//void CHKSipService::GetRtspIPandPort(char *CameraAddressCode,osip_body_t *body)//��body�н���ʵʱrtsp��IP�Ͷ˿�
//{
//	if(CameraAddressCode == NULL)
//	{
//		cerr<<"in GetRtspIPandPort CameraAddressCode is NULL"<<endl;
//		return;
//	}
//	if(body->body != NULL)
//	{
//		cerr<<"in GetRtspIPandPort CameraAddressCode:"<<CameraAddressCode<<endl;
//		string tmpDestRtspIP;
//		string tmpTransport;
//		string tmpPort;
//		char *tmp1 = NULL;
//		tmp1 = strstr(body->body,"<ReceiveSocket>");//�ҵ���<Socket>��ʼ���ַ���
//		cerr<<"tmp1:"<<tmp1<<endl;
//		if(tmp1 != NULL)
//		{
//			char *tmp2 = NULL;
//			tmp2 = tmp1 + 15;
//			cerr<<"tmp2:"<<tmp2<<endl;
//			if(tmp2 != NULL)
//			{
//				tmpDestRtspIP = strtok(tmp2," ");
//				if(tmpDestRtspIP.size() > 0)
//				{
//					cerr<<"tmpDestRtspIP:"<<tmpDestRtspIP<<endl;
//					
//				}
//				else
//				{
//					cerr<<"tmpDestRtspIP unkown:"<<tmpDestRtspIP<<endl;
//					return;
//
//				}
//				
//				tmpTransport = strtok(NULL," ");
//				if(tmpTransport.size() > 0)
//				{
//					cerr<<"tmpTransport:"<<tmpTransport<<endl;
//				}
//				else
//				{
//					cerr<<"tmpTransport unknown:"<<endl;
//					return;
//				}
//
//				tmpPort = strtok(NULL,"<");
//				if(tmpPort.size() > 0)
//				{
//					cerr<<"tmpPort:"<<tmpPort<<endl;
//					cerr<<"tmpPort:"<<atoi(tmpPort.c_str())<<endl;
//				}
//				else
//				{
//					cerr<<"tmpPort"<<endl;
//					return;
//				}
//
//				cerr<<"in GetRtspIPandPort 1111111111"<<endl;
//				/*VideoServerIpAndPort tmpStruct;
//				tmpStruct.VideoServerIp = tmpDestRtspIP;
//				tmpStruct.Transport = tmpTransport;
//				tmpStruct.Port = tmpPort;*/
//				string strCode = CameraAddressCode;
//				/*pthread_mutex_lock(&m_mapIpPortID_mutex);
//				m_mapIpPortID.insert(mapIpAndPortID::value_type(strCode,tmpStruct));
//				pthread_mutex_unlock(&m_mapIpPortID_mutex);*/
//				pthread_mutex_lock(&m_map_mutex);
//				mapSipID::iterator it = m_mapSipID.find(strCode);
//				if(it != m_mapSipID.end())
//				{
//					(it->second).VideoServerIp = tmpDestRtspIP;
//					(it->second).Transport = tmpTransport;
//					(it->second).Port = tmpPort;
//				}
//				pthread_mutex_unlock(&m_map_mutex);
//				cerr<<"in GetRtspIPandPort 2222222"<<endl;
//			}
//		}
//		else
//		{
//			cerr<<"not Found <ReceiveSocket>"<<endl;
//			return;
//		}
//	}
//	else
//	{
//		cerr<<"osip_body nothing\n"<<endl;
//		return;
//	}
//}

void CHKSipService::GetRtspIPandPort(char *CameraAddressCode,sdp_message_t *sdp)//��sdp�н���ʵʱrtsp��IP�Ͷ˿�
{
	if(CameraAddressCode == NULL)
	{
		cerr<<"in GetRtspIPandPort CameraAddressCode is NULL"<<endl;
		return;
	}
	if (sdp != NULL)
	{
		cerr<<"GetRtspIPandPort=====SDP INFO:"<<endl
			<<"o_addrtype="<<sdp->o_addrtype<<endl
			<<"o_addr="<<sdp->o_addr<<endl
			<<"c_addr="<<sdp->c_connection->c_addr<<endl;

		string strRtspIp("");
		string strRtspPort("");
		string strCode = CameraAddressCode;
		//����client��ip���˿�
		strRtspIp = sdp->o_addr;

		sdp_media_t* media = eXosip_get_video_media(sdp);
		if (media != NULL)
		{
			cerr<<"m_port="<<media->m_port<<endl;
			strRtspPort = media->m_port;
		}
		pthread_mutex_lock(&m_map_mutex);
		mapSipID::iterator it = m_mapSipID.find(strCode);
		if(it != m_mapSipID.end())
		{
			//(it->second).VideoServerIp = strRtspIp;
			//(it->second).VideoServerIp = sdp->c_connection->c_addr;
			(it->second).VideoServerIp = g_monitorHostInfo.chMonitorHost;
			(it->second).Port = strRtspPort;
			
		}
		pthread_mutex_unlock(&m_map_mutex);
	}
	else
	{
		cerr<<"sdp has nothing\n"<<endl;
		return;
	}
}

int CHKSipService::GetSPort()//��ȡ���������ķ���ʵʱ��Ƶ���Ķ˿�
{
	if(m_destRtspPort.size() > 0)
	{
		return atoi(m_destRtspPort.c_str());
	}
	else
	{
		return 0;
	}
	
}
string CHKSipService::GetHost() //��ȡ���������ķ���ʵʱ��Ƶ���Ļ���IP
{
	return m_destRtspIP;
}


int CHKSipService::GetSPortBasedOnCameraCode(string CameraCode)//��ȡ���������ķ���ʵʱ��Ƶ���Ķ˿�
{
	cerr<<"in GetSPortBasedOnCameraCode mapSipId size:"<<m_mapSipID.size()<<endl;;

	int nPort = 0;

	if(CameraCode.size() > 0)
	{
		pthread_mutex_lock(&m_map_mutex);
		//////test
		mapSipID::iterator it1 = m_mapSipID.begin();
		while (it1 != m_mapSipID.end())
		{
			cerr<<"in GetSPortBasedOnCameraCode"<<endl;
			cerr<<"it1->fisrt CameraCode:"<<it1->first<<endl;
			cerr<<"it1->seconde.VideoServerIp:"<<(it1->second).VideoServerIp<<endl;
			cerr<<"it1->seconde.Transport:"<<(it1->second).Transport<<endl;
			cerr<<"it1->seconde.Port:"<<(it1->second).Port<<endl;
			it1++;
		}
		//////test
		mapSipID::iterator it = m_mapSipID.find(CameraCode);
		if(it != m_mapSipID.end())
		{
			cerr<<"in GetSPortBasedOnCameraCode found "<<CameraCode<<",Port:"<<atoi((it->second).Port.c_str())<<endl;

			if((it->second).Port.size()>0)
			{
				nPort = atoi((it->second).Port.c_str());
			}
		}
		else
		{
			cerr<<"in GetSPortBasedOnCameraCode"<<endl;
		}

		pthread_mutex_unlock(&m_map_mutex);

		
	}

	return nPort;
}
string CHKSipService::GetHostBaseOnCameraCode(string CameraCode) //��ȡ���������ķ���ʵʱ��Ƶ���Ļ���IP
{
	cerr<<"in GetHostBaseOnCameraCode mapSipId:"<<m_mapSipID.size()<<",CameraCode:"<<CameraCode<<endl;

	string strHost = "";

	if(CameraCode.size() > 0)
	{
		pthread_mutex_lock(&m_map_mutex);
		//////test
		mapSipID::iterator it1 = m_mapSipID.begin();
		while (it1 != m_mapSipID.end())
		{
			cerr<<"in GetHostBaseOnCameraCode"<<endl;
			cerr<<"it1->fisrt CameraCode:"<<it1->first<<endl;
			cerr<<"it1->seconde.VideoServerIp:"<<(it1->second).VideoServerIp<<endl;
			cerr<<"it1->seconde.Transport:"<<(it1->second).Transport<<endl;
			cerr<<"it1->seconde.Port:"<<(it1->second).Port<<endl;
			it1++;
		}
		//////test
		mapSipID::iterator it = m_mapSipID.find(CameraCode);
		if(it != m_mapSipID.end())
		{
			cerr<<"in GetHostBaseOnCameraCode found:"<<CameraCode<<":HostIp:"<<(it->second).VideoServerIp<<endl;
			cerr<<"in GetHostBaseOnCameraCode found:"<<CameraCode<<":HostIp g_monitorHostInfo.chMonitorHost:"<<g_monitorHostInfo.chMonitorHost<<endl;
			//strHost = (it->second).VideoServerIp;
			strHost = g_monitorHostInfo.chMonitorHost;
		}
		else
		{
			
			cerr<<"in GetHostBaseOnCameraCode"<<endl;
			
		}

		pthread_mutex_unlock(&m_map_mutex);
	}
	
	return strHost;
}


bool CHKSipService::UserLogOnServer()
{
	eXosip_lock ();
	//��sip������ע��
	//m_registerId = eXosip_register_build_initial_register(localSip.c_str(), server.c_str(), NULL, 1800, &m_reg);
	m_registerId = eXosip_register_build_initial_register(m_sourceCall.c_str(), m_serverCall.c_str(), NULL, 1800, &m_reg);
	cerr<<"in UserLogOnServer() m_registerId"<<m_registerId<<endl;
	if (m_registerId < 0)
	{
		cerr<<"Build register error!"<<endl;
		eXosip_unlock ();
		return false;
	}
	//testcode
	cerr<<"clear password()="<<eXosip_clear_authentication_info()<<endl;
	cerr<<"add password()="<<eXosip_add_authentication_info(m_sourcTelNumber.c_str(), m_sourcTelNumber.c_str(), m_strPassword.c_str(), "MD5", NULL)<<endl;


	cerr<<m_reg->sip_method<<endl;
	int ret = eXosip_register_send_register (m_registerId, m_reg);
	eXosip_unlock ();



	cerr<<"in UserLogOnServer() ret"<<ret<<endl;
	if (ret < 0)
	{
		cerr<<"send register error!"<<endl;
		return false;
	}

	return true;
}

void CHKSipService::LoginHKServer()
{
	/*while(!g_bEndThread)
	{
		while(!m_bLogOnServer)
		{*/
			m_bLogOnServer = UserLogOnServer();
		/*	sleep(3600);
		}

		sleep(5);
	}*/
}

#endif
