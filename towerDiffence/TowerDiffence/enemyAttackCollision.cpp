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
void EnemyCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	switch (direction)
	{
	case characterNS::RIGHT:
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Boxの衝突判定用
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.x = centerX + width / 2;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::UP:
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Boxの衝突判定用
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY - height / 2 - spriteData.height - 10;
		break;
	case characterNS::LEFT:
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Boxの衝突判定用
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.x = centerX - width / 2 - spriteData.width;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::DOWN:
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Boxの衝突判定用
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY + height / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
	setRect();
}