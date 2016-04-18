//==========================================================
/// @file
/// @brief    Rectクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _RECT_H              // このファイルが複数の箇所でインクルードされる場合に、
#define _RECT_H              // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

// Rectクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace rectNS
{
	const UINT WIDTH = GAME_WIDTH;						// 矩形の幅（ピクセル単位）
	const UINT HEIGHT = 50;								// 矩形の高さ（ピクセル単位）
	const UINT X = 0;									// 左上隅からの画面位置
	const UINT Y = 0;
	const COLOR_ARGB BACK_COLOR = graphicsNS::BLACK;	// 背景の色
}

// 単純な四角形クラス
class Rect
{
private:
	Graphics    *mGraphics;             // grapicsへのポインタ
	float       mX, mY;                 // rectの位置
	int mWidth, mHeight;				// 幅、高さ（ピクセル単位）
	COLOR_ARGB  mBackColor;             // 背景色(a,r,g,b)
	VertexC mVtx[4];                    // 背景用のvertexデータ
	LP_VERTEXBUFFER mVertexBuffer;      // vertexデータ保存用のバッファ
    bool        mInitialized;           // 初期化に成功した場合、true

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

	// グラフィックスデバイスが消失したときに呼び出される
	void onLostDevice();

	// グラフィックスデバイスがリセットされたときに呼び出される
	void onResetDevice();

	// パラメータリセット
	void reset();
	// setter
	// X位置をセット
	void setX(float nx) { mX = nx; }
	// Y位置をセット
	void setY(float ny) { mY = ny; }
	// 幅をセット
	void setWidth(int w) { mWidth = w; }
	// 高さをセット
	void setHeight(int h) { mHeight = h; }
	// 背景色をセット
	void setBackColor(COLOR_ARGB clr) { mBackColor = clr; }
	
	// getter
	// X位置を戻す
	float getX() { return mX; }
	// Y位置を戻す
	float getY() { return mY; }
};

#endif

