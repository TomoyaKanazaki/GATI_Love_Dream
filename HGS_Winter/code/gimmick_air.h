//==========================================================
//
// ���M�~�b�N [gimmick_button.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_AIR_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_AIR_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CObject3D;

//==========================================================
// ���̃N���X��`(�h���N���X)
//==========================================================
class CGimmickAir : public CGimmick
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	enum TYPE
	{
		TYPE_REVERSE = 0,	// �����]
		TYPE_DOOR,		// �h�A�J��
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickAir();	// �R���X�g���N�^
	~CGimmickAir();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickAir *Create(void);
	void Reverse(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)
	void SetMove(D3DXVECTOR3 move);
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	void SetRevease(bool bRevease) { m_bRevease = bRevease; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);

	// �����o�ϐ�
	CObject3D *m_pObject;		// �I�u�W�F�N�g�|�C���^
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR2 m_moveTex;		// �e�N�X�`���ړ���
	D3DXVECTOR2 m_TexPos;		// �e�N�X�`�����W
	bool m_bRevease;			// ���]���邩
	float m_fWidth;			// ��
	float m_fHeight;			// ����
};

#endif