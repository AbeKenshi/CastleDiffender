// TowerDiffenceはゲームのメインクラス
#include "towerDiffence.h"

//==========================================================
// コンストラクタ
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	menuOn = true;
}

//==========================================================
// デストラクタ
//==========================================================
TowerDiffence::~TowerDiffence()
{
	releaseAll();	// すべてのグラフィックスアイテムについて、onLostDevice()を呼び出す
}

//==========================================================
// ゲームを初期化
// エラー時にGameErrorをスロー
//==========================================================
void TowerDiffence::initialize(HWND hwnd)
{
	Game::initialize(hwnd);	// GameErrorをスロー

	// メニューのテクスチャ
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// メニューの画像
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	menu.setScale(2);

	// 勇者のテクスチャ
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// 勇者
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);

	return;
}

//==========================================================
// すべてのゲームアイテムを更新
//==========================================================
void TowerDiffence::update()
{
	if (menuOn)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
			roundStart();
		}
	}
	else
	{
		brave.update(frameTime);
	}
}

//==========================================================
// プレイの新しいラウンドを開始
//==========================================================
void TowerDiffence::roundStart()
{

}

//==========================================================
// 人工知能
//==========================================================
void TowerDiffence::ai()
{

}

//==========================================================
// 衝突を処理
//==========================================================
void TowerDiffence::collisions()
{

}

//==========================================================
// ゲームアイテムをレンダー
//==========================================================
void TowerDiffence::render()
{
	graphics->spriteBegin();	// スプライトの描画を開始

	if (menuOn)
		menu.draw();
	else
	{
		brave.draw();
	}

	graphics->spriteEnd();		// スプライトの描画を開始
}

//==========================================================
// グラフィックスデバイスが消失した場合
// グラフィックスデバイスをリセット可能にするため、
// 予約されていたビデオメモリをすべて解放
//==========================================================
void TowerDiffence::releaseAll()
{
	menuTexture.onLostDevice();
	braveTexture.onLostDevice();

	Game::releaseAll();
	return;
}

//==========================================================
// グラフィックスデバイスがリセットされた場合
// すべてのサーフェイスを再作成
//==========================================================
void TowerDiffence::resetAll()
{
	braveTexture.onResetDevice();
	menuTexture.onResetDevice();

	Game::resetAll();
	return;
}