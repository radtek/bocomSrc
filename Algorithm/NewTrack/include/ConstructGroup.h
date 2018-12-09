//group�γɺ͵���
#ifndef _MV_CONSTRUCT_GROUP_H_
#define _MV_CONSTRUCT_GROUP_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>

//#include <map>

#include "libHeader.h"

#include <algorithm>

#include "MvMathUtility.h" 

#include "MatchTrack.h"
#include "MvDistGraph.h"

#include "comHeader.h"  //�����

using namespace std;

using namespace MV_MATH_UTILITY;
using namespace MV_AN_DISTGRAPH;

#ifndef PTTR_SEGMENT_MAP_INIT_VAL
	#define PTTR_SEGMENT_MAP_INIT_VAL -1  //��켣����ƥ���map��ʼֵ
#endif

#ifndef SEGMENT_THRESHOLD
	#define SEGMENT_THRESHOLD(size, c) (c/size)
#endif

//�켣����ģ�͵���ʾ
#ifndef SHOW_TRACKS_DIFFERENT_MOD
	enum{
		SHOW_MOVE_UNCONS = 1,	  //�ι켣����˶���һ����
		SHOW_PTDIST_UNCONS,       //�ڵ���Ĳ�һ����
		SHOW_DIFF_VECTOR_VAL	  //�켣����������ֵ 
	};
#endif



//�켣�и�С�ε��˶���Ϣ
typedef struct TRACK_LITTLESEG_MVINFO
{
	//x/y������˶��Ƿ���Ч 
	bool  bVaild; 

	//�ù켣x/y����ľ���λ���ܺ�
	float fSum;

	//�öι켣x/y����ľ���λ��
	float fADiff[N_REF];

	//�öι켣x/y����ľ���λ�ƻ���
	float fAInteDiff[N_REF];

	//�öι켣x/y����ľ���λ��ռ�ܳ��ȵı���
	float fARate[N_REF];

	//�öι켣x/y����ľ���λ�Ʊ��ʵķֲ�����
	float fAPDF[N_REF];


	TRACK_LITTLESEG_MVINFO( )
	{
		bVaild = false;  	
		fSum = 0.0f;
	}

}StruTrLitSegMvInfo;

//��켣����ṹ��
typedef struct MV_PTTR_SEGMENT 
{
public:
	MV_PTTR_SEGMENT( )
	{
		initVar( );
	};

	//��ʼ������
	void initVar( );
	
	//��ʼ����켣����ṹ��
	void mvInitPtTracksSegment( AnGlobalSet *pGlobalSet );

	//�Ե�켣�����������ͷ�
	void mvUninitPtTracksSegment( );

	//�Ե�켣���о���
	void mvPointTracksSegmente( 	
			int nNoNullTrNum,	  //�ǿչ켣��Ŀ
			int *nANoNullTrIdx,   //�ǿչ켣����Ӧ�����
			MyTrackElem **pATrPointer //�켣��Ӧ�ĵ�ַ(ָ��)
		);

private:
	//�Ե�켣���о���֮ǰ���д���
	void mvProcessBeforeSegmente( 
			int nNoNullTrNum,	  //�ǿչ켣��Ŀ
			int *nANoNullTrIdx,   //�ǿչ켣����Ӧ�����
			MyTrackElem **pATrPointer, //�켣��Ӧ�ĵ�ַ(ָ��)
			vector<int> &vectWaitSegmentTr //�ȴ�����ָ�Ĺ켣
		);

	//��ȡ��켣�ϵĽڵ��˶���Ϣ
	void mvGetMoveInfoNodes( const MyTrack& tr,
			StruTrLitSegMvInfo &StruTrLSMvInfo
		);


	//�������켣�����Ĳ���ֵ
	float mvCalcVectorDiffVal( 
			const MyTrack &tr1,  //�켣1
			const MyTrack &tr2	 //�켣2
		);

	//�������켣�ڵ���벻һ����
	float mvCalUnconsistencyOfNodeDist( 
			const MyTrack &tr1,  //�켣1
			const MyTrack &tr2,	 //�켣2
			IplImage *pCarW,  //����ͼ��
			IplImage *pCarH,  //����ͼ��
			float &fRatio_x,  //��ǰ֡����x����복�����
			float &fRatio_y   //��ǰ֡����y����복�߱��� 
		);


	//�������켣�ڵ���벻һ����
	float mvCalMoveUnconsistency( 
			int nTr1, int nTr2, int nMinComLen, 
			StruTrLitSegMvInfo *pStruTrLSMvInfo
		);

	//�Ե�켣���о���֮����д���
	void mvProcessAfterSegmente( 
			int nNoNullTrNum,	  //�ǿչ켣��Ŀ
			int *nANoNullTrIdx,   //�ǿչ켣����Ӧ�����
			MyTrackElem **pATrPointer, //�켣��Ӧ�ĵ�ַ(ָ��)
			const vector<int> &vectWaitSegmentTr //�ȴ�����ָ�Ĺ켣
		);

	//��ʾ��켣�ɽ���Զ�Ĺ켣��ŵĽ��
	void mvShowSimilarityResult( 
			int nTrCnt,		//��ȡ�Ĺ켣��Ŀ
			int *nACorTrIdx,   //�켣��Ӧ�����
			MyTrackElem **m_pATrPointer,  //�켣��Ӧ�ĵ�ַ(ָ��)
			int nVaildEdgeCnt, //��Ч����
			MvSegmEdge *pEdges,  //�����켣����γɵı�
			int nShowMod		 //��ʾģʽ
		);

	//��ͼ���зָ�
	CSegmUniverse * mvSegmentGraph( 
			int num_vertices, 
			int num_edges, 
			MvSegmPoint4D *coors,
			MvSegmEdge *edges,	
			MvSegmDiff *pDiff,
			float c );

private:
	//ָ��ȫ����Ϣ����ָ��
	AnGlobalSet *m_pGlobalSet;
	
	bool m_bInit;	//�Ƿ�ɹ���ʼ��

private:
	IplImage *m_pSegmenteTrMap;	//�μӾ���Ĺ켣map

}StruPtTrSegment;

/*
typedef struct MV_GROUP 
{
	int  nGroupId;			//���
	bool bHaveCarnum;		//�Ƿ��������		
	int  nStatus;			//״̬,Ĭ��Ϊ0��

	CvRect rtContour;		//Ŀ������
	MvTrack tr;			    //Ŀ���������й켣,û�й�������ǰ������켣Ϊ��

	int nType;

	vector<int> vecTrackID;		//�洢�����ڸü����е�trackID
	
	MV_GROUP( )
	{
		nGroupId = -1;
		nStatus = 0;
		bHaveCarnum = false;
		nType = -1;
	}
}MvGroup;

typedef struct _mvSimpleObject 
{
	int     nGroupId;	//��Ӧ��group���
	int     nGroupNo;	//��Ӧ��group�����е����

	int     nObjType;    //Ŀ�������

	CvPoint ptCentroid;  //Ŀ�������

	float   fImgDirection; //Ŀ���ͼ����

	int64  ts_appear;  //Ŀ����ֱ�����ʱ��,msΪ��λ

	_mvSimpleObject( )
	{
		nGroupId = -1;
		nGroupNo = -1;

		nObjType = DEFAULT_TYPE;
		ptCentroid  = cvPoint(-1000, -1000); 
		fImgDirection = -1000.0f; 

		ts_appear = -1000000;
	}
}MvSimpleObject;


class CConstructGroup
{
public:

	//��ȡ�õ�Ŀ��Ĵ�Сͼ��
	void mvGetObjSzImg( IplImage *pHImg, IplImage *pWImg )
	{
		m_pObjHImg = pHImg,	m_pObjWImg = pWImg;
	};

	//��ȡ�õ���ǰ�Ĳ�����Ϣ
	void mvGetNowParaInfo( int dTs )
	{
		m_tsNow = dTs;
	};

	//�ɹ켣����Ϊgroup
	int mvConstructGroup( vector<MvTrack> vecTrack ); 

	//�����켣ID�͹켣֮���ӳ���ϵ
	void mvCreateIdTrackMap( vector<MvTrack> vecTrack );

	//��track����group�����м̳�
	void mvTrackGroup( vector<MvTrack> vecTrack );

	//��group������е���
	void AjustGroup( vector<MvTrack> &vecTrack );

	//��group�������ΪĿ��
	void SaveGroupAsObject( );

	//��ʾgroup���
	void mvShowGroupResult( IplImage *pShowImg, char *p_chWinName=NULL );

private:
	
	//����group��ID
	int _GenGroupId( );

	//�ɹ켣����group
	int GenerateGroup( vector<MvTrack> &vecTrack ); 

	//����ĳһ��������Ͻǵ�����½ǵ� 
	void AjustPoint(CvPoint pt, CvPoint &ptLT, CvPoint &ptRB);

	void AjustGroupContour( vector<MvTrack> &vecTrack, MvGroup &gr );

	bool IsNormalGroup( MvGroup &gr );

	int  GetSimTrNumInGroup( MvTrack &tr, MvGroup &gr, map<int,MvTrack> &mapTrack, float fTresh );

	bool IsNear( CvPoint pt, CvRect rt, float fThresh );

	bool AddTrackToGroup( MvTrack &tr, MvGroup &gr, map<int,MvTrack> &mapTrack, float fTresh );

	void MergeSplit(vector<MvTrack> &vecTrack, MvGroup &gr1, MvGroup &gr2);

	void MergeGroup(vector<MvTrack> &vecTrack, MvGroup &gr1, MvGroup &gr2);

public:
	map<int, MvTrack> m_mapTrack;	//trackID ��track��Ӧ��ϵ

	int m_nGroupIndex;             //group��ID
	vector<MvGroup> m_vecGroup;	   //������еĳ���

	vector<MvSimpleObject> m_vecObject;  //���Ŀ����Ϣ	
private:
	IplImage *m_pObjHImg;
	IplImage *m_pObjWImg;

	int m_tsNow;
private:

};
*/

#endif