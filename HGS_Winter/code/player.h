//==========================================================
//
// �v���C���[�̏��� [player.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PLAYER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

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
class CCar;
class CShadow;
class CMeshBalloon;

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CPlayer : public CTask
{
public:

	// �����ޗ񋓌^
	enum TYPE
	{
		TYPE_NONE,	// ����s�\
		TYPE_SEND,	// �f�[�^���M
		TYPE_ACTIVE,	// ����\
		TYPE_MAX
	};

private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_APPEAR = 0,	// �o�����
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_DEATH,		// ���S���
		STATE_SPAWN,		// ���������
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

	CPlayer();	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPlayer *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3& move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3& pos) { m_Info.pos = pos; m_Info.posDiff = pos; }
	void SetDiffPosition(const D3DXVECTOR3& pos) { m_Info.posDiff = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_Info.rot = rot; }
	void BindId(int nId) { m_nId = nId; }
	void SetType(TYPE type);
	void SetGoalValue(bool bValue) { m_bGoal = bValue; }
	void SetUp(bool bValue) { m_bSetUp = bValue; }
	void SetGoal(bool bValue);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	int GetId(void) { return m_nId; }
	static CPlayer *GetTop(void) { return m_pTop; }
	CPlayer *GetNext(void) { return m_pNext; }
	void Damage(int nDamage);
	void SetLife(int nLife);
	bool GetSetUp(void) { return m_bSetUp; }
	bool GetGoal(void) { return m_bGoal; }
	static int GetNum(void) { return m_nNumCount; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Rotation(void);
	void Adjust(void);
	void KeyBoardRotation(void);

	// �����o�ϐ�
	static CPlayer *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CPlayer *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CObjectBillboard **m_ppBillBoard;
	SInfo m_Info;			// �������g�̏��
	CCharacter *m_pObject;	// �`��I�u�W�F�N�g
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	float m_fStepCoolTime;	// �X�e�b�v�N�[���^�C��
	D3DXMATRIX m_mtxRot;	// ��]�}�g���b�N�X
	D3DXQUATERNION m_quat;	// �N�H�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;	// ��]��
	float m_fValueRot;	// ��]�p
	CShadow *m_pShadow;	// �e�̃|�C���^
	CObject2D *m_pMapIcon;	// �~�j�}�b�v�\���p�A�C�R��
	CObject2D *m_pGoal;
	int m_nLife;	// �̗�
	int m_nId;	// ID
	bool m_bSetUp;	// �����������ǂ���
	TYPE m_type;	// ���
	bool m_bGoal;	// �S�[��������
	static int m_nNumCount;
	float m_fEffectCount;	// �G�t�F�N�g�J�E���^�[
	
};

#endif