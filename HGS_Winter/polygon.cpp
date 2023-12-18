//========================================
//
//�V���[�e�B���O�A�N�V����[polygon.cpp]
//Author�F�X��x��
//
//========================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//========================================
//�}�N����`
//========================================
#define POLYGON_TEX		"data\\texture\\block001.jpg"

//========================================
//�ÓI�����o�ϐ�
//========================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CPolygon::CPolygon()
{
}

//========================================
//�f�X�g���N�^
//========================================
CPolygon::~CPolygon()
{
}

//========================================
//�|���S������
//========================================
CPolygon *CPolygon::Create(void)
{
	//CPlayer�^�̃|�C���^
	CPolygon *pPolygon = nullptr;

	if (pPolygon == nullptr)
	{
		//�v���C���[����
		pPolygon = new CPolygon;

		//������
		pPolygon->Init();
	}

	//�|�C���^��Ԃ�
	return pPolygon;
}

//========================================
//������
//========================================
HRESULT CPolygon::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (m_pObj3D == nullptr)
	{
		//CObject2D�̃|�C���^
		m_pObj3D = CObject3D::Create();

		//�e�N�X�`�����蓖��
		m_pObj3D->BindTexture(pTexture->Regist(POLYGON_TEX));
	}

	return S_OK;
}

//========================================
//�I��
//========================================
void CPolygon::Uninit(void)
{
	//�I��
	CObject3D::Uninit();
}

//========================================
//�X�V
//========================================
void CPolygon::Update(void)
{

}

//========================================
//�`��
//========================================
void CPolygon::Draw(void)
{
	//�`��
	CObject3D::Draw();
}