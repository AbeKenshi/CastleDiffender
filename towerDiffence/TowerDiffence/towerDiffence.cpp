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
	brave.setScale(2);
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
	// �G���G�̓����蔻��p
	if (!enemyAttackCollision.initialize(this, enemyAttackCollisionNS::WIDTH, enemyAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
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
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setScale(2);
	enemy.setMapPointer(&map);
	enemy.setBarricadesPointer(barricades);

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
	brave.reset();
	enemy.reset();
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
	enemy.ai(frameTime, brave);
}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;
	// �v���C���[�ƎG���G�̏Փ˂̏ꍇ
	if (enemy.collidesWith(brave, collisionVector))
	{
		enemy.setNearPlayer(true);
	}
	else
		enemy.setNearPlayer(false);
	
	// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
	if (braveAttackCollision.collidesWith(enemy, collisionVector))
	{
		enemy.damage(BRAVE_ATTACK);
		braveAttackCollision.setVisible(false);
		braveAttackCollision.setActive(false);
	}
	// �G�̍U���R���W�����ƃv���C���[�̏Փ˂̏ꍇ
	if (enemyAttackCollision.collidesWith(brave, collisionVector))
	{
		brave.damage(ENEMY_ATTACK);
		enemyAttackCollision.setVisible(false);
		enemyAttackCollision.setActive(false);
	}
	// �G�̍U���R���W�����Ə�̏Փ˂̏ꍇ
	if (enemyAttackCollision.collidesWith(castle, collisionVector))
	{
		castle.damage(ENEMY_ATTACK);
		enemyAttackCollision.setVisible(false);
		enemyAttackCollision.setActive(false);
	}
	// ���ƎG���G�̏Փ˂̏ꍇ
	if (fire.collidesWith(enemy, collisionVector))
	{
		enemy.damage(FIRE);
		fire.setVisible(false);
		fire.setActive(false);
	}

	// �U�����Ȃ�΍s���I���͍s��Ȃ�
	if (enemy.getState() == enemyNS::ATTACK_BARRICADE || enemy.getState() == enemyNS::ATTACK_BRAVE || enemy.getState() == enemyNS::ATTACK_CASTLE || enemy.getState() == enemyNS::PRE_ATTACK)
	{
	}
	else if (enemy.collidesWith(brave, collisionVector))// �G���G�ƃv���C���[�̏Փ˔���
	{
		enemy.changeAttack(collisionVector);
		enemy.setAttackState(enemyNS::ATTACK_BRAVE);
	}
	else if (enemy.collidesWith(castle, collisionVector))	// �G���G�Ə�̏Փ˔���
	{
		enemy.changeAttack(collisionVector);
		enemy.setAttackState(enemyNS::ATTACK_CASTLE);
	}
	else if (!enemy.checkBarricadeOnLine(castle.getCenterX(), castle.getCenterY()))	// ��܂ł̒�����Ƀo���P�[�h�����邩���`�F�b�N
	{
		enemy.setState(enemyNS::MOVE_CASTLE);
		VECTOR2 pos;
		pos.x = castle.getCenterX();
		pos.y = castle.getCenterY();
		enemy.setGoalPost(pos);
	}
	else 
	{
		// �ŋߐڂ̃o���P�[�h��T��
		int nearBarricadeIndex = enemy.searchNearBarricadeIndex();
		// �ŋߐڂ̃o���P�[�h�ɏՓ˂��Ă�����U���A����ȊO�Ȃ�o���P�[�h�Ɍ������B
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
	// �G�ƃo���P�[�h�̏Փ�, 1�ł��Փ˂��Ă�����G�ɒʒm
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

	// �G�̍U���R���W�����ƃo���P�[�h�̏Փ�
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (enemyAttackCollision.collidesWith(barricades[i], collisionVector)) {
			barricades[i].damage();
			enemyAttackCollision.setVisible(false);
			enemyAttackCollision.setActive(false);
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
					map.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);                    // �^�C����X��ݒ�
					if (map.getX() > -mapNS::TEXTURE_SIZE && map.getX() < GAME_WIDTH)     // �^�C������ʏ�ɂ��邩�ǂ���
						map.draw();    // �^�C����`��
				}
				if (map.getMapObj(row, col) >= 0)
				{
					//barricades[count].setCurrentFrame(map.getMapObj(row, col));		    							// �I�u�W�F�N�g�̃e�N�X�`����ݒ�
					barricades[count].setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);								// �I�u�W�F�N�g��X��ݒ�
					barricades[count].setY((float)(row*barricadeNS::WIDTH));										// �I�u�W�F�N�g��Y��ݒ�
					if (barricades[count].getX() > -mapNS::TEXTURE_SIZE && barricades[count].getX() < GAME_WIDTH)	// �I�u�W�F�N�g����ʏ�ɂ��邩�ǂ���
					{
						barricades[count].draw();   // �I�u�W�F�N�g��`��
						count++;
					}
				}
			}
		}

		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

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