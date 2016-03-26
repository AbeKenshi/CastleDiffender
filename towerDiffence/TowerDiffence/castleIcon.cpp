#include "castleIcon.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
CastleIcon::CastleIcon() : Image()
{
	spriteData.width = castleIconNS::WIDTH;			// 勇者のアイコンのサイズ
	spriteData.height = castleIconNS::HEIGHT;
	spriteData.x = castleIconNS::X;					// 画面上の位置
	spriteData.y = castleIconNS::Y;
	spriteData.rect.bottom = castleIconNS::HEIGHT;		// 画面の一部を選択
	spriteData.rect.right = castleIconNS::WIDTH;
	startFrame = castleIconNS::START_FRAME;
	currentFrame = startFrame;
}

