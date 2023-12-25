//===============================================
//
// パーティクルの処理 [particle.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "billboard.h"

//===============================================
// マクロ定義
//===============================================
#define LIFE	(30)		// 寿命

//===============================================
// コンストラクタ
//===============================================
CParticle::CParticle()
{

}

//===============================================
// デストラクタ
//===============================================
CParticle::~CParticle()
{

}

//===============================================
// 生成
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, CEffect::TYPE type)
{
	// オブジェクトの種類の設定
	Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type, 0);
}

//===============================================
// 頂点情報設定
//===============================================
void CParticle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, CEffect::TYPE type, int nNum)
{
	// オブジェクトの種類の設定
	Set(pos, move, type, nNum);
}

//===============================================
// 設定
//===============================================
void CParticle::Set(const D3DXVECTOR3& Defpos, const D3DXVECTOR3& Defmove, CEffect::TYPE type, int nNum)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 move = {};	// 移動量
	D3DXCOLOR col = {};	// 色
	CEffect::TYPE ParType = type;
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;
	float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

	// 移動ベクトルを求める
	D3DXVec3Normalize(&nor, &Defmove);	// ベクトルを正規化する

	switch (type)
	{
	case CEffect::TYPE_NONE:	// 何もない

		break;

	case CEffect::TYPE_SNOWATK:	// 煙
	{
		float fTanf = atan2f(Defmove.x, Defmove.z);
		for (int nCnt = 0; nCnt < nNum; nCnt++)
		{
			// 座標の設定
			pos = Defpos;

			float fRand = static_cast<float>((rand() % 51 - 25) * 0.01f);
			float fRand2 = static_cast<float>(rand() % 100);
			//移動量の設定
			move.x = sinf(fRand + fTanf) * (fRand2 * 0.5f);
			move.y = ((float)(rand() % 3 + 1)) * 0.2f;
			move.z = cosf(fRand + fTanf) * (fRand2 * 0.5f);

			float frand = rand() % 8 * 0.1f;

			//色の設定
			col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

			//半径の設定
			fRadius = 5.0f;

			//寿命の設定
			fLife = 500.0f;

			CEffect::Create(Defpos + (move), move, col, fRadius, fLife, type);
		}
	}
	break;
	}
}