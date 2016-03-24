#include "enemyAttackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
EnemyAttackCollision::EnemyAttackCollision() : Entity()
{
	active = false;									// 攻撃はアクティブでない状態から開始
	spriteData.width = enemyAttackCollisionNS::WIDTH;	// １つの画像のサイズ
	spriteData.height = enemyAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = enemyAttackCollisionNS::HEIGHT;
	spriteData.rect.right = enemyAttackCollisionNS::WIDTH;
	radius = 4;										// 円の衝突判定用
	visible = false;
	collisionType = entityNS::CIRCLE;
	collisionTimer = 0.0f;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void EnemyAttackCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= enemyAttackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	Image::update(frameTime);
}

//==========================================================
// Attack
// 雑魚敵から攻撃を発動
//==========================================================
void EnemyAttackCollision::attack(Enemy *enemy)
{
	switch (enemy->getDirection())
	{
	case enemyNS::RIGHT:
		spriteData.x = enemy->getCenterX() + spriteData.width / 2;
		spriteData.y = enemy->getCenterY();
		spriteData.angle = 0.0f;
		break;
	case enemyNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth() / 2;
		spriteData.angle = PI / 2;
		break;
	case enemyNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY();
		spriteData.angle = 0.0f;
		break;
	case enemyNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 2;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}