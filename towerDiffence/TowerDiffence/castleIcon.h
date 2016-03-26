#ifndef _CASTLE_ICON_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _CASTLE_ICON_H		// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"

namespace castleIconNS
{
	const int WIDTH = 48;			// 画像の幅（各フレーム）
	const int HEIGHT = 48;			// 画像の高さ
	const int X = 780;				// 初期位置
	const int Y = 0;
	const int TEXTURE_COLS = 1;		// テクスチャは1列
	const int START_FRAME = 1;		// アニメーションはフレーム1から開始
}

class CastleIcon : public Image
{
public:
	// コンストラクタ
	CastleIcon();
};
#endif // !_BRAVE_ICON_H
