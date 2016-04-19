//==========================================================
/// @file
/// @brief    CastleIconクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _CASTLE_ICON_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _CASTLE_ICON_H		// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"

// CastleIconクラスの定数
// ゲーム内でのステータス以外をここに記述
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
