#include "MpTextImage.h"

//==========================================================
// デフォルトコンストラクタ
//==========================================================
MpTextImage::MpTextImage() : Image()
{
	spriteData.width = mpTextImageNS::WIDTH;	// テキスト画像のサイズ
	spriteData.height = mpTextImageNS::HEIGHT;
	spriteData.x = mpTextImageNS::X;			// 画面上の初期位置
	spriteData.y = mpTextImageNS::Y;
	spriteData.rect.bottom = mpTextImageNS::HEIGHT;	// 画面の一部を選択
	spriteData.rect.right = mpTextImageNS::WIDTH;
	startFrame = mpTextImageNS::START_FRAME;
	endFrame = startFrame;
	currentFrame = startFrame;
}