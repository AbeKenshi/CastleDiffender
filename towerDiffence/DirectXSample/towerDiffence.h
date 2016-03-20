#ifndef _TOWERDIFFENCE_H	// このファイルが複数の箇所でインクルードされる場合に、
#define _TOWERDIFFENCE_H	// 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"

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
