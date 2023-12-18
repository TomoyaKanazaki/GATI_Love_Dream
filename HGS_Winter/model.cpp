//========================================
//
//�V���[�e�B���O�A�N�V����[model.cpp]
//Author�F�X��x��
//
//========================================
#include "model.h"
#include "renderer.h"
#include "manager.h"

//========================================
//�R���X�g���N�^
//========================================
CModel::CModel() : 
	m_pTexture(nullptr),		//���L�e�N�X�`��
	m_pMesh(nullptr),			//���b�V��(���_���)�ւ̃|�C���^
	m_pBuffMat(nullptr),		//�}�e���A���ւ̃|�C���^
	m_dwNumMat(NULL),			//�}�e���A���̐�
	m_pos(0.0f, 0.0f, 0.0f),	//�ʒu
	m_rot(0.0f, 0.0f, 0.0f),	//����
	m_pParent(nullptr)			//�e���f���ւ̃|�C���^
{

}

//========================================
//�f�X�g���N�^
//========================================
CModel::~CModel()
{

}

//========================================
//���f������
//========================================
CModel *CModel::Create(const char *pFilename)
{
	//CModel�^�̃|�C���^
	CModel *pModel = nullptr;

	if (pModel == nullptr)
	{
		//�v���C���[����
		pModel = new CModel;

		//������
		pModel->Init(pFilename);
	}

	//�|�C���^��Ԃ�
	return pModel;
}

//========================================
//������
//========================================
HRESULT CModel::Init(const char *pFilename)
{
	//���[�J���ϐ��錾
	D3DXMATERIAL *pMat;

	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ʒu�̐ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_dwNumMat,
		&m_pMesh);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)m_dwNumMat; nCntTex++)
	{
		if (pMat[nCntTex].pTextureFilename != nullptr)
		{//�e�N�X�`���t�@�C���������݂���
		 //�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntTex].pTextureFilename, &m_pTexture);
		}
	}
	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CModel::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//========================================
//�X�V
//========================================
void CModel::Update(void)
{

}

//========================================
//�`��
//========================================
void CModel::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;
	D3DXMATRIX mtxParent;			//�e���f���̃}�g���b�N�X

	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{//�e�����݂���
		//�e���f���̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e�����݂��Ȃ�
		//����(�ŐV)�̃}�g���b�N�X���擾����{ = �v���C���[�̃}�g���b�N�X}
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{//�}�e���A���̐�����
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture); //�e�N�X�`�����g�p���ĂȂ��Ƃ���nullptr

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================================
//�e���f��
//========================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//========================================
//���[���h�}�g���b�N�X�̎擾
//========================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//========================================
//���_���
//========================================
void CModel::SetVertex(void)
{

}

//========================================
//�T�C�Y����
//========================================
void CModel::SetSize(float fWidht, float fHeight)
{

}

//========================================
//�ʒu�ݒ�
//========================================
void CModel::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================
//�ʒu�擾
//========================================
D3DXVECTOR3 CModel::GetPosition(void)
{
	return m_pos;
}

//========================================
//�����ݒ�
//========================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================
//�����擾
//========================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//========================================
//���f���̔ԍ��ݒ�
//========================================
void CModel::SetIndex(CModel *pModel)
{
	m_pParent = pModel;
}

//========================================
//���f���̔ԍ��ݒ�
//========================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_setPos = pos;
}

//========================================
//���f���̈ʒu�擾
//========================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_setPos;
}

//========================================
//���f���̌���
//========================================
void CModel::SetRotate(D3DXVECTOR3 rot)
{
	m_setRot = rot;
}

//========================================
//���f���̈ʒu�擾
//========================================
D3DXVECTOR3 CModel::GetRotate(void)
{
	return m_setRot;
}
