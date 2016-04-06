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
			spriteData.width = braveAttackCollisionNS::WIDTH;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Boxの衝突判定用
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.x = brave->getCenterX() + brave->getWidth() / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			break;
		case characterNS::UP:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Boxの衝突判定用
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() - brave->getHeight() / 2 - spriteData.height;
			break;
		case characterNS::LEFT:
			spriteData.width = braveAttackCollisionNS::WIDTH;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Boxの衝突判定用
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2 - brave->getWidth();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			break;
		case characterNS::DOWN:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Boxの衝突判定用
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() + 10;
			break;
	}
	collisionTimer = 0.0f;
	//visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}