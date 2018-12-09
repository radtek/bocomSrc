// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cxcore.h>
#include <cv.h>
#include <vector>
#include "StdAfx.h"

//using namespace std;
typedef struct _LineInfoInRect
{
	float lineLenInRect;  //ֱ����Rect�ڵĲ��ֵĳ��ȣ�
	float rate; //ֱ����Rect�ڲ���ռ�����߶γ��ȵı�����
	CvPoint pt1, pt2;  //ֱ����Rect�ڵ����㣡
}LineInfoInRect;

class Geometry
{
public:
	static bool    IsTwoRectInteracting(CvRect r1, CvRect r2);
	static double  IsTwoRectPosMatch(const CvRect &r1, const CvRect &r2);
	static void    IsTwoRectPosMatch(const CvRect &r1, const CvRect &r2, double &ret1, double &ret2);
	static double  IsTwoRectPosMatchXY(const CvRect &r1, const CvRect &r2, double &ret1, double &ret2);
	static double  IsTwoRectLeftMatch(const CvRect &r1, const CvRect &r2);
	static double  IsTwoRectRightMatch(const CvRect &r1, const CvRect &r2);
	static CvRect  GetBoundingRect(const CvRect &r1, const CvRect &r2);
	static double  GetTwoRectsCenterDis(const CvRect &r1, const CvRect &r2);
	static void    GetTwoRectsBoudaryMinDis(const CvRect &r1, const CvRect &r2, double &xdis, double &ydis);
	static bool    GetTwoLinesUnion(int l1x1, int l1x2, int l2x1, int l2x2, float &fU1, float &fU2);  //����һάˮƽ�ߵ��ཻ�����
	static CvRect  GetCenRect(const CvRect &r1, CvPoint CenPoin);
	// ��������Rect�Ľ���Rect             
	inline static bool    GetUnionRect(CvRect r1, CvRect r2, CvRect &ret)
	{
		int lx = MAX_OF_TWO(r1.x, r2.x);
		int rx = MIN_OF_TWO(r1.x+r1.width-1, r2.x+r2.width-1);
		int ty = MAX_OF_TWO(r1.y, r2.y);
		int by = MIN_OF_TWO(r1.y+r1.height-1, r2.y+r2.height-1);

		if (rx <= lx || ty >= by)
		{
			return false;
		}

		ret.x = lx;
		ret.y = ty;
		ret.width = rx-lx + 1;
		ret.height= by-ty + 1;
		return true;
	}
	
	inline static void    GetBoundRect(CvRect r1, CvRect r2, CvRect &ret)
	{
		int lx = MIN_OF_TWO(r1.x, r2.x);
		int rx = MAX_OF_TWO(r1.x+r1.width-1, r2.x+r2.width-1);
		int ty = MIN_OF_TWO(r1.y, r2.y);
		int by = MAX_OF_TWO(r1.y+r1.height-1, r2.y+r2.height-1);

		ret.x = lx;
		ret.y = ty;
		ret.width = rx-lx + 1;
		ret.height= by-ty + 1;

	}

	// �������������ļнǡ������һ��������0�������׳��쳣��
	static double   GetAngleBetweenTwoVector(double vx1, double vy1, double vx2, double vy2);
	static bool    IsRectAContainsB(const CvRect &a, const CvRect &b);
	static bool    IsPointInRect(CvPoint2D32f p, const CvRect &r);
	static bool    IsPointInRect(CvPoint p, const CvRect &r);
	static bool    IsLinePassRect(const CvPoint &p1, const CvPoint &p2, const CvRect &rect);

//	template <class T>
	static bool    IsTwoLineSegCross(const CvPoint &line1start, const CvPoint &line1end, const CvPoint &line2s, const CvPoint &line2e);
	static bool    IsTwoLineSegCross(const CvPoint2D64f &line1start, const CvPoint2D64f &line1end, const CvPoint2D64f &line2s, const CvPoint2D64f &line2e);
	//�ж��߶�����μ�ļ��ι�ϵ�����أ�0���߶��ھ����⣻1���߶��ھ����ڣ�2.�߶�������ཻ��
	static int     RelationBtwLineAndRect(CvPoint line_start, CvPoint line_end, CvRect rect, LineInfoInRect &lineInRect, int &nIntersectionNum);
	//ȡ��ֱ����Rect�еĲ��֣������˵㡢���ȼ���ռ�߶��ܳ��ȵı�����
	static void    GetLineInRect(CvPoint line_start, CvPoint line_end, CvRect rect, LineInfoInRect &lineInRect);
	static float   CrossMultiply(CvPoint p1, CvPoint p2, CvPoint p0);
	static float   CrossMultiply(CvPoint2D64f p1, CvPoint2D64f p2, CvPoint2D64f p0);
	static int    PointtoRectDis(CvPoint p, const CvRect &r);

	/**
	* Compute the intersection between two line segments, or two lines
	* of infinite length.
	* 
	* @param  x0              X coordinate first end point first line segment.
	* @param  y0              Y coordinate first end point first line segment.
	* @param  x1              X coordinate second end point first line segment.
	* @param  y1              Y coordinate second end point first line segment.
	* @param  x2              X coordinate first end point second line segment.
	* @param  y2              Y coordinate first end point second line segment.
	* @param  x3              X coordinate second end point second line segment.
	* @param  y3              Y coordinate second end point second line segment.
	* @param  intersection[2] Preallocated by caller to double[2]
	* @return -1 if lines are parallel (x,y unset),
	*         -2 if lines are parallel and overlapping (x, y center)
	*          0 if intersection outside segments (x,y set)
	*         +1 if segments intersect (x,y set)
	*/
	static int     GetLineSegIntersection(double x0, double y0, double x1, double y1,
						double x2, double y2, double x3, double y3, double* intersection);


	// -1��rect���ߵ����/�±ߡ�0�ཻ��1�ϱ�/�ұ�
	static int     GetPosRelationBetweenLineAndRect(CvPoint pt1, CvPoint pt2, CvRect rect, bool bFlag = false, float fScalWidht = 0.2 );


	// r1 = r1-r2;�����ڼ��������
	// ֻ��������rect�߶���y��ͬ��������rect�����ཻ
	static CvRect  SubtractRect(CvRect &r1, const CvRect &r2);

	static int JudgeXUnit(CvRect Src, CvRect Dst, float fXRioTrd=0.5 ,bool IsGetRio = true,bool ComparSrc = false );

	static bool JudgeYUnit(CvRect Src, CvRect Dst,float fYRioTrd);

	// 
	static void  SubtractRect(CvRect r1, CvRect r2, std::vector<CvRect> &ret);


	static void  SubtractRect(std::vector<CvRect> v1, std::vector<CvRect> v2, std::vector<CvRect> &ret);


	// ��һ��rect��Ϊ����.����е�λ�ú�rect���ཻ�򷵻�false��
	// ���򷵻�true������dest�洢�����г�����rect��
	static bool    SplitRect(CvRect src, int splitPos, CvRect *dest);
	
	// ��һ��rect�п���rects������Ż����ص���һЩrect��
	static void    SplitRects(std::vector<CvRect> &rects, int nSplitPos);
	
	// ���Խ�һ�黥���ص���rects��һ�£�����ֵ�����û�����С�
	// �������aSplitedRes�д洢�����к���ѿ�������rect
	static bool    TrySplitRect(const std::vector<CvRect> &rects, int nSplitPos, CvRect aSplitedRes[2]);


	static bool    IsTwoPointClose(const CvPoint &p1, const CvPoint &p2, float dis);


	// ����rect��
	// rect.x *= fScaleX;
	// rect.w *= fScaleX;
	// rect.y *= fScaleY;
	// rect.h *= fScaleY;
	static void    ResizeRect(CvRect &rect, float fScaleX, float fScaleY);

	//����㵽ֱ�ߵľ���
	static float   CalculateDistanceBetweenPoint2Line(const CvPoint &pt,
												   const CvPoint &pt1OfLine,const CvPoint &pt2OfLine);

	static float   CalculateDistanceBetweenPoint2Line(const CvPoint2D64f &pt,
												   const CvPoint2D64f &pt1OfLine,const CvPoint2D64f &pt2OfLine);
	//��������֮��ľ���
	static float	   CalculateDistanceBetween2Points(const float &x1, const float &y1, const float &x2, const float &y2);


	static CvRect      GetBoudingRect(const std::vector<CvPoint> &pts);

	static CvRect      GetBoudingRect(CvRect r, CvPoint pt);

	static bool IsXDir(const CvRect &r1, const CvRect &r2);

	static int PoinInLine(const CvPoint &p1, const CvPoint &p2,const CvPoint &point);




	///////////////////////////////////////////////////////////////////////
	//  ����:
	//     double P1X,P1Y             -�߶ε��������
	//	   double P2X,P2Y             -�߶ε��յ�����
	//     int    nHeight,nWidth      -ͼ��ĸߺͿ�
	//     double w                   -�߶εĿ��
	//     int    &nPixelNum          -�߶��ϵ����ص���
	//	   int    *nPixelXY           -�߶��ϵ�����λ��
	//  ˵��:
	//     �ú���ʵ�ֻ�ȡ������������ȷ�����߶��ϵ��������ص�(��ͼ��)      \
	//   by hyp
	/////////////////////////////////////////////////////////////////////////
	static bool        GetPixelsOnLine(double P1X, double P1Y, double P2X, double P2Y, 
		int nHeight, int nWidth, double w, int &nPixelNum, int *nPixelYX);


	// r1��r2�Ƿ���x�����ǱȽϿ�����
	static bool        IsTwoRectCloseX(const CvRect &r1, const CvRect &r2, int dis);

	// r1��r2�Ƿ���y�����ǱȽϿ�����
	static bool        IsTwoRectCloseY(const CvRect &r1, const CvRect &r2, int dis);

	static CvPoint   GetRectCentre(const CvRect &Rec);

	static CvRect  ExpandRec (const CvRect &Rec,float ExpRio);
};


#endif
