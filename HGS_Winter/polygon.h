//========================================
//
//シューティングアクション[polygon.h]
//Author：森川駿弥
//
//========================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "main.h"
#include "object3D.h"

//========================================
//ポリゴンクラス
//========================================
class CPolygon : public CObject3D
{
public:
	CPolygon();		//コンストラクタ
	~CPolygon();	//デストラクタ

	//メンバ関数
	static CPolygon *Create(void);	//ポリゴン生成

	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画

private:
	//メンバ変数
	static 	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	CObject3D *m_pObj3D;
};

#endif