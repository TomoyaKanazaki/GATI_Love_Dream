//=======================================
//
//�V���[�e�B���O�A�N�V����[polygon.cpp]
//Author : MORIKAWA SHUNYA
//
//=======================================

#include "main.h"		//�쐬����main.h���C���N���[�h����
#include "billboard.h"  //�쐬����fade.h���C���N���[�h����
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=======================================
//�}�N����`
//=======================================
#define BILLBOARD_TEX	"data\\TEXTURE\\LIFE.png"

#define BILL_WIDTH		(40)	//�r���{�[�h�̕�
#define BILL_HEIGHT		(40)	//�r���{�[�h�̍���

#define BULLET_SIZE     (25)    //�e�̃T�C�Y

//========================================
//�ÓI�����o�ϐ�
//========================================
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = nullptr;	//�e�N�X�`���̃|�C���^

//=======================================
//�R���X�g���N�^
//=======================================
CBillboard::CBillboard() : 
	m_nIdxTexture(0),		//�e�N�X�`���ԍ�
	m_pVtxBuff(nullptr),	//���_���
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//�ʒu
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//�ړ���
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		//����
	m_col(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)),	//�F
	m_fLength(0.0f),	//�Ίp���̒���
	m_fAngle(0.0f)		//�Ίp���̒���
{
}

//=======================================
//�f�X�g���N�^
//=======================================
CBillboard::~CBillboard()
{
}

//=======================================
//�e�N�X�`���ǂݍ���
//=======================================
HRESULT CBillboard::Load(void)
{
	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		BILLBOARD_TEX,
		&m_pTexture)))
	{// ���s��Ԃ�
		return E_FAIL;
	}

	//������Ԃ�
	return S_OK;
}

//=======================================
//�e�N�X�`���j��
//=======================================
void CBillboard::Unload(void)
{
	//�e�N�X�`���̏I������
	if (m_pTexture != nullptr)
	{//m_pTexture��nullptr����Ȃ��Ƃ�
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//=======================================
//�r���{�[�h����
//=======================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, float fwidth, float fheight)
{
	//pBillboard�^�̃|�C���^
	CBillboard *pBillboard = nullptr;

	if (pBillboard == nullptr)
	{//pBillboard��nullptr�̎�
		//�r���{�[�h����
		pBillboard = new CBillboard;

		//�T�C�Y�ݒ�
		pBillboard->SetSize(fwidth, fheight);

		//�ʒu�ݒ�
		pBillboard->SetPosition(pos);

		//������
		pBillboard->Init();
	}

	//�|�C���^��Ԃ�
	return pBillboard;
}

//=======================================
//�r���{�[�h�̏���������
//=======================================
HRESULT CBillboard::Init(void)
{
	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=======================================
//�r���{�[�h�̏I������
//=======================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̏I������
	if (m_pVtxBuff != nullptr)
	{//m_pTexture��nullptr����Ȃ��Ƃ�
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g(�������g)�̔j��
	Release();
}

//=======================================
//�r���{�[�h�̍X�V����
//=======================================
void CBillboard::Update(void)
{
}

//=======================================
//�r���{�[�h�̕`�揈��
//=======================================
void CBillboard::Draw(void)
{
	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���N�X�擾�p

	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//CTexture�^�̃|�C���^
	CTexture *pTexture = CManager::GetTexture();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);	//�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture)); //�e�N�X�`�����g�p���ĂȂ��Ƃ���nullptr

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=======================================
//�e�N�X�`�����蓖��
//=======================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//========================================
//�e�N�X�`���̊��蓖��
//========================================
void CBillboard::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}

//========================================
//�e�̒��_���W
//========================================
void CBillboard::SetPosVertex(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�A�j���[�V�����r���{�[�h�̒��_���W
//========================================
void CBillboard::SetVertexAnim(int Num, int Cnt)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍Đݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / Num * Cnt, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / Num * (Cnt + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / Num * Cnt, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / Num * (Cnt + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//���_���̃T�C�Y�ݒ�
//========================================
void CBillboard::SetSizeVertex(float fwidth, float fheight)
{
	m_fWidth = fwidth;
	m_fHeight = fheight;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-fwidth, fheight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fwidth, fheight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fwidth, -fheight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fwidth, -fheight, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�r���{�[�h�G�t�F�N�g�̒��_���W
//========================================
void CBillboard::SetEffectVertex(float fEffectsize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍Đݒ�
	pVtx[0].pos = D3DXVECTOR3(-fEffectsize, fEffectsize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fEffectsize, fEffectsize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fEffectsize, -fEffectsize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fEffectsize, -fEffectsize, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�r���{�[�h�̈ړ���
//========================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//========================================
//�r���{�[�h�̈ړ��ʎ擾
//========================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}

//========================================
//�r���{�[�h�̒��_���W
//========================================
void CBillboard::SetVertex(void)
{

}

//========================================
//�e�r���{�[�h�̒��_���W
//========================================
void CBillboard::SetSize(float fWidht, float fHeight)
{
	//�Ίp���̒���(���A�c)
	m_fLength = sqrtf(fWidht * fWidht + fHeight * fHeight) * 1.0f;

	//�Ίp���̌���(���A�c)
	m_fAngle = atan2f(fWidht, fHeight);
}

//========================================
//�ʒu�ݒ�
//========================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================
//�ʒu�擾
//========================================
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}