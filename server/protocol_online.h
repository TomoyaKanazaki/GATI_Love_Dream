//==========================================================
//
// �����L���O����M�v���g�R�� [protocol_ranking.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PROTOCOL_ONLINE_H_
#define _PROTOCOL_ONLINE_H_

// �}�N����`
#define MAX_COMMAND_DATA	((sizeof(int) + sizeof(int) + 1024))	// �f�[�^�̃}�b�N�X�T�C�Y

//**********************************************************
// ����M�p�v���g�R���񋓂��`
//**********************************************************
enum COMMAND_TYPE
{
	COMMAND_TYPE_NONE = 0,			// �������Ȃ�
	COMMAND_TYPE_SETPOSITION,		// ���W�ݒ�
	COMMAND_TYPE_SETROTATION,		// �����ݒ�
	COMMAND_TYPE_SETLIFE,			// �̗͐ݒ�
	COMMAND_TYPE_SETCHECKPOINT,	// �`�F�b�N�|�C���g�ʉ�
	COMMAND_TYPE_GOAL,			// �S�[��
	COMMAND_TYPE_START_OK,			// �J�n��������
	COMMAND_TYPE_CREATE,			// ����
	COMMAND_TYPE_DAMAGE,			// �_���[�W
	COMMAND_TYPE_DELETE,			// ����
	COMMAND_TYPE_GETID,			// ID�擾
	COMMAND_TYPE_MAX
};

#endif