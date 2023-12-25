//==========================================
//
//  攻撃対象クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "Xfile.h"
#include "manager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float DAMAGE = 0.001f; // 一回のヒットで受けるダメージ量
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_Life(0.0f)
{

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
bool CEnemy::CollisionCheck(D3DXVECTOR3& pos, D3DXVECTOR3& posOld, D3DXVECTOR3& move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	// ダメージを受ける
	if (m_Life < 1.0f)
	{
		m_Life += DAMAGE;
	}

	/*
	ここで色を変える
	*/

	return CObjectX::CollisionCheck(pos, posOld, move, vtxMin, vtxMax);
}
