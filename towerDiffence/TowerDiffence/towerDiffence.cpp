// TowerDiffenceはゲームのメインクラス
#include "towerDiffence.h"

//==========================================================
// コンストラクタ
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	menuOn = true;
	rect = NULL;
}

//==========================================================
// デストラクタ
//==========================================================
TowerDiffence::~TowerDiffence()
{
	safeDelete(rect);
	releaseAll();	// すべてのグラフィックスアイテムについて、onLostDevice()を呼び出す
}

//==========================================================
// ゲームを初期化
// エラー時にGameErrorをスロー
//==========================================================
void TowerDiffence::initialize(HWND hwnd)
{
	Game::initialize(hwnd);	// GameErrorをスロー
	rect = new Rect();
	rect->initialize(graphics);

	// メニューのテクスチャ
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// メニューの画像
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	menu.setScale(2);

	// マップのテクスチャ
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// マップの画像
	if (!tile.initialize(graphics, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// バリケードのテクスチャ
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	// バリケードの画像
	if (!barricade.initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
	barricade.setScale(1);
	barricade.setX(0);
	barricade.setY(0);

	// 勇者のテクスチャ
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// 勇者
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);

	// 炎のテクスチャ
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!fire.initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));

	// 雑魚敵のテクスチャ
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setScale(2);

	// ダッシュボード
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	barGraph.initialize(graphics, &dashboardTextures, towerDiffenceNS::BAR_GRAPH_X, towerDiffenceNS::BAR_GRAPH_Y, 0.5f, 20, graphicsNS::RED);
	barGraph.set(brave.getHealth());

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
		if (input->isKeyDown(BRAVE_FIRE_KEY))
			fire.fire(&brave);
		brave.update(frameTime);
		enemy.update(frameTime);
		fire.update(frameTime);
		barricade.update(frameTime);
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
	VECTOR2 collisionVector;

	if (brave.collidesWith(barricade, collisionVector)) {
		// 破壊処理
	}
}

//==========================================================
// ゲームアイテムをレンダー
// プレイ中のレイヤー：マップ→黒背景→その他アイテムの順
//==========================================================
void TowerDiffence::render()
{
	graphics->spriteBegin();	// スプライトの描画を開始

	if (menuOn)
	{
		menu.draw();
	}
	else
	{
		// ステージの描画
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // マップの各行を処理
		{
			tile.setY((float)(row*mapNS::TEXTURE_SIZE));      // タイルのYを設定
			barricade.setY((float)(row*barricadeNS::WIDTH));  // オブジェクトのYを設定
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // マップの各列を処理
			{
				if (mapNS::tileMap[row][col] >= 0)            // タイルが存在する場合
				{
					tile.setCurrentFrame(mapNS::tileMap[row][col]);                       // タイルのテクスチャを設定
					tile.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);                   // タイルのXを設定
					if (tile.getX() > -mapNS::TEXTURE_SIZE && tile.getX() < GAME_WIDTH)   // タイルが画面上にあるかどうか
						tile.draw();    // タイルを描画
				}
				if (mapNS::tileObj[row][col] >= 0)
				{
					barricade.setCurrentFrame(mapNS::tileObj[row][col]);							// オブジェクトのテクスチャを設定
					barricade.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);						// オブジェクトのXを設定
					if (barricade.getX() > -mapNS::TEXTURE_SIZE && barricade.getX() < GAME_WIDTH)   // オブジェクトが画面上にあるかどうか
						barricade.draw();   // オブジェクトを描画
				}
			}
		}
		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始

		enemy.draw();
		fire.draw();
		brave.draw();
		barGraph.set(brave.getHealth());
		barGraph.draw(graphicsNS::FILTER);	// 体力バーを描画
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
	dashboardTextures.onLostDevice();
	safeOnLostDevice(rect);
	Game::releaseAll();
	return;
}

//==========================================================
// グラフィックスデバイスがリセットされた場合
// すべてのサーフェイスを再作成
//==========================================================
void TowerDiffence::resetAll()
{
	dashboardTextures.onLostDevice();
	braveTexture.onResetDevice();
	menuTexture.onResetDevice();
	safeOnResetDevice(rect);
	Game::resetAll();
	return;
}