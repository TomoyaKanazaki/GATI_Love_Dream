//=======================================
//
//シューティングアクション[light.h]
//Author　:　MORIKAWA SHUNYA
//
//=======================================

#ifndef _LIGHT_H_     //このマクロ定義が定義されていなかったら
#define _LIGHT_H_    //2連インクルード防止のマクロを定義する

#include "main.h"

//=======================================
//ライトクラス
//=======================================
class CLight
{
public:
	CLight();	//コンストラクタ
	~CLight();	//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	//メンバ変数
	D3DLIGHT9 m_alight[3];	//ライトの情報
};

#endif