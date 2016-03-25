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
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// バリケードオブジェクト初期化
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i] = *(new Barricade());
	}

	// バリケードのテクスチャ
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	// バリケードの画像
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!barricades[i].initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		barricades[i].setScale(1);
	}

	// 城のテクスチャ
	if (!castleTexture.initialize(graphics, CASTLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle texture"));
	// 城の画像
	if (!castle.initialize(this, castleNS::WIDTH, castleNS::HEIGHT, 0, &castleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle"));
	castle.setScale(120.0f / 96.0f);

	// 勇者のテクスチャ
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// 勇者
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);


	// 勇者の当たり判定用のテクスチャ
	if (!attackCollisionTexture.initialize(graphics, COLLISION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision texture"));
	// 勇者のあたり判定用
	if (!braveAttackCollision.initialize(this, braveAttackCollisionNS::WIDTH, braveAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision"));
	// 雑魚敵の当たり判定用
	if (!enemyAttackCollision.initialize(this, enemyAttackCollisionNS::WIDTH, enemyAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	
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
		if (brave.getAttackCollisionFlag())
			braveAttackCollision.attack(&brave);
		if (enemy.getAttackCollisionFlag())
			enemyAttackCollision.attack(&enemy);
		brave.update(frameTime, &map);
		enemy.update(frameTime, &map);
		fire.update(frameTime);
		braveAttackCollision.update(frameTime);
		enemyAttackCollision.update(frameTime);
		castle.update(frameTime);
		for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
		{
			barricades[i].update(frameTime);
		}
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
	enemy.ai(frameTime, brave, barricades);
}

//==========================================================
// 衝突を処理
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;
	// プレイヤーと雑魚敵の衝突の場合
	if (enemy.collidesWith(brave, collisionVector))
	{
		enemy.setNearPlayer(true);
	}
	else
		enemy.setNearPlayer(false);
	
	// プレイヤーの攻撃コリジョンと雑魚敵の衝突の場合
	if (braveAttackCollision.collidesWith(enemy, collisionVector))
	{
		enemy.damage(BRAVE_ATTACK);
		braveAttackCollision.setVisible(false);
		braveAttackCollision.setActive(false);
	}
	// 敵の攻撃コリジョンとプレイヤーの衝突の場合
	if (enemyAttackCollision.collidesWith(brave, collisionVector))
	{
		brave.damage(ENEMY_ATTACK);
		enemyAttackCollision.setVisible(false);
		enemyAttackCollision.setActive(false);
	}
	// 炎と雑魚敵の衝突の場合
	if (fire.collidesWith(enemy, collisionVector))
	{
		enemy.damage(FIRE);
		fire.setVisible(false);
		fire.setActive(false);
	}
	// プレイヤーとバリケードの衝突
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++) {
		if (enemy.collidesWith(barricades[i], collisionVector)) {
			barricades[i].setActive(false);
			barricades[i].setVisible(false);

		}

		barricades[i].draw();
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
		// マップとバリケードは初めだけ描画
		int count = 0;  // バリケードの数数える用
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // マップの各行を処理
		{
			map.setY((float)(row*mapNS::TEXTURE_SIZE));       // タイルのYを設定
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // マップの各列を処理
			{
				if (map.getMapData(row, col) >= 0)            // タイルが存在する場合
				{
					map.setCurrentFrame(map.getMapData(row, col));                       // タイルのテクスチャを設定
					map.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);                    // タイルのXを設定
					if (map.getX() > -mapNS::TEXTURE_SIZE && map.getX() < GAME_WIDTH)     // タイルが画面上にあるかどうか
						map.draw();    // タイルを描画
				}
				if (map.getMapObj(row, col) >= 0)
				{
					barricades[count].setCurrentFrame(map.getMapObj(row, col));		    							// オブジェクトのテクスチャを設定
					barricades[count].setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);								// オブジェクトのXを設定
					barricades[count].setY((float)(row*barricadeNS::WIDTH));										// オブジェクトのYを設定
					if (barricades[count].getX() > -mapNS::TEXTURE_SIZE && barricades[count].getX() < GAME_WIDTH)	// オブジェクトが画面上にあるかどうか
					{
						barricades[count].draw();   // オブジェクトを描画
						count++;
					}
				}
			}
		}

		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始

		castle.draw();
		enemy.draw();
		fire.draw();
		brave.draw();
		braveAttackCollision.draw();
		enemyAttackCollision.draw();
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