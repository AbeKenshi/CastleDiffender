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
	spriteData.width = castleIconNS::WIDTH;			// 城のアイコンのサイズ
	spriteData.height = castleIconNS::HEIGHT;
	spriteData.x = castleIconNS::X;					// 画面上の位置
	spriteData.y = castleIconNS::Y;
	spriteData.rect.bottom = castleIconNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = castleIconNS::WIDTH;
	startFrame = castleIconNS::START_FRAME;			// アニメーションの最初のフレーム
	currentFrame = startFrame;						// 現在のフレームをアニメーションの最初のフレームにセット
}

