//==========================================
//
//  スコアクラス(score.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "score.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "number.h"
#include "object2D.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const int MAX_SCORE = 99999999; // スコアの最大値
	const D3DXVECTOR2 NUM_SIZE = D3DXVECTOR2(80.0f, 120.0f); // 数字のサイズ
	const D3DXVECTOR3 NUM_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - NUM_SIZE.x * (NUM_NUM * 0.5f - 0.5f), SCREEN_HEIGHT * 0.5f, 0.0f); // 数字の位置
}

//==========================================
//  静的メンバ変数宣言
//==========================================
int CScore::m_ScorePoint = 0; // 自分自身のポインタ

//==========================================
//  コンストラクタ
//==========================================
CScore::CScore()
{
	for (int i = 0; i < NUM_NUM; ++i)
	{
		m_apNumber[i] = nullptr;
	}
}

//==========================================
//  デストラクタ
//==========================================
CScore::~CScore()
{

}

//==========================================
//  初期化初期
//==========================================
void CScore::Init()
{
	// リザルトの時だけ数字を出す
	if (CManager::GetInstance()->GetMode() == CScene::MODE_RESULT)
	{
		// テクスチャ座標を算出
		int nCalc = m_ScorePoint;
		int nNum[NUM_NUM];
		for (int i = NUM_NUM - 1; i >= 0; --i)
		{
			nNum[i] = nCalc % 10;
			nCalc /= 10;
		}

		for (int i = 0; i < NUM_NUM; ++i)
		{
			if (m_apNumber[i] == nullptr)
			{
				D3DXVECTOR3 pos = NUM_POS;
				pos.x += NUM_SIZE.x * i + NUM_SIZE.x * 0.5f;
				m_apNumber[i] = CNumber::Create(pos, NUM_SIZE.x, NUM_SIZE.y);
				m_apNumber[i]->GetObject2D()->BindTexture(CTexture::TYPE_SCORE);
				m_apNumber[i]->SetIdx(nNum[i]);
			}
		}
	}

	// スコアを初期化
	m_ScorePoint = 0;
}

//==========================================
//  終了処理
//==========================================
void CScore::Uninit()
{
	// 数字を破棄
	for (int i = 0; i < NUM_NUM; ++i)
	{
		if (m_apNumber[i] != nullptr)
		{
			delete m_apNumber[i];
			m_apNumber[i] = nullptr;
		}
	}

	// 自分自身の破棄
	delete this;
}

//==========================================
//  更新処理
//==========================================
void CScore::Update()
{
#ifdef _DEBUG
	// デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print
	(
		"スコア : %d", m_ScorePoint
	);

	// デバッグキー
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_UP))
	{
		m_ScorePoint += 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_DOWN))
	{
		m_ScorePoint -= 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetPress(DIK_RIGHT))
	{
		m_ScorePoint += 100;
	}
	if (CManager::GetInstance()->GetInputKeyboard()->GetPress(DIK_LEFT))
	{
		m_ScorePoint -= 100;
	}
#endif

	// スコア制限
	LimitScore();
}

//==========================================
//  描画処理
//==========================================
void CScore::Draw()
{

}

//==========================================
//  スコアの加算
//==========================================
void CScore::AddScorePoint(const int AddPoint)
{
	// スコアを加算する
	m_ScorePoint += AddPoint;

	// スコア制限
	LimitScore();
}

//==========================================
//  生成処理
//==========================================
CScore* CScore::Create()
{
	CScore* pScore = new CScore;

	pScore->Init();

	return pScore;
}

//==========================================
//  スコア制限
//==========================================
void CScore::LimitScore()
{
	// スコアを補正する
	if (m_ScorePoint < 0) // スコアが負の数になった場合
	{
		// スコアを0に補正する
		m_ScorePoint = 0;
	}
	else if (m_ScorePoint > MAX_SCORE)
	{
		// スコアを最大値に補正する
		m_ScorePoint = MAX_SCORE;
	}
}
