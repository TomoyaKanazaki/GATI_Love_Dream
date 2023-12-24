//==========================================================
//
// �{�^���M�~�b�N�̏��� [gimmick_button.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_BUTTON_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_BUTTON_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CObjectX;

//==========================================================
// �{�^���̃N���X��`(�h���N���X)
//==========================================================
class CGimmickButton : public CGimmick
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	enum TYPE
	{
		TYPE_REVERSE = 0,	// �����]
		TYPE_DOOR,		// �h�A�J��
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickButton();	// �R���X�g���N�^
	~CGimmickButton();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickButton *Create(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)
	void SetGoalPos(const D3DXVECTOR3& pos) { m_GoalPos = pos; }
	void SetType(TYPE type) { m_type = type; }
	void SetId(int nId) { m_nId = nId; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);

	// �����o�ϐ�
	D3DXVECTOR3 m_GoalPos;		// ���͌���W
	CObjectX *m_pObject;		// �I�u�W�F�N�g�|�C���^
	bool m_bPress;	// ���͍ςݔ���
	int m_nId;	// ID
	bool m_bPressOld;
	TYPE m_type;
};

#endif

