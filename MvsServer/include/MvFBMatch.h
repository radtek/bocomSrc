#ifndef __MV_FBMATCH_H__
#define __MV_FBMATCH_H__

#include <vector>
#include <cv.h>
#include "structdef.h"
using namespace std;

//#define MV_LOCAL_DEBUG		//���ص����ã�������ص�

#ifdef  MV_LOCAL_DEBUG
typedef unsigned int        UINT32;
#define MAX_VIDEO			128
#define MAX_PLATE			16

/*
//���Ƽ�¼�ṹ
typedef struct _RECORD_PLATE
{
	UINT32 uSeq;						//���к�
#ifdef MV_LOCAL_DEBUG
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMin;
	int nSec;
#endif
	UINT32 uTime;						//ʶ����ʱ��(��)
	UINT32 uMiTime;					//ʶ����ʱ��(����)
	char chText[MAX_PLATE];					//�����ı�
	UINT32 uColor;					//�������ͣ���ɫ��

	UINT32 uCredit;					//ʶ��ɿ���
	UINT32 uRoadWayID;				//������

	UINT32 uType;						//��������(��16λ���С�С����16λ��������ʿ���γ��ȣ�

	UINT32 uSmallPicSize;				//����Сͼ��С
	UINT32 uSmallPicWidth;			//����Сͼ���
	UINT32 uSmallPicHeight;			//����Сͼ�߶�

	UINT32 uPicSize;					//����ȫ��ͼƬ��С
	UINT32 uPicWidth;					//����ȫ��ͼƬ���
	UINT32 uPicHeight;				//����ȫ��ͼƬ�߶�

	UINT32 uPosLeft;					//������ȫ��ͼƬ�е�λ����
	UINT32 uPosTop;					//������ȫ��ͼƬ�е�λ����
	UINT32 uPosRight;					//������ȫ��ͼƬ�е�λ����
	UINT32 uPosBottom;				//������ȫ��ͼƬ�е�λ����


	UINT32 uCarColor1;				//������ɫ
	UINT32 uSpeed;					//����
	UINT32 uDirection;				//��ʻ����
	UINT32 uCarBrand;				//���̱�־
	char chPlace[64];				//�����ص�
	char chVideoPath[MAX_VIDEO];				//¼��·��
	char chPicPath[MAX_VIDEO];				//��ͼƬ·��

	UINT32 uCarColor2;                    //������ɫ2

	UINT32 uWeight1;                    //������ɫȨ��1
	UINT32 uWeight2;                    //������ɫȨ��2

	UINT32 uSeqID;                      //֡���
	UINT32 uPlateType;            //���ƽṹ
	UINT32 uViolationType;       //Υ������(����Ƶ�)

	UINT32 uTypeDetail;       //����ϸ��
	UINT32 uStatusType;       //��¼����
	UINT32 Position;                   // ͼ��֡���ļ��еĿ�ʼλ�ã���λΪ�ֽڣ�

	UINT32 uChannelID;                  //ͨ�����

	UINT32 uLongitude;//�ص�γ��(ʵ�ʾ���*10000, ��ȷ��С�������λ)
	UINT32 uLatitude; //�ص㾭��(ʵ�ʾ���*10000, ��ȷ��С�������λ)
	UINT32 uTime2;						//�ڶ�����ʱ��(��)
	UINT32 uMiTime2;					//�ڶ�����ʱ��(����)
	UINT32 uAlarmKind;            //�ڰ���������1��������2������
	UINT32 uSignalTime;				//���ʱ��
	UINT32 uRedLightBeginTime;                    //��ƿ�ʼʱ��(��)
	UINT32 uRedLightBeginMiTime;                  //��ƿ�ʼʱ��(����)
	UINT32 uRedLightEndTime;                    //��ƽ���ʱ��(��)
	UINT32 uRedLightEndMiTime;                  //��ƽ���ʱ��(����)
	UINT32 uLimitSpeed;                    //����ֵ
	UINT32 uOverSpeed;                  //��������ֵ

	UINT32 uCameraId;//���ID
	char chReserved[124];//��չ

	_RECORD_PLATE()
	{
		uSeq = 0;
		uTime = 0;
		uMiTime = 0;
		memset(chText,0,MAX_PLATE);
		uColor = 1;

		uCredit = 90;
		uRoadWayID = 0;

		uType = 0;

		uSmallPicSize = 0;
		uSmallPicWidth = 0;
		uSmallPicHeight = 0;

		uPicSize = 0;
		uPicWidth = 0;
		uPicHeight = 0;

		uPosLeft = 0;
		uPosTop = 0;
		uPosRight = 0;
		uPosBottom = 0;

		uSpeed = 0;
		uCarColor1 = 11;//δ֪
		uDirection = 0;
		uCarBrand = 1000;
		memset(chPlace,0,64);
		memset(chVideoPath,0,MAX_VIDEO);
		memset(chPicPath,0,MAX_VIDEO);

		uCarColor2 = 11;
		uWeight1 = 100;
		uWeight2 = 0;

		uAlarmKind = 0;
		uPlateType = 0;
		uViolationType = 0;

		uSeqID = 0;
		uTypeDetail = 0;
		uStatusType = 0;
		Position = 0;

		uLongitude = 0;
		uLatitude = 0;

		uChannelID = 0;
		uTime2 = 0;
		uMiTime2 = 0;
		uSignalTime = 0;
		uRedLightBeginTime = 0;
		uRedLightBeginMiTime = 0;
		uRedLightEndTime = 0;
		uRedLightEndMiTime = 0;
		uLimitSpeed = 0;
		uOverSpeed = 0;

		uCameraId = 0;
		memset(chReserved, 0, 124);

	}
}RECORD_PLATE;
*/


#else
#include "structdef.h"
#endif


/*


typedef struct _RECORD_PLATE_DSP_MATCH
{
	RECORD_PLATE dspRecord;
	IplImage *pImg;//ͼƬ
	IplImage *pImgArray[3];//ͼƬ

	_RECORD_PLATE_DSP_MATCH()
	{
		pImg = NULL;
		pImgArray[0] = NULL;
		pImgArray[1] = NULL;
		pImgArray[2] = NULL;
	}

}RECORD_PLATE_DSP_MATCH;

//ƥ�������
typedef struct __MatchPair
{
	RECORD_PLATE_DSP_MATCH A;
	vector<RECORD_PLATE_DSP_MATCH> vecB;

	vector<int> vecDis;
}MatchPair;

//��ƥ�����Ϣ
typedef struct _ObjMatchInfo
{
	RECORD_PLATE_DSP_MATCH plate;
	int nMatchTimes;

	_ObjMatchInfo()
	{
		nMatchTimes = 0;
	}
}ObjMatchInfo;
*/

class MvFBMatch
{
public:
	MvFBMatch(void);
	~MvFBMatch(void);

private:
	int m_nAChnl, m_nBChnl;										//��¼ƥ���ͨ����
	vector<ObjMatchInfo> m_vecA, m_vecB;						//����
	vector<int> m_vecDiff;										//��¼ʱ���	
	unsigned int m_uLastMatchTimeA, m_uLastMatchTimeB;			//���ƥ��ʱ��

private:
	int GetCarNumDis(const char * str1, const char * str2);
	int IsSimilar(const char c1, const char c2);
	int GetSimiDis(const char * str1, const char * str2);

	void CleanCache(vector<ObjMatchInfo> &vecCache, const unsigned int ts);											//�������������

#ifdef MV_LOCAL_DEBUG
public:
	void LogFile(vector<ObjMatchInfo> vecObj, const char *Path);
	void Match(vector<ObjMatchInfo> &vecA,vector<ObjMatchInfo> &vecB,const char *path, const char *unsure);
#endif


public:
	void mvInput(RECORD_PLATE_DSP_MATCH plate);
	vector<MatchPair> mvOutput();
	
};

#endif