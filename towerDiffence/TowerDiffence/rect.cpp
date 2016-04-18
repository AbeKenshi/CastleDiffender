//==========================================================
/// @file
/// @brief    rect.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "rect.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Rect::Rect()
{
	initialized = false;                // 正常に初期化された場合、trueを設定
	graphics = NULL;
	backColor = rectNS::BACK_COLOR;

	x = rectNS::X;						// 最初の四角形の位置
	y = rectNS::Y;

	width = rectNS::WIDTH;
	height = rectNS::HEIGHT;

	vertexBuffer = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
Rect::~Rect()
{
	onLostDevice();
}

//=============================================================================
// Rectを初期化
//=============================================================================
bool Rect::initialize(Graphics *g)
{
	try {
		graphics = g;                    // グラフィックシステム

		// 左上
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// 右上
		vtx[1].x = x + width;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// 右下
		vtx[2].x = x + width;
		vtx[2].y = y + height;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// 左下
		vtx[3].x = x;
		vtx[3].y = y + height;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

	}
	catch (...) {
		return false;
	}

	initialized = true;
	return true;
}


//=============================================================================
// reset
//=============================================================================
void Rect::reset()
{
	// 左上
	vtx[0].x = x;
	vtx[0].y = y;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = backColor;

	// 右上
	vtx[1].x = x + width;
	vtx[1].y = y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = backColor;

	// 右下
	vtx[2].x = x + width;
	vtx[2].y = y + height;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = backColor;

	// 左下
	vtx[3].x = x;
	vtx[3].y = y + height;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = backColor;

	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

}

//=============================================================================
// 四角形を描画
// 実行前：BeginSceneとEndSceneの内側にする
//=============================================================================
const void Rect::draw()
{
	graphics->drawQuad(vertexBuffer);       // 背景を描画

	graphics->spriteBegin();                // スプライトの描画を開始

	graphics->spriteEnd();                      // スプライトの描画を終了
}

//=============================================================================
// グラフィックスデバイスが消失したときに呼び出される
//=============================================================================
void Rect::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(vertexBuffer);
}

//=============================================================================
// グラフィックスデバイスがリセットされたときに呼び出される
//=============================================================================
void Rect::onResetDevice()
{
	if (!initialized)
		return;
	graphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
}

