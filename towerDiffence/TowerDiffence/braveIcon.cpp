#include "braveIcon.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
BraveIcon::BraveIcon() : Image()
{
	spriteData.width = braveIconNS::WIDTH;			// �E�҂̃A�C�R���̃T�C�Y
	spriteData.height = braveIconNS::HEIGHT;
	spriteData.x = braveIconNS::X;					// ��ʏ�̈ʒu
	spriteData.y = braveIconNS::Y;
	spriteData.rect.bottom = braveIconNS::HEIGHT;		// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveIconNS::WIDTH;
	startFrame = braveIconNS::START_FRAME;
	endFrame = braveIconNS::END_FRAME;
	currentFrame = startFrame;
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================	
void BraveIcon::update(float frameTime)
{
	if (currentFrame == 0 && brave->getHealth() < 75)
		Image::update(frameTime);
	if (currentFrame == 1 && brave->getHealth() < 50)
		Image::update(frameTime);
	if (currentFrame == 2 && brave->getHealth() < 25)
		Image::update(frameTime);
}

