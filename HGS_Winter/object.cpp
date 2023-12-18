//========================================
//
//�V���[�e�B���O�A�N�V����[object.cp]
//Author�F�X��x��
//
//========================================
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "texture.h"

//========================================
//�ÓI�����o�ϐ��錾
//========================================
CObject *CObject::m_apObject[MAX_DATA] = {};
int CObject::m_nNumAll = 0;

//========================================
//�R���X�g���N�^
//========================================
CObject::CObject(void)
{//�l�N���A
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] == nullptr)
		{
			m_apObject[nCntObject] = this;	//�������g����
			m_nID = nCntObject;				//�������g��ID
			m_nNumAll++;					//�������J�E���g�A�b�v
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
			break;
		}
	}
}

//========================================
//�f�X�g���N�^
//========================================
CObject::~CObject(void)
{
}

//========================================
//���ׂẴI�u�W�F�N�g�̔j��
//========================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//========================================
//���ׂẴI�u�W�F�N�g�̍X�V
//========================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Update();
		}
	}
}

//========================================
//���ׂẴI�u�W�F�N�g�̕`��
//========================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//�J�����ݒ�
	pCamera->SetCamera();

	for (int nCntObject = 0; nCntObject < MAX_DATA; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//========================================
//�I�u�W�F�N�g�̔j��
//========================================
void CObject::Release(void)
{
	int nNum = m_nID;

	if (m_apObject[nNum] != nullptr)
	{
		//�I�u�W�F�N�g(�������g�̔j��)
		delete m_apObject[nNum];
		m_apObject[nNum] = nullptr;

		//�������J�E���g�_�E��
		m_nNumAll--;
	}
}

//========================================
//TYPE�̎擾
//========================================
CObject *CObject::GetObject(int nIdx)
{
	return m_apObject[nIdx];
}

//========================================
//�e�N�X�`���̊��蓖��
//========================================
void CObject::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}