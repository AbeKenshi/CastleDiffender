//==========================================================
/// @file
/// @brief    hpTextImage.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "hpTextImage.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
HpTextImage::HpTextImage() : Image()
{
	spriteData.width = hpTextImageNS::WIDTH;		// テキスト画像のサイズ
	spriteData.height = hpTextImageNS::HEIGHT;
	spriteData.x = hpTextImageNS::X;				// 画面上の初期位置
	spriteData.y = hpTextImageNS::Y;
	spriteData.rect.bottom = hpTextImageNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = hpTextImageNS::WIDTH;
	startFrame = hpTextImageNS::START_FRAME;		// アニメーションの最初のフレーム
	endFrame = startFrame;							// アニメーションの最後のフレーム
	currentFrame = startFrame;						// 現在のフレームはアニメーションの最初のフレームにセット
}