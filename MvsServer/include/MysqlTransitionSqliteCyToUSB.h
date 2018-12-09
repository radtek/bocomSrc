#ifndef MYSQLTRANSITIONSQLITECYTOUSB_H
#define MYSQLTRANSITIONSQLITECYTOUSB_H

/*
	�������Ҫ�����ǣ� ��mysql���������copy�� sqlite ���� Ȼ���� ��sqlite3 ���͵����ݰ�epolice.db
	copy�� u����
	
*/

#include <math.h>
#include "Common.h"
#include "global.h"
#include <sys/stat.h>
#include <sys/mount.h>
#include <string>
#include <iconv.h>
#include <stdio.h>
#include <memory.h>

#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <linux/kd.h> 
#include "/usr/include/mysql/mysql.h"


//#define SQLITE_OK
  
#ifdef SQLITE_OK
#include "sqlite3.h"

using namespace std;

class MysqlTransitionSqlteCyToUSB
{
public:
	MYSQL  * m_mysql;
	sqlite3 * m_db;
	pthread_mutex_t m_sqlite3_mutex;

	iconv_t cd;
	
	//pthread_t m_nThreadId;


	MysqlTransitionSqlteCyToUSB();
	~MysqlTransitionSqlteCyToUSB();

	int openSqlite();                                     // ��sqlite3���ݿ�

	int  AddField();

	int  createTablePassVehicle();                        // ���� passVehicle �� 

	int  deleteTablePassVehicle();                        // ɾ��passVehicle ��
	
	bool intThreadMonitorFindUSB();						  // �������һ����ⷢ��u�̵��߳�
	
	void RunToCopy();                                     // ���������������������һ���̣߳� ����̲߳��ϵļ���Ƿ���u�̲�������з��ֶ��������copy�Ĺ�����

	int fileWriteUSB();                                   // �����db�ļ�copy��u������

	void closeSqlite();							          // �ر�sqlite3���ݿ�         

 	int insetIntosqliteMessage(string str);         // �����ݲ��뵽sqlite3 ����

	int execsqlInsqlite(string strSql);		// ��sqlite3 ��ִ��sql���

	int insetIntosqliteMessage(string sqlPaht, string strSql);                                           

	char * transitionData(MYSQL_ROW row);                                  // ��������Ĺ������ǣ� ��mysql�������������������ϳɲ���sqlite3��sql ���

	int carLabel(int number);    //����

	int carColor(int number);    //������ɫ
	
	int wfxw(int number);       //���������

	int carType(int number, string str);  //��������

	int wflx(int number);

	void CodeConverterOpen(const char *from_charset,const char *to_charset) 
	{
			 cd = iconv_open(to_charset,from_charset);
	}

		
	void CodeConverterClose() 
	{
			iconv_close(cd);
	}

		// ת�����	
	int converting(char *inbuf,int inlen,char *outbuf,int outlen) 
	{
			char **pin = &inbuf;
			char **pout = &outbuf;

			memset(outbuf,0,outlen);
			return iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);
	}

protected:


private:


};




//void * findUSBThread(void *);                              // ����߳��Ƿ�����û��usb ���ȥ



#endif
#endif
