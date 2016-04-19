//==========================================================
/// @file
/// @brief    mpTextImage.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "MpTextImage.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
MpTextImage::MpTextImage() : Image()
{
	mSpriteData.width = mpTextImageNS::WIDTH;		// テキスト画像のサイズ
	mSpriteData.height = mpTextImageNS::HEIGHT;
	mSpriteData.x = mpTextImageNS::X;				// 画面上の初期位置
	mSpriteData.y = mpTextImageNS::Y;
	mSpriteData.rect.bottom = mpTextImageNS::HEIGHT;	// 画面の一部を選択
	mSpriteData.rect.right = mpTextImageNS::WIDTH;
	mStartFrame = mpTextImageNS::START_FRAME;		// アニメーションの最初のフレーム	
	mEndFrame = mStartFrame;							// アニメーションの最後のフレーム
	mCurrentFrame = mStartFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
}