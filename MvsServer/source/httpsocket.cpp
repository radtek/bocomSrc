#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
 
#include "httpsocket.h"
 
int Connect(int fd, struct sockaddr *addr, socklen_t len)
{
    int result;
    if ((result = connect(fd, addr, len)) == -1) {
        perror("connect");
        return -1;
    }
    return 0;
}
 
int Socket_Connect(char *ip,char *port)
{
    struct sockaddr_in addr;
 
    int sockfd;
    int len;
 
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//127.0.0.1Ϊ����ip
    addr.sin_port = htons(atoi(port));
    len = sizeof(addr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int nRet = Connect(sockfd, (struct sockaddr*)&addr, len);
	if (nRet == -1)
	{
		return -1;
	}
    return sockfd;
 
}
 
 
/*
����:��socketfd��������,�ڲ�ʵ����ѭ������len����
����:
sockfd �Ǵ�������Զ�̳������ӵ��׽�����������
msg ��һ��ָ�룬ָ�����뷢�͵���Ϣ�ĵ�ַ��
len �����뷢����Ϣ�ĳ��ȡ�
flags ���ͱ�ǡ�һ�㶼��Ϊ0
����:
0-------- �ɹ�
�˳�---ʧ��
�޸�:
��ע:
����
*/
int Send(int sockfd, char *sendbuf, int len, int flags)
{
    int sendlen = 0;
    int ret = -1;
 
    while(sendlen < len)
    {
        ret = send(sockfd, sendbuf+sendlen, len-sendlen, flags);
        if(-1 == ret)
        {
            perror("send");
            return -1;
        }
        else
            sendlen += ret;
 
    }
 
    return 0;
 
}
 
int Close(int sockfd)
{
    return close(sockfd);
    
 
}
int Recv(int sockfd, char *recvbuf, int len, int flags)
{
    int recv_len;
 
    if ((recv_len = recv(sockfd, recvbuf, len, flags)) < 0)
    {
        perror("recv error");
        return -1;
    }
 
    return recv_len;
}
