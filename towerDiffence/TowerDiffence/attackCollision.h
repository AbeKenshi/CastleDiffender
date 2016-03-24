#ifndef _ATTACK_COLLISION_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ATTACK_COLLISION_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "brave.h"

namespace attackCollisionNS
{
	const int WIDTH = 48;				// 画像の幅（各フレーム）
	const int HEIGHT = 96;				// 画像の高さ
	const int COLLISION_RADIUS = 4;		// 円の衝突判定
	const float COLLISION_TIME = 0.5f;	// 攻撃の当たり判定が出ている時間
}

class AttackCollision : public Entity
{
private:
	float collisionTimer;				// 攻撃の当たり判定が出ている時間を計測するタイマー
public:
	// コンストラクタ
	AttackCollision();

	// 継承されたメンバー関数
	void update(float frameTime);

	// 新しいメンバー関数
	void attack(Brave *brave);	// 勇者からの攻撃
};

#endif // !_ATTACK_COLLISION_H
