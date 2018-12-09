//�ж��Ƿ�ΪͬһĿ��ļ����
#ifndef __SAME_OBJECT_CHECK_H
#define __SAME_OBJECT_CHECK_H

#include <vector>
#include "libHeader.h"
#include "comHeader.h"

using namespace std;

#define MAX_SAVE_REMOTE_PICNUM 4   //����������Զ��ͼ����Ŀ
#define MAX_SAVE_STOPAREA_NUM 100  //����������ֹͣ������Ŀ
#define MAX_PTNUM_OF_STOPAREA 100  //ֹͣ�������Ľǵ���Ŀ

enum enumCheckMode  //����Ƿ�Ϊͬһ���¼���Ŀ��
{
	CHECK_SAME_STOP_OBJ = 0,
	CHECK_SAME_OTHER_OBJ	
};

//Id������
typedef struct StructIdAssign
{
public:
	int m_nId;

public:
	StructIdAssign( );

	void mvInitVar( );  //��ʼ������
	void mvIdAdd( );    //��ID��������
 
}AnIdAssign;


//�¼�ID������
typedef struct StructEventIdAssign
{
public:
	AnIdAssign m_stopEventIdAssign;  //ֹͣ�¼�ID������

public:
	StructEventIdAssign( );

	void mvInitVar( );               //��ʼ������
	bool mvIdAdd( int nCheckMode );  //��ID��������
	int  mvGetId( int nCheckMode );  //��ȡ��ǰҪ�����¼���ID
		 
}AnEventIdAssign;


//ֹͣ����ڵ�ṹ
typedef struct StructStopAreaNode
{
public:
	double dTsAdd;         //�ڵ�ļ����ʱ���
	double dTsUpdate;      //�ڵ�ļ���ĸ��´�

	CvPoint ptLtStopArea;  //�ڵ�����Ӧ��ͣ���������ϵ�
	CvPoint ptRbStopArea;  //�ڵ�����Ӧ��ͣ���������µ�

	int		 nPtCnt;	   //�ǵ���Ŀ 
	siftFeat pSiftFeat[MAX_PTNUM_OF_STOPAREA];  //���ǵ������
public:
	StructStopAreaNode( );

}AnStopAreaNode;


//ֹͣ����洢�ṹ
typedef struct StructStopObjStore
{
public:
	double dTsAdd;		  //������ļ���ʱ���
	int    nStopObjId;	  //����������Ӧ��ֹͣĿ���ID

	CvRect rct4CamCtrl;   //�������ʱ��rect����

	int  nSaveNodeCnt;    //�������ѱ���Ľڵ���Ŀ
	int  nHadSavePicCnt;  //�������ѱ����ͼƬ��Ŀ
	AnStopAreaNode stopAreaChain[MAX_SAVE_REMOTE_PICNUM]; //ֹͣ����Ĵ洢��

public:
	StructStopObjStore( );

}AnStopObjNode;


//���"�豣�����Զ��Ԥ��λͼ"�����"�Ƿ�Ϊ��ֹͬͣ����"
typedef struct StruSameStopAreaCheck
{
public:
	StruSameStopAreaCheck( );

	void mvInitVar( );

	//��ʼ��
	void mvInitSameStopAreaCheck( );

	//���õ��ƥ�䷶Χ
	void mvSetPtMatchRange( const CvPoint &ptMatchRange );
	
	//�ͷ�
	void mvUninitSameStopAreaCheck( );

	//��������Ŀ���Ƿ���ֹͣ����洢��
	int mvCheckAndSaveGiveObj(
			double dTsNow,           //��ǰ��ʱ���
			double dMinInterval,	 //��ǰ������ڵ����С��� 
			const CvPoint &ptLtArea, //������ֹͣ�������ϵ�
			const CvPoint &ptRbArea, //������ֹͣ�������ϵ�
			const int nPtCnt,       //������ֹͣ�ǵ���Ŀ
			siftFeat *pSiftFeat     //������ֹͣ�ǵ�����(λ�ú�siftֵ)
		);

	//����ǰ�����Ϊ�ڵ���뵽ֹͣ����洢��
	int mvAddGiveObjAsStopStoreNode(
			double dTsNow,         //��ǰ��ʱ���
			const CvPoint &ptLtA,  //��ǰ�������ϵ�
			const CvPoint &ptRbA,  //��ǰ�������µ�
			const int nPtCnt,          //��ǰ����Ľǵ���Ŀ
			const siftFeat *pSiftFeat, //��ǰ����ĸ��ǵ�����
			const int nMatchStoreIdx = -1 //ƥ���ϴ洢�ڵ�ID
		);

	//��ֹͣ�洢�л�ȡ����ID��ֹͣ����(���ظ������Ľڵ���Ŀ)
	int mvGetGiveId4StopStore(
			const int nGiveStopEventId  //������ֹͣ�¼���ID
		);

	//��ֹͣ�洢�и���ID��ֹͣ����������"�������rect"
	bool mvSetCamCtrlRect4GiveId( 
		    const CvRect &rctCamCtrl,  //�������ǰ��Ӧ��rect
			const int nGiveStopEventId  //������ֹͣ�¼���ID
		);

	//��ֹͣ�洢�л�ȡ����ID��ֹͣ��������Ӧ"�������rect"
	bool mvGetCamCtrlRect4GiveId(
		    CvRect &rctCamCtrl,  //�������ǰ��Ӧ��rect
			const int nGiveStopEventId  //������ֹͣ�¼���ID
		);


	//��ֹͣ�洢��ɾ��û�ټ�⵽��ֹͣ����(����ɾ���ڵ���¼�ID)
	vector<int> mvDelNomoreDet4StopStore(
			double dTsNow,       //��ǰ��ʱ���
			double dMaxSaveTime  //��ౣ����ʱ��
		);

	//��ֹͣ�洢�нڵ��ȡ�Ѿ������˽ڵ㣬����û��ͼ���ֹͣ����
	vector<int> mvGetNoSavePic4StopStore( 
			vector<CvRect> &vectObjArea, //�õ���ֹͣĿ������
			const int nSaveNodeCntTh     //����ڵ����ĿҪ��
		);

	//�Ի�û��ͼ���ֹͣ����Ĵ�ͼ������
	void mvAddSavePicCnt4StopStore( 
			const vector<int> &vectGiveStopEventId  //������ֹͣ�¼���ID
		);

public:
	CvPoint  m_ptMatchRange;  //��ƥ�䷶Χ

	AnEventIdAssign  m_eventIdAssign;  //�¼�ID������
	vector<AnStopObjNode> m_vectStopCache;  //ֹͣ����

}AnSameStopAreaCheck;


////////////////////////////////////////////
#endif