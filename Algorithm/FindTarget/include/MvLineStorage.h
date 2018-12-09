/*
 *��Ĺ��ܣ��ڸ���ֱ�߱���ʱ��¼֡�ż�ֱ�ߣ������������ط���ȡֱ��ʱ���ã����Ż��������ܣ�
 */
#ifndef MV_LINE_STORAGE_H
#define MV_LINE_STORAGE_H

#include "MvLineSegment.h"


class MvLineStorage
{
public:
	MvLineStorage();
	~MvLineStorage();

public:
	void Update(unsigned int uFrm, const BLine *pAllLine, unsigned int lineNum);
	unsigned int GetCurrentFrm();
	bool GetLine(CvRect rectRoi, BLine **pRetLine, int &lineNum);

private:
	unsigned int m_uCurrentFrm;
	BLine *m_pLine;
	unsigned int m_uLineNum;

};

#endif