#ifndef _ENEMY_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _ENEMY_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "character.h"
#include "constants.h"
#include "map.h"
#include "barricade.h"
#include "enemyAttackCollision.h"

namespace enemyNS
{
	const int WIDTH = 32;							// �摜�̕��i�e�t���[���j
	const int HEIGHT = 32;							// �摜�̍���
	const int MOVE_SPEED = 80;						// �ړ����x�i�s�N�Z���j
	const int TEXTURE_COLS = 12;					// �e�N�X�`����12��
	const int MOVE_UP_START_FRAME = 54;				// ������ړ��̃A�j���[�V�����̓t���[��54����J�n
	const int MOVE_UP_END_FRAME = 56;				// ������ړ��̃A�j���[�V�����t���[����54�A55�A56
	const int MOVE_RIGHT_START_FRAME = 66;			// �E�����ړ��̃A�j���[�V�����̓t���[��66����J�n
	const int MOVE_RIGHT_END_FRAME = 68;			// �E�����ړ��̃A�j���[�V�����t���[����66�A67�A68
	const int MOVE_DOWN_START_FRAME = 78;			// �������ړ��̃A�j���[�V�����̓t���[��78����J�n
	const int MOVE_DOWN_END_FRAME = 80;				// �������ړ��̃A�j���[�V�����t���[����78�A79�A80
	const int MOVE_LEFT_START_FRAME = 90;			// �������ړ��̃A�j���[�V�����̓t���[��90����J�n
	const int MOVE_LEFT_END_FRAME = 92;				// �������ړ��̃A�j���[�V�����t���[����90�A91�A92
	const float MOVE_ANIMATION_DELAY = 0.1f;			// �ړ��A�j���[�V�����̃t���[���Ԃ̎���
	const int ATTACK_UP_START_FRAME = 151;			// ������U���̃A�j���[�V�����̓t���[��151����J�n
	const int ATTACK_UP_END_FRAME = 151 + 36;		// ������U���ɃA�j���[�V�����t���[����151�A163�A175�A184
	const int ATTACK_RIGHT_START_FRAME = 148;		// �E�����U���̃A�j���[�V�����̓t���[��148����J�n
	const int ATTACK_RIGHT_END_FRAME = 148 + 36;	// �E�����U���̃A�j���[�V�����t���[����148�A161�A173�A182
	const int ATTACK_DOWN_START_FRAME = 103;		// �������U���̃A�j���[�V�����̓t���[��103����J�n
	const int ATTACK_DOWN_END_FRAME = 103 + 36;		// �������U���̃A�j���[�V�����t���[����103�A115�A127�A139
	const int ATTACK_LEFT_START_FRAME = 100;		// �������U���̃A�j���[�V�����̓t���[��100����J�n
	const int ATTACK_LEFT_END_FRAME = 100 + 36;		// �������U���̃A�j���[�V�����t���[����100�A112�A124�A136
	const float ATTACK_TIME = 0.8f;					// �v���C���[�ɗאڂ��Ă���U���Ɉڂ�܂ł̗��ߎ���
	const float CONTINUE_ATTACK_TIME = 0.8f;		// �A���ōU������ꍇ�̗��ߎ���
	const float DAMAGE_TIME = 1.0f;					// �_���[�W���󂯂Ă���ꍇ�ADAMAGE_TIME���Ƃɉ摜���_��
	const float ATTACK_DAMAGE = 5.0f;
	enum STATE_DETAIL { MOVE_CASTLE, MOVE_BARRICADE, ATTACK_BRAVE, ATTACK_CASTLE, ATTACK_BARRICADE, PRE_ATTACK, GAURD , WAIT };	// �G���G�̏��
	enum TYPE {NORMAL, RED, BLUE};                  // �G�̎��
}

// Enemy�N���X
class Enemy : public Character
{
protected:
	characterNS::DIRECTION oldDirection;	// �U�����O�Ɍ����Ă����������i�[
	characterNS::DIRECTION goalDirection;	// ���ɐi�ނׂ�����
	enemyNS::STATE_DETAIL stateDeteil;		// ���
	enemyNS::STATE_DETAIL attackState;		// �U���p�̏��
	float attackTimer;						// �U���A�j���[�V�����p�̃^�C�}�[
	bool nearBarricade;						// �o���P�[�h�Ɨאڂ��Ă��邩�ǂ���
	bool isAttacked;						// �U���������ォ�ǂ���
	bool inCertainRange;					// �v���C���[�����͈͓��ɂ��邩
	bool canMakeDecesionMove;				// �ړ��Ɋւ��Ă̈ӎv������s���邩�ǂ���
	Barricade* barricades;					// �o���P�[�h�̔z��ւ̃|�C���^
	int nearBarricadeIndex;					// �ŋߐڂ̃o���P�[�h�̃C���f�b�N�X
	float continueAttackTime;
	float attackTime;
	float attackDamage;
	imageNS::MODE attackAnimationMode;
	enemyNS::TYPE type;                     // �G�̎��
	EnemyCollision attackCollision;			// �U������p�̃R���W����
public:
	// �R���X�g���N�^
	Enemy();

	//==========================================================
	// �p�����ꂽ�����o�[�֐�
	//==========================================================
	// Update
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
	virtual void update(float frameTime);
	// �l�H�m�\�BNPC�̍s�������肷��̂Ɏg�p
	virtual void ai(float frameTime, Entity &ent);
	// �L�����N�^�[�Ƀ_���[�W��^����֐�
	virtual void damage(WEAPON);
	// �p�����[�^���Z�b�g
	virtual void reset();

	//==========================================================
	// setter
	//==========================================================
	// �o���P�[�h�Ɨאڂ��Ă��邩�ǂ������Z�b�g
	void setNearBarricade(bool nb) { nearBarricade = nb; }
	// ��Ԃ��Z�b�g����֐�
	void setStateDetail(enemyNS::STATE_DETAIL st) { stateDeteil = st; }
	// �U���̏�Ԃ��Z�b�g����֐�
	void setAttackState(enemyNS::STATE_DETAIL st) { attackState = st; }
	// �o���P�[�h�̔z��ւ̃|�C���^���Z�b�g����֐�
	void setBarricadesPointer(Barricade *b) { barricades = b; }
	// ���ɐi�ނׂ��������Z�b�g����֐�
	void setGoalDirection(characterNS::DIRECTION gd) { goalDirection = gd; }
	// �G�̎�ނ��Z�b�g����֐�
	void setEnemyType(enemyNS::TYPE t);
	// �_���[�W���󂯂鎞�Ɋ|���銄���̍X�V
	void setDamagerPer(float per);

	//==========================================================
	// getter
	//==========================================================
	// ��Ԃ�Ԃ��֐�
	enemyNS::STATE_DETAIL getStateDetail() { return stateDeteil; }
	// ���ɐi�ނׂ�������Ԃ��֐�
	characterNS::DIRECTION getGoalDirection() { return goalDirection; }
	// �ړ��Ɋւ��Ă̈ӎv������s���邩�ǂ���
	bool canMakeDecesionMoving() { return canMakeDecesionMove; }
	// �ŋߐڂ̃o���P�[�h�̃C���f�b�N�X��Ԃ�
	int getNearBarricadeIndex() { return nearBarricadeIndex; }
	// �U������p�̃R���W������Ԃ�
	EnemyCollision& getAttackCollision() { return attackCollision; }
	
	// ������goalDirection�ւƃA�b�v�f�[�g����֐�
	void changeDirection(int strF, int endF);
	// �v���C���[�Ƃ̋��������͈͓��Ȃ�true�A����ȊO��false��Ԃ�
	bool checkDistancePlayer(int px, int py);
	// ��ԋ߂��̃o���P�[�h�̈ʒu��Ԃ��֐�
	VECTOR2 searchNearBarricade(Entity &entity);
	// ��ԋ߂��̃o���P�[�h�̃C���f�b�N�X��Ԃ��֐�
	int searchNearBarricadeIndex();
	// �G���G�����܂ł̒�����Ƀo���P�[�h�����݂�����true�A���݂��Ȃ��ꍇ��false��Ԃ��B
	bool checkBarricadeOnLine();
	// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
	virtual void changeAttack(VECTOR2 &collisionVector);
	// �U�����[�h�Ƀ`�F���W����Ƃ��ɌĂяo���֐�
	virtual void changeAttack(characterNS::DIRECTION dir);
	// �^�C���̒����ɃL�����N�^�[�����邩�ǂ���
	virtual bool isCenterOfTile();
	// �w�肵�������ɐi�߂邩�ǂ���
	bool canMoveTo(characterNS::DIRECTION dir);
	// �G�̎�ނ��擾����֐�
    enemyNS::TYPE getEnemyType();
};
#endif
