// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

#ifndef FITTING_H
#define FITTING_H

class Fitting
{
public:

	// y = kx + b.���ֱ�߲���k��b�����ֱ���Ǵ�ֱ�ߡ�ver=true,ֱ�߷���Ϊx=b
	static void FittingLine(double *x, double *y, int size, bool &ver, double &k, double &b);


	static void TestFittingLine();
};


#endif