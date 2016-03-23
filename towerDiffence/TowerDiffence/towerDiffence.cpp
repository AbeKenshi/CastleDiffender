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
	if (!tile.initialize(graphics, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �o���P�[�h�̃e�N�X�`��
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	// �o���P�[�h�̉摜
	if (!barricade.initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
	barricade.setScale(1);
	barricade.setX(0);
	barricade.setY(0);

	// �E�҂̃e�N�X�`��
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// �E��
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);

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
		brave.update(frameTime);
		enemy.update(frameTime);
		fire.update(frameTime);
		barricade.update(frameTime);
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

}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	VECTOR2 collisionVector;

	if (brave.collidesWith(barricade, collisionVector)) {
		// �j�󏈗�
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
		// �X�e�[�W�̕`��
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // �}�b�v�̊e�s������
		{
			tile.setY((float)(row*mapNS::TEXTURE_SIZE));      // �^�C����Y��ݒ�
			barricade.setY((float)(row*barricadeNS::WIDTH));  // �I�u�W�F�N�g��Y��ݒ�
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // �}�b�v�̊e�������
			{
				if (mapNS::tileMap[row][col] >= 0)            // �^�C�������݂���ꍇ
				{
					tile.setCurrentFrame(mapNS::tileMap[row][col]);                       // �^�C���̃e�N�X�`����ݒ�
					tile.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);                   // �^�C����X��ݒ�
					if (tile.getX() > -mapNS::TEXTURE_SIZE && tile.getX() < GAME_WIDTH)   // �^�C������ʏ�ɂ��邩�ǂ���
						tile.draw();    // �^�C����`��
				}
				if (mapNS::tileObj[row][col] >= 0)
				{
					barricade.setCurrentFrame(mapNS::tileObj[row][col]);							// �I�u�W�F�N�g�̃e�N�X�`����ݒ�
					barricade.setX((float)(col*mapNS::TEXTURE_SIZE) + mapX);						// �I�u�W�F�N�g��X��ݒ�
					if (barricade.getX() > -mapNS::TEXTURE_SIZE && barricade.getX() < GAME_WIDTH)   // �I�u�W�F�N�g����ʏ�ɂ��邩�ǂ���
						barricade.draw();   // �I�u�W�F�N�g��`��
				}
			}
		}
		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

		enemy.draw();
		fire.draw();
		brave.draw();
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