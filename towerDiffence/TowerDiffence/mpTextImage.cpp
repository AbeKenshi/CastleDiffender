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
	spriteData.width = mpTextImageNS::WIDTH;		// テキスト画像のサイズ
	spriteData.height = mpTextImageNS::HEIGHT;
	spriteData.x = mpTextImageNS::X;				// 画面上の初期位置
	spriteData.y = mpTextImageNS::Y;
	spriteData.rect.bottom = mpTextImageNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = mpTextImageNS::WIDTH;
	startFrame = mpTextImageNS::START_FRAME;		// アニメーションの最初のフレーム	
	endFrame = startFrame;							// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームに設定
}