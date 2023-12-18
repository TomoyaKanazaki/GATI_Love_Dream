//========================================
//
//シューティングアクション[number.h]
//Author：森川駿弥
//
//========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//========================================
//ナンバークラス
//========================================
class CNumber : public CObject2D
{
public:
	CNumber();		//コンストラクタ
	~CNumber();		//デストラクタ

	//メンバ関数
	static CNumber *Create(void);	//プレイヤー生成
};

#endif