//========================================
//
//�V���[�e�B���O�A�N�V����[texture.cpp]
//Author�F�X��x��
//
//========================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//�ꊇ�Ǘ�
const char *str[] = {"data\\texture\\Player.png"};

//========================================
//�ÓI�����o�ϐ�
//========================================
int CTexture::m_nNumAll = 0;

//========================================
//�R���X�g���N�^
//========================================
CTexture::CTexture()
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_apTexture[nCntTex] = {};	//�e�N�X�`���̃|�C���^
		m_apPath[nCntTex] = "\0";
	}
}

//========================================
//�f�X�g���N�^
//========================================
CTexture::~CTexture()
{

}

//========================================
//�e�N�X�`���ꊇ�ǂݍ���
//========================================
HRESULT CTexture::Load(void)
{
	////CRenderer�^�̃|�C���^
	//CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	//{//�S�Ẵe�N�X�`���̓ǂݍ���
	//	if (FAILED(D3DXCreateTextureFromFile(pDevice,
	//		str[nCntTex],
	//		&m_apTexture[nCntTex])))
	//	{// ���s��Ԃ�
	//		return E_FAIL;
	//	}
	//}

	return S_OK;
}

//========================================
//�e�N�X�`���j��
//========================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{//�e�N�X�`���̏I������
		if (m_apTexture[nCntTex] != nullptr)
		{//m_apTexture[nCntTex]��nullptr����Ȃ��Ƃ�
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = nullptr;
		}
	}
}

//========================================
//�e�N�X�`���ʊ��蓖��
//========================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (strcmp(m_apPath[nCntTex], pFilename) == 0)
		{//�t�@�C��������v�����Ƃ�
			//nCntTex�Ԗڂ�Ԃ�
			return nCntTex;
		}

		if (m_apTexture[nCntTex] == nullptr)
		{//nullptr�̎�
			//CRenderer�^�̃|�C���^
			CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

			//�w��̃e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[nCntTex]);

			//�t�@�C����������
			m_apPath[nCntTex] = pFilename;

			//�������J�E���g�A�b�v
			m_nNumAll++;

			//nCntTex�Ԗڂ�Ԃ�
			return nCntTex;
		}
	}

	//NULL��Ԃ�
	return NULL;
}

//========================================
//�e�N�X�`���̃A�h���X�擾
//========================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx >= 0 && nIdx <= m_nNumAll)
	{
		return m_apTexture[nIdx];
	}

	//nullptr��Ԃ�
	return nullptr;
}