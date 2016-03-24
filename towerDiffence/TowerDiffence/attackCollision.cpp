#include "attackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
AttackCollision::AttackCollision() : Entity()
{
	active = false;									// 攻撃はアクティブでない状態から開始
	spriteData.width = attackCollisionNS::WIDTH;	// １つの画像のサイズ
	spriteData.height = attackCollisionNS::HEIGHT;
	spriteData.rect.bottom = attackCollisionNS::HEIGHT;
	spriteData.rect.right = attackCollisionNS::WIDTH;
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
void AttackCollision::update(float frameTime)
{
	collisionTimer += frameTime;
	if (collisionTimer >= attackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	if (visible == false)
		return;
	Image::update(frameTime);
}

//==========================================================
// Attack
// 勇者から攻撃を発動
//==========================================================
void AttackCollision::attack(Brave * brave)
{
	switch (brave->getDirection())
	{
		case braveNS::RIGHT:
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::UP:
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = PI / 2;
			break;
		case braveNS::LEFT:
			spriteData.x = brave->getCenterX() - spriteData.width * 3 / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::DOWN:
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = PI / 2;
			break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 炎を表示
	active = true;							// 衝突可能にする
}