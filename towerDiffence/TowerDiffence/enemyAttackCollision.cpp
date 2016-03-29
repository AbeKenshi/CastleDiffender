#include "enemyAttackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
EnemyCollision::EnemyCollision() : Entity()
{
	active = false;									// 攻撃はアクティブでない状態から開始
	spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
	spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
	visible = false;
	// Boxの衝突判定用
	edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void EnemyCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= enemyCollisionNS::COLLISION_TIME)
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
void EnemyCollision::attack(Enemy *enemy)
{
	spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
	spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
	visible = false;
	// Boxの衝突判定用
	edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	switch (enemy->getDirection())
	{
	case characterNS::RIGHT:
		spriteData.x = enemy->getCenterX() + spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth() / 2;
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	case characterNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 2;
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
	setRect();
}

//==========================================================
// Walk
// 雑魚敵が歩くときに発動
//==========================================================
void EnemyCollision::walk(Enemy *enemy)
{
	spriteData.width = enemyCollisionNS::WALK_WIDTH;	// １つの画像のサイズ
	spriteData.height = enemyCollisionNS::WALK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::WALK_HEIGHT;
	spriteData.rect.right = enemyCollisionNS::WALK_WIDTH;
	visible = false;
	// Boxの衝突判定用
	switch (enemy->getGoalDirection())
	{
	case characterNS::RIGHT:
		spriteData.x = enemy->getX() + enemy->getWidth() * enemy->getScale() - 10;
		spriteData.y = enemy->getY() + enemy->getHeight() * enemy->getScale() / 2 + 8;
		edge.left = -enemyCollisionNS::WALK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::WALK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::WALK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::WALK_HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY();
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	case characterNS::LEFT:
		spriteData.x = enemy->getX() + 10;
		spriteData.y = enemy->getY() + enemy->getHeight() * enemy->getScale() / 2;
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY();
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
	setRect();
}