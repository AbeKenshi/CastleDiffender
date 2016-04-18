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
	mSpriteData.width = castleNS::WIDTH;			// １つの画像のサイズ
	mSpriteData.height = castleNS::HEIGHT;
	mSpriteData.rect.bottom = castleNS::HEIGHT;	// 画像内の選択する部分
	mSpriteData.rect.right = castleNS::WIDTH;
	mSpriteData.x = castleNS::X;					// 画面上の位置
	mSpriteData.y = castleNS::Y;
	mCols = castleNS::TEXTURE_COLS;				// テクスチャの列数
	mStartFrame = castleNS::START_FRAME;			// アニメーションの最初のフレーム
	mCurrentFrame = mStartFrame;					// 現在のフレームをアニメーションの最初のフレームにセット
	// Boxの衝突判定用
	mEdge.left = (LONG)(-castleNS::WIDTH / 1.8);
	mEdge.right = (LONG)(castleNS::WIDTH / 1.8);
	mEdge.top = (LONG)(-castleNS::HEIGHT / 1.8);
	mEdge.bottom = (LONG)(castleNS::HEIGHT / 1.8);
	mCollisionType = entityNS::BOX;

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
	if (mVisible == false)
		return;


	// ダメージを受けているなら一定時間ごとにアニメーションを点滅
	if (mIsDamaged)
	{
		// ダメージ時にアニメーション用のタイマーを加算
		mDamageTimer += frameTime;
		mTotalDamageTime += frameTime;
		// 0.15秒ごとに描画フラグを切り替え
		if (mDamageTimer > 0.15f)
		{
			if (mDrawFlag)
				mDrawFlag = false;
			else
				mDrawFlag = true;
			mDamageTimer = 0.0f;
		}
		// DAMAGE_TIME分だけ点滅したら、点滅を終了
		if (mTotalDamageTime > 1.0f)
		{
			mDamageTimer = 0.0f;
			mTotalDamageTime = 0.0f;
			mDrawFlag = true;
			mIsDamaged = false;
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
	if (!mActive)
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
		mHealth -= enemyAttackDamage * mDamagePer;
		// ダメージ状態のフラグをオン
		mIsDamaged = true;
		break;
	case MIDBOSS_ATTACK:		// 中ボスの攻撃
		// 一定ダメージを受ける
		mHealth -= midBossAttackDamage * mDamagePer;
		// ダメージ状態のフラグをオン
		mIsDamaged = true;
		break;
	default:
		break;
	}
	// 体力が0以下になったなら、死亡
	if (mHealth <= 0)
		death = true;
}