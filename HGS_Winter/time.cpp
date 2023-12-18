//========================================
//
//�V���[�e�B���O�A�N�V����[time.cpp]
//Author�F�X��x��
//
//========================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//========================================
//�}�N����`
//========================================
#define TIME_TEX		"data\\texture\\time.png"		//�e�N�X�`���ւ̃p�X
#define TIME_SPACE		(40.0f)		//�^�C���̌������̊Ԋu
#define TIME_POSX		(900.0f)	//�^�C����X���W
#define TIME_POSY		(35.0f)		//�^�C����Y���W
#define TIME_VALUE		(120)		//�^�C���̒l

//========================================
//�R���X�g���N�^
//========================================
CTime::CTime()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Time = 0;			//�^�C���̒l
	m_nCounterTimer = 0;	//�^�C���J�E���^�[

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;		//CNumber�̔z��
	}
}

//========================================
//�f�X�g���N�^
//========================================
CTime::~CTime()
{
}

//========================================
//�^�C������
//========================================
CTime *CTime::Create(void)
{
	//CTime�^�̃|�C���^
	CTime *pTime = nullptr;

	if (pTime == nullptr)
	{//pTime��nullptr�̎�
		//�^�C���̐���
		pTime = new CTime;

		//�ʒu�̏�����
		pTime->m_pos = D3DXVECTOR3(TIME_POSX, TIME_POSY, 0.0f);

		//������
		pTime->Init();

		//�^�C���̏����l
		pTime->SetTime(TIME_VALUE);
	}

	//�|�C���^��Ԃ�
	return pTime;
}

//========================================
//������
//========================================
HRESULT CTime::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetTexture();

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{//nullptr�̎�
			//�^�C���̐���
			m_apNumber[nCnt] = CNumber::Create();

			if (m_apNumber[nCnt] != nullptr)
			{
				m_apNumber[nCnt]->BindTexture(pTexture->Regist(TIME_TEX));

				//�^�C���̃T�C�Y
				m_apNumber[nCnt]->SetSize(70.0f, 70.0f);

				D3DXVECTOR3 posNum = m_pos;

				//�����̊Ԋu
				posNum.x += nCnt * 70.0f;

				//�ʒu�̐ݒ�
				m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(posNum.x - 350.0f, 40.0f, 0.0f));
			}
		}
	}

	//�^�C���̒l
	m_Time = TIME_VALUE;

	//������Ԃ�
	return S_OK;
}

//========================================
//�I��
//========================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	//�������g�̔j��
	CObject::Release();
}

//========================================
//�X�V
//========================================
void CTime::Update(void)
{
	//�J�E���^�[���Z
	m_nCounterTimer++;

	if (m_nCounterTimer >= 60)
	{//�J�E���^�[��60�𒴂�����
		//�^�C�����Z
		SubTime(1);

		m_nCounterTimer = 0;
	}

	if (m_Time == 0)
	{//0�ɂȂ�����^�C�}�[���~�߂�
		m_Time = 0;
	}
}

//========================================
//�`��
//========================================
void CTime::Draw(void)
{
}

//========================================
//�^�C���ݒ�
//========================================
void CTime::SetTime(int nTime)
{
	m_Time = nTime;

	int aTexU[TIME_DIGIT];  //�e���̐������i�[

	aTexU[0] = m_Time % 1000 / 100;
	aTexU[1] = m_Time % 100 / 10;
	aTexU[2] = m_Time % 10 / 1;

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{//��������
		//�A�j���[�V�������_���W(�p�^�[���̍ő吔�A���݂̃p�^�[��)
		m_apNumber[nCnt]->SetVertexAnim(10, aTexU[nCnt]);
	}
}

//========================================
//���_���
//========================================
void CTime::SetVertex(void)
{
}

//========================================
//�T�C�Y����
//========================================
void CTime::SetSize(float fWidht, float fHeight)
{
}
