#include "enemyAttackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
EnemyCollision::EnemyCollision() : Entity()
{
	active = false;									// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
	visible = false;
	// Box�̏Փ˔���p
	edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
	edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void EnemyCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= enemyCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	Image::update(frameTime);
}

//==========================================================
// Attack
// �G���G����U���𔭓�
//==========================================================
void EnemyCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	switch (direction)
	{
	case characterNS::RIGHT:
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Box�̏Փ˔���p
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.x = centerX + width / 2;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::UP:
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Box�̏Փ˔���p
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY - height / 2 - spriteData.height - 10;
		break;
	case characterNS::LEFT:
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Box�̏Փ˔���p
		edge.left = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.right = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		spriteData.x = centerX - width / 2 - spriteData.width;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::DOWN:
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Box�̏Փ˔���p
		edge.left = -enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.right = enemyCollisionNS::ATTACK_HEIGHT / 2.0;
		edge.top = -enemyCollisionNS::ATTACK_WIDTH / 2.0;
		edge.bottom = enemyCollisionNS::ATTACK_WIDTH / 2.0;
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY + height / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
	setRect();
}