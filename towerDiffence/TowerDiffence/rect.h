// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// console.h v1.0

#ifndef _RECT_H              // Prevent multiple definitions if this 
#define _RECT_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

namespace rectNS
{
	const UINT WIDTH = GAME_WIDTH;     // 矩形の幅（ピクセル単位）
	const UINT HEIGHT = 50;            // 矩形の高さ（ピクセル単位）
	const UINT X = 0;                  // 左上隅からの画面位置
	const UINT Y = 0;
	const COLOR_ARGB BACK_COLOR = graphicsNS::BLACK;
}

// 単純な四角形クラス
class Rect
{
private:
	Graphics    *graphics;              // graphics system
	float       x, y;                   // console location (dynamic)
	int width, height;					// 幅、高さ（ピクセル単位）
	COLOR_ARGB  backColor;              // background color (a,r,g,b)
	VertexC vtx[4];                     // vertex data for background
	LP_VERTEXBUFFER vertexBuffer;       // buffer to hold vertex data
	bool        initialized;            // true when initialized successfully

public:
	// コンストラクタ
	Rect();

	// デストラクタ
	virtual ~Rect();

	// Rectの初期化
	bool initialize(Graphics *g);

	// 四角形を描画
	// 実行前：BeginSceneとEndSceneの内側にする
	const void draw();

	// Call when graphics device is lost.
	void onLostDevice();

	// Call when graphics device is reset.
	void onResetDevice();

	void reset();
	// setter
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }

	// getter
	float getX() { return x; }
	float getY() { return y; }
	// 背景色をセット
	void setBackColor(COLOR_ARGB clr) { backColor = clr; }
};

#endif

