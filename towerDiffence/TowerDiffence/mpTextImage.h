#ifndef _MP_TEXT_IMAGE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _MP_TEXT_IMAGE_H		// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"

namespace mpTextImageNS
{
	const int WIDTH = 40;		// 画像の幅（各フレーム）
	const int HEIGHT = 20;		// 画像の高さ
	const int X = 60;			// 初期位置
	const int Y = 30;
	const int TEXTURE_COLS = 5;	// テクスチャは5列
	const int START_FRAME = 20;	// アニメーションはフレーム15から開始
}

class MpTextImage : public Image
{
public:
	// コンストラクタ
	MpTextImage();
};
#endif // !_MP_TEXT_IMAGE_H
