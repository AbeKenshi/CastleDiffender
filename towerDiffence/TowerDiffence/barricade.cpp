//==========================================================
/// @file
/// @brief    barricade.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#include "barricade.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
Barricade::Barricade() : Entity()
{
	spriteData.width = barricadeNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = barricadeNS::HEIGHT;
	spriteData.rect.bottom = barricadeNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = barricadeNS::WIDTH;
	cols = barricadeNS::TEXTURE_COLS;				// テクスチャの列数
	startFrame = barricadeNS::START_FRAME;			// アニメーションの最初のフレーム
	endFrame = barricadeNS::END_FRAME;				// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
	// Boxの衝突判定用
	edge.left = (LONG)(-barricadeNS::WIDTH / 2.0);
	edge.right = (LONG)(barricadeNS::WIDTH / 2.0);
	edge.top = (LONG)(-barricadeNS::HEIGHT / 2.0);
	edge.bottom = (LONG)(barricadeNS::HEIGHT / 2.0);
	collisionType = entityNS::BOX;
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void Barricade::update(float frameTime)
{
	// 非アクティブな場合、何もしない
	if (active == false)
		return;

	// 残り体力ごとに、アニメーションを分岐
	// 境界を残り体力が上下した場合、アニメーションを遷移させる
	if ((currentFrame == barricadeNS::START_FRAME && health < 66) || (currentFrame == barricadeNS::START_FRAME + 1 && health < 33))
	{
		// 体力が境界を下回った場合、アニメーションを進める
		setCurrentFrame(currentFrame + 1);
	}
	if ((currentFrame == barricadeNS::END_FRAME && health >= 33) || (currentFrame == barricadeNS::START_FRAME + 1 && health >= 66))
	{
		// 体力が境界を上回った場合、アニメーションを戻す
		setCurrentFrame(currentFrame - 1);
	}
	// 攻撃がヒットしたときのアニメーションを更新
	hitEffect.update(frameTime);
	// アニメーション以外を更新
	updateWithoutImage(frameTime);
	
}

//==========================================================
// ダメージ処理
// WEAPONの種類によって受けるダメージが分岐
//==========================================================
void Barricade::damage(WEAPON weapon)
{
	// 非アクティブな場合、ダメージは受けない
	if (!active)
		return;
	
	// WEAPONによってダメージを分岐
	switch (weapon)
	{
	case FIRE:					// 炎（プレイヤーの必殺技）
		// 変化なし
		break;
	case BRAVE_ATTACK:			// プレイヤーの攻撃
	case BRAVE_SECOND_ATTACK:	// プレイヤーの攻撃
		// バリケードを回復
		health += 20;
		// MAX100を超えた場合は100にする
		if (health > 100)
		{
			health = 100;
		}
		// 攻撃がヒットしたときのアニメーションを発動
		hitEffect.hit(getCenterX(), getCenterY());
		break;
	case ENEMY_ATTACK:
		// バリケードにダメージ
		health -= 10 * damagePer;
		// 攻撃がヒットしたときのアニメーションを発動
		hitEffect.hit(getCenterX(), getCenterY());
		// 残り体力がなくなった場合、
		if (health <= 0)
		{
			// 自身と攻撃がヒットしたときのアニメーションを非アクティブにする
			visible = false;
			active = false;
			hitEffect.setVisible(false);
		}
		break;
	case MIDBOSS_ATTACK:
		// バリケードにダメージ
		health -= 20 * damagePer;
		// 攻撃がヒットしたときのアニメーションを発動
		hitEffect.hit(getCenterX(), getCenterY());
		// 残り体力がなくなった場合、
		if (health <= 0)
		{
			// 自身と攻撃がヒットしたときのアニメーションを非アクティブにする
			visible = false;
			active = false;
			hitEffect.setVisible(false);
		}
		break;
	default:
		break;
	}
}