//==========================================
//
//  �U���ΏۃN���X(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "objectX.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy : public CObjectX
{
public:

	// �����o�֐�
	CEnemy(int nPriority = 0); // �R���X�g���N�^
	~CEnemy(); // �f�X�g���N�^

	HRESULT Init(void) override; // ����������
	void Uninit(void) override; // �I������
	void Update(void) override; // �X�V����
	void Draw(void) override; // �`�揈��
	void Hit(); // ����������
	CEnemy *GetNext(void) { return m_pNext; }

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority = 4);
	static CEnemy* GetTop(void) { return m_pTop; }

private:

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) override;

	// �����o�ϐ�
	// �����o�ϐ�c
	static CEnemy *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

	CEnemy *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	float m_Life; // �I�u�W�F�N�g�̗̑�
};

#endif
