//==========================================================
//
// �ړ��M�~�b�N [gimmick_move.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_DOOR_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_DOOR_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "gimmick.h"

// �O���錾
class CSlow;
class CModel;

//==========================================================
// �h�A�̃N���X��`
//==========================================================
class CGimmickDoor : public CGimmick
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_UP = 0,	// �㑤
		TYPE_DOWN,	// ����
		TYPE_MAX
	};

	// �I�u�W�F�N�g�\����
	struct SObject
	{
		CModel *pModel;	// ���f���̃|�C���^
		D3DXVECTOR3 GoalPos;	// ���W
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmickDoor();	// �R���X�g���N�^
	~CGimmickDoor();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmickDoor *Create(void);
	static CGimmickDoor *Create(const D3DXVECTOR3& pos);
	void Open(int nId);

	// �����o�֐�(�擾)
	void SetId(int nId) { m_nId = nId; }

private:	// �����������A�N�Z�X�\

			// �����o�֐�
	void Controller(void);
	bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);

	// �����o�ϐ�
	SObject m_aObject[TYPE_MAX];
	CSlow *m_pSlow;		// �X���[
	bool m_bOpen;			// ��
	int m_nId;			// ID
};

#endif

