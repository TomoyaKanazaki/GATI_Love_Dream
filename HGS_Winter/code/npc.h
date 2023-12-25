//==========================================================
//
// NPC�̏��� [npc.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _NPC_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _NPC_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// �O���錾
class CShadow;
class CCharacter;
class CWaist;
class CObject2D;
class CObjectBillboard;
class CModel;
class CLockOn;
class CMeshOrbit;
class CObject3D;
class CEnemy;

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CNpc : public CTask
{
private:	// �����������A�N�Z�X�\�Ȓ�`

			// ��ԗ񋓌^
	enum STATE
	{
		STATE_NEUTRAL = 0,	// �ҋ@���
		STATE_MOVE,		// �ړ����
		STATE_STOP,		// ��~���
		STATE_WAIT,		// �ҋ@
		STATE_DEATH,
		STATE_MAX
	};

	// ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;	// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		D3DXVECTOR3 posDiff;
		STATE state;			// ���
		float fStateCounter;	// ��ԊǗ��J�E���^�[
	}SInfo;

public:	// �N�ł��A�N�Z�X�\

	CNpc();	// �R���X�g���N�^
	~CNpc();	// �f�X�g���N�^

				// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CNpc *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3& move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3& pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3& pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_Info.rot = rot; }
	void SetType(TYPE type);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	static CNpc *GetTop(void) { return m_pTop; }
	CNpc *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);
	static int GetNum(void) { return m_nNumCount; }

private:	// �����������A�N�Z�X�\

			// �����o�֐�
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void KeyBoardRotation(void);
	void LockOn(void);

	// �����o�ϐ�
	static CNpc *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CNpc *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CNpc *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CNpc *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	SInfo m_Info;			// �������g�̏��
	CEnemy *m_pTarget;	// �ڕW
	CCharacter *m_pObject;	// �`��I�u�W�F�N�g
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	int m_nLife;	// �̗�
	static int m_nNumCount;
};

#endif
