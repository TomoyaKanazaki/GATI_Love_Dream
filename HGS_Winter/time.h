//========================================
//
//�V���[�e�B���O�A�N�V����[time.h]
//Author�F�X��x��
//
//========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#include "number.h"

//========================================
//�}�N����`
//========================================
#define TIME_DIGIT	(3)		//�^�C���̌���

//========================================
//�^�C���N���X
//========================================
class CTime : public CObject
{
public:
	CTime();	//�R���X�g���N�^
	~CTime();	//�f�X�g���N�^

				//�����o�֐�
	static CTime *Create(void);	//�G����

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime);
	void SubTime(int nTime) {SetTime(m_Time - nTime);}	//�^�C�����Z
	int GetTime(void) { return m_Time; }

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�
	int m_Time;				//�^�C���̒l
	int m_nCounterTimer;	//�^�C���J�E���^�[
	CNumber *m_apNumber[TIME_DIGIT];		//CNumber�̔z��
};

#endif