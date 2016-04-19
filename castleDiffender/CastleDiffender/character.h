//==========================================================
/// @file
/// @brief    Character�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _CHARACTER_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CHARACTER_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "map.h"

// Character�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace characterNS
{
	enum DIRECTION { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NONE = 4};				// �L�����N�^�[�̌����i�㉺���E�j
	enum STATE { MOVE, ATTACK, SECOND_ATTACK, GAURD , PRE_ATTACK , WAIT , DEATH };	// ��ԁi�ړ����A�U�����A��񌂒��A�K�[�h���A�U�����O�A�ҋ@�A���S�j
}

// Character�N���X
// �v���C���[��G�N���X�̊�{�ƂȂ�N���X�B
// �p�����邱�ƂŎg�p�\�B�p���Ȃ��ł̓I�u�W�F�N�g�̐����͂ł��Ȃ��B
class Character : public Entity
{
protected:
	characterNS::DIRECTION mDirection;	// �L�����N�^�[�̌����i�㉺���E�j
	int mOldStartFrame;					// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����t���[���ۑ��p
	int mOldEndFrame;					// �U���A�j���[�V�����I����ɖ߂�ׂ��A�j���[�V�����t���[���ۑ��p
	bool mAttackCollisionFlag;			// �U���p�̏Փ˔�����o��������t���O�B�U�����J�n���Ă����莞�Ԍ��true�ƂȂ�B���Ԃ𒲐����邱�Ƃɂ���ăA�j���[�V�����Ɠ���������̂��ړI�B
	Map *mMap;							// �X�e�[�W�}�b�v�ւ̃|�C���^
	characterNS::STATE mState;			// ��ԁi�ړ����A�U�����A��񌂒��A�K�[�h���A�U�����O�A�ҋ@�A���S�j
	int mMoveUpStartFrame;				// ������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	int mMoveUpEndFrame;				// ������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	int mMoveRightStartFrame;			// �E�����ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	int mMoveRightEndFrame;				// �E�����ړ��̃A�j���[�V�����̍Ō�̃t���[��
	int mMoveDownStartFrame;			// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	int mMoveDownEndFrame;				// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	int mMoveLeftStartFrame;			// �������ړ��̃A�j���[�V�����̍ŏ��̃t���[��
	int mMoveLeftEndFrame;				// �������ړ��̃A�j���[�V�����̍Ō�̃t���[��
	int mAttackUpStartFrame;			// ������U���̃A�j���[�V�����̍ŏ��̃t���[��
	int mAttackUpEndFrame;				// ������U���̃A�j���[�V�����̍Ō�̃t���[��
	int mAttackRightStartFrame;			// �E�����U���̃A�j���[�V�����̍ŏ��̃t���[��
	int mAttackRightEndFrame;			// �E�����U���̃A�j���[�V�����̍Ō�̃t���[��
	int mAttackDownStartFrame;			// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	int mAttackDownEndFrame;			// �������U���̃A�j���[�V�����̍Ō�̃t���[��
	int mAttackLeftStartFrame;			// �������U���̃A�j���[�V�����̍ŏ��̃t���[��
	int mAttackLeftEndFrame;			// �������U���̃A�j���[�V�����̍Ō�̃t���[��
public:
	// �R���X�g���N�^
	Character();

	//==========================================================
	// �p�����ꂽ�����o�[�֐�
	//==========================================================
	// Update
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
	virtual void update(float frameTime) = 0;
	// �l�H�m�\�BNPC�̍s�������肷��̂Ɏg�p
	virtual void ai(float frameTime, Entity &ent) = 0;
	// �L�����N�^�[�Ƀ_���[�W��^����֐�
	virtual void damage(WEAPON) = 0;

	//==========================================================
	// �V�����ǉ����郁���o�[�֐�
	//==========================================================
	// �p�����[�^���Z�b�g
	virtual void reset();
	// �ړ��\���`�F�b�N
	// ���s�O�Fx�Ay = �`�F�b�N�������ʒu�̉�ʏ�ł̍��W
	virtual bool checkCanMove(float x, float y);	
	// ���S���ɌĂяo���֐�
	void dead();
	// �ړ����̃A�b�v�f�[�g�֐�
	// �A�j���[�V�����ȊO���A�b�v�f�[�g
	void updateMoving(float frameTime);
	// �U�����̃A�b�v�f�[�g�֐�
	// ����ł͒ʏ�̃A�b�v�f�[�g
	void updateAttacking(float frameTime);

	//==========================================================
	// setter
	//==========================================================
	// �}�b�v�ւ̃|�C���^���Z�b�g����֐�
	void setMapPointer(Map& m) { mMap = &(m); }
	// ��Ԃ��Z�b�g����֐�
	void setState(characterNS::STATE st) { mState = st; }
	// �����Ă���������Z�b�g����
	// ���s�O�Fdir = �Z�b�g����L�����N�^�[�̌���
	void setDirection(characterNS::DIRECTION dir);

	//==========================================================
	// getter
	//==========================================================
	// �U���p�̏Փ˔�����o��������t���O��Ԃ��֐��B�U����ԂɑJ�ڂ��������true�ƂȂ��āA����ȊO��false
	bool getAttackCollisionFlag() { return mAttackCollisionFlag; }
	// �����Ă��������Ԃ��֐�
	characterNS::DIRECTION getDirection() { return mDirection; }
	// ��Ԃ�Ԃ��֐�
	characterNS::STATE getState() { return mState; }

	// �ړ����ւƏ�Ԃ�J��
	void changeStateToMove();

};

#endif // !_CHARACTER_H
