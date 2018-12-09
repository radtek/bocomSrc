#ifndef _FILE_SOCKET
#define _FILE_SOCKET

#include "CSocketBase.h"

//#define _TEST_CODE

class CGetFileClientSocket:public mvCSocketBase
{
public:
	CGetFileClientSocket();
	virtual ~CGetFileClientSocket();
private:
	int m_nSocket;
	int m_nPort;
	UINT32 uTimestamp;				//ʱ���
	string m_strData;
	//�Ƿ������ݣ�����ڷ���֮ǰ���������� ����10��û���������ݶϿ�����
	bool m_bSendBuf;
	int m_nRecvNum;

	
	int RecvMsg(std::string &response,int nSize);
	bool SendMsg(RECORD_PARA para);
	/*��������¼������ID
	��������0:���Ʋ�ѯ��1:�¼���ѯ��2:ȫ��¼��*/
	int FindLocalPic(string &strData,RECORD_PARA para);
	//��ftp·����������ȷ�ı��ش洢·��
	void GetCorrectLocalDir(string &strLocalPath,string strFtpPath,int nVideoType = 0);
#ifdef _TEST_CODE
	bool ReadLocalPic(char* szFile,std::string &strBuffer);
#endif
public:
	char m_chHost[16];
	bool m_bEndThread;
	
	bool Init(int nSocket,char *pchar,int nPort);
	void UnInit();
	void SetRecvBuf(string strData){m_strData = strData;}
	string GetRecvBuf(){return m_strData;}
	bool CheckClientSendState();

	int GetSocket(){return m_nSocket;}
	int DealMsg();
};

//�ͻ����б�
typedef std::map<int,CGetFileClientSocket*> GetFileClientMap;
class CGetFileServerSocket:public mvCSocketBase
{
public:
	CGetFileServerSocket();
	virtual ~CGetFileServerSocket();
private:
	//�����˿�
	int m_nPort;
	bool m_bEndThread;
	//ClientMap�źŻ���
	pthread_mutex_t m_thread_mutex;
	//�ͻ�������ӳ���б�
	GetFileClientMap m_ClientMap;
	//�������ӵ��׽���
	int m_nPermitSocket;
	//static DWORD WINAPI ThreadAccept(LPVOID lpParam);
	//static DWORD WINAPI ThreadOnLine(LPVOID lpParam);
public:
	//�����׽�������
	int m_nAcceptSocket;
	//��ʼ��������
	bool Init();
	//�ͷ�
	bool UnInit();
	//��ӿͻ���
	//bool AddClient(SRIP_CLEINT sClient);
	//ɾ���ͻ���
	//bool DelClient(int nSocket,bool bAll=false);
	//��ӿͻ���
	bool AddClient(int nClientSocket,char *pchHost,int nPort);//CMsgSocket* sMsgSocket);
	//ɾ���ͻ���
	bool DelClient(int nSocket);
	bool DelAllClients();
	//��ⳬʱ
	bool CheckClientTimeOut();
};
#ifdef _TEST_CODE
extern BOOL g_bEndThread;
#endif
//ͨѶ����
//extern CGetFileServerSocket g_skpFileServer;
#endif