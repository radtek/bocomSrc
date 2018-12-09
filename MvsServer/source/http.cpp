#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "http.h"
#include "httpsocket.h"
#include "Common.h"

#define  URL_LEN 256
#define FILENAME_LEN 1024
#define PATH_LEN 1024

#define MAX_RECV_SIZE    1440//Ӳ���������Ľ����ֽ���
char g_host[URL_LEN];
char g_ip[URL_LEN+1];//ip/����
char g_port[5+1];
 
char g_buf_send[4*1024];//���������ݴ���
char g_buf_recv[10*1024];//���������ݴ���



/*
����:�����ļ�,׷��д
����:
����:
0---------�ɹ�
*/
 
int Save_File(char *filebuf,int filelength,char *filename)
{
	//LogNormal("Save_File: START\n");
	printf("***************\n%s\n***************\n",filebuf);
	FILE* fp = NULL;
	char strSaveFile[1024] = {0};
	sprintf(strSaveFile,"./%s",filename);

	fp = fopen(strSaveFile,"wb");
	if (fp)
	{
		fwrite(filebuf,filelength,1,fp);
		fclose(fp);
	}
	//LogNormal("Save_File:END\n");
    return 0;
}
 
 
int HTTP_GetResponseCode(void)
{
 
 
}
 
 /*
����:��ȡhttp���ص�Э��ʵ�����峤��
����:
revbuf--------���յ��ķ���ֵ
����ֵ:
>=0---------����(ʵ������)�ĳ���
-1-----------���ݷ��ش���
*/
int HTTP_GetRecvLength(char *revbuf)
{
    char *p1 = NULL;
    int HTTP_Body = 0;//�����峤��
    int HTTP_Head = 0;//HTTP Э��ͷ����
 
	//LogNormal("HTTP_GetRecvLength: START[%s]\n",revbuf);
    HTTP_Body = HTTP_GetContentLength(revbuf);
    if(HTTP_Body == -1)
        return -1;
 
	//LogNormal("HTTP_GetRecvLength: END[%d]\n",HTTP_Body);

    p1=strstr(revbuf,"\r\n\r\n");
    if(p1==NULL)
        return -1;
    else
    {
        HTTP_Head = p1- revbuf +4;// 4��\r\n\r\n�ĳ���
        return HTTP_Body+HTTP_Head;
    }
 
 
}
 
 
/*
����:��ȡhttp���ص�Content-Length����
����:
revbuf--------���յ�������
����ֵ:
>=0---------Content-Length����
-1-----------���ݷ��ش���
*/
int HTTP_GetContentLength(char *revbuf)
{
    char *p1 = NULL, *p2 = NULL;
    int HTTP_Body = -1;//�����峤��
 
	//Content-Length �������
	//Content-length ����ʵ��
	const char szContent[2][20] = {"Content-length", "Content-Length"};
	
	for(int i=0; i<2; i++)
	{	
		p1 = strstr(revbuf,szContent[i]);
		if(p1 == NULL)
		{
			//return -1;
			continue;
		}
		else
		{
			p2 = p1+strlen(szContent[i])+ 2;
			HTTP_Body = atoi(p2);
			//return HTTP_Body;
			break;
		}				
	}

	return HTTP_Body;	
}
 
 /*
 ����:
 ����:
 sockfd--------���յ��ķ���ֵ
 ����ֵ:
 >0---------���յ�����
 -1----------ʧ��
 =0---------����˶Ͽ�����
 ע:�ڲ����ջ���10k
 */
 
int HTTP_Recv(int sockfd,char *buf_recv)
{
    int ret;
    int recvlen=0;
    int downloadlen = 0;
    //int contentlen=0;
    char buf_recv_tmp[10*1024+1];
    //LogNormal("HTTP_Recv: START\n");

    memset(buf_recv_tmp,0x0,sizeof(buf_recv_tmp));
    while(1)
    {
        ret = Recv(sockfd,buf_recv_tmp+recvlen,sizeof(buf_recv_tmp)-1,0);
 
        if(ret <= 0)//����ʧ��
        {
            perror("ERR:recv fail");
            return ret;
        }
    
    
        if(recvlen == 0)
        {
            #ifdef DEBUG_HTTP_RECV
            printf("recv len = %d\n", ret);
             printf("recv = %s\n", buf_recv_tmp);
            #endif
            //��ȡ��Ҫ���س���;
            downloadlen = HTTP_GetRecvLength(buf_recv_tmp);
			//LogNormal("HTTP_Recv: START:downloadlen:%d\n",downloadlen);
 
            #ifdef DEBUG_HTTP_RECV
            printf("downloadlen = %d\n",downloadlen);
            #endif
        }
 
        recvlen += ret;
        #ifdef DEBUG_HTTP_RECV
        printf("total recvlen = %d\n",recvlen);
        #endif
 
        if(downloadlen == recvlen)//�������
            break;
 
 
    }
    memcpy(buf_recv,buf_recv_tmp,downloadlen);
    return recvlen;
 
}
 
/*
����:��ȡ����url�е��ļ���,���һ��/����ַ�
����:
����ֵ:
0-----------�ɹ�
-1----------ʧ��
ע:�ڲ����ջ���10k
*/
 
int HTTP_GetFileName(char *url,char *filename)
{
    //��ȡurl�����һ��/�������
    int len;
    int i;
 
    len = strlen(url);
    for(i=len-1;i>0;i--)
    {
        if(url[i] == '/')
            break;
    }
    if(i == 0)//���ص�ַ����
    {
        printf("url not contain '/'\n");
        return -1;
    }
    else
    {
    
        strcpy(filename,url+i+1);
        #ifdef DEBUG_HTTP
        printf("filename=%s\n",filename);
        #endif
        return 0;
    }
}
 
/*
����:��ȡ����url�е�·��,��һ��/����ַ�
����:
����ֵ:
0-----------�ɹ�
-1----------ʧ��
ע:url ex "http://host:port/path"
*/
int HTTP_GetPath(char *url,char *path)
{
    char *p;
 
    p = strstr(url,"http://");
    if(p == NULL)
    {
        p = strchr(url,'/');
        if(p == NULL)
            return -1;
        else
        {
            strcpy(path,p);
            return 0;
        }
    }
    else
    {
        p = strchr(url+strlen("http://"),'/');
        if(p == NULL)
            return -1;
        else
        {
            strcpy(path,p);
            return 0;
        }
    }
 
}
/*
����:��ȡ����url�е�ip��port,ip֧������,�˿�Ĭ��Ϊ80
����:
����ֵ:
1-----------����ʽ
2-----------ip portʽ
-1----------ʧ��
ע:url ex "http://host:port/path"
*/
 
int HTTP_Get_IP_PORT(char *url,char *ip,char *port)
{
    char *p = NULL;
    int offset = 0;
    char DOMAIN_NAME[128];
 
    p = strstr(url,"http://");
    if(p == NULL)
    {
        offset = 0;
    }
    else
    {
        offset = strlen("http://");
    }
 
    p = strchr(url+offset,'/');
    if(p == NULL)
    {
        printf("url:%s format error\n",url);
        return -1;
        
    }
    else
    {
 
        memset(DOMAIN_NAME,0x0,sizeof(DOMAIN_NAME));
        memcpy(DOMAIN_NAME,url+offset,(p-url-offset));
        p = strchr(DOMAIN_NAME,':');
        if(p == NULL)
        {
            strcpy(ip,DOMAIN_NAME);
            strcpy(port,"80");
            //printf("ip %p,port %p\n",ip,port);
            
            #ifdef DEBUG_HTTP
            printf("ip=%s,port=%s\n",ip,port);//debug info
            #endif
            return 1;
 
        }
        else
        {    
            *p = '\0';
 
            strcpy(ip,DOMAIN_NAME);
            strcpy(port,p+1);
            
            #ifdef DEBUG_HTTP
            printf("ip=%s,port=%s\n",ip,port);//debug info
            #endif
            return 2;
 
        }
 
 
        return 0;
    }
    
}
void Package_Url_Get_File(char *path, char *range)
{
    char buf[64];
    memset(g_buf_send,0x0,sizeof(g_buf_send));         
    sprintf(g_buf_send, "GET %s",path);
 
    
    //HTTP/1.1\r\n ǰ����Ҫһ���ո�
    strcat(g_buf_send," HTTP/1.1\r\n");
    strcat(g_buf_send, "Host: ");
    strcat(g_buf_send, g_host);
    //strcat(g_buf_send, ":");
    //strcat(g_buf_send, PORT);
    
    sprintf(buf, "\r\nRange: bytes=%s",range);
    strcat(g_buf_send,buf);
    strcat(g_buf_send, "\r\nKeep-Alive: 200");
    strcat(g_buf_send,"\r\nConnection: Keep-Alive\r\n\r\n");
    
 
}
 
int Package_Url_Get_FileSize(char *url)
{
    
    memset(g_buf_send,0x0,sizeof(g_buf_send));         
    //sprintf(g_buf_send, "HEAD %s",url);
	sprintf(g_buf_send, "GET %s",url);
 
        //HTTP/1.1\r\n ǰ����Ҫһ���ո�
    strcat(g_buf_send," HTTP/1.1\r\n");
    strcat(g_buf_send, "Host: ");
    strcat(g_buf_send, g_host);
    //strcat(g_buf_send, ":");
    //strcat(g_buf_send, PORT);
    strcat(g_buf_send,"\r\nConnection: Keep-Alive\r\n\r\n");
 
    return 0;
}
 
 
int HTTP_GetFileSize(int sockfd,char *path)
{
    int ret = -1;
    char buf_recv_tmp[10*1024+1];
 
    Package_Url_Get_FileSize(path);
	//LogNormal("BOCOM:send = %s \n",g_buf_send);

    Send(sockfd, g_buf_send, strlen(g_buf_send), 0);
 
    memset(buf_recv_tmp,0x0,sizeof(buf_recv_tmp));                                                 
    ret = Recv(sockfd,buf_recv_tmp,sizeof(buf_recv_tmp)-1,0);
	//LogNormal("BOCOM:recv len = %d\n", ret);
    //LogNormal("BOCOM:recv = %s\n", buf_recv_tmp);

    if(ret <= 0)
    {
        perror("ERR:recv fail GetFileSize()");
        return -1;
 
    }
    ret = HTTP_GetContentLength(buf_recv_tmp);
	//LogNormal("HTTP_GetFileSize:%d\n",ret);
    if(ret <= 0)
        return -1;
    else
        return ret;
 
 
}
 
 
 
 
/*
����:�ֶ������ļ�
����:
����ֵ:
>0----------�������ļ���С(�������ϴ�����)
-1----------ʧ��
*/
int HTTP_GetFile(int sockfd,char *path,int filelength,int download_size,char *filebuf)
{
    int count;
    char range[32];
    int i;
    int j = 0;//�ɹ����ش���
    int ret = -1;
    char *p = NULL;
    int download_index;//���ؿ�ʼ����
 
    count = (filelength%MAX_RECV_SIZE)?(filelength/MAX_RECV_SIZE +1):(filelength/MAX_RECV_SIZE);
 
    download_index = download_size/MAX_RECV_SIZE;
	//LogNormal("HTTP_GetFile: START:path:%s filelength:%d download_size:%d filebuf:%s\n",path,filelength,download_size,filebuf);
	//LogNormal("HTTP_GetFile: download_index:%d count:%d\n",download_index,count);
	for(i=download_index;i<count;i++)
    {
        if((i == (count-1))&&(filelength%MAX_RECV_SIZE))
            sprintf(range,"%d-%d",i*MAX_RECV_SIZE,filelength-1);
        else
            sprintf(range,"%d-%d",i*MAX_RECV_SIZE,(i+1)*MAX_RECV_SIZE-1);
 
 
        Package_Url_Get_File(path,range);
		//LogNormal("BOCOM:send = %s \n",g_buf_send);

         Send(sockfd, g_buf_send, strlen(g_buf_send), 0);
 
        /*���Ϊ��ȡhttp ����Э��ͷ��Э�����ܳ�,Ȼ�󶨳�����*/
        memset(g_buf_recv,0x0,sizeof(g_buf_recv));                                              
        ret = HTTP_Recv(sockfd,g_buf_recv);
		//LogNormal("BOCOM:HTTP_Recv:%s\n",g_buf_send);
        if(ret < 0)
            break;
        if(ret == 0 )//����˶Ͽ�����
        {
            sockfd = Socket_Connect(g_ip,g_port);
             i--;
            continue;
        }
        /*��ȡЭ��������,������filebuf��*/
        p = strstr(g_buf_recv,"\r\n\r\n");
        if(p == NULL)//jia ru duan dian baocun
        {
			LogNormal("BOCOM:ERR:g_buf_recv not contain end flag\n");
            break;
        }
         else
         {
             memcpy(filebuf+j*MAX_RECV_SIZE,p+4,strlen(p+4));
             j++;
 
         }
    }

    if(i == count)
        return (filelength-download_size);
    else
        return (i*MAX_RECV_SIZE-download_size);
}
 
/*
����:HTTP�����ļ�
����:
����ֵ:
0----------�������
-1---------ʧ��
-2---------�����������
ע:�����ļ���bin����Ŀ¼
*/
int HTTP_DownloadFile(char *url,bool bFisrtDown)
{
    int ret;
    int sockfd;
    int filesize;
    int download_size;
    char filename[FILENAME_LEN+1];
    char filename_bp[FILENAME_LEN+3+1];
    char *filebuf;
    char save_file_path[FILENAME_LEN+1];//���������ļ���·��+�ļ���
 
    char path[PATH_LEN+1];//url�е�path
 
    ret = HTTP_Get_IP_PORT(url,g_ip,g_port);
    if(ret == -1)
        return -1;
    else
    {
        sprintf(g_host,"%s:%s",g_ip,g_port);
    }

	//LogNormal("BOCOM:%s\n",url);
	//��ȡ�����ļ���
    ret = HTTP_GetFileName(url,filename);

	//LogNormal("HTTP_DownloadFile::HTTP_GetFileName: ret:%d filename:%s\n",ret,filename);
	if(ret == -1)
        return -1;
 
    ret = HTTP_GetPath(url,path);
	//LogNormal("HTTP_DownloadFile::HTTP_GetPath ret%d\n",ret);
    if(ret == -1)
        return -1;
    //sleep(3);//debug info
    //��������
    sockfd = Socket_Connect(g_ip,g_port);
	if (sockfd == -1)
	{
		LogError("Http Server is not exist![%s]\n",url);
		return -1;
	}
	
	//��ȡ�����ļ��ܴ�С
    filesize = HTTP_GetFileSize(sockfd,path);
	LogNormal("HTTP_DownloadFile::HTTP_GetFileSize :%d\n",filesize);
    if(filesize == -1)
        return -1;

    //malloc����洢�ļ��ռ�
    filebuf = (char *)malloc(filesize);
    if(filebuf == NULL)
    {
        perror("malloc filebuf fail");
        return -1;
    }
    else
        memset(filebuf,0x0,filesize);
 
    download_size = 0;
    //�ֶ������ļ�
	//LogNormal("HTTP_DownloadFile::HTTP_GetFile START:filesize:%d download_size:%d\n",filesize,download_size);
	ret = HTTP_GetFile(sockfd,path,filesize,download_size,filebuf);
	//LogNormal("HTTP_DownloadFile::HTTP_GetFile END:ret:%d FILEBUF:\n%s\n",ret,filebuf);
    Close(sockfd);
    if(ret < 0)
    {
		LogNormal("HTTP_GetFile : Failed\n");
        free(filebuf);
        return -1;
    }
    else
    {
		char strFileName[1024] = {0};

		if (bFisrtDown == true)
		{
			sprintf(strFileName,"./config/kafkaServerList.txt");
		}
		else
		{
			sprintf(strFileName,"./config/kafkaServerListlast.txt");
		}

		Save_File(filebuf,filesize,strFileName);
		if (filebuf)
		{
			free(filebuf);
			filebuf = NULL;
		}
        return 0;
    }
 
}