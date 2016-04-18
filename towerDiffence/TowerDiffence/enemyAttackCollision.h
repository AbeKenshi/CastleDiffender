//==========================================================
/// @file
/// @brief    EnemyAttackCollisionクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _ENEMY_COLLISION_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ENEMY_COLLISION_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "character.h"

// EnemyAttackCollisionクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace enemyCollisionNS
{
	const int ATTACK_WIDTH = 10;		// 画像の幅（各フレーム）
	const int ATTACK_HEIGHT = 32;		// 画像の高さ
	const float COLLISION_TIME = 0.3f;	// 攻撃の当たり判定が出ている時間
}

class EnemyCollision : public Entity
{
private:
	float mCollisionTimer;				// 攻撃の当たり判定が出ている時間を計測するタイマー
public:
	// コンストラクタ
	EnemyCollision();

	// 継承されたメンバー関数
	void update(float frameTime);

	// 新しいメンバー関数
	// Attack
	// 敵からの攻撃
	// 指定した位置にこのエンティティをアクティブにして出現させる
	void attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction);
};

#endif // !_ATTACK_COLLISION_H
