//========================================
//
//�V���[�e�B���O�A�N�V����[manager.h]
//Author�F�X��x��
//
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "object.h"

//========================================
//�O���錾
//========================================
class CObject;
class CInputKeyboard;
class CRenderer;
class CScene;
class CDebugProc;
class CTexture;
class CCamera;
class CGame;
class CFade;
class CInputPad;
class CCamera;

//========================================
//�V�[���N���X
//========================================
class CScene
{
public:
	enum MODE
	{//���[�h�̗񋓌^
		MODE_NONE = 0,	//�ݒ�Ȃ�
		MODE_TITLE,		//�^�C�g��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_GAME,		//�Q�[��
		MODE_RESULT,	//���U���g
		MODE_MAX
	};

	CScene();	//�R���X�g���N
	~CScene();	//�f�X�g���N�^

	//�����o�֐�
	static CScene *Create(int nMode);

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	MODE GetMode(void) { return m_mode; }	//���[�h�擾


private:
	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�����i�[
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
	MODE m_mode;			//���݂̃��[�h
};

//========================================
//�}�l�[�W���N���X
//========================================
class CManager
{
public:
	CManager();		//�R���X�g���N�^
	virtual ~CManager();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputPad *GetInputPad(void) { return m_pInputPad; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); }	//���[�h�擾
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CManager *GetInstance();

private:
	//�����o�ϐ�
	int m_nCnt;		//�����J�ڃJ�E���^�[
	int m_state;	//��ԕύX
	int m_NowScene;	//���݂̃V�[��
	static CRenderer *m_pRenderer;				//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	static CInputPad *m_pInputPad;		//�R���g���[���[�̃|�C���^
	static CScene *m_pScene;			//�V�[���̃|�C���^
	static CDebugProc *m_pDebugProc;	//�f�o�b�O�\���̃|�C���^
	static CTexture *m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	static CGame *m_pGame;				//�Q�[���}�l�[�W���[�̃|�C���^
	static CCamera *m_pCamera;			//�J�����̃|�C���^
	static CManager *m_pManager;

};

#endif
