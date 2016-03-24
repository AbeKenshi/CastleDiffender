#include "attackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
AttackCollision::AttackCollision() : Entity()
{
	active = false;									// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	spriteData.width = attackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = attackCollisionNS::HEIGHT;
	spriteData.rect.bottom = attackCollisionNS::HEIGHT;
	spriteData.rect.right = attackCollisionNS::WIDTH;
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
void AttackCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= attackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	Image::update(frameTime);
}

//==========================================================
// Attack
// �E�҂���U���𔭓�
//==========================================================
void AttackCollision::attack(Brave * brave)
{
	switch (brave->getDirection())
	{
		case braveNS::RIGHT:
			spriteData.x = brave->getCenterX();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::UP:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2 - brave->getWidth();
			spriteData.angle = PI / 2;
			break;
		case braveNS::LEFT:
			spriteData.x = brave->getCenterX() - spriteData.width / 2 - brave->getWidth();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::DOWN:
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() + spriteData.height / 16;
			spriteData.angle = PI / 2;
			break;
	}
	collisionTimer = 0.0f;
	visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}

//==========================================================
// Attack
// �G���G����U���𔭓�
//==========================================================
void AttackCollision::attack(Enemy *enemy)
{
	switch (enemy->getDirection())
	{
	case braveNS::RIGHT:
		spriteData.x = enemy->getCenterX();
		spriteData.y = enemy->getCenterY() - spriteData.height / 2;
		spriteData.angle = 0.0f;
		break;
	case braveNS::UP:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() - spriteData.height / 2 - enemy->getWidth();
		spriteData.angle = PI / 2;
		break;
	case braveNS::LEFT:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2 - enemy->getWidth();
		spriteData.y = enemy->getCenterY() - spriteData.height / 2;
		spriteData.angle = 0.0f;
		break;
	case braveNS::DOWN:
		spriteData.x = enemy->getCenterX() - spriteData.width / 2;
		spriteData.y = enemy->getCenterY() + spriteData.height / 16;
		spriteData.angle = PI / 2;
		break;
	}
	collisionTimer = 0.0f;
	visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}