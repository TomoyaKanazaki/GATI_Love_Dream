//==========================================
//
//  スコアクラス(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

//==========================================
//  クラス定義
//==========================================
class CScore
{
public:

	// メンバ関数
	CScore(); // コンストラクタ
	~CScore(); // デストラクタ

	void Init(); // 初期化処理
	void Uninit(); // 終了処理
	void Update(); // 更新処理
	void Draw(); // 描画処理
	void AddScorePoint(const int AddPoint) { m_ScorePoint += AddPoint; } // スコアの加算
	int GetScorePoint() const { return m_ScorePoint; } // スコアの取得

	// 静的メンバ関数
	static CScore* Create();

private:

	// メンバ変数
	int m_ScorePoint; // 現在のスコア

	// 静的メンバ変数
	static CScore* m_pScore; // 自分自身のポインタ

};

#endif
