//==========================================================
/// @file
/// @brief    Textクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _TEXT_H                 // このファイルが複数の箇所でインクルードされる場合に、
#define _TEXT_H                 // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

class Text;

#include <string>
#include "image.h"
#include "constants.h"

// Textクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace textNS
{
	enum Alignment { LEFT, RIGHT, CENTER, CENTER_MIDDLE, CENTER_BOTTOM, LEFT_BOTTOM, RIGHT_BOTTOM };	// アラインメント（左端、右端、中央上、中央、中央下、左下、右下）
	// フォントデータ構造体
	struct FontData
	{
		UINT left;	// 左位置
		UINT right;	// 右位置
	};
	// フォントの高さは62、幅は48ピクセル
	const int FONT_BORDER = 3;      // 右と下に1ピクセル幅の透明な境界＋可視セル境界
	const int FONT_WIDTH = 48;		// フォントは48ピクセルの幅
	const int FONT_HEIGHT = 62;     // フォントは62ピクセルの高さ
	const int GRID_WIDTH = FONT_WIDTH + FONT_BORDER;	// 実質的なフォントの幅
	const int GRID_HEIGHT = FONT_HEIGHT + FONT_BORDER;	// 実質的なフォントの高さ
	const int COLUMNS = 16;         // フォントの画像の行数
	const int ROWS = 14;            // フォントの画像の列数
	const int FRAMES = 1;           // アニメーションのフレーム数（1 = アニメーションなし）
	const double ANIM_DELAY = 0.0;  // アニメーションのフレーム間の時間
	const int MAX_FONT_HEIGHT = 1000;	// 最大のフォントの高さ
	const int MIN_CHAR = 0x0020;    // 最小文字コード
	const int MAX_CHAR = 0x00FF;    // 最大文字コード
	const int PROPORTIONAL_SPACING = 5; // プロポーショナルフォントの1:1スケールの場合の文字間のスペース
	const int TAB_SIZE = 8;			// タブの幅
	const char UNDERLINE = '_';		// 下線
	const char SOLID = 0x7F;        // コード$7Fの文字に使用される固定ブロック
	const int BOLD_SIZE = 4;        // 太字表示のときのシフトするピクセル数
}


class Text : public Image
{
private:
	TextureManager fontTexture;     // それぞれのフォントのテクスチャ
	LP_TEXTURE textureData;         // 一時保存用テクスチャデータ
	char    *file;                  // テクスチャファイル名
	Graphics *graphics;             // graphicsへのポインタ
	UINT width, height;             // 1文字の幅、高さ
	textNS::FontData fontData[textNS::ROWS][textNS::COLUMNS]; // それぞれの文字の左端と右端
	COLOR_ARGB color;               // フォントカラー(a,r,g,b)
	COLOR_ARGB backColor;           // 背景色(a,r,g,b)
	UINT  fontHeight;               // フォントの高さ
	UINT  tabSize;                  // タブの幅
	UINT  proportionalSpacing;      // プロポーショナルフォントの文字間のスペース
	bool proportional;              // プロポーショナルフォントの場合、true
	bool underline;
	bool bold;
	textNS::Alignment align;        // アラインメント(center, left, etc)

public:
	// デフォルトコンストラクタ
	Text();

	// デストラクタ
	virtual ~Text();

	//=============================================================
	// 継承したメンバ関数
	//=============================================================

	// Textを初期化
	// フォント画像内の各文字の左端と右端を特定
	// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
	// fontData配列は、各文字と左端と右端を格納
	virtual bool initialize(Graphics *g, const char *file);
	virtual void update(float frameTime) {};
	virtual void onLostDevice();
	virtual void onResetDevice();

	//=============================================================
	// 新しいメンバ関数
	//=============================================================

	// 表示する位置（XY座標）をセット
	virtual void setXY(int x, int y);

	// 文字列をX、Yに出力。spriteBegin()とspriteEnd()の間に呼び出す
	virtual void print(const std::string &str);

	// 文字列をX、Yに出力。spriteBegin()とspriteEnd()の間に呼び出す
	virtual void print(const std::string &str, int x, int y);

	// 文字列をX、Yに出力。spriteBegin()とspriteEnd()の間に呼び出す
	virtual void print(const std::string &str, int x, int y, textNS::Alignment align);

	// 現在のフォントサイズでの文字列の幅と高さ（ピクセル単位）を取得
	// 文字列は表示しない
	virtual void getWidthHeight(const std::string &str, UINT &width, UINT &height);

	// フォントカラーをセット
	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	// フォントカラーを戻す
	virtual COLOR_ARGB getFontColor() { return color; }

	// 背景色をセット
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }

	// 背景色を戻す
	virtual COLOR_ARGB getBackColor() { return backColor; }

	// フォントの高さをセット
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > textNS::MAX_FONT_HEIGHT)  // 不可能な高さの場合
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)textNS::FONT_HEIGHT;
	}

	// フォントの高さを戻す
	virtual UINT getFontHeight() { return fontHeight; }

	// プロポーショナルフォントかどうかをセット
	virtual void setProportional(bool p) { proportional = p; }

	// プロポーショナルフォントかどうかを戻す
	virtual bool getProportional() { return proportional; }

	// プロポーショナルフォントの文字間のスペースをセット
	virtual void setProportionalSpacing(UINT s) { proportionalSpacing = s; }

	// プロポーショナルフォントの文字間のスペースを戻す
	virtual UINT getProportionalSpacing() { return proportionalSpacing; }

	// 下線を表示するかどうかをセット
	virtual void setUnderline(bool u) { underline = u; }

	// 下線を表示するかどうかを戻す
	virtual bool getUnderline() { return underline; }

	// 太字にするかどうかをセット
	virtual void setBold(bool b) { bold = b; }

	// 太字にするかどうかを戻す
	virtual bool getBold() { return bold; }

	// タブのサイズをセット
	virtual void setTabSize(UINT size)
	{
		if (size == 0)
			return;
		tabSize = size;
	}

	// タブのサイズを返す
	virtual UINT getTabSize() { return tabSize; }

	// 現在の文字列と配置の指定に合わせてspriteData.x、spriteData.yを設定
	// デフォルトの配置はLEFT
	virtual void doAlign(const std::string &str);

	// spriteDateによって記述される文字スプライトを色と塗りつぶしを使って表示
	// 下線と文字を表示する
	virtual void drawChar(UCHAR ch);
};

#endif

