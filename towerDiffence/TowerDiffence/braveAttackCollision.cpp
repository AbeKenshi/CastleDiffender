#include "braveAttackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
BraveAttackCollision::BraveAttackCollision() : Entity()
{
	active = false;									// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	spriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
	spriteData.height = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.right = braveAttackCollisionNS::WIDTH;
	visible = false;
	// Box�̏Փ˔���p
	edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
	edge.right = braveAttackCollisionNS::WIDTH / 2.0;
	edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
	edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void BraveAttackCollision::update(float frameTime)
{
	if (visible == false)
		return;
	collisionTimer += frameTime;
	if (collisionTimer >= braveAttackCollisionNS::COLLISION_TIME)
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
void BraveAttackCollision::attack(Brave * brave)
{
	switch (brave->getDirection())
	{
		case characterNS::RIGHT:
			spriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.x = brave->getCenterX() + brave->getWidth() / 2;
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			break;
		case characterNS::UP:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() - brave->getHeight() / 2 - spriteData.height;
			break;
		case characterNS::LEFT:
			spriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			edge.left = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.right = braveAttackCollisionNS::WIDTH / 2.0;
			edge.top = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.bottom = braveAttackCollisionNS::HEIGHT / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2 - brave->getWidth();
			spriteData.y = brave->getCenterY() - spriteData.height / 2;
			break;
		case characterNS::DOWN:
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			edge.left = -braveAttackCollisionNS::HEIGHT / 2.0;
			edge.right = braveAttackCollisionNS::HEIGHT / 2.0;
			edge.top = -braveAttackCollisionNS::WIDTH / 2.0;
			edge.bottom = braveAttackCollisionNS::WIDTH / 2.0;
			spriteData.x = brave->getCenterX() - spriteData.width / 2;
			spriteData.y = brave->getCenterY() + 10;
			break;
	}
	collisionTimer = 0.0f;
	//visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}