// TowerDiffenceはゲームのメインクラス
#include "towerDiffence.h"

//==========================================================
// コンストラクタ
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	fontCK = new Text();   // sprite based font
	menuOn = true;
	roundOver = false;
	rect = NULL;
	remainingTime = 1500.0f;
}

//==========================================================
// デストラクタ
//==========================================================
TowerDiffence::~TowerDiffence()
{
	safeDelete(rect);
	safeDelete(fontCK);
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

	// init text
	if (!fontCK->initialize(graphics, FONT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CKfont"));


	// メニューのテクスチャ
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// メニューの画像
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	menu.setScale(2);

	// リザルトのテクスチャ
	if (!resultTexture.initialize(graphics, RESULT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result texture"));
	// リザルトの画像
	if (!result.initialize(graphics, 0, 0, 0, &resultTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result"));
	result.setScale(2);

	// マップのテクスチャ
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// マップの画像
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

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
	if (!castle.initialize(this, castleNS::WIDTH, castleNS::HEIGHT, castleNS::TEXTURE_COLS, &castleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle"));

	// 城のアイコンのテクスチャ
	if (!castleIconTexture.initialize(graphics, CASTLE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle icon texture"));
	// 城のアイコンの画像
	if (!castleIcon.initialize(graphics, castleIconNS::WIDTH, castleIconNS::HEIGHT, castleIconNS::TEXTURE_COLS, &castleIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle icon"));

	// 勇者のテクスチャ
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// 勇者
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);
	brave.setMapPointer(&map);

	// 勇者のアイコンのテクスチャ
	if (!braveIconTexture.initialize(graphics, BRAVE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon texture"));
	// 勇者のアイコンの画像
	if (!braveIcon.initialize(graphics, braveIconNS::WIDTH, braveIconNS::HEIGHT, braveIconNS::TEXTURE_COLS, &braveIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon"));
	braveIcon.linkEntity(&brave);

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
	fire.setScale(1.5);

	// 雑魚敵のテクスチャ
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setScale(2);
	enemy.setMapPointer(&map);
	enemy.setBarricadesPointer(barricades);

	// ダッシュボード
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	braveHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_HEALTH_BAR_X, towerDiffenceNS::BRAVE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::RED);
	braveHealthBar.set(brave.getHealth());
	braveMpBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_MP_BAR_X, towerDiffenceNS::BRAVE_MP_BAR_Y, 0.5f, 100, graphicsNS::GREEN);
	braveMpBar.set(brave.getMP());
	castleHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::CASTLE_HEALTH_BAR_X + 40, towerDiffenceNS::CASTLE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::BLUE);
	castleHealthBar.set(castle.getHealth());

	// テキスト画像
	if (!textTexture.initialize(graphics, TEXT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text textures"));
	if (!braveHpText.initialize(graphics, hpTextImageNS::WIDTH, hpTextImageNS::HEIGHT, hpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	if (!braveMpText.initialize(graphics, mpTextImageNS::WIDTH, mpTextImageNS::HEIGHT, mpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	if (!castleHpText.initialize(graphics, hpTextImageNS::WIDTH, hpTextImageNS::HEIGHT, hpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	castleHpText.setX(830);

	// タイトルBGM再生
	audio->playCue("title");

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
			audio->stopCue("title");
			audio->playCue("stage");
			roundStart();
		}
	}
	else if (roundOver)
	{
		if (input->isKeyDown('Z'))
		{
			menuOn = true;
			input->clearAll();
			audio->stopCue("gameover");
			audio->playCue("title");
			roundStart();
		}
		else if (input->isKeyDown('X'))
		{
			exit(1);
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
		brave.update(frameTime);
		enemy.update(frameTime);
		fire.update(frameTime);
		braveAttackCollision.update(frameTime);
		enemyAttackCollision.update(frameTime);
		castle.update(frameTime);
		braveIcon.update(frameTime);
		for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
		{
			barricades[i].update(frameTime);
		}
		// 残り時間が0ならゲームオーバー
		remainingTime -= frameTime;
		if (remainingTime < 0)
		{
			audio->stopCue("stage");
			audio->playCue("gameover");
			roundOver = true;
			// roundTimer = towerDiffenceNS::ROUND_TIME;
		}
		/*
		if (roundOver)
		{
			roundTimer -= frameTime;
			if (roundTimer <= 0)
				roundStart();
		}
		*/
	}
}

//==========================================================
// プレイの新しいラウンドを開始
//==========================================================
void TowerDiffence::roundStart()
{
	// 初期化
	brave.reset();
	enemy.reset();
	castle.reset();
	fire.reset();

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}

	// HP,MP初期化
	brave.setHealth(100);
	brave.setMP(100);

	remainingTime = 1500.0f;

	roundOver = false;
}

//==========================================================
// 人工知能
//==========================================================
void TowerDiffence::ai()
{
	enemy.ai(frameTime, brave);
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
	// 敵の攻撃コリジョンと城の衝突の場合
	if (enemyAttackCollision.collidesWith(castle, collisionVector))
	{
		castle.damage(ENEMY_ATTACK);
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

	// 攻撃中ならば行動選択は行わない
	if (enemy.getState() == enemyNS::ATTACK_BARRICADE || enemy.getState() == enemyNS::ATTACK_BRAVE || enemy.getState() == enemyNS::ATTACK_CASTLE || enemy.getState() == enemyNS::PRE_ATTACK)
	{
	}
	else if (enemy.collidesWith(brave, collisionVector))// 雑魚敵とプレイヤーの衝突判定
	{
		enemy.changeAttack(collisionVector);
		enemy.setAttackState(enemyNS::ATTACK_BRAVE);
	}
	else if (enemy.collidesWith(castle, collisionVector))	// 雑魚敵と城の衝突判定
	{
		enemy.changeAttack(collisionVector);
		enemy.setAttackState(enemyNS::ATTACK_CASTLE);
	}
	else if (!enemy.checkBarricadeOnLine(castle.getCenterX(), castle.getCenterY()))	// 城までの直線上にバリケードがあるかをチェック
	{
		enemy.setState(enemyNS::MOVE_CASTLE);
		VECTOR2 pos;
		pos.x = castle.getCenterX();
		pos.y = castle.getCenterY();
		enemy.setGoalPost(pos);
	}
	else 
	{
		// 最近接のバリケードを探索
		int nearBarricadeIndex = enemy.searchNearBarricadeIndex();
		// 最近接のバリケードに衝突していたら攻撃、それ以外ならバリケードに向かう。
		if (enemy.collidesWith(barricades[nearBarricadeIndex], collisionVector))
		{
			enemy.changeAttack(collisionVector);
			enemy.setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else
		{
			enemy.setState(enemyNS::MOVE_BARRICADE);
			VECTOR2 pos;
			pos.x = barricades[nearBarricadeIndex].getX();
			pos.y = barricades[nearBarricadeIndex].getY();
			enemy.setGoalPost(pos);
		}
	}
	
	/*
	// 敵とバリケードの衝突, 1つでも衝突していたら敵に通知
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (enemy.collidesWith(barricades[i], collisionVector))
		{
			enemy.setNearBarricade(true);
			break;
		}
		if (i == mapNS::BARRICADE_NUM - 1)
			enemy.setNearBarricade(false);
	}*/

	// 敵の攻撃コリジョンとバリケードの衝突
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (enemyAttackCollision.collidesWith(barricades[i], collisionVector)) {
			barricades[i].damage();
			enemyAttackCollision.setVisible(false);
			enemyAttackCollision.setActive(false);
		}
	}
	// 死亡チェック
	if ((castle.isDeath() || brave.getActive() == false) && !roundOver)
	{
		audio->stopCue("stage");
		audio->playCue("gameover");
		roundOver = true;
		/*
		exit(1);
		if (roundOver == false)
		{
			roundOver = towerDiffenceNS::ROUND_TIME;
			roundOver = true;
		}
		*/
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
	else if (roundOver)
	{
		result.draw();
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
					//barricades[count].setCurrentFrame(map.getMapObj(row, col));		    							// オブジェクトのテクスチャを設定
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

		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		castle.draw();
		enemy.draw();
		fire.draw();
		brave.draw();
		braveAttackCollision.draw();
		enemyAttackCollision.draw();
		braveHealthBar.set(brave.getHealth());
		braveMpBar.set(brave.getMP());
		castleHealthBar.set(castle.getHealth());
		braveHealthBar.draw(graphicsNS::FILTER);	// 体力バーを描画
		braveMpBar.draw(graphicsNS::FILTER);
		castleHealthBar.draw(graphicsNS::FILTER);
		// shadow
		char str[128] = "TIME-";
		char time[5] = { 0 };
		sprintf_s(time, "%04d", (int)remainingTime);
		strcat_s(str, time);
		fontCK->setFontHeight(40);
		fontCK->setFontColor(SETCOLOR_ARGB(128, 128, 128, 128));  // shadow grey
		fontCK->print(str, 512, 10);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->print(str, 505, 7);
		fontCK->setFontHeight(14);
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
	SAFE_ON_LOST_DEVICE(fontCK);
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
	SAFE_ON_RESET_DEVICE(fontCK);
	dashboardTextures.onLostDevice();
	braveTexture.onResetDevice();
	menuTexture.onResetDevice();
	safeOnResetDevice(rect);
	Game::resetAll();
	return;
}