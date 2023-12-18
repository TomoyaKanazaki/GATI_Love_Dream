//=======================================
//
//�G�t�F�N�g����[effect.h]
//Author : MORIKAWA SHUNYA
//
//=======================================

#ifndef _EFECT_H_     //���̃}�N����`����`����Ă��Ȃ�������
#define _EFECT_H_    //2�A�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "billboard.h"

//===========================================
//�}�N����`
//===========================================
#define MAX_EFFECT		(30)		//�G�t�F�N�g�̍ő吔

//===========================================
//�G�t�F�N�g�N���X
//===========================================
class CEffect : public CBillboard
{
public:
	CEffect();		//�R���X�g���N�^
	~CEffect();		//�f�X�g���N�^

	//�����o�֐�
	static CEffect *Create(void);	//�v���C���[����

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	D3DXVECTOR3 m_rot;	//����
	D3DXCOLOR m_col;	//�F
	float m_fRadius;	//���a(�傫��)
	int m_nLife;		//����(�\������)
	int m_nType;		//���
	D3DXMATRIX m_g_mtxWorldEffectt;	//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxRot; 	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX m_mtxTrans;
	D3DXMATRIX m_mtxView;		//�r���[�}�g���N�X�擾�p
	bool m_balpha;			//���Z����
};

#endif