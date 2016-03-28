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
	visible = false;
	// Box�̏Փ˔���p
	edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
	edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
	edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
	edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
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
	case characterNS::RIGHT:
		spriteData.x = enemy->getCenterX() + spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
		edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth() / 2;
		edge.left = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.right = enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.top = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.bottom = enemyAttackCollisionNS::WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	case characterNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 + 10;
		edge.left = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.right = enemyAttackCollisionNS::WIDTH / 2.0;
		edge.top = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.bottom = enemyAttackCollisionNS::HEIGHT / 2.0;
		spriteData.angle = 0.0f;
		break;
	case characterNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 2;
		edge.left = -enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.right = enemyAttackCollisionNS::HEIGHT / 2.0;
		edge.top = -enemyAttackCollisionNS::WIDTH / 2.0;
		edge.bottom = enemyAttackCollisionNS::WIDTH / 2.0;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}