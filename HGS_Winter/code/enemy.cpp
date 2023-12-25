//==========================================
//
//  �U���ΏۃN���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "Xfile.h"
#include "manager.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float DAMAGE = 0.001f; // ���̃q�b�g�Ŏ󂯂�_���[�W��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_Life(0.0f)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	return CObjectX::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	CObjectX::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority)
{
	CEnemy* pEnemy = nullptr;
	CXFile* pModelFile = CManager::GetInstance()->GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// �����ł����ꍇ
		// ����������
		pEnemy->Init();

		// ���W
		pEnemy->SetPosition(pos);

		// ����
		pEnemy->SetRotation(rot);

		// ��ސݒ�
		pEnemy->SetType(TYPE_MODEL);

		// �ǂݍ��݊m�F
		pEnemy->BindFile(pModelFile->Regist(pFileName));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy;
}

//==========================================
//  �ʔ���`�F�b�N(override)
//==========================================
bool CEnemy::CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	// �_���[�W���󂯂�
	if (m_Life < 1.0f)
	{
		m_Life += DAMAGE;
	}

	/*
	�����ŐF��ς���
	*/

	return CObjectX::CollisionCheck(pos, posOld, move, vtxMin, vtxMax);
}
