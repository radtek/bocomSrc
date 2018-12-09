// StreamBuffer.h: interface for the CStreamBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCODERBUFFER_H__2E192A08_4E32_40DA_89C8_A881515802D7__INCLUDED_)
#define AFX_ENCODERBUFFER_H__2E192A08_4E32_40DA_89C8_A881515802D7__INCLUDED_
/* 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/
#include <pthread.h>
#define ROUNDARRYLEN 100
extern char* GetNowTime(char*);

/************************************************************************/
/* 
����Ϊ���ݻ��������ߣ�Ϊ���λ�����
�������Ĵ�С�����ݵĴ�С����
Ŀǰ����5S������
*/
/************************************************************************/
class CStreamBuffer
{
public:
	CStreamBuffer( int iBufSize );
	virtual ~CStreamBuffer();

public:
    //�򻺳���д������
	void WriteBuffer( char *pData, int len );
	//�ӻ�������������
    int ReadBuffer( char *pData, unsigned long long &iPos, int len );
	//��ȡд�������������
    unsigned long long GetCurrentWriteTotal();
    //��������
	void SseCopy( void *pData, void *pSrc, int len );
private:
    //��������С
	unsigned long long m_ubiBufSize;
    //д�������������
	unsigned long long m_ubiTotalWrite;
    //��д����������������
	pthread_mutex_t totalWriteLock;
	//������bufָ��
    char *m_pBuf;
    //д����ʱ��Ӧ��buf��ַ
	int m_iWritePtr;
    //���ν������ݵ���󳤶�
	int m_iPackageLen;
    //��д���������ݻ�����
	pthread_mutex_t datalock;	
};

#endif // !defined(AFX_ENCODERBUFFER_H__2E192A08_4E32_40DA_89C8_A881515802D7__INCLUDED_)
