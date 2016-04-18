//==========================================================
/// @file
/// @brief    hitEffect.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "hitEffect.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
HitEffect::HitEffect() : Image()
{
	visible = false;								// 非表示がデフォルト
	spriteData.width = hitEffectNS::WIDTH;			// １つの画像のサイズ
	spriteData.height = hitEffectNS::HEIGHT;
	spriteData.rect.bottom = hitEffectNS::HEIGHT;	// 画像内の選択する部分
	spriteData.rect.right = hitEffectNS::WIDTH;
	cols = hitEffectNS::TEXTURE_COLS;				// テクスチャの列数
	frameDelay = hitEffectNS::ANIMATION_DELAY;		// アニメーションの各フレームの間隔
	startFrame = hitEffectNS::START_FRAME;			// アニメーションの最初のフレーム
	endFrame = hitEffectNS::END_FRAME;				// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
	setScale(0.5);									// スケール
	loop = false;									// アニメーションはループさせない
}

//==========================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void HitEffect::update(float frameTime)
{
	// 非表示時には何もしない
	if (visible == false)
		return;
	// 画像を更新
	Image::update(frameTime);
	// アニメーションが終了した場合、非表示にする
	if (animComplete)
		visible = false;
}

//==========================================================
// Hit
// この関数が呼ばれると攻撃がヒットしたときのエフェクトが発動
//==========================================================
void HitEffect::hit(float x, float y)
{
	// 指定された座標の四方にランダムに表示
	spriteData.x = x - spriteData.width * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	spriteData.y = y - spriteData.height * spriteData.scale / 2.0f + (rand() % 2) * 20 - 10;
	visible = true;
	setCurrentFrame(startFrame);
}