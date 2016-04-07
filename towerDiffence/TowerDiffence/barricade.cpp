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
}

//==========================================================
// �o���P�[�h��`��
//==========================================================
void Barricade::draw()
{
	Image::draw();	// ���`��
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Barricade::update(float frameTime)
{
	if (active == false)
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
	hitEffect.update(frameTime);
	updateWithoutImage(frameTime);
	
}

//==========================================================
// �_���[�W����
//==========================================================
void Barricade::damage()
{
	if (!active)
		return;
	hitEffect.hit(getCenterX(), getCenterY());
	health -= 10 * damagePer;

	if (health <= 0)
	{
		visible = false;
		active = false;
		hitEffect.setVisible(false);
	}

	isDamaged = true;
}