//����Ӧ��ѡȡ����ģ��
#ifndef __MODEL_SELECTOR_H
#define __MODEL_SELECTOR_H
	
#include "libHeader.h"

//ǰ����ȡģʽ
enum ENUM_FKIMG_EXT_MODEL
{
	DEFAULT_FK_EXT_MODEL = 0,
	EASY_FK_EXT_MODEL,
	HARD_FK_EXT_MODEL
};

//�ǵ���ȡģʽ
enum ENUM_KEYPT_EXT_MODEL
{
	DEFAULT_KEYPT_EXT_MODEL = 0,
	EASY_KEYPT_EXT_MODEL,
	HARD_KEYPT_EXT_MODEL
};

typedef struct StruModelSelector
{
public:
	StruModelSelector( );
	~StruModelSelector( );

private:
	void mvInitVar( );

private:
	ENUM_FKIMG_EXT_MODEL m_nFkImgExtrackModel;  //ǰ����ȡģʽ

	ENUM_KEYPT_EXT_MODEL m_nKeyPtsExtrackModel; //�ǵ���ȡģʽ

}MvModelSelector;



//--------------------------------

#endif