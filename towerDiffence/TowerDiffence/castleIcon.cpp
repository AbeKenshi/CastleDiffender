//==========================================================
/// @file
/// @brief    castleIcon.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "castleIcon.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
CastleIcon::CastleIcon() : Image()
{
	mSpriteData.width = castleIconNS::WIDTH;			// 城のアイコンのサイズ
	mSpriteData.height = castleIconNS::HEIGHT;
	mSpriteData.x = castleIconNS::X;					// 画面上の位置
	mSpriteData.y = castleIconNS::Y;
	mSpriteData.rect.bottom = castleIconNS::HEIGHT;	// 画面の一部を選択
	mSpriteData.rect.right = castleIconNS::WIDTH;
	mStartFrame = castleIconNS::START_FRAME;			// アニメーションの最初のフレーム
	mCurrentFrame = mStartFrame;						// 現在のフレームをアニメーションの最初のフレームにセット
}

