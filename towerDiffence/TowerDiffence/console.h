//==========================================================
/// @file
/// @brief    Consoleクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _CONSOLE_H              // このファイルが複数の箇所でインクルードされる場合に、
#define _CONSOLE_H              // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <deque>
#include "constants.h"
#include "textDX.h"
#include "graphics.h"
#include "input.h"

namespace consoleNS
{
    const UINT WIDTH = 1000;										// コンソールの矩形の幅（ピクセル単位）
    const UINT HEIGHT = 400;										// コンソールの矩形の高さ（ピクセル単位）
    const UINT X = 5;												// コンソールの左上隅からの画面位置
    const UINT Y = 5;
    const UINT MARGIN = 4;											// コンソールの端からテキストまでの余白
    const char FONT[] = "Courier New";								// コンソールのテキストに使用するフォント
    const int FONT_HEIGHT = 14;										// コンソールのフォントの高さ
    const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;				// コンソールのフォントの色
    const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192,128,128,128);   // コンソールの背景の色
    const int MAX_LINES = 256;										// テキストバッファ内の表示可能なテキストの最大行数
}

// 
class Console
{
private:
    Graphics    *graphics;              // グラフィックシステムへのポインタ
    Input       *input;                 // 入力システムへのポインタ
    TextDX      dxFont;                 // DirectXフォント
    float       x,y;                    // コンソールの位置
    int         rows;                   // コンソールに収まるテキストの行数
    std::string commandStr;             // コンソールコマンド
    std::string inputStr;               // コンソールへの入力テキスト
    std::deque<std::string> text;       // デックtext
    RECT        textRect;               // テキスト表示rect
    COLOR_ARGB  fontColor;              // フォントカラー(a,r,g,b)
    COLOR_ARGB  backColor;              // 背景色(a,r,g,b)
    VertexC vtx[4];                     // 背景用のvertexデータ
    LP_VERTEXBUFFER vertexBuffer;       // vertexデータ保存用のバッファ
    int         scrollAmount;           // スクロールされている行数
    bool        initialized;            // 初期化に成功した場合、true
    bool        visible;                // コンソールを表示させる場合、true

public:
	// コンストラクタ
    Console();

	// デストラクタ
    virtual ~Console();

	// コンソールを初期化
    bool initialize(Graphics *g, Input *in);

	// コンソールを描画
	// 実行前：BeginSceneとEndSceneの内側にする
    const void draw();

	// コンソールの表示/非表示を制御するプロパティを反転させます。
	// 表示されているコンソールは非表示になり、
	// 非表示のコンソールは表示されるようになります。
    void showHide();

	// 表示/非表示を制御するプロパティの現在の状態を戻します。
    bool getVisible() {return visible;}

	// コンソールを表示します。
    void show() {visible = true;}

	// コンソールを非表示にします。
    void hide() {visible = false;}

	// コンソールディスプレイにテキスト文字列を追加します。
    void print(const std::string &str);

	// シングルキーのコンソールコマンドを処理します。
	// ユーザーが入力したコマンド文字列を戻します。
    std::string getCommand();

	// コンソールの入力テキストを戻します
    std::string getInput() {return inputStr;}

	// コンソールの入力テキストをクリアします
    void clearInput()   {inputStr = "";}

	// グラフィックスデバイスが消失したときに呼び出される
    void onLostDevice();

	// グラフィックスデバイスがリセットされたときに呼び出される
    void onResetDevice();
};

#endif

