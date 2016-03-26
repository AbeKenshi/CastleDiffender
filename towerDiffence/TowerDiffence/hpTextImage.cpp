#include "hpTextImage.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
HpTextImage::HpTextImage() : Image()
{
	spriteData.width = hpTextImageNS::WIDTH;	// �e�L�X�g�摜�̃T�C�Y
	spriteData.height = hpTextImageNS::HEIGHT;
	spriteData.x = hpTextImageNS::X;			// ��ʏ�̏����ʒu
	spriteData.y = hpTextImageNS::Y;
	spriteData.rect.bottom = hpTextImageNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = hpTextImageNS::WIDTH;
	startFrame = hpTextImageNS::START_FRAME;
	endFrame = startFrame;
	currentFrame = startFrame;
}