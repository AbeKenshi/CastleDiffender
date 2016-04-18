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
#include "brave.h"

class Stage
{
private:
	Map map;		// �X�e�[�W�̃}�b�v���
	int enemyNum;	// �G�̐�
	Enemy *enemy;	// �G�̔z��
	Brave brave;	// �v���C���[
public:
	// �R���X�g���N�^
	Stage();

	//==========================================================
	// getter
	//==========================================================
	Map& getMap() { return &map; }
	int getEnemyNum() { return enemyNum; }
	Enemy& getEnemy(int index) { return &enemy[index]; }
	Brave& getBrave() { return brave; }
};
#endif