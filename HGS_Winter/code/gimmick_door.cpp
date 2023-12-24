//==========================================================
//
// �ړ��I�u�W�F�N�g [objectmove.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "gimmick_door.h"
#include "manager.h"
#include "slow.h"
#include "Xfile.h"
#include "objectX.h"
#include "model.h"

// �}�N����`
#define DAMAGE		(1)

//==========================================================
// �R���X�g���N�^
//==========================================================
CGimmickDoor::CGimmickDoor()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aObject[nCnt].GoalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aObject[nCnt].pModel = NULL;
	}

	m_bOpen = nullptr;
	m_nId = -1;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CGimmickDoor::~CGimmickDoor()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CGimmickDoor::Init(void)
{

	// �ǂݍ��݊m�F
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aObject[nCnt].pModel = CModel::Create("data\\MODEL\\door.x");
		m_aObject[nCnt].pModel->SetParent(GetMtxWorld());
		m_aObject[nCnt].GoalPos = D3DXVECTOR3(400.0f + (-800.0f * nCnt), 0.0f, 0.0f);
		m_aObject[nCnt].pModel->SetCurrentPosition(D3DXVECTOR3(150.0f + (-300.0f * nCnt), 0.0f, 0.0f));
	}

	// �X���[���o����
	m_pSlow = CManager::GetInstance()->GetSlow();

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CGimmickDoor::Uninit(void)
{
	
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aObject[nCnt].pModel != nullptr)
		{
			m_aObject[nCnt].pModel->Uninit();
			m_aObject[nCnt].pModel = nullptr;
		}
	}

	ListOut();

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CGimmickDoor::Update(void)
{
	// ����֘A
	Controller();

	SetMtxWorld();
}

//==========================================================
// �`�揈��
//==========================================================
void CGimmickDoor::Draw(void)
{

}

//==========================================================
// ����
//==========================================================
CGimmickDoor *CGimmickDoor::Create(void)
{
	CGimmickDoor *pObjectDoor = new CGimmickDoor;

	if (pObjectDoor != NULL)
	{
		// ����������
		pObjectDoor->Init();
	}

	return pObjectDoor;
}

//==========================================================
// ����
//==========================================================
CGimmickDoor *CGimmickDoor::Create(const D3DXVECTOR3& pos)
{
	CGimmickDoor *pObjectDoor = new CGimmickDoor;

	if (pObjectDoor != NULL)
	{
		// ����������
		pObjectDoor->Init();

		// �ݒ�
		pObjectDoor->SetPosition(pos);
	}

	return pObjectDoor;
}

//==========================================================
// ����֘A
//==========================================================
void CGimmickDoor::Controller(void)
{
	// ���W�X�V
	if (m_bOpen)
	{
		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
		{
			if (m_aObject[nCnt].pModel == nullptr)
			{
				continue;
			}

			D3DXVECTOR3 pos = m_aObject[nCnt].pModel->GetCurrentPosition();
			D3DXVECTOR3 posDiff = m_aObject[nCnt].GoalPos - 
				pos;

			pos += posDiff * 0.04f;
			m_aObject[nCnt].pModel->SetCurrentPosition(pos);
		}
	}

}

//==========================================================
// �ʔ���`�F�b�N
//==========================================================
bool CGimmickDoor::CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage)
{
	CXFile *pFile = CManager::GetInstance()->GetModelFile();
	bool bLand = false;	// ���n�������ۂ�
	D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ObjPos = GetPosition();
	D3DXVECTOR3 ObjRot = GetRotation();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aObject[nCnt].pModel == nullptr)
		{
			continue;
		}

		// �����𔽉f
		m_aObject[nCnt].pModel->SetRotSize(vtxObjMax,
			vtxObjMin,
			pFile->GetMax(m_aObject[nCnt].pModel->GetId()),
			pFile->GetMin(m_aObject[nCnt].pModel->GetId()),
			ObjRot.y);

		ObjPos = D3DXVECTOR3(m_aObject[nCnt].pModel->GetMtxWorld()->_41, m_aObject[nCnt].pModel->GetMtxWorld()->_42, m_aObject[nCnt].pModel->GetMtxWorld()->_43);

		if (pos.y + vtxMax.y > ObjPos.y + vtxObjMin.y
			&& pos.y + vtxMin.y <= ObjPos.y + vtxObjMax.y)
		{//�v���C���[�ƃ��f�������������ɂ���
			if (posOld.x + vtxMin.x >= ObjPos.x + vtxObjMax.x
				&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x
				&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
				&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
			{//�E���獶�ɂ߂荞��
				bLand = true;
				move.x *= -1.0f;
				pos.x = ObjPos.x + vtxObjMax.x - vtxMin.x + 0.1f;
				nDamage = DAMAGE;
			}
			else if (posOld.x + vtxMax.x <= ObjPos.x + vtxObjMin.x
				&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
				&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
				&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z)
			{//������E�ɂ߂荞��
			 //�ʒu��߂�
				bLand = true;
				move.x *= -1.0f;
				pos.x = ObjPos.x + vtxObjMin.x - vtxMax.x - 0.1f;
				nDamage = DAMAGE;
			}
			else if (posOld.z + vtxMin.z >= ObjPos.z + vtxObjMax.z
				&& pos.z + vtxMin.z < ObjPos.z + vtxObjMax.z
				&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
				&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
			{//�������O�ɂ߂荞��
			 //�ʒu��߂�
				bLand = true;
				move.z *= -1.0f;
				pos.z = ObjPos.z + vtxObjMax.z - vtxMin.z + 0.1f;
				nDamage = DAMAGE;
			}
			else if (posOld.z + vtxMax.z <= ObjPos.z + vtxObjMin.z
				&& pos.z + vtxMax.z > ObjPos.z + vtxObjMin.z
				&& pos.x + vtxMax.x > ObjPos.x + vtxObjMin.x
				&& pos.x + vtxMin.x < ObjPos.x + vtxObjMax.x)
			{//��O���牜�ɂ߂荞��t
			 //�ʒu��߂�
				bLand = true;
				move.z *= -1.0f;
				pos.z = ObjPos.z + vtxObjMin.z - vtxMax.z - 0.1f;
				nDamage = DAMAGE;
			}
		}
	}

	return bLand;
}

void CGimmickDoor::Open(int nId)
{
	if (nId == m_nId)
	{
		m_bOpen = true;
	}
}