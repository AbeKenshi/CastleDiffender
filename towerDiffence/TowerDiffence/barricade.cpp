#include "barricade.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Barricade::Barricade() : Entity()
{
	active = true;
	spriteData.width = barricadeNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = barricadeNS::HEIGHT;
	spriteData.rect.bottom = barricadeNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = barricadeNS::WIDTH;
	cols = barricadeNS::TEXTURE_COLS;
	// �A�j���[�V�����̍ŏ��̃t���[��
	startFrame = barricadeNS::START_FRAME;
	// �A�j���[�V�����̍Ō�̃t���[��
	endFrame = barricadeNS::END_FRAME;
	currentFrame = startFrame;
	radius = barricadeNS::COLLISION_RADIUS;			// �~�̏Փ˔���p
	visible = true;
	collisionType = entityNS::CIRCLE;
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Barricade::update(float frameTime)
{
	if (visible == false)
		return;

//	updateWithoutImage(frameTime);
	Image::update(frameTime);
}