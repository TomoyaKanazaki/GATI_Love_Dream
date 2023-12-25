//===============================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
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
#include "billboard.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(1.0f)		// �ړ���
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

// �O���錾
CPlayer *CPlayer::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CPlayer *CPlayer::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CPlayer::m_nNumCount = 0;

//===============================================
// �R���X�g���N�^
//===============================================
//CPlayer::CPlayer()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer()
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
	m_pShadow = NULL;
	m_nLife = 0;
	m_ppBillBoard = NULL;
	m_type = TYPE_NONE;
	m_nId = -1;
	m_fEffectCount = 0.0f;
	m_bSetUp = false;
	m_bGoal = false;
	m_pGoal = nullptr;

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
CPlayer::~CPlayer()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CPlayer::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\motion_kidsboy.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;
	m_bSetUp = false;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxRot);

	if (m_ppBillBoard == nullptr)
	{
		m_ppBillBoard = new CObjectBillboard*[START_LIFE];

		for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
		{
			m_ppBillBoard[nCnt] = nullptr;

			if (nullptr == m_ppBillBoard[nCnt])
			{
				m_ppBillBoard[nCnt] = CObjectBillboard::Create(m_Info.pos, 5);
				m_ppBillBoard[nCnt]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(rand() % 628 - 314)));
				m_ppBillBoard[nCnt]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\balloon.png"));
				m_ppBillBoard[nCnt]->SetSize(90.0f + nCnt * 5.0f, 90.0f + nCnt * 5.0f);
			}
		}
	}

	// �e�̐���
	if (nullptr == m_pShadow)
	{
		m_pShadow = CShadow::Create(m_Info.pos, 50.0f, 50.0f);
		m_pShadow->SetpVtx(m_ppBillBoard[m_nLife - 1]->GetWidth(), m_ppBillBoard[m_nLife - 1]->GetHeight());
		m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)((float)m_nLife / (float)START_LIFE * SHADOW_ALPHA)));
	}

	m_pObject->SetDraw();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
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

	if (nullptr != m_pObject){
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (nullptr != m_pShadow){
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	if (m_ppBillBoard != NULL)
	{
		for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
		{
			if (nullptr != m_ppBillBoard[nCnt])
			{
				m_ppBillBoard[nCnt]->Uninit();
				m_ppBillBoard[nCnt] = NULL;
			}
		}

		delete[] m_ppBillBoard;	// �|�C���^�̊J��
		m_ppBillBoard = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	if (m_pMapIcon != NULL)
	{
		m_pMapIcon->Uninit();
		m_pMapIcon = NULL;
	}

	if (m_pGoal != NULL)
	{
		m_pGoal->Uninit();
		m_pGoal = NULL;
	}

	m_nNumCount--;

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_pGoal != nullptr)
	{
		D3DXVECTOR3 pos = m_pGoal->GetPosition();

		// �ړ�
		if (pos.x > SCREEN_WIDTH * 0.75f)
		{
			pos.x -= 30.0f;
		}
		else if (pos.x < SCREEN_WIDTH * 0.35f)
		{
			pos.x -= 40.0f;
		}
		else
		{
			pos.x -= 2.5f;
		}

		m_pGoal->SetPosition(pos);
		m_pGoal->SetVtx();

		if (pos.x < -SCREEN_WIDTH * 0.5f)
		{
			m_pGoal->Uninit();
			m_pGoal = NULL;
		}
	}

	if (m_type == TYPE_SEND)
	{
		CManager::GetInstance()->GetCamera()->Setting(m_Info.pos, m_Info.rot);
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}

	if (m_type == TYPE_ACTIVE)
	{
		if (m_nLife <= 0)
		{
			for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
			{
				if (nullptr != m_ppBillBoard[nCnt]) {
					m_ppBillBoard[nCnt]->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 50.0f + 10.0f * nCnt, m_Info.pos.z));
				}
			}

			return;
		}

		if (m_Info.state != STATE_SPAWN)
		{
			// �v���C���[����
			Controller();
		}

		// �J�����Ǐ]
		CCamera *pCamera = CManager::GetInstance()->GetCamera();

		// �Ǐ]����
		pCamera->Pursue(GetPosition(), GetRotation());

		// �I�����C�����M
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}
	else
	{// ����L�����ł͂Ȃ�
		D3DXVECTOR3 posDest = m_Info.posDiff - m_Info.pos;
		m_Info.pos += posDest * 0.95f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("���� [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("�̗� [ %d ]\n", m_nLife);

	if (m_bGoal)
	{
		CManager::GetInstance()->GetDebugProc()->Print("[ �S�[������ ]\n", m_nLife);
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("[ �S�[�����ĂȂ� ]\n", m_nLife);
	}

	// ���S�m�F
	if (m_nLife <= 0 && m_Info.state != STATE_DEATH)
	{
		if (m_pObject == nullptr)
		{
			return;
		}

		m_pObject->SetDraw(false);
		m_pShadow->SetDraw(false);
		m_Info.state = STATE_DEATH;
		m_Info.fStateCounter = DEATH_INTERVAL;

		
	}
	else if (m_nLife > 0 && (m_Info.state != STATE_DEATH && m_Info.state != STATE_APPEAR))
	{// �̗͂���
		m_fEffectCount += CManager::GetInstance()->GetSlow()->Get();

		if (m_fEffectCount >= PARTICLE_TIMER)
		{
			m_fEffectCount = 0.0f;
			
		}
	}

	// �g�p�I�u�W�F�N�g�X�V
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y - 50.0f, m_Info.pos.z - 20.0f));
		m_pObject->SetRotation(m_Info.rot);
		m_pObject->Update();
		m_pObject->GetMotion()->BlendSet(START_LIFE - m_nLife);
	}

	// �N���Ƃ̓����蔻��
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(m_Info.pos);

	// �e�̐ݒ�
	if (nullptr != m_pShadow) {
		m_pShadow->SetPosition(D3DXVECTOR3(m_Info.pos.x, fHeight + 1.0f, m_Info.pos.z));
	}
}

//===============================================
// ����
//===============================================
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move)
{
	CPlayer *pPlayer = NULL;

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer;

	if (nullptr != pPlayer)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init();

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);

		// ��ނ̐ݒ�
		//pPlayer->SetType(TYPE_PLAYER);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pPlayer;
}

//===============================================
// ���쏈��
//===============================================
void CPlayer::Controller(void)
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
		if (pInputKey->GetPress(DIK_SPACE) == false && pInputPad->GetPress(CInputPad::BUTTON_A, m_nId) == false)
		{
			Move();		// �ړ�
		}

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
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (m_ppBillBoard != nullptr){
			vtxMax = D3DXVECTOR3(m_ppBillBoard[0]->GetWidth() * 0.7f, m_ppBillBoard[0]->GetHeight(), m_ppBillBoard[0]->GetHeight() * 0.7f);
			vtxMin = vtxMax * -1.0f;
		}

		// �M�~�b�N
		if (CGimmick::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, nDamage))
		{
			bDamage = true;
			CManager::GetInstance()->GetDebugProc()->Print("***�M�~�b�N�Ɠ���������***\n");
		}

		// ��
		if (CObjectX::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, 0.3f))
		{
			bDamage = true;
			CManager::GetInstance()->GetDebugProc()->Print("***�ǂƓ���������***\n");
			if (nDamage == 0)
			{
				nDamage = 1;
			}
		}
	}

	// �_���[�W�m�F
	if (m_Info.state == STATE_NORMAL)
	{
		if (nDamage >= 0)
		{
			if (bDamage)
			{
				CManager::GetInstance()->GetScene()->SendDamage(nDamage);
				Damage(nDamage);

				if (m_type == TYPE_ACTIVE)
				{
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
				}
			}
		}
	}

	{
		float fIner = INER;
		if (pInputKey->GetPress(DIK_SPACE) == true || pInputPad->GetPress(CInputPad::BUTTON_A, m_nId) == true)
		{
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

			CParticle::Create(m_Info.pos, m_Info.move, CEffect::TYPE_SNOWATK, static_cast<int>(fAdd) * 15);
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
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	float fSpeed = MOVE;	// �ړ���

	// ���͑��u�m�F
	if (nullptr == pInputKey){
		return;
	}

	// ���͑��u�m�F
	if (nullptr == pInputPad){
		return;
	}

	if (pInputKey->GetPress(DIK_A) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.8f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.8f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
}

//===============================================
// ��]
//===============================================
void CPlayer::Rotation(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ���͑��u�m�F
	if (nullptr == pInputPad){
		return;
	}

	if (!pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_PLUS) && 
		!pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.1f, CInputPad::STICK_MINUS) &&
		!pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_PLUS) &&
		!pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.1f, CInputPad::STICK_MINUS))
	{// �R���g���[���[���͖���
		KeyBoardRotation();
		return;
	}

	D3DXVECTOR2 vec;
	vec.y = pInputPad->GetStickAdd(0, CInputPad::BUTTON_LEFT_X, 0.1f);
	vec.x = pInputPad->GetStickAdd(0, CInputPad::BUTTON_LEFT_Y, 0.1f);
	D3DXVec2Normalize(&vec, &vec);

	m_fRotDest = atan2f(vec.y, vec.x);
}

//===============================================
// ��]
//===============================================
void CPlayer::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^

	if (nullptr == pInputKey){
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
void CPlayer::Adjust(void)
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
void CPlayer::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_APPEAR:

		CManager::GetInstance()->GetDebugProc()->Print("��� : [���G]\n");
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}

		break;

	case STATE_NORMAL:

		CManager::GetInstance()->GetDebugProc()->Print("��� : [�ʏ�]\n");

		break;

	case STATE_DAMAGE:

		CManager::GetInstance()->GetDebugProc()->Print("��� : [�_���[�W]\n");

		if (m_ppBillBoard != NULL)
		{
			if (m_nLife >= 0 && m_nLife < START_LIFE)
			{
				m_ppBillBoard[m_nLife]->SetSize(m_ppBillBoard[m_nLife]->GetWidth() + 11.0f, m_ppBillBoard[m_nLife]->GetHeight() + 11.0f);
			}
		}

		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;

			if (m_ppBillBoard != NULL)
			{
				if (m_nLife >= 0 && m_nLife < START_LIFE)
				{
					m_ppBillBoard[m_nLife]->SetDraw(false);
				}
			}

			if (m_pShadow != nullptr)
			{
				m_pShadow->SetpVtx(m_ppBillBoard[m_nLife - 1]->GetWidth(), m_ppBillBoard[m_nLife - 1]->GetHeight());
				m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)((float)m_nLife / (float)START_LIFE * SHADOW_ALPHA)));

			}
		}

		break;

	case STATE_DEATH:

		CManager::GetInstance()->GetDebugProc()->Print("��� : [���S]\n");

		if (m_ppBillBoard != NULL)
		{
			if (m_nLife >= 0 && m_nLife < START_LIFE)
			{
				m_ppBillBoard[m_nLife]->SetSize(m_ppBillBoard[m_nLife]->GetWidth() + 50.0f, m_ppBillBoard[m_nLife]->GetHeight() + 50.0f);
			}
		}

		{
			float fOld = m_Info.fStateCounter;
			m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
			if (m_Info.fStateCounter <= DEATH_INTERVAL * 0.95f && fOld >= DEATH_INTERVAL * 0.95f)
			{
				if (m_ppBillBoard != NULL)
				{
					if (m_nLife >= 0 && m_nLife < START_LIFE)
					{
						m_ppBillBoard[m_nLife]->SetDraw(false);
					}
				}
			}
		}

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = SPAWN_INTERVAL;
			m_Info.state = STATE_SPAWN;
			m_pShadow->SetDraw();
			m_pShadow->SetpVtx(0.0f, 0.0f);
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Info.pos.y = -600.0f;
			SetPosition(m_Info.pos);
			m_nLife = START_LIFE;

			if (m_type == TYPE_ACTIVE)
			{
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SPAWN);
			}

			for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
			{
				if (nullptr != m_ppBillBoard[nCnt])
				{
					m_ppBillBoard[nCnt]->SetDraw(true);
					m_ppBillBoard[nCnt]->SetSize(0.0f, 0.0f);
				}
			}
		}

		break;

	case STATE_SPAWN:
	{
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();

		m_Info.pos.y += 10.0f;
		SetPosition(m_Info.pos);

		for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
		{
			if (nullptr != m_ppBillBoard[nCnt])
			{
				m_ppBillBoard[nCnt]->SetSize(m_ppBillBoard[nCnt]->GetWidth() + 1.0f + nCnt * 0.25f, m_ppBillBoard[nCnt]->GetHeight() + 1.0f + nCnt * 0.25f);
			}
		}

		m_pShadow->SetpVtx(m_pShadow->GetWidth() + 1.0f + START_LIFE * 0.25f, m_pShadow->GetHeight() + 1.0f + START_LIFE * 0.25f);
		m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)((float)(SPAWN_INTERVAL - m_Info.fStateCounter) / (float)SPAWN_INTERVAL * SHADOW_ALPHA)));

		if (m_Info.fStateCounter <= 0.0f)
		{
			for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
			{
				if (nullptr != m_ppBillBoard[nCnt])
				{
					m_ppBillBoard[nCnt]->SetSize(90.0f + nCnt * 5.0f, 90.0f + nCnt * 5.0f);
				}
			}

			m_pObject->SetDraw();
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_APPEAR;
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
		break;
	}
}

//===============================================
// �_���[�W����
//===============================================
void CPlayer::Damage(int nDamage) 
{ 
	int nOldLife = m_nLife;
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
	{
		if (nullptr != m_ppBillBoard)
		{
			if (nCnt > m_nLife)
			{
				m_ppBillBoard[nCnt]->SetDraw(false);
			}
		}
	}

	if (m_nLife != nOldLife)
	{
		m_Info.fStateCounter = DAMAGE_INTERVAL;
		m_Info.state = STATE_DAMAGE;
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	for (int nCnt = 0; nCnt < START_LIFE; nCnt++)
	{
		if (nullptr != m_ppBillBoard)
		{
			if (nCnt > m_nLife)
			{
				m_ppBillBoard[nCnt]->SetDraw(false);
			}
		}
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CPlayer::SetType(TYPE type)
{
	m_type = type;

	if (m_type == TYPE_ACTIVE)
	{
		if (m_pMapIcon != nullptr)
		{
			m_pMapIcon->SetCol(D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f));
			m_pMapIcon->SetPosition(D3DXVECTOR3(m_pMapIcon->GetPosition().x, SCREEN_HEIGHT * 0.93f, 0.0f));
		}

		if (m_pGoal == nullptr && CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
		{
			m_pGoal = CObject2D::Create(6);
			m_pGoal->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
			m_pGoal->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
			m_pGoal->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.2f);
			m_pGoal->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\start.png"));
		}
	}
}

//===============================================
// �|���S���`��
//===============================================
void CPlayer::SetGoal(bool bValue)
{
	bool Old = m_bGoal;
	m_bGoal = bValue;

	if (Old == false && m_bGoal == true)
	{
		m_pGoal = CObject2D::Create(6);
		m_pGoal->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
		m_pGoal->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
		m_pGoal->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);

		if (m_pGoal != nullptr)
		{
			if (m_type == TYPE_NONE)
			{
				m_pGoal->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\goal_lose.png"));
			}
			else
			{
				m_pGoal->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\goal_win.png"));
			}
		}
	}
}