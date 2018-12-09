// ����������Ƶ���ʶ����� V2.0
// Bocom Intelligent Video Detection & Recognition Software V2.0
// ��Ȩ���� 2008-2010 �Ϻ�����������Ϣ�������޹�˾
// Copyright 2008-2010 Shanghai Bocom Intelligent Information Technologies Ltd
// �������ܹ�˾����   Bocom Intelligent Information Technologies Ltd Confidential Proprietary
//

/********************************************************************
	created:	2010_10_8   15:05
	filename: 	e:\BocomProjects\find_target_lib\include\NoPassingInfo.h
	file path:	e:\BocomProjects\find_target_lib\include
	file base:	NoPassingInfo
	file ext:	h
	author:		Durong
	
	purpose:	�����Ľ�����Ϣ��
*********************************************************************/

#ifndef NO_PASSING_INFO_H
#define NO_PASSING_INFO_H

//#define ODD_ODD 0x01 //����
//#define ODD_EVE 0x02

#define MON 0x01//��һ
#define TUE 0x02//�ܶ�
#define WEN 0x04//����
#define THU 0x08//����
#define FRI 0x10//����
#define SAT 0x20//����
#define SUN 0x40//����
#define WEK 0x7F//ȫ��
#define WED 0x60//����������
#define WKD 0x1F//��һ�����壬������

// ��ֹͨ����Ϣ��
// ������ֹͨ�е�ʱ��Σ��Լ���ֹͨ�еĳ������͡�
typedef struct _NoPassingInfo
{
	unsigned char ucWeekDay; //��ֹͨ�е����졣���԰�λ��

	int nStart;   // ��ֹͨ��ʱ��Ͽ�ʼ����0ʱ0��0�뵽��ֹͨ��ʱ���������
	int nEnd;     // �����1�㵽�����ǽ���ʱ�䣬��nStart = 1*60*60, nEnd = 2*60*60

	int nVehType; // //0��ʾ�����У�1��ʾ����С����2��ʾ���д󳵣�3��ʾ�������г���

	_NoPassingInfo()
	{
		ucWeekDay = WEK;
		nStart    = -1;
		nEnd      = -1;
		nVehType  = 0;
	}
} NoPassingInfo;

#endif