//==========================================================
/// @file
/// @brief    textDX.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "textDX.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
TextDX::TextDX()
{
    color = SETCOLOR_ARGB(255,255,255,255); // default to white font

    // set font position
    fontRect.top = 0;
    fontRect.left = 0;
    fontRect.right = GAME_WIDTH;
    fontRect.bottom = GAME_HEIGHT;
    dxFont = NULL;
    angle  = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
TextDX::~TextDX()
{
    SAFE_RELEASE(dxFont);
}

//=============================================================================
// DirectXフォントを作成
//=============================================================================
bool TextDX::initialize(Graphics *g, int height, bool bold, bool italic, 
                        const std::string &fontName)
{
    graphics = g;                   // グラフィックシステム

    UINT weight = FW_NORMAL;
    if(bold)
        weight = FW_BOLD;

	// DirectXフォントを作成
    if(FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(),
        &dxFont))) return false;

    // 変換行列を初期化
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

    return true;
}

//=============================================================================
// テキストをx、yに出力
// 失敗時には0を、成功時にはテキストの高さを戻す
// 実行前：spriteBegin()
// 実行後：spriteEnd()
//=============================================================================
int TextDX::print(const std::string &str, int x, int y)
{
    if(dxFont == NULL)
        return 0;
	// フォント位置を設定
    fontRect.top = y;
    fontRect.left = x;

	// 回転中心
    D3DXVECTOR2 rCenter=D3DXVECTOR2((float)x,(float)y);
    // テキストを特定の角度で回転する行列を準備
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);
    // 行列をスプライトに適用
    graphics->getSprite()->SetTransform(&matrix);
    return dxFont->DrawTextA(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_LEFT, color);
}

//=============================================================================
// DirectXテキスト書式を使って、RECT内にテキストを出力
// 失敗時には0を、成功時にはテキストの高さを戻す
// 実行前：spriteBegin()
// 実行後：spriteEnd()
//=============================================================================
int TextDX::print(const std::string &str, RECT &rect, UINT format)
{
    if(dxFont == NULL)
        return 0;

	// テキストを回転させない行列を準備
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, NULL, NULL);
	// 行列をスプライトに適用
    graphics->getSprite()->SetTransform(&matrix);
    return dxFont->DrawTextA(graphics->getSprite(), str.c_str(), -1, &rect, format, color);
}

//=============================================================================
// グラフィックスデバイスが消失したときに呼び出される
//=============================================================================
void TextDX::onLostDevice()
{
    if(dxFont == NULL)
        return;
    dxFont->OnLostDevice();
}

//=============================================================================
// グラフィックスデバイスがリセットされたときに呼び出される
//=============================================================================
void TextDX::onResetDevice()
{
    if(dxFont == NULL)
        return;
    dxFont->OnResetDevice();
}
