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
	active = false;												// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	visible = false;
	spriteData.width = braveAttackCollisionNS::WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = braveAttackCollisionNS::HEIGHT;
	spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = braveAttackCollisionNS::WIDTH;
	// Box�̏Փ˔���p
	edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
	edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
	edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
	edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;										// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void BraveAttackCollision::update(float frameTime)
{
	// �U���̏Ռ��h���X�V
	attackEffect.update(frameTime);
	// ��A�N�e�B�u�Ȃ�A���̃G���e�B�e�B�̍X�V�͂��Ȃ�
	if (visible == false)
		return;
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z
	collisionTimer += frameTime;
	// �U���̓����蔻�肪���ȏ�o�Ă���Ȃ�A���̃G���e�B�e�B���A�N�e�B�u�ɂ���
	if (collisionTimer >= braveAttackCollisionNS::COLLISION_TIME)
	{
		collisionTimer = 0.0f;
		visible = false;
		active = false;
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
	attackEffect.attack(centerX, centerY, width, height, direction);
	// �E�҂̌����ɂ���ďo���ʒu�𕪊�
	// �E�҂̉摜�ɕ΂肪���邽�߁A�኱�ʒu���C�����Ă���
	switch (direction)
	{
		case characterNS::RIGHT:	// �E
			spriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			spriteData.x = centerX + width / 2;
			spriteData.y = centerY - spriteData.height / 2;
			break;
		case characterNS::UP:		// ��
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			edge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			spriteData.x = centerX - spriteData.width / 2;
			spriteData.y = centerY - height / 2 - spriteData.height;
			break;
		case characterNS::LEFT:		// ��
			spriteData.width = braveAttackCollisionNS::WIDTH;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.bottom = braveAttackCollisionNS::HEIGHT;
			spriteData.rect.right = braveAttackCollisionNS::WIDTH;
			// Box�̏Փ˔���p
			edge.left = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			spriteData.x = centerX - spriteData.width / 2 - width;
			spriteData.y = centerY - spriteData.height / 2;
			break;
		case characterNS::DOWN:		// ��
			spriteData.width = braveAttackCollisionNS::HEIGHT;	// �P�̉摜�̃T�C�Y
			spriteData.height = braveAttackCollisionNS::WIDTH;
			spriteData.rect.bottom = braveAttackCollisionNS::WIDTH;
			spriteData.rect.right = braveAttackCollisionNS::HEIGHT;
			// Box�̏Փ˔���p
			edge.left = (LONG)(-braveAttackCollisionNS::HEIGHT / 2.0);
			edge.right = (LONG)(braveAttackCollisionNS::HEIGHT / 2.0);
			edge.top = (LONG)(-braveAttackCollisionNS::WIDTH / 2.0);
			edge.bottom = (LONG)(braveAttackCollisionNS::WIDTH / 2.0);
			spriteData.x = centerX - spriteData.width / 2;
			spriteData.y = centerY + 10;
			break;
	}
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z�b�g
	collisionTimer = 0.0f;
	visible = true;						// �U����\��
	active = true;							// �Փˉ\�ɂ���
}