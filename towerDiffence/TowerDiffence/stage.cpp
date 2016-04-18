//==========================================================
/// @file
/// @brief    stage.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "stage.h"

//==========================================================
// コンストラクタ
//==========================================================
Stage::Stage()
{
	roundOver = false;
	clearedStage = false;
	enemyNum = 0;
	enemy = NULL;
	enemyX = NULL;
	enemyY = NULL;
	enemyWaveNum = 0;
	remainingTime = 1500.0f;
	stageNum = 0;
}

//==========================================================
// デストラクタ
//==========================================================
Stage::~Stage()
{
	for (int i = 0; i < enemyNum; ++i)
	{
		safeDelete(enemy[i]);
	}
	safeDeleteArray(enemy);
	safeDeleteArray(enemyX);
	safeDeleteArray(enemyY);
}
//==========================================================
// ステージ情報を初期化
//==========================================================
void Stage::reset() 
{
	roundOver = false;
	clearedStage = false;
	enemyNum = 0;
	enemy = NULL;
	enemyX = NULL;
	enemyY = NULL;
	enemyWaveNum = 0;
	remainingTime = 1500.0f;
	stageNum = 0;
}

//==========================================================
// プレイの新しいラウンドを開始
//==========================================================
void Stage::roundStart()
{
	map.readMapFile(stageNum + 1);
	enemyWaveNum = 0;
	enemyNum = 0;
	initializeEnemies(stageNum + 1, enemyWaveNum + 1);
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
	// 残り時間を初期化
	remainingTime = 1500.0f;
	// ゲームオーバーのフラグを初期化
	roundOver = false;
	clearedStage = false;
}

//==========================================================
// 人工知能
//==========================================================
void Stage::ai(float frameTime)
{
	// 各敵を更新
	for (int i = 0; i < enemyNum; i++)
		enemy[i]->ai(frameTime, brave);
}

//==========================================================
// ステージを1ステップ分進める
//==========================================================
void Stage::runStage(float frameTime)
{
	// それぞれの敵を更新
	for (int i = 0; i < enemyNum; i++) {
		enemy[i]->update(frameTime);
	}
	// 勇者を更新
	brave.update(frameTime);
	// 城を更新
	castle.update(frameTime);
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
		roundOver = true;
	}

	// 死亡チェック
	if ((castle.isDeath() || brave.getActive() == false) && !roundOver)
	{
		roundOver = true;
	}
}

//==========================================================
// 衝突を処理
//==========================================================
void Stage::collisions()
{
	VECTOR2 collisionVector;	// 衝突判定したときの衝突相手へのベクトル
	bool braveAttackCollidesWithAnyEnemy = false;
	// 各敵について衝突判定
	for (int i = 0; i < enemyNum; i++) {
		// プレイヤーの攻撃コリジョンと雑魚敵の衝突の場合
		if (brave.getBraveAttackCollision().collidesWith(*enemy[i], collisionVector))
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					brave.damage(ENEMY_ATTACK);
				}
				else
				{
					brave.damage(MIDBOSS_ATTACK);
				}
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					castle.damage(ENEMY_ATTACK);
				}
				else
				{
					castle.damage(MIDBOSS_ATTACK);
				}
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					barricades[enemy[i]->getNearBarricadeIndex()].damage(ENEMY_ATTACK);
				}
				else
				{
					barricades[enemy[i]->getNearBarricadeIndex()].damage(MIDBOSS_ATTACK);
				}
				// 敵の攻撃コリジョンをなくす
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
				// 攻撃されたバリケードが破壊された場合、
				if (!barricades[enemy[i]->getNearBarricadeIndex()].getActive())
				{
					// マップデータを更新
					map.updateMapObjInt(barricades[enemy[i]->getNearBarricadeIndex()].getTileY(), barricades[enemy[i]->getNearBarricadeIndex()].getTileX(), -1);
					if (map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 + 1) != 0
						&& map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 + 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY(), barricades[enemy[i]->getNearBarricadeIndex()].getX() + 32, -1);
					}
					if (map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 - 1) != 0
						&& map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 - 1) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY(), barricades[enemy[i]->getNearBarricadeIndex()].getX() - 32, -1);
					}
					if (map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 + 1, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0
						&& map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 + 1, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 1)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() + 32, barricades[enemy[i]->getNearBarricadeIndex()].getX(), -1);
					}
					if (map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 - 1, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0
						&& map.getMapObj((int)barricades[enemy[i]->getNearBarricadeIndex()].getY() / 32 - 1, (int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32) != 0)
					{
						map.updateMapObj(barricades[enemy[i]->getNearBarricadeIndex()].getY() - 32, barricades[enemy[i]->getNearBarricadeIndex()].getX(), -1);
					}
				}
			}
		}

		// 炎と雑魚敵の衝突の場合
		if (brave.getFire().collidesWith(*enemy[i], collisionVector))
		{
			enemy[i]->damage(FIRE);
			brave.getFire().setVisible(false);
			brave.getFire().setActive(false);
		}

		// 攻撃中ならば行動選択は行わない
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
		}
		else if (enemy[i]->collidesWith(brave, collisionVector))// 雑魚敵とプレイヤーが衝突している場合、
		{
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
		}
		else if (enemy[i]->canMakeDecesionMoving())	// 敵が方向転換可能な状態にあるとき、意思決定を行い進む方向を決める
		{
			bool changeGoalDirectionFlag = false;	// 進みたい方向を変える必要があるかどうか
			if (rand() % 3 == 0)
			{
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
					enemy[i]->setState(characterNS::MOVE);
					// 確率50%でx方向に進むかどうかを先に決定し、そのあとにy方向に進むかどうかを決定
					bool canMoveXDirection = false;
					bool canMoveYDirection = false;
					characterNS::DIRECTION xDirection;
					characterNS::DIRECTION yDirection;
					if ((int)barricades[enemy[i]->getNearBarricadeIndex()].getX() / 32 < enemy[i]->getTileX())
					{
						if (!(map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() - 1) >= 1))
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
						if (!(map.getMapCol(enemy[i]->getTileY(), enemy[i]->getTileX() + 1) >= 1))
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
						if (!(map.getMapCol(enemy[i]->getTileY() - 1, enemy[i]->getTileX()) >= 1))
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
						if (!(map.getMapCol(enemy[i]->getTileY() + 1, enemy[i]->getTileX()) >= 1))
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
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		// プレイヤーの攻撃コリジョンとの衝突の場合
		if (brave.getBraveAttackCollision().collidesWith(barricades[i], collisionVector))
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
		brave.getBraveAttackCollision().setVisible(false);
		brave.getBraveAttackCollision().setActive(false);
	}
}

//==========================================================
// 敵の数をチェックし、マップ上に敵がいなければ新たに生成
//==========================================================
void Stage::checkCurrentEnemyNum()
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
	enemyWaveNum += 1;
	initializeEnemies(stageNum + 1, enemyWaveNum + 1);
}

//==========================================================
// 指定されたステージの敵データを読み込む
//==========================================================
bool Stage::readEnemyFile(int stageNum, int enemyWave)
{
	string enemyDataFilename = "stageData\\stage" + std::to_string(stageNum) + "\\enemy" + std::to_string(enemyWave) + "\\enemydata.csv";

	enemyNum = 0;
	ifstream* ifs = new ifstream(enemyDataFilename);
	if (!*ifs)
	{
		clearedStage = true;
		return false;
	}
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
				if ((int)stof(token) <= 3)
				{
					enemy[i] = new Enemy();
					switch ((int)stof(token))
					{
					case 1:
						enemy[i]->setEnemyType(enemyNS::NORMAL);
						break;
					case 2:
						enemy[i]->setEnemyType(enemyNS::RED);
						break;
					case 3:
						enemy[i]->setEnemyType(enemyNS::BLUE);
					}
				}
				else if ((int)stof(token) == 4)
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
	return true;
}

//==========================================================
// 指定されたステージ、派の敵データを読み込み敵を初期化する
//==========================================================
void Stage::initializeEnemies(int stageNum, int enemyWave)
{
	if (!readEnemyFile(stageNum, enemyWave))
	{
		return;
	}
	for (int i = 0; i < enemyNum; i++) {
		enemy[i]->setScale(1.5);
		enemy[i]->setMapPointer(map);
		enemy[i]->setBarricadesPointer(barricades);
		enemy[i]->reset();
		enemy[i]->setX(enemyX[i]);
		enemy[i]->setY(enemyY[i]);
		enemy[i]->initTileXY();
	}
	initializedEnemies = true;
}