#pragma once
#include <cv.h>

using namespace cv;



typedef struct Target
{
	Rect rRect;//Ŀ��λ����Ϣ

	double dConfidece; //Ŀ�����Ŷ�
};


typedef struct TargetInfo
{
	int nClassType;//Ŀ����𣬴�1��ʼ������ģ�ͼ���˳����

	Target tTarget;//Ŀ����Ϣ
};


class MvDetect;

class MvMulObjDetect
{

public:

	MvMulObjDetect(void);

	~MvMulObjDetect(void);


	//ԭʼ�ӿڣ�����������
public:

	//��ȡ�汾��
	static char* mvGetVision();
	
	bool mvInitDetectModel(char* );

	void mvUnInitDetectModel();


	/*����汾�ӿڣ���Ӧ��ΰ*/

	//�������ӿڣ�����ͼ�񣬼�⵽Ŀ��λ�ã����Ŷȣ����Ŷ���ֵ,����ϲ�������Ĭ�ϲ��ϲ�
	void mvSingleClassDetect(Mat mImg,vector<Target>&vTarget,double dThres=30.0,double dCover=2.0);


	//����������ģ��
	bool mvInitMultiModel(char*,char*);

	void mvUnInitMultiModel();

	//������ӿڣ�����ͼ�񣬼�⵽Ŀ��λ�ã����Ŷȣ����Ŷ���ֵ������ϲ�������Ĭ�ϲ��ϲ�
	void mvMultiClassDetect(Mat mImg,vector<Target>&vClass1,
		vector<Target>&vClass2,double dThres=30,double dThres1=30,double dCover=2.0);



/*�¼�N����ӿڣ�������ٸ����ģ�ͣ������ٸ���� */
public:

	//����N����ģ��,ClassifierΪ������·�����ƣ�nClassΪ�����
	bool mvInitMulti(char**Classifier ,int nClass);

	//�����ͷź���
	void mvUnInitMulti();


	//N��Ŀ����ӿڣ�����ͼ�񣬼�⵽Ŀ����Ϣ�����Ŷ���ֵ���飬Ŀ��ϲ�������ͼ�񳤱����ų��ȣ�1.0������
	void mvNClassDetect(Mat mImg,vector<vector<Target> >&vTarget,
		double* dThres,double dCover=2.0,double dMaxLength=1.0);




private:

	MvDetect* mMultiDetect;

	//�߽籣��
	vector<Target> mvRationality( vector<Target>& V, const Mat pImage );

	double mvRectCoverRate( Rect r1, Rect r2 );   //�����������ε��ص���

	Rect mvRectCombineBig( Rect r1, Rect r2 );

	//Ŀ��ϲ�����
	int mvRectGroup( vector<Target>& V,double dThres);

};