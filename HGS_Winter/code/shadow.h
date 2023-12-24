//==========================================================
//
// �e�̏����S�� [shadow.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SHADOW_H_	 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SHADOW_H_	 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include
#include "object3D.h"

//**********************************************************
// �e�N���X�̒�`
//**********************************************************
class CShadow : public CObject3D
{
public:		// �N�ł��A�N�Z�X�\

	CShadow();	// �R���X�g���N�^
	~CShadow();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow *Create(const D3DXVECTOR3& pos, float fWidth, float fHeight);

private:	// �����������A�N�Z�X�\
};

#endif
