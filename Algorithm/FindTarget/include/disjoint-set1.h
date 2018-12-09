/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
graph-based track clustering
*/


#ifndef DISJOINT1_SET_H
#define DISJOINT1_SET_H

#include <vector>
#include <map>
#include <cxcore.h>

//using namespace std;
// disjoint-set forests using union-by-rank and path compression (sort of).

typedef struct _ClusterRect{
	float minx, miny, maxx, maxy;
	_ClusterRect()
	{
		minx=-1;
		miny=-1;
		maxx=-1;
		maxy=-1;
	}
} ClusterRect;

typedef struct
{
	int rank;
	int p;
	int size;
	//int weight;
	int minx,miny,maxx,maxy;  //four corners of the area
	//int minx45,miny45,maxx45,maxy45;  //45 degress rotated four corners of the area
	//int area;	//��С��Χ���ε����
	int extra;
	int nId;
} Uni_elt;




typedef struct EDGE
{
	float w;
	float DisW;
	int a,b;
#ifdef MV_DSP_SURPPORT_STL
	MV_DSP_EDGE()
	{
		a = 0;
		b = 0;
		w = 1000;
		DisW = 1000;
	}
#endif
}Edge;






typedef std::vector<int> Elements;
typedef std::map<int, Elements> GroupIdToElesMap;

class Universe
{
public:


	//
	Universe(int elements, Uni_elt *coors);		//elementsΪ�ܶ�����

	//
	~Universe();

	
	// ����x��������������ţ���
	int Find(int x);




	// ��ȡ��������
	CvRect GetClusterRgn(int x);

	// ������ϣ������Ϻ���ߴ��ڸ�����ֵ�򷵻�ʧ�ܡ����򷵻سɹ���
	bool TryJoin(int x, int y, int wThres, int hThres);


	CvRect TryJoin(int x, int y);


	// �ϲ����Ϊx��y���������
	void Join(int x, int y);

	void GetPrintInfo();	


	
	// ��ʼԪ�ظ���
	int Size(int x) const { return elts[x].size; }

	
	// ����ǰ������
	int GetEleNum() const { return oriEleNum; }

	// �����������
	int GetSetsNum() const { return num; }

	// ��ȡ����Ľ��
	void GetClusterRects(std::vector<ClusterRect> &ret);
	
	// ��ȡ����Ľ��
	void GetClusterRects(std::vector<CvRect> &ret);

	//��ȡ����Ľ����ֻ����Ԫ�ظ�������sizeThresh����
	void GetClusterRects(std::vector<CvRect> &ret, int sizeThresh);
	

	// ��ȡgroup�����һ�ȡÿ��group�İ�����Ԫ����ţ��͹���ʱ���������ͬ��
	void GetClusterRects(std::vector<CvRect> &ret, int sizeThresh, GroupIdToElesMap &mapGroupIdToEles);

	// ��ȡ������
	void GetClusterRects(std::vector<Uni_elt> &ret);

	
	typedef std::vector<Uni_elt> Group;
	typedef std::map<int, Group> Groups;
	typedef std::map<int, Group>::iterator GroupsIt;

	void GetClusterResult(Groups &groups);

	// 
	Uni_elt* GetElementPoint(int x);

	Uni_elt* GetElement(int x);

private:
	Uni_elt *elts;	//�ṹ��Ԫ��ָ��
	int oriEleNum;  // ��ʼԪ�ظ���
	int num;		//�ϲ���ʣ���������

};

#endif
