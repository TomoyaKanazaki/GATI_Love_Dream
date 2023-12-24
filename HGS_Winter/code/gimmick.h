//==========================================================
//
// �M�~�b�N��� [gimmick.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _GIMMICK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GIMMICK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CGimmick : public CTask
{
protected:

	// ��ޗ񋓌^
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_MOVE,
		TYPE_ROTATE,
		TYPE_FISH,
		TYPE_MAX
	};

public:	// �N�ł��A�N�Z�X�\

	CGimmick();	// �R���X�g���N�^
	virtual ~CGimmick();	// �f�X�g���N�^

	// �������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Reverse(void) { }
	virtual void Open(int) { }

	// �����o�֐�
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	void SetMtxWorld(void);
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }
	static bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage);
	void AirReverse(void);
	void DoorOpen(int nId);

protected:

	// ��ސݒ�
	void BindType(TYPE type) { m_type = type; }
	void ListOut(void);

private:	// �����������A�N�Z�X�\

	virtual bool CollisionCheck(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, const D3DXVECTOR3& vtxMin, const D3DXVECTOR3& vtxMax, int &nDamage) = 0;

	// �����o�ϐ�
	static CGimmick *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CGimmick *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CGimmick *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CGimmick *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;	// ���
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
};

#endif


