// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2009 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2009 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//


#ifndef OBJCOLOR_H
#define OBJCOLOR_H

#ifndef OBJECTCOLOR
#define OBJECTCOLOR
typedef struct OBJECT_COLOR
{
	int  nColor1;       //��ɫ1
	int  nColor2;	    //��ɫ2
	int  nColor3;       //��ɫ3
	
	int  nWeight1;    //��ɫȨ��1
	int  nWeight2;    //��ɫȨ��2
	int  nWeight3;    //��ɫȨ��3
	
	OBJECT_COLOR()
	{
		nColor1 = 11;
		nColor2 = 11;
		nColor3 = 11;
		nWeight1 = 0;
		nWeight2 = 0;
		nWeight3 = 0;
	}
} object_color;
#endif

#endif