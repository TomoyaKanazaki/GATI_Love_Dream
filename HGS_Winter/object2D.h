//========================================
//
//シューティングアクション[object2D.h]
//Author：森川駿弥
//
//========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//========================================
//マクロ定義
//========================================
#define MAX_OBJ	(64)		//背景の最大数

//========================================
//オブジェクト2Dクラス
//========================================
class CObject2D : public CObject
{
public:
	CObject2D();	//コンストラクタ
	~CObject2D();	//デストラクタ

	//メンバ関数
	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画
	static CObject2D *Create();		//オブジェクトの生成
	void SetVertex(void);			//頂点情報
	void SetSize(float fWidht, float fHeight);	//大きさ
	void SetPosition(D3DXVECTOR3 pos);			//位置設定
	D3DXVECTOR3 GetPosition(void);				//位置取得
	void BindTexture(int pTexture);				//テクスチャ割り当て
	void SetVertexAnim(int Num, int Cnt);		//テクスチャアニメーション
	void SetPosVertex(void);		//頂点情報
	void SetVertexBg(void);			//背景の頂点情報
	void SetVertexEffect(float m_fRadius, D3DXCOLOR m_col);		//エフェクトの頂点座標
	void SetVertexMoveBg(void);
	void SetScoreVertex(void);		//スコアの頂点情報
	void SetScore(int nNum[8]);

private:
	//メンバ変数
	int m_nIdxTexture;		//テクスチャの番号
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		//頂点情報を格納
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き
	D3DXCOLOR m_col;        //色
	float m_fLength;		//対角線の長さ
	float m_fAngle;			//対角線の角度
	int m_nCounterAnim;     //アニメーションカウンター
	int m_nPatternAnim;     //アニメーションパターンNo,
	float m_aTexV;			//テクスチャ座標の開始位置
};

#endif