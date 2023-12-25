//===============================================
//
// NPCの処理 [npc.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "npc.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "meshfield.h"
#include "Xfile.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include "shadow.h"
#include "gimmick.h"
#include <assert.h>
#include "character.h"
#include "motion.h"
#include "sound.h"
#include "particle.h"
#include "enemy.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE	(0.21f)		// 移動量
#define SHW_MOVE	(1.0f)	// シャワー中移動量
#define PLAYER_GRAVITY	(-0.15f)		//プレイヤー重力
#define PLAYER_JUMP		(10.0f)		//プレイヤージャンプ力
#define ROT_MULTI	(0.075f)	// 向き補正倍率
#define WIDTH	(20.0f)		// 幅
#define HEIGHT	(80.0f)	// 高さ
#define INER	(0.015f)		// 慣性
#define STOP_INER (0.125f)	// 停止慣性
#define STEP_SPEED	(50.0f)
#define STEP_COOLTIME	(90.0f)
#define START_LIFE	(4)	// 初期体力
#define DAMAGE_INTERVAL	(10.0f)
#define DAMAGE_APPEAR	(110.0f)
#define DEATH_INTERVAL	(120.0f)
#define DASH_INTERVAL	(60.0f)
#define SPAWN_INTERVAL	(60.0f)
#define PARTICLE_TIMER	 (5.0f)
#define SHADOW_ALPHA	(0.4f)
#define STOP_LENGTH	(300.0f)

namespace COOLTIME
{
	const int STOP = (90);
	const int WAIT = (90);
}

namespace
{
	const float DAMAGE = 0.002f; // 一回のヒットで受けるダメージ量
	const float RADIUS = 100.0f;
	const int MAX_SPAWN = 3;
	const int SPAWN_TIMER = 20;
}

// 前方宣言
CNpc *CNpc::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CNpc *CNpc::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
int CNpc::m_nNumCount = 0;
float CNpc::m_SpawnCnt = 0.0f;

//===============================================
// コンストラクタ
//===============================================
//CNpc::CNpc()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CNpc::CNpc()
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pObject = NULL;
	m_fLife = 0;
	m_pTarget = nullptr;

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

	m_nNumCount++;
}

//===============================================
// デストラクタ
//===============================================
CNpc::~CNpc()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CNpc::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\Enemy.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
	}

	m_fLife = 0.0f;

	m_pObject->SetDraw();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CNpc::Uninit(void)
{
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

	if (nullptr != m_pObject) {
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	m_nNumCount--;

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CNpc::Update(void)
{
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_Info.state != STATE_DEATH)
	{
		// プレイヤー操作
		Controller();
	}

	CManager::GetInstance()->GetDebugProc()->Print("向き [%f, %f, %f]\n", GetRotation().x, GetRotation().y, GetRotation().z);
	CManager::GetInstance()->GetDebugProc()->Print("位置 [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);

	// 使用オブジェクト更新
	if (nullptr != m_pObject) {
		m_pObject->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y - 50.0f, m_Info.pos.z - 20.0f));
		m_pObject->SetRotation(m_Info.rot);
		m_pObject->Update();
	}

	// 起伏との当たり判定
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y - 1.0f, m_Info.pos.z));
	m_Info.pos.y = fHeight;
}

//===============================================
// 生成
//===============================================
CNpc *CNpc::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move)
{
	CNpc *pNpc = NULL;

	// オブジェクト2Dの生成
	pNpc = new CNpc;

	if (nullptr != pNpc)
	{// 生成できた場合
	 // 初期化処理
		pNpc->Init();

		// 座標設定
		pNpc->SetPosition(pos);

		// 向き設定
		pNpc->SetRotation(rot);

		pNpc->m_fRotDest = rot.y;

		// 移動量設定
		pNpc->SetMove(move);

		// 種類の設定
		//pNpc->SetType(TYPE_PLAYER);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pNpc;
}

//===============================================
// 操作処理
//===============================================
void CNpc::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得
	D3DXVECTOR3 rot = GetRotation();	// 向きを取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();					// カメラのポインタ
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	D3DXVECTOR3 CamRot = pCamera->GetRotation();								// カメラの角度
	bool bDamage = false;
	m_fRotMove = rot.y;	//現在の向きを取得
	int nDamage = 0;

	// 操作処理
	{

		Move();		// 移動
		Rotation();	// 回転
	}

	pos = GetPosition();	// 座標を取得

	// 慣性(ステップ状態別)
	pos.x += m_Info.move.x * CManager::GetInstance()->GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetInstance()->GetSlow()->Get();

	// 調整
	Adjust();

	// オブジェクトとの当たり判定
	if (nullptr != m_pObject)
	{
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(-50.0f, -50.0f, -50.0f);

		// ギミック
		if (CGimmick::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, nDamage))
		{
			bDamage = true;
			CManager::GetInstance()->GetDebugProc()->Print("***ギミックと当たったよ***\n");
		}

		// 壁
	}

	// ダメージ確認
	
	if (nDamage >= 0)
	{
		if (bDamage)
		{
			CManager::GetInstance()->GetScene()->SendDamage(nDamage);
			Damage(nDamage);
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
		}
	}

	{
		float fIner = INER;

		// 慣性を変更するか確認
		if (m_Info.state == STATE_MOVE) {	// 移動中
			if (m_pTarget != nullptr) {
				// 距離を取得
				float fLength = sqrtf((pos.x - m_pTarget->GetPosition().x) * (pos.x - m_pTarget->GetPosition().x)
					+ (pos.z - m_pTarget->GetPosition().z) * (pos.z - m_pTarget->GetPosition().z));

				if (fLength <= STOP_LENGTH) {
					fIner = STOP_INER;
					m_Info.state = STATE_STOP;
					m_Info.fStateCounter = COOLTIME::WAIT;
				}
			}
		}
		else {
			fIner = STOP_INER;
		}

		D3DXVECTOR3 moveOld = m_Info.move;

		m_Info.move.x += (0.0f - m_Info.move.x) * fIner;	//x座標
		m_Info.move.z += (0.0f - m_Info.move.z) * fIner;	//x座標

		if (fIner == STOP_INER) {	// 停止中の場合
			D3DXVECTOR3 moveDiff = moveOld - m_Info.move;

			// 移動量負だったら正にする
			if (moveDiff.x < -1.0f) {
				moveDiff.x *= -1.0f;
			}
			if (moveDiff.y < -1.0f) {
				moveDiff.y *= -1.0f;
			}
			if (moveDiff.z < -1.0f) {
				moveDiff.z *= -1.0f;
			}

			float fAdd = moveDiff.x + moveDiff.y + moveDiff.z;
			fAdd * 1.5f;

			CParticle::Create(m_Info.pos, m_Info.move, CEffect::TYPE_SNOWNPC, static_cast<int>(fAdd) * 4);
		}
	}

	// 壁との当たり判定
	CMeshWall::Collision(pos, m_Info.posOld);

	m_Info.pos = pos;

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n回転[W,A,S,D] : 加速[SPACE] : ステップ[K, (Rボタン)]\n");
}

//===============================================
// 移動
//===============================================
void CNpc::Move(void)
{
	if (m_Info.state != STATE_MOVE) {
		return;
	}

	if (m_pTarget == nullptr) {
		return;
	}

	float fMove = MOVE * (1.0f - m_fLife);
	D3DXVECTOR3 nor = m_pTarget->GetPosition() - m_Info.pos;
	D3DXVec3Normalize(&nor, &nor);
	m_fRotDest = atan2f(nor.x, nor.z);
	m_Info.move.x += sinf(m_fRotDest) * fMove;
	m_Info.move.z += cosf(m_fRotDest) * fMove;
	m_fRotDest *= -1.0f;

	nor = m_Info.pos - m_pTarget->GetPosition();
	D3DXVec3Normalize(&nor, &nor);
	m_fRotDest = atan2f(nor.x, nor.z);
}

//===============================================
// 回転
//===============================================
void CNpc::Rotation(void)
{
	
}

//===============================================
// 回転
//===============================================
void CNpc::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ

	if (nullptr == pInputKey) {
		return;
	}

	if (pInputKey->GetPress(DIK_W))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.25f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.25f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 0.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_S))
	{
		if (pInputKey->GetPress(DIK_A))
		{
			m_fRotDest = -D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_D))
		{
			m_fRotDest = D3DX_PI * 0.75f;
		}
		else
		{
			m_fRotDest = D3DX_PI * 1.0f;
		}
	}
	else if (pInputKey->GetPress(DIK_A))
	{
		m_fRotDest = -D3DX_PI * 0.5f;
	}
	else if (pInputKey->GetPress(DIK_D))
	{
		m_fRotDest = D3DX_PI * 0.5f;
	}
}

//===============================================
// 調整
//===============================================
void CNpc::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//目標までの移動方向の差分

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//===============================================
// 状態管理
//===============================================
void CNpc::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_NEUTRAL:

		m_pObject->GetMotion()->Set(0);
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_MOVE;

			// 対象を設定
			LockOn();
		}

		break;

	case STATE_MOVE:
	{
		m_pObject->GetMotion()->BlendSet(1);
	}
		break;

	case STATE_STOP:

		m_pObject->GetMotion()->BlendSet(2);
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = COOLTIME::STOP;
			m_Info.state = STATE_NEUTRAL;
		}

		break;

	case STATE_DEATH:

		

		break;
	}
}

//===============================================
// ダメージ処理
//===============================================
void CNpc::Damage(int nDamage)
{
	/*int nOldLife = m_nLife;
	m_nLife -= nDamage;

	if (m_nLife < 0)
	{
	m_nLife = 0;
	}

	if (m_nLife != nOldLife)
	{
	m_Info.fStateCounter = DAMAGE_INTERVAL;
	m_Info.state = STATE_DAMAGE;
	}*/
}

//===============================================
// 体力設定
//===============================================
void CNpc::SetLife(int nLife)
{
	
}

//===============================================
// ロックオン設定
//===============================================
void CNpc::LockOn(void)
{
	CEnemy *pEnemy = CEnemy::GetTop();
	CEnemy *KariTarget = nullptr;

	// 次のターゲットを設定
	while (pEnemy != nullptr) {
		CEnemy *pEnemyNext = pEnemy->GetNext();

		if (m_pTarget != pEnemy) {
			KariTarget = pEnemy;

			if (rand() % 3 == 0) {
				break;
			}
		}

		pEnemy = pEnemyNext;
	}

	m_pTarget = KariTarget;
}

//===============================================
// 当たり判定
//===============================================
bool CNpc::Collision(const D3DXVECTOR3& pos, float fRadius)
{
	// 距離を取得
	float fLength = sqrtf((pos.x - m_Info.pos.x) * (pos.x - m_Info.pos.x)
		+ (pos.z - m_Info.pos.z) * (pos.z - m_Info.pos.z));

	float fSize = fRadius + RADIUS;

	if (fLength > fSize)
	{// 触れていない
		return false;
	}

	m_fLife += DAMAGE;

	if (m_fLife >= 1.0f) {
		Uninit();
	}
	
	return true;
}

//===============================================
// 当たり判定
//===============================================
void CNpc::Spawn(void)
{
	if (m_nNumCount >= MAX_SPAWN) {
		return;
	}

	m_SpawnCnt += CManager::GetInstance()->GetDeltaTime();
	
	if (m_SpawnCnt >= SPAWN_TIMER) {
		m_SpawnCnt = 0.0f;
		CNpc::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}