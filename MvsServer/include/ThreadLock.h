#ifndef __THREADLOCK_H
#define __THREADLOCK_H

#ifdef linux
#	include <stdint.h>
#	include <signal.h>
#	include <unistd.h> 
#	include <fcntl.h>
#	include <dirent.h>
#	include <pthread.h>
#	include <sys/time.h>
#	include <sys/file.h>
#	include <sys/socket.h>
#	include <sys/ipc.h>
#	include <sys/shm.h>
#	include <sys/wait.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <sys/param.h>
extern int h_errno;
#endif // linux

#ifdef WIN32
#   define FD_SETSIZE 1024
#   include <winsock2.h>
#	include <sys/locking.h>
#	include <io.h>
#	include <rpc.h>
#endif //WIN32

namespace BASE
{
	class ThreadLock
	{
	public:
		/*
		��ʽ��ThreadLock(void)
		������ThreadLock�������߳�����Ĺ��캯����
		���룺
			��
		�㷨����
			��ʼ��������
		�������
		���أ�
			��
		*/
		ThreadLock(void)
		{
#ifdef WIN32
			InitializeCriticalSection(&criCounter);
#endif
#ifdef linux
			pthread_mutex_init(&fastmutex, NULL);
#endif
		};
		/*
		��ʽ��~ThreadLock(void)
		������~ThreadLock�ǽ��������������
		���룺
			��
		�㷨����
		    �ͷ�������ٽ�α�����
		�������
		���أ�
			��
		*/
		~ThreadLock(void)
		{
#ifdef WIN32
			DeleteCriticalSection(&criCounter);
#endif
		};

		// ���������˳���
		/*
		��ʽ��bool Lock()
		������Lock���߳̽����������ĺ�����
		���룺
			��
		�㷨����
		    �������ϵͳ���������ٽ���
		�������
		���أ�
			�ɹ����أ�true
			ʧ�ܷ��أ�false
		*/
		bool Lock()
		{
#ifdef WIN32
			EnterCriticalSection(&criCounter);
			return true;
#endif
#ifdef linux
			return pthread_mutex_lock( &fastmutex ) == 0;
#endif
		};
		/*
		��ʽ��bool UnLock()
		������UnLock�����ǽ��߳̽��н����Ĳ�����
		���룺
			��
		�㷨����
		    �������ϵͳ�����˳��ٽ���
		�������
		���أ�
			�ɹ����أ�true
			ʧ�ܷ��أ�false
		*/
		bool UnLock()
		{
#ifdef WIN32
			LeaveCriticalSection(&criCounter);
			return true;
#endif
#ifdef linux
			return pthread_mutex_unlock( &fastmutex ) == 0;
#endif
		};


	private:
#ifdef WIN32
		CRITICAL_SECTION criCounter;	//windows�����µ��ٽ�α���
#endif
#ifdef linux
		pthread_mutex_t fastmutex;		//linux�����µ�posix������
#endif
	};

};
#endif //__THREADLOCK_H

