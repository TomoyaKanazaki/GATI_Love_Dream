//===============================================
//
// プレイヤーの処理 [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
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
#include "billboard.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE	(0.8f)		// 移動量
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

// 前方宣言
CPlayer *CPlayer::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CPlayer *CPlayer::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
int CPlayer::m_nNumCount = 0;

//===============================================
// コンストラクタ
//===============================================
//CPlayer::CPlayer()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CPlayer::CPlayer()
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
	m_pShadow = NULL;
	m_nLife = 0;
	m_type = TYPE_NONE;
	m_nId = -1;
	m_fEffectCount = 0.0f;
	m_bSetUp = false;
	m_bGoal = false;
	m_pGoal = nullptr;

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
CPlayer::~CPlayer()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CPlayer::Init(void)
{
	if (nullptr == m_pObject)
	{
		m_pObject = CCharacter::Create("data\\TXT\\player.txt");
		m_pObject->GetMotion()->InitSet(0);
		m_pObject->SetShadow(true);
	}

	m_nLife = START_LIFE;
	m_type = TYPE_NONE;
	m_bSetUp = false;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxRot);

	// 影の生成
	if (nullptr == m_pShadow)
	{
		m_pShadow = CShadow::Create(m_Info.pos, 50.0f, 50.0f);
		m_pShadow->SetpVtx(100.0f, 100.0f);
		m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	m_pObject->SetDraw();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
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

	if (nullptr != m_pObject){
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	if (nullptr != m_pShadow){
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	if (m_pMapIcon != NULL)
	{
		m_pMapIcon->Uninit();
		m_pMapIcon = NULL;
	}

	if (m_pGoal != NULL)
	{
		m_pGoal->Uninit();
		m_pGoal = NULL;
	}

	m_nNumCount--;

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CPlayer::Update(void)
{
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();

	if (m_pGoal != nullptr)
	{
		D3DXVECTOR3 pos = m_pGoal->GetPosition();

		// 移動
		if (pos.x > SCREEN_WIDTH * 0.75f)
		{
			pos.x -= 30.0f;
		}
		else if (pos.x < SCREEN_WIDTH * 0.35f)
		{
			pos.x -= 40.0f;
		}
		else
		{
			pos.x -= 2.5f;
		}

		m_pGoal->SetPosition(pos);
		m_pGoal->SetVtx();

		if (pos.x < -SCREEN_WIDTH * 0.5f)
		{
			m_pGoal->Uninit();
			m_pGoal = NULL;
		}
	}

	if (m_type == TYPE_SEND)
	{
		CManager::GetInstance()->GetCamera()->Setting(m_Info.pos, m_Info.rot);
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}

	if (m_type == TYPE_ACTIVE)
	{
		if (m_nLife <= 0)
		{
			return;
		}

		if (m_Info.state != STATE_SPAWN)
		{
			// プレイヤー操作
			Controller();
		}

		// カメラ追従
		CCamera *pCamera = CManager::GetInstance()->GetCamera();

		// 追従処理
		pCamera->Pursue(GetPosition(), GetRotation());

		// オンライン送信
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
		CManager::GetInstance()->GetScene()->SendLife(m_nLife);
	}
	else
	{// 操作キャラではない
		D3DXVECTOR3 posDest = m_Info.posDiff - m_Info.pos;
		m_Info.pos += posDest * 0.95f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("向き [%f, %f, %f] : ID [ %d]\n", GetRotation().x, GetRotation().y, GetRotation().z, m_nId);
	CManager::GetInstance()->GetDebugProc()->Print("位置 [%f, %f, %f]", GetPosition().x, GetPosition().y, GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("体力 [ %d ]\n", m_nLife);

	if (m_bGoal)
	{
		CManager::GetInstance()->GetDebugProc()->Print("[ ゴールした ]\n", m_nLife);
	}
	else
	{
		CManager::GetInstance()->GetDebugProc()->Print("[ ゴールしてない ]\n", m_nLife);
	}

	// 死亡確認
	if (m_nLife <= 0 && m_Info.state != STATE_DEATH)
	{
		if (m_pObject == nullptr)
		{
			return;
		}

		m_pObject->SetDraw(false);
		m_pShadow->SetDraw(false);
		m_Info.state = STATE_DEATH;
		m_Info.fStateCounter = DEATH_INTERVAL;

		
	}
	else if (m_nLife > 0 && (m_Info.state != STATE_DEATH && m_Info.state != STATE_APPEAR))
	{// 体力ある
		m_fEffectCount += CManager::GetInstance()->GetSlow()->Get();

		if (m_fEffectCount >= PARTICLE_TIMER)
		{
			m_fEffectCount = 0.0f;
			
		}
	}

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

	// 影の設定
	if (nullptr != m_pShadow) {
		m_pShadow->SetPosition(D3DXVECTOR3(m_Info.pos.x, fHeight + 1.0f, m_Info.pos.z));
	}
}

//===============================================
// 生成
//===============================================
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& move)
{
	CPlayer *pPlayer = NULL;

	// オブジェクト2Dの生成
	pPlayer = new CPlayer;

	if (nullptr != pPlayer)
	{// 生成できた場合
		// 初期化処理
		pPlayer->Init();

		// 座標設定
		pPlayer->SetPosition(pos);

		// 向き設定
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// 移動量設定
		pPlayer->SetMove(move);

		// 種類の設定
		//pPlayer->SetType(TYPE_PLAYER);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pPlayer;
}

//===============================================
// 操作処理
//===============================================
void CPlayer::Controller(void)
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
		RotateCamera();	// カメラ回転
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
		if (CObjectX::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax))
		{
			bDamage = true;
			CManager::GetInstance()->GetDebugProc()->Print("***壁と当たったよ***\n");
			if (nDamage == 0)
			{
				nDamage = 1;
			}
		}
	}

	// ダメージ確認
	if (m_Info.state == STATE_NORMAL)
	{
		if (nDamage >= 0)
		{
			if (bDamage)
			{
				CManager::GetInstance()->GetScene()->SendDamage(nDamage);
				Damage(nDamage);

				if (m_type == TYPE_ACTIVE)
				{
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
				}
			}
		}
	}

	{
		float fIner = INER;
		if (pInputKey->GetPress(DIK_SPACE) == true || pInputPad->GetPress(CInputPad::CInputPad::BUTTON_LEFTBUTTON, m_nId) == true || pInputPad->GetPress(CInputPad::CInputPad::BUTTON_RIGHTBUTTON, m_nId) == true)
		{
			if (pInputKey->GetTrigger(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::CInputPad::BUTTON_LEFTBUTTON, m_nId) == true || pInputPad->GetTrigger(CInputPad::CInputPad::BUTTON_RIGHTBUTTON, m_nId) == true)
			{

			}
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

			CParticle::Create(m_Info.pos, m_Info.move, CEffect::TYPE_SNOWATK, static_cast<int>(fAdd) * 4);
		}

		if (fIner == STOP_INER) {
			m_pObject->GetMotion()->BlendSet(2);
		}
		else if (m_bMove) {
			m_pObject->GetMotion()->BlendSet(1);
		}
		else {
			m_pObject->GetMotion()->Set(0);
		}
	}

	// 壁との当たり判定
	CMeshWall::Collision(pos, m_Info.posOld);

	m_Info.pos = pos;

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n回転[W,A,S,D] : 加速[SPACE] : ステップ[K, (Rボタン)]\n");

	if (m_pObject == nullptr) {
		return;
	}

	if (m_pObject->GetMotion() == nullptr) {
		return;
	}

	if (m_pObject->GetMotion()->GetNowMotion() == 1 && m_pObject->GetMotion()->GetNowFrame() == 0) {

	}
}

//===============================================
// 移動
//===============================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	float fSpeed = MOVE;	// 移動量
	m_bMove = false;

	if (pInputKey->GetPress(DIK_SPACE) || pInputPad->GetPress(CInputPad::BUTTON_LEFTBUTTON, m_nId) || pInputPad->GetPress(CInputPad::CInputPad::BUTTON_RIGHTBUTTON, m_nId))
	{
		fSpeed = 0.0f;
	}

	// 入力装置確認
	if (nullptr == pInputKey){
		return;
	}

	// 入力装置確認
	if (nullptr == pInputPad){
		return;
	}

	if (pInputKey->GetPress(DIK_A) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.8f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_X, 0.8f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(m_nId, CInputPad::BUTTON_LEFT_Y, 0.8f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;
	}
}

//===============================================
// 回転
//===============================================
void CPlayer::Rotation(void)
{
	
}

//===============================================
// 回転
//===============================================
void CPlayer::KeyBoardRotation(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ

	if (nullptr == pInputKey){
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
void CPlayer::Adjust(void)
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
void CPlayer::StateSet(void)
{
	switch (m_Info.state)
	{
	case STATE_APPEAR:

		CManager::GetInstance()->GetDebugProc()->Print("状態 : [無敵]\n");
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}

		break;

	case STATE_NORMAL:

		CManager::GetInstance()->GetDebugProc()->Print("状態 : [通常]\n");

		break;

	case STATE_DAMAGE:

		CManager::GetInstance()->GetDebugProc()->Print("状態 : [ダメージ]\n");

		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;
		}

		break;

	case STATE_DEATH:

		CManager::GetInstance()->GetDebugProc()->Print("状態 : [死亡]\n");

		{
			float fOld = m_Info.fStateCounter;
			m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();
		}

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = SPAWN_INTERVAL;
			m_Info.state = STATE_SPAWN;
			m_pShadow->SetDraw();
			m_pShadow->SetpVtx(0.0f, 0.0f);
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Info.pos.y = -600.0f;
			SetPosition(m_Info.pos);
			m_nLife = START_LIFE;

			if (m_type == TYPE_ACTIVE)
			{
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SPAWN);
			}
		}

		break;

	case STATE_SPAWN:
	{
		m_Info.fStateCounter -= CManager::GetInstance()->GetSlow()->Get();

		m_Info.pos.y += 10.0f;
		SetPosition(m_Info.pos);

		m_pShadow->SetpVtx(m_pShadow->GetWidth() + 1.0f + START_LIFE * 0.25f, m_pShadow->GetHeight() + 1.0f + START_LIFE * 0.25f);
		m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, (float)((float)(SPAWN_INTERVAL - m_Info.fStateCounter) / (float)SPAWN_INTERVAL * SHADOW_ALPHA)));

		if (m_Info.fStateCounter <= 0.0f)
		{

			m_pObject->SetDraw();
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_APPEAR;
			m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
		break;
	}
}

//===============================================
// ダメージ処理
//===============================================
void CPlayer::Damage(int nDamage) 
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
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}
}

//===============================================
// 体力設定
//===============================================
void CPlayer::SetType(TYPE type)
{
	m_type = type;

	
}

//===============================================
// ポリゴン描画
//===============================================
void CPlayer::SetGoal(bool bValue)
{
	bool Old = m_bGoal;
	m_bGoal = bValue;
}

//===============================================
// カメラ操作
//===============================================
void CPlayer::RotateCamera(void)
{
	CManager::GetInstance()->GetCamera()->Rotate();
}