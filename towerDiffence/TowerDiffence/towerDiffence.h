//==========================================================
/// @file
/// @brief    TowerDiffenceクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _TOWERDIFFENCE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _TOWERDIFFENCE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "text.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"
#include "braveAttackCollision.h"
#include "enemyAttackCollision.h"
#include "fire.h"
#include "map.h"
#include "castle.h"
#include "enemy.h"
#include "midBoss.h"
#include "dashboard.h"
#include "rect.h"
#include "barricade.h"
#include "braveIcon.h"
#include "castleIcon.h"
#include "hpTextImage.h"
#include "mpTextImage.h"
#include "hitEffect.h"
#include "attackEffect.h"
#include <string>
#include "stage.h"

// TowerDiffenceクラスの定数
// ゲーム内でのステータス以外をここに記述
namespace towerDiffenceNS
{
	const char FONT[] = "Arial Bold";	// フォント
	const int FONT_BIG_SIZE = 256;		// フォントの高さ
	const int FONT_SCORE_SIZE = 48;
	// 体力バーの位置
	const int BRAVE_HEALTH_BAR_X = 100;
	const int BRAVE_HEALTH_BAR_Y = 0;
	const int BRAVE_MP_BAR_X = BRAVE_HEALTH_BAR_X;
	const int BRAVE_MP_BAR_Y = 25;
	const int CASTLE_HEALTH_BAR_X = 830;
	const int CASTLE_HEALTH_BAR_Y = 0;
	const int COUNT_DOWN_X = GAME_WIDTH / 2 - FONT_BIG_SIZE / 4;
	const int COUNT_DOWN_Y = GAME_HEIGHT / 2 - FONT_BIG_SIZE / 2;
	const int ROUND_TIME = 3;           // 新しいラウンドが開始するまでの時間
	const int ENEMY_NUM = 10;  // 雑魚敵の数
}

//==========================================================
// Gameクラスを継承してTowerDiffenceクラスを作成
//==========================================================
class TowerDiffence : public Game
{
private:
	// ゲームアイテム
	Stage stage;										// ステージ情報
	TextDX  fontBig;									// ゲームバナーのDirectXフォン
	Text    *fontCK;									// sprite based font
	TextureManager menuTexture;							// タイトルのテクスチャ
	TextureManager stageSelectTexture;					// ステージ選択画面のテクスチャ
	TextureManager resultTexture;                       // リザルトのテクスチャ
	TextureManager stageClearTexture;					// ステージクリア画面のテクスチャ
	TextureManager descriptionTexture;                  // 操作説明のテクスチャ
	TextureManager braveTexture;						// 勇者のテクスチャ
	TextureManager attackEffectTexture;					// 攻撃の衝撃波のテクスチャ
	TextureManager braveIconTexture;					// 勇者のアイコンのテクスチャ
	TextureManager attackCollisionTexture;				// 勇者の攻撃の当たり判定用のテクスチャ
	TextureManager tileTexture;							// タイルのテクスチャ
	TextureManager barricadeTexture;					// バリケードのテクスチャ
	TextureManager hitEffectTexture;					// 攻撃がヒットしたときのアニメーション画像のテクスチャ
	TextureManager castleTexture;						// 城のテクスチャ
	TextureManager castleIconTexture;					// 城のアイコンのテクスチャ
	TextureManager fireTexture;							// 炎のテクスチャ
	TextureManager enemyTexture;						// 雑魚敵のテクスチャ
	TextureManager midBossTexture;						// 中ボスのテクスチャ
	TextureManager dashboardTextures;					// ダッシュボードテクスチャ
	TextureManager textTexture;							// テキスト（ＭＰ、ＨＰ）のテクスチャ
	Image menu;											// タイトル画像
	Image stageSelect;									// ステージ選択画面の画像
	Image result;                                       // リザルト画像
	Image stageClear;									// ステージクリア画像
	Image description;                                  // 操作説明画像
	BraveIcon braveIcon;								// 勇者のアイコン
	CastleIcon castleIcon;								// 城のアイコン
	BarGraph braveHealthBar;							// 勇者の体力バー
	BarGraph braveMpBar;								// 勇者のMPバー
	BarGraph castleHealthBar;							// 城の体力バー
	HpTextImage braveHpText;							// 勇者のＨＰテキスト
	MpTextImage braveMpText;							// 勇者のＭＰテキスト
	HpTextImage castleHpText;							// 城のＨＰテキスト
	Rect *rect;											// Rectへのポインター
	bool menuOn;										// メニューフラグ
	bool stageSelectOn;									// ステージ選択フラグ
	bool descriptionOn;                                 // 操作説明フラグ
	float   roundTimer;									// 新しいラウンドが開始するまでの時間
public:
	// コンストラクタ
	TowerDiffence();

	// デストラクタ
	virtual ~TowerDiffence();

	// ゲームを初期化
	void initialize(HWND hwnd);

	// Gameからの純粋仮想関数をオーバーライドする必要がある
	void update();
	void ai();
	void collisions();
	void render();

	// プレイの新しいラウンドを開始
	void roundStart();

	void consoleCommand();	// コンソールコマンドを処理

	// グラフィックスデバイスが消失した場合
	// グラフィックスデバイスをリセット可能にするため、
	// 予約されていたビデオメモリをすべて解放
	void releaseAll();

	// グラフィックスデバイスがリセットされた場合
	// すべてのサーフェイスを再作成
	void resetAll();


	// ゲームオーバー時に呼び出す
	void gameOver();

	// ステージクリア時に呼び出す
	void clearStage();

	// 敵のテクスチャを初期化する
	void initializeEnemiesTexture();
};
#endif
