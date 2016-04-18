//==========================================================
/// @file
/// @brief    Stageクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _STAGE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _STAGE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"
#include "brave.h"

class Stage
{
private:
	Map map;		// ステージのマップ情報
	int enemyNum;	// 敵の数
	Enemy *enemy;	// 敵の配列
	Brave brave;	// プレイヤー
public:
	// コンストラクタ
	Stage();

	//==========================================================
	// getter
	//==========================================================
	Map& getMap() { return &map; }
	int getEnemyNum() { return enemyNum; }
	Enemy& getEnemy(int index) { return &enemy[index]; }
	Brave& getBrave() { return brave; }
};
#endif