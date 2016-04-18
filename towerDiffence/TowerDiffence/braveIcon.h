//==========================================================
/// @file
/// @brief    BraveIconクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _BRAVE_ICON_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _BRAVE_ICON_H		// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"
#include "brave.h"

// BraveIconクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace braveIconNS
{
	const int WIDTH = 48;			// 画像の幅（各フレーム）
	const int HEIGHT = 48;			// 画像の高さ
	const int X = 10;				// 初期位置
	const int Y = 0;
	const int TEXTURE_COLS = 4;		// テクスチャは4列
	const int START_FRAME = 0;		// アニメーションはフレーム0から開始
	const int END_FRAME = 3;		// アニメーションフレームは0、1、2、3
}

class BraveIcon : public Image
{
private:
	Brave *mBrave;	// 勇者へのポインタ。オブジェクトはこのクラス外で生成されるのでデストラクタは必要ない。
public:
	// コンストラクタ
	BraveIcon();

	// 継承されたメンバー関数
	// update
	void update(float frameTime);
	// パラメータリセット
	// roundStart()内で呼び出される
	void reset();
	
	// 新しいメンバー関数
	// Entityオブジェクトとリンクさせる。
	// initialize関数の直後に呼び出す。
	void linkEntity(Brave& brv) { mBrave = &(brv); }
};
#endif // !_BRAVE_ICON_H
