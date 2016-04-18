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
const float FRAME_RATE = 60.0f;							// フレームレート (frames/sec)
const float MIN_FRAME_RATE = 10.0f;						// 最小のフレームレート
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;			// 1フレームに要する最小の時間
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;		// 1フレームに要する最大の時間

// ゲーム内のパラメータ
// 勇者関係
const int braveAttackDamage = 50;				// 勇者（プレイヤー）の攻撃力（ダメージ量）
const int braveFireDamage = 110;				// 勇者のファイアー（必殺技）の攻撃力（ダメージ量）
const int braveMpRecovery = 10;					// 勇者のMP回復量（mpRecoveryTime秒ごとに回復）
const float braveMpRecoveryTime = 2.0f;			// 勇者のMPが回復する間隔（秒）
const float braveMoveSpeed = 150.0f;			// 勇者の移動速度（ピクセル）

// 画像
const char MENU_IMAGE[] = "pictures\\systemGraphics\\title.png";				// メニュー画像
const char STAGE_SELECT_IMAGE[] = "pictures\\systemGraphics\\stageselect.png";	// ステージ選択画面画像
const char RESULT_IMAGE[] = "pictures\\systemGraphics\\gameover.png";           // リザルト画像
const char STAGE_CLEAR_IMAGE[] = "pictures\\systemGraphics\\stageclear.png";	// ステージクリア画像
const char DESCRIPTION_IMAGE[] = "pictures\\systemGraphics\\description.png";   // 操作説明画像
const char BRAVE_MOVE_IMAGE[] = "pictures\\alex\\alex_main.png";				// 勇者の歩行画像
const char FIRE_IMAGE[] = "pictures\\alex\\fire.png";							// 炎の画像
const char ENEMY_IMAGE[] = "pictures\\enemy\\enemy.png";						// 雑魚敵の画像
const char MID_BOSS_IMAGE[] = "pictures\\enemy\\midBoss.png";					// 中ボスの画像
const char TILE_IMAGES[] = "pictures\\map\\ground.png";							// マップ画像
const char DASHBOARD_TEXTURES[] = "pictures\\systemGraphics\\dashboard.png";	// ダッシュボード画像
const char BARRICADE_IMAGE[] = "pictures\\map\\barricade.png";					// バリケードの画像
const char HIT_EFFECT_IMAGE[] = "pictures\\effect\\hitEffect.png";				// ダメージエフェクトの画像
const char ATTACK_EFFECT_IMAGE[] = "pictures\\effect\\attackEffect.png";		// 攻撃エフェクトの画像
const char COLLISION_IMAGE[] = "pictures\\alex\\attackCollision.png";			// 攻撃用のテクスチャ
const char CASTLE_IMAGE[] = "pictures\\map\\castle.png";						// 城画像
const char BRAVE_ICON_IMAGE[] = "pictures\\alex\\icon.png";						// 勇者のアイコン画像
const char TEXT_IMAGE[] = "pictures\\systemGraphics\\text.png";					// テキスト（ＭＰ、ＨＰ）画像
const char CASTLE_ICON_IMAGE[] = "pictures\\map\\castleIcon.png";				// 城のアイコンの画像
const char FONT_IMAGE[] = "pictures\\systemGraphics\\CKfont.png";				// スプライトテキストの画像

// 音声
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";
// audio cues
const char TITLE[]    = "title";
const char STAGE[]    = "stage";
const char CLEAR[]    = "clear";
const char GAMEOVER[] = "gameover";
const char KILL[]     = "kill";
const char FIRE_SE[]  = "fire";


// キーマップ
const UCHAR CONSOLE_KEY = '`';				// `キー
const UCHAR ESC_KEY = VK_ESCAPE;			// Escキー
const UCHAR ALT_KEY = VK_MENU;				// Altキー
const UCHAR ENTER_KEY = VK_RETURN;			// Enterキー
const UCHAR BRAVE_LEFT_KEY = VK_LEFT;		// 左移動キー
const UCHAR BRAVE_RIGHT_KEY = VK_RIGHT;		// 右移動キー
const UCHAR BRAVE_UP_KEY = VK_UP;			// 上移動キー
const UCHAR BRAVE_DOWN_KEY = VK_DOWN;		// 下移動キー
const UCHAR BRAVE_ATTACK_KEY = 'A';			// 攻撃キー
const UCHAR BRAVE_GAURD_KEY = 'D';			// ガードキー
const UCHAR BRAVE_FIRE_KEY = 'S';			// 必殺技キー

// weapon types
enum WEAPON { FIRE, BRAVE_ATTACK, BRAVE_SECOND_ATTACK, ENEMY_ATTACK , MIDBOSS_ATTACK};

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// ポインタ参照されるアイテムを安全に解放
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

// ポインタ参照されるアイテムを安全に削除
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
