#ifndef _ENEMY_COLLISION_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ENEMY_COLLISION_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "character.h"

namespace enemyCollisionNS
{
	const int ATTACK_WIDTH = 10;				// 画像の幅（各フレーム）
	const int ATTACK_HEIGHT = 32;				// 画像の高さ
	const float COLLISION_TIME = 0.3f;	// 攻撃の当たり判定が出ている時間
}

class EnemyCollision : public Entity
{
private:
	float collisionTimer;				// 攻撃の当たり判定が出ている時間を計測するタイマー
public:
	// コンストラクタ
	EnemyCollision();

	// 継承されたメンバー関数
	void update(float frameTime);

	// 新しいメンバー関数
	void attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction);	// 雑魚敵からの攻撃
};

#endif // !_ATTACK_COLLISION_H
