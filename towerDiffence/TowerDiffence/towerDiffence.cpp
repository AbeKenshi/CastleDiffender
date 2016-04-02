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
	brave.setScale(1.0);
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
	midBoss.setScale(1.0);
	midBoss.setMapPointer(&map);
	midBoss.setBarricadesPointer(barricades);
	// �G���G�̓����蔻��p
	if (!midBossAttackCollision.initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));

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
	if (menuOn)		// ���j���[��ʕ\�����ɂ����ꂩ�̃L�[���������܂ł̓��j���[��ʂ�\����������
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
	else if (roundOver)	// �Q�[���I�[�o�[����Z�������ꂽ�烁�j���[��ʂɖ߂�AX�������ꂽ��v���O�����I��
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
	else				// �Q�[�����̏ꍇ�A
	{
		// FIRE_KEY�ɑΉ�����L�[�������ꂽ��E�҂��牊�𔭎�
		if (input->isKeyDown(BRAVE_FIRE_KEY))
			fire.fire(&brave);
		// �E�҂̍U�����肪�łĂ���ꍇ�̓R���W�����𐶐����ē����蔻����Ƃ�
		if (brave.getAttackCollisionFlag())
			braveAttackCollision.attack(&brave);
		// ���ꂼ��̓G���X�V
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
		// �E�҂��X�V
		brave.update(frameTime);
		// �����X�V
		fire.update(frameTime);
		// �E�҂̍U���R���W�������X�V
		braveAttackCollision.update(frameTime);
		// �G�̍U���R���W�������X�V
		midBossAttackCollision.update(frameTime);
		// ����X�V
		castle.update(frameTime);
		// �E�҂̃A�C�R���摜���X�V
		braveIcon.update(frameTime);
		// ���ꂼ��̃o���P�[�h���X�V
		for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
		{
			barricades[i].update(frameTime);
		}
		// �G�̐����`�F�b�N���āA�}�b�v��ɑ��݂��Ȃ���ΐV���ɐ���
		checkCurrentEnemyNum();
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
	// �}�b�v�ƃo���P�[�h��������
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
	// �E�҂�������
	brave.reset();
	// �e�G��������
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].reset();
		enemy[i].setX(enemyNS::X[i]);
		enemy[i].setY(enemyNS::Y[i]);
		enemy[i].initTileXY();
	}
	// ���{�X��������
	midBoss.reset();
	midBoss.setX(GAME_WIDTH / 2 - 500);
	midBoss.setY(GAME_HEIGHT / 2 - 80);
	midBoss.initTileXY();
	// ���������
	castle.reset();
	// ����������
	fire.reset();
	// �e�o���P�[�h��������
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}
	// �c�莞�Ԃ�������
	remainingTime = 1500.0f;
	// �Q�[���I�[�o�[�̃t���O��������
	roundOver = false;
}

//==========================================================
// �G�̐����`�F�b�N���A�}�b�v��ɓG�����Ȃ���ΐV���ɐ���
//==========================================================
void TowerDiffence::checkCurrentEnemyNum()
{
	// �G���G�����݂�����
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		if (enemy[i].getActive())
			return;
	}

	// ���{�X�����݂�����
	if (midBoss.getActive())
		return;

	// �G�����݂��Ă��Ȃ����ߑS�ď�����
	// �G���G�̏�����
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
	{
		enemy[i].reset();
		// �ʒu�̓����_��
		if (i % 4 == 0) // ����
		{
			enemy[i].setX(rand() % 200);
			enemy[i].setY(rand() % 200);
		}
		else if (i % 4 == 1) // �E��
		{
			enemy[i].setX(GAME_WIDTH - (rand() % 200));
			enemy[i].setY(rand()% 200);
		}
		else if (i % 4 == 2) // ����
		{
			enemy[i].setX(rand() % 200);
			enemy[i].setY(GAME_HEIGHT - (rand() % 200));
		}
		else if (i % 4 == 3) // �E��
		{
			enemy[i].setX(GAME_WIDTH - (rand() % 200));
			enemy[i].setY(GAME_HEIGHT - (rand() % 200));
		}
		enemy[i].setActive(true);
	}

	// ���{�X�̏�����
	midBoss.setX(GAME_WIDTH / 2 - 600);
	midBoss.setY(GAME_HEIGHT / 2 - 80);
	midBoss.reset();
	midBoss.setActive(true);
}

//==========================================================
// �l�H�m�\
//==========================================================
void TowerDiffence::ai()
{
	// �e�G���X�V
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++)
		enemy[i].ai(frameTime, brave);
	// ���{�X���X�V
	midBoss.ai(frameTime, brave);
}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;	// �Փ˔��肵���Ƃ��̏Փˑ���ւ̃x�N�g��
	bool braveAttackCollidesWithAnyEnemy = false;
	// �e�G�ɂ��ďՓ˔���
	for (int i = 0; i < towerDiffenceNS::ENEMY_NUM; i++) {

		// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
		if (braveAttackCollision.collidesWith(enemy[i], collisionVector))
		{
			// �G�Ƀ_���[�W��^����
			enemy[i].damage(BRAVE_ATTACK);
			// �����ꂩ�̓G�ɍU�������������̂Ń��[�v�𔲂�����ɍU���R���W�������Ȃ���
			braveAttackCollidesWithAnyEnemy = true;
		}

		// �G���U�����́A��ƃv���C���[�ƃo���P�[�h�Ƃ̓����蔻������ꂼ��`�F�b�N
		if (enemy[i].getState() == characterNS::ATTACK)
		{
			// �G�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(brave, collisionVector))
			{
				// �v���C���[�Ƀ_���[�W��^����
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) brave.setDamagePer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) brave.setDamagePer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) brave.setDamagePer(1.1f);
				brave.damage(ENEMY_ATTACK);
				// �G�̍U���R���W�������Ȃ���
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// �G�̍U���R���W�����Ə�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(castle, collisionVector))
			{
				// ��Ƀ_���[�W��^����
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) castle.setDamagePer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) castle.setDamagePer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) castle.setDamagePer(1.1f);
				castle.damage(ENEMY_ATTACK);
				// �G�̍U���R���W�������Ȃ���
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
			}
			// �G�̍U���R���W�����ƃo���P�[�h�̏Փ˂̏ꍇ
			if (enemyAttackCollision[i].collidesWith(barricades[enemy[i].getNearBarricadeIndex()], collisionVector)) {
				// �o���P�[�h�Ƀ_���[�W��^����ibarricades[enemy[i].getNearBarricadeIndex()]���U���ΏۂɂȂ�͂��j
				if (enemy[i].getEnemyType() == enemyNS::NORMAL) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.0f);
				else if (enemy[i].getEnemyType() == enemyNS::RED) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.2f);
				else if (enemy[i].getEnemyType() == enemyNS::BLUE) barricades[enemy[i].getNearBarricadeIndex()].setDamagerPer(1.1f);
				barricades[enemy[i].getNearBarricadeIndex()].damage();
				// �G�̍U���R���W�������Ȃ���
				enemyAttackCollision[i].setVisible(false);
				enemyAttackCollision[i].setActive(false);
				// �U�����ꂽ�o���P�[�h���j�󂳂ꂽ�ꍇ�A
				if (!barricades[enemy[i].getNearBarricadeIndex()].getActive())
				{
					// �}�b�v�f�[�^���X�V
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
		else if (enemy[i].collidesWith(brave, collisionVector))// �G���G�ƃv���C���[���Փ˂��Ă���ꍇ�A
		{
			// �G�̏�Ԃ�E�ҍU����ԂɕύX
			enemy[i].setAttackState(enemyNS::ATTACK_BRAVE);
			// �E�҂���������ɉ����čU�����������ύX
			enemy[i].changeAttack(collisionVector);
		}
		else if (map.getMapCol(enemy[i].getTileY(), enemy[i].getTileX()) == -1)	// �G���G�Ə邪�Փ˂��Ă�����U���A
		{
			// �邪��������ɉ����čU�����������ύX
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
			// �G�̏�Ԃ���U����ԂɕύX
			enemy[i].setAttackState(enemyNS::ATTACK_CASTLE);
		}
		else if (map.getMapObj(enemy[i].getTileY(), enemy[i].getTileX()) == -2)	// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U��
		{
			// �o���P�[�h����������ɉ����čU�����������ύX
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
			// �G�̏�Ԃ��o���P�[�h�U����ԂɕύX
			enemy[i].setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else if (enemy[i].canMakeDecesionMoving())	// �G�������]���\�ȏ�Ԃɂ���Ƃ��A�ӎv������s���i�ޕ��������߂�
		{
			bool changeGoalDirectionFlag = false;	// �i�݂���������ς���K�v�����邩�ǂ���
			// �ŋߐڂ̃o���P�[�h��T��
			enemy[i].searchNearBarricadeIndex();
			if (!enemy[i].checkBarricadeOnLine())	// ��܂ł̒�����Ƀo���P�[�h���Ȃ��ꍇ�A��ւƐi�s����
			{
				// �G�̏�Ԃ���ړ����ւƕύX
				enemy[i].setStateDetail(enemyNS::MOVE_CASTLE);
				enemy[i].setState(characterNS::MOVE);
				// �i�݂��������ɐi�߂Ȃ��ꍇ�A������i�݂��������������_���ɕϊ�
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
			else // ��܂ł̒�����Ƀo���P�[�h�����݂���ꍇ�A
			{
				// �G�̏�Ԃ��o���P�[�h�ɐi�s���ւƕύX
				enemy[i].setStateDetail(enemyNS::MOVE_BARRICADE);
				enemy[i].setState(characterNS::MOVE);
				// �m��50%��x�����ɐi�ނ��ǂ������Ɍ��肵�A���̂��Ƃ�y�����ɐi�ނ��ǂ���������
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
				// �i�݂��������ɐi�߂Ȃ��ꍇ�A�����_���ɕ��������߂Ȃ���
				if (changeGoalDirectionFlag)
				{
					// �����_���ɐi�݂����������C��
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// ����ł��i�߂Ȃ��ꍇ�A�G��ҋ@��Ԃɂ��ĐÎ~������
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
	// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
	if (braveAttackCollision.collidesWith(midBoss, collisionVector))
	{
		// �G�Ƀ_���[�W��^����
		midBoss.damage(BRAVE_ATTACK);
		// �����ꂩ�̓G�ɍU�������������̂Ń��[�v�𔲂�����ɍU���R���W�������Ȃ���
		braveAttackCollidesWithAnyEnemy = true;
	}

	// �G���U�����́A��ƃv���C���[�ƃo���P�[�h�Ƃ̓����蔻������ꂼ��`�F�b�N
	if (midBoss.getState() == characterNS::ATTACK)
	{
		// �G�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
		if (midBossAttackCollision.collidesWith(brave, collisionVector))
		{
			// �v���C���[�Ƀ_���[�W��^����
			brave.setDamagePer(1.5f);
			brave.damage(ENEMY_ATTACK);
			// �G�̍U���R���W�������Ȃ���
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
		// �G�̍U���R���W�����Ə�̏Փ˂̏ꍇ
		if (midBossAttackCollision.collidesWith(castle, collisionVector))
		{
			// ��Ƀ_���[�W��^����
			castle.setDamagePer(1.5f);
			castle.damage(ENEMY_ATTACK);
			// �G�̍U���R���W�������Ȃ���
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
		}
		// �G�̍U���R���W�����ƃo���P�[�h�̏Փ˂̏ꍇ
		if (midBossAttackCollision.collidesWith(barricades[midBoss.getNearBarricadeIndex()], collisionVector)) {
			// �o���P�[�h�Ƀ_���[�W��^����ibarricades[enemy[i].getNearBarricadeIndex()]���U���ΏۂɂȂ�͂��j
			barricades[midBoss.getNearBarricadeIndex()].damage();
			// �G�̍U���R���W�������Ȃ���
			midBossAttackCollision.setVisible(false);
			midBossAttackCollision.setActive(false);
			// �U�����ꂽ�o���P�[�h���j�󂳂ꂽ�ꍇ�A
			if (!barricades[midBoss.getNearBarricadeIndex()].getActive())
			{
				// �}�b�v�f�[�^���X�V
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
	else if (midBoss.collidesWith(brave, collisionVector))// �G���G�ƃv���C���[���Փ˂��Ă���ꍇ�A
	{
		// �G�̏�Ԃ�E�ҍU����ԂɕύX
		midBoss.setAttackState(enemyNS::ATTACK_BRAVE);
		// �E�҂���������ɉ����čU�����������ύX
		midBoss.changeAttack(collisionVector);
	}
	else if (map.getMapCol(midBoss.getTileY(), midBoss.getTileX()) == -1)	// �G���G�Ə邪�Փ˂��Ă�����U���A
	{
		// �邪��������ɉ����čU�����������ύX
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
		// �G�̏�Ԃ���U����ԂɕύX
		midBoss.setAttackState(enemyNS::ATTACK_CASTLE);
	}
	else if (map.getMapObj(midBoss.getTileY(), midBoss.getTileX()) == -2)	// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U��
	{
		// �o���P�[�h����������ɉ����čU�����������ύX
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
		// �G�̏�Ԃ��o���P�[�h�U����ԂɕύX
		midBoss.setAttackState(enemyNS::ATTACK_BARRICADE);
	}
	else if (midBoss.canMakeDecesionMoving())	// �G�������]���\�ȏ�Ԃɂ���Ƃ��A�ӎv������s���i�ޕ��������߂�
	{
		bool changeGoalDirectionFlag = false;	// �i�݂���������ς���K�v�����邩�ǂ���
												// �ŋߐڂ̃o���P�[�h��T��
		midBoss.searchNearBarricadeIndex();
		if (!midBoss.checkBarricadeOnLine())	// ��܂ł̒�����Ƀo���P�[�h���Ȃ��ꍇ�A��ւƐi�s����
		{
			// �G�̏�Ԃ���ړ����ւƕύX
			midBoss.setStateDetail(enemyNS::MOVE_CASTLE);
			midBoss.setState(characterNS::MOVE);
			// �i�݂��������ɐi�߂Ȃ��ꍇ�A������i�݂��������������_���ɕϊ�
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
		else // ��܂ł̒�����Ƀo���P�[�h�����݂���ꍇ�A
		{
			// �G�̏�Ԃ��o���P�[�h�ɐi�s���ւƕύX
			midBoss.setStateDetail(enemyNS::MOVE_BARRICADE);
			midBoss.setState(characterNS::MOVE);
			// �m��50%��x�����ɐi�ނ��ǂ������Ɍ��肵�A���̂��Ƃ�y�����ɐi�ނ��ǂ���������
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
			// �i�݂��������ɐi�߂Ȃ��ꍇ�A�����_���ɕ��������߂Ȃ���
			if (changeGoalDirectionFlag)
			{
				// �����_���ɐi�݂����������C��
				characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
				// ����ł��i�߂Ȃ��ꍇ�A�G��ҋ@��Ԃɂ��ĐÎ~������
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
	// �E�҂̍U���������ꂩ�̓G�ɓ��������ꍇ�A�U���R���W�������Ȃ���
	if (braveAttackCollidesWithAnyEnemy)
	{
		braveAttackCollision.setVisible(false);
		braveAttackCollision.setActive(false);
	}

	// ���S�`�F�b�N
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
			// �G�̕`��A�F�͓K���ɕ����Ă�A�F�ɂ���Ĕ\�͒l�𕪂���
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