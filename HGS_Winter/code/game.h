//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _GAME_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GAME_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"
#include <mutex>

// �O���錾
class CScore;
class CTime;
class CPlayer;
class CMapCamera;
class CFileLoad;
class CEditor;
class CPause;
class CObject2D;
class CClient;
class CMeshDome;
class CCountDown;

// �}�N����`
#define NUM_FILTER	(2)

//===============================================
// �Q�[���N���X�̒�`(�h���N���X)
//===============================================
class CGame : public CScene
{
public:

	enum STATE
	{
		STATE_TIMEATTACK = 0,
		STATE_MULTI,
		STATE_END,
		STATE_MAX
	};

public:

	// �����o�֐�
	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetState(STATE state) { m_state = state; }
	void SendPosition(const D3DXVECTOR3& pos);
	void SendRotation(const D3DXVECTOR3& rot);
	void SendDamage(const int nDamage);
	void SendLife(const int nLife);
	void SendSetUp(void);
	void SendGoal(void);

	// �����o�֐�(�|�C���^)
	CScore *GetScore(void);
	CTime *GetTime(void);
	CPlayer *GetPlayer(void);
	CFileLoad *GetFileLoad(void);
	CPause *GetPause(void);
	CEditor *GetEditor(void);
	CMapCamera *GetMapCamera(void) { return m_pMapCamera; }

private:

	void GimmickSet(void);

	// TCP�ʐM�p�֐�
	void Online(void);
	void ByteCheck(char *pRecvData, int nRecvByte);
	void OnlineEnd(void);
	void AddressLoad(char *pAddrss);

	CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	CScore *m_pScore;		// �X�R�A�̃|�C���^
	CTime *m_pTime;		// �^�C���̃|�C���^
	CPlayer *m_pPlayer;	// �v���C���[�̃|�C���^
	CPause *m_pPause;		// �|�[�Y�̃|�C���^
	CEditor *m_pEditor;	// �G�f�B�^�[�̃|�C���^
	CMapCamera *m_pMapCamera;		// �~�j�}�b�v�p�J����
	CMeshDome *m_pMeshDome;		// ���b�V���h�[���̃|�C���^
	CObject2D *m_pStart;	// �X�^�[�g���̕���
	CClient *m_pClient;	// �N���C�A���g�̃|�C���^
	char m_aAddress[30];	// �ڑ���T�[�o�[�̃A�h���X
	static STATE m_state;	// ���
	int m_nSledCnt;		// ���ݓ��삵�Ă���X���b�h��
	CCountDown *m_pCountDown;	// �J�E���g�_�E���̃|�C���^
	WSADATA m_wsaData;
	std::mutex m_mutex;
	bool m_bEnd;
};

#endif