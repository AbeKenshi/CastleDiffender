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
	stageSelectOn = false;
	descriptionOn = false;
	roundOver = false;
	rect = NULL;
	remainingTime = 1500.0f;
	enemyNum = 0;
	enemy = NULL;
	enemyX = NULL;
	enemyY = NULL;
	stageNum = 0;
}

//==========================================================
// デストラクタ
//==========================================================
TowerDiffence::~TowerDiffence()
{
	safeDelete(rect);
	safeDelete(fontCK);
	for (int i = 0; i < enemyNum; ++i)
	{
		safeDelete(enemy[i]);
	}
	safeDeleteArray(enemy);
	safeDeleteArray(enemyX);
	safeDeleteArray(enemyY);
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
	result.setY(-result.getHeight());

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
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// バリケードのテクスチャ
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	if (!hitEffectTexture.initialize(graphics, HIT_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit effect texture"));
	// バリケードの画像
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!barricades[i].initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		barricades[i].setScale(1);
		if (!barricades[i].getHitEffect().initialize(graphics, hitEffectNS::WIDTH, hitEffectNS::HEIGHT, hitEffectNS::TEXTURE_COLS, &hitEffectTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hitEffect"));
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
	brave.setScale(1.5);
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
	if (!attackEffectTexture.initialize(graphics, ATTACK_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect texture"));
	if (!braveAttackCollision.getAttackEffect().initialize(graphics, attackEffectNS::WIDTH, attackEffectNS::HEIGHT, attackEffectNS::TEXTURE_COLS, &attackEffectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect"));

	// 炎のテクスチャ
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!fire.initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));
	fire.setScale(1.5);

	// 雑魚敵のテクスチャ
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	// 中ボスのテクスチャ
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));
	initializeEnemies(stageNum + 1, 1);

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
	if (menuOn)		// メニュー画面表示中にZキーが押されるまではメニュー画面を表示し続ける
	{
		if (input->isKeyDown('Z')) // Zキーでステージ選択画面に以降
		{
			menuOn = false;
			input->clearAll();
			audio->stopCue("title");
			stageSelectOn = true;
			stageNum = 0;

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
			exit(1);
		}
	}
	else if (stageSelectOn)
	{
		if (input->isKeyDown('Z'))	// Zキーでステージ決定
		{
			stageSelectOn = false;
			audio->playCue("stage");
			roundStart();

			rect->setX(rectNS::X);
			rect->setY(rectNS::Y);
			rect->setWidth(rectNS::WIDTH);
			rect->setHeight(rectNS::HEIGHT);
			rect->setBackColor(rectNS::BACK_COLOR);
			rect->reset();
		}
		else if (input->isKeyDown(BRAVE_DOWN_KEY))
		{
			if (stageNum < 3 - 1)
			{
				stageNum += 1;
				rect->setY(rect->getY() + 240);
				rect->reset();
			}
			input->clearAll();
		}
		else if (input->isKeyDown(BRAVE_UP_KEY))
		{
			if (stageNum > 0)
			{
				stageNum -= 1;
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
	else if (roundOver)	// ゲームオーバー中にZが押されたらメニュー画面に戻る、Xが押されたらプログラム終了
	{
		if (result.getY() > 50)
		{
			if (input->isKeyDown('X'))
			{
				menuOn = true;
				input->clearAll();
				audio->stopCue("gameover");
				audio->playCue("title");
				roundStart();
			}
			else if (input->isKeyDown('E'))
			{
				exit(1);
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
	else				// ゲーム中の場合、
	{
		if (roundTimer > 0.0f)
		{
			roundTimer -= frameTime;
			return;
		}
		// FIRE_KEYに対応するキーが押されたら勇者から炎を発射
		if (input->isKeyDown(BRAVE_FIRE_KEY))
			fire.fire(&brave);
		// 勇者の攻撃判定がでている場合はコリジョンを生成して当たり判定をとる
		if (brave.getAttackCollisionFlag())
			braveAttackCollision.attack(brave);
		// それぞれの敵を更新
		for (int i = 0; i < enemyNum; i++) {
			enemy[i]->update(frameTime);
		}
		// 勇者を更新
		brave.update(frameTime);
		// 炎を更新
		fire.update(frameTime);
		// 勇者の攻撃コリジョンを更新
		braveAttackCollision.update(frameTime);
		// 城を更新
		castle.update(frameTime);
		// 勇者のアイコン画像を更新
		braveIcon.update(frameTime);
		// それぞれのバリケードを更新
		for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
		{
			barricades[i].update(frameTime);
		}
		// 敵の数をチェックして、マップ上に存在しなければ新たに生成
		checkCurrentEnemyNum();
		// 残り時間が0ならゲームオーバー
		remainingTime -= frameTime;
		if (remainingTime < 0)
		{
			audio->stopCue("stage");
			audio->playCue("gameover");
			gameOver();
			roundTimer = towerDiffenceNS::ROUND_TIME;
		}
	}
}

//==========================================================
// プレイの新しいラウンドを開始
//==========================================================
void TowerDiffence::roundStart()
{
	map.readMapFile(stageNum + 1);
	// 各バリケードを初期化
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}
	// 初期化
	// マップとバリケードを初期化
	int count = 0;  // バリケードの数数える用
	for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // マップの各行を処理
	{
		map.setY((float)(row*mapNS::TEXTURE_SIZE));       // タイルのYを設定
		for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // マップの各列を処理
		{
			if (map.getMapData(row, col) >= 0)            // タイルが存在する場合
			{
				map.setCurrentFrame(map.getMapData(row, col));                       // タイルのテクスチャを設定
				map.setX((float)(col*mapNS::TEXTURE_SIZE));                    // タイルのXを設定
			}
			if (map.getMapObj(row, col) == 0)
			{
				barricades[count].setX((float)(col*mapNS::TEXTURE_SIZE));								// オブジェクトのXを設定
				barricades[count].setY((float)(row*mapNS::TEXTURE_SIZE));										// オブジェクトのYを設定
				barricades[count].setTileX(col);								// オブジェクトのXを設定
				barricades[count].setTileY(row);										// オブジェクトのYを設定
				if (barricades[count].getX() > -mapNS::TEXTURE_SIZE && barricades[count].getX() < GAME_WIDTH)	// オブジェクトが画面上にあるかどうか
				{
					count++;
				}
			}
		}
	}
	result.setY(-result.getHeight());
	// 勇者を初期化
	brave.reset();
	// 各敵を初期化
	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i]->reset();
		enemy[i]->setX(enemyX[i]);
		enemy[i]->setY(enemyY[i]);
		enemy[i]->initTileXY();
	}
	// 城を初期化
	castle.reset();
	// 炎を初期化
	fire.reset();
	// 残り時間を初期化
	remainingTime = 1500.0f;
	// ゲームオーバーのフラグを初期化
	roundOver = false;
	roundTimer = towerDiffenceNS::ROUND_TIME;
}

//==========================================================
// 敵の数をチェックし、マップ上に敵がいなければ新たに生成
//==========================================================
void TowerDiffence::checkCurrentEnemyNum()
{
	// 雑魚敵が存在したら
	for (int i = 0; i < enemyNum; i++)
	{
		if (enemy[i]->getActive())
			return;
	}

	// 第2波
	for (int i = 0; i < enemyNum; i++)
	{
		safeDelete(enemy[i]);
	}
	safeDeleteArray(enemy);
	safeDeleteArray(enemyX);
	safeDeleteArray(enemyY);
	map.resetMapCol();
	initializeEnemies(1, 2);
}

//==========================================================
// 人工知能
//==========================================================
void TowerDiffence::ai()
{
	// 各敵を更新
	for (int i = 0; i < enemyNum; i++)
		enemy[i]->ai(frameTime, brave);
}

//==========================================================
// 衝突を処理
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;	// 衝突判定したときの衝突相手へのベクトル
	bool braveAttackCollidesWithAnyEnemy = false;
	// 各敵について衝突判定
	for (int i = 0; i < enemyNum; i++) {
		// プレイヤーの攻撃コリジョンと雑魚敵の衝突の場合
		if (braveAttackCollision.collidesWith(*enemy[i], collisionVector))
		{
			// 敵にダメージを与える
			enemy[i]->damage(BRAVE_ATTACK);
			// いずれかの敵に攻撃があたったのでループを抜けた後に攻撃コリジョンをなくす
			braveAttackCollidesWithAnyEnemy = true;
		}

		if (enemy[i]->getState() == characterNS::DEATH)
		{
			continue;
		}

		// 敵が攻撃時は、城とプレイヤーとバリケードとの当たり判定をそれぞれチェック
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
			// 敵の攻撃コリジョンとプレイヤーの衝突の場合
			if (enemy[i]->getAttackCollision().collidesWith(brave, collisionVector))
			{
				// プレイヤーにダメージを与える
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) brave.setDamagePer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) brave.setDamagePer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) brave.setDamagePer(1.1f);
				brave.damage(ENEMY_ATTACK);
				// 敵の攻撃コリジョンをなくす
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
			}
			// 敵の攻撃コリジョンと城の衝突の場合
			if (enemy[i]->getAttackCollision().collidesWith(castle, collisionVector))
			{
				// 城にダメージを与える
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) castle.setDamagePer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) castle.setDamagePer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) castle.setDamagePer(1.1f);
				castle.damage(ENEMY_ATTACK);
				// 敵の攻撃コリジョンをなくす
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
			}
			// 敵の攻撃コリジョンとバリケードの衝突の場合
			if (enemy[i]->getAttackCollision().collidesWith(barricades[enemy[i]->getNearBarricadeIndex()], collisionVector)) {
				// バリケードにダメージを与える（barricades[enemy[i].getNearBarricadeIndex()]が攻撃対象になるはず）
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.1f);
				barricades[enemy[i]->getNearBarricadeIndex()].damage(ENEMY_ATTACK);
				// 敵の攻撃コリジョンをなくす
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
				// 攻撃されたバリケードが破壊された場合、
				if (!barricades[enemy[i]->getNearBarricadeIndex()].getActive())
				{
					// マップデータを更新
					map.updateMapObjInt(barricades[enemy[i]->getNearBarricadeIndex()].getTileY(), barricades[enemy[i]->getNearBarricadeIndex()].getTileX(), -1);
					if (map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 + 1) != 0 
						&& map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 + 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY(), barricades[enemy[i]->getNearBarricadeIndex()].getX() + 32, -1);
					}
					if (map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 - 1) != 0 
						&& map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 - 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY(), barricades[enemy[i]->getNearBarricadeIndex()].getX() - 32, -1);
					}
					if (map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 + 1, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0 
						&& map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 + 1, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() + 32, barricades[enemy[i]->getNearBarricadeIndex()].getX(), -1);
					}
					if (map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 - 1, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0 
						&& map.getMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 - 1, barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() - 32, barricades[enemy[i]->getNearBarricadeIndex()].getX(), -1);
					}
				}
			}
		}

		// 炎と雑魚敵の衝突の場合
		if (fire.collidesWith(*enemy[i], collisionVector))
		{
			enemy[i]->damage(FIRE);
			fire.setVisible(false);
			fire.setActive(false);
		}

		// 攻撃中ならば行動選択は行わない
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
		}
		else if (enemy[i]->collidesWith(brave, collisionVector))// 雑魚敵とプレイヤーが衝突している場合、
		{
			// 敵の状態を勇者攻撃状態に変更
			enemy[i]->setAttackState(enemyNS::ATTACK_BRAVE);
			// 勇者がいる方向に応じて攻撃する方向を変更
			enemy[i]->changeAttack(collisionVector);
		}
		else if (map.getMapObj(enemy[i]->getTileY(), enemy[i]->getTileX()) == 1)	// 雑魚敵と城が衝突していたら攻撃、
		{
			// 城がある方向に応じて攻撃する方向を変更
			if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() + 1) == 2)
			{
				enemy[i]->changeAttack(characterNS::RIGHT);
			}
			else if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() - 1) == 2)
			{
				enemy[i]->changeAttack(characterNS::LEFT);
			}
			else if (map.getMapCol(enemy[i]->getTileY() + 1, enemy[i]->getTileX()) == 2)
			{
				enemy[i]->changeAttack(characterNS::DOWN);
			}
			else if (map.getMapCol(enemy[i]->getTileY() - 1, enemy[i]->getTileX()) == 2)
			{
				enemy[i]->changeAttack(characterNS::UP);
			}
			// 敵の状態を城攻撃状態に変更
			enemy[i]->setAttackState(enemyNS::ATTACK_CASTLE);
		}
		else if (map.getMapObj(enemy[i]->getTileY(), enemy[i]->getTileX()) == -2)	// 最近接のバリケードに衝突していたら攻撃
		{
			// バリケードがある方向に応じて攻撃する方向を変更
			if (enemy[i]->getTileX() < (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32)
				enemy[i]->changeAttack(characterNS::RIGHT);
			else if (enemy[i]->getTileX() > (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32)
				enemy[i]->changeAttack(characterNS::LEFT);
			else if (enemy[i]->getTileY() < (int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32)
				enemy[i]->changeAttack(characterNS::DOWN);
			else if (enemy[i]->getTileY() > (int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32)
				enemy[i]->changeAttack(characterNS::UP);
			else
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error enemy and barricades"));
			// 敵の状態をバリケード攻撃状態に変更
			enemy[i]->setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else if (enemy[i]->canMakeDecesionMoving())	// 敵が方向転換可能な状態にあるとき、意思決定を行い進む方向を決める
		{
			bool changeGoalDirectionFlag = false;	// 進みたい方向を変える必要があるかどうか
			if (rand() % 3 == 0)
			{
				enemy[i]->setStateDetail(enemyNS::MOVE_CASTLE);
				enemy[i]->setState(characterNS::MOVE);
				enemy[i]->setGoalDirection((characterNS::DIRECTION) (rand() % 4));
				switch (enemy[i]->getGoalDirection())
				{
				case characterNS::LEFT:
					if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() - 1) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::RIGHT:
					if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() + 1) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::UP:
					if (map.getMapCol(enemy[i]->getTileY() - 1, enemy[i]->getTileX()) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::DOWN:
					if (map.getMapCol(enemy[i]->getTileY() + 1, enemy[i]->getTileX()) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				}
				// 進みたい方向に進めない場合、ランダムに方向を決めなおす
				if (changeGoalDirectionFlag)
				{
					// ランダムに進みたい方向を修正
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// それでも進めない場合、敵を待機状態にして静止させる
					if (enemy[i]->canMoveTo(newDirection))
					{
						enemy[i]->setGoalDirection(newDirection);
					}
					else
					{
						enemy[i]->setState(characterNS::WAIT);
						enemy[i]->setStateDetail(enemyNS::WAIT);
					}
				}
			}
			else
			{
				// 最近接のバリケードを探索
				enemy[i]->searchNearBarricadeIndex();
				if (!enemy[i]->checkBarricadeOnLine())	// 城までの直線上にバリケードがない場合、城へと進行する
				{
					// 敵の状態を城移動中へと変更
					enemy[i]->setStateDetail(enemyNS::MOVE_CASTLE);
					enemy[i]->setState(characterNS::MOVE);
					// 進みたい方向に進めない場合、方向を進みたい方向をランダムに変換
					switch (enemy[i]->getGoalDirection())
					{
					case characterNS::LEFT:
						if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() - 1) >= 1)
						{
							changeGoalDirectionFlag = true;
						}
						break;
					case characterNS::RIGHT:
						if (map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() + 1) >= 1)
						{
							changeGoalDirectionFlag = true;
						}
						break;
					case characterNS::UP:
						if (map.getMapCol(enemy[i]->getTileY() - 1, enemy[i]->getTileX()) >= 1)
						{
							changeGoalDirectionFlag = true;
						}
						break;
					case characterNS::DOWN:
						if (map.getMapCol(enemy[i]->getTileY() + 1, enemy[i]->getTileX()) >= 1)
						{
							changeGoalDirectionFlag = true;
						}
						break;
					}
				}
				else // 城までの直線状にバリケードが存在する場合、
				{
					// 敵の状態をバリケードに進行中へと変更
					enemy[i]->setStateDetail(enemyNS::MOVE_BARRICADE);
					enemy[i]->setState(characterNS::MOVE);
					// 確率50%でx方向に進むかどうかを先に決定し、そのあとにy方向に進むかどうかを決定
					bool canMoveXDirection = false;
					bool canMoveYDirection = false;
					characterNS::DIRECTION xDirection;
					characterNS::DIRECTION yDirection;
					if ((int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 < enemy[i]->getTileX())
					{
						if (!map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() - 1) >= 1)
						{
							xDirection = characterNS::LEFT;
							enemy[i]->setGoalDirection(characterNS::LEFT);
							canMoveXDirection = true;
						}
						else
							changeGoalDirectionFlag = true;
					}
					else if ((int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 > enemy[i]->getTileX())
					{
						if (!map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() + 1) >= 1)
						{
							xDirection = characterNS::RIGHT;
							enemy[i]->setGoalDirection(characterNS::RIGHT);
							canMoveXDirection = true;
						}
						else
							changeGoalDirectionFlag = true;
					}
					if ((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 < enemy[i]->getTileY())
					{
						if (!map.getMapCol(enemy[i]->getTileY() - 1, enemy[i]->getTileX()) >= 1)
						{
							yDirection = characterNS::UP;
							enemy[i]->setGoalDirection(characterNS::UP);
							canMoveYDirection = true;
						}
						else
							changeGoalDirectionFlag = true;
					}
					else if ((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 > enemy[i]->getTileY())
					{
						if (!map.getMapCol(enemy[i]->getTileY() + 1, enemy[i]->getTileX()) >= 1)
						{
							yDirection = characterNS::DOWN;
							enemy[i]->setGoalDirection(characterNS::DOWN);
							canMoveYDirection = true;
						}
						else
							changeGoalDirectionFlag = true;
					}
					if (canMoveXDirection && canMoveYDirection)
					{
						if (rand() % 2 == 0)
							enemy[i]->setGoalDirection(xDirection);
						else
							enemy[i]->setGoalDirection(yDirection);
					}
				}
				// 進みたい方向に進めない場合、ランダムに方向を決めなおす
				if (changeGoalDirectionFlag)
				{
					// ランダムに進みたい方向を修正
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// それでも進めない場合、敵を待機状態にして静止させる
					if (enemy[i]->canMoveTo(newDirection))
					{
						enemy[i]->setGoalDirection(newDirection);
					}
					else
					{
						enemy[i]->setState(characterNS::WAIT);
						enemy[i]->setStateDetail(enemyNS::WAIT);
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		// プレイヤーの攻撃コリジョンとの衝突の場合
		if (braveAttackCollision.collidesWith(barricades[i], collisionVector))
		{
			// バリケードにダメージを与える
			barricades[i].damage(BRAVE_ATTACK);
			// いずれかのバリケードに攻撃があたったのでループを抜けた後に攻撃コリジョンをなくす
			braveAttackCollidesWithAnyEnemy = true;
		}
	}

	// 勇者の攻撃がいずれかの敵に当たった場合、攻撃コリジョンをなくす
	if (braveAttackCollidesWithAnyEnemy)
	{
		braveAttackCollision.setVisible(false);
		braveAttackCollision.setActive(false);
	}

	// 死亡チェック
	if ((castle.isDeath() || brave.getActive() == false) && !roundOver)
	{
		audio->stopCue("stage");
		audio->playCue("gameover");
		gameOver();
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

		char str[128]  = "PUSH Z KEY : STAGE SELECT";
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
			map.setY((float)(row*mapNS::TEXTURE_SIZE));       // タイルのYを設定
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // マップの各列を処理
			{
				if (map.getMapData(row, col) >= 0)            // タイルが存在する場合
				{
					map.setCurrentFrame(map.getMapData(row, col));                       // タイルのテクスチャを設定
					map.setX((float)(col*mapNS::TEXTURE_SIZE));                    // タイルのXを設定
					if (map.getX() > -mapNS::TEXTURE_SIZE && map.getX() < GAME_WIDTH)     // タイルが画面上にあるかどうか
						map.draw();    // タイルを描画
				}
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			barricades[i].draw();   // オブジェクトを描画
			barricades[i].getHitEffect().draw();
		}

		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始

		for (int i = 0; i < enemyNum; i++) {
			float tmpX = enemy[i]->getX();
			float tmpY = enemy[i]->getY();
			enemy[i]->setX(tmpX - enemy[i]->getWidth() * (enemy[i]->getScale() - 1) / 2.0);
			enemy[i]->setY(tmpY - enemy[i]->getHeight() * (enemy[i]->getScale() - 1) / 2.0 - 10);
			// 敵の描画、色は適当に分けてる、色によって能力値を分ける
			if (i % 3 == 0) {
				enemy[i]->draw(graphicsNS::WHITE);
				enemy[i]->setEnemyType(enemyNS::NORMAL);
			}
			else if (i % 3 == 1) {
				enemy[i]->draw(graphicsNS::RED);
				enemy[i]->setEnemyType(enemyNS::RED);
			}
			else if (i % 3 == 2) {
				enemy[i]->draw(graphicsNS::BLUE);
				enemy[i]->setEnemyType(enemyNS::BLUE);
			}
			enemy[i]->getAttackCollision().draw();
			enemy[i]->setX(tmpX);
			enemy[i]->setY(tmpY);
		}
		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		castle.draw();
		fire.draw();
		float tmpX = brave.getX();
		float tmpY = brave.getY();
		brave.setX(tmpX - brave.getWidth() * (brave.getScale() - 1) / 2.0);
		brave.setY(tmpY - brave.getHeight() * (brave.getScale() - 1) / 2.0 - 10);
		brave.draw(graphicsNS::WHITE);
		brave.setX(tmpX);
		brave.setY(tmpY);
		braveAttackCollision.draw();
		braveAttackCollision.getAttackEffect().draw();
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
		if (roundTimer > 0.0f)
		{
			string str1 = "STAGE" + to_string(stageNum + 1);
			char str2[128] = "START!";
			float fontSize = 60.0f;
			float fastSpeed = 900.0f;
			float secondSpeed = 50.0f;
			float initX = -fontSize * 6.0f;
			fontCK->setFontHeight(fontSize);
			float T = (GAME_WIDTH - initX * 2.0f - fontSize * 6) / (2.0f * fastSpeed);
			if (roundTimer > towerDiffenceNS::ROUND_TIME - T)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed, 303);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed, 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed, 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed, 400);
			}
			else if (roundTimer > towerDiffenceNS::ROUND_TIME - T * 2.0f)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T, 303);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T, 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T, 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T, 400);
			}
			else 
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T , 303);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T, 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T, 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T, 400);
			}
		}
	}
	if (roundOver)
	{
		result.draw();
		if (result.getY() > 50)
		{
			char str[128] = "CONTINUE?";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str, GAME_WIDTH / 2 - 35 * 9 / 2, result.getHeight() + result.getY());
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str, GAME_WIDTH / 2 - 35 * 9 / 2, result.getHeight() + result.getY() - 3);
			char str2[128] = "PUSH Z KEY : RETRY STAGE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str2, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() + 55);
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str2, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() - 3 + 55);
			char str3[128] = "PUSH X KEY : RETURN TITLE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str3, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() + 55 * 2);
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str3, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() - 3 + 55 * 2);
			char str4[128] = "PUSH E KEY : EXIT";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // 影
			fontCK->print(str4, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() + 55 * 3);
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str4, GAME_WIDTH / 2 - 35 * 20 / 2, result.getHeight() + result.getY() - 3 + 55 * 3);
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

//==========================================================
// 指定されたステージの敵データを読み込む
//==========================================================
void TowerDiffence::readEnemyFile(int stageNum, int enemyWave)
{
	string enemyDataFilename = "stageData\\stage" + std::to_string(stageNum) + "\\enemy" + std::to_string(enemyWave) + "\\enemydata.csv";

	ifstream* ifs = new ifstream(enemyDataFilename);
	//csvファイルを1行ずつ読み込む
	string str;
	if (getline(*ifs, str))
	{
		string token;
		istringstream stream(str);
		if (getline(stream, token, ','))
		{
			enemyNum = (int)stof(token);
			enemy = new Enemy*[enemyNum];
			enemyX = new float[enemyNum];
			enemyY = new float[enemyNum];
		}
	}
	if (getline(*ifs, str)) 
	{
		string token;
		istringstream stream(str);
		for (int i = 0; i < enemyNum; ++i)
		{
			if (getline(stream, token, ','))
			{
				if ((int)stof(token) == 1)
					enemy[i] = new Enemy();
				else if ((int)stof(token) == 2)
					enemy[i] = new MidBoss();
			}
		}
	}
	if (getline(*ifs, str))
	{
		string token;
		istringstream stream(str);
		for (int i = 0; i < enemyNum; ++i)
		{
			if (getline(stream, token, ','))
			{
				enemyX[i] = stof(token);
			}
		}
	}
	if (getline(*ifs, str))
	{
		string token;
		istringstream stream(str);
		for (int i = 0; i < enemyNum; ++i)
		{
			if (getline(stream, token, ','))
			{
				enemyY[i] = stof(token);
			}
		}
	}

	safeDelete(ifs);
}

//==========================================================
// 指定されたステージ、派の敵データを読み込み敵を初期化する
//==========================================================
void TowerDiffence::initializeEnemies(int stageNum, int enemyWave)
{
	readEnemyFile(stageNum, enemyWave);
	for (int i = 0; i < enemyNum; i++) {
		if (typeid(*enemy[i]) == typeid(Enemy))
		{
			if (!enemy[i]->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		}
		else if (typeid(*enemy[i]) == typeid(MidBoss))
		{
			if (!enemy[i]->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &midBossTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss"));
		}
		enemy[i]->setScale(1.5);
		enemy[i]->setMapPointer(&map);
		enemy[i]->setBarricadesPointer(barricades);

		// 雑魚敵の当たり判定用
		if (!enemy[i]->getAttackCollision().initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
		enemy[i]->reset();
		enemy[i]->setX(enemyX[i]);
		enemy[i]->setY(enemyY[i]);
		enemy[i]->initTileXY();
	}
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
				if (map.getMapObj(i, j) >= 0)
				{
					str += " " + to_string(map.getMapObj(i, j)) + ",";
				}
				else
				{
					str += to_string(map.getMapObj(i, j)) + ",";
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
				if (map.getMapCol(i, j) >= 0)
				{
					str += " " + to_string(map.getMapCol(i, j)) + ",";
				}
				else
				{
					str += to_string(map.getMapCol(i, j)) + ",";
				}
			}
			console->print(str);
		}
	}
	if (command == "barricade")
	{
		for (int i = 0; i < 8; ++i)
		{
			console->print(to_string(barricades[i].getActive()));
		}
	}
	if (command == "enemystate")
	{
		for (int i = 0; i < enemyNum; ++i)
		{
			console->print(to_string(enemy[i]->getState()));
		}
	}
	if (command == "enemytile")
	{
		for (int i = 0; i < enemyNum; ++i)
		{
			console->print(to_string(enemy[i]->getTileX()) + "," + to_string(enemy[i]->getTileY()));
		}
	}
}

//==========================================================
// GameOver時に呼び出す
//==========================================================
void TowerDiffence::gameOver()
{
	roundOver = true;
}