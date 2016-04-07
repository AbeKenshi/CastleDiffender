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
	descriptionOn = false;
	roundOver = false;
	rect = NULL;
	remainingTime = 1500.0f;
	enemyNum = 0;
	enemy = NULL;
	enemyX = NULL;
	enemyY = NULL;
}

//==========================================================
// �f�X�g���N�^
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
	menu.setScale(1);

	// ���U���g�̃e�N�X�`��
	if (!resultTexture.initialize(graphics, RESULT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result texture"));
	// ���U���g�̉摜
	if (!result.initialize(graphics, 0, 0, 0, &resultTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result"));
	result.setScale(2);

	// ��������̃e�N�X�`��
	if (!descriptionTexture.initialize(graphics, DESCRIPTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description texture"));
	// ��������̉摜
	if (!description.initialize(graphics, 0, 0, 0, &descriptionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description"));
	description.setScale(1);

	// �}�b�v�̃e�N�X�`��
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// �}�b�v�̉摜
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �o���P�[�h�̃e�N�X�`��
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	if (!hitEffectTexture.initialize(graphics, HIT_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit effect texture"));
	// �o���P�[�h�̉摜
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!barricades[i].initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		barricades[i].setScale(1);
		if (!barricades[i].getHitEffect().initialize(graphics, hitEffectNS::WIDTH, hitEffectNS::HEIGHT, hitEffectNS::TEXTURE_COLS, &hitEffectTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hitEffect"));
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
	if (!attackEffectTexture.initialize(graphics, ATTACK_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect texture"));
	if (!braveAttackCollision.getAttackEffect().initialize(graphics, attackEffectNS::WIDTH, attackEffectNS::HEIGHT, attackEffectNS::TEXTURE_COLS, &attackEffectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect"));

	// ���̃e�N�X�`��
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!fire.initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));
	fire.setScale(1.5);

	// �G���G�̃e�N�X�`��
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	// ���{�X�̃e�N�X�`��
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));
	initializeEnemies(1, 1);

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

	return;
}

//==========================================================
// ���ׂẴQ�[���A�C�e�����X�V
//==========================================================
void TowerDiffence::update()
{
	if (menuOn)		// ���j���[��ʕ\������Z�L�[���������܂ł̓��j���[��ʂ�\����������
	{
		if (input->isKeyDown('Z')) // Z�L�[�ŃQ�[���X�^�[�g
		{
			menuOn = false;
			input->clearAll();
			audio->stopCue("title");
			audio->playCue("stage");
			roundStart();
		}
		else if (input->isKeyDown('X')) // X�L�[�ő�������\��
		{
			descriptionOn = true;
			menuOn = false;
			input->clearAll();
		}
	}
	else if (descriptionOn) // �����������X�L�[�Ń^�C�g���ɖ߂�
	{
		if (input->isKeyDown('X'))
		{
			descriptionOn = false;
			menuOn = true;
			input->clearAll();
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
			braveAttackCollision.attack(brave);
		// ���ꂼ��̓G���X�V
		for (int i = 0; i < enemyNum; i++) {
			enemy[i]->update(frameTime);
		}
		// �E�҂��X�V
		brave.update(frameTime);
		// �����X�V
		fire.update(frameTime);
		// �E�҂̍U���R���W�������X�V
		braveAttackCollision.update(frameTime);
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
	map.readMapFile(1);
	// �e�o���P�[�h��������
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i].reset();
	}
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
			if (map.getMapObj(row, col) == 0)
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
	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i]->reset();
		enemy[i]->setX(enemyX[i]);
		enemy[i]->setY(enemyY[i]);
		enemy[i]->initTileXY();
	}
	// ���������
	castle.reset();
	// ����������
	fire.reset();
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
	for (int i = 0; i < enemyNum; i++)
	{
		if (enemy[i]->getActive())
			return;
	}

	// ��2�g
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
// �l�H�m�\
//==========================================================
void TowerDiffence::ai()
{
	// �e�G���X�V
	for (int i = 0; i < enemyNum; i++)
		enemy[i]->ai(frameTime, brave);
}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;	// �Փ˔��肵���Ƃ��̏Փˑ���ւ̃x�N�g��
	bool braveAttackCollidesWithAnyEnemy = false;
	// �e�G�ɂ��ďՓ˔���
	for (int i = 0; i < enemyNum; i++) {
		// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
		if (braveAttackCollision.collidesWith(*enemy[i], collisionVector))
		{
			// �G�Ƀ_���[�W��^����
			enemy[i]->damage(BRAVE_ATTACK);
			// �����ꂩ�̓G�ɍU�������������̂Ń��[�v�𔲂�����ɍU���R���W�������Ȃ���
			braveAttackCollidesWithAnyEnemy = true;
		}

		if (enemy[i]->getState() == characterNS::DEATH)
		{
			continue;
		}

		// �G���U�����́A��ƃv���C���[�ƃo���P�[�h�Ƃ̓����蔻������ꂼ��`�F�b�N
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
			// �G�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
			if (enemy[i]->getAttackCollision().collidesWith(brave, collisionVector))
			{
				// �v���C���[�Ƀ_���[�W��^����
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) brave.setDamagePer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) brave.setDamagePer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) brave.setDamagePer(1.1f);
				brave.damage(ENEMY_ATTACK);
				// �G�̍U���R���W�������Ȃ���
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
			}
			// �G�̍U���R���W�����Ə�̏Փ˂̏ꍇ
			if (enemy[i]->getAttackCollision().collidesWith(castle, collisionVector))
			{
				// ��Ƀ_���[�W��^����
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) castle.setDamagePer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) castle.setDamagePer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) castle.setDamagePer(1.1f);
				castle.damage(ENEMY_ATTACK);
				// �G�̍U���R���W�������Ȃ���
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
			}
			// �G�̍U���R���W�����ƃo���P�[�h�̏Փ˂̏ꍇ
			if (enemy[i]->getAttackCollision().collidesWith(barricades[enemy[i]->getNearBarricadeIndex()], collisionVector)) {
				// �o���P�[�h�Ƀ_���[�W��^����ibarricades[enemy[i].getNearBarricadeIndex()]���U���ΏۂɂȂ�͂��j
				if (enemy[i]->getEnemyType() == enemyNS::NORMAL) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.0f);
				else if (enemy[i]->getEnemyType() == enemyNS::RED) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.2f);
				else if (enemy[i]->getEnemyType() == enemyNS::BLUE) barricades[enemy[i]->getNearBarricadeIndex()].setDamagerPer(1.1f);
				barricades[enemy[i]->getNearBarricadeIndex()].damage();
				// �G�̍U���R���W�������Ȃ���
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
				// �U�����ꂽ�o���P�[�h���j�󂳂ꂽ�ꍇ�A
				if (!barricades[enemy[i]->getNearBarricadeIndex()].getActive())
				{
					// �}�b�v�f�[�^���X�V
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

		// ���ƎG���G�̏Փ˂̏ꍇ
		if (fire.collidesWith(*enemy[i], collisionVector))
		{
			enemy[i]->damage(FIRE);
			fire.setVisible(false);
			fire.setActive(false);
		}

		// �U�����Ȃ�΍s���I���͍s��Ȃ�
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
		}
		else if (enemy[i]->collidesWith(brave, collisionVector))// �G���G�ƃv���C���[���Փ˂��Ă���ꍇ�A
		{
			// �G�̏�Ԃ�E�ҍU����ԂɕύX
			enemy[i]->setAttackState(enemyNS::ATTACK_BRAVE);
			// �E�҂���������ɉ����čU�����������ύX
			enemy[i]->changeAttack(collisionVector);
		}
		else if (map.getMapObj(enemy[i]->getTileY(), enemy[i]->getTileX()) == 1)	// �G���G�Ə邪�Փ˂��Ă�����U���A
		{
			// �邪��������ɉ����čU�����������ύX
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
			// �G�̏�Ԃ���U����ԂɕύX
			enemy[i]->setAttackState(enemyNS::ATTACK_CASTLE);
		}
		else if (map.getMapObj(enemy[i]->getTileY(), enemy[i]->getTileX()) == -2)	// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U��
		{
			// �o���P�[�h����������ɉ����čU�����������ύX
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
			// �G�̏�Ԃ��o���P�[�h�U����ԂɕύX
			enemy[i]->setAttackState(enemyNS::ATTACK_BARRICADE);
		}
		else if (enemy[i]->canMakeDecesionMoving())	// �G�������]���\�ȏ�Ԃɂ���Ƃ��A�ӎv������s���i�ޕ��������߂�
		{
			bool changeGoalDirectionFlag = false;	// �i�݂���������ς���K�v�����邩�ǂ���
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
				// �i�݂��������ɐi�߂Ȃ��ꍇ�A�����_���ɕ��������߂Ȃ���
				if (changeGoalDirectionFlag)
				{
					// �����_���ɐi�݂����������C��
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// ����ł��i�߂Ȃ��ꍇ�A�G��ҋ@��Ԃɂ��ĐÎ~������
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
				// �ŋߐڂ̃o���P�[�h��T��
				enemy[i]->searchNearBarricadeIndex();
				if (!enemy[i]->checkBarricadeOnLine())	// ��܂ł̒�����Ƀo���P�[�h���Ȃ��ꍇ�A��ւƐi�s����
				{
					// �G�̏�Ԃ���ړ����ւƕύX
					enemy[i]->setStateDetail(enemyNS::MOVE_CASTLE);
					enemy[i]->setState(characterNS::MOVE);
					// �i�݂��������ɐi�߂Ȃ��ꍇ�A������i�݂��������������_���ɕϊ�
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
				else // ��܂ł̒�����Ƀo���P�[�h�����݂���ꍇ�A
				{
					// �G�̏�Ԃ��o���P�[�h�ɐi�s���ւƕύX
					enemy[i]->setStateDetail(enemyNS::MOVE_BARRICADE);
					enemy[i]->setState(characterNS::MOVE);
					// �m��50%��x�����ɐi�ނ��ǂ������Ɍ��肵�A���̂��Ƃ�y�����ɐi�ނ��ǂ���������
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
				// �i�݂��������ɐi�߂Ȃ��ꍇ�A�����_���ɕ��������߂Ȃ���
				if (changeGoalDirectionFlag)
				{
					// �����_���ɐi�݂����������C��
					characterNS::DIRECTION newDirection = (characterNS::DIRECTION) (rand() % 4);
					// ����ł��i�߂Ȃ��ꍇ�A�G��ҋ@��Ԃɂ��ĐÎ~������
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

		char str[128]  = "PUSH Z KEY TO START!";
		char str2[128] = "PUSH X KEY TO THE OPERATION DESCRIPTION";
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
		fontCK->print(str, 373, 453);
		fontCK->setFontHeight(20);
		fontCK->print(str2, 343, 553);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->setFontHeight(35);
		fontCK->print(str, 370, 450);
		fontCK->setFontHeight(20);
		fontCK->print(str2, 340, 550);
	}
	else if (descriptionOn)
	{
		menu.draw();
		description.setX(160);
		description.setY(90);
		description.draw();
	}
	else if (roundOver)
	{
		result.draw();
	}
	else
	{
		// �}�b�v�ƃo���P�[�h�͏��߂����`��
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
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			barricades[i].draw();   // �I�u�W�F�N�g��`��
			barricades[i].getHitEffect().draw();
		}

		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

		for (int i = 0; i < enemyNum; i++) {
			float tmpX = enemy[i]->getX();
			float tmpY = enemy[i]->getY();
			enemy[i]->setX(tmpX - enemy[i]->getWidth() * (enemy[i]->getScale() - 1) / 2.0);
			enemy[i]->setY(tmpY - enemy[i]->getHeight() * (enemy[i]->getScale() - 1) / 2.0 - 10);
			// �G�̕`��A�F�͓K���ɕ����Ă�A�F�ɂ���Ĕ\�͒l�𕪂���
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

//==========================================================
// �w�肳�ꂽ�X�e�[�W�̓G�f�[�^��ǂݍ���
//==========================================================
void TowerDiffence::readEnemyFile(int stageNum, int enemyWave)
{
	string enemyDataFilename = "stageData\\stage" + std::to_string(stageNum) + "\\enemy" + std::to_string(enemyWave) + "\\enemydata.csv";

	ifstream* ifs = new ifstream(enemyDataFilename);
	//csv�t�@�C����1�s���ǂݍ���
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
// �w�肳�ꂽ�X�e�[�W�A�h�̓G�f�[�^��ǂݍ��ݓG������������
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

		// �G���G�̓����蔻��p
		if (!enemy[i]->getAttackCollision().initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
		enemy[i]->reset();
		enemy[i]->setX(enemyX[i]);
		enemy[i]->setY(enemyY[i]);
		enemy[i]->initTileXY();
	}
}

//=============================================================================
// �R���\�[���R�}���h������
//=============================================================================
void TowerDiffence::consoleCommand()
{
	command = console->getCommand();    // �R���\�[������̃R�}���h���擾
	if (command == "")                  // �R�}���h���Ȃ��ꍇ
		return;

	if (command == "help")              // �uhelp�v�R�}���h�̏ꍇ
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
		fpsOn = !fpsOn;                 // �t���[�����[�g�̕\����؂�ւ���
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