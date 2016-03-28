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
	visible = false;
	// Boxの衝突判定用
	edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
	edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
	edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
	edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
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
	case characterNS::RIGHT:
		spriteData.x = enemy->getCenterX() + spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
		edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth() / 2;
		edge.left = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.right = enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.top = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.bottom = enemyAttackCollisionNS::WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	case characterNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
		edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 2;
		edge.left = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.right = enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.top = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.bottom = enemyAttackCollisionNS::WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}