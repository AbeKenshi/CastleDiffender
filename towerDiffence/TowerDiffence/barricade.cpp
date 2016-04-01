#include "barricade.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Barricade::Barricade() : Entity()
{
	active = true;
	visible = true;
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
	// Box�̏Փ˔���p
	edge.left = -barricadeNS::WIDTH / 2.0;
	edge.right = barricadeNS::WIDTH / 2.0;
	edge.top = -barricadeNS::HEIGHT / 2.0;
	edge.bottom = barricadeNS::HEIGHT / 2.0;
	collisionType = entityNS::BOX;
	health = 100;
	death = false;
	isDamaged = false;
	drawFlag = true;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Barricade::reset()
{
	active = true;
	visible = true;
	health = 100;
	// �A�j���[�V�����̍ŏ��̃t���[��
	startFrame = barricadeNS::START_FRAME;
	// �A�j���[�V�����̍Ō�̃t���[��
	endFrame = barricadeNS::END_FRAME;
	currentFrame = startFrame;
	death = false;
	isDamaged = false;
	drawFlag = true;
	mode = imageNS::HORIZONTAL;
}

//==========================================================
// �o���P�[�h��`��
//==========================================================
void Barricade::draw()
{
	if (drawFlag)
		Image::draw();	// ���`��
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

	
	if ((currentFrame == barricadeNS::START_FRAME && health < 66) || (currentFrame == barricadeNS::START_FRAME + 1 && health < 33))
	{
		currentFrame++;
		if (currentFrame < startFrame || currentFrame > endFrame)
		{
			if (loop == true)            // if looping animation
				currentFrame = startFrame;
			else                        // not looping animation
			{
				currentFrame = endFrame;
				animComplete = true;    // animation complete
			}
		}
		setRect();                      // set spriteData.rect
	}
	updateWithoutImage(frameTime);
	
}

//==========================================================
// �_���[�W����
//==========================================================
void Barricade::damage()
{
	health -= 5;
	if (health <= 0)
	{
		visible = false;
		active = false;
	}

	isDamaged = true;
}