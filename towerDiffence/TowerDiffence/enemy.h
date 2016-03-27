#ifndef _ENEMY_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "brave.h"
#include "constants.h"
#include "map.h"
#include "barricade.h"
#include "castle.h"

namespace enemyNS
{
	const int WIDTH = 24;							// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;							// �摜�̍���
	const int X = 200;								// ��ʏ�̈ʒu
	const int Y = 000;
	const int MOVE_SPEED = 100;						// �ړ����x�i�s�N�Z���j
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };	// �����Ă������
	const int TEXTURE_COLS = 12;					// �e�N�X�`����12��
	const int MOVE_UP_START_FRAME = 54;				// ������ړ��̃A�j���[�V�����̓t���[��54����J�n
	const int MOVE_UP_END_FRAME = 56;				// ������ړ��̃A�j���[�V�����t���[����54�A55�A56
	const int MOVE_RIGHT_START_FRAME = 66;			// �E�����ړ��̃A�j���[�V�����̓t���[��66����J�n
	const int MOVE_RIGHT_END_FRAME = 68;			// �E�����ړ��̃A�j���[�V�����t���[����66�A67�A68
	const int MOVE_DOWN_START_FRAME = 78;			// �������ړ��̃A�j���[�V�����̓t���[��78����J�n
	const int MOVE_DOWN_END_FRAME = 80;				// �������ړ��̃A�j���[�V�����t���[����78�A79�A80
	const int MOVE_LEFT_START_FRAME = 90;			// �������ړ��̃A�j���[�V�����̓t���[��90����J�n
	const int MOVE_LEFT_END_FRAME = 92;				// �������ړ��̃A�j���[�V�����t���[����90�A91�A92
	const float MOVE_ANIMATION_DELAY = 0.1;			// �ړ��A�j���[�V�����̃t���[���Ԃ̎���
	const int ATTACK_UP_START_FRAME = 151;			// ������U���̃A�j���[�V�����̓t���[��151����J�n
	const int ATTACK_UP_END_FRAME = 151 + 36;		// ������U���ɃA�j���[�V�����t���[����151�A163�A175�A184
	const int ATTACK_RIGHT_START_FRAME = 148;		// �E�����U���̃A�j���[�V�����̓t���[��148����J�n
	const int ATTACK_RIGHT_END_FRAME = 148 + 36;	// �E�����U���̃A�j���[�V�����t���[����148�A161�A173�A182
	const int ATTACK_DOWN_START_FRAME = 103;		// �������U���̃A�j���[�V�����̓t���[��103����J�n
	const int ATTACK_DOWN_END_FRAME = 103 + 36;		// �������U���̃A�j���[�V�����t���[����103�A115�A127�A139
	const int ATTACK_LEFT_START_FRAME = 100;		// �������U���̃A�j���[�V�����̓t���[��100����J�n
	const int ATTACK_LEFT_END_FRAME = 100 + 36;		// �������U���̃A�j���[�V�����t���[����100�A112�A124�A136
	const float ATTACK_TIME = 0.6f;					// �v���C���[�ɗאڂ��Ă���U���Ɉڂ�܂ł̗��ߎ���
	const float CONTINUE_ATTACK_TIME = 0.8f;		// �A���ōU������ꍇ�̗��ߎ���
	const float DAMAGE_TIME = 1.0f;					// �_���[�W���󂯂Ă���ꍇ�ADAMAGE_TIME���Ƃɉ摜���_��
	const int ATTACK_DAMAGE = 5.0f;
	enum STATE {MOVE_CASTLE, MOVE_BARRICADE , ATTACK_BRAVE, ATTACK_CASTLE, ATTACK_BARRICADE , PRE_ATTACK, GAURD };	// �G���G�̏��
}

// Enemy�N���X
class Enemy : public Entity
{
private:
	enemyNS::DIRECTION direction;		// ����
	enemyNS::DIRECTION oldDirection;	// �U�����O�Ɍ����Ă����������i�[
	enemyNS::DIRECTION goalDirection;	// ���ɐi�ނׂ�����
	enemyNS::STATE state;				// ���
	enemyNS::STATE attackState;			// �U���p�̏��
	VECTOR2 goalPos;					// �ڕW�n�_�̍��W
	int oldStartFrame;					// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����t���[���ۑ��p
	int oldEndFrame;					// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����t���[���ۑ��p
	float distanceCounter;				// �����v���p�J�E���^�[�A���������Ɉ�苗���i�܂Ȃ��ƕ����]���ł��Ȃ��悤�ɂ���
	float damageTimer;					// �_���[�W���̃A�j���[�V�����p�̃^�C�}�[
	float totalDamageTime;				// �_���[�W���̃A�j���[�V�����p�̃^�C�}�[
	float attackTimer;					// �U���A�j���[�V�����p�̃^�C�}�[
	bool isDamaged;						// �_���[�W���󂯂Ă����Ԃ��ǂ���
	bool drawFlag;						// �`��t���O�A�_���[�W���󂯂Ă����Ԏ��Ɏg�p
	bool nearPlayer;					// �v���C���[�Ɨאڂ��Ă��邩�ǂ���
	bool nearBarricade;                 // �o���P�[�h�Ɨאڂ��Ă��邩�ǂ���
	bool isAttacked;					// �U���������ォ�ǂ���
	bool attackCollisionFlag;			// �U���p�̏Փ˔�����o��������t���O
	bool inCertainRange;                // �v���C���[�����͈͓��ɂ��邩
public:
	// �R���X�g���N�^
	Enemy();

	// �p�����ꂽ�����o�[�֐�
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	virtual void ai(float frameTime, Entity &ent, Barricade *barricades);
	void damage(WEAPON);	


	// �V�����ǉ����郁���o�[�֐�
	void update(float frameTime, Map *map);
	// �ړ����̃A�b�v�f�[�g�֐�
	void updateMoving(float frameTime);
	// �U�����̃A�b�v�f�[�g�֐�
	void updateAttacking(float frameTime);
	// �����Ă��������Ԃ�
	enemyNS::DIRECTION getDirection(){ return direction; }
	// �v���C���[�Ɨאڂ��Ă��邩�ǂ������Z�b�g
	void setNearPlayer(bool np)
	{
		nearPlayer = np;
	}
	// �o���P�[�h�Ɨאڂ��Ă��邩�ǂ������Z�b�g
	void setNearBarricade(bool nb)
	{
		nearBarricade = nb;
	}
	// ��Ԃ��Z�b�g����֐�
	void setState(enemyNS::STATE st) { state = st; }
	// �U���̏�Ԃ��Z�b�g����֐�
	void setAttackState(enemyNS::STATE st) { attackState = st; }
	// �ڕW�n�_���Z�b�g����֐�
	void setGoalPost(VECTOR2 pos) { goalPos = pos; }
	// ������goalDirection�ւƃA�b�v�f�[�g����֐�
	void changeDirection(int strF, int endF);
	// ���S���ɌĂяo���֐�
	void dead();
	// �ړ��\���`�F�b�N
	bool checkCanMove(float x, float y, Map *map);
	// �U���p�̏Փ˔�����o��������t���O�A�U����ԂɑJ�ڂ��������true�ƂȂ��āA����ȊO��false
	bool getAttackCollisionFlag() { return attackCollisionFlag; }
	// ��Ԃ�Ԃ��֐�
	enemyNS::STATE getState() { return state; }
	// �v���C���[�Ƃ̋��������͈͓��Ȃ�true�A����ȊO��false��Ԃ�
	bool checkDistancePlayer(int px, int py);
	// ��ԋ߂��̃o���P�[�h�̈ʒu��Ԃ��֐�
	VECTOR2 searchNearBarricade(Entity &entity, Barricade *barricade);
	// ��ԋ߂��̃o���P�[�h�̃C���f�b�N�X��Ԃ��֐�
	int searchNearBarricadeIndex(Barricade *barricade);
	// �G���G���炠��_�܂ł̒�����Ƀo���P�[�h�����݂�����true�A���݂��Ȃ��ꍇ��false��Ԃ��B
	bool checkBarricadeOnLine(float x, float y, Map *map);
	// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
	void changeAttack();
	// �p�����[�^���Z�b�g
	void reset();
};
#endif
