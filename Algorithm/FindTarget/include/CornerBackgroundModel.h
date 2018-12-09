// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   10:28
	filename: 	e:\BocomProjects\find_target_lib\include\CornerBackgroundModel.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	CornerBackgroundModel
	file ext:	h
	author:		Durong
	
	purpose:	�ǵ㱳��ģ�ͣ�����˼�룺ͳ�ƹ�ȥһ��ʱ���ڸ������ش��ǵ���ֵ�
	������������ĵط��ܿ����Ǳ���ͼ��仯���ҵĵط�����Щ�ط��Ľǵ㱻��Ϊ�Ǳ���
	�ǵ㡣
*********************************************************************/

#ifndef CORNER_BACKGOUND_MODEL_H
#define CORNER_BACKGOUND_MODEL_H

#include <vector>
#include <list>
//using namespace std;

#define LIST_SIZE 300

#define CORNER_TEST

template <class _Point>
class CornerBackgroundModel
{
public:

	CornerBackgroundModel(int nXRes, int nYRes);

	~CornerBackgroundModel();

	void Input(_Point* pPts, int nPtSize);

	void GetForegroundCorners(_Point *pPts, int &nPtSize,const std::vector<CvRect> &CarGroupPark) const;

	void UpdateBackground();
	

private:

	int    GetMaxValueInMap() const;


	int    m_nXRes;  //X��Y�����ͼ���С
	int    m_nYRes;

	//
	int    m_nPointBufferMaxSize;

	int    m_nPointCount;
	
	// ����buffer
	_Point *m_pPointBuffer;

	// �������buffer�ɷ����ڸ��±���ģ�͡�
	// ������֮�󣬸�ֵ��Ϊfalse����ֹһ��ֵ���ظ����½�ģ�͡�
	bool m_bPointBufferUpdateAble;

	// ���ÿ��ͼ������λ�ó��ֽϽǵ�Ĵ�����
	int    *m_pMap;

	int    m_nMapMaxValue;

	typedef std::vector<_Point> _Pts;
	//typedef typename vector<_Point>::iterator _PtsIt;

	std::list<_Pts> m_lstPoints;
};






template <class _Point>
CornerBackgroundModel<_Point>::CornerBackgroundModel(int nXRes, int nYRes)
{
	m_nXRes        = nXRes;
	m_nYRes        = nYRes;
	m_nPointBufferMaxSize = nYRes * nXRes;
	m_pPointBuffer = new _Point[m_nPointBufferMaxSize];
	m_nPointCount  = 0;
	m_pMap         = new int[nXRes * nYRes];
	m_nMapMaxValue = 0;
	m_bPointBufferUpdateAble = false;

	for (int i=0; i<nXRes*nYRes; i++)
	{
		m_pMap[i] = 0;
	}
}

template <class _Point>
void CornerBackgroundModel<_Point>::GetForegroundCorners(_Point *pPts, int &nPtSize,const std::vector<CvRect> &CarGroupPark) const
{
	nPtSize = 0;
	std::vector<CvRect>::const_iterator CarParkIter; //Υ�³���ͣ������
	for (int i=0; i< m_nPointCount; i++)
	{
		int x = m_pPointBuffer[i].x;
		int y = m_pPointBuffer[i].y;

		assert(y < m_nYRes && x < m_nXRes );

		bool InPark = false; //��ͣ�������ڵĽǵ���Ϣ�����й���
		for (CarParkIter = CarGroupPark.begin();CarParkIter !=  CarGroupPark.end(); CarParkIter++)
		{
			if (x >= CarParkIter->x && x <= CarParkIter->x+CarParkIter->width 
				&& y >= CarParkIter->y && y <=CarParkIter->y + CarParkIter->height)
			{
				InPark = true;
				break;
			}
		}
		

		//����ýǵ����ʷλ���ϳ��ֵĴ�����=0.2 * m_nMapMaxValue���Ҵ���LIST_SIZE * 0.08 =24����й��˵�
		//m_nMapMaxValuedaֵ��ʾ��ǰm_pMap�г��ִ������ģ���UpdateBackground��ȡ
		if (m_pMap[y * m_nXRes + x] < 0.2 * m_nMapMaxValue || 
			m_pMap[y * m_nXRes + x] < LIST_SIZE * 0.08
			|| InPark)
		{
			pPts[nPtSize++] = m_pPointBuffer[i];
		}

	}
}

template <class _Point>
void CornerBackgroundModel<_Point>::Input(_Point* pPts, int nPtSize)
{
	for (int i=0; i<nPtSize; i++)
	{
		
		m_pPointBuffer[i] = pPts[i];
	}
	m_nPointCount = nPtSize;
	m_bPointBufferUpdateAble = true;
}


template <class _Point>

void CornerBackgroundModel<_Point>::UpdateBackground()
{
	int i;



	if (m_bPointBufferUpdateAble == false || m_nPointCount == 0)
	{	

		return;
	}
	//������ĸ�������LIST_SIZEʱ������ж������е�һ���������ݸ���
	//ͬʱ���¸���map��������ݣ�---ֻ��¼���ڽ���LIST_SIZE��������Ϣ


	if (m_lstPoints.size() == LIST_SIZE)
	{
		_Pts pts = m_lstPoints.front();


		
		typename std::vector<_Point>::iterator it;
		for (it = pts.begin(); it!=pts.end(); it++)
		{
			int x = it->x;
			int y = it->y;

			assert(y < m_nYRes && x <m_nXRes);



			m_pMap[y * m_nXRes + x] -= 1;  
			assert(m_pMap[y * m_nXRes + x] >= 0);
		}



		m_lstPoints.pop_front();   


	}
	
	_Pts pts;



	//�ѵ�ǰ���µõ��ǵ��λ�÷���map����ͳ����ͼ������ͬһλ�ó��ֵĴ���
	for (i=0; i< m_nPointCount; i++)
	{
		int x = m_pPointBuffer[i].x;
		int y = m_pPointBuffer[i].y;
		m_pMap[y * m_nXRes + x] += 1;



		pts.push_back(m_pPointBuffer[i]);
	}	
	//�ѵ�ǰ֡���µõ��ı����ǵ���ɵ�һ���������m_lstPoints��ȥ
	m_lstPoints.push_back(pts);	




    //�õ�m_pMap�г��ֵĴ��������ǽǵ���ͼ��ͬһ����ֵĴ���������һ��
	m_nMapMaxValue = GetMaxValueInMap();


	

	
}


template <class _Point>
int CornerBackgroundModel<_Point>::GetMaxValueInMap() const
{
	int max = 0;
	for (int i=0; i<m_nXRes * m_nYRes; i++)
	{
		if (m_pMap[i] > max)
			max = m_pMap[i];
	}
	return max;
}


template <class _Point>
CornerBackgroundModel<_Point>::~CornerBackgroundModel()
{
	if (m_pPointBuffer != NULL)
	{
		delete [] m_pPointBuffer;
		m_pPointBuffer = NULL;
	}

	if (m_pMap)
	{
		delete [] m_pMap;
		m_pMap = NULL;
	}
}

#endif
