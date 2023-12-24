//==========================================================
//
// ��]�M�~�b�N [gimmick_rotate.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_ROTATE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_ROTATE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CCharacter;
class CShadow;

// �}�N����`
#define NUM_ROTATEBOX	(10)

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmickRotate : public CGimmick
{
private:

	// �Ǐ]��]�I�u�W�F
	struct Obj
	{
		D3DXVECTOR3 s_posOld;
		CCharacter *s_pModel;
		CShadow *s_pShadow;
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickRotate();	// �R���X�g���N�^
	//CGimmickRotate(int nPriOrity = 0);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CGimmickRotate();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickRotate *Create(void);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetRotate(void) { return m_RotateSpeed; }

	// �����o�֐�(�ݒ�)
	void SetRotate(D3DXVECTOR3 rotate);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	virtual bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);
	void SetRotationCharacter(void);
	// �����o�ϐ�
	Obj m_aObj[NUM_ROTATEBOX];	// �I�u�W�F�z��
	D3DXVECTOR3 m_RotateSpeed;	// ��]��
	float m_fSize;		// 1�ӂ�̃I�u�W�F�T�C�Y
};

#endif
