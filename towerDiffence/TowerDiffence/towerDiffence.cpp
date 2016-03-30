// TowerDiffence�̓Q�[���̃��C���N���X
#include "towerDiffence.h"

//==========================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//==========================================================
TowerDiffence::~TowerDiffence()
{
	safeDelete(rect);
	safeDelete(fontCK);
	releaseAll();	// ���ׂẴO���t�B�b�N�X�A�C�e���ɂ��āAonLostDevice()���Ăяo��
}

//==========================================================
// �Q�[����������
// �G���[����GameError���X���[
//==========================================================
void TowerDiffence::initialize(HWND hwnd)
{
	Game::initialize(hwnd);	// GameError���X���[
	rect = new Rect();
	rect->initialize(graphics);

	// init text
	if (!fontCK->initialize(graphics, FONT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing CKfont"));


	// ���j���[�̃e�N�X�`��
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// ���j���[�̉摜
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	menu.setScale(2);

	// ���U���g�̃e�N�X�`��
	if (!resultTexture.initialize(graphics, RESULT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result texture"));
	// ���U���g�̉摜
	if (!result.initialize(graphics, 0, 0, 0, &resultTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result"));
	result.setScale(2);

	// �}�b�v�̃e�N�X�`��
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// �}�b�v�̉摜
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �o���P�[�h�̃e�N�X�`��
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	// �o���P�[�h�̉摜
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!barricades[i].initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		barricades[i].setScale(1);
	}

	// ��̃e�N�X�`��
	if (!castleTexture.initialize(graphics, CASTLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle texture"));
	// ��̉摜
	if (!castle.initialize(this, castleNS::WIDTH, castleNS::HEIGHT, castleNS::TEXTURE_COLS, &castleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle"));

	// ��̃A�C�R���̃e�N�X�`��
	if (!castleIconTexture.initialize(graphics, CASTLE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle icon texture"));
	// ��̃A�C�R���̉摜
	if (!castleIcon.initialize(graphics, castleIconNS::WIDTH, castleIconNS::HEIGHT, castleIconNS::TEXTURE_COLS, &castleIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle icon"));

	// �E�҂̃e�N�X�`��
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// �E��
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(1.5);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);
	brave.setMapPointer(&map);

	// �E�҂̃A�C�R���̃e�N�X�`��
	if (!braveIconTexture.initialize(graphics, BRAVE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon texture"));
	// �E�҂̃A�C�R���̉摜
	if (!braveIcon.initialize(graphics, braveIconNS::WIDTH, braveIconNS::HEIGHT, braveIconNS::TEXTURE_COLS, &braveIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon"));
	braveIcon.linkEntity(&brave);

	// �E�҂̓����蔻��p�̃e�N�X�`��
	if (!attackCollisionTexture.initialize(graphics, COLLISION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision texture"));
	// �E�҂̂����蔻��p
	if (!braveAttackCollision.initialize(this, braveAttackCollisionNS::WIDTH, braveAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision"));
	// ���{�X�̓����蔻��p
	if (!midBossAttackCollision.initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	
	// ���̃e�N�X�`��
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!fire.initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));
	fire.setScale(1.5);

	// �G���G�̃e�N�X�`��
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
		if (!enemy[i].initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		enemy[i].setScale(1.0);
		enemy[i].setMapPointer(&map);
		enemy[i].setBarricadesPointer(barricades);

		// �G���G�̓����蔻��p
		if (!enemyAttackCollision[i].initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	}
	// ���{�X
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));
	if (!midBoss.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &midBossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss"));
	midBoss.setScale(1.5);
	midBoss.setMapPointer(&map);
	midBoss.setBarricadesPointer(barricades);
	
	// �_�b�V���{�[�h
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	braveHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_HEALTH_BAR_X, towerDiffenceNS::BRAVE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::RED);
	braveHealthBar.set(brave.getHealth());
	braveMpBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_MP_BAR_X, towerDiffenceNS::BRAVE_MP_BAR_Y, 0.5f, 100, graphicsNS::GREEN);
	braveMpBar.set(brave.getMP());
	castleHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::CASTLE_HEALTH_BAR_X + 40, towerDiffenceNS::CASTLE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::BLUE);
	castleHealthBar.set(castle.getHealth());

	// �e�L�X�g�摜
	if (!textTexture.initialize(graphics, TEXT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text textures"));
	if (!braveHpText.initialize(graphics, hpTextImageNS::WIDTH, hpTextImageNS::HEIGHT, hpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	if (!braveMpText.initialize(graphics, mpTextImageNS::WIDTH, mpTextImageNS::HEIGHT, mpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	if (!castleHpText.initialize(graphics, hpTextImageNS::WIDTH, hpTextImageNS::HEIGHT, hpTextImageNS::TEXTURE_COLS, &textTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hp text"));
	castleHpText.setX(830);

	// �^�C�g��BGM�Đ�
	audio->playCue("title");

	// �G�̈ʒu������
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].setX(enemyNS::X[i]);
		enemy[i].setY(enemyNS::Y[i]);
	}

	return;
}

//==========================================================
// ���ׂẴQ�[���A�C�e�����X�V
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
		for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
			if (enemy[i].getAttackCollisionFlag()) {
				enemyAttackCollision[i].attack(&enemy[i]);
			}
			enemy[i].update(frameTime);
			enemyAttackCollision[i].update(frameTime);
		}
		if (midBoss.getAttackCollisionFlag())
			midBossAttackCollision.attack(&midBoss);
		if (midBoss.getState() == characterNS::MOVE)
			midBossAttackCollision.walk(&midBoss);
		brave.update(frameTime);
		//midBoss.update(frameTime);
		fire.update(frameTime);
		braveAttackCollision.update(frameTime);
		midBossAttackCollision.update(frameTime);
		castle.update(frameTime);
		braveIcon.update(frameTime);
		for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
		{
			barricades[i].update(frameTime);
		}
		// �c�莞�Ԃ�0�Ȃ�Q�[���I�[�o�[
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
// �v���C�̐V�������E���h���J�n
//==========================================================
void TowerDiffence::roundStart()
{
	// ������
	// �}�b�v�ƃo���P�[�h�͏��߂����`��
	int count = 0;  // �o���P�[�h�̐�������p
	for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // �}�b�v�̊e�s������
	{
		map.setY((float)(row*mapNS::TEXTURE_SIZE));       // �^�C����Y��ݒ�
		for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // �}�b�v�̊e�������
		{
			if (map.getMapData(row, col) >= 0)            // �^�C�������݂���ꍇ
			{
				map.setCurrentFrame(map.getMapData(row, col));                       // �^�C���̃e�N�X�`����ݒ�
				map.setX((float)(col*mapNS::TEXTURE_SIZE));                    // �^�C����X��ݒ�
			}
			if (map.getMapObj(row, col) >= 0)
			{
				barricades[count].setX((float)(col*mapNS::TEXTURE_SIZE));								// �I�u�W�F�N�g��X��ݒ�
				barricades[count].setY((float)(row*mapNS::TEXTURE_SIZE));										// �I�u�W�F�N�g��Y��ݒ�
				barricades[count].setTileX(col);								// �I�u�W�F�N�g��X��ݒ�
				barricades[count].setTileY(row);										// �I�u�W�F�N�g��Y��ݒ�
				if (barricades[count].getX() > -mapNS::TEXTURE_SIZE && barricades[count].getX() < GAME_WIDTH)	// �I�u�W�F�N�g����ʏ�ɂ��邩�ǂ���
				{
					count++;
				}
			}
		}
	}
	brave.reset();
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].reset();
		enemy[i].setX(enemyNS::X[i]);
		enemy[i].setY(enemyNS::Y[i]);
		enemy[i].initTileXY();
	}
	midBoss.reset();
	midBoss.setX(GAME_WIDTH / 2 - 500);
	midBoss.setY(GAME_HEIGHT / 2 - 80);
	midBoss.initTileXY();
	castle.reset();
	fire.reset();

	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}

	// HP,MP������
	brave.setHealth(100);
	brave.setMP(100);

	remainingTime = 1500.0f;

	roundOver = false;
}

//==========================================================
// �l�H�m�\
//==========================================================
void TowerDiffence::ai()
{
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
		enemy[i].ai(frameTime, brave);
	midBoss.ai(frameTime, brave);
}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
		// �v���C���[�ƎG���G�̏Փ˂̏ꍇ
		if (enemy[i].collidesWith(brave, collisionVector))
			enemy[i].setNearPlayer(true);
		else
			enemy[i].setNearPlayer(false);

		// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
		if (braveAttackCollision.collidesWith(enemy[i], collisionVector))
		{
			enemy[i].damage(BRAVE_ATTACK);
			braveAttackCollision.setVisible(false);
			braveAttackCollision.setActive(false);
		}

		// �G���U�����́A��ƃv���C���[�ƃo���P�[�h�Ƃ̓����蔻����`�F�b�N
		if (enemy[i].getState() == characterNS::ATTACK)
		{
			// �G�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(brave, collisionVector))
			{
				brave.damage(ENEMY_ATTACK);
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// �G�̍U���R���W�����Ə�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(castle, collisionVector))
			{
				castle.damage(ENEMY_ATTACK);
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// �G�̍U���R���W�����ƃo���P�[�h�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(barricades[enemy[i].getNearBarricadeIndex()], collisionVector)) {
				barricades[enemy[i].getNearBarricadeIndex()].damage();
				//enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
				if (!barricades[enemy[i].getNearBarricadeIndex()].getActive())
				{
					//map.updateMapObjInt(10, 15, -1);
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
		// �G���ړ����ɂ́A���̓G�Ƃ̓����蔻����`�F�b�N
		enemy[i].setCanMove(true);
		if (enemy[i].getState() == characterNS::MOVE)
		{
			// �����蔻���i�s�����ɑ΂��ďo��
			enemyAttackCollision[i].walk(&enemy[i]);
			// �i�����Ƃ��Ă�������ɑ��̓G��������ړ��͂ł��Ȃ�
			if (enemyAttackCollision[i].collidesWith(midBoss, collisionVector))
			{
				enemy[i].setCanMove(false);
			}
			//enemyAttackCollision.setVisible(false);
			enemyAttackCollision[i].setActive(false);
		}

		// ���ƎG���G�̏Փ˂̏ꍇ
		if (fire.collidesWith(enemy[i], collisionVector))
		{
			enemy[i].damage(FIRE);
			fire.setVisible(false);
			fire.setActive(false);
		}

		// �U�����Ȃ�΍s���I���͍s��Ȃ�
		if (enemy[i].getState() == characterNS::ATTACK)
		{
		}
		else if (map.getMapObj(enemy[i].getTileY(), enemy[i].getTileX()) == -2)
		{
			// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U���A����ȊO�Ȃ�o���P�[�h�Ɍ������B
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
			enemy[i].setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else if (enemy[i].collidesWith(brave, collisionVector))// �G���G�ƃv���C���[�̏Փ˔���
		{
			enemy[i].changeAttack(collisionVector);
			enemy[i].setAttackState(enemyNS::ATTACK_BRAVE);
		}
		else if (enemy[i].collidesWith(castle, collisionVector))	// �G���G�Ə�̏Փ˔���
		{
			enemy[i].changeAttack(collisionVector);
			enemy[i].setAttackState(enemyNS::ATTACK_CASTLE);
		}
		else if (enemy[i].canMakeDecesionMoving())
		{
			// �ŋߐڂ̃o���P�[�h��T��
			enemy[i].searchNearBarricadeIndex();
			if (!enemy[i].checkBarricadeOnLine())	// ��܂ł̒�����Ƀo���P�[�h�����邩���`�F�b�N
			{
				enemy[i].setStateDetail(enemyNS::MOVE_CASTLE);
				enemy[i].setState(characterNS::MOVE);
				switch (enemy[i].getGoalDirection())
				{
				case characterNS::LEFT:
					if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) >= 1)
					{
						enemy[i].setGoalDirection(characterNS::RIGHT);
					}
					break;
				case characterNS::RIGHT:
					if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) >= 1)
					{
						enemy[i].setGoalDirection(characterNS::LEFT);
					}
					break;
				case characterNS::UP:
					if (map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) >= 1)
					{
						enemy[i].setGoalDirection(characterNS::DOWN);
					}
					break;
				case characterNS::DOWN:
					if (map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) >= 1)
					{
						enemy[i].setGoalDirection(characterNS::UP);
					}
					break;
				}
			}
			else
			{
				enemy[i].setStateDetail(enemyNS::MOVE_BARRICADE);
				enemy[i].setState(characterNS::MOVE);
				if (rand() % 2 == 0)
				{
					if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 < enemy[i].getTileX())
					{
						if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) >= 1)
						{
							enemy[i].setGoalDirection(characterNS::LEFT);
						}
						else
						{
							enemy[i].setGoalDirection(characterNS::RIGHT);
						}
					}
					else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 > enemy[i].getTileX())
					{
						if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) >= 1)
						{
							enemy[i].setGoalDirection(characterNS::RIGHT);
						}
						else
						{
							enemy[i].setGoalDirection(characterNS::LEFT);
						}
					}
					else
					{
						if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 < enemy[i].getTileY())
						{
							if (!map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) >= 1)
							{
								enemy[i].setGoalDirection(characterNS::UP);
							}
							else
							{
								enemy[i].setGoalDirection(characterNS::DOWN);
							}
						}
						else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 > enemy[i].getTileY())
						{
							if (!map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) >= 1)
							{
								enemy[i].setGoalDirection(characterNS::DOWN);
							}
							else
							{
								enemy[i].setGoalDirection(characterNS::UP);
							}
						}
						else
							throw(GameError(gameErrorNS::FATAL_ERROR, "Error change enemy goalDirection"));
					}
				}
				else
				{

					if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 < enemy[i].getTileY())
					{
						if (!map.getMapCol(enemy[i].getTileY() - 1, enemy[i].getTileX()) >= 1)
						{
							enemy[i].setGoalDirection(characterNS::UP);
						}
						else
						{
							enemy[i].setGoalDirection(characterNS::DOWN);
						}
					}
					else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getY() / 32 > enemy[i].getTileY())
					{
						if (!map.getMapCol(enemy[i].getTileY() + 1, enemy[i].getTileX()) >= 1)
						{
							enemy[i].setGoalDirection(characterNS::DOWN);
						}
						else
						{
							enemy[i].setGoalDirection(characterNS::UP);
						}
					}
					else
					{
						if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 < enemy[i].getTileX())
						{
							if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() - 1) >= 1)
							{
								enemy[i].setGoalDirection(characterNS::LEFT);
							}
							else
							{
								enemy[i].setGoalDirection(characterNS::RIGHT);
							}
						}
						else if ((int)barricades[enemy[i].getNearBarricadeIndex()].getX() / 32 > enemy[i].getTileX())
						{
							if (!map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX() + 1) >= 1)
							{
								enemy[i].setGoalDirection(characterNS::RIGHT);
							}
							else
							{
								enemy[i].setGoalDirection(characterNS::LEFT);
							}
						}
					}
				}
			}
		}
	}

	// �v���C���[�ƒ��{�X�̏Փ˂̏ꍇ
	if (midBoss.collidesWith(brave, collisionVector))
	{
		midBoss.setNearPlayer(true);
	}
	else
		midBoss.setNearPlayer(false);

	// �v���C���[�̍U���R���W�����ƒ��{�X�̏Փ˂̏ꍇ
	if (braveAttackCollision.collidesWith(midBoss, collisionVector))
	{
		midBoss.damage(BRAVE_ATTACK);
		braveAttackCollision.setVisible(false);
		braveAttackCollision.setActive(false);
	}

	if (midBoss.getState() == characterNS::ATTACK)
	{
		// ���{�X�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
		if (midBossAttackCollision.collidesWith(brave, collisionVector))
		{
			brave.damage(ENEMY_ATTACK);
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
		// ���{�X�̍U���R���W�����Ə�̏Փ˂̏ꍇ
		if (midBossAttackCollision.collidesWith(castle, collisionVector))
		{
			castle.damage(ENEMY_ATTACK);
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
	}
	midBoss.setCanMove(true);
	if (midBoss.getState() == characterNS::MOVE)
	{
		for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
			if (midBossAttackCollision.collidesWith(enemy[i], collisionVector))
			{
				midBoss.setCanMove(false);
				midBossAttackCollision.setVisible(false);
				midBossAttackCollision.setActive(false);
			}
		}
	}
	// ���ƎG���G�̏Փ˂̏ꍇ
	if (fire.collidesWith(midBoss, collisionVector))
	{
		midBoss.damage(FIRE);
		fire.setVisible(false);
		fire.setActive(false);
	}

	// �U�����Ȃ�΍s���I���͍s��Ȃ�
	if (midBoss.getState() == characterNS::ATTACK)
	{
	}
	else if (midBoss.collidesWith(brave, collisionVector))// ���{�X�ƃv���C���[�̏Փ˔���
	{
		midBoss.changeAttack(collisionVector);
		midBoss.setAttackState(enemyNS::ATTACK_BRAVE);
	}
	else if (midBoss.collidesWith(castle, collisionVector))	// ���{�X�Ə�̏Փ˔���
	{
		midBoss.changeAttack(collisionVector);
		midBoss.setAttackState(enemyNS::ATTACK_CASTLE);
	}
	else if (!midBoss.checkBarricadeOnLine())	// ��܂ł̒�����Ƀo���P�[�h�����邩���`�F�b�N
	{
		midBoss.setStateDetail(enemyNS::MOVE_CASTLE);
		midBoss.setState(characterNS::MOVE);
		VECTOR2 pos;
		pos.x = castle.getCenterX();
		pos.y = castle.getCenterY();
		midBoss.setGoalPost(pos);
	}
	else
	{
		// �ŋߐڂ̃o���P�[�h��T��
		int nearBarricadeIndex = midBoss.searchNearBarricadeIndex();
		// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U���A����ȊO�Ȃ�o���P�[�h�Ɍ������B
		if (midBoss.collidesWith(barricades[nearBarricadeIndex], collisionVector))
		{
			midBoss.changeAttack(collisionVector);
			midBoss.setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else
		{
			midBoss.setStateDetail(enemyNS::MOVE_BARRICADE);
			midBoss.setState(characterNS::MOVE);
			VECTOR2 pos;
			pos.x = barricades[nearBarricadeIndex].getX();
			pos.y = barricades[nearBarricadeIndex].getY();
			midBoss.setGoalPost(pos);
		}
	}

	// ���{�X�̍U���R���W�����ƃo���P�[�h�̏Փ�
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (midBossAttackCollision.collidesWith(barricades[i], collisionVector)) {
			barricades[i].damage();
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
	}
	// ���S�`�F�b�N
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
// �Q�[���A�C�e���������_�[
// �v���C���̃��C���[�F�}�b�v�����w�i�����̑��A�C�e���̏�
//==========================================================
void TowerDiffence::render()
{
	graphics->spriteBegin();	// �X�v���C�g�̕`����J�n
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
		// �}�b�v�ƃo���P�[�h�͏��߂����`��
		int count = 0;  // �o���P�[�h�̐�������p
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // �}�b�v�̊e�s������
		{
			map.setY((float)(row*mapNS::TEXTURE_SIZE));       // �^�C����Y��ݒ�
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // �}�b�v�̊e�������
			{
				if (map.getMapData(row, col) >= 0)            // �^�C�������݂���ꍇ
				{
					map.setCurrentFrame(map.getMapData(row, col));                       // �^�C���̃e�N�X�`����ݒ�
					map.setX((float)(col*mapNS::TEXTURE_SIZE));                    // �^�C����X��ݒ�
					if (map.getX() > -mapNS::TEXTURE_SIZE && map.getX() < GAME_WIDTH)     // �^�C������ʏ�ɂ��邩�ǂ���
						map.draw();    // �^�C����`��
				}
				if (map.getMapObj(row, col) == 0)
				{
					barricades[count].draw();   // �I�u�W�F�N�g��`��
					count++;
				}
				else if (map.getMapObj(row, col) == 1)
				{
					count++;
				}
			}
		}

		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

		for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {
			// �G�̕`��A�F�͓K���ɕ����Ă�̂Łc
			if (i % 3 == 0)
				enemy[i].draw(graphicsNS::WHITE);
			else if (i % 3 == 1)
				enemy[i].draw(graphicsNS::RED);
			else if (i % 3 == 2)
				enemy[i].draw(graphicsNS::BLUE);

			enemyAttackCollision[i].draw();
		}
		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		castle.draw();
		midBoss.draw(graphicsNS::WHITE);
		fire.draw();
		brave.draw(graphicsNS::WHITE);
		braveAttackCollision.draw();
		midBossAttackCollision.draw();
		braveHealthBar.set(brave.getHealth());
		braveMpBar.set(brave.getMP());
		castleHealthBar.set(castle.getHealth());
		braveHealthBar.draw(graphicsNS::FILTER);	// �̗̓o�[��`��
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
	graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
}

//==========================================================
// �O���t�B�b�N�X�f�o�C�X�����������ꍇ
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽�߁A
// �\�񂳂�Ă����r�f�I�����������ׂĉ��
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
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�ꍇ
// ���ׂẴT�[�t�F�C�X���č쐬
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