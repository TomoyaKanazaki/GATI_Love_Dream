//========================================
//
//�Q�[��������[game.h]
//Author�F�X��x��
//
//========================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"

//========================================
//�O���錾
//========================================
class CObjectX;
class CObject3D;
class CLight;
class CPlayer;
class CPolygon;
class CGameObject;
class CBg;
class CTime;

//========================================
//�}�N��
//========================================
#define MAX_ITEM	(256)	//�A�C�e���̍ő吔
#define MAX_BULLET	(80)	//�e�̍ő吔

//========================================
//�Q�[���N���X
//========================================
class CGame : public CScene
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	//�����o�֐�
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PauseState(bool bPauseState) { m_bPause = bPauseState; }	//�|�[�Y��Ԃ��ǂ���

	static CGame *GetGame(void) { return m_pGame; }		//�Q�[���}�l�[�W���[�̏��
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	static CObject *m_pObject[MAX_DATA];		//�I�u�W�F�N�g�̃|�C���^
	static CObjectX *m_pObjectX;		//X�t�@�C���I�u�W�F�N�g�̃|�C���^
	static CObject3D *m_pObject3D;		//�I�u�W�F�N�g3D�̃|�C���^
	static CGame *m_pGame;				//�Q�[���}�l�[�W���[�̃|�C���^
	static CLight *m_pLight;			//���C�g�̃|�C���^
	static CPlayer *m_pPlayer;			//�v���C���[�̃|�C���^
	static CPolygon *m_pPolygon;		//�|���S���̃|�C���^
	static CGameObject *m_pGameObject;	//�Q�[�����I�u�W�F�N�g
	static CBg *m_pBg;					//�w�i�̃|�C���^
	static CTime *m_pTime;				//�^�C���̃|�C���^
	bool m_bPause;						//�|�[�Y��Ԃ�ON/OFF
};

#endif
