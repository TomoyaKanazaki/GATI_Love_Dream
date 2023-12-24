//===============================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "slow.h"
#include "game.h"
#include "meshfield.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(30)		// ����

// ��ނ��Ƃ̐F
const D3DXCOLOR CEffect::m_aColInfo[TYPE_MAX]
{
	{ 1.0f, 1.0f, 1.0f, 1.0f },
	{ 0.5f, 0.5f, 1.0f, 1.0f },
};

// ��ނ��Ƃ̔��a
const float CEffect::m_aRadiusInfo[TYPE_MAX]
{
	{ 30.0f },
	{ 6.0f },
};

//===============================================
// �R���X�g���N�^
//===============================================
//CEffect::CEffect()
//{
//	// �l�̃N���A
//	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Info.fLife = 0;
//	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_Info.fRadius = 0.0f;
//	m_Info.Type = TYPE_NONE;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEffect::CEffect(int nPriority) : CObjectBillboard(nPriority)
{
	// �l�̃N���A
	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Info.fLife = 0;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.fRadius = 0.0f;
	m_Info.Type = TYPE_NONE;
	m_fusion = FUSION_ADD;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEffect::~CEffect()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEffect::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	CObjectBillboard::Init();

	m_Info.fLife = LIFE;	// �̗͂̏�����
	m_Info.Type = TYPE_NONE;

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEffect::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObjectBillboard::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CEffect::Update(void)
{
	m_Info.fLife -= CManager::GetInstance()->GetSlow()->Get();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(GetPosition());

	if (m_Info.fLife < 0)
	{// �������Ȃ��Ȃ����ꍇ

		// �I������
		Uninit();
	}
	else
	{// �܂�����ꍇ
		D3DXVECTOR3 pos = GetPosition();	// ���W

		pos += m_Info.move * CManager::GetInstance()->GetSlow()->Get();

		// ���W
		SetPosition(pos);

		switch (m_Info.Type)
		{
		case TYPE_NONE:
			m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
			break;

		case TYPE_BULLET:
			m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
			break;

		case TYPE_DUST:
			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= 0.1f * CManager::GetInstance()->GetSlow()->Get();

			m_Info.move -= m_Info.move * 0.035f * CManager::GetInstance()->GetSlow()->Get();

			break;
		case TYPE_EXPLOSION:
			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.y += 0.01f * CManager::GetInstance()->GetSlow()->Get();
			break; 

		case TYPE_SHWBULLET:
			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= (rand() % 100 - 50) * 0.01f;
			m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();

			break;

		case TYPE_SHWREF:
			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= (rand() % 100 - 50) * 0.01f;
			m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();

			if (GetPosition().y < fHeight)
			{
				m_Info.move.y *= -1.0f;
			}

			break;

		case TYPE_SWEAT:
			m_Info.col.a -= 0.04f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= 0.005f * CManager::GetInstance()->GetSlow()->Get();
			//m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();
			break;

		case TYPE_HEAT:
			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= (rand() % 100 - 50) * 0.01f;
			//m_Info.move.y += -0.1f * CManager::GetInstance()->GetSlow()->Get();
			break;

		case TYPE_SWAP:

			m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.x -= m_Info.move.x * 0.5f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.z -= m_Info.move.z * 0.5f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.y -= m_Info.move.y * 0.05f * CManager::GetInstance()->GetSlow()->Get();

			break;
		case TYPE_BALEXPLOSION:	// ����

			m_Info.col.a -= 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= 1.2f * CManager::GetInstance()->GetSlow()->Get();

			break;

		case TYPE_SMAKE:	// ����

			m_Info.col.a -= 0.035f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.y -= m_Info.move.y * 0.005f * CManager::GetInstance()->GetSlow()->Get();

			break;

		case TYPE_HEATHAZE:	// ����

			m_Info.col.a -= 0.0001f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= (rand() % 100 - 50) * 0.01f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.x += (rand() % 100 - 50) * 0.01f;
			m_Info.move.z += (rand() % 100 - 50) * 0.01f;

			break;

		case TYPE_BUBBLE:	// ����

			m_Info.col.a -= 0.0001f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.fRadius -= (rand() % 100 - 50) * 0.05f * CManager::GetInstance()->GetSlow()->Get();
			m_Info.move.x += (rand() % 100 - 50) * 0.005f;
			m_Info.move.z += (rand() % 100 - 50) * 0.005f;

			break;
		}

		if (m_Info.col.a < 0.0f || m_Info.fRadius < 0.0f)
		{// �l���Ђ�����Ԃ���
			Uninit();
		}
		else
		{
			if (m_Info.Type != TYPE_SWAP)
			{
				SetSize(m_Info.fRadius, m_Info.fRadius);
			}

			SetCol(m_Info.col);
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�𖳌�������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	CObjectBillboard::Draw();

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	if (m_fusion == FUSION_ADD)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else if (m_fusion == FUSION_MINUS)
	{
		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect(7);

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// ����������
		pEffect->Init();

		// �I�u�W�F�N�g�̎�ނ̐ݒ�
		pEffect->SetType(CObject::TYPE_NONE);

		// �G�t�F�N�g�̐ݒ�
		pEffect->m_Info.Type = type;

		// ���a�ݒ�
		pEffect->RadiusSet();

		// �T�C�Y�̐ݒ�
		//pEffect->SetSize(pEffect->m_Info.fRadius, pEffect->m_Info.fRadius);

		// �F�̐ݒ�
		pEffect->ColorSet();

		// �e�N�X�`���̊��蓖��
		pEffect->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_EFFECT)));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fLife, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect();

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// ����������
		pEffect->Init();

		// �I�u�W�F�N�g�̎�ނ̐ݒ�
		pEffect->SetType(CObject::TYPE_NONE);

		// �G�t�F�N�g�̐ݒ�
		pEffect->m_Info.Type = type;

		// ���a�ݒ�
		pEffect->m_Info.fRadius = fRadius;

		// �����ݒ�
		pEffect->m_Info.fLife = fLife;

		// �ړ��ʐݒ�
		pEffect->SetMove(move);

		// �T�C�Y�̐ݒ�
		//pEffect->SetSize(pEffect->m_Info.fRadius, pEffect->m_Info.fRadius);

		// �F�̐ݒ�
		pEffect->m_Info.col = col;
		pEffect->SetCol(pEffect->m_Info.col);

		// �e�N�X�`���̊��蓖��
		pEffect->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_EFFECT)));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// �F�ݒ�
//===============================================
void CEffect::ColorSet(void)
{
	// ��ނ��ƂɐF�̐ݒ�
	m_Info.col = m_aColInfo[m_Info.Type];
   	SetCol(m_Info.col);
}

//===============================================
// �T�C�Y�̐ݒ�
//===============================================
void CEffect::RadiusSet(void)
{
	// ���a�̐ݒ�
	m_Info.fRadius = m_aRadiusInfo[m_Info.Type];
}

//===============================================
// �ړ��ʂ̐ݒ�
//===============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	m_Info.move = move;
}