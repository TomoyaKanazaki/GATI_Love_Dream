//==========================================
//
//  攻撃対象クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "game.h"

// 静的メンバ変数宣言
CEnemy *CEnemy::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CEnemy *CEnemy::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ

//==========================================
//  定数定義
//==========================================
namespace
{
	const float DAMAGE = 0.015f; // 一回のヒットで受けるダメージ量
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_Life(0.0f)
{
	// 自分自身をリストに追加
	if (m_pTop != NULL)
	{// 先頭が存在している場合
		m_pCur->m_pNext = this;	// 現在最後尾のオブジェクトのポインタにつなげる
		m_pPrev = m_pCur;
		m_pCur = this;	// 自分自身が最後尾になる
	}
	else
	{// 存在しない場合
		m_pTop = this;	// 自分自身が先頭になる
		m_pCur = this;	// 自分自身が最後尾になる
	}
}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	return CObjectX::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();

	// リストから自分自身を削除する
	if (m_pTop == this)
	{// 自身が先頭
		if (m_pNext != NULL)
		{// 次が存在している
			m_pTop = m_pNext;	// 次を先頭にする
			m_pNext->m_pPrev = NULL;	// 次の前のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else if (m_pCur == this)
	{// 自身が最後尾
		if (m_pPrev != NULL)
		{// 次が存在している
			m_pCur = m_pPrev;			// 前を最後尾にする
			m_pPrev->m_pNext = NULL;	// 前の次のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_pTop = NULL;	// 先頭がない状態にする
			m_pCur = NULL;	// 最後尾がない状態にする
		}
	}
	else
	{
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;	// 自身の次に前のポインタを覚えさせる
		}
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;	// 自身の前に次のポインタを覚えさせる
		}
	}
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	CObjectX::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* pFileName, const int nPriority)
{
	CEnemy* pEnemy = nullptr;
	CXFile* pModelFile = CManager::GetInstance()->GetModelFile();

	// オブジェクトXの生成
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// 生成できた場合
		// 初期化処理
		pEnemy->Init();

		// 座標
		pEnemy->SetPosition(pos);

		// 向き
		pEnemy->SetRotation(rot);

		// 種類設定
		pEnemy->SetType(TYPE_MODEL);

		// 読み込み確認
		pEnemy->BindFile(pModelFile->Regist(pFileName));

		// 変更後マテリアルカラーの初期化
		pEnemy->ResetMaterial(pFileName);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pEnemy;
}

//==========================================
//  個別判定チェック(override)
//==========================================
bool CEnemy::CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, const int nDamage)
{
	// ヒット判定を取得
	if (!CObjectX::CollisionCheck(pos, posOld, move, vtxMin, vtxMax, nDamage))
	{
		return false;
	}

	// ダメージを受ける
	if (m_Life < 1.0f)
	{
		if (nDamage == 1) {
			m_Life += DAMAGE * 0.85f;

			if (m_Life > 1.0f) {
				m_Life = 1.0f;
			}
			else
			{
				CGame::GetScore()->AddScorePoint(10);
			}
		}
		else if (nDamage == 2) {
			m_Life += DAMAGE * 0.5f;

			if (m_Life > 1.0f) {
				m_Life = 1.0f;
			}
		}

		SetLife(m_Life);

		// マテリアル変更フラグをオンにする
		ChangeCol(true);
	}

	// ヒットで返す
	return true;
}
