//==========================================================
//
// �`���b�g����M�v���g�R�� [protocol_chat.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PROTOCOL_CHAT_H_
#define _PROTOCOL_CHAT_H_

// �}�N����`

//**********************************************************
// ����M�p�v���g�R���񋓂��`
//**********************************************************
enum COMMAND_TYPE
{
	COMMAND_TYPE_NONE = 0,	// �������Ȃ�
	COMMAND_TYPE_CHAT,		// �`���b�g
	COMMAND_TYPE_JOIN,		// ����
	COMMAND_TYPE_SETNAME,	// ���O�ݒ�
	COMMAND_TYPE_LEAVE,		// �ގ�
	COMMAND_TYPE_MAX
};

#endif
