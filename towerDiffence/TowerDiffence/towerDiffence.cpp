// TowerDiffence�̓Q�[���̃��C���N���X
#include "towerDiffence.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	menuOn = true;
	rect = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
TowerDiffence::~TowerDiffence()
{
	safeDelete(rect);
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

	// ���j���[�̃e�N�X�`��
	if (!menuTexture.initialize(graphics, MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// ���j���[�̉摜
	if (!menu.initialize(graphics, 0, 0, 0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	menu.setScale(2);

	// �}�b�v�̃e�N�X�`��
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// �}�b�v�̉摜
	if (!map.initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �o���P�[�h�I�u�W�F�N�g������
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		barricades[i] = *(new Barricade());
	}

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
	if (!castle.initialize(this, castleNS::WIDTH, castleNS::HEIGHT, 0, &castleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle"));
	castle.setScale(120.0f / 96.0f);

	// �E�҂̃e�N�X�`��
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// �E��
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);


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

	// �G���G�̃e�N�X�`��
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	if (!enemy.initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setScale(2);

	// �_�b�V���{�[�h
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	barGraph.initialize(graphics, &dashboardTextures, towerDiffenceNS::BAR_GRAPH_X, towerDiffenceNS::BAR_GRAPH_Y, 0.5f, 20, graphicsNS::RED);
	barGraph.set(brave.getHealth());

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
// �v���C�̐V�������E���h���J�n
//==========================================================
void TowerDiffence::roundStart()
{

}

//==========================================================
// �l�H�m�\
//==========================================================
void TowerDiffence::ai()
{
	enemy.ai(frameTime, brave, barricades);
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
	// ���ƎG���G�̏Փ˂̏ꍇ
	if (fire.collidesWith(enemy, collisionVector))
	{
		enemy.damage(FIRE);
		fire.setVisible(false);
		fire.setActive(false);
	}
	// �v���C���[�ƃo���P�[�h�̏Փ�
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++) {
		if (enemy.collidesWith(barricades[i], collisionVector)) {
			barricades[i].setActive(false);
			barricades[i].setVisible(false);

		}

		barricades[i].draw();
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
					barricades[count].setCurrentFrame(map.getMapObj(row, col));		    							// �I�u�W�F�N�g�̃e�N�X�`����ݒ�
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

		castle.draw();
		enemy.draw();
		fire.draw();
		brave.draw();
		braveAttackCollision.draw();
		enemyAttackCollision.draw();
		barGraph.set(brave.getHealth());
		barGraph.draw(graphicsNS::FILTER);	// �̗̓o�[��`��
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
	dashboardTextures.onLostDevice();
	braveTexture.onResetDevice();
	menuTexture.onResetDevice();
	safeOnResetDevice(rect);
	Game::resetAll();
	return;
}