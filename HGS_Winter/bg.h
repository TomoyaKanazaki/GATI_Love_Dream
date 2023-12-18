//========================================
//
//シューティングアクション[bg.h]
//Author：森川駿弥
//
//========================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "object2D.h"

//========================================
//マクロ定義
//========================================
#define MAX_BG	(3)		//背景の最大数

//========================================
//背景クラス
//========================================
class CBg : public CObject2D
{
public:
	CBg();		//コンストラクタ
	~CBg();		//デストラクタ
	
	//メンバ関数
	static CBg *Create(void);		//背景の生成

	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画

	void SetPosition(D3DXVECTOR3 pos);		//位置設定
	D3DXVECTOR3 GetPosition(void);			//位置取得

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;		//共有テクスチャ
	D3DXVECTOR3 m_pos;
	float m_aTexV;		//テクスチャ座標の開始位置(V値)
};

#endif