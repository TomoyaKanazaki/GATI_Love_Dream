//=======================================
//
//�V���[�e�B���O�A�N�V����[light.h]
//Author�@:�@MORIKAWA SHUNYA
//
//=======================================

#ifndef _LIGHT_H_     //���̃}�N����`����`����Ă��Ȃ�������
#define _LIGHT_H_    //2�A�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//=======================================
//���C�g�N���X
//=======================================
class CLight
{
public:
	CLight();	//�R���X�g���N�^
	~CLight();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	//�����o�ϐ�
	D3DLIGHT9 m_alight[3];	//���C�g�̏��
};

#endif