//========================================
//
//シューティングアクション[Number.cpp]
//Author：森川駿弥
//
//========================================
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"

//========================================
//コンストラクタ
//========================================
CNumber::CNumber()
{

}

//========================================
//デストラクタ
//========================================
CNumber::~CNumber()
{

}

//========================================
//ナンバー生成
//========================================
CNumber *CNumber::Create(void)
{
	//CBullet型のポインタ
	CNumber *pNumber = nullptr;

	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetTexture();

	if (pNumber == nullptr)
	{
		//プレイヤー生成
		pNumber = new CNumber;

		//初期化
		pNumber->Init();
	}

	//ポインタを返す
	return pNumber;
}
