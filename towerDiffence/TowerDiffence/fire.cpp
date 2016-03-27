#include "fire.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Fire::Fire() : Entity()
{
	active = false;								// ���̓A�N�e�B�u�łȂ���Ԃ���J�n
	spriteData.width = fireNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = fireNS::HEIGHT;
	spriteData.rect.bottom = fireNS::HEIGHT;	// �摜���̑I�����镔��
	spriteData.rect.right = fireNS::WIDTH;
	cols = fireNS::TEXTURE_COLS;
	frameDelay = fireNS::ANIMATION_DELAY;
	// �t�@�C�A�[�A�j���[�V�����̍ŏ��̃t���[��
	startFrame = fireNS::START_FRAME;
	// �t�@�C�A�[�A�j���[�V�����̍Ō�̃t���[��
	endFrame = fireNS::END_FRAME;
	currentFrame = startFrame;
	radius = fireNS::COLLISION_RADIUS;			// �~�̏Փ˔���p
	visible = false;
	fireTimer = 0.0f;
	collisionType = entityNS::CIRCLE;
	mode = imageNS::VERTICAL;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Fire::reset()
{
	active = false;								// ���̓A�N�e�B�u�łȂ���Ԃ���J�n
	frameDelay = fireNS::ANIMATION_DELAY;
	// �t�@�C�A�[�A�j���[�V�����̍ŏ��̃t���[��
	startFrame = fireNS::START_FRAME;
	// �t�@�C�A�[�A�j���[�V�����̍Ō�̃t���[��
	endFrame = fireNS::END_FRAME;
	currentFrame = startFrame;
	radius = fireNS::COLLISION_RADIUS;			// �~�̏Փ˔���p
	visible = false;
	fireTimer = 0.0f;
	collisionType = entityNS::CIRCLE;
	mode = imageNS::VERTICAL;
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
// Brave����~�T�C���𔭎�
//==========================================================
void Fire::fire(Brave *brave)
{
	if (fireTimer <= 0.0f && brave->getMP() > fireNS::FIRE_MP)	// ���ˉ\�ȏꍇ
	{
		switch (brave->getDirection())
		{
		case braveNS::UP:
			velocity.x = 0.0f;
			velocity.y = -fireNS::SPEED;
			spriteData.angle = PI / 2;
			break;
		case braveNS::RIGHT:
			velocity.x = fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = -PI;
			break;
		case braveNS::DOWN:
			velocity.x = 0.0f;
			velocity.y = fireNS::SPEED;
			spriteData.angle = -PI / 2;
			break;
		case braveNS::LEFT:
			velocity.x = -fireNS::SPEED;
			velocity.y = 0.0f;
			spriteData.angle = 0.0f;
			break;
		}
		spriteData.x = brave->getCenterX() - spriteData.width / 2;
		spriteData.y = brave->getCenterY() - spriteData.height / 2;
		visible = true;									// ����\��
		active = true;									// �Փˉ\�ɂ���
		fireTimer = fireNS::FIRE_DELAY;					// ���˂̊Ԋu
		brave->setMP(brave->getMP() - fireNS::FIRE_MP);	// MP������
	}
}