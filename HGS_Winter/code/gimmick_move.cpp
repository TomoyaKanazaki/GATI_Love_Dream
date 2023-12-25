//==========================================================
//
// �ړ��I�u�W�F�N�g [objectmove.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_move.h"
#include "manager.h"
#include "slow.h"
#include "Xfile.h"
#include "character.h"
#include "motion.h"
#include "shadow.h"
#include "meshfield.h"
#include "particle.h"
#include "renderer.h"

// �}�N����`
#define COLLISION_SIZE		(50.0f)
#define DAMAGE		(1)

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickMove::CGimmickMove()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fNowMoveTimer = 0.0f;
	m_fNumMoveTimer = 0.0f;
	m_pObject = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickMove::~CGimmickMove()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickMove::Init(void)
{

	// �ǂݍ��݊m�F
	if(m_pObject == NULL)
	{
		m_pObject = CCharacter::Create("data\\TXT\\motion_bee.txt");
		m_pObject->GetMotion()->InitSet(0);
	}

	// �e�̐���
	if (nullptr == m_pShadow)
	{
		//m_pShadow = CShadow::Create(GetPosition(), 50.0f, 50.0f);
	}

	// �X���[���o����
	m_pSlow = CManager::GetInstance()->GetSlow();

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickMove::Uninit(void)
{
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	if (nullptr != m_pShadow) {
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	ListOut();

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickMove::Update(void)
{
	m_posOld = GetPosition();

	// ����֘A
	Controller();

	SetMtxWorld();

	if (m_pObject != nullptr)
	{
		m_pObject->Update();
	}

	// �N���Ƃ̓����蔻��
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(GetPosition());

	// �e�̐ݒ�
	if (nullptr != m_pShadow) {
		m_pShadow->SetPosition(D3DXVECTOR3(GetPosition().x, fHeight + 1.0f, GetPosition().z));
	}

	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);	// �v���W�F�N�V�����}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);				// �r���[�}�g���b�N�X���擾
	pDevice->GetViewport(&Viewport);							// �r���[�|�[�g���擾

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h���W����X�N���[�����W�ɕϊ�����
	D3DXVec3Project(&ScreenPos, &pos, &Viewport, &mtxProjection, &mtxView, &mtxWorld);

	if (ScreenPos.x < 0.0f || ScreenPos.x > SCREEN_WIDTH ||
		ScreenPos.y < 0.0f || ScreenPos.y > SCREEN_HEIGHT || ScreenPos.z >= 1.0f)
	{// ��ʂɕ`�悳��Ă��Ȃ�
		return;
	}

	
}

//==========================================================
// �`�揈��
//==========================================================
void CGimmickMove::Draw(void)
{

}

//==========================================================
// ����
//==========================================================
CGimmickMove *CGimmickMove::Create(void)
{
	CGimmickMove *pObjectMove = new CGimmickMove;

	if (pObjectMove != NULL)
	{
		// ����������
		pObjectMove->Init();
	}

	return pObjectMove;
}

//==========================================================
// ����
//==========================================================
CGimmickMove *CGimmickMove::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, float fTimer)
{
	CGimmickMove *pObjectMove = new CGimmickMove;

	if (pObjectMove != NULL)
	{
		// ����������
		pObjectMove->Init();

		// �ݒ�
		pObjectMove->SetPosition(pos);
		pObjectMove->SetMove(move);
		pObjectMove->SetNumTimer(fTimer);
		pObjectMove->SetNowTimer(fTimer);
	}

	return pObjectMove;
}

//==========================================================
// ����֘A
//==========================================================
void CGimmickMove::Controller(void)
{
	// ���W�X�V
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();
	float m_fSlowMulti = 1.0f;	// �X���[�{��

	if (!m_pSlow)
	{
		m_fSlowMulti = m_pSlow->Get();
	}

	pos += m_move;
	SetPosition(pos);

	if (m_fNumMoveTimer == 0.0f)
	{// �������Ȃ�
		return;
	}

	m_fNowMoveTimer -= m_fSlowMulti;

	if (m_fNowMoveTimer <= 0.0f)
	{
		m_move *= -1.0f;
		m_fNowMoveTimer = m_fNumMoveTimer;

		D3DXVECTOR2 vec;
		vec.y = -m_move.x;
		vec.x = -m_move.z;
		D3DXVec2Normalize(&vec, &vec);
		rot.y = atan2f(vec.y, vec.x);
		SetRotation(rot);
	}

	if(m_pObject != NULL)
	{
		m_pObject->SetPosition(GetPosition());
		m_pObject->SetRotation(GetRotation());
	}
}

//==========================================================
// �ʔ���`�F�b�N
//==========================================================
bool CGimmickMove::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage)
{
	bool bLand = false;	// ���n�������ۂ�
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(COLLISION_SIZE, COLLISION_SIZE, COLLISION_SIZE);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(-COLLISION_SIZE, -COLLISION_SIZE, -COLLISION_SIZE);
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	if (m_pObject == NULL)
	{
		return bLand;
	}

	// �����𔽉f

	if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
		&& pos.y + vtxMin.y <= ObjPos.y + vtxObjMax.y)
	{//�v���C���[�ƃ��f�������������ɂ���
		if (posOld.x + vtxMin.x >= m_posOld.x + vtxObjMax.x
			&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
			&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
		{//�E���獶�ɂ߂荞��
			bLand = true;
			move.x *= -1.0f;
			//move.x *= fRefMulti;
			pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f + m_move.x;
			nDamage = DAMAGE;
		}
		else if (posOld.x + vtxMax.x <= m_posOld.x + vtxObjMin.x
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
			&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
		{//������E�ɂ߂荞��
		 //�ʒu��߂�
			bLand = true;
			move.x *= -1.0f;
			//move.x *= fRefMulti;
			pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f + m_move.x;
			//move.x = 0.0f;
			nDamage = DAMAGE;
		}
		else if (posOld.z + vtxMin.z >= m_posOld.z + vtxObjMax.z
			&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
			&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
		{//�������O�ɂ߂荞��
			//�ʒu��߂�
			bLand = true;
			move.z *= -1.0f;
			//move.z *= fRefMulti;
			pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f + m_move.z;
			//move.z = 0.0f;
			nDamage = DAMAGE;
		}
		else if (posOld.z + vtxMax.z <= m_posOld.z + vtxObjMin.z
			&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
			&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
			&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
		{//��O���牜�ɂ߂荞��t
		 //�ʒu��߂�
			bLand = true;
			move.z *= -1.0f;
			//move.z *= fRefMulti;
			pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f + m_move.z;
			//move.z = 0.0f;
			nDamage = DAMAGE;
		}
	}

	return bLand;
}