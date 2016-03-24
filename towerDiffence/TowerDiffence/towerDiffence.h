#ifndef _TOWERDIFFENCE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _TOWERDIFFENCE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"
#include "attackCollision.h"
#include "fire.h"
#include "map.h"
#include "enemy.h"
#include "dashboard.h"
#include "rect.h"
#include "barricade.h"

namespace towerDiffenceNS
{
	// �̗̓o�[�̈ʒu
	const int BAR_GRAPH_X = 0;	
	const int BAR_GRAPH_Y = 0;
	const int HBAR_X = 0;
	const int HBAR_Y = 0;
}

//==========================================================
// Game�N���X���p������TowerDiffence�N���X���쐬
//==========================================================
class TowerDiffence : public Game
{
private:
	// �Q�[���A�C�e��
	TextureManager menuTexture;		// �^�C�g���̃e�N�X�`��
	Image menu;						// �^�C�g���摜
	TextureManager braveTexture;	// �E�҂̃e�N�X�`��
	Brave brave;					// �E��
	TextureManager braveAttackCollisionTexture;	// �E�҂̍U���̓����蔻��p�̃e�N�X�`��
	AttackCollision braveAttackCollision;		// �E�҂̍U���̓����蔻��p
	TextureManager tileTexture;     // �^�C���̃e�N�X�`��
	Map map;                        // �^�C���摜
	TextureManager barricadeTexture;	// �o���P�[�h�̃e�N�X�`��
	Barricade barricade;			// �o���P�[�h�摜
	TextureManager fireTexture;		// ���̃e�N�X�`��
	Fire fire;						// ���̉摜
	TextureManager enemyTexture;	// �G���G�̃e�N�X�`��
	Enemy enemy;					// �G���G�̉摜
	TextureManager dashboardTextures;	// �_�b�V���{�[�h�e�N�X�`��
	BarGraph barGraph;				// �̗̓o�[
	Rect *rect;						// Rect�ւ̃|�C���^�[
	float mapX;                     // ����X���W
	bool menuOn;					// ���j���[�t���O

public:
	// �R���X�g���N�^
	TowerDiffence();

	// �f�X�g���N�^
	virtual ~TowerDiffence();

	// �Q�[����������
	void initialize(HWND hwnd);

	// Game����̏������z�֐����I�[�o�[���C�h����K�v������
	void update();
	void ai();
	void collisions();
	void render();

	// �v���C�̐V�������E���h���J�n
	void roundStart();

	// �O���t�B�b�N�X�f�o�C�X�����������ꍇ
	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽�߁A
	// �\�񂳂�Ă����r�f�I�����������ׂĉ��
	void releaseAll();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�ꍇ
	// ���ׂẴT�[�t�F�C�X���č쐬
	void resetAll();

};
#endif
