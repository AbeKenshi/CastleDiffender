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
	visible = false;
	// Boxの衝突判定用
	edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
	edge.right = braveAttackCollisionNS::WIDTH / 2.0;
	edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
	edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
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
		case characterNS::RIGHT:
			spriteData.x = brave->getCenterX() + brave->getWidth() * brave->getScale() / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.angle = 0.0f;
			break;
		case characterNS::UP:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2 - brave->getWidth();
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.angle = PI / 2;
			break;
		case characterNS::LEFT:
			spriteData.x = brave->getCenterX() - spriteData.width / 2 - brave->getWidth();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.angle = 0.0f;
			break;
		case characterNS::DOWN:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() + spriteData.height / 16;
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.angle = PI / 2;
			break;
	}
	collisionTimer = 0.0f;
	visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}