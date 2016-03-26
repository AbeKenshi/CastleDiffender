#include "hpTextImage.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
HpTextImage::HpTextImage() : Image()
{
	spriteData.width = hpTextImageNS::WIDTH;	// テキスト画像のサイズ
	spriteData.height = hpTextImageNS::HEIGHT;
	spriteData.x = hpTextImageNS::X;			// 画面上の初期位置
	spriteData.y = hpTextImageNS::Y;
	spriteData.rect.bottom = hpTextImageNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = hpTextImageNS::WIDTH;
	startFrame = hpTextImageNS::START_FRAME;
	endFrame = startFrame;
	currentFrame = startFrame;
}