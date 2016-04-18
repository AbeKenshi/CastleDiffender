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
	edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
	edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
	edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
	edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
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
	attackEffect.update(frameTime);
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
void BraveAttackCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	attackEffect.attack(centerX, centerY, width, height, direction);
	switch (direction)
	{
		case characterNS::RIGHT:
			spriteData.width = braveAttackCollisionNS::WIDTH;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Boxの衝突判定用
			edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			spriteData.x = centerX + width / 2;
			spriteData.y = centerY - spriteData.height / 2;
			break;
		case characterNS::UP:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Boxの衝突判定用
			edge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			spriteData.x = centerX - spriteData.width / 2;
			spriteData.y = centerY - height / 2 - spriteData.height;
			break;
		case characterNS::LEFT:
			spriteData.width = braveAttackCollisionNS::WIDTH;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Boxの衝突判定用
			edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			spriteData.x = centerX - spriteData.width / 2 - width;
			spriteData.y = centerY - spriteData.height / 2;
			break;
		case characterNS::DOWN:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// １つの画像のサイズ
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Boxの衝突判定用
			edge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			spriteData.x = centerX - spriteData.width / 2;
			spriteData.y = centerY + 10;
			break;
	}
	collisionTimer = 0.0f;
	//visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}