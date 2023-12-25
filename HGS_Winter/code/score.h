//==========================================
//
//  スコアクラス(score.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCORE_H_
#define _SCORE_H_

//==========================================
//  前方宣言
//==========================================
class CNumber;

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
	void AddScorePoint(const int AddPoint = 5); // スコアの加算
	int GetScorePoint() const { return m_ScorePoint; } // スコアの取得

	// 静的メンバ関数
	static CScore* Create();

private:

	//定数定義
#define NUM_NUM (8) // すうじのかず

	// メンバ関数
	void LimitScore(); // スコアの制限

	// メンバ変数
	CNumber* m_apNumber[NUM_NUM]; // 数字のポインタ

	// 静的メンバ変数
	static int m_ScorePoint; // 現在のスコア

};

#endif
