//==========================================================
/// @file
/// @brief    enemyAttackCollision.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "enemyAttackCollision.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
EnemyCollision::EnemyCollision() : Entity()
{
	active = false;												// 攻撃はアクティブでない状態から開始
	visible = false;
	spriteData.width = enemyCollisionNS::ATTACK_WIDTH;			// １つの画像のサイズ
	spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
	// Boxの衝突判定用
	edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
	edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
	edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
	edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;										// 攻撃の当たり判定が出ている時間を計測するタイマー
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void EnemyCollision::update(float frameTime)
{
	// 非アクティブなら、このエンティティの更新はしない
	if (visible == false)
		return;
	// 攻撃の当たり判定が出ている時間を加算
	collisionTimer += frameTime;
	// 攻撃の当たり判定が一定以上出ているなら、このエンティティを非アクティブにする
	if (collisionTimer >= enemyCollisionNS::COLLISION_TIME)
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
// 敵から攻撃を発動
// 指定した位置にこのエンティティをアクティブにして出現させる
//==========================================================
void EnemyCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	// 敵の向きによって出現位置を分岐
	// 敵の画像に偏りがあるため、若干位置を修正している
	switch (direction)
	{
	case characterNS::RIGHT:	// 右
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Boxの衝突判定用
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		spriteData.x = centerX + width / 2;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::UP:		// 上
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Boxの衝突判定用
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY - height / 2 - spriteData.height - 10;
		break;
	case characterNS::LEFT:		// 左
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Boxの衝突判定用
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		spriteData.x = centerX - width / 2 - spriteData.width;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::DOWN:		// 下
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// １つの画像のサイズ
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Boxの衝突判定用
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY + height / 2;
		break;
	}
	// 攻撃の当たり判定が出ている時間をリセット
	collisionTimer = 0.0f;
	//visible = true;							// 攻撃を表示
	active = true;							// 衝突可能にする
}