//==========================================================
//
// ���M�~�b�N(������o�Ă���) [gimmick_fish.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_Fish_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_Fish_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CSlow;
class CCharacter;

//==========================================================
// �ړ��I�u�W�F�N�g�̃N���X��`
//==========================================================
class CGimmickFish : public CGimmick
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_NONE = 0,	// �������Ă��Ȃ�
		STATE_UP,		// �㏸
		STATE_ATK,		// �U��
		STATE_ATKEND,		// �U���I��
		STATE_DOWN,		// ���~
		STATE_WAIT,		// �ҋ@
	};

	// ���[�V�����񋓌^
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		MOTION_JUMP,			// �W�����v���[�V����
		MOTION_BITE,			// ���݂����[�V����
		MOTION_AFTERGRAW,		// ���݂���]�C���[�V����
		MOTION_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickFish();	// �R���X�g���N�^
	~CGimmickFish();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CGimmickFish *Create(void);
	static CGimmickFish *Create(D3DXVECTOR3& pos, D3DXVECTOR3& move, float fTimer);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetFish(void) { return m_move; }	// �ړ��ʎ擾
	float GetNowTimer(void) { return m_fNowFishTimer; }	// ���݃^�C�}�[�擾
	float GetNumTimer(void) { return m_fNumFishTimer; }	// ����^�C�}�[�擾

	// �����o�֐�(�ݒ�)
	void SetFish(D3DXVECTOR3 move) { m_move = move; }	// �ړ��ʐݒ�
	void SetNowTimer(float fTimer) { m_fNowFishTimer = fTimer; }	// ���݃^�C�}�[�ݒ�
	void SetNumTimer(float fTimer) { m_fNumFishTimer = fTimer; }	// ����^�C�}�[�ݒ�

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);

	// �����o�ϐ�
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_posOld;
	float m_fNowFishTimer;
	float m_fNumFishTimer;
	bool m_bEat;			// �H�ׂ����ǂ���
	float m_fStateCounter;	// ��ԊǗ��J�E���^�[
	CSlow *m_pSlow;		// �X���[
	CCharacter *m_pCharacter;	// �K�w�\���N���X�̃|�C���^
	STATE m_state;	// ���
};

#endif
