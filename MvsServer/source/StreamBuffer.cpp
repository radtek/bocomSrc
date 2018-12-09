// StreamBuffer.cpp: implementation of the CStreamBuffer class.
//
//////////////////////////////////////////////////////////////////////
#include "StreamBuffer.h"
#include <malloc.h>
#include <string.h>
#include "fastmemcpy.h"
#include <assert.h>
#include <stdio.h>
#include "constdef.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStreamBuffer::CStreamBuffer( int iBufSize )
{
	m_ubiBufSize = iBufSize;
	m_ubiTotalWrite = 0ULL;
	
	m_iPackageLen = MAX_DSP_BUF_LEN;
	m_iWritePtr = 0;

	m_pBuf = NULL;
	m_pBuf = (char *)calloc( m_ubiBufSize, 1);
	pthread_mutex_init((&datalock), NULL);
	pthread_mutex_init((&totalWriteLock), NULL);
}


CStreamBuffer::~CStreamBuffer()
{
	if (m_pBuf != NULL)
	{
		free( m_pBuf );
		m_pBuf = 0;
	}
	pthread_mutex_destroy(&datalock);
	pthread_mutex_destroy(&totalWriteLock);
}


void CStreamBuffer::SseCopy( void *pData, void *pSrc, int len )
{
#ifdef WIN32

	int iLoop = len / 8;
	if ( iLoop * 8   < len ) iLoop++;

	__asm
	{
		mov esi, [pSrc];
		mov edi, [pData];

		mov ecx, iLoop
nextcopy:
		pxor mm0, mm0
		movq mm0, [esi]
		movq [edi], mm0
		
		add esi, 8
		add edi, 8
		sub ecx, 1

		cmp ecx, 0
		jg nextcopy
		emms
	};
#else
	memcpy( pData, pSrc, len );
//	fast_sse_memcpy( pData, pSrc, len );
#endif
}


void CStreamBuffer::WriteBuffer( char *pData, int len )
{
	if ( pData == NULL || len <= 0)
	{
		return;
	}

	int iTmp =  m_iWritePtr + len + 12;//ÿ��д��������12�ֽڵĸ�����Ϣ����д�������ݣ���д��������
	if (iTmp <= m_ubiBufSize )//д�볤��λ��û�г���buf�Ĵ�С��ֱ�Ӹ�ֵ
	{
		SseCopy( m_pBuf + m_iWritePtr+12, pData, len );//д����������������
		unsigned long long* lp = (unsigned long long*)(m_pBuf + m_iWritePtr);//��Ӧ��ʼд�븽�����ݵ�λ��
		pthread_mutex_lock(&totalWriteLock);
		*lp = m_ubiTotalWrite;//��������ǰ8���ֽڣ�Ϊ�Ѿ�д�����ݵ�������
		pthread_mutex_unlock(&totalWriteLock);
		int *lp1 = (int*)(m_pBuf + m_iWritePtr + 8);//��Ӧ�����������4���ֽ�λ��
		*lp1 = len;//�����������4���ֽ�,��ֵΪ����д������ݳ���

		m_iWritePtr = (m_iWritePtr + len + 12)%m_ubiBufSize;
	}
	else//д�볤��λ�ó�����buf�Ĵ�С��β�����ײ��ֿ���ֵ����Ϊ����buf������
	{
		unsigned char szIndexHead[12];
		unsigned long long* lp = (unsigned long long*)(&szIndexHead[0]);
		pthread_mutex_lock(&totalWriteLock);
		*lp = m_ubiTotalWrite;//��������ǰ8���ֽڣ�Ϊ�Ѿ�д�����ݵ�������
		pthread_mutex_unlock(&totalWriteLock);
		int *lp1 = (int*)(szIndexHead + 8);
		*lp1 = len;//�����������4���ֽ�,��ֵΪ����д������ݳ���
		
		int iTailSize = m_ubiBufSize - m_iWritePtr;//ʣ��ĳ��ȹ�����12���ֽڵĸ��ӳ���

		if(iTailSize >= 12)//�㹻�������ݵĸ�ֵ
		{
			SseCopy( m_pBuf + m_iWritePtr, szIndexHead, 12 );//����������Ϣ
			m_iWritePtr += 12;
			iTailSize -= 12;
			SseCopy( m_pBuf + m_iWritePtr, pData, iTailSize );//������ĩβ��ʣiTailSize�Ŀռ䣬����������������
			
			int iHeadSize = iTmp - m_ubiBufSize;
			m_iWritePtr = 0;
			SseCopy( m_pBuf + m_iWritePtr, pData + iTailSize, iHeadSize );//ʣ�µ��������ݿ������������ײ�
			m_iWritePtr += iHeadSize;
		}
		else//�����������ݵĸ�ֵ��β�׻��θ�ֵ
		{
			SseCopy( m_pBuf + m_iWritePtr, szIndexHead, iTailSize );//β���������ָ�������

			m_iWritePtr = 0;
			SseCopy( m_pBuf + m_iWritePtr, szIndexHead + iTailSize, 12 - iTailSize );//ʣ�µĸ������ݿ������ײ�
			m_iWritePtr += 12 - iTailSize;
			SseCopy( m_pBuf + m_iWritePtr, pData, len );//������������
			m_iWritePtr += len;
		}
	}
	pthread_mutex_lock(&totalWriteLock);
	m_ubiTotalWrite += len+12;//�Ѿ�д�����ݵ�����������
	pthread_mutex_unlock(&totalWriteLock);
	assert(m_ubiTotalWrite<0xfffffffffff00000LLU);//���ֵ��1M
}


int CStreamBuffer::ReadBuffer( char *pData, unsigned long long &iPos, int len )
{
	unsigned long long  tmpTotalWrite = 0ULL;

	pthread_mutex_lock(&totalWriteLock);
	tmpTotalWrite = m_ubiTotalWrite; 
	pthread_mutex_unlock(&totalWriteLock);
	
	unsigned long long off = tmpTotalWrite - iPos;//д����������-��ȡ��������
	if(off == 0)
	{
		//printf("**************************1111111111111111\n");
        return 0;
	}

    if(off > (m_ubiBufSize-m_iPackageLen)) //д���λ�ó�����ȡλ�õĳ��ȳ����˻������ĳ��ȡ���ʱ��ʧ�����ˡ�
	{
//		sExceptionInfos tagErroException;
//		memset(&tagErroException,0,sizeof(sExceptionInfos));
//		tagErroException.iErrCode = Err_CANT_RECEIVE_SOURCE_DATA;
//		
//		if((int)off <= m_ubiBufSize)
//		{
////			CStUnitImp::m_gpVisLog->Warning(MODULE_SRCTODEST,LOGLEVEL_ADMIN,\
//	//			"���ݶ�ʧ <= %d Bytes, usable count: %d",m_ubiBufSize,m_iPackageLen);
//			sprintf(tagErroException.sDescription,"���ݶ�ʧ <= %d Bytes, usable count: %d",m_ubiBufSize,m_iPackageLen);
//		}
//		else
//		{
////			CStUnitImp::m_gpVisLog->Warning(MODULE_SRCTODEST,LOGLEVEL_ADMIN,\
//	//			"���ݶ�ʧ  %d Bytes",(int)off);
//			sprintf(tagErroException.sDescription,"���ݶ�ʧ  %d Bytes",(int)off);
//		}
//
//		CStUnitImp::m_gpExceptionCBFun((sExceptionInfos*)&tagErroException,0);
		iPos = tmpTotalWrite;
		printf("**************************2222222222222\n");
		return 0;
	}
	
	//get datalen 
	int iReadPos = 0;
	int iPackageLen = 0;
	iReadPos = iPos % m_ubiBufSize;
	unsigned char szCheck[12] = {0};
	int uiTmp = iReadPos + 12;
	if(uiTmp <= m_ubiBufSize)//������ʣ�೤���㹻���渽������
	{
		unsigned long long ubiCheck = 0ULL;
		ubiCheck = *((unsigned long long*)(m_pBuf+iReadPos));
		iPackageLen = *((int*)(m_pBuf+iReadPos+8));//ȡ�����ݰ��ĳ���
		iReadPos += 12;
		iReadPos = iReadPos % m_ubiBufSize;//��λ��ȡ���ݵĿ�ʼλ��
	}
	else//����������Ҫ�ְ�����
	{
		SseCopy( szCheck, m_pBuf + iReadPos,  m_ubiBufSize - iReadPos);//�������ݿ�����������ͷ��
		SseCopy( szCheck + m_ubiBufSize - iReadPos, m_pBuf,  uiTmp - m_ubiBufSize);//�������ݿ�����������β��

		unsigned long long ubiCheck = 0ULL;
		ubiCheck = *((unsigned long long*)(szCheck));
		iPackageLen = *((int*)(szCheck+8));
		iReadPos += 12;
		iReadPos = iReadPos % m_ubiBufSize;
	}

	uiTmp = iReadPos+iPackageLen;//��ǰ��ȡλ�ü������ݰ��ĳ���
	if ( uiTmp <= m_ubiBufSize )//�������������Ĵ�С
	{
		SseCopy( pData, m_pBuf + iReadPos,  iPackageLen);//ֱ�ӿ����������ݺ󷵻�
		return iPackageLen;
	}
	
    //��ǰ��ȡλ�ü������ݰ��ĳ��ȳ����������Ĵ�С
	int iTailSize = m_ubiBufSize - iReadPos;
	SseCopy( pData, m_pBuf + iReadPos, iTailSize );//����β��������

	int iHeadSize = iReadPos + iPackageLen - m_ubiBufSize;
	SseCopy( pData + iTailSize, m_pBuf, iHeadSize  );//����ͷ��������
	return iPackageLen;
}

unsigned long long CStreamBuffer::GetCurrentWriteTotal()
{
	unsigned long long tempTotal;
	pthread_mutex_lock(&totalWriteLock);
	tempTotal=m_ubiTotalWrite;
	pthread_mutex_unlock(&totalWriteLock);

	return tempTotal;
}
