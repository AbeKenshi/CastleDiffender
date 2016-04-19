//==========================================================
/// @file
/// @brief    Stage�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _STAGE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _STAGE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"
#include "midBoss.h"
#include "brave.h"
#include "castle.h"
#include "textureManager.h"

class Stage
{
private:
	Map mMap;									// �X�e�[�W�̃}�b�v���
	Barricade mBarricades[mapNS::BARRICADE_NUM];// �o���P�[�h�̔z��
	Brave mBrave;								// �v���C���[
	Castle mCastle;								// ��
	Enemy **mEnemy;	    						// �G�ւ̃|�C���^�̔z��
	float *mEnemyX;								// �G�̏����ʒuX�̔z��
	float *mEnemyY;								// �G�̏����ʒuY�̔z��
	float mRemainingTime;						// �Q�[�����̎c�莞��
	int mEnemyNum;								// �G�̐�
	int mStageNum;								// �I�����Ă���X�e�[�W�̔ԍ�
	int mEnemyWaveNum;							// ���݂̓G�̔g�̔ԍ��i���g�A���g�A�A�A�j
	bool    mRoundOver;							// ���E���h���I�������ꍇ�Atrue
	bool mClearedStage;							// �X�e�[�W���N���A�����ꍇ�Atrue
	bool mInitializedEnemies;					// �G���������ł�����true
public:
	// �R���X�g���N�^
	Stage();
	// �f�X�g���N�^
	~Stage();

	//==========================================================
	// getter
	//==========================================================
	// �}�b�v����Ԃ�
	Map& getMap() { return mMap; }
	// �G�̐���Ԃ�
	int getEnemyNum() { return mEnemyNum; }
	// �X�e�[�W�ԍ���Ԃ�
	int getStageNum() { return mStageNum; }
	// �Q�[�����̎c�莞�Ԃ�Ԃ�
	float getRemainingTime() { return mRemainingTime; }
	// �w�肵���C���f�b�N�X�̓G��Ԃ�
	Enemy& getEnemy(int index) { return *mEnemy[index]; }
	// �E�҂�Ԃ�
	Brave& getBrave() { return mBrave; }
	// �w�肵���C���f�b�N�X�̃o���P�[�h��Ԃ�
	Barricade& getBarricade(int index) { return mBarricades[index]; }
	// ���Ԃ�
	Castle& getCastle() { return mCastle; }
	// �Q�[���I�[�o�[���ǂ�����Ԃ�
	bool getRoundOver() { return mRoundOver; }
	// �X�e�[�W���N���A�������ǂ�����Ԃ�
	bool getClearedStage() { return mClearedStage; }
	// �G���������ł��Ă��邩�ǂ���
	bool getInitializedEnemies() { return mInitializedEnemies; }


	//==========================================================
	// setter
	//==========================================================
	// �X�e�[�W���N���A�������ǂ������Z�b�g
	void setClearedStage(bool cs) { mClearedStage = cs; }
	// �X�e�[�W�ԍ����Z�b�g
	void setStageNum(int sn) { mStageNum = sn; }
	// �G���������ł��Ă��邩�ǂ������Z�b�g
	void setInitializedEnemies(bool initializedE) { mInitializedEnemies = initializedE; }

	// �X�e�[�W����������
	void reset();
	// ���݂̃X�e�[�W�ԍ��ŃQ�[���X�^�[�g
	void roundStart();
	// �l�H�m�\
	void ai(float frameTime);
	// �Փ˂�����
	void collisions();
	// stage��1�X�e�b�v���i�߂�
	void runStage(float frameTime);
	// �G�̐����`�F�b�N���A�}�b�v��ɓG�����Ȃ���ΐV���ɐ���
	void checkCurrentEnemyNum();
	// �w�肳�ꂽ�X�e�[�W�̓G�f�[�^��ǂݍ���
	bool readEnemyFile(int stageNum, int enemyWave);
	// �w�肳�ꂽ�X�e�[�W�A�h�̓G�f�[�^��ǂݍ��ݓG������������
	void initializeEnemies(int stageNum, int enemyWave);
};
#endif