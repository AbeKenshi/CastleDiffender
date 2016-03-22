// TowerDiffence�̓Q�[���̃��C���N���X
#include "towerDiffence.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	menuOn = true;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
TowerDiffence::~TowerDiffence()
{
	releaseAll();	// ���ׂẴO���t�B�b�N�X�A�C�e���ɂ��āAonLostDevice()���Ăяo��
}

//==========================================================
// �Q�[����������
// �G���[����GameError���X���[
//==========================================================
void TowerDiffence::initialize(HWND hwnd)
{
	Game::initialize(hwnd);	// GameError���X���[

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
	if (!tile.initialize(graphics, towerDiffenceNS::TEXTURE_SIZE, towerDiffenceNS::TEXTURE_SIZE, towerDiffenceNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �E�҂̃e�N�X�`��
	if (!braveTexture.initialize(graphics, BRAVE_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move texture"));
	// �E��
	if (!brave.initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	brave.setScale(2);
	brave.setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	brave.setCurrentFrame(braveNS::MOVE_UP_START_FRAME);

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
		brave.update(frameTime);
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

}

//==========================================================
// �Q�[���A�C�e���������_�[
//==========================================================
void TowerDiffence::render()
{
	graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

	if (menuOn)
		menu.draw();
	else
	{
		// �X�e�[�W�̕`��
		for (int row = 0; row<towerDiffenceNS::MAP_HEIGHT; row++)       // �}�b�v�̊e�s������
		{
			tile.setY((float)(row*towerDiffenceNS::TEXTURE_SIZE));      // �^�C����Y��ݒ�
			for (int col = 0; col<towerDiffenceNS::MAP_WIDTH; col++)    // �}�b�v�̊e�������
			{
				if (towerDiffenceNS::tileMap[row][col] >= 0)            // �^�C�������݂���ꍇ
				{
					tile.setCurrentFrame(towerDiffenceNS::tileMap[row][col]);                       // �^�C���̃e�N�X�`����ݒ�
					tile.setX((float)(col*towerDiffenceNS::TEXTURE_SIZE) + mapX);                   // �^�C����X��ݒ�
					if (tile.getX() > -towerDiffenceNS::TEXTURE_SIZE && tile.getX() < GAME_WIDTH)   // �^�C������ʏ�ɂ��邩�ǂ���
						tile.draw();    // �^�C����`��
				}
			}
		}

		brave.draw();
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

	Game::releaseAll();
	return;
}

//==========================================================
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�ꍇ
// ���ׂẴT�[�t�F�C�X���č쐬
//==========================================================
void TowerDiffence::resetAll()
{
	braveTexture.onResetDevice();
	menuTexture.onResetDevice();

	Game::resetAll();
	return;
}