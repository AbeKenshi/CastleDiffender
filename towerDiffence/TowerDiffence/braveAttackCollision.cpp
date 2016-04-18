//==========================================================
/// @file
/// @brief    braveAttackCollision.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "braveAttackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
BraveAttackCollision::BraveAttackCollision() : Entity()
{
	active = false;												// 攻撃はアクティブでない状態から開始
	visible = false;
	spriteData.width = braveAttackCollisionNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = braveAttackCollisionNS::WIDTH;
	// Boxの衝突判定用
	edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
	edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
	edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
	edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;										// 攻撃の当たり判定が出ている時間を計測するタイマー
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void BraveAttackCollision::update(float frameTime)
{
	// 攻撃の衝撃派を更新
	attackEffect.update(frameTime);
	// 非アクティブなら、このエンティティの更新はしない
	if (visible == false)
		return;
	// 攻撃の当たり判定が出ている時間を加算
	collisionTimer += frameTime;
	// 攻撃の当たり判定が一定以上出ているなら、このエンティティを非アクティブにする
	if (collisionTimer >= braveAttackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	// エンティティを更新
	Entity::update(frameTime);
}

//==========================================================
// Attack
// 勇者から攻撃を発動
// 指定した位置にこのエンティティをアクティブにして出現させる
//==========================================================
void BraveAttackCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	// 攻撃の衝撃派のアニメーションを表示
	attackEffect.attack(centerX, centerY, width, height, direction);
	// 勇者の向きによって出現位置を分岐
	// 勇者の画像に偏りがあるため、若干位置を修正している
	switch (direction)
	{
		case characterNS::RIGHT:	// 右
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
		case characterNS::UP:		// 上
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
		case characterNS::LEFT:		// 左
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
		case characterNS::DOWN:		// 下
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
	// 攻撃の当たり判定が出ている時間をリセット
	collisionTimer = 0.0f;
	visible = true;						// 攻撃を表示
	active = true;							// 衝突可能にする
}