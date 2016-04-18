//==========================================================
/// @file
/// @brief    braveIcon.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
#include "braveIcon.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
BraveIcon::BraveIcon() : Image()
{
	spriteData.width = braveIconNS::WIDTH;			// 勇者のアイコンのサイズ
	spriteData.height = braveIconNS::HEIGHT;
	spriteData.x = braveIconNS::X;					// 画面上の位置
	spriteData.y = braveIconNS::Y;
	spriteData.rect.bottom = braveIconNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = braveIconNS::WIDTH;
	startFrame = braveIconNS::START_FRAME;			// アニメーションの最初のフレーム
	endFrame = braveIconNS::END_FRAME;				// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
}

//=============================================================================
// Update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
// プレイヤーの体力に応じて、アニメーションを分岐
//=============================================================================	
void BraveIcon::update(float frameTime)
{
	// プレイヤーの体力に応じて、アニメーションを分岐
	if (currentFrame == startFrame && brave->getHealth() < 75)
		setCurrentFrame(startFrame + 1);
	if (currentFrame == startFrame + 1 && brave->getHealth() < 50)
		setCurrentFrame(startFrame + 2);
	if (currentFrame == startFrame + 2 && brave->getHealth() < 25)
		setCurrentFrame(startFrame + 3);
}

//==========================================================
// パラメータリセット
//==========================================================
void BraveIcon::reset()
{
	// 現在のフレームはアニメーションの最初のフレームに設定
	setCurrentFrame(startFrame);
}
