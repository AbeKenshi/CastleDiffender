//==========================================================
/// @file
/// @brief    towerDiffence.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "towerDiffence.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
TowerDiffence::TowerDiffence()
{
	initialized = false;
	fontCK = new Text();   // sprite based font
	menuOn = true;
	stageSelectOn = false;
	descriptionOn = false;
	rect = NULL;
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

	// �X�e�[�W�I����ʂ̃e�N�X�`��
	if (!stageSelectTexture.initialize(graphics, STAGE_SELECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage select texture"));
	// �X�e�[�W�I����ʂ̉摜
	if (!stageSelect.initialize(graphics, 0, 0, 0, &stageSelectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage select"));

	// ���U���g�̃e�N�X�`��
	if (!resultTexture.initialize(graphics, RESULT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result texture"));
	// ���U���g�̉摜
	if (!result.initialize(graphics, 0, 0, 0, &resultTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing result"));
	result.setX(GAME_WIDTH / 2.0f - result.getWidth() / 2.0f);
	result.setY((float)-result.getHeight());

	// �X�e�[�W�N���A��ʂ̃e�N�X�`��
	if (!stageClearTexture.initialize(graphics, STAGE_CLEAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage clear texture"));
	// �X�e�[�W�N���A�摜
	if (!stageClear.initialize(graphics, 0, 0, 0, &stageClearTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing stage clear"));
	stageClear.setX(GAME_WIDTH / 2.0f - stageClear.getWidth() / 2.0f);
	stageClear.setY((float)GAME_HEIGHT);

	// ��������̃e�N�X�`��
	if (!descriptionTexture.initialize(graphics, DESCRIPTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description texture"));
	// ��������̉摜
	if (!description.initialize(graphics, 0, 0, 0, &descriptionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing description"));

	// �}�b�v�̃e�N�X�`��
	if (!tileTexture.initialize(graphics, TILE_IMAGES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map texture"));
	// �}�b�v�̉摜
	if (!stage.getMap().initialize(this, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_SIZE, mapNS::TEXTURE_COLS, &tileTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));

	// �o���P�[�h�̃e�N�X�`��
	if (!barricadeTexture.initialize(graphics, BARRICADE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade texture"));
	if (!hitEffectTexture.initialize(graphics, HIT_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit effect texture"));
	// �o���P�[�h�̉摜
	for (int i = 0; i < mapNS::BARRICADE_NUM; i++)
	{
		if (!stage.getBarricade(i).initialize(this, barricadeNS::WIDTH, barricadeNS::HEIGHT, barricadeNS::TEXTURE_COLS, &barricadeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing barricade"));
		stage.getBarricade(i).setScale(1);
		if (!stage.getBarricade(i).getHitEffect().initialize(graphics, hitEffectNS::WIDTH, hitEffectNS::HEIGHT, hitEffectNS::TEXTURE_COLS, &hitEffectTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hitEffect"));
	}

	// ��̃e�N�X�`��
	if (!castleTexture.initialize(graphics, CASTLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing castle texture"));
	// ��̉摜
	if (!stage.getCastle().initialize(this, castleNS::WIDTH, castleNS::HEIGHT, castleNS::TEXTURE_COLS, &castleTexture))
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
	if (!stage.getBrave().initialize(this, braveNS::WIDTH, braveNS::HEIGHT, braveNS::TEXTURE_COLS, &braveTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave_move"));
	stage.getBrave().setScale(1.5);
	stage.getBrave().setFrames(braveNS::MOVE_UP_START_FRAME, braveNS::MOVE_UP_END_FRAME);
	stage.getBrave().setCurrentFrame(braveNS::MOVE_UP_START_FRAME);
	stage.getBrave().setMapPointer(stage.getMap());

	// �E�҂̃A�C�R���̃e�N�X�`��
	if (!braveIconTexture.initialize(graphics, BRAVE_ICON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon texture"));
	// �E�҂̃A�C�R���̉摜
	if (!braveIcon.initialize(graphics, braveIconNS::WIDTH, braveIconNS::HEIGHT, braveIconNS::TEXTURE_COLS, &braveIconTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing brave icon"));
	braveIcon.linkEntity(stage.getBrave());

	// �E�҂̓����蔻��p�̃e�N�X�`��
	if (!attackCollisionTexture.initialize(graphics, COLLISION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision texture"));
	// �E�҂̂����蔻��p
	if (!stage.getBrave().getBraveAttackCollision().initialize(this, braveAttackCollisionNS::WIDTH, braveAttackCollisionNS::HEIGHT, 0, &attackCollisionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack collision"));
	if (!attackEffectTexture.initialize(graphics, ATTACK_EFFECT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect texture"));
	if (!stage.getBrave().getBraveAttackCollision().getAttackEffect().initialize(graphics, attackEffectNS::WIDTH, attackEffectNS::HEIGHT, attackEffectNS::TEXTURE_COLS, &attackEffectTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing attack effect"));

	// ���̃e�N�X�`��
	if (!fireTexture.initialize(graphics, FIRE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire texture"));
	if (!stage.getBrave().getFire().initialize(this, fireNS::WIDTH, fireNS::HEIGHT, fireNS::TEXTURE_COLS, &fireTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing fire"));
	stage.getBrave().getFire().setScale(1.5);

	// �G���G�̃e�N�X�`��
	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	// ���{�X�̃e�N�X�`��
	if (!midBossTexture.initialize(graphics, MID_BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss texture"));

	// �_�b�V���{�[�h
	if (!dashboardTextures.initialize(graphics, DASHBOARD_TEXTURES))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dashboard textures"));
	braveHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_HEALTH_BAR_X, towerDiffenceNS::BRAVE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::RED);
	braveHealthBar.set(stage.getBrave().getHealth());
	braveMpBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::BRAVE_MP_BAR_X, towerDiffenceNS::BRAVE_MP_BAR_Y, 0.5f, 100, graphicsNS::GREEN);
	braveMpBar.set((float)stage.getBrave().getMP());
	castleHealthBar.initialize(graphics, &dashboardTextures, towerDiffenceNS::CASTLE_HEALTH_BAR_X + 40, towerDiffenceNS::CASTLE_HEALTH_BAR_Y, 0.5f, 100, graphicsNS::BLUE);
	castleHealthBar.set(stage.getCastle().getHealth());

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
		if (input->isKeyDown('Z')) // Z�L�[�ŃX�e�[�W�I����ʂɈȍ~
		{
			menuOn = false;
			input->clearAll();
			stageSelectOn = true;
			stage.reset();

			rect->setX(380);
			rect->setY(80);
			rect->setWidth(510);
			rect->setHeight(81);
			rect->setBackColor(SETCOLOR_ARGB(50, 120, 120, 255));
			rect->reset();
		}
		else if (input->isKeyDown('X')) // X�L�[�ő�������\��
		{
			descriptionOn = true;
			menuOn = false;
			input->clearAll();
		}
		else if (input->isKeyDown('E'))
		{
			exitGame();
		}
	}
	else if (stageSelectOn)
	{
		if (input->isKeyDown('Z'))	// Z�L�[�ŃX�e�[�W����
		{
			stageSelectOn = false;
			audio->stopCue("title");
			roundStart();

			rect->setX((float)rectNS::X);
			rect->setY((float)rectNS::Y);
			rect->setWidth(rectNS::WIDTH);
			rect->setHeight(rectNS::HEIGHT);
			rect->setBackColor(rectNS::BACK_COLOR);
			rect->reset();
		}
		else if (input->isKeyDown(BRAVE_DOWN_KEY))
		{
			if (stage.getStageNum() < 3 - 1)
			{
				stage.setStageNum(stage.getStageNum() + 1);
				rect->setY(rect->getY() + 240);
				rect->reset();
			}
			input->clearAll();
		}
		else if (input->isKeyDown(BRAVE_UP_KEY))
		{
			if (stage.getStageNum() > 0)
			{
				stage.setStageNum(stage.getStageNum() - 1);
				rect->setY(rect->getY() - 240);
				rect->reset();
			}
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
	else if (stage.getRoundOver())	// �Q�[���I�[�o�[����Z�������ꂽ�烁�j���[��ʂɖ߂�AX�������ꂽ��v���O�����I��
	{
		if (result.getY() > 50)
		{
			if (input->isKeyDown('X'))
			{
				menuOn = true;
				input->clearAll();
				audio->stopCue("gameover");
				audio->playCue("title");
			}
			else if (input->isKeyDown('E'))
			{
				exitGame();
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
	else if (stage.getClearedStage())
	{
		if (stageClear.getY() < 250)
		{
			if (input->isKeyDown('X'))
			{
				menuOn = true;
				input->clearAll();
				audio->stopCue("clear");
				audio->playCue("title");
				stage.setClearedStage(false);
			}
			else if (input->isKeyDown('E'))
			{
				exitGame();
			}
			else if (input->isKeyDown('Z'))
			{
				input->clearAll();
				audio->stopCue("clear");
				roundStart();
			}
		}
		else
		{
			stageClear.setY(stageClear.getY() - frameTime * 320.0f);
		}
	}
	else				// �Q�[�����̏ꍇ�A
	{
		if (roundTimer > 0.0f)
		{
			roundTimer -= frameTime;
			return;
		}
		stage.runStage(frameTime);
		if (stage.getInitializedEnemies())
		{
			initializeEnemiesTexture();
		}
		if (stage.getRoundOver())
		{
			gameOver();
		}
		if (stage.getClearedStage())
		{
			clearStage();
		}

		// �E�҂̃A�C�R���摜���X�V
		braveIcon.update(frameTime);
	}
}

//==========================================================
// �v���C�̐V�������E���h���J�n
//==========================================================
void TowerDiffence::roundStart()
{
	stage.roundStart();
	result.setY((float)-result.getHeight());
	stageClear.setY((float)GAME_HEIGHT);
	braveIcon.reset();
	roundTimer = towerDiffenceNS::ROUND_TIME;
	audio->playCue("stage");
}

//==========================================================
// �l�H�m�\
//==========================================================
void TowerDiffence::ai()
{
	stage.ai(frameTime);
}

//==========================================================
// �Փ˂�����
//==========================================================
void TowerDiffence::collisions()
{
	stage.collisions();
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

		char str[128] = "PUSH Z KEY : STAGE SELECT";
		char str2[128] = "PUSH X KEY : OPERATION DESCRIPTION";
		char str3[128] = "PUSH E KEY : EXIT";
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
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
		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n
		char str[128] = "PUSH Z KEY : START STAGE!";
		fontCK->setFontHeight(35);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
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
		// �}�b�v�ƃo���P�[�h�͏��߂����`��
		for (int row = 0; row<mapNS::MAP_HEIGHT; row++)       // �}�b�v�̊e�s������
		{
			stage.getMap().setY((float)(row*mapNS::TEXTURE_SIZE));       // �^�C����Y��ݒ�
			for (int col = 0; col<mapNS::MAP_WIDTH; col++)    // �}�b�v�̊e�������
			{
				if (stage.getMap().getMapData(row, col) >= 0)            // �^�C�������݂���ꍇ
				{
					stage.getMap().setCurrentFrame(stage.getMap().getMapData(row, col));                       // �^�C���̃e�N�X�`����ݒ�
					stage.getMap().setX((float)(col*mapNS::TEXTURE_SIZE));                    // �^�C����X��ݒ�
					if (stage.getMap().getX() > -mapNS::TEXTURE_SIZE && stage.getMap().getX() < GAME_WIDTH)     // �^�C������ʏ�ɂ��邩�ǂ���
						stage.getMap().draw();    // �^�C����`��
				}
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			stage.getBarricade(i).draw();   // �I�u�W�F�N�g��`��
			stage.getBarricade(i).getHitEffect().draw();
		}

		graphics->spriteEnd();		// �X�v���C�g�̕`����J�n
		rect->draw();
		graphics->spriteBegin();	// �X�v���C�g�̕`����J�n

		for (int i = 0; i < stage.getEnemyNum(); i++) {
			float tmpX = stage.getEnemy(i).getX();
			float tmpY = stage.getEnemy(i).getY();
			stage.getEnemy(i).setX((float)(tmpX - stage.getEnemy(i).getWidth() * (stage.getEnemy(i).getScale() - 1) / 2.0));
			stage.getEnemy(i).setY((float)(tmpY - stage.getEnemy(i).getHeight() * (stage.getEnemy(i).getScale() - 1) / 2.0 - 10.0));
			switch (stage.getEnemy(i).getEnemyType())
			{
			case enemyNS::RED:
				stage.getEnemy(i).draw(graphicsNS::RED);
				break;
			case enemyNS::BLUE:
				stage.getEnemy(i).draw(graphicsNS::BLUE);
				break;
			default:
				stage.getEnemy(i).draw(graphicsNS::WHITE);
				break;
			}
			stage.getEnemy(i).getAttackCollision().draw();
			stage.getEnemy(i).setX(tmpX);
			stage.getEnemy(i).setY(tmpY);
		}
		braveHpText.draw();
		braveMpText.draw();
		castleHpText.draw();
		braveIcon.draw();
		castleIcon.draw();
		stage.getCastle().draw();
		stage.getBrave().getFire().draw();
		float tmpX = stage.getBrave().getX();
		float tmpY = stage.getBrave().getY();
		stage.getBrave().setX((float)(tmpX - stage.getBrave().getWidth() * (stage.getBrave().getScale() - 1) / 2.0));
		stage.getBrave().setY((float)(tmpY - stage.getBrave().getHeight() * (stage.getBrave().getScale() - 1) / 2.0 - 10));
		stage.getBrave().draw(graphicsNS::WHITE);
		stage.getBrave().setX(tmpX);
		stage.getBrave().setY(tmpY);
		stage.getBrave().getBraveAttackCollision().draw();
		stage.getBrave().getBraveAttackCollision().getAttackEffect().draw();
		braveHealthBar.set(stage.getBrave().getHealth());
		braveMpBar.set((float)stage.getBrave().getMP());
		castleHealthBar.set(stage.getCastle().getHealth());
		braveHealthBar.draw(graphicsNS::FILTER);	// �̗̓o�[��`��
		braveMpBar.draw(graphicsNS::FILTER);
		castleHealthBar.draw(graphicsNS::FILTER);
		// shadow
		char str[128] = "TIME-";
		char time[5] = { 0 };
		sprintf_s(time, "%04d", (int)stage.getRemainingTime());
		strcat_s(str, time);
		fontCK->setFontHeight(40);
		fontCK->setFontColor(SETCOLOR_ARGB(128, 128, 128, 128));  // shadow grey
		fontCK->print(str, 512, 10);
		fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 255));
		fontCK->print(str, 505, 7);
		fontCK->setFontHeight(14);
		if (roundTimer > 0.0f)
		{
			string str1 = "STAGE" + to_string(stage.getStageNum() + 1);
			char str2[128] = "START!";
			float fontSize = 60.0f;
			float fastSpeed = 900.0f;
			float secondSpeed = 50.0f;
			float initX = -fontSize * 6.0f;
			fontCK->setFontHeight((UINT)fontSize);
			float T = (GAME_WIDTH - initX * 2.0f - fontSize * 6) / (2.0f * fastSpeed);
			if (roundTimer > towerDiffenceNS::ROUND_TIME - T)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer) * fastSpeed), 400);
			}
			else if (roundTimer > towerDiffenceNS::ROUND_TIME - T * 2.0f)
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T) * secondSpeed + fastSpeed * T), 400);
			}
			else
			{
				fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 303);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 403);
				fontCK->setFontColor(graphicsNS::BLUE);
				fontCK->print(str1, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 300);
				fontCK->setFontColor(graphicsNS::RED);
				fontCK->print(str2, (int)(initX + (towerDiffenceNS::ROUND_TIME - roundTimer - T * 2.0f) * fastSpeed + (fastSpeed + secondSpeed) * T), 400);
			}
		}
	}
	if (stage.getRoundOver())
	{
		result.draw();
		if (result.getY() > 50)
		{
			char str[128] = "CONTINUE?";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(result.getHeight() + result.getY()));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(result.getHeight() + result.getY() - 3));
			char str2[128] = "PUSH Z KEY : RETRY STAGE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55));
			char str3[128] = "PUSH X KEY : RETURN TITLE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55 * 2));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55 * 2));
			char str4[128] = "PUSH E KEY : EXIT";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() + 55 * 3));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(result.getHeight() + result.getY() - 3 + 55 * 3));
		}
	}
	else if (stage.getClearedStage())
	{
		stageClear.draw();
		if (stageClear.getY() < 250)
		{
			char str[128] = "CONTINUE?";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(stageClear.getHeight() + stageClear.getY()));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str, (int)(GAME_WIDTH / 2 - 35 * 9 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3));
			char str2[128] = "PUSH Z KEY : RETRY STAGE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str2, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55));
			char str3[128] = "PUSH X KEY : RETURN TITLE";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55 * 2));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str3, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55 * 2));
			char str4[128] = "PUSH E KEY : EXIT";
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 0, 0, 0));  // �e
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() + 55 * 3));
			fontCK->setFontHeight(35);
			fontCK->setFontColor(SETCOLOR_ARGB(255, 255, 255, 50));
			fontCK->print(str4, (int)(GAME_WIDTH / 2 - 35 * 20 / 2), (int)(stageClear.getHeight() + stageClear.getY() - 3 + 55 * 3));
		}
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
	stageSelectTexture.onLostDevice();
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
	stageSelectTexture.onResetDevice();
	safeOnResetDevice(rect);
	Game::resetAll();
	return;
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
				if (stage.getMap().getMapObj(i, j) >= 0)
				{
					str += " " + to_string(stage.getMap().getMapObj(i, j)) + ",";
				}
				else
				{
					str += to_string(stage.getMap().getMapObj(i, j)) + ",";
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
				if (stage.getMap().getMapCol(i, j) >= 0)
				{
					str += " " + to_string(stage.getMap().getMapCol(i, j)) + ",";
				}
				else
				{
					str += to_string(stage.getMap().getMapCol(i, j)) + ",";
				}
			}
			console->print(str);
		}
	}
	if (command == "barricade")
	{
		for (int i = 0; i < 8; ++i)
		{
			console->print(to_string(stage.getBarricade(i).getActive()));
		}
	}
	if (command == "enemystate")
	{
		for (int i = 0; i < stage.getEnemyNum(); ++i)
		{
			console->print(to_string(stage.getEnemy(i).getState()));
		}
	}
	if (command == "enemytile")
	{
		for (int i = 0; i < stage.getEnemyNum(); ++i)
		{
			console->print(to_string(stage.getEnemy(i).getTileX()) + "," + to_string(stage.getEnemy(i).getTileY()));
		}
	}
}

//==========================================================
// GameOver���ɌĂяo��
//==========================================================
void TowerDiffence::gameOver()
{
	audio->stopCue("stage");
	audio->playCue("gameover");
}

//==========================================================
// �X�e�[�W�N���A���ɌĂяo��
//==========================================================
void TowerDiffence::clearStage()
{
	audio->stopCue("stage");
	audio->playCue("clear");
}

//==========================================================
// �G�̃e�N�X�`��������������
//==========================================================
void TowerDiffence::initializeEnemiesTexture()
{
	for (int i = 0; i < stage.getEnemyNum(); i++) {
		if (typeid(stage.getEnemy(i)) == typeid(Enemy))
		{
			if (!stage.getEnemy(i).initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		}
		else if (typeid(stage.getEnemy(i)) == typeid(MidBoss))
		{
			if (!stage.getEnemy(i).initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &midBossTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midBoss"));
		}

		// �G���G�̓����蔻��p
		if (!stage.getEnemy(i).getAttackCollision().initialize(this, enemyCollisionNS::ATTACK_WIDTH, enemyCollisionNS::ATTACK_HEIGHT, 0, &attackCollisionTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy attack collision"));
	}
	stage.setInitializedEnemies(false);
}