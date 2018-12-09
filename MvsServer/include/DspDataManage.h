#ifndef DSP_DATA_MANAGE
#define DSP_DATA_MANAGE
#include "global.h"
#ifndef ALGORITHM_YUV
#ifndef ALGORITHM_DL
#include "CarnumParameter.h"
#else
#include "Mv_CarnumDetect.h"
#endif
#include "MvVehicleClassify.h"
#include "MvFindTargetByVirtualLoop.h"
#include "CvxText.h"
#include "LabelRecognition.h"
#include "ColorRecognition.h"
#ifndef ALGORITHM_DL
#include "Mv_CarnumDetect.h"
#endif
#include "DspDataProcess.h"

typedef std::list<string> listPicData;
typedef std::map<UINT32, listPicData> mapPicData; //�������-ͼƬ����ӳ��
typedef std::map<Picture_Key,listPicData> mapPKPicData;//�������ţ�ͼƬ֡�ţ�-ͼƬ����ӳ��

#define  IMAGEBUFUNIT	80 //Jpg�����С
#define  MAX_TIME_DIS	420	//�����Чʱ����,500s
#define MAX_TIME_DEAL  1200 //���ǿ�����ʱ����,1200s

class CDspDataProcess;

typedef struct tagImageBuf
{
	int nImgWidth;
	int nImgHeight;
	IplImage* imgSnap;//����
	IplImage* imgComposeSnap;// Υ��
	IplImage* imgComposeResult;// Υ�½��
	bool bUsed;

}SImageBuf,*PSImageBuf;

typedef struct tagDataProcess
{
	UINT32 uCameraId;
	UINT16 nCameraType;
	UINT16 nType;// 2:���� 10:Υ��

	SImageBuf imgBufForSimplePic;
	SImageBuf imgBufForComposePic;
	SImageBuf imgComposeResultPic;

	BYTE* pBuffer;
}SDataProcess,*PSDataProcess;

typedef struct tagDspDataManage
{
	int nIndex;
	void* pManage;
}SDspDataManage,*PDspDataManage;

typedef struct tagDspOutPutKeyTemp
{
	Picture_Key key;
	int64_t ts;
	int64_t tsRecv;	//��������ʱ��
	CDspDataProcess* pDataProc;

	bool operator < (const tagDspOutPutKeyTemp& other) const
	{
		if(tsRecv < other.tsRecv)
		{
			return true;
		}
		else if (ts < other.ts)        //��ʱ�������
		{
			return true;
		}
		else if (ts == other.ts)  //���֡����ͬ���������ID��������
		{
			return key < other.key;
		}

		return false;
	}
} SDspOutPutKeyTemp, *PDspOutPutKeyTemp;

typedef std::map<SDspOutPutKeyTemp, string> CarnumMap;

class CDspDataManage{
public:
	CDspDataManage(int nDataCount = 10);
	~CDspDataManage();

public:
	//��ʼ��
	bool InitDspData(int nChannelId, CHANNEL_DETECT_KIND nDetectType = DETECT_NONE);
	bool AddFrame(char* pBuffer);
	int DataProcessThreadFor200W();
	int DataProcessThreadFor500W();
	int DoDataProcessFor200W(int nIndex);
	int DoDataProcessFor500W(int nIndex);

	int DataProcessThreadOutPutTemp();
	int DoDataProcessOutPutTemp(int nIndex);

	bool GetImageByJpgKey(const Picture_Elem &PicElem,PLATEPOSITION *pTimeStamp,IplImage* pImage);
	int GetServerIpgCount();

	//�˲��Ƿ����ͼƬ
	bool CheckCarNumOutPut(const Picture_Key &Pic_Key, const int64_t &ts);
	//����Picture_Key,ʱ���,��JpgMapȡͼ
	bool FindPicFromJpgMap(Picture_Key key, int64 ts, string &strPic);
	//ȷ���Ƿ�,�ܸ���Picture_Key,ʱ���,��JpgMapȡ��ͼ
	bool IsFindPicFromJpgMap(Picture_Key key, int64 ts);

private:
	bool AddJpgFrame(BYTE* pBuffer);
	//void GetPicByKeyFromMap(Picture_Key pickeyDst, string& strPic);
	int RemoveServerJpg(Image_header_dsp *pHeader);

private:
	int m_nChannelId;
	int m_nDataCount;
	int m_nThreadCntFor200W;
	int m_nThreadCntFor500W;

	int m_nThreadCntForTemp;

	//�ı�����߶�
	int m_nExtentHeight;
	int m_nWordPos;

	//jpg������
	pthread_mutex_t m_JpgFrameMutex;
	pthread_mutex_t m_WaitFor200WMutex;
	pthread_mutex_t m_WaitFor500WMutex;

	pthread_mutex_t m_OutPutMutex;

	//�ؼ���Ϊ֡�ź���������ɵĽṹ���JPG��ͼ����(�����Ϊ�����)
	//map<Picture_Key,string> m_ServerJpgFrameMap;
	 JpgMap m_ServerJpgFrameMap;

	static int               m_DataExit;//�����˳���ʶ

	vector<string> m_mapWaitListFor200W;
	vector<string> m_mapWaitListFor500W;
	unsigned long long 	m_nWaitNumFor200W;
	unsigned long long 	m_nWaitNumFor500W;

	CarnumMap m_mapCarnumOut; //�����������
	unsigned long long 	m_nWaitNumForTemp;
	int m_nTestSeq;
	CHANNEL_DETECT_KIND m_nDetectKind;
};


#endif
#endif
