// ������ͨ��Ƶ����ʶ������� V1.0
// Mimax Intelligent Transport Video Recognition & Detection Software V1.0
// ��Ȩ���� 2008 �Ͼ�������Ѷ�Ƽ����޹�˾
// Copyright 2008 Nanjing Mimax Vision Technologies Ltd
// ������Ѷ��˾����  Mimax Vision Confidential Proprietary
//
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include "yuv_driver.h"
#include "../../ipp/ippcc.h"


#define MAX_LEN	1024

#define WIDTH	1920
#define HEIGHT	540

//���ݻ���
yuv_video_buf *buffer = NULL;
int nFirstFieldSeq = -1;  //��֡�����
int nPreFieldSeq = -1; //��һ֡�����
//int nPreSeq = -10; //��һ֡֡��
unsigned int nSeq = 0;

FILE * fp = NULL;


//���豸,����socket
int yuv_open(const char* host,int port,const char* user,const char* pass)
{
	 struct sockaddr_in addr;
     int fd;
     struct ip_mreq mreq;
	 int nLen = 8192000; //���ջ�������С(8M)

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) 
	 {
	   return -1;
     }


     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(port);
     
     /* bind to receive address */
     if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) 
	 {
	   return -1;
     }
     
     /* use setsockopt() to request that the kernel join a multicast group */
     mreq.imr_multiaddr.s_addr=inet_addr(host);
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) 
	 {
	   return -1;
     }

	 //���ý��ջ�������С
	 if (setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&nLen,sizeof(int)) < 0) 
	 {
	   return -1;
     }

	 //�����ڴ�ռ�
     buffer = (yuv_video_buf*)malloc(sizeof(yuv_video_buf));
     if (buffer==NULL) return -2;
  
	 //�Ѿ�֪�����ݸ�ʽ
	buffer->width = WIDTH;
	buffer->height = HEIGHT;
	buffer->nSeq = 0;
	buffer->size = WIDTH * HEIGHT * 2;
	buffer->data = (unsigned char*)malloc(buffer->size);
	if(buffer->data == NULL) return  -2;

	fp = fopen("/data/video/demosave.yuv","wb"); 

	return fd;
}
//�ر��豸
int yuv_close (int fd)
{
	//�ر�
	shutdown(fd,0);
	//�˳�
	close(fd); 
	return 0;
}

//��������
int yuv_nextframe(int fd,yuv_video_buf** pBuf)
{
	struct sockaddr_in recv_addr;
	int addrlen,bytes,index,left;
	//yuv��С(1092x540x2)
	int nSize = WIDTH * HEIGHT*2;

	char buf[MAX_LEN]={0};

    addrlen=sizeof(recv_addr);

	yuv_video_header* header;

	bytes = 0;
	index = 0;
	//����
    while(1)
	{
		
       if(bytes==28)
		{
		   memcpy(buf,&(buffer->data[index]),bytes);
		   index= 0;
		}
		else
		{
			//��������ͷ 
			bytes = recvfrom(fd, &buf[index], MAX_LEN, 0,(struct sockaddr *) &recv_addr, &addrlen);
			if(bytes == -1)	
			{
				continue;     //���½���yuvͷ��������
			}
		}
		//ͬ���ж�
		if (buf[0] =='$'&&
			buf[1] =='$'&&
			buf[2] =='$'&&
			buf[3] =='$')
		{	
           
		    header = (yuv_video_header*)buf;
		    if((!(header->cType[0] == 'U' && header->cType[1] == 'Y' && header->cType[2] == 'V' && header->cType[3] == 'Y'))||
				(header->nWidth!=WIDTH)||(header->nHeight!=HEIGHT*2)||(header->nSize!=nSize))
			{
               continue;
			}
			
		   //��������
		   bytes = 0;
		   index = 0;
		   left = nSize;
		   
		   while(left > 0)
		   {
				bytes = recvfrom(fd, &buffer->data[index], left > MAX_LEN ? MAX_LEN : left, 0,(struct sockaddr *) &recv_addr, &addrlen);
				if(bytes==28)
			   {
                  break;
			   }
				if(bytes == -1)	
				{
					//�˳���������ѭ��
					break;
				}
				left -= bytes;
				index +=bytes;
			}

			if(bytes == -1||bytes==28)//���½���yuvͷ��������
			{
				continue;
			}
			
			//���ݳ���ż���ʱ���
			//��¼��֡�����
			if(nFirstFieldSeq<0)
			{
			   nFirstFieldSeq = header->nFieldSeq;
			}
			else if(header->nFieldSeq<nPreFieldSeq)//��ǰ֡�����С����һ֡�����
			{
			   nSeq++ ;
			}
			//��ǰ֡��
			buffer->nSeq = nSeq*65536+header->nFieldSeq-nFirstFieldSeq;
			//ʱ���
			buffer->ts = (buffer->nSeq)*40000;
			buffer->uTimestamp = time(NULL);

			printf("header->nFieldSeq=%d,nPreFieldSeq=%d,nSize=%d,nSeq=%d\r\n",header->nFieldSeq,nPreFieldSeq,nSize,nSeq);
			//��¼��һ֡�����
			nPreFieldSeq = header->nFieldSeq;
			
			//���ճɹ�����
			*pBuf = buffer;

			fwrite(buf,sizeof(char),sizeof(yuv_video_header),fp);
			fwrite(buffer->data,sizeof(char),nSize,fp);

			return 0;
			///////////////////////////////////////
		}
		else
		{
			bytes = 0;
	        index = 0;
		}
	}

	return -1;
}

//�ͷ��ڴ�
int yuv_release_buf()
{
	if(buffer)
	{
		if(buffer->data)
		{
		    free(buffer->data);
			printf("yuv buffer->data free \r\n");
		}

		free(buffer);
		printf("yuv buffer free \r\n");
	}
   fclose(fp);
	buffer = NULL;
	return 0;
}

//ʱ���
int64_t yuv_to_timestamp(struct timeval *tv)
{
    long long ts;

	// ��ʽ  timeval.tv_sec:timeval.tv_usec
	//      timeval.tv_sec:��
	//      timeval.tv_usec:����
    ts  = tv->tv_sec;
    ts *= 1000000;
    ts += tv->tv_usec;
   // ts *= 1000;
    return ts;
}
