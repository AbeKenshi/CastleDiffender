//==========================================================
/// @file
/// @brief    BraveAttackCollisionクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _ATTACK_COLLISION_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _ATTACK_COLLISION_H		// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "attackEffect.h"

// BraveAttackCollisionクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace braveAttackCollisionNS
{
	const int WIDTH = 24;				// 画像の幅（各フレーム）
	const int HEIGHT = 96;				// 画像の高さ
	const float COLLISION_TIME = 0.3f;	// 攻撃の当たり判定が出ている時間
}

class BraveAttackCollision : public Entity
{
private:
	float collisionTimer;			// 攻撃の当たり判定が出ている時間を計測するタイマー
	AttackEffect attackEffect;		// 攻撃の衝撃派
public:
	// コンストラクタ
	BraveAttackCollision();

	// 継承されたメンバー関数
	void update(float frameTime);

	// 新しいメンバー関数
	// Attack
	// 勇者から攻撃を発動
	// 指定した位置にこのエンティティをアクティブにして出現させる
	void attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction);

	//==========================================================
	// getter
	//==========================================================
	// 攻撃の衝撃派の画像を戻す
	AttackEffect& getAttackEffect() { return attackEffect; }
};

#endif // !_ATTACK_COLLISION_H
