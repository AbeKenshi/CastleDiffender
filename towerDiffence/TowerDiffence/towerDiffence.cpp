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
	brave.setScale(1.0);
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
	// 中ボスの当たり判定用
	if (!midBossAttackCollision.initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
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
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
		if (!enemy[i].initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		enemy[i].setScale(1.0);
		enemy[i].setMapPointer(&map);
		enemy[i].setBarricadesPointer(barricades);

		// 雑魚敵の当たり判定用
		if (!enemyAttackCollision[i].initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	}
	// 中ボス
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));
	if (!midBoss.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &midBossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss"));
	midBoss.setScale(1.0);
	midBoss.setMapPointer(&map);
	midBoss.setBarricadesPointer(barricades);
	// 雑魚敵の当たり判定用
	if (!midBossAttackCollision.initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));

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

	// 敵の位置初期化
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].setX(enemyNS::X[i]);
		enemy[i].setY(enemyNS::Y[i]);
	}

	return;
}

//==========================================================
// すべてのゲームアイテムを更新
//==========================================================
void TowerDiffence::update()
{
	if (menuOn)		// メニュー画面表示中にいずれかのキーが押されるまではメニュー画面を表示し続ける
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
	else if (roundOver)	// ゲームオーバー中にZが押されたらメニュー画面に戻る、Xが押されたらプログラム終了
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
	else				// ゲーム中の場合、
	{
		// FIRE_KEYに対応するキーが押されたら勇者から炎を発射
		if (input->isKeyDown(BRAVE_FIRE_KEY))
			fire.fire(&brave);
		// 勇者の攻撃判定がでている場合はコリジョンを生成して当たり判定をとる
		if (brave.getAttackCollisionFlag())
			braveAttackCollision.attack(&brave);
		// それぞれの敵を更新
		for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
			if (enemy[i].getAttackCollisionFlag()) {
				enemyAttackCollision[i].attack(&enemy[i]);
			}
			enemy[i].update(frameTime);
			enemyAttackCollision[i].update(frameTime);
		}
		if (midBoss.getAttackCollisionFlag())
			midBossAttackCollision.attack(&midBoss);
		midBoss.update(frameTime);
		midBossAttackCollision.update(frameTime);
		// 勇者を更新
		brave.update(frameTime);
		// 炎を更新
		fire.update(frameTime);
		// 勇者の攻撃コリジョンを更新
		braveAttackCollision.update(frameTime);
		// 敵の攻撃コリジョンを更新
		midBossAttackCollision.update(frameTime);
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
			if (map.getMapObj(row, col) >= 0)
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
	// 勇者を初期化
	brave.reset();
	// 各敵を初期化
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].reset();
		enemy[i].setX(enemyNS::X[i]);
		enemy[i].setY(enemyNS::Y[i]);
		enemy[i].initTileXY();
	}
	// 中ボスを初期化
	midBoss.reset();
	midBoss.setX(GAME_WIDTH / 2 - 500);
	midBoss.setY(GAME_HEIGHT / 2 - 80);
	midBoss.initTileXY();
	// 城を初期化
	castle.reset();
	// 炎を初期化
	fire.reset();
	// 各バリケードを初期化
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}
	// 残り時間を初期化
	remainingTime = 1500.0f;
	// ゲームオーバーのフラグを初期化
	roundOver = false;
}

//==========================================================
// 敵の数をチェックし、マップ上に敵がいなければ新たに生成
//==========================================================
void TowerDiffence::checkCurrentEnemyNum()
{
	// 雑魚敵が存在したら
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		if (enemy[i].getActive())
			return;
	}

	// 中ボスが存在したら
	if (midBoss.getActive())
		return;

	// 敵が存在していないため全て初期化
	// 雑魚敵の初期化
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].reset();
		// 位置はランダム
		if (i % 4 == 0) // 左上
		{
			enemy[i].setX(rand() % 200);
			enemy[i].setY(rand() % 200);
		}
		else if (i % 4 == 1) // 右上
		{
			enemy[i].setX(GAME_WIDTH - (rand() % 200));
			enemy[i].setY(rand()% 200);
		}
		else if (i % 4 == 2) // 左下
		{
			enemy[i].setX(rand() % 200);
			enemy[i].setY(GAME_HEIGHT - (rand() % 200));
		}
		else if (i % 4 == 3) // 右下
		{
			enemy[i].setX(GAME_WIDTH - (rand() % 200));
			enemy[i].setY(GAME_HEIGHT - (rand() % 200));
		}
		enemy[i].setActive(true);
	}

	// 中ボスの初期化
	midBoss.setX(GAME_WIDTH / 2 - 600);
	midBoss.setY(GAME_HEIGHT / 2 - 80);
	midBoss.reset();
	midBoss.setActive(true);
}

//==========================================================
// 人工知能
//==========================================================
void TowerDiffence::ai()
{
	// 各敵を更新
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
		enemy[i].ai(frameTime, brave);
	// 中ボスを更新
	midBoss.ai(frameTime, brave);
}

//==========================================================
// 衝突を処理
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;	// 衝突判定したときの衝突相手へのベクトル
	bool braveAttackCollidesWithAnyEnemy = false;
	// 各敵について衝突判定
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {

		// プレイヤーの攻撃コリジョンと雑魚敵の衝突の場合
		if (braveAttackCollision.collidesWith(enemy[i], collisionVector))
		{
			// 敵にダメージを与える
			enemy[i].damage(BRAVE_ATTACK);
			// いずれかの敵に攻撃があたったのでループを抜けた後に攻撃コリジョンをなくす
			braveAttackCollidesWithAnyEnemy = true;
		}

		// 敵が攻撃時は、城とプレイヤーとバリケードとの当たり判定をそれぞれチェック
		if (enemy[i].getState() == characterNS::ATTACK)
		{
			// 敵の攻撃コリジョンとプレイヤーの衝突の場合
			if (enemyAttackCollision[i].collidesWith(brave, collisionVector))
			{
				// プレイヤーにダメージを与える
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) brave.setDamagePer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) brave.setDamagePer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) brave.setDamagePer(1.1f);
				brave.damage(ENEMY_ATTACK);
				// 敵の攻撃コリジョンをなくす
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// 敵の攻撃コリジョンと城の衝突の場合
			if (enemyAttackCollision[i].collidesWith(castle, collisionVector))
			{
				// 城にダメージを与える
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) castle.setDamagePer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) castle.setDamagePer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) castle.setDamagePer(1.1f);
				castle.damage(ENEMY_ATTACK);
				// 敵の攻撃コリジョンをなくす
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// 敵の攻撃コリジョンとバリケードの衝突の場合
			if (enemyAttackCollision[i].collidesWith(barricades[enemy[i].getNearBarricadeIndex()], collisionVector)) {
				// バリケードにダメージを与える（barricades[enemy[i].getNearBarricadeIndex()]が攻撃対象になるはず）
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.1f);
				barricades[enemy[i].getNearBarricadeIndex()].damage();
				// 敵の攻撃コリジョンをなくす
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
				// 攻撃されたバリケードが破壊された場合、
				if (!barricades[enemy[i].getNearBarricadeIndex()].getActive())
				{
					// マップデータを更新
					map.updateMapObjInt(barricades[enemy[i].getNearBarricadeIndex()].getTileY(), barricades[enemy[i].getNearBarricadeIndex()].getTileX(), 1);
					if (map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 + 1) != 0 && map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 + 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY(), barricades[enemy[i].getNearBarricadeIndex()].getX() + 32, -1);
					}
					if (map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 - 1) != 0 && map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 - 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY(), barricades[enemy[i].getNearBarricadeIndex()].getX() - 32, -1);
					}
					if (map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 + 1, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32) != 0 && map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 + 1, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32) != 1)
					{
						map.updateMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() + 32, barricades[enemy[i].getNearBarricadeIndex()].getX(), -1);
					}
					if (map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 - 1, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32) != 0 && map.getMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 - 1, barricades[enemy[i].getNearBarricadeIndex()].getX() / 32) != 0)
					{
						map.updateMapObj(barricades[enemy[i].getNearBarricadeIndex()].getY() - 32, barricades[enemy[i].getNearBarricadeIndex()].getX(), -1);
					}
				}
			}
		}

		// 炎と雑魚敵の衝突の場合
		if (fire.collidesWith(enemy[i], collisionVector))
		{
			enemy[i].damage(FIRE);
			fire.setVisible(false);
			fire.setActive(false);
		}

		// 攻撃中ならば行動選択は行わない
		if (enemy[i].getState() == characterNS::ATTACK)
		{
		}
		else if (enemy[i].collidesWith(brave, collisionVector))// 雑魚敵とプレイヤーが衝突している場合、
		{
			// 敵の状態を勇者攻撃状態に変更
			enemy[i].setAttackState(enemyNS::ATTACK_BRAVE);
			// 勇者がいる方向に応じて攻撃する方向を変更
			enemy[i].changeAttack(collisionVector);
		}
		else if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX()) == -1)	// 雑魚敵と城が衝突していたら攻撃、
		{
			// 城がある方向に応じて攻撃する方向を変更
			if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) == 2)
			{
				enemy[i].changeAttack(characterNS::RIGHT);
			}
			else if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) == 2)
			{
				enemy[i].changeAttack(characterNS::LEFT);
			}
			else if (map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) == 2)
			{
				enemy[i].changeAttack(characterNS::DOWN);
			}
			else if (map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) == 2)
			{
				enemy[i].changeAttack(characterNS::UP);
			}
			// 敵の状態を城攻撃状態に変更
			enemy[i].setAttackState(enemyNS::ATTACK_CASTLE);
		}
		else if (map.getMapObj(enemy[i].getTileY(), enemy[i].getTileX()) == -2)	// 最近接のバリケードに衝突していたら攻撃
		{
			// バリケードがある方向に応じて攻撃する方向を変更
			if (enemy[i].getTileX() < (int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32)
				enemy[i].changeAttack(characterNS::RIGHT);
			else if (enemy[i].getTileX() > (int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32)
				enemy[i].changeAttack(characterNS::LEFT);
			else if (enemy[i].getTileY() < (int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32)
				enemy[i].changeAttack(characterNS::DOWN);
			else if (enemy[i].getTileY() > (int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32)
				enemy[i].changeAttack(characterNS::UP);
			else
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error enemy and barricades"));
			// 敵の状態をバリケード攻撃状態に変更
			enemy[i].setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else if (enemy[i].canMakeDecesionMoving())	// 敵が方向転換可能な状態にあるとき、意思決定を行い進む方向を決める
		{
			bool changeGoalDirectionFlag = false;	// 進みたい方向を変える必要があるかどうか
			// 最近接のバリケードを探索
			enemy[i].searchNearBarricadeIndex();
			if (!enemy[i].checkBarricadeOnLine())	// 城までの直線上にバリケードがない場合、城へと進行する
			{
				// 敵の状態を城移動中へと変更
				enemy[i].setStateDetail(enemyNS::MOVE_CASTLE);
				enemy[i].setState(characterNS::MOVE);
				// 進みたい方向に進めない場合、方向を進みたい方向をランダムに変換
				switch (enemy[i].getGoalDirection())
				{
				case characterNS::LEFT:
					if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::RIGHT:
					if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::UP:
					if (map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				case characterNS::DOWN:
					if (map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) >= 1)
					{
						changeGoalDirectionFlag = true;
					}
					break;
				}
			}
			else // 城までの直線状にバリケードが存在する場合、
			{
				// 敵の状態をバリケードに進行中へと変更
				enemy[i].setStateDetail(enemyNS::MOVE_BARRICADE);
				enemy[i].setState(characterNS::MOVE);
				// 確率50%でx方向に進むかどうかを先に決定し、そのあとにy方向に進むかどうかを決定
				bool canMoveXDirection = false;
				bool canMoveYDirection = false;
				characterNS::DIRECTION xDirection;
				characterNS::DIRECTION yDirection;
				if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 < enemy[i].getTileX())
				{
					if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) >= 1)
					{
						xDirection = characterNS::LEFT;
						enemy[i].setGoalDirection(characterNS::LEFT);
						canMoveXDirection = true;
					}
					else
						changeGoalDirectionFlag = true;
				}
				else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 > enemy[i].getTileX())
				{
					if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) >= 1)
					{
						xDirection = characterNS::RIGHT;
						enemy[i].setGoalDirection(characterNS::RIGHT);
						canMoveXDirection = true;
					}
					else
						changeGoalDirectionFlag = true;
				}
				if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 < enemy[i].getTileY())
				{
					if (!map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) >= 1)
					{
						yDirection = characterNS::UP;
						enemy[i].setGoalDirection(characterNS::UP);
						canMoveYDirection = true;
					}
					else
						changeGoalDirectionFlag = true;
				}
				else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 > enemy[i].getTileY())
				{
					if (!map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) >= 1)
					{
						yDirection = characterNS::DOWN;
						enemy[i].setGoalDirection(characterNS::DOWN);
						canMoveYDirection = true;
					}
					else
						changeGoalDirectionFlag = true;
				}
				if (canMoveXDirection && canMoveYDirection)
				{
					if (rand() % 2 == 0)
						enemy[i].setGoalDirection(xDirection);
					else
						enemy[i].setGoalDirection(yDirection);
				}
				// 進みたい方向に進めない場合、ランダムに方向を決めなおす
				if (changeGoalDirectionFlag)
				{
					// ランダムに進みたい方向を修正
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// それでも進めない場合、敵を待機状態にして静止させる
					if (enemy[i].canMoveTo(newDirection))
					{
						enemy[i].setGoalDirection(newDirection);
					}
					else
					{
						enemy[i].setState(characterNS::WAIT);
						enemy[i].setStateDetail(enemyNS::WAIT);
					}
				}
			}
		}
	}
	// プレイヤーの攻撃コリジョンと雑魚敵の衝突の場合
	if (braveAttackCollision.collidesWith(midBoss, collisionVector))
	{
		// 敵にダメージを与える
		midBoss.damage(BRAVE_ATTACK);
		// いずれかの敵に攻撃があたったのでループを抜けた後に攻撃コリジョンをなくす
		braveAttackCollidesWithAnyEnemy = true;
	}

	// 敵が攻撃時は、城とプレイヤーとバリケードとの当たり判定をそれぞれチェック
	if (midBoss.getState() == characterNS::ATTACK)
	{
		// 敵の攻撃コリジョンとプレイヤーの衝突の場合
		if (midBossAttackCollision.collidesWith(brave, collisionVector))
		{
			// プレイヤーにダメージを与える
			brave.setDamagePer(1.5f);
			brave.damage(ENEMY_ATTACK);
			// 敵の攻撃コリジョンをなくす
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
		// 敵の攻撃コリジョンと城の衝突の場合
		if (midBossAttackCollision.collidesWith(castle, collisionVector))
		{
			// 城にダメージを与える
			castle.setDamagePer(1.5f);
			castle.damage(ENEMY_ATTACK);
			// 敵の攻撃コリジョンをなくす
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
		// 敵の攻撃コリジョンとバリケードの衝突の場合
		if (midBossAttackCollision.collidesWith(barricades[midBoss.getNearBarricadeIndex()], collisionVector)) {
			// バリケードにダメージを与える（barricades[enemy[i].getNearBarricadeIndex()]が攻撃対象になるはず）
			barricades[midBoss.getNearBarricadeIndex()].damage();
			// 敵の攻撃コリジョンをなくす
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
			// 攻撃されたバリケードが破壊された場合、
			if (!barricades[midBoss.getNearBarricadeIndex()].getActive())
			{
				// マップデータを更新
				map.updateMapObjInt(barricades[midBoss.getNearBarricadeIndex()].getTileY(), barricades[midBoss.getNearBarricadeIndex()].getTileX(), 1);
				if (map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32, barricades[midBoss.getNearBarricadeIndex()].getX() / 32 + 1) != 0 
					&& map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32, barricades[midBoss.getNearBarricadeIndex()].getX() / 32 + 1) != 1)
				{
					map.updateMapObj(barricades[midBoss.getNearBarricadeIndex()].getY(), barricades[midBoss.getNearBarricadeIndex()].getX() + 32, -1);
				}
				if (map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32, barricades[midBoss.getNearBarricadeIndex()].getX() / 32 - 1) != 0 
					&& map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32, barricades[midBoss.getNearBarricadeIndex()].getX() / 32 - 1) != 1)
				{
					map.updateMapObj(barricades[midBoss.getNearBarricadeIndex()].getY(), barricades[midBoss.getNearBarricadeIndex()].getX() - 32, -1);
				}
				if (map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32 + 1, barricades[midBoss.getNearBarricadeIndex()].getX() / 32) != 0 
					&& map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32 + 1, barricades[midBoss.getNearBarricadeIndex()].getX() / 32) != 1)
				{
					map.updateMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() + 32, barricades[midBoss.getNearBarricadeIndex()].getX(), -1);
				}
				if (map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32 - 1, barricades[midBoss.getNearBarricadeIndex()].getX() / 32) != 0 
					&& map.getMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() / 32 - 1, barricades[midBoss.getNearBarricadeIndex()].getX() / 32) != 0)
				{
					map.updateMapObj(barricades[midBoss.getNearBarricadeIndex()].getY() - 32, barricades[midBoss.getNearBarricadeIndex()].getX(), -1);
				}
			}
		}
	}

	// 炎と雑魚敵の衝突の場合
	if (fire.collidesWith(midBoss, collisionVector))
	{
		midBoss.damage(FIRE);
		fire.setVisible(false);
		fire.setActive(false);
	}

	// 攻撃中ならば行動選択は行わない
	if (midBoss.getState() == characterNS::ATTACK)
	{
	}
	else if (midBoss.collidesWith(brave, collisionVector))// 雑魚敵とプレイヤーが衝突している場合、
	{
		// 敵の状態を勇者攻撃状態に変更
		midBoss.setAttackState(enemyNS::ATTACK_BRAVE);
		// 勇者がいる方向に応じて攻撃する方向を変更
		midBoss.changeAttack(collisionVector);
	}
	else if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX()) == -1)	// 雑魚敵と城が衝突していたら攻撃、
	{
		// 城がある方向に応じて攻撃する方向を変更
		if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX() + 1) == 2)
		{
			midBoss.changeAttack(characterNS::RIGHT);
		}
		else if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX() - 1) == 2)
		{
			midBoss.changeAttack(characterNS::LEFT);
		}
		else if (map.getMapCol(midBoss.getTileY() + 1, midBoss.getTileX()) == 2)
		{
			midBoss.changeAttack(characterNS::DOWN);
		}
		else if (map.getMapCol(midBoss.getTileY() - 1, midBoss.getTileX()) == 2)
		{
			midBoss.changeAttack(characterNS::UP);
		}
		// 敵の状態を城攻撃状態に変更
		midBoss.setAttackState(enemyNS::ATTACK_CASTLE);
	}
	else if (map.getMapObj(midBoss.getTileY(), midBoss.getTileX()) == -2)	// 最近接のバリケードに衝突していたら攻撃
	{
		// バリケードがある方向に応じて攻撃する方向を変更
		if (midBoss.getTileX() < (int)barricades[midBoss.getNearBarricadeIndex()].getX() / 32)
			midBoss.changeAttack(characterNS::RIGHT);
		else if (midBoss.getTileX() > (int)barricades[midBoss.getNearBarricadeIndex()].getX() / 32)
			midBoss.changeAttack(characterNS::LEFT);
		else if (midBoss.getTileY() < (int)barricades[midBoss.getNearBarricadeIndex()].getY() / 32)
			midBoss.changeAttack(characterNS::DOWN);
		else if (midBoss.getTileY() > (int)barricades[midBoss.getNearBarricadeIndex()].getY() / 32)
			midBoss.changeAttack(characterNS::UP);
		else
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error enemy and barricades"));
		// 敵の状態をバリケード攻撃状態に変更
		midBoss.setAttackState(enemyNS::ATTACK_BARRICADE);
	}
	else if (midBoss.canMakeDecesionMoving())	// 敵が方向転換可能な状態にあるとき、意思決定を行い進む方向を決める
	{
		bool changeGoalDirectionFlag = false;	// 進みたい方向を変える必要があるかどうか
												// 最近接のバリケードを探索
		midBoss.searchNearBarricadeIndex();
		if (!midBoss.checkBarricadeOnLine())	// 城までの直線上にバリケードがない場合、城へと進行する
		{
			// 敵の状態を城移動中へと変更
			midBoss.setStateDetail(enemyNS::MOVE_CASTLE);
			midBoss.setState(characterNS::MOVE);
			// 進みたい方向に進めない場合、方向を進みたい方向をランダムに変換
			switch (midBoss.getGoalDirection())
			{
			case characterNS::LEFT:
				if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX() - 1) >= 1)
				{
					changeGoalDirectionFlag = true;
				}
				break;
			case characterNS::RIGHT:
				if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX() + 1) >= 1)
				{
					changeGoalDirectionFlag = true;
				}
				break;
			case characterNS::UP:
				if (map.getMapCol(midBoss.getTileY() - 1, midBoss.getTileX()) >= 1)
				{
					changeGoalDirectionFlag = true;
				}
				break;
			case characterNS::DOWN:
				if (map.getMapCol(midBoss.getTileY() + 1, midBoss.getTileX()) >= 1)
				{
					changeGoalDirectionFlag = true;
				}
				break;
			}
		}
		else // 城までの直線状にバリケードが存在する場合、
		{
			// 敵の状態をバリケードに進行中へと変更
			midBoss.setStateDetail(enemyNS::MOVE_BARRICADE);
			midBoss.setState(characterNS::MOVE);
			// 確率50%でx方向に進むかどうかを先に決定し、そのあとにy方向に進むかどうかを決定
			bool canMoveXDirection = false;
			bool canMoveYDirection = false;
			characterNS::DIRECTION xDirection;
			characterNS::DIRECTION yDirection;
			if ((int)barricades[midBoss.getNearBarricadeIndex()].getX() / 32 < midBoss.getTileX())
			{
				if (!map.getMapCol(midBoss.getTileY(), midBoss.getTileX() - 1) >= 1)
				{
					xDirection = characterNS::LEFT;
					midBoss.setGoalDirection(characterNS::LEFT);
					canMoveXDirection = true;
				}
				else
					changeGoalDirectionFlag = true;
			}
			else if ((int)barricades[midBoss.getNearBarricadeIndex()].getX() / 32 > midBoss.getTileX())
			{
				if (!map.getMapCol(midBoss.getTileY(), midBoss.getTileX() + 1) >= 1)
				{
					xDirection = characterNS::RIGHT;
					midBoss.setGoalDirection(characterNS::RIGHT);
					canMoveXDirection = true;
				}
				else
					changeGoalDirectionFlag = true;
			}
			if ((int)barricades[midBoss.getNearBarricadeIndex()].getY() / 32 < midBoss.getTileY())
			{
				if (!map.getMapCol(midBoss.getTileY() - 1, midBoss.getTileX()) >= 1)
				{
					yDirection = characterNS::UP;
					midBoss.setGoalDirection(characterNS::UP);
					canMoveYDirection = true;
				}
				else
					changeGoalDirectionFlag = true;
			}
			else if ((int)barricades[midBoss.getNearBarricadeIndex()].getY() / 32 > midBoss.getTileY())
			{
				if (!map.getMapCol(midBoss.getTileY() + 1, midBoss.getTileX()) >= 1)
				{
					yDirection = characterNS::DOWN;
					midBoss.setGoalDirection(characterNS::DOWN);
					canMoveYDirection = true;
				}
				else
					changeGoalDirectionFlag = true;
			}
			if (canMoveXDirection && canMoveYDirection)
			{
				if (rand() % 2 == 0)
					midBoss.setGoalDirection(xDirection);
				else
					midBoss.setGoalDirection(yDirection);
			}
			// 進みたい方向に進めない場合、ランダムに方向を決めなおす
			if (changeGoalDirectionFlag)
			{
				// ランダムに進みたい方向を修正
				characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
				// それでも進めない場合、敵を待機状態にして静止させる
				if (midBoss.canMoveTo(newDirection))
				{
					midBoss.setGoalDirection(newDirection);
				}
				else
				{
					midBoss.setState(characterNS::WAIT);
					midBoss.setStateDetail(enemyNS::WAIT);
				}
			}
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
		roundOver = true;
		/*
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
					map.setX((float)(col*mapNS::TEXTURE_SIZE));                    // タイルのXを設定
					if (map.getX() > -mapNS::TEXTURE_SIZE && map.getX() < GAME_WIDTH)     // タイルが画面上にあるかどうか
						map.draw();    // タイルを描画
				}
				if (map.getMapObj(row, col) == 0)
				{
					barricades[count].draw();   // オブジェクトを描画
					count++;
				}
				else if (map.getMapObj(row, col) == 1)
				{
					count++;
				}
			}
		}

		graphics->spriteEnd();		// スプライトの描画を開始
		rect->draw();
		graphics->spriteBegin();	// スプライトの描画を開始

		for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
			// 敵の描画、色は適当に分けてる、色によって能力値を分ける
			if (i % 3 == 0) {
				enemy[i].draw(graphicsNS::WHITE);
				enemy[i].setEnemyType(enemyNS::NORMAL);
			}
			else if (i % 3 == 1) {
				enemy[i].draw(graphicsNS::RED);
				enemy[i].setEnemyType(enemyNS::RED);
			}
			else if (i % 3 == 2) {
				enemy[i].draw(graphicsNS::BLUE);
				enemy[i].setEnemyType(enemyNS::BLUE);
			}
			enemyAttackCollision[i].draw();
		}
		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		castle.draw();
		midBoss.draw(graphicsNS::WHITE);
		midBossAttackCollision.draw();
		fire.draw();
		brave.draw(graphicsNS::WHITE);
		braveAttackCollision.draw();
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