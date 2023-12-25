//===============================================
//
// リザルト画面の管理処理 [result.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "result.h"
#include "time.h"
#include "fileload.h"
#include "meshdome.h"
#include "character.h"
#include "motion.h"
#include "camera.h"

// マクロ定義
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// ランキングファイル
#define MOVE_TIMER	(660)

// リザルトスコア
int CResult::m_nScore = 0;
CResult::TYPE CResult::m_type = CResult::TYPE_MAX;

//===============================================
// コンストラクタ
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
	m_nTimer = 0;
	m_pTime = NULL;

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apCharacter[nCnt] = NULL;
	}
}

//===============================================
// デストラクタ
//===============================================
CResult::~CResult()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CResult::Init(void)
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CResult::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] != NULL)
		{
			m_apScore[nCntRank]->Uninit();
			delete m_apScore[nCntRank];	// メモリの開放
			m_apScore[nCntRank] = NULL;	// 使用していない状態にする
		}
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apCharacter[nCnt] != NULL)
		{
			m_apCharacter[nCnt]->Uninit();
			delete m_apCharacter[nCnt];
			m_apCharacter[nCnt] = NULL;
		}
	}

	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = NULL;
	}

	m_type = TYPE_MAX;
	m_nScore = 0;
}

//===============================================
// 更新処理
//===============================================
void CResult::Update(void)
{
	m_nTimer++;

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apCharacter[nCnt] != nullptr)
		{
			m_apCharacter[nCnt]->Update();
		}
	}

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || m_nTimer > MOVE_TIMER 
		|| CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
	}

	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}

//===============================================
// ランキングデータ保存
//===============================================
void CResult::Save(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //データを読み込む
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===============================================
// ランキングデータ読み込み
//===============================================
void CResult::Load(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //データを読み込む
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
	 //要素を入れておく
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 500 + (nCntRanking * 100);
		}
	}
}

//===============================================
// ランキングデータソート
//===============================================
void CResult::Sort(int *pScore)
{
	// 降順ソート
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// 仮の一番大きい番号

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// 値が大きい場合
				nTempNum = nCntSec;	// 大きい番号を変更
			}
		}

		if (nTempNum != nCntFst)
		{// 変更する場合
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// ランキングイン確認
//===============================================
void CResult::RankIn(int *pScore, int nResult)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// ソート処理
		Sort(pScore);

		// 保存処理
		Save(pScore);

		//ランクインした順位を確認する
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// ランクインした順位を保存			
				break;
			}
		}
	}
}