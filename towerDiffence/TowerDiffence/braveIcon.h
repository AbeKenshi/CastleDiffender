#ifndef _BRAVE_ICON_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _BRAVE_ICON_H		// 多重に定義されることを防ぎます。

#include "image.h"
#include "constants.h"
#include "brave.h"

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
	Brave *brave;	// 勇者へのポインタ。オブジェクトはこのクラス外で生成されるのでデストラクタは必要ない。
public:
	// コンストラクタ
	BraveIcon();

	// 継承されたメンバー関数
	void update(float frameTime);
	
	// 新しいメンバー関数
	// Entityオブジェクトとリンクさせる。
	// initialize関数の直後に呼び出す。
	void linkEntity(Brave* brv) { brave = brv; }
};
#endif // !_BRAVE_ICON_H
