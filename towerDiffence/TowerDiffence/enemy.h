#ifndef _ENEMY_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH = 24;				// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;				// �摜�̍���
	const int X = 200;					// ��ʏ�̈ʒu
	const int Y = 200;
	const int MOVE_SPEED = 100;			// �ړ����x�i�s�N�Z���j
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };	// �����Ă������
	const int TEXTURE_COLS = 12;		// �e�N�X�`����12��
	const int MOVE_UP_START_FRAME = 3;	// ������ړ��̃A�j���[�V�����̓t���[��3����J�n
	const int MOVE_UP_END_FRAME = 5;	// ������ړ��̃A�j���[�V�����t���[����3�A4�A5
	const int MOVE_RIGHT_START_FRAME = 15;	// �E�����ړ��̃A�j���[�V�����̓t���[��15����J�n
	const int MOVE_RIGHT_END_FRAME = 17;	// �E�����ړ��̃A�j���[�V�����t���[����15�A16�A17
	const int MOVE_DOWN_START_FRAME = 27;	// �������ړ��̃A�j���[�V�����̓t���[��27����J�n
	const int MOVE_DOWN_END_FRAME = 29;	// �������ړ��̃A�j���[�V�����t���[����27�A28�A29
	const int MOVE_LEFT_START_FRAME = 39;	// �������ړ��̃A�j���[�V�����̓t���[��39����J�n
	const int MOVE_LEFT_END_FRAME = 41;	// �������ړ��̃A�j���[�V�����t���[����39�A40�A41
	const float MOVE_ANIMATION_DELAY = 0.2;	// �ړ��A�j���[�V�����̃t���[���Ԃ̎���
	const float DAMAGE_TIME = 1.0f;
	enum STATE {MOVE, ATTACK, GAURD };
}

// Enemy�N���X
class Enemy : public Entity
{
private:
	enemyNS::DIRECTION direction;		// ����
	enemyNS::STATE state;				// ���
	int oldStartFrame;
	int oldEndFrame;
	float timeCounter;					// �A�j���[�V�����p�̃^�C�}�[
	float totalTimeCounter;
	bool isDamaged;						// �_���[�W���󂯂Ă����Ԃ��ǂ���
	bool drawFlag;
public:
	// �R���X�g���N�^
	Enemy();

	// �p�����ꂽ�����o�[�֐�
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);

	// �V�����ǉ����郁���o�[�֐�
	// �ړ����̃A�b�v�f�[�g�֐�
	void updateMoving(float frameTime);
	// �U�����̃A�b�v�f�[�g�֐�
	void updateAttacking(float frameTime);
	// �����Ă��������Ԃ�
	enemyNS::DIRECTION getDirection(){ return direction; }

};
#endif
