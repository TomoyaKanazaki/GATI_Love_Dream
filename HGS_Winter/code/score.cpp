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

//==========================================
//  定数定義
//==========================================
namespace
{
	const int MAX_SCORE = 99999; // スコアの最大値
}

//==========================================
//  静的メンバ変数宣言
//==========================================
CScore* CScore::m_pScore = nullptr; // 自分自身のポインタ

//==========================================
//  コンストラクタ
//==========================================
CScore::CScore(): m_ScorePoint(0)
{

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
	// スコアを初期化
	m_ScorePoint = 0;
}

//==========================================
//  終了処理
//==========================================
void CScore::Uninit()
{
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
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;
		m_pScore->Init();
	}

	return m_pScore;
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
