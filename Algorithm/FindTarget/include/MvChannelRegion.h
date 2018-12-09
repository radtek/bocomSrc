#ifndef MV_CHANNEL_REGION_H
#define MV_CHANNEL_REGION_H

#include <vector>
#include "StdAfx.h"
#include "MvPolygon.h"
#include "MvPointList.h"
#include "NoPassingInfo.h"
#include "MvLine.h"

using namespace std;

enum ChannelDriveDir
{
	StraightForwardChannel = 0,         //ֱ�г�����
	TurnLeftChannel,                    //��ת������
	TurnLeftStraightForwardChannel,     //ֱ��+��ת������
	TurnRightChannel,                   //��ת������
	TurnRightStraightForwardChannel,    //ֱ��+��ת������
	Other = -1                          //������
};

/*
 �����ṹ�塣
*/
typedef struct _ChannelRegion
{
	
	int      nRoadIndex;	//�������
	int      nVerRoadIndex; //�����߼���ţ���ʱû���ô���
	int      nDirection;    //��������
	MvLine   vDirection;    //
	MvPointList vListChannel;     //��������
	bool     bNoTurnLeft;   //����
	bool     bNoTurnRight;  //����
	bool     bNoForeward;   //��ֹǰ��
	
	bool     bNoReverse;    // ��ֹ����
	bool     bNoPressLine;  //��ֹѹ�ߣ�
	bool     bNoChangeChannel;   //��ֹ�����
	bool     bNoPark;           //��ֹͣ��

	//������ʻ����:ֱ�г�������ת��������ת��������ת+ֱ�г�������ת+ֱ�г���,�ȣ�
	int      nChannelDriveDir;
	MvLine   vForeLine;  //ÿ����һ��ǰ���ߣ������ԭͼ���꣡���Ǵ���MvViolationDetecter��ֹͣ�ߺ�vDirection�����߶�Ϊ��Сͼ���꣬��һ��Ҫע�⣡

	//ÿ������һ��ֹͣ��
	MvLine   vStopLine;


	bool     bHoldSet;//���ô�ת״̬��
	bool     bFlagHoldStopReg;//��ת�Ⱥ�״̬��
	MvLine   vHoldForeLineFirst;
	MvLine   vHoldForeLineSecond;
	MvLine   vHoldStopLineFirst;
	MvLine   vHoldStopLineSecond;

	CvRect OnOffRed;
	CvRect OnOffGreen;
	
	//������
	CvRect roiLeftLight;
	CvRect roiMidLight;
	CvRect roiRightLight;
	CvRect roiTurnAroundLight;

	//�����ǿ�õ�
	CvRect roiLeftLight_red, roiLeftLight_green;
	CvRect roiMidLight_red, roiMidLight_green;
	CvRect roiRightLight_red, roiRightLight_green;
	CvRect roiTurnAroundLight_red, roiTurnAroundLight_green; 
	
	CvRect rectMedianPos;  //����ƻ�羯ʱ���ɿͻ���ָ���ĵڶ���ͼ�ĳ���λ�á�����̫���ϣ�������ת����ת�羯�Ϳ���ȡ���������е�ȡͼ���ðɣ�

	std::vector<NoPassingInfo>   vecNoPassingInfo; //��ֹͨ��ʱ���

	int    m_RedLightTime;//�ó����ĺ��ʱ�䳤��,����Ϊ��λ.

	_ChannelRegion()
	{
		nRoadIndex		= 0;
		nVerRoadIndex   = 0;
		nDirection      = 0;
		bHoldSet = false;
		bNoTurnLeft     = false;
		bNoTurnRight    = false;
		bNoForeward     = false;
		bNoReverse      = false;
		bFlagHoldStopReg = false;
		bNoPark = false;
		nChannelDriveDir = 0;  //Ĭ��Ϊֱ�г�����
		vForeLine.start = cvPoint(0, 0);
		vForeLine.end   = cvPoint(0, 0);

		//��ʼ����תͣ����
		vHoldForeLineFirst.start = cvPoint( 0, 0 );
		vHoldForeLineFirst.end = cvPoint( 0, 0 );

		vHoldForeLineSecond.start = cvPoint( 0, 0 );
		vHoldForeLineSecond.end = cvPoint( 0, 0 );

		vHoldStopLineFirst.start = cvPoint( 0, 0 );
		vHoldStopLineFirst.end = cvPoint( 0, 0 );

		vHoldStopLineSecond.start = cvPoint( 0, 0 );
		vHoldStopLineSecond.end = cvPoint( 0, 0 );




		OnOffRed   = cvRect(0, 0, 0, 0);
		OnOffGreen = cvRect(0, 0, 0, 0);

		roiLeftLight = cvRect(0, 0, 0, 0);
		roiMidLight = cvRect(0, 0, 0, 0);
		roiRightLight = cvRect(0, 0, 0, 0);
		roiTurnAroundLight = cvRect(0, 0, 0, 0);

		roiLeftLight_red = cvRect( 0,0,0,0 );
		roiLeftLight_green = cvRect( 0,0,0,0 );

		roiMidLight_red = cvRect( 0,0,0,0 );
		roiMidLight_green = cvRect( 0,0,0,0 );

		roiRightLight_red = cvRect( 0,0,0,0 );
		roiRightLight_green = cvRect( 0,0,0,0 );

		roiTurnAroundLight_red = cvRect( 0,0,0,0 );
		roiTurnAroundLight_green = cvRect( 0,0,0,0 );

		rectMedianPos = cvRect(0, 0, 0, 0);

		m_RedLightTime = 300;//��
	}


	static _ChannelRegion GetChannelInfoByIndex(const std::vector<_ChannelRegion> &lstChns, int Index)
	{
		std::vector<_ChannelRegion>::const_iterator it;
		for (it=lstChns.begin(); it!=lstChns.end(); it++)
		{
			if (it->nRoadIndex == Index)
			{
				return *it;
			}
		}
		
		assert(false);
		return _ChannelRegion();
	}

	//����λ�û�ó�����ţ�ԭͼ�����꣡
	static int GetChannelIndexByPos(const std::vector<_ChannelRegion> &lstChns, CvPoint pt)
	{
		int ret = -1;

		std::vector<_ChannelRegion>::const_iterator it;
		
		for (it=lstChns.begin(); it!=lstChns.end(); it++)
		{
			if (it->IsPointInRegion(pt))
			{
				ret = it->nRoadIndex;
				break;
			}
		}

		return ret;
	}
	
	//���ݳ�����Ż�ó�������
	static int GetChannelDirByIndex(const std::vector<_ChannelRegion> &lstChns, int Index)
	{
		assert(Index > 0);
		
		int ret = -1;

		std::vector<_ChannelRegion>::const_iterator it;
		for (it=lstChns.begin(); it!=lstChns.end(); it++)
		{
			if (it->nRoadIndex == Index)
			{
				ret = it->nDirection;
				break;
			}
		}

		return ret;
	}

	// �жϵ��ڲ��ڳ�����������
	bool IsPointInRegion(CvPoint pt) const
	{
		MvPointList pts = vListChannel;
		pts.push_back(vListChannel.front());
		MvPolygon poly(pts);
		return poly.IsPointInPoly(pt)==1;
		
	}

	void DrawChannel(IplImage *img)
	{
		MvPointList::iterator it1, it2;
		for (it1=vListChannel.begin(); it1!=vListChannel.end(); it1++)
		{
			it2=it1;
			it2++;
			if (it2==vListChannel.end())
			{
				it2=vListChannel.begin();
			}

			cvLine(img, cvPoint(it1->x, it1->y), 
				cvPoint(it2->x, it2->y), 
				CV_RGB(255, 255, 255));
		}
		
		it1=vListChannel.begin();
		char buffer[300];
		
		//sprintf(buffer, "nRoadIndex=%d,nVerRoadIndex=%d,nDirection=%d,bNoTurnLeft=%d,bNoTurnRight=%d,bNoForeward=%d,bNoReverse=%d,dirstart.x=%d", 
		//	nRoadIndex,nVerRoadIndex,nDirection,bNoTurnLeft,bNoTurnRight,bNoForeward,bNoReverse, vDirection.start.x);
		
		for (std::vector<NoPassingInfo>::iterator itt = vecNoPassingInfo.begin(); itt!=vecNoPassingInfo.end(); itt++)
		{
			//sprintf(buffer, "%s,nType=%d,nStart=%d,nEnd=%d", buffer, itt->nVehType, itt->nStart, itt->nEnd);
		}

		CvFont font;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.7f, 1.0f);
		DRAW_MV_LINE(img, &vDirection);
		cvPutText(img, "start", vDirection.start, &font, CV_RGB(255, 255, 255));
		cvPutText(img, "end", vDirection.end, &font, CV_RGB(255, 255, 255));

		
		cvPutText(img, buffer, cvPoint(0, it1->y), &font, CV_RGB(255, 255, 255));
	}


	
	// ���س�����û�н�������
	// timestamp��ǰʱ���뱾��0ʱ0��0�뾭����������
	bool HasNoPassingConstrain(int timestamp) const
	{
		std::vector<NoPassingInfo>::const_iterator nit;
		for (nit=vecNoPassingInfo.begin(); nit!=vecNoPassingInfo.end(); nit++)
		{
			if (timestamp > nit->nStart && timestamp < nit->nEnd)
			{
				return true;
			}
		}

		return false;
	}

	// �ж���һ���е�ĳ��ʱ�䣬ĳ��������û�н������ơ�
	// int timestamp ʱ�䡣
	static bool HaveNoPassingConstrain(const std::vector<_ChannelRegion> &vecChannelRgns, 
											int timestamp, int nRoadIndex)
	{
		std::vector<_ChannelRegion>::const_iterator cit;
		for (cit=vecChannelRgns.begin(); cit!=vecChannelRgns.end(); cit++)
		{
			if (cit->nRoadIndex == nRoadIndex)
			{
				if (cit->HasNoPassingConstrain(timestamp))
					return true;
			}
		}

		return false;
	}

	//ȡ�������С�ĳ�����ţ�
	static bool GetMaxMinChannelIndex(const vector<_ChannelRegion> &vecChns, int &nMaxRoadIndex, int &nMinRoadIndex)
	{
		if (vecChns.size() <= 0)
		{
			return false;
		}

		int nMaxIndex = -1, nMinIndex = MAX_INT;
		vector<_ChannelRegion>::const_iterator citCR;
		for (citCR = vecChns.begin(); citCR != vecChns.end(); citCR++)
		{
			int nTmpRoadIndex = citCR->nRoadIndex;
			if (nMinIndex > nTmpRoadIndex)
			{
				nMinIndex = nTmpRoadIndex;
			}
			if (nMaxIndex < nTmpRoadIndex)
			{
				nMaxIndex = nTmpRoadIndex;
			}
		}
		
		nMaxRoadIndex = nMaxIndex;
		nMinRoadIndex = nMinIndex;

		return true;
	}

}ChannelRegion;

#endif