#include "brave.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
Brave::Brave() : Entity()
{
	spriteData.width = braveNS::WIDTH;			// �E�҂̃T�C�Y
	spriteData.height = braveNS::HEIGHT;
	spriteData.x = braveNS::X;					// ��ʏ�̈ʒu
	spriteData.y = braveNS::Y;
	spriteData.rect.bottom = braveNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveNS::WIDTH;
	frameDelay = braveNS::MOVE_ANIMATION_DELAY;
	startFrame = braveNS::MOVE_UP_START_FRAME;
	endFrame = braveNS::MOVE_UP_END_FRAME;
	currentFrame = startFrame;
}

//==========================================================
// �E�҂�������
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//==========================================================
bool Brave::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//==========================================================
// �E�҂�`��
//==========================================================
void Brave::draw()
{
	Image::draw();		// �E�҂�`��
}

//=============================================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Brave::update(float frameTime)
{
	// ���L�[��������ĂāA����xcount��0�ȏ�Ȃ�0�ɂ��Ă���frameTime�������B
	// ����ȊO��frameTime�������B
	if (input->isKeyDown(BRAVE_LEFT_KEY))
	{
		if (direction != braveNS::DIRECTION::LEFT)
		{
			direction = braveNS::DIRECTION::LEFT;
			startFrame = braveNS::MOVE_LEFT_START_FRAME;
			endFrame = braveNS::MOVE_LEFT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		spriteData.x -= braveNS::MOVE_SPEED * frameTime;
		Entity::update(frameTime);
	}
	// �E�L�[��������ĂāA����xcount��0�ȉ��Ȃ�0�ɂ��Ă���frameTime�𑫂��B
	// ����ȊO��frameTime�𑫂��B
	if (input->isKeyDown(BRAVE_RIGHT_KEY))
	{
		if (direction != braveNS::DIRECTION::RIGHT)
		{
			direction = braveNS::DIRECTION::RIGHT;
			startFrame = braveNS::MOVE_RIGHT_START_FRAME;
			endFrame = braveNS::MOVE_RIGHT_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		spriteData.x += braveNS::MOVE_SPEED * frameTime;
		Entity::updateOnlyImage(frameTime);
	}
	// ��L�[��������ĂāA����ycount��0�ȏ�Ȃ�0�ɂ��Ă���frameTime�������B
	// ����ȊO��frameTime�������B
	if (input->isKeyDown(BRAVE_UP_KEY))
	{
		if (direction != braveNS::DIRECTION::UP)
		{
			direction = braveNS::DIRECTION::UP;
			startFrame = braveNS::MOVE_UP_START_FRAME;
			endFrame = braveNS::MOVE_UP_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		spriteData.y -= braveNS::MOVE_SPEED * frameTime;
		Entity::updateOnlyImage(frameTime);
	}
	// ���L�[��������ĂāA����ycount��0�ȉ��Ȃ�0�ɂ��Ă���frameTime�𑫂��B
	// ����ȊO��frameTime�𑫂��B
	if (input->isKeyDown(BRAVE_DOWN_KEY))
	{
		if (direction != braveNS::DIRECTION::DOWN)
		{
			direction = braveNS::DIRECTION::DOWN;
			startFrame = braveNS::MOVE_DOWN_START_FRAME;
			endFrame = braveNS::MOVE_DOWN_END_FRAME;
			currentFrame = startFrame;
			animTimer = 0.0f;
			setRect();
		}
		spriteData.y += braveNS::MOVE_SPEED * frameTime;
		Entity::updateOnlyImage(frameTime);
	}
	Entity::updateWithoutImage(frameTime);
}

//==========================================================
// �_���[�W
//==========================================================
void Brave::damage(WEAPON weapon)
{

}