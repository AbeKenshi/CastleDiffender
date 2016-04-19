//==========================================================
/// @file
/// @brief    braveAttackCollision.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "braveAttackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
BraveAttackCollision::BraveAttackCollision() : Entity()
{
	mActive = false;												// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	mVisible = false;
	mSpriteData.width = braveAttackCollisionNS::WIDTH;			// �P�̉摜�̃T�C�Y
	mSpriteData.height = braveAttackCollisionNS::HEIGHT;
	mSpriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	mSpriteData.rect.right = braveAttackCollisionNS::WIDTH;
	// Box�̏Փ˔���p
	mEdge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
	mEdge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
	mEdge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
	mEdge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
	mCollisionType = entityNS::BOX;
	mCollisionTimer = 0.0f;										// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void BraveAttackCollision::update(float frameTime)
{
	// �U���̏Ռ��h���X�V
	mAttackEffect.update(frameTime);
	// ��A�N�e�B�u�Ȃ�A���̃G���e�B�e�B�̍X�V�͂��Ȃ�
	if (mVisible == false)
		return;
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z
	mCollisionTimer += frameTime;
	// �U���̓����蔻�肪���ȏ�o�Ă���Ȃ�A���̃G���e�B�e�B���A�N�e�B�u�ɂ���
	if (mCollisionTimer >= braveAttackCollisionNS::COLLISION_TIME)
	{
		mCollisionTimer = 0.0f;
		mVisible = false;
		mActive = false;
	}
	// �G���e�B�e�B���X�V
	Entity::update(frameTime);
}

//==========================================================
// Attack
// �E�҂���U���𔭓�
// �w�肵���ʒu�ɂ��̃G���e�B�e�B���A�N�e�B�u�ɂ��ďo��������
//==========================================================
void BraveAttackCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	// �U���̏Ռ��h�̃A�j���[�V������\��
	mAttackEffect.attack(centerX, centerY, width, height, direction);
	// �E�҂̌����ɂ���ďo���ʒu�𕪊�
	// �E�҂̉摜�ɕ΂肪���邽�߁A�኱�ʒu���C�����Ă���
	switch (direction)
	{
		case characterNS::RIGHT:	// �E
			mSpriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			mSpriteData.height = braveAttackCollisionNS::HEIGHT;
			mSpriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			mSpriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			mEdge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			mSpriteData.x = centerX + width / 2;
			mSpriteData.y = centerY - mSpriteData.height / 2;
			break;
		case characterNS::UP:		// ��
			mSpriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			mSpriteData.height = braveAttackCollisionNS::WIDTH;
			mSpriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			mSpriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			mEdge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			mSpriteData.x = centerX - mSpriteData.width / 2;
			mSpriteData.y = centerY - height / 2 - mSpriteData.height;
			break;
		case characterNS::LEFT:		// ��
			mSpriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			mSpriteData.height = braveAttackCollisionNS::HEIGHT;
			mSpriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			mSpriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			mEdge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			mSpriteData.x = centerX - mSpriteData.width / 2 - width;
			mSpriteData.y = centerY - mSpriteData.height / 2;
			break;
		case characterNS::DOWN:		// ��
			mSpriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			mSpriteData.height = braveAttackCollisionNS::WIDTH;
			mSpriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			mSpriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			mEdge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			mEdge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			mEdge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			mSpriteData.x = centerX - mSpriteData.width / 2;
			mSpriteData.y = centerY + 10;
			break;
	}
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z�b�g
	mCollisionTimer = 0.0f;
	//visible = true;						// �U����\��
	mActive = true;							// �Փˉ\�ɂ���
}