#include "enemyAttackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
EnemyAttackCollision::EnemyAttackCollision() : Entity()
{
	active = false;									// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	spriteData.width = enemyAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = enemyAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = enemyAttackCollisionNS::HEIGHT;
	spriteData.rect.right = enemyAttackCollisionNS::WIDTH;
	radius = 4;										// �~�̏Փ˔���p
	visible = false;
	collisionType = entityNS::CIRCLE;
	collisionTimer = 0.0f;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void EnemyAttackCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= enemyAttackCollisionNS::COLLISION_TIME)
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
void EnemyAttackCollision::attack(Enemy *enemy)
{
	switch (enemy->getDirection())
	{
	case enemyNS::RIGHT:
		spriteData.x = enemy->getCenterX() + spriteData.width / 2;
		spriteData.y = enemy->getCenterY();
		spriteData.angle = 0.0f;
		break;
	case enemyNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth() / 2;
		spriteData.angle = PI / 2;
		break;
	case enemyNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY();
		spriteData.angle = 0.0f;
		break;
	case enemyNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 2;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}