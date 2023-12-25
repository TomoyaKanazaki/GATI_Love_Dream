//==========================================
//
//  �X�R�A�N���X(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

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
	void AddScorePoint(const int AddPoint) { m_ScorePoint += AddPoint; } // �X�R�A�̉��Z
	int GetScorePoint() const { return m_ScorePoint; } // �X�R�A�̎擾

	// �ÓI�����o�֐�
	static CScore* Create();

private:

	// �����o�ϐ�
	int m_ScorePoint; // ���݂̃X�R�A

	// �ÓI�����o�ϐ�
	static CScore* m_pScore; // �������g�̃|�C���^

};

#endif
