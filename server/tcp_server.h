//==========================================================
//
// winsock�ʐM(�T�[�o�[) [tcp_server.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TCP_SERVER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TCP_SERVER_H_	// ��d�C���N���[�h�h�~�̃}�N�����`

#include "tcp_listener.h"

//==========================================================
// �T�[�o�[�N���X�̒�`
//==========================================================
class CServer : public CListener
{
public:	// �N�ł��A�N�Z�X�\

	CServer();	// �R���X�g���N�^
	~CServer();	// �f�X�g���N�^

	// �����o�֐�
	bool Init(int nPortNum);
	void Uninit(void);

private:	// ���������A�N�Z�X�\

};

#endif