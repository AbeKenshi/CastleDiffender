//==========================================================
/// @file
/// @brief    towerDiffence.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "towerDiffence.h"

//==========================================================
// コンストラクタ
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	fontCK = new Text();   // sprite based font
	menuOn = true;
	stageSelectOn = false;
	descriptionOn = false;
	rect = NULL;
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

	// ステージ選択画面のテクスチャ
	if (!stageSelectTexture.initialize(graphics, STAGE_SELECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage select texture"));
	// ステージ選択画面の画像
	if (!stageSelect.initialize(graphics, 0, 0, 0, &stageSelectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage select"));

	// リザルトのテクスチャ
	if (!resultTexture.initialize(graphics, RESULT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result texture"));
	// リザルトの画像
	if (!result.initialize(graphics, 0, 0, 0, &resultTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result"));
	result.setX(GAME_WIDTH / 2.0f - result.getWidth() / 2.0f);
	result.setY((float)-result.getHeight());

	// ステージクリア画面のテクスチャ
	if (!stageClearTexture.initialize(graphics, STAGE_CLEAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage clear texture"));
	// ステージクリア画像
	if (!stageClear.initialize(graphics, 0, 0, 0, &stageClearTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage clear"));
	stageClear.setX(GAME_WIDTH / 2.0f - stageClear.getWidth() / 2.0f);
	stageClear.setY((float)GAME_HEIGHT);

	// 操作説明のテクスチャ
	if (!descriptionTexture.initialize(graphics, DESCRIPTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description texture"));
	// 操作説明の画像
	if (!description.initialize(graphics, 0, 0, 0, &descriptionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description"));

	// マップのテクスチャ
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// マップの画像
	if (!stage.getMap().initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// バリケードのテクスチャ
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	if (!hitEffectTexture.initialize(graphics, HIT_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit effect texture"));
	// バリケードの画像
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!stage.getBarricade(i).initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		stage.getBarricade(i).setScale(1);
		if (!stage.getBarricade(i).getHitEffect().initialize(graphics, hitEffectNS::WIDTH, hitEffectNS::HEIGHT, hitEffectNS::TEXTURE_COLS, &hitEffectTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hitEffect"));
	}

	// 城のテクスチャ
	if (!castleTexture.initialize(graphics, CASTLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle texture"));
	// 城の画像
	if (!stage.getCastle().initialize(this, castleNS::WIDTH, castleNS::HEIGHT, castleNS::TEXTURE_COLS, &castleTexture))
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
	if (!stage.getBrave().initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	stage.getBrave().setScale(1.5);
	stage.getBrave().setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	stage.getBrave().setCurrentFrame(braveNS::MOVE_UP_START_FRAME);
	stage.getBrave().setMapPointer(stage.getMap());

	// 勇者のアイコンのテクスチャ
	if (!braveIconTexture.initialize(graphics, BRAVE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon texture"));
	// 勇者のアイコンの画像
	if (!braveIcon.initialize(graphics, braveIconNS::WIDTH, braveIconNS::HEIGHT, braveIconNS::TEXTURE_COLS, &braveIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon"));
	braveIcon.linkEntity(stage.getBrave());

	// 勇者の当たり判定用のテクスチャ
	if (!attackCollisionTexture.initialize(graphics, COLLISION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision texture"));
	// 勇者のあたり判定用
	if (!stage.getBrave().getBraveAttackCollision().initialize(this, braveAttackCollisionNS::WIDTH, braveAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision"));
	if (!attackEffectTexture.initialize(graphics, ATTACK_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect texture"));
	if (!stage.getBrave().getBraveAttackCollision().getAttackEffect().initialize(graphics, attackEffectNS::WIDTH, attackEffectNS::HEIGHT, attackEffectNS::TEXTURE_COLS, &attackEffectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect"));

	// 炎のテクスチャ
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!stage.getBrave().getFire().initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));
	stage.getBrave().getFire().setScale(1.5);

	// 雑魚敵のテクスチャ
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	// 中ボスのテクスチャ
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));

	// ダッシュボード
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	braveHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_HEALTH_BAR_X, towerDiffenceNS::BRAVE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::RED);
	braveHealthBar.set(stage.getBrave().getHealth());
	braveMpBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_MP_BAR_X, towerDiffenceNS::BRAVE_MP_BAR_Y, 0.5f, 100, graphicsNS::GREEN);
	braveMpBar.set((float)stage.getBrave().getMP());
	castleHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::CASTLE_HEALTH_BAR_X + 40, towerDiffenceNS::CASTLE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::BLUE);
	castleHealthBar.set(stage.getCastle().getHealth());

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
	if (menuOn)		// メニュー画面表示中にZキーが押されるまではメニュー画面を表示し続ける
	{
		if (input->isKeyDown('Z')) // Zキーでステージ選択画面に以降
		{
			menuOn = false;
			input->clearAll();
			stageSelectOn = true;
			stage.reset();

			rect->setX(380);
			rect->setY(80);
			rect->setWidth(510);
			rect->setHeight(81);
			rect->setBackColor(SETCOLOR_ARGB(50, 120, 120, 255));
			rect->reset();
		}
		else if (input->isKeyDown('X')) // Xキーで操作説明表示
		{
			descriptionOn = true;
			menuOn = false;
			input->clearAll();
		}
		else if (input->isKeyDown('E'))
		{
			exitGame();
		}
	}
	else if (stageSelectOn)
	{
		if (input->isKeyDown('Z'))	// Zキーでステージ決定
		{
			stageSelectOn = false;
			audio->stopCue("title");
			roundStart();

			rect->setX((float)rectNS::X);
			rect->setY((float)rectNS::Y);
			rect->setWidth(rectNS::WIDTH);
			rect->setHeight(rectNS::HEIGHT);
			rect->setBackColor(rectNS::BACK_COLOR);
			rect->reset();
		}
		else if (input->isKeyDown(BRAVE_DOWN_KEY))
		{
			if (stage.getStageNum() < 3 - 1)
			{
				stage.setStageNum(stage.getStageNum() + 1);
				rect->setY(rect->getY() + 240);
				rect->reset();
			}
			input->clearAll();
		}
		else if (input->isKeyDown(BRAVE_UP_KEY))
		{
			if (stage.getStageNum() > 0)
			{
				stage.setStageNum(stage.getStageNum() - 1);
				rect->setY(rect->getY() - 240);
				rect->reset();
			}
			input->clearAll();
		}
	}
	else if (descriptionOn) // 操作説明中はXキーでタイトルに戻る
	{
		if (input->isKeyDown('X'))
		{
			descriptionOn = false;
			menuOn = true;
			input->clearAll();
		}
	}
	else if (stage.getRoundOver())	// ゲームオーバー中にZが押されたらメニュー画面に戻る、Xが押されたらプログラム終了
	{
		if (result.getY() > 50)
		{
			if (input->isKeyDown('X'))
			{
				menuOn = true;
				input->clearAll();
				audio->stopCue("gameover");
				audio->playCue("title");
			}
			else if (input->isKeyDown('E'))
			{
				exitGame();
			}
			else if (input->isKeyDown('Z'))
			{
				input->clearAll();
				audio->stopCue("gameover");
				roundStart();
			}
		}
		else
		{
			result.setY(result.getY() + frameTime * 120.0f);
		}
	}
	else if (stage.getClearedStage())
	{
		if (stageClear.getY() < 250)
		{
			if (input->isKeyDown('X'))
			{
				menuOn = true;
				input->clearAll();
				audio->stopCue("clear");
				audio->playCue("title");
				stage.setClearedStage(false);
			}
			else if (input->isKeyDown('E'))
			{
				exitGame();
			}
			else if (input->isKeyDown('Z'))
			{
				input->clearAll();
				audio->stopCue("clear");
				roundStart();
			}
		}
		else
		{
			stageClear.setY(stageClear.getY() - frameTime * 320.0f);
		}
	}
	else				// ゲーム中の場合、
	{
		if (roundTimer > 0.0f)
		{
			roundTimer -= frameTime;
			return;
		}
		stage.runStage(frameTime);
		if (stage.getInitializedEnemies())
		{
			initializeEnemiesTexture();
		}
		if (stage.getRoundOver())
		{
			gameOver();
		}
		if (stage.getClearedStage())
		{
			clearStage();
		}

		// 勇者のアイコン画像を更新
		braveIcon.update(frameTime);
	}
}

//==========================================================
// プレイの新しいラウンドを開始
//==========================================================
void TowerDiffence::roundStart()
{
	stage.roundStart();
	result.setY((float)-result.getHeight());
	stageClear.setY((float)GAME_HEIGHT);
	braveIcon.reset();
	roundTimer = towerDiffenceNS::ROUND_TIME;
	audio->playCue("stage");
}

//==========================================================
// 人工知能
//==========================================================
void TowerDiffence::ai()
{
	stage.ai(frameTime);
}

//==========================================================
// 衝突を処理
//==========================================================
void TowerDiffence::collisions()
{
	stage.collisions();
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

		char str[128] = "PUSH Z KEY : STAGE SELECT";
		char str2[128] = "PUSH X KEY : OPERATION DESCRIPTION";
		char str3[128] = "PUSH E KEY : EXIT";
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
		fontCK->print(str, 273, 353);
		fontCK->print(str2, 273, 453);
		fontCK->print(str3, 273, 553);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->print(str, 273, 350);
		fontCK->print(str2, 273, 450);
		fontCK->print(str3, 273, 550);
	}
	else if (stageSelectOn)
	{
		stageSelect.draw();
		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始
		char str[128] = "PUSH Z KEY : START STAGE!";
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
		fontCK->print(str, 373, 653);
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->print(str, 370, 650);
	}
	else if (descriptionOn)
	{
		menu.draw();
		description.draw();
	}
	else
	{
		// マップとバリケードは初めだけ描画
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // マップの各行を処理
		{
			stage.getMap().setY((float)(row*mapNS::TEXTURE_SIZE));       // タイルのYを設定
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // マップの各列を処理
			{
				if (stage.getMap().getMapData(row, col) >= 0)            // タイルが存在する場合
				{
					stage.getMap().setCurrentFrame(stage.getMap().getMapData(row, col));                       // タイルのテクスチャを設定
					stage.getMap().setX((float)(col*mapNS::TEXTURE_SIZE));                    // タイルのXを設定
					if (stage.getMap().getX() > -mapNS::TEXTURE_SIZE && stage.getMap().getX() < GAME_WIDTH)     // タイルが画面上にあるかどうか
						stage.getMap().draw();    // タイルを描画
				}
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			stage.getBarricade(i).draw();   // オブジェクトを描画
			stage.getBarricade(i).getHitEffect().draw();
		}

		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始

		for (int i = 0; i < stage.getEnemyNum(); i++) {
			float tmpX = stage.getEnemy(i).getX();
			float tmpY = stage.getEnemy(i).getY();
			stage.getEnemy(i).setX((float)(tmpX - stage.getEnemy(i).getWidth() * (stage.getEnemy(i).getScale() - 1) / 2.0));
			stage.getEnemy(i).setY((float)(tmpY - stage.getEnemy(i).getHeight() * (stage.getEnemy(i).getScale() - 1) / 2.0 - 10.0));
			switch (stage.getEnemy(i).getEnemyType())
			{
			case enemyNS::RED:
				stage.getEnemy(i).draw(graphicsNS::RED);
				break;
			case enemyNS::BLUE:
				stage.getEnemy(i).draw(graphicsNS::BLUE);
				break;
			default:
				stage.getEnemy(i).draw(graphicsNS::WHITE);
				break;
			}
			stage.getEnemy(i).getAttackCollision().draw();
			stage.getEnemy(i).setX(tmpX);
			stage.getEnemy(i).setY(tmpY);
		}
		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		stage.getCastle().draw();
		stage.getBrave().getFire().draw();
		float tmpX = stage.getBrave().getX();
		float tmpY = stage.getBrave().getY();
		stage.getBrave().setX((float)(tmpX - stage.getBrave().getWidth() * (stage.getBrave().getScale() - 1) / 2.0));
		stage.getBrave().setY((float)(tmpY - stage.getBrave().getHeight() * (stage.getBrave().getScale() - 1) / 2.0 - 10));
		stage.getBrave().draw(graphicsNS::WHITE);
		stage.getBrave().setX(tmpX);
		stage.getBrave().setY(tmpY);
		stage.getBrave().getBraveAttackCollision().draw();
		stage.getBrave().getBraveAttackCollision().getAttackEffect().draw();
		braveHealthBar.set(stage.getBrave().getHealth());
		braveMpBar.set((float)stage.getBrave().getMP());
		castleHealthBar.set(stage.getCastle().getHealth());
		braveHealthBar.draw(graphicsNS::FILTER);	// 体力バーを描画
		braveMpBar.draw(graphicsNS::FILTER);
		castleHealthBar.draw(graphicsNS::FILTER);
		// shadow
		char str[128] = "TIME-";
		char time[5] = { 0 };
		sprintf_s(time, "%04d", (int)stage.getRemainingTime());
		strcat_s(str, time);
		fontCK->setFontHeight(40);
		fontCK->setFontColor(SETCOLOR_ARGB(128, 128, 128, 128));  // shadow grey
		fontCK->print(str, 512, 10);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->print(str, 505, 7);
		fontCK->setFontHeight(14);
		if (roundTimer > 0.0f)
		{
			string str1 = "STAGE" + to_string(stage.getStageNum() + 1);
			char str2[128] = "START!";
			float fontSize = 60.0f;
			float fastSpeed = 900.0f;
			float secondSpeed = 50.0f;
			float initX = -fontSize * 6.0f;
			fontCK->setFontHeight((UINT)fontSize);
			float T = (GAME_WIDTH - initX * 2.0f - fontSize * 6) / (2.0f * fastSpeed);
			if (roundTimer > towerDiffenceNS::ROUND_TIME - T)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 400);
			}
			else if (roundTimer > towerDiffenceNS::ROUND_TIME - T * 2.0f)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 400);
			}
			else
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 400);
			}
		}
	}
	if (stage.getRoundOver())
	{
		result.draw();
		if (result.getY() > 50)
		{
			char str[128] = "CONTINUE?";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(result.getHeight() + result.getY()));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(result.getHeight() + result.getY() - 3));
			char str2[128] = "PUSH Z KEY : RETRY STAGE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55));
			char str3[128] = "PUSH X KEY : RETURN TITLE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55 * 2));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55 * 2));
			char str4[128] = "PUSH E KEY : EXIT";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55 * 3));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55 * 3));
		}
	}
	else if (stage.getClearedStage())
	{
		stageClear.draw();
		if (stageClear.getY() < 250)
		{
			char str[128] = "CONTINUE?";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(stageClear.getHeight() + stageClear.getY()));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3));
			char str2[128] = "PUSH Z KEY : RETRY STAGE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55));
			char str3[128] = "PUSH X KEY : RETURN TITLE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55 * 2));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55 * 2));
			char str4[128] = "PUSH E KEY : EXIT";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55 * 3));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55 * 3));
		}
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
	stageSelectTexture.onLostDevice();
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
	stageSelectTexture.onResetDevice();
	safeOnResetDevice(rect);
	Game::resetAll();
	return;
}


//=============================================================================
// コンソールコマンドを処理
//=============================================================================
void TowerDiffence::consoleCommand()
{
	command = console->getCommand();    // コンソールからのコマンドを取得
	if (command == "")                  // コマンドがない場合
		return;

	if (command == "help")              // 「help」コマンドの場合
	{
		console->print("Console Commands:");
		console->print("fps - toggle display of frames per second");
		console->print("mapobj - display map object data");
		console->print("mapcol - display map collision data");
		console->print("mapdata - display map data");
		return;
	}
	if (command == "fps")
	{
		fpsOn = !fpsOn;                 // フレームレートの表示を切り替える
		if (fpsOn)
			console->print("fps On");
		else
			console->print("fps Off");
	}
	if (command == "mapobj")
	{
		for (int i = 0; i < mapNS::MAP_HEIGHT; ++i)
		{
			string str = "";
			for (int j = 0; j < mapNS::MAP_WIDTH; ++j)
			{
				if (stage.getMap().getMapObj(i, j) >= 0)
				{
					str += " " + to_string(stage.getMap().getMapObj(i, j)) + ",";
				}
				else
				{
					str += to_string(stage.getMap().getMapObj(i, j)) + ",";
				}
			}
			console->print(str);
		}
	}
	if (command == "mapcol")
	{
		for (int i = 0; i < mapNS::MAP_HEIGHT; ++i)
		{
			string str = "";
			for (int j = 0; j < mapNS::MAP_WIDTH; ++j)
			{
				if (stage.getMap().getMapCol(i, j) >= 0)
				{
					str += " " + to_string(stage.getMap().getMapCol(i, j)) + ",";
				}
				else
				{
					str += to_string(stage.getMap().getMapCol(i, j)) + ",";
				}
			}
			console->print(str);
		}
	}
	if (command == "barricade")
	{
		for (int i = 0; i < 8; ++i)
		{
			console->print(to_string(stage.getBarricade(i).getActive()));
		}
	}
	if (command == "enemystate")
	{
		for (int i = 0; i < stage.getEnemyNum(); ++i)
		{
			console->print(to_string(stage.getEnemy(i).getState()));
		}
	}
	if (command == "enemytile")
	{
		for (int i = 0; i < stage.getEnemyNum(); ++i)
		{
			console->print(to_string(stage.getEnemy(i).getTileX()) + "," + to_string(stage.getEnemy(i).getTileY()));
		}
	}
}

//==========================================================
// GameOver時に呼び出す
//==========================================================
void TowerDiffence::gameOver()
{
	audio->stopCue("stage");
	audio->playCue("gameover");
}

//==========================================================
// ステージクリア時に呼び出す
//==========================================================
void TowerDiffence::clearStage()
{
	audio->stopCue("stage");
	audio->playCue("clear");
}

//==========================================================
// 敵のテクスチャを初期化する
//==========================================================
void TowerDiffence::initializeEnemiesTexture()
{
	for (int i = 0; i < stage.getEnemyNum(); i++) {
		if (typeid(stage.getEnemy(i)) == typeid(Enemy))
		{
			if (!stage.getEnemy(i).initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		}
		else if (typeid(stage.getEnemy(i)) == typeid(MidBoss))
		{
			if (!stage.getEnemy(i).initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &midBossTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss"));
		}

		// 雑魚敵の当たり判定用
		if (!stage.getEnemy(i).getAttackCollision().initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	}
	stage.setInitializedEnemies(false);
}