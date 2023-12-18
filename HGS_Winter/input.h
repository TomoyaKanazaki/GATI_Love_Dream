//========================================
//
//�V���[�e�B���O�A�N�V����[input.h]
//Author�F�X��x��
//
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#define  DIRECTINPUT_VERSION (0x0800)   //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"   //���͏����ɕK�v
#include "Xinput.h"

//========================================
//���C�u�����̃����N
//========================================
#pragma comment(lib,"dinput8.lib")  //���͏����ɕK�v
#pragma comment (lib,"xinput.lib")

//========================================
//�}�N����`
//========================================
#define NUM_MAX_KEY		(256)	//�L�[�̍ő吔
#define NUM_MAX_PAD		(4)		//�p�b�h�̍ő吔
//#define NUM_PAD_MAX  (13)    //�p�b�h�̃{�^���̍ő吔

//========================================
//�C���v�b�g�N���X
//========================================
class CInput
{
public:
	CInput();			//�R���X�g���N�^
	virtual ~CInput();	//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;		//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;		//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

//========================================
//�L�[�{�[�h�N���X
//========================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();	//�R���X�g���N�^
	~CInputKeyboard();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	//�����o�ϐ�
	BYTE m_aKeyState[NUM_MAX_KEY];			//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_MAX_KEY];	//�L�[�{�[�h�̃g���K�[���
};

//========================================
//�R���g���[���[�N���X
//========================================
class CInputPad : public CInput
{
public:
	enum JOYKEY
	{
		BUTTON_UP,		//�\����
		BUTTON_DOWN,	//�\����
		BUTTON_LEFT,	//�\����
		BUTTON_RIGHT,	//�\����
		BUTTON_START,	//START
		BUTTON_BACK,	//BACK
		BUTTON_PUSHING_L,     //���X�e�B�b�N��������
		BUTTON_PUSHING_R,     //�E�X�e�B�b�N��������
		BUTTON_LB,		//LB
		BUTTON_RB,		//RB
		BUTTON_10,		//�s��(�g���K�[)
		BUTTON_11,		//�s��(�g���K�[)
		BUTTON_A,		//A�{�^��
		BUTTON_B,		//B�{�^��
		BUTTON_X,		//X�{�^��
		BUTTON_Y,		//Y�{�^��
		BUTTON_XSTICK,	//X�X�e�B�b�N
		BUTTON_17,		//�s��
		BUTTON_18,		//�s��
		BUTTON_19,		//�s��
		BUTTON_20,
		BUTTONSTATE_MAX
	};

	CInputPad();	//�R���X�g���N�^
	~CInputPad();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey, int nPlayer) {return (m_aPadState[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false;}	//�v���X���擾
	bool GetTrigger(int nKey, int nPlayer) { return (m_aPadStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }	//�g���K�[���擾
	SHORT GetLStickXPress(JOYKEY Key, int nPlayer) { return m_aPadState[nPlayer].Gamepad.sThumbLX; }	//L�X�e�B�b�N��X���v���X���擾
	SHORT GetLStickYPress(JOYKEY Key, int nPlayer) { return m_aPadState[nPlayer].Gamepad.sThumbLY; }	//L�X�e�B�b�N��Y���v���X���擾
	SHORT GetLStickXTrigger(JOYKEY Key, int nPlayer) { return m_aPadStateTrigger[nPlayer].Gamepad.sThumbLX; }	//L�X�e�B�b�N��X���g���K�[���擾
	SHORT GetLStickYTrigger(JOYKEY Key, int nPlayer) { return m_aPadStateTrigger[nPlayer].Gamepad.sThumbLY; }	//L�X�e�B�b�N��Y���g���K�[���擾

	SHORT GetRStickXPress(JOYKEY Key, int nPlayer) { return m_aPadState[nPlayer].Gamepad.sThumbLX; }	//R�X�e�B�b�N��X���v���X���擾
	SHORT GetRStickYPress(JOYKEY Key, int nPlayer) { return m_aPadState[nPlayer].Gamepad.sThumbLY; }	//R�X�e�B�b�N��Y���v���X���擾

private:
	//�����o�ϐ�
	XINPUT_STATE m_aPadState[NUM_MAX_PAD];            //�p�b�h�̏��
	XINPUT_STATE m_aPadStateTrigger[NUM_MAX_PAD];     //�p�b�h�̃g���K�[���
};

#endif