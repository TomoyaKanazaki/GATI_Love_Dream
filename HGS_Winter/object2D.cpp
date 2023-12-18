//========================================
//
//�V���[�e�B���O�A�N�V����[object.cp]
//Author�F�X��x��
//
//========================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "input.h"
#include "texture.h"

//========================================
//�}�N����`
//========================================
#define NUM_PLACE		(8)			//�X�R�A�̌���
#define SCORE_WIDTH		(20.0f)		//�X�R�A�̃T�C�Y
#define SCORE_HEIGHT	(20.0f)		//�X�R�A�̃T�C�Y
#define SCORE_SPACE		(40.0f)		//�X�R�A�̌������̊Ԋu

//========================================
//�R���X�g���N�^
//========================================
CObject2D::CObject2D(void) : 
	m_pos(0.0f, 0.0f, 0.0f),		//�ʒu
	m_move(0.0f, 0.0f, 0.0f),		//�ړ���
	m_rot(0.0f, 0.0f, 0.0f),		//����
	m_col(0.0f, 0.0f, 0.0f, 0.0f),	//�F
	m_fLength(0.0f),		//�Ίp���̒���
	m_fAngle(0.0f),			//�Ίp���̊p�x
	m_nCounterAnim(0),		//�A�j���[�V�����J�E���^�[
	m_nPatternAnim(0),		//�A�j���[�V�����p�^�[��No
	m_pVtxBuff(nullptr),	//���_�����i�[
	m_nIdxTexture(0)		//�e�N�X�`���̔ԍ�
{//�l�N���A

}

//========================================
//�f�X�g���N�^
//========================================
CObject2D::~CObject2D(void)
{

}

//========================================
//�|���S���̐���
//========================================
CObject2D *CObject2D::Create()
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//2D�I�u�W�F�N�g�̐���
		pObject2D = new CObject2D;

		//������
		pObject2D->Init();
	}

	//�|�C���^��Ԃ�
	return pObject2D;
}

//========================================
//�|���S���̏�����
//========================================
HRESULT CObject2D::Init(void)
{
	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (pDevice != nullptr)
	{
		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			nullptr)))
		{// ���s��Ԃ�
			return E_FAIL;
		}

		//�ϐ��̏�����
		m_fLength = sqrtf(50.0f * 50.0f + 50.0f * 50.0f) * 1.0f;	//�Ίp���̒������Z�o����
		m_fAngle = atan2f(50.0f, 50.0f);	//�Ίp���̊p�x���Z�o����

		//���_���
		SetVertex();
	}

	return S_OK;
}

//========================================
//�|���S���̏I��
//========================================
void CObject2D::Uninit(void)
{
	//���_���̏I��
	if (m_pVtxBuff != nullptr)
	{//m_pVtxBuff��nullptr����Ȃ��Ƃ�
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g(�������g)�̔j��
	Release();
}

//========================================
//�|���S���̍X�V
//========================================
void CObject2D::Update(void)
{
	//���_���W
	SetPosVertex();
}

//========================================
//�|���S���̕`��
//========================================
void CObject2D::Draw(void)
{
	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//CTexture�^�̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (pDevice != nullptr)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//========================================
//���_���̐ݒ�
//========================================
void CObject2D::SetVertex(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) *  m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) *  m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) *  m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) *  m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) *  m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) *  m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
}

//========================================
//�|���S���̃T�C�Y����
//========================================
void  CObject2D::SetSize(float fWidht, float fHeight)
{
	//�Ίp���̒���(���A�c)
	m_fLength = sqrtf(fWidht * fWidht + fHeight * fHeight) * 0.5f;

	//�Ίp���̌���(���A�c)
	m_fAngle = atan2f(fWidht, fHeight);

	//���_���
	SetVertex();
}

//========================================
//�ʒu�ݒ�
//========================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;

	//���_���
	SetVertex();
}

//========================================
//�ʒu�擾
//========================================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//========================================
//�e�N�X�`���̊��蓖��
//========================================
void CObject2D::BindTexture(int pTexture)
{
	m_nIdxTexture = pTexture;
}

//========================================
//�A�j���[�V�����e�N�X�`�����W�̍X�V
//========================================
void CObject2D::SetVertexAnim(int Num, int Cnt)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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
//���_���W
//========================================
void CObject2D::SetPosVertex(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) *  m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) *  m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) *  m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) *  m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) *  m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) *  m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) *  m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�w�i�̒��_���
//========================================
void CObject2D::SetVertexBg(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�e�N�X�`�����W�̊J�n�ʒu(V�l)
//========================================
void CObject2D::SetVertexMoveBg(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W(V�l�̍X�V)
	m_aTexV -= 0.001f;

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, m_aTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f, m_aTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_aTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, m_aTexV + 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�G�t�F�N�g�̒��_���W
//========================================
void CObject2D::SetVertexEffect(float m_fRadius, D3DXCOLOR m_col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W���X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fRadius, m_pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fRadius, m_pos.y + m_fRadius, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�X�R�A���_���
//========================================
void CObject2D::SetScoreVertex(void)
{
	//CRenderer�^�̃|�C���^
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - SCORE_WIDTH, m_pos.y - SCORE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y - SCORE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - SCORE_WIDTH, m_pos.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y + SCORE_HEIGHT, 0.0f);

		//�X�R�A�̌��������炷
		m_pos.x += SCORE_SPACE;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   //0.0�`1.0f�Őݒ�
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPatternAnim * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + m_nPatternAnim * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPatternAnim * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + m_nPatternAnim * 0.1f, 1.0f);

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//========================================
//�X�R�A�ݒ�̒��_���
//========================================
void CObject2D::SetScore(int nNum[8])
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_���W���X�V
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - SCORE_WIDTH, m_pos.y - SCORE_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y - SCORE_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - SCORE_WIDTH, m_pos.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y + SCORE_HEIGHT, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);   //0.0�`1.0f�Őݒ�
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + nNum[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + nNum[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nNum[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + nNum[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;

		//�X�R�A�̌��������炷
		m_pos.x += SCORE_SPACE;
	}
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
