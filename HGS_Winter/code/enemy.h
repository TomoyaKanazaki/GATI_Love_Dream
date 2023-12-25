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

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority = 4);

private:

	// �����o�֐�
	bool CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) override;

	// �����o�ϐ�
	float m_Life; // �I�u�W�F�N�g�̗̑�
};

#endif
