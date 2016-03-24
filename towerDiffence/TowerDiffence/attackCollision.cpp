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
	collisionTimer += frameTime;
	if (collisionTimer >= attackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
	}
	if (visible == false)
		return;
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
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::UP:
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = PI / 2;
			break;
		case braveNS::LEFT:
			spriteData.x = brave->getCenterX() - spriteData.width * 3 / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = 0.0f;
			break;
		case braveNS::DOWN:
			spriteData.x = brave->getCenterX() + spriteData.width / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			spriteData.angle = PI / 2;
			break;
	}
	collisionTimer = 0.0f;
	visible = true;							// ����\��
	active = true;							// �Փˉ\�ɂ���
}