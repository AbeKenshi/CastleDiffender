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
	Map map;									// �X�e�[�W�̃}�b�v���
	Barricade barricades[mapNS::BARRICADE_NUM];	// �o���P�[�h�̔z��
	Brave brave;								// �v���C���[
	Castle castle;								// ��
	Enemy **enemy;	    						// �G�ւ̃|�C���^�̔z��
	float *enemyX;								// �G�̏����ʒuX�̔z��
	float *enemyY;								// �G�̏����ʒuY�̔z��
	float remainingTime;						// �Q�[�����̎c�莞��
	int enemyNum;								// �G�̐�
	int stageNum;								// �I�����Ă���X�e�[�W�̔ԍ�
	int enemyWaveNum;							// ���݂̓G�̔g�̔ԍ��i���g�A���g�A�A�A�j
	bool    roundOver;							// ���E���h���I�������ꍇ�Atrue
	bool clearedStage;							// �X�e�[�W���N���A�����ꍇ�Atrue
	bool initializedEnemies;					// �G���������ł�����true
public:
	// �R���X�g���N�^
	Stage();
	// �f�X�g���N�^
	~Stage();

	//==========================================================
	// getter
	//==========================================================
	// �}�b�v����Ԃ�
	Map& getMap() { return map; }
	// �G�̐���Ԃ�
	int getEnemyNum() { return enemyNum; }
	// �X�e�[�W�ԍ���Ԃ�
	int getStageNum() { return stageNum; }
	// �Q�[�����̎c�莞�Ԃ�Ԃ�
	float getRemainingTime() { return remainingTime; }
	// �w�肵���C���f�b�N�X�̓G��Ԃ�
	Enemy& getEnemy(int index) { return *enemy[index]; }
	// �E�҂�Ԃ�
	Brave& getBrave() { return brave; }
	// �w�肵���C���f�b�N�X�̃o���P�[�h��Ԃ�
	Barricade& getBarricade(int index) { return barricades[index]; }
	// ���Ԃ�
	Castle& getCastle() { return castle; }
	// �Q�[���I�[�o�[���ǂ�����Ԃ�
	bool getRoundOver() { return roundOver; }
	// �X�e�[�W���N���A�������ǂ�����Ԃ�
	bool getClearedStage() { return clearedStage; }
	// �G���������ł��Ă��邩�ǂ���
	bool getInitializedEnemies() { return initializedEnemies; }


	//==========================================================
	// setter
	//==========================================================
	// �X�e�[�W���N���A�������ǂ������Z�b�g
	void setClearedStage(bool cs) { clearedStage = cs; }
	// �X�e�[�W�ԍ����Z�b�g
	void setStageNum(int sn) { stageNum = sn; }
	// �G���������ł��Ă��邩�ǂ������Z�b�g
	void setInitializedEnemies(bool initializedE) { initializedEnemies = initializedE; }

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