//==========================================================
//
//�e�`�揈��
//Author ����ɐ�
//
//==========================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CShadow::CShadow() : CObject3D(3)
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CShadow::~CShadow()
{

}

//==========================================================
//�e�̏���������
//==========================================================
HRESULT CShadow::Init(void)
{
	CObject3D::Init();

	return S_OK;
}

//==========================================================
//�e�̏I������
//==========================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================================
//�e�̍X�V����
//==========================================================
void CShadow::Update(void)
{

}

//==========================================================
//�e�̕`�揈��
//==========================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CObject3D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================================
//�e�̐ݒ菈��
//==========================================================
CShadow *CShadow::Create(const D3DXVECTOR3& pos, float fWidth, float fHeight)
{
	CShadow *pShadow = NULL;	// �e�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���̃|�C���^

	// �I�u�W�F�N�g2D�̐���
	pShadow = new CShadow;

	if (pShadow != NULL)
	{// �����ł����ꍇ

		// ����������
		pShadow->Init();

		// ���W�ݒ�
		pShadow->SetPosition(pos);

		// �T�C�Y�ݒ�
		pShadow->SetpVtx(fWidth, fHeight);

		// ��ސݒ�
		pShadow->SetType(TYPE_NONE);

		// �e�N�X�`���ݒ�
		pShadow->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_SHADOW)));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pShadow;
}
