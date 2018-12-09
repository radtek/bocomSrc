#ifndef SKP_MJPEG_H
#define SKP_MJPEG_H

#include <string>
#include "byteswap.h"
#include <stdio.h>
#include "avifmt.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <list>


typedef struct _Jpeg_Data
{
  unsigned int size;
  unsigned int offset;
}Jpeg_Data;

typedef std::list<Jpeg_Data> ListJpeg;


class CMJpegAvi
{
public:
	CMJpegAvi();
	virtual ~CMJpegAvi();

//���з���
public:
	//����Ƶ�ļ�
	bool OpenFile(const char* chFileName);
	//�ر���Ƶ�ļ�
	bool CloseFile();
	//���һ������
	bool AddFrame(const unsigned char* pBuffer,const unsigned int nLength);
	//�Ƿ�ʼ����
	bool IsEncoding() {return m_EncodeFile != 0;}
	//����¼����
	void SetWidth(unsigned int uWidth) { m_uWidth = uWidth;}
	void SetHeight(unsigned int uHeight){ m_uHeight = uHeight;}
	//����¼���ļ���
	const char*  GetEncodingFileName() { return m_strFileName.c_str();}

protected:
	void print_quartet(unsigned int i);
	long get_file_sz();
//˽�б���
private:

	//Ŀ���ļ�
	FILE* m_EncodeFile;

	//��
	unsigned int m_uWidth;
	//��
	unsigned int m_uHeight;

	//�ļ���
	std::string m_strFileName;

	//
	ListJpeg m_list;

	//
	int m_nFrame;
};

#endif // SKP_MJPEG_H
