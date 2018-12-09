// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef MVLINEPROCESS_H
#define MVLINEPROCESS_H

#include <vector>

#include "MvLineSegment.h"
using namespace std;

#ifndef EPSILONN
#define EPSILONN (0.00000001f)
#endif

class MvLineProcess  
{
public:
	MvLineProcess(void);

	virtual ~MvLineProcess(void);

	static void mvSortTwoPointByXCoordinate_SH( vector<LSDLine> &srcLine );

	static void mvSortTwoPointByYCoordinate_SH( vector<LSDLine> &srcLine );

	static void mvSortTwoPointByYCoordinate_SH( LSDLine *srcLine, int nLineNumber );

	static void mvSortTwoPointByXCoordinate_SH( LSDLine *srcLine, int nLineNumber );

	static void mvSortLinesAscending_MedianY(vector<LSDLine> &line);

	static void mvSortLinesAscending_X(vector<LSDLine> &line);

	static void mvPointToLineDistance(const CvPoint2D32f &pt, const double &k, const double &b, double &dis);

	static void mvThreeLineOverlappingRatio(const double &pt10, const double &pt11, 
		const double &pt20, const double &pt21, double &overlappingRatio);
	static void mvTwoLineOverlappingRatio(const double &pt10, const double &pt11, 
		const double &pt20, const double &pt21, double &overlappingRatio);
	static void mvGetTwoPointOverlapping(const double &pt10,const double &pt11, const double &pt20,
		const double &pt21, double &m, double &n);


public:
	/************************************************************************
	*pt1 ֱ���ϵ�
	*pt2 ֱ���ϵ�
	*k ����ֱ�ߵ�б��
	*b ����ֱ����y���ϵĽؾ�
	************************************************************************/
	inline static bool mvGetLineParametter(const CvPoint2D32f &pt1, const CvPoint2D32f &pt2, double &k, double &b) 
	{
		k = b = 0;
		//��ֱֱ��
		if (fabs(pt1.x-pt2.x) < EPSILONN) 
		{
			return false;
		}
		k = (pt1.y - pt2.y) / (pt1.x - pt2.x);
		b = pt1.y - pt1.x * k; //ʹ��ͼ�����Ͻ�Ϊ����ϵ���

		return true;
	}

	/************************************************************************
	*pt1 ֱ���ϵ�
	*pt2 ֱ���ϵ�
	*coordinateX ��x������ƽ�е�ֱ���ཻ
	*nPosX ������xƽ������������λ��
	************************************************************************/
	inline static bool mvGetIntersectionPoint_X_SH(const double &k, const double &b, const double &y, double &x) 
	{
		if (k > EPSILONN || k < -EPSILONN)
		{
			x = (y - b) / k;
		}
		else 
			return false;

		return true;
	}

	/************************************************************************
	*pt1 ֱ���ϵ�
	*pt2 ֱ���ϵ�
	*x ��y������ƽ�е�ֱ���ཻ
	*y ������yƽ������������λ��
	************************************************************************/
	inline static bool mvGetIntersectionPoint_Y_SH(const double &k, const double &b, const double &x, double &y) 
	{ 
		if (k > EPSILONN || k < -EPSILONN)
		{
			y = k * x + b;
		}
		else 
			return false;

		return true;
	}


	template<class T>
	inline static void mvSwap_SH( T &a, T &b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}

	template<class T>
	/************************************************************************/
	/* �������ܣ������߶�x������������                                      */
	/************************************************************************/
	static void mvSortTwoPointByXCoordinate_SH( T &x1, T &y1, T &x2, T &y2 )
	{
		if ( x1 > x2 )
		{
			mvSwap_SH( x1, x2 );
			mvSwap_SH( y1, y2 );
		}
	}

	template<class T>
	/************************************************************************/
	/* �������ܣ������߶�Y������������                                      */
	/************************************************************************/
	static void mvSortTwoPointByYCoordinate_SH( T &x1, T &y1, T &x2, T &y2 )
	{
		if ( y1 > y2 )
		{
			mvSwap_SH( x1, x2 );
			mvSwap_SH( y1, y2 );
		}
	}




};


#endif
