//==========================================================
//
// winsock通信(サーバー) [tcp_server.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include <stdio.h>
#include "tcp_server.h"
#include "tcp_client.h"

//==========================================================
// コンストラクタ
//==========================================================
CServer::CServer()
{
	
}

//==========================================================
// デストラクタ
//==========================================================
CServer::~CServer()
{

}

//==========================================================
// 初期化処理
//==========================================================
bool CServer::Init(int nPortNum)
{
	// ソケットの作成
	if (CListener::Init(nPortNum) == FALSE)
	{// 失敗
		printf("*** ソケットの作成に失敗しました ***\n");

		// キー入力待ち
		rewind(stdin);
		getchar();

		return FALSE;
	}

	return TRUE;
}

//==========================================================
// 終了処理
//==========================================================
void CServer::Uninit(void)
{
	// 接続受付用ソケットを閉じる
	CListener::Uninit();
}
