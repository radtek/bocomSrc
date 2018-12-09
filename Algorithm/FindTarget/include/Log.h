// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#if !defined(AFX_LOG_H__8A650BE4_FEAE_4BA5_833E_A992F5C7193C__INCLUDED_)
#define AFX_LOG_H__8A650BE4_FEAE_4BA5_833E_A992F5C7193C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

class Log  
{
public:
	Log(std::string filePath);
	void Write(std::string str);
	void WriteF(char *str, ...);
	void WriteLine(std::string str);
	void WriteLineHtml(std::string str);
	void WriteLineF(char *str, ...);
	void AddStage();
	void DecStage();
	virtual ~Log();

private:
	std::ofstream m_stm;
	int stage;//�����ȼ���0����������1������1�Ρ�����
	void WriteStage();
};

#endif // !defined(AFX_LOG_H__8A650BE4_FEAE_4BA5_833E_A992F5C7193C__INCLUDED_)
