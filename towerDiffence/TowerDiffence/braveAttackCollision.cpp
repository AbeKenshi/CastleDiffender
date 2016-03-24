#include "braveAttackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
BraveAttackCollision::BraveAttackCollision() : Entity()
{
	active = false;									// 攻撃はアクティブでない状態から開始
	spriteData.width = braveAttackCollisionNS::WIDTH;	// １つの画像のサイズ
	spriteData.height = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.right = braveAttackCollisionNS::WIDTH;
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
void BraveAttackCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= braveAttackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	Image::update(frameTime);
}

//==========================================================
// Attack
// 勇者から攻撃を発動
//==========================================================
void BraveAttackCollision::attack(Brave * brave)
{
	switch (brave->getDirection())
	{
		case braveNS::RIGHT:
			spriteData.x = brave->getCenterX();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::UP:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2 - brave->getWidth();
			spriteData.angle = PI / 2;
			break;
		case braveNS::LEFT:
			spriteData.x = brave->getCenterX() - spriteData.width / 2 - brave->getWidth();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::DOWN:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() + spriteData.height / 16;
			spriteData.angle = PI / 2;
			break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}