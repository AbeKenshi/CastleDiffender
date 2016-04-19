//==========================================================
/// @file
/// @brief    ダッシュボード関連のクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _DASHBOARD_H            // このファイルが複数の箇所でインクルードされる場合に、 
#define _DASHBOARD_H            // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "image.h"
#include "constants.h"
#include "textureManager.h"
#include "input.h"

// ダッシュボードの定数
// ゲーム内でのステータス以外をここに記述
namespace dashboardNS
{
	const int	WIDTH = 48;				// 画像の幅（各フレーム）
	const int	HEGIHT = 48;			// 画像の高さ
    const int   TEXTURE_COLS = 4;       // テクスチャは4列
    const int   BAR_FRAME = 0;          // それぞれのテクスチャのフレーム番号
    const int   DIAL360_FRAME = 1;      // "
    const int   DIAL270_FRAME = 2;      // ...
    const int   DIAL180_FRAME = 3;
    const int   LIGHT_FRAME = 4;
    const int   POINTER_FRAME = 5;
    const int   SEGMENT_FRAME = 6;
    const int   DECIMAL_FRAME = 7;
    const int   SWITCH_OFF_FRAME = 8;
    const int   SWITCH_ON_FRAME = 9;
    const int   BUTTON_UP_FRAME = 10;
    const int   BUTTON_DOWN_FRAME = 11;
    const int   BAR_GRAPH_FRAME = 12;
    const int   SWITCH_WIDTH = 44;      // トグルスイッチの幅（ピクセル単位）
    const int   BAR_GRAPH_WIDTH = 8;    // 棒グラフの幅＋空きスペース
    enum DialType{DIAL360, DIAL270, DIAL180};
}

class SevenSegment : public Image
{
private:
    Image   mDecimal;	// セブンセグメントの画像
    UINT    mDigits;	// 桁数
    double  mNumber;	// 表示する数値
public:
	// コンストラクタ
    SevenSegment();
	// セブンセグメント表示の初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   left、top = 画面位置
	//         scale = 倍率（ズーム）
	//		   digits = 桁数
	//		   color = 数字の色
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT digits, COLOR_ARGB color);
	// セブンセグメント表示に表示する数値を設定
    void set(double value);
    // updateをオーバーライド
    virtual void update(float frameTime)    {}
	// セブンセグメントの数字「0」～「9」と「-」を表示
    void drawDigit(char n, COLOR_ARGB color);
	// 小数点を描画
    void drawDecimal(COLOR_ARGB color);
	// セブンセグメント表示を描画
	// number変数には、表示する浮動小数点数値が格納されている
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);
};

class Bar : public Image
{
public:
	// Barを初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   left、top = 画面位置
	//         scale = 倍率（ズーム）
	//		   color = バーの色
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, COLOR_ARGB color);
	// バーのサイズを設定
    void set(float percentOn);
	// updateをオーバーライド
    virtual void update(float frameTime)    {}
};

class DialGauge : public Image
{
private:
    Image   mPointer;					// 画像
    dashboardNS::DialType mDialType;	// 円盤の種類
public:
	// DialGaugeを初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   left、top = 画面位置
	//         scale = 倍率（ズーム）
	//		   type = 円盤の種類
	//		   zeroAngle = 円盤のゼロの位置
	//		   dialColor = 円盤の色
	//		   pointColor = 数字の色
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, dashboardNS::DialType type, float zeroAngle,
                    COLOR_ARGB dialColor, COLOR_ARGB pointerColor);
	// DialGaugeの指針を設定
    void set(float percentOn);
	// updateをオーバーライド
    virtual void update(float frameTime)    {}
	// DialGaugeと指針を描画
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

class Light : public Image
{
private:
    float   mFlashTimer;	// ライト点滅用のタイマー
    float   mFlashDelay;	// ライトが点滅する間隔
    COLOR_ARGB  mOnColor;	// 点灯時のライトの色
    COLOR_ARGB  mOffColor;	// 消灯時のライトの色
public:
	// コンストラクタ
    Light();
	// Lightを初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   left、top = 画面位置
	//         scale = 倍率（ズーム）
	//		   flashRate = 点灯/消灯/点滅の速さ
	//		   （<0の場合は点灯、=0の場合は消灯、>0の場合は1秒あたりの点滅の時間）
	//		   colorOn = 点灯時のライトの色
	//		   colorOff = 消灯時のライトの色
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                float scale,float flashRate, COLOR_ARGB colorOn, COLOR_ARGB colorOff);
	// flashRateを設定：<0の場合は点灯、 =0の場合は消灯、>0の場合は点滅の周期
	void set(float rate);
	// updateをオーバーライド
    virtual void update(float frameTime);
};

class ToggleSwitch : public Image
{
private:
    Input   *mInput;			// 入力システムへのポインタ
    HWND    mHwnd;				// ウィンドウハンドル
    RECT    mSwitchRect;        // マウスクリックを受け付ける範囲
    bool    mSwitchOn;          // スイッチの状態
    bool    mMouseClick;        // マウスクリックの状態
    public:
    // Toggle switchコンストラクタ
    ToggleSwitch();
	// 切り替えスイッチ（ToggleSwitch）を初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   *in = Inputオブジェクトへのポインタ
	//         hwnd = ウィンドウへのハンドル
	//		   left、top = 画面位置
	//		   scale = 倍率（ズーム）
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale);
	// updateをオーバーライド
    virtual void update(float frameTime);
    // スイッチの状態を取得
    bool getSwitchOn()   {return mSwitchOn;}
    // スイッチの状態を設定
    void setSwitch(bool on) {mSwitchOn = on;}
};

class PushButton : public Image
{
private:
	Input   *mInput;			// 入力システムへのポインタ
	HWND    mHwnd;				// ウィンドウハンドル
	RECT    mSwitchRect;        // マウスクリックを受け付ける範囲
	bool    mSwitchOn;          // スイッチの状態
	bool    mMouseClick;        // マウスクリックの状態
    bool    mMomentary;         // 一定時間ごとに切り替える場合はtrue、トグルの場合はfalse
public:
    // Pushbutton switchコンストラクタ
    PushButton();
	// プッシュボタン（PushButton）を初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   *in = Inputオブジェクトへのポインタ
	//         hwnd = ウィンドウへのハンドル
	//		   left、top = 画面位置
	//		   scale = 倍率（ズーム）
	//		   type = trueの場合はモーメンタリー、falseの場合はオルタネート
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale, bool momentary);
	// updateをオーバーライド
    virtual void update(float frameTime);
	// スイッチの状態を取得
    bool getSwitchOn()  {return mSwitchOn;}
	// スイッチの状態を設定
    void setSwitch(bool on) {mSwitchOn = on;}
};

//
class BarGraph : public Image
{
private:
    int mMaxBars;			// バーの本数の最大数
    int mBarsOn;			// 現在のバーの本数
public:
    // BarGraphコンストラクタ
    BarGraph();
	// BarGraphを初期化
	// 実行前：*graphics = Graphicsオブジェクトへのポインタ
	//		   *textureM = TextureManagerオブジェクトへのポインタ
	//		   left、top = 画面位置
	//		   scale = 倍率（ズーム）
	//		   bars = メーター内のバーの本数
	//		   color = バーの色
	// 実行後：成功した場合はtrue、エラーの場合はfalseを戻す
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT bars, COLOR_ARGB color);
	// barsOnの値を、表示するバーの本数に設定
	// パラメータpは割合（0～100）
    void set(float percentOn);	
	// updateをオーバーライド
    virtual void update(float frameTime)    {}
	// BarGraphを描画
	// barsOnは、表示するバーの本数を格納
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

#endif

