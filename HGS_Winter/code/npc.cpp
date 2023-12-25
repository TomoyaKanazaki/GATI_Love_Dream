//===============================================
//
// NPC�̏��� [npc.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "npc.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "meshfield.h"
#include "Xfile.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include "shadow.h"
#include "gimmick.h"
#include <assert.h>
#include "character.h"
#include "motion.h"
#include "sound.h"
#include "particle.h"
#include "enemy.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(0.21f)		// �ړ���
#define SHW_MOVE	(1.0f)	// �V�����[���ړ���
#define PLAYER_GRAVITY	(-0.15f)		//�v���C���[�d��
#define PLAYER_JUMP		(10.0f)		//�v���C���[�W�����v��
#define ROT_MULTI	(0.075f)	// �����␳�{��
#define WIDTH	(20.0f)		// ��
#define HEIGHT	(80.0f)	// ����
#define INER	(0.015f)		// ����
#define STOP_INER (0.125f)	// ��~����
#define STEP_SPEED	(50.0f)
#define STEP_COOLTIME	(90.0f)
#define START_LIFE	(4)	// �����̗�
#define DAMAGE_INTERVAL	(10.0f)
#define DAMAGE_APPEAR	(110.0f)
#define DEATH_INTERVAL	(120.0f)
#define DASH_INTERVAL	(60.0f)
#define SPAWN_INTERVAL	(60.0f)
#define PARTICLE_TIMER	 (5.0f)
#define SHADOW_ALPHA	(0.4f)
#define STOP_LENGTH	(300.0f)

namespace COOLTIME
{
	const int STOP = (90);
	const int WAIT = (90);
}

namespace
{
	const float DAMAGE = 0.002f; // ���̃q�b�g�Ŏ󂯂�_���[�W��
	const float RADIUS = 100.0f;
	const int MAX_SPAWN = 3;
	const int SPAWN_TIMER = 20;
}

// �O���錾
CNpc *CNpc::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CNpc *CNpc::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CNpc::m_nNumCount = 0;
float CNpc::m_SpawnCnt = 0.0f;

//===============================================
// �R���X�g���N�^
//===============================================
//CNpc::CNpc()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CNpc::CNpc()
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_fLife = 0;
	m_pTarget = nullptr;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}

	m_nNumCount++;
}

//===============================================
// �f�X�g���N�^
//===============================================
CNpc::~CNpc()
{

}

//===============================================
// ����������
//===============================================
HRESULT CNpc::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\Enemy.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
	}

	m_fLife = 0.0f;

	m_pObject->SetDraw();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CNpc::Uninit(void)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != NULL)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != NULL)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
			m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	if (nullptr != m_pObject) {
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	m_nNumCount--;

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CNpc::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_Info.state != STATE_DEATH)
	{
		// �v���C���[����
		Controller();
	}

	CManager::GetInstance()->GetDebugProc()->Print("���� [%f, %f, %f]\n", GetRotation().x, GetRotation().y, GetRotation().z);
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y - 50.0f, m_Info.pos.z - 20.0f));
		m_pObject->SetRotation(m_Info.rot);
		m_pObject->Update();
	}

	// �N���Ƃ̓����蔻��
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y - 1.0f, m_Info.pos.z));
	m_Info.pos.y = fHeight;
}

//===============================================
// ����
//===============================================
CNpc *CNpc::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move)
{
	CNpc *pNpc = NULL;

	// �I�u�W�F�N�g2D�̐���
	pNpc = new CNpc;

	if (nullptr != pNpc)
	{// �����ł����ꍇ
	 // ����������
		pNpc->Init();

		// ���W�ݒ�
		pNpc->SetPosition(pos);

		// �����ݒ�
		pNpc->SetRotation(rot);

		pNpc->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pNpc->SetMove(move);

		// ��ނ̐ݒ�
		//pNpc->SetType(TYPE_PLAYER);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pNpc;
}

//===============================================
// ���쏈��
//===============================================
void CNpc::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();					// �J�����̃|�C���^
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	D3DXVECTOR3 CamRot = pCamera->GetRotation();								// �J�����̊p�x
	bool bDamage = false;
	m_fRotMove = rot.y;	//���݂̌������擾
	int nDamage = 0;

	// ���쏈��
	{

		Move();		// �ړ�
		Rotation();	// ��]
	}

	pos = GetPosition();	// ���W���擾

	// ����(�X�e�b�v��ԕ�)
	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// ����
	Adjust();

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	if (nullptr != m_pObject)
	{
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, -50.0f, -50.0f);

		// �M�~�b�N
		if (CGimmick::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, nDamage))
		{
			bDamage = true;
			CManager::GetInstance()->GetDebugProc()->Print("***�M�~�b�N�Ɠ���������***\n");
		}

		// ��
	}

	// �_���[�W�m�F
	
	if (nDamage >= 0)
	{
		if (bDamage)
		{
			CManager::GetInstance()->GetScene()->SendDamage(nDamage);
			Damage(nDamage);
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
		}
	}

	{
		float fIner = INER;

		// ������ύX���邩�m�F
		if (m_Info.state == STATE_MOVE) {	// �ړ���
			if (m_pTarget != nullptr) {
				// �������擾
				float fLength = sqrtf((pos.x - m_pTarget->GetPosition().x) * (pos.x - m_pTarget->GetPosition().x)
					+ (pos.z - m_pTarget->GetPosition().z) * (pos.z - m_pTarget->GetPosition().z));

				if (fLength <= STOP_LENGTH) {
					fIner = STOP_INER;
					m_Info.state = STATE_STOP;
					m_Info.fStateCounter = COOLTIME::WAIT;
				}
			}
		}
		else {
			fIner = STOP_INER;
		}

		D3DXVECTOR3 moveOld = m_Info.move;

		m_Info.move.x += (0.0f - m_Info.move.x) * fIner;	//x���W
		m_Info.move.z += (0.0f - m_Info.move.z) * fIner;	//x���W

		if (fIner == STOP_INER) {	// ��~���̏ꍇ
			D3DXVECTOR3 moveDiff = moveOld - m_Info.move;

			// �ړ��ʕ��������琳�ɂ���
			if (moveDiff.x < -1.0f) {
				moveDiff.x *= -1.0f;
			}
			if (moveDiff.y < -1.0f) {
				moveDiff.y *= -1.0f;
			}
			if (moveDiff.z < -1.0f) {
				moveDiff.z *= -1.0f;
			}

			float fAdd = moveDiff.x + moveDiff.y + moveDiff.z;
			fAdd * 1.5f;

			CParticle::Create(m_Info.pos, m_Info.move, CEffect::TYPE_SNOWNPC, static_cast<int>(fAdd) * 4);
		}
	}

	// �ǂƂ̓����蔻��
	CMeshWall::Collision(pos, m_Info.posOld);

	m_Info.pos = pos;

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n��][W,A,S,D] : ����[SPACE] : �X�e�b�v[K, (R�{�^��)]\n");
}

//===============================================
// �ړ�
//===============================================
void CNpc::Move(void)
{
	if (m_Info.state != STATE_MOVE) {
		return;
	}

	if (m_pTarget == nullptr) {
		return;
	}

	float fMove = MOVE * (1.0f - m_fLife);
	D3DXVECTOR3 nor = m_pTarget->GetPosition() - m_Info.pos;
	D3DXVec3Normalize(&nor, &nor);
	m_fRotDest = atan2f(nor.x, nor.z);
	m_Info.move.x += sinf(m_fRotDest) * fMove;
	m_Info.move.z += cosf(m_fRotDest) * fMove;
	m_fRotDest *= -1.0f;

	nor = m_Info.pos - m_pTarget->GetPosition();
	D3DXVec3Normalize(&nor, &nor);
	m_fRotDest = atan2f(nor.x, nor.z);
}

//===============================================
// ��]
//===============================================
void CNpc::Rotation(void)
{
	
}

//===============================================
// ��]
//===============================================
void CNpc::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^

	if (nullptr == pInputKey) {
		return;
	}

	if (pInputKey->GetPress(DIK_W))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.25f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.25f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 0.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_S))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.75f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 1.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_A))
	{
		m_fRotDest = -D3DX_PI * 0.5f;
	}
	else if (pInputKey->GetPress(DIK_D))
	{
		m_fRotDest = D3DX_PI * 0.5f;
	}
}

//===============================================
// ����
//===============================================
void CNpc::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//===============================================
// ��ԊǗ�
//===============================================
void CNpc::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_NEUTRAL:

		m_pObject->GetMotion()->Set(0);
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_MOVE;

			// �Ώۂ�ݒ�
			LockOn();
		}

		break;

	case STATE_MOVE:
	{
		m_pObject->GetMotion()->BlendSet(1);
	}
		break;

	case STATE_STOP:

		m_pObject->GetMotion()->BlendSet(2);
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = COOLTIME::STOP;
			m_Info.state = STATE_NEUTRAL;
		}

		break;

	case STATE_DEATH:

		

		break;
	}
}

//===============================================
// �_���[�W����
//===============================================
void CNpc::Damage(int nDamage)
{
	/*int nOldLife = m_nLife;
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
	m_nLife = 0;
	}

	if (m_nLife != nOldLife)
	{
	m_Info.fStateCounter = DAMAGE_INTERVAL;
	m_Info.state = STATE_DAMAGE;
	}*/
}

//===============================================
// �̗͐ݒ�
//===============================================
void CNpc::SetLife(int nLife)
{
	
}

//===============================================
// ���b�N�I���ݒ�
//===============================================
void CNpc::LockOn(void)
{
	CEnemy *pEnemy = CEnemy::GetTop();
	CEnemy *KariTarget = nullptr;

	// ���̃^�[�Q�b�g��ݒ�
	while (pEnemy != nullptr) {
		CEnemy *pEnemyNext = pEnemy->GetNext();

		if (m_pTarget != pEnemy) {
			KariTarget = pEnemy;

			if (rand() % 3 == 0) {
				break;
			}
		}

		pEnemy = pEnemyNext;
	}

	m_pTarget = KariTarget;
}

//===============================================
// �����蔻��
//===============================================
bool CNpc::Collision(const D3DXVECTOR3& pos, float fRadius)
{
	// �������擾
	float fLength = sqrtf((pos.x - m_Info.pos.x) * (pos.x - m_Info.pos.x)
		+ (pos.z - m_Info.pos.z) * (pos.z - m_Info.pos.z));

	float fSize = fRadius + RADIUS;

	if (fLength > fSize)
	{// �G��Ă��Ȃ�
		return false;
	}

	m_fLife += DAMAGE;

	if (m_fLife >= 1.0f) {
		Uninit();
	}
	
	return true;
}

//===============================================
// �����蔻��
//===============================================
void CNpc::Spawn(void)
{
	if (m_nNumCount >= MAX_SPAWN) {
		return;
	}

	m_SpawnCnt += CManager::GetInstance()->GetDeltaTime();
	
	if (m_SpawnCnt >= SPAWN_TIMER) {
		m_SpawnCnt = 0.0f;
		CNpc::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}