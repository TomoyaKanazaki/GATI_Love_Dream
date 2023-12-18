//========================================
//
//シューティングアクション[object3D.h]
//Author：森川駿弥
//
//========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//========================================
//オブジェクト3Dクラス
//========================================
class CObject3D : public CObject
{
public:
	CObject3D();	//コンストラクタ
	~CObject3D();	//デストラクタ

	//メンバ関数
	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画
	static CObject3D *Create();		//オブジェクトの生成
	void BindTexture(int pTexture);	//テクスチャ割り当て

	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetVertex3D(void);
	void SetVerTexBillboard(void);
	void Collision(void);
	void MeshVertex(void);

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点情報へのポインタ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		 //インデックスバッファへのポインタ

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き

	int m_nIdxTexture;		//テクスチャの番号
};

#endif