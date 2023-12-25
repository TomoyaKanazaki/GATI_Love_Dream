//===============================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "billboard.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(30)		// ����

//===============================================
// �R���X�g���N�^
//===============================================
CParticle::CParticle()
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CParticle::~CParticle()
{

}

//===============================================
// ����
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, CEffect::TYPE type)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type, 0);
}

//===============================================
// ���_���ݒ�
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, CEffect::TYPE type, int nNum)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, move, type, nNum);
}

//===============================================
// �ݒ�
//===============================================
void CParticle::Set(const D3DXVECTOR3& Defpos, const D3DXVECTOR3& Defmove, CEffect::TYPE type, int nNum)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 move = {};	// �ړ���
	D3DXCOLOR col = {};	// �F
	CEffect::TYPE ParType = type;
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;
	float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

	// �ړ��x�N�g�������߂�
	D3DXVec3Normalize(&nor, &Defmove);	// �x�N�g���𐳋K������

	switch (type)
	{
	case CEffect::TYPE_NONE:	// �����Ȃ�

		break;

	case CEffect::TYPE_SNOWATK:	// ��
	{
		float fTanf = atan2f(Defmove.x, Defmove.z);
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			float fRand = static_cast<float>((rand() % 51 - 25) * 0.01f);
			float fRand2 = static_cast<float>(rand() % 100);
			//�ړ��ʂ̐ݒ�
			move.x = sinf(fRand + fTanf) * (fRand2 * 0.5f);
			move.y = ((float)(rand() % 3 + 1)) * 0.2f;
			move.z = cosf(fRand + fTanf) * (fRand2 * 0.5f);

			float frand = rand() % 8 * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

			//���a�̐ݒ�
			fRadius = 5.0f;

			//�����̐ݒ�
			fLife = 500.0f;

			CEffect::Create(Defpos + (move), move, col, fRadius, fLife, type);
		}
	}
	break;
	}
}