#ifndef MV_LINE_H
#define MV_LINE_H

#include <cxcore.h>

// ���ڱ�ʾֹͣ�ߡ����м���ߡ�ǰ�м���ߡ����м���ߵ�Line�ṹ�塣
typedef struct _MvLine
{
	// ͼ�����ꡣ
	CvPoint start;
	CvPoint end;

	// �������ꡣ
	CvPoint2D64f startw;
	CvPoint2D64f endw;


	// ����ͼ������x����н�
	float fAngle;

	float fAngleWorld;


	float fLength;

	float fLengthWorld;

	
	_MvLine()
	{
		start   = cvPoint(0, 0);
		end     = cvPoint(0, 0);
		startw  = cvPoint2D64f(0.0, 0.0);
		endw    = cvPoint2D64f(0.0, 0.0);
	}

	int x1() const
	{
		return start.x;
	}

	int y1() const
	{
		return start.y;
	}

	int x2() const
	{
		return end.x;
	}

	int y2() const
	{
		return end.y;
	}

	double x1w() const
	{
		return startw.x;
	}

	double y1w() const
	{
		return startw.y;
	}

	double x2w() const
	{
		return endw.x;
	}

	double y2w() const
	{
		return endw.y;
	}

	// ��ȡֱ�ߵ��е㣨��������ϵ��
	CvPoint2D32f GetMidPointWorld() const
	{
		return cvPoint2D32f((x1w() + x2w())/2, (y1w() + y2w())/2);
	}

	// ��ȡֱ�ߵ��е㣨ͼ������ϵ��
	CvPoint GetMidPoint() const
	{
		return cvPoint((x1() + x2())/2, (y1() + y2())/2);
	}


	void GetVectorWorld(float &vx, float &vy) const
	{
		vx = (float) (endw.x - startw.x);
		vy = (float) (endw.y - startw.y);
	}



} MvLine;



#define DRAW_MV_LINE(img, pline) cvLine((img), ((pline)->start), ((pline)->end), CV_RGB(255, 0, 0), 3);
#define DRAW_MV_LINE2(img, pline, color) cvLine((img), ((pline)->start), ((pline)->end), (color), 1);


#endif
