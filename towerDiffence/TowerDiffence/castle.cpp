#include "castle.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Castle::Castle() : Entity()
{
	active = true;
	visible = true;
	spriteData.width = castleNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = castleNS::HEIGHT;
	spriteData.rect.bottom = castleNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = castleNS::WIDTH;
	spriteData.x = castleNS::X;
	spriteData.y = castleNS::Y;
	cols = 0;
	startFrame = castleNS::START_FRAME;
	currentFrame = startFrame;
	radius = castleNS::COLLISION_RADIUS;		// �~�̏Փ˔���p
	collisionType = entityNS::CIRCLE;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Castle::update(float frameTime)
{
	if (visible == false)
		return;

	Image::update(frameTime);
}