//==========================================================
/// @file
/// @brief    stage.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "stage.h"

//==========================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
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
// �X�e�[�W����������
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
// �v���C�̐V�������E���h���J�n
//==========================================================
void Stage::roundStart()
{
	map.readMapFile(stageNum + 1);
	enemyWaveNum = 0;
	enemyNum = 0;
	initializeEnemies(stageNum + 1, enemyWaveNum + 1);
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
	// �c�莞�Ԃ�������
	remainingTime = 1500.0f;
	// �Q�[���I�[�o�[�̃t���O��������
	roundOver = false;
	clearedStage = false;
}

//==========================================================
// �l�H�m�\
//==========================================================
void Stage::ai(float frameTime)
{
	// �e�G���X�V
	for (int i = 0; i < enemyNum; i++)
		enemy[i]->ai(frameTime, brave);
}

//==========================================================
// �X�e�[�W��1�X�e�b�v���i�߂�
//==========================================================
void Stage::runStage(float frameTime)
{
	// ���ꂼ��̓G���X�V
	for (int i = 0; i < enemyNum; i++) {
		enemy[i]->update(frameTime);
	}
	// �E�҂��X�V
	brave.update(frameTime);
	// ����X�V
	castle.update(frameTime);
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
		roundOver = true;
	}

	// ���S�`�F�b�N
	if ((castle.isDeath() || brave.getActive() == false) && !roundOver)
	{
		roundOver = true;
	}
}

//==========================================================
// �Փ˂�����
//==========================================================
void Stage::collisions()
{
	VECTOR2 collisionVector;	// �Փ˔��肵���Ƃ��̏Փˑ���ւ̃x�N�g��
	bool braveAttackCollidesWithAnyEnemy = false;
	// �e�G�ɂ��ďՓ˔���
	for (int i = 0; i < enemyNum; i++) {
		// �v���C���[�̍U���R���W�����ƎG���G�̏Փ˂̏ꍇ
		if (brave.getBraveAttackCollision().collidesWith(*enemy[i], collisionVector))
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					brave.damage(ENEMY_ATTACK);
				}
				else
				{
					brave.damage(MIDBOSS_ATTACK);
				}
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					castle.damage(ENEMY_ATTACK);
				}
				else
				{
					castle.damage(MIDBOSS_ATTACK);
				}
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
				if (typeid(*enemy[i]) == typeid(Enemy))
				{
					barricades[enemy[i]->getNearBarricadeIndex()].damage(ENEMY_ATTACK);
				}
				else
				{
					barricades[enemy[i]->getNearBarricadeIndex()].damage(MIDBOSS_ATTACK);
				}
				// �G�̍U���R���W�������Ȃ���
				enemy[i]->getAttackCollision().setVisible(false);
				enemy[i]->getAttackCollision().setActive(false);
				// �U�����ꂽ�o���P�[�h���j�󂳂ꂽ�ꍇ�A
				if (!barricades[enemy[i]->getNearBarricadeIndex()].getActive())
				{
					// �}�b�v�f�[�^���X�V
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

		// ���ƎG���G�̏Փ˂̏ꍇ
		if (brave.getFire().collidesWith(*enemy[i], collisionVector))
		{
			enemy[i]->damage(FIRE);
			brave.getFire().setVisible(false);
			brave.getFire().setActive(false);
		}

		// �U�����Ȃ�΍s���I���͍s��Ȃ�
		if (enemy[i]->getState() == characterNS::ATTACK)
		{
		}
		else if (enemy[i]->collidesWith(brave, collisionVector))// �G���G�ƃv���C���[���Փ˂��Ă���ꍇ�A
		{
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
		}
		else if (enemy[i]->canMakeDecesionMoving())	// �G�������]���\�ȏ�Ԃɂ���Ƃ��A�ӎv������s���i�ޕ��������߂�
		{
			bool changeGoalDirectionFlag = false;	// �i�݂���������ς���K�v�����邩�ǂ���
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
					enemy[i]->setState(characterNS::MOVE);
					// �m��50%��x�����ɐi�ނ��ǂ������Ɍ��肵�A���̂��Ƃ�y�����ɐi�ނ��ǂ���������
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
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		// �v���C���[�̍U���R���W�����Ƃ̏Փ˂̏ꍇ
		if (brave.getBraveAttackCollision().collidesWith(barricades[i], collisionVector))
		{
			// �o���P�[�h�Ƀ_���[�W��^����
			barricades[i].damage(BRAVE_ATTACK);
			// �����ꂩ�̃o���P�[�h�ɍU�������������̂Ń��[�v�𔲂�����ɍU���R���W�������Ȃ���
			braveAttackCollidesWithAnyEnemy = true;
		}
	}

	// �E�҂̍U���������ꂩ�̓G�ɓ��������ꍇ�A�U���R���W�������Ȃ���
	if (braveAttackCollidesWithAnyEnemy)
	{
		brave.getBraveAttackCollision().setVisible(false);
		brave.getBraveAttackCollision().setActive(false);
	}
}

//==========================================================
// �G�̐����`�F�b�N���A�}�b�v��ɓG�����Ȃ���ΐV���ɐ���
//==========================================================
void Stage::checkCurrentEnemyNum()
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
	enemyWaveNum += 1;
	initializeEnemies(stageNum + 1, enemyWaveNum + 1);
}

//==========================================================
// �w�肳�ꂽ�X�e�[�W�̓G�f�[�^��ǂݍ���
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
// �w�肳�ꂽ�X�e�[�W�A�h�̓G�f�[�^��ǂݍ��ݓG������������
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