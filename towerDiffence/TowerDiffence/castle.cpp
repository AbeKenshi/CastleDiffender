//==========================================================
/// @file
/// @brief    castle.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "castle.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Castle::Castle() : Entity()
{
	spriteData.width = castleNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = castleNS::HEIGHT;
	spriteData.rect.bottom = castleNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = castleNS::WIDTH;
	spriteData.x = castleNS::X;					// 画面上の位置
	spriteData.y = castleNS::Y;
	cols = castleNS::TEXTURE_COLS;				// テクスチャの列数
	startFrame = castleNS::START_FRAME;			// アニメーションの最初のフレーム
	currentFrame = startFrame;					// 現在のフレームをアニメーションの最初のフレームにセット
	// Boxの衝突判定用
	edge.left = (LONG)(-castleNS::WIDTH / 1.8);
	edge.right = (LONG)(castleNS::WIDTH / 1.8);
	edge.top = (LONG)(-castleNS::HEIGHT / 1.8);
	edge.bottom = (LONG)(castleNS::HEIGHT / 1.8);
	collisionType = entityNS::BOX;

	death = false;								// 死亡していない状態からスタート
}

//==========================================================
// パラメータ初期化
//==========================================================
void Castle::reset()
{
	death = false;								// 死亡していない状態にリセット
	// エンティティをリセット
	Entity::reset();
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションを制御するために使用
//==========================================================
void Castle::update(float frameTime)
{
	// 非アクティブなら、何もしない
	if (visible == false)
		return;


	// ダメージを受けているなら一定時間ごとにアニメーションを点滅
	if (isDamaged)
	{
		// ダメージ時にアニメーション用のタイマーを加算
		damageTimer += frameTime;
		totalDamageTime += frameTime;
		// 0.15秒ごとに描画フラグを切り替え
		if (damageTimer > 0.15f)
		{
			if (drawFlag)
				drawFlag = false;
			else
				drawFlag = true;
			damageTimer = 0.0f;
		}
		// DAMAGE_TIME分だけ点滅したら、点滅を終了
		if (totalDamageTime > 1.0f)
		{
			damageTimer = 0.0f;
			totalDamageTime = 0.0f;
			drawFlag = true;
			isDamaged = false;
		}
	}
	// エンティティを更新
	Entity::update(frameTime);
}

//==========================================================
// ダメージ処理
// WEAPONの種類によって受けるダメージが分岐
//==========================================================
void Castle::damage(WEAPON weapon)
{
	// 非アクティブな場合、ダメージは受けない
	if (!active)
		return;

	// WEAPONによってダメージを分岐
	switch (weapon)
	{
	case FIRE:					// 炎
		break;
	case BRAVE_ATTACK:			// 勇者の攻撃
		break;
	case BRAVE_SECOND_ATTACK:	// 勇者の第二撃
		break;
	case ENEMY_ATTACK:			// 雑魚敵の攻撃
		// 一定ダメージを受ける
		health -= enemyAttackDamage * damagePer;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	case MIDBOSS_ATTACK:		// 中ボスの攻撃
		// 一定ダメージを受ける
		health -= midBossAttackDamage * damagePer;
		// ダメージ状態のフラグをオン
		isDamaged = true;
		break;
	default:
		break;
	}
	// 体力が0以下になったなら、死亡
	if (health <= 0)
		death = true;
}