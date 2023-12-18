//=======================================
//
//シューティングアクション[billboard.h]
//Author　:　MORIKAWA SHUNYA
//
//=======================================

#ifndef _BILLBOARD_H_     //このマクロ定義が定義されていなかったら
#define _BILLBOARD_H_    //2連インクルード防止のマクロを定義する

#include "main.h"
#include "object3d.h"

//=======================================
//ビルボードクラス
//=======================================
class CBillboard : public CObject
{
public:
	CBillboard();	//コンストラクタ
	~CBillboard();	//デストラクタ

	//メンバ関数
	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄

	static CBillboard *Create(D3DXVECTOR3 pos, float fwidth, float fheight);	//ビルボード生成

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ割り当て
	void BindTexture(int pTexture);				//テクスチャ割り当て
	void SetPosVertex(void);
	void SetVertexAnim(int Num, int Cnt);		//テクスチャアニメーション
	void SetSizeVertex(float size, float fheight);
	void SetEffectVertex(float fEffectsize);		//エフェクトの頂点情報
	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetMove(void);
	void SetVertex(void);
	void SetSize(float fWidht, float fHeight);	//サイズ設定
	void SetPosition(D3DXVECTOR3 pos);			//位置設定
	D3DXVECTOR3 GetPosition(void);				//位置取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	int m_nIdxTexture;		//テクスチャの番号
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//頂点情報を格納
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き
	D3DXCOLOR m_col;        //色
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fLength;		//対角線の長さ
	float m_fAngle;			//対角線の角度
};

#endif