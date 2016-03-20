#ifndef _CONSTANTS_H            // このファイルが複数の箇所でインクルードされる場合に、
#define _CONSTANTS_H            // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
//                  定数
//=============================================================================

// ウィンドウに関する定数
const char CLASS_NAME[] = "TowerDiffence";
const char GAME_TITLE[] = "TowerDiffence ver0.1";
const bool FULLSCREEN = false;							// フルスクリーンの場合true
const UINT GAME_WIDTH = 1280;							// ゲーム画面の幅（ピクセル単位）
const UINT GAME_HEIGHT = 720;							// ゲーム画面の高さ（ピクセル単位）

// ゲーム内の定数
const double PI = 3.14159265;							// 円周率
const float FRAME_RATE = 60.0f;						// フレームレート (frames/sec)
const float MIN_FRAME_RATE = 10.0f;						// 最小のフレームレート
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;			// 1フレームに要する最小の時間
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;		// 1フレームに要する最大の時間

// 画像
const char MENU_IMAGE[] = "pictures\\menu.png";				// メニュー画像
const char BRAVE_MOVE_IMAGE[] = "pictures\\alex\\move_atack.png";	// 勇者の歩行画像

// 音声
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\waveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\soundBank.xsb";
// audio cues


// キーマップ
const UCHAR CONSOLE_KEY = '`';			// `キー
const UCHAR ESC_KEY = VK_ESCAPE;		// Escキー
const UCHAR ALT_KEY = VK_MENU;			// Altキー
const UCHAR ENTER_KEY = VK_RETURN;		// Enterキー
const UCHAR BRAVE_LEFT_KEY = VK_LEFT;	// 左移動キー
const UCHAR BRAVE_RIGHT_KEY = VK_RIGHT;	// 右移動キー
const UCHAR BRAVE_UP_KEY = VK_UP;		// 上移動キー
const UCHAR BRAVE_DOWN_KEY = VK_DOWN;	// 下移動キー
const UCHAR BRAVE_ATTACK_KEY = VK_RETURN;// 攻撃キー

// weapon types
enum WEAPON { TORPEDO, SHIP, PLANET };

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
	if (ptr)
		ptr->onLostDevice();
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
	if (ptr)
		ptr->onResetDevice();
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif
