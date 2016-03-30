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
#include <string>

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
	const int ROUND_TIME = 5;           // 新しいラウンドが開始するまでの時間
	const int ENEMY_NUM = 1;  // 雑魚敵の数
}

//==========================================================
// Gameクラスを継承してTowerDiffenceクラスを作成
//==========================================================
class TowerDiffence : public Game
{
private:
	// ゲームアイテム
	TextDX  fontBig;									// ゲームバナーのDirectXフォン
	Text    *fontCK;									// sprite based font
	TextureManager menuTexture;							// タイトルのテクスチャ
	Image menu;											// タイトル画像
	TextureManager resultTexture;                       // リザルトのテクスチャ
	Image result;                                       // リザルト画像
	TextureManager braveTexture;						// 勇者のテクスチャ
	Brave brave;										// 勇者
	TextureManager braveIconTexture;					// 勇者のアイコンのテクスチャ
	BraveIcon braveIcon;								// 勇者のアイコン
	TextureManager attackCollisionTexture;				// 勇者の攻撃の当たり判定用のテクスチャ
	BraveAttackCollision braveAttackCollision;			// 勇者の攻撃の当たり判定用
	EnemyCollision enemyAttackCollision[towerDiffenceNS::ENEMY_NUM]; // 雑魚敵の攻撃の当たり判定用
	EnemyCollision midBossAttackCollision;		// 中ボスの攻撃の当たり判定用
	TextureManager tileTexture;							// タイルのテクスチャ
	Map map;											// タイル画像
	TextureManager barricadeTexture;					// バリケードのテクスチャ
	Barricade barricades[mapNS::BARRICADE_NUM];         // バリケードの配列
	TextureManager castleTexture;						// 城のテクスチャ
	Castle castle;										// 城
	TextureManager castleIconTexture;					// 城のアイコンのテクスチャ
	CastleIcon castleIcon;								// 城のアイコン
	TextureManager fireTexture;							// 炎のテクスチャ
	Fire fire;											// 炎
	TextureManager enemyTexture;						// 雑魚敵のテクスチャ
	Enemy enemy[towerDiffenceNS::ENEMY_NUM];	    	// 雑魚敵
	TextureManager midBossTexture;						// 中ボスのテクスチャ
	MidBoss midBoss;									// 中ボス
	TextureManager dashboardTextures;					// ダッシュボードテクスチャ
	BarGraph braveHealthBar;							// 勇者の体力バー
	BarGraph braveMpBar;								// 勇者のMPバー
	BarGraph castleHealthBar;							// 城の体力バー
	TextureManager textTexture;							// テキスト（ＭＰ、ＨＰ）のテクスチャ
	HpTextImage braveHpText;							// 勇者のＨＰテキスト
	MpTextImage braveMpText;							// 勇者のＭＰテキスト
	HpTextImage castleHpText;							// 城のＨＰテキスト
	Rect *rect;											// Rectへのポインター
	bool menuOn;										// メニューフラグ
	float remainingTime;								// ゲーム内の残り時間
	bool    roundOver;									// ラウンドが終了した場合、true
	float   roundTimer;									// 新しいラウンドが開始するまでの時間
	int a = 0;
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

	// グラフィックスデバイスが消失した場合
	// グラフィックスデバイスをリセット可能にするため、
	// 予約されていたビデオメモリをすべて解放
	void releaseAll();

	// グラフィックスデバイスがリセットされた場合
	// すべてのサーフェイスを再作成
	void resetAll();

};
#endif
