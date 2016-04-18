//==========================================================
/// @file
/// @brief    fire.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "fire.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Fire::Fire() : Entity()
{
	active = false;								// ���̓A�N�e�B�u�łȂ���Ԃ���J�n
	visible = false;
	spriteData.width = fireNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = fireNS::HEIGHT;
	spriteData.rect.bottom = fireNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = fireNS::WIDTH;
	cols = fireNS::TEXTURE_COLS;				// �e�N�X�`���̗�
	frameDelay = fireNS::ANIMATION_DELAY;		// �A�j���[�V�����̊e�t���[���̊Ԋu
	startFrame = fireNS::START_FRAME;			// �t�@�C�A�[�A�j���[�V�����̍ŏ��̃t���[��
	endFrame = fireNS::END_FRAME;				// �t�@�C�A�[�A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;					// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	collisionType = entityNS::CIRCLE;			// �~�̏Փ˔���
	radius = fireNS::COLLISION_RADIUS;			// �~�̏Փ˔���p
	fireTimer = 0.0f;							// �������ˉ\�ɂȂ�܂ł̎c�莞��
	mode = imageNS::VERTICAL;					// �A�j���[�V�����̃��[�h
}

//==========================================================
// �p�����[�^������
//==========================================================
void Fire::reset()
{
	active = false;								// ���̓A�N�e�B�u�łȂ���Ԃ���J�n	
	visible = false;
	frameDelay = fireNS::ANIMATION_DELAY;		// �A�j���[�V�����̊e�t���[���̊Ԋu
	startFrame = fireNS::START_FRAME;			// �t�@�C�A�[�A�j���[�V�����̍ŏ��̃t���[��
	endFrame = fireNS::END_FRAME;				// �t�@�C�A�[�A�j���[�V�����̍Ō�̃t���[��
	currentFrame = startFrame;					// ���݂̃t���[���̓A�j���[�V�����̍ŏ��̃t���[���ɐݒ�
	collisionType = entityNS::CIRCLE;			// �~�̏Փ˔���
	radius = fireNS::COLLISION_RADIUS;			// �~�̏Փ˔���p
	fireTimer = 0.0f;							// �������ˉ\�ɂȂ�܂ł̎c�莞��
	mode = imageNS::VERTICAL;					// �A�j���[�V�����̃��[�h
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Fire::update(float frameTime)
{
	fireTimer -= frameTime;						// ���˂��\�ɂȂ�܂ł̎c�莞��
	
	if (visible == false)
		return;

	if (fireTimer < 0)							// ���ˉ\�ȏꍇ
	{
		visible = false;						// �Â����𖳌���
		active = false;
	}

	Image::update(frameTime);

	spriteData.x += frameTime * velocity.x;		// X�����Ɉړ�
	spriteData.y += frameTime * velocity.y;		// Y�����Ɉړ�
	// ��ʂ̒[�܂ŗ��������
	if (spriteData.x > GAME_WIDTH || spriteData.x < 0 || spriteData.y < 0 || spriteData.y > GAME_HEIGHT)
	{
		visible = false;
		active = false;
	}
}

//==========================================================
// Fire
// Brave���牊�𔭎�
//==========================================================
void Fire::fire(float centerX, float centerY, float width, float height, float scale, int& mp, characterNS::DIRECTION direction)
{
	if (fireTimer <= 0.0f && mp > fireNS::FIRE_MP)	// ���ˉ\�ȏꍇ
	{
		audio->playCue("fire");
		switch (direction)
		{
		case characterNS::UP:
			velocity.x = 0.0f;
			velocity.y = -fireNS::SPEED;
			spriteData.angle = (float)PI / 2.0f;
			break;
		case characterNS::RIGHT:
			velocity.x = fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = (float)-PI;
			break;
		case characterNS::DOWN:
			velocity.x = 0.0f;
			velocity.y = fireNS::SPEED;
			spriteData.angle = (float)-PI / 2;
			break;
		case characterNS::LEFT:
			velocity.x = -fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = 0.0f;
			break;
		}
		spriteData.x = (float)(centerX - spriteData.width / 2 - width * (scale - 1) / 2.0);
		spriteData.y = (float)(centerY - spriteData.height / 2 - height * (scale - 1) / 2.0f - 10.0f);
		visible = true;									// ����\��
		active = true;									// �Փˉ\�ɂ���
		fireTimer = fireNS::FIRE_DELAY;					// ���˂̊Ԋu
		mp -= fireNS::FIRE_MP;							// MP������
	}
}