#ifndef _TOWERDIFFENCE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _TOWERDIFFENCE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"
#include "attackCollision.h"
#include "fire.h"
#include "map.h"
#include "enemy.h"
#include "dashboard.h"
#include "rect.h"
#include "barricade.h"

namespace towerDiffenceNS
{
	// 体力バーの位置
	const int BAR_GRAPH_X = 0;	
	const int BAR_GRAPH_Y = 0;
	const int HBAR_X = 0;
	const int HBAR_Y = 0;
}

//==========================================================
// Gameクラスを継承してTowerDiffenceクラスを作成
//==========================================================
class TowerDiffence : public Game
{
private:
	// ゲームアイテム
	TextureManager menuTexture;		// タイトルのテクスチャ
	Image menu;						// タイトル画像
	TextureManager braveTexture;	// 勇者のテクスチャ
	Brave brave;					// 勇者
	TextureManager braveAttackCollisionTexture;	// 勇者の攻撃の当たり判定用のテクスチャ
	AttackCollision braveAttackCollision;		// 勇者の攻撃の当たり判定用
	TextureManager tileTexture;     // タイルのテクスチャ
	Map map;                        // タイル画像
	TextureManager barricadeTexture;	// バリケードのテクスチャ
	Barricade barricade;			// バリケード画像
	TextureManager fireTexture;		// 炎のテクスチャ
	Fire fire;						// 炎の画像
	TextureManager enemyTexture;	// 雑魚敵のテクスチャ
	Enemy enemy;					// 雑魚敵の画像
	TextureManager dashboardTextures;	// ダッシュボードテクスチャ
	BarGraph barGraph;				// 体力バー
	Rect *rect;						// Rectへのポインター
	float mapX;                     // 初期X座標
	bool menuOn;					// メニューフラグ

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
