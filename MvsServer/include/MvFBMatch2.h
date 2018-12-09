#ifndef __MV_FBMATCH2_H__
#define __MV_FBMATCH2_H__

#include <vector>
#include <cv.h>
#include "structdef.h"
using namespace std;

#define MAX_MATCH_SIZE 60 //< MAX_IMG_TAG_NUM/3
typedef std::map<int, vector<ObjMatchInfo> > VecMatchMap;

class MvFBMatch2
{
public:
	MvFBMatch2(void);
	~MvFBMatch2(void);

private:
	//const int m_nADirection, m_nBDirection;					//��¼ƥ��ķ���A,��β�ƣ�B��ǰ��
	vector<ObjMatchInfo> m_vecA/*, m_vecB*/;						//����
	vector<int> m_vecDiff;										//��¼ʱ���	
	unsigned int m_uLastMatchTimeA, m_uLastMatchTimeB;			//���ƥ��ʱ��
	VecMatchMap m_ChanIDAndFPlateMap;							//ͨ����ǰ�ƶ�Ӧ��
	vector<RECORD_PLATE_DSP_MATCH> m_NoMatchList;				//����δ�ҵ��ĳ���
private:
	int GetCarNumDis(const char * str1, const char * str2);
	int IsSimilar(const char c1, const char c2);
	int GetSimiDis(const char * str1, const char * str2);

	void CleanCache(vector<ObjMatchInfo> &vecCache, const unsigned int ts);	//�������������
	void WriteFPlateToMap(ObjMatchInfo & ObjMat);//д��ǰ��
	int mvDspCalcCarNumDis(const char *num1, const char *num2, int useSimilarChar); //ģ��ƥ�� 

#ifdef MV_LOCAL_DEBUG
public:
	void LogFile(vector<ObjMatchInfo> vecObj, const char *Path);
	void Match(vector<ObjMatchInfo> &vecA,vector<ObjMatchInfo> &vecB,const char *path, const char *unsure);
#endif

public:
	void mvInput(RECORD_PLATE_DSP_MATCH &plate);
	vector<MatchPair> mvOutput();	
	
	//�������
	pthread_mutex_t m_OutMutex;
	pthread_mutex_t m_MapMutex;
	unsigned int m_uUpdateFlag;//���¼�¼״̬��� 0:δ���� 1:����m_vecA 3:����m_vecB 

	void AddPlateNoMatch(RECORD_PLATE_DSP_MATCH &plate);
	bool PopPlateNoMatch(RECORD_PLATE_DSP_MATCH &plate);
	pthread_mutex_t m_OutMutex2;
};
extern MvFBMatch2 g_MvFBMatch2;
#endif