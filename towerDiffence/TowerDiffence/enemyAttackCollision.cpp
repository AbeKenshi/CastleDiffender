//==========================================================
/// @file
/// @brief    enemyAttackCollision.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "enemyAttackCollision.h"

//==========================================================
// �f�t�H���g�R���X�g���N�^
//==========================================================
EnemyCollision::EnemyCollision() : Entity()
{
	active = false;												// �U���̓A�N�e�B�u�łȂ���Ԃ���J�n
	visible = false;
	spriteData.width = enemyCollisionNS::ATTACK_WIDTH;			// �P�̉摜�̃T�C�Y
	spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
	spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;	// ��ʂ̈ꕔ��I��
	spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
	// Box�̏Փ˔���p
	edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
	edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
	edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
	edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
	collisionType = entityNS::BOX;
	collisionTimer = 0.0f;										// �U���̓����蔻�肪�o�Ă��鎞�Ԃ��v������^�C�}�[
}

//==========================================================
// Update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void EnemyCollision::update(float frameTime)
{
	// ��A�N�e�B�u�Ȃ�A���̃G���e�B�e�B�̍X�V�͂��Ȃ�
	if (visible == false)
		return;
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z
	collisionTimer += frameTime;
	// �U���̓����蔻�肪���ȏ�o�Ă���Ȃ�A���̃G���e�B�e�B���A�N�e�B�u�ɂ���
	if (collisionTimer >= enemyCollisionNS::COLLISION_TIME)
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
// �G����U���𔭓�
// �w�肵���ʒu�ɂ��̃G���e�B�e�B���A�N�e�B�u�ɂ��ďo��������
//==========================================================
void EnemyCollision::attack(float centerX, float centerY, float width, float height, characterNS::DIRECTION direction)
{
	// �G�̌����ɂ���ďo���ʒu�𕪊�
	// �G�̉摜�ɕ΂肪���邽�߁A�኱�ʒu���C�����Ă���
	switch (direction)
	{
	case characterNS::RIGHT:	// �E
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Box�̏Փ˔���p
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		spriteData.x = centerX + width / 2;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::UP:		// ��
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Box�̏Փ˔���p
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY - height / 2 - spriteData.height - 10;
		break;
	case characterNS::LEFT:		// ��
		spriteData.width = enemyCollisionNS::ATTACK_WIDTH;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_HEIGHT;
		spriteData.rect.right = enemyCollisionNS::ATTACK_WIDTH;
		// Box�̏Փ˔���p
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		spriteData.x = centerX - width / 2 - spriteData.width;
		spriteData.y = centerY - height / 2;
		break;
	case characterNS::DOWN:		// ��
		spriteData.width = enemyCollisionNS::ATTACK_HEIGHT;	// �P�̉摜�̃T�C�Y
		spriteData.height = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.bottom = enemyCollisionNS::ATTACK_WIDTH;
		spriteData.rect.right = enemyCollisionNS::ATTACK_HEIGHT;
		// Box�̏Փ˔���p
		edge.left = (LONG)(-enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.right = (LONG)(enemyCollisionNS::ATTACK_HEIGHT / 2.0);
		edge.top = (LONG)(-enemyCollisionNS::ATTACK_WIDTH / 2.0);
		edge.bottom = (LONG)(enemyCollisionNS::ATTACK_WIDTH / 2.0);
		spriteData.x = centerX - width / 2;
		spriteData.y = centerY + height / 2;
		break;
	}
	// �U���̓����蔻�肪�o�Ă��鎞�Ԃ����Z�b�g
	collisionTimer = 0.0f;
	//visible = true;							// �U����\��
	active = true;							// �Փˉ\�ɂ���
}