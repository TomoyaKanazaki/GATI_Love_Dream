//==========================================================
//
// ���M�~�b�N [gimmick_button.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_air.h"
#include "manager.h"
#include "slow.h"
#include "debugproc.h"
#include "object3D.h"
#include "texture.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickAir::CGimmickAir()
{
	m_pObject = NULL;
	m_bRevease = false;
	m_fHeight = 0.0f; 
	m_fWidth = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveTex = D3DXVECTOR2(0.0f, 0.0f);
	m_TexPos = D3DXVECTOR2(0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickAir::~CGimmickAir()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickAir::Init(void)
{
	// �ǂݍ��݊m�F
	if (m_pObject == NULL)
	{
		m_pObject = CObject3D::Create(GetPosition(), GetRotation());
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickAir::Uninit(void)
{
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	ListOut();

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickAir::Update(void)
{
	// ����֘A
	Controller();

	SetMtxWorld();
}

//==========================================================
// ����
//==========================================================
CGimmickAir *CGimmickAir::Create(void)
{
	CGimmickAir *pObjectAir = new CGimmickAir;

	if (pObjectAir != NULL)
	{
		// ����������
		pObjectAir->Init();
	}

	return pObjectAir;
}

//==========================================================
// ����֘A
//==========================================================
void CGimmickAir::Controller(void)
{
	if (m_pObject == nullptr)
	{
		return;
	}

	m_TexPos += m_moveTex;

	if (m_TexPos.x > 1.0f)
	{
		m_TexPos.x += -1.0f;
	}
	else if (m_TexPos.x < -1.0f)
	{
		m_TexPos.x += 1.0f;
	}
	if (m_TexPos.y > 1.0f)
	{
		m_TexPos.y += -1.0f;
	}
	else if (m_TexPos.y < -1.0f)
	{
		m_TexPos.y += 1.0f;
	}

	// �X�V
	m_pObject->SetpVtx(m_fWidth, m_fHeight);
	m_pObject->SetTextureVtx(m_TexPos.x, m_TexPos.y);
	m_pObject->SetPosition(GetPosition());
}

//==========================================================
// �ʔ���`�F�b�N
//==========================================================
bool CGimmickAir::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage)
{
	bool bLand = false;	// ���n�������ۂ�
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	if (pos.x >= ObjPos.x - m_fWidth &&
		pos.x <= ObjPos.x + m_fWidth &&
		pos.z >= ObjPos.z - m_fHeight &&
		pos.z <= ObjPos.z + m_fHeight)
	{
		CManager::GetInstance()->GetDebugProc()->Print("���ɓ���������[\n");
		// �͈͓�
		move += m_move;
		nDamage = -1;
	}

	return bLand;
}

//==========================================================
// ���]
//==========================================================
void CGimmickAir::Reverse(void)
{
	if (!m_bRevease){
		SetMove(m_move * -1.0f);
	}
}

//==========================================================
// �ړ��ʐݒ�
//==========================================================
void CGimmickAir::SetMove(D3DXVECTOR3 move)
{
	m_move = move;

	if (m_pObject == nullptr)
	{
		return;
	}

	m_moveTex = D3DXVECTOR2(m_move.x * -0.005f, m_move.z * 0.005f);

	D3DXVECTOR3 vec = m_move;
	D3DXVec3Normalize(&vec, &vec);

	if (vec.x != 0.0f)
	{// ���̕�
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\air_rightleft.png"));
	}
	else if (vec.z != 0.0f)
	{// �c�̕�
		m_pObject->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\air_updown.png"));
	}
}