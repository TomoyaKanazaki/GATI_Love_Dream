//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TUTORIAL_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TUTORIAL_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

// �O���錾
class CScore;
class CTime;
class CPlayer;
class CMapCamera;
class CLight;
class CFileLoad;
class CEditor;
class CSlow;
class CObject3D;
class CMeshField;
class CPause;
class CThermo;
class CEnemyManager;
class CCarManager;
class CEnemyRoute;
class CMeshDome;

//===============================================
// �Q�[���N���X�̒�`(�h���N���X)
//===============================================
class CTutorial : public CScene
{
public:

	// �����o�֐�
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����o�֐�(�|�C���^)
	static CScore *GetScore(void);
	CTime *GetTime(void);
	CPlayer *GetPlayer(void);
	static CSlow *GetSlow(void);
	static CMeshField *GetMeshField(void);
	static void SetMesh(CMeshField *pMesh) { m_pMeshField = pMesh; }
	CFileLoad *GetFileLoad(void);
	CEnemyRoute *GetEnemyRoute(void) { return m_pEnemyRoute; }
	CCarManager *GetCarManager(void) { return m_pCarManager; }

private:

	void DataReset(void);
	void EnemySet(void);
	void CarSet(void);
	void SkySet(void);
	void StartEnemy(void);

	CFileLoad *m_pFileLoad;			// �t�@�C���ǂݍ��݂̃|�C���^
	static CScore *m_pScore;		// �X�R�A�̃|�C���^
	CTime *m_pTime;					// �^�C���̃|�C���^
	CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^
	static CSlow *m_pSlow;			// �X���[�̃|�C���^
	static CMeshField *m_pMeshField;	// ���b�V���t�B�[���h�̃|�C���^
	CEnemyManager *m_pEnemyManager;	// �G�l�~�[�}�l�[�W���[�̃|�C���^
	CCarManager *m_pCarManager;		// �J�[�}�l�[�W���[�̃|�C���^
	CEnemyRoute *m_pEnemyRoute;		// �G�̏��H�Ǘ��̃|�C���^
	CMeshDome *m_pMeshDome;			// ���b�V���h�[���̃|�C���^
};

#endif