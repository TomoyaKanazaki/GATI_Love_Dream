//=======================================
//
//�G�t�F�N�g����[effect.cpp]
//Author : MORIKAWA SHUNYA
//
//=======================================

#include "effect.h"      //�쐬����effect.h���C���N���[�h����
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===========================================
//�}�N����`
//===========================================
#define EFFECT_LIFE		(100)		//�G�t�F�N�g�̎���
#define EFFECT_MOVE		(10.0f)		//�G�t�F�N�g�̈ړ���

//===========================================
//�R���X�g���N�^
//===========================================
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	m_fRadius = 0.0f;	//���a(�傫��)
	m_nLife = 0;		//����(�\������)
	m_nType = 0;		//���
	bool m_balpha = false;			//���Z����

}

//===========================================
//�f�X�g���N�^
//===========================================
CEffect::~CEffect()
{
}

//===========================================
//����
//===========================================
CEffect *CEffect::Create(void)
{
	//CEffect�^�̃|�C���^
	CEffect *pEffect = nullptr;

	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetTexture();

	if (pEffect == nullptr)
	{//nullptr�̎�
		//�C���X�^���X����
		pEffect = new CEffect;

		//������
		pEffect->Init();

		//�e�N�X�`�����蓖��
		pEffect->BindTexture(pTexture->Regist("data\\texture\\effect000.png"));
	}

	//�|�C���^��Ԃ�
	return pEffect;
}

//===========================================
//�G�t�F�N�g�̏���������
//===========================================
HRESULT CEffect::Init(void)
{
	//������
	CBillboard::Init();

	//������Ԃ�
	return S_OK;
}

//===========================================
//�G�t�F�N�g�̏I������
//===========================================
void CEffect::Uninit(void)
{
	//�I��
	CBillboard::Uninit();
}

//===========================================
//�G�t�F�N�g�̍X�V����
//===========================================
void CEffect::Update(void)
{
	//�X�V
	CBillboard::Update();

	//�e�̈ړ�
	D3DXVECTOR3 pos = GetPosition();

	//�e�̈ʒu�X�V
	pos += m_move;

	//���a
	m_fRadius += ((float)(rand() % 100) / 100.0f - 0.3f) * 5.0f;

	//���l(�����鑬�x)
	m_col.a -= 0.01f;

	//�̗͌��Z
	m_nLife--;

	if (m_nLife < 0)
	{
		//�j������
		Uninit();
	}
}

//===========================================
//�G�t�F�N�g�̕`�揈��
//===========================================
void CEffect::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�`��
	CBillboard::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
