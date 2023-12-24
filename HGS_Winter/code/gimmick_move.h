//==========================================================
//
// �ړ��M�~�b�N [gimmick_move.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_MOVE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_MOVE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CSlow;
class CCharacter;
class CShadow;

//==========================================================
// �ړ��I�u�W�F�N�g�̃N���X��`
//==========================================================
class CGimmickMove : public CGimmick
{
public:	// �N�ł��A�N�Z�X�\

	CGimmickMove();	// �R���X�g���N�^
	~CGimmickMove();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmickMove *Create(void);
	static CGimmickMove *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, float fTimer);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾
	float GetNowTimer(void) { return m_fNowMoveTimer; }	// ���݃^�C�}�[�擾
	float GetNumTimer(void) { return m_fNumMoveTimer; }	// ����^�C�}�[�擾

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }	// �ړ��ʐݒ�
	void SetNowTimer(float fTimer) { m_fNowMoveTimer = fTimer; }	// ���݃^�C�}�[�ݒ�
	void SetNumTimer(float fTimer) { m_fNumMoveTimer = fTimer; }	// ����^�C�}�[�ݒ�

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);

	// �����o�ϐ�
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_posOld;
	CCharacter *m_pObject;
	CShadow *m_pShadow;
	float m_fNowMoveTimer;
	float m_fNumMoveTimer;
	CSlow *m_pSlow;		// �X���[

};

#endif

