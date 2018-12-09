#ifndef _MV_CSIFTRACK_H
#define _MV_CSIFTRACK_H

#include "declare.h"
#include "Mem_Alloc.h"
#include "Corner.h"
#include "MvSift.h"
//#include "MvTrack.h"
#include <vector>
#include "MvUtility.h"

using namespace std;

#define TRACKCOL

using namespace Shut_Corner;
namespace Shut_Track
{

	//��¼�ǵ���Ϣ
	typedef struct _MV_TRACK_POINT
	{
		int64 ts;
		short nStatus;  //0������Ƶ�
		CvPoint corner;

		_MV_TRACK_POINT()
		{
			ts = 0;
			nStatus = 0;
			corner = cvPoint(0,0);

		}
	} MvTrackPoint;

	//��¼�켣����Ϣ
	typedef struct _MV_TRACK
	{
		int nTrackId;   //�켣��ID

		short nEstTimes;  //�켣�й��ƽǵ������
		CvPoint ptPredict;  //�켣��Ԥ��ǵ�
		unsigned char *feature;

		MvTrackPoint *pTrackPoint;
		short nTrackLen;
		bool  bShut;
	

#ifdef TRACKCOL
		CvScalar TrackCol;
		bool     bColSet;
#endif

		_MV_TRACK()
		{
			nTrackId = -1;
			nEstTimes = 0;
			feature = NULL;
			pTrackPoint = NULL;
			nTrackLen = 0;
			bShut    = false;
			ptPredict = cvPoint(0,0);
			

#ifdef TRACKCOL
			bColSet = false;;
#endif
		}

	} MvTrack;



	class CsiftTrack
	{

	public:
		void mvInit(CvSize ImgSize,int **pnMaxSize,int nSizW);
		void mvProcessTrack(int nTrackLenTresh );
		void mvGetConerData( MvCornerParm ConerPam);
		void mvSetTrackShutStatInRegi(CvRect RegionRec);
		void mvGetTrackIdInRegi(CvRect RegionRec,int &nTrackNum ,int &nTrackShutNum);
		void mvGetInRegiPoint(CvRect RegionRec,int nDisTrd,vector<CvPoint> &TrackPoint);
		void DrawTrack(IplImage *pImg,MvTrack *pTrack,CvScalar col);
		void DrawAllTrack(IplImage *pImg,CvScalar col);
		void mvUnInit();
		CsiftTrack();
		~CsiftTrack();

	private:
		

		void mvRemoveUnreasonableTracks();
		void   mvPredictTrack(MvTrack *pTrack,CvSize Size);
		CvRect mvFindMatchRect(MvTrack *pTrack);
		int    mvFindMatchTrackPoint(MvTrack *pTrack, CvRect rt, int *pCornerPos, int *pCornerTrackDis);


		bool    mvIsTrackReasonable(MvTrack *pTrack);
		int    mvGenTrackId(void);
		void mvMacthTrackOri();//�켣Ѱ��ƥ���
		void mvUpdataTrackOri();//���¹켣
		void mvSetTrackFil(int nTrackLenTresh);
		void mvInitMacPoi();
		void mvGenerateNewTrack();
		

	private:
		ushort **m_MaxSizeX;  //
		ushort **m_MaxSizeY;   //
		CvSize m_ImgSize;

		int m_nPointsCount;  //�ǵ�����
		CvPoint *m_pCornPoints;  //�ǵ�����λ�� 
		uchar **m_pFeature;  //�ǵ��sift������
		char  *m_pMatchStatus;  //�ǵ��ƥ��״̬



		int m_nTrackIndex;
		int *m_pCornerPos;
		int *m_pTrackPos;
		int *m_pCornerTrackDis;
		int m_nCornerTrackCount;  //�ǵ�͹켣��ƥ����Ϣ


		MvTrack *m_pTrackOri;
		int m_nTrackCntOri;  //����ǰ�켣��������Ϣ

		MvTrack *m_pTrackFlt;
		int m_nTrackCntFlt;  //���˺�Ĺ켣��Ϣ 



		//�켣
		MvTrack *m_pTrack;
		int m_nTrackCnt;  //�켣��������Ϣ

		int  m_GroupCnt;


		bool m_bInitSucs;

	};

};
#endif
