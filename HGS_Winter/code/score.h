//==========================================
//
//  �X�R�A�N���X(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

//==========================================
//  �O���錾
//==========================================
class CNumber;

//==========================================
//  �N���X��`
//==========================================
class CScore
{
public:

	// �����o�֐�
	CScore(); // �R���X�g���N�^
	~CScore(); // �f�X�g���N�^

	void Init(); // ����������
	void Uninit(); // �I������
	void Update(); // �X�V����
	void Draw(); // �`�揈��
	void AddScorePoint(const int AddPoint = 5); // �X�R�A�̉��Z
	int GetScorePoint() const { return m_ScorePoint; } // �X�R�A�̎擾

	// �ÓI�����o�֐�
	static CScore* Create();

private:

	//�萔��`
#define NUM_NUM (8) // �������̂���

	// �����o�֐�
	void LimitScore(); // �X�R�A�̐���

	// �����o�ϐ�
	CNumber* m_apNumber[NUM_NUM]; // �����̃|�C���^

	// �ÓI�����o�ϐ�
	static int m_ScorePoint; // ���݂̃X�R�A

};

#endif
