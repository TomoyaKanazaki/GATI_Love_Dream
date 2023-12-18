//=======================================
//
//エフェクト処理[effect.h]
//Author : MORIKAWA SHUNYA
//
//=======================================

#ifndef _EFECT_H_     //このマクロ定義が定義されていなかったら
#define _EFECT_H_    //2連インクルード防止のマクロを定義する

#include "main.h"
#include "billboard.h"

//===========================================
//マクロ定義
//===========================================
#define MAX_EFFECT		(30)		//エフェクトの最大数

//===========================================
//エフェクトクラス
//===========================================
class CEffect : public CBillboard
{
public:
	CEffect();		//コンストラクタ
	~CEffect();		//デストラクタ

	//メンバ関数
	static CEffect *Create(void);	//プレイヤー生成

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR3 m_rot;	//向き
	D3DXCOLOR m_col;	//色
	float m_fRadius;	//半径(大きさ)
	int m_nLife;		//寿命(表示時間)
	int m_nType;		//種類
	D3DXMATRIX m_g_mtxWorldEffectt;	//ワールドマトリックス
	D3DXMATRIX m_mtxRot; 	//計算用マトリックス
	D3DXMATRIX m_mtxTrans;
	D3DXMATRIX m_mtxView;		//ビューマトリクス取得用
	bool m_balpha;			//加算合成
};

#endif