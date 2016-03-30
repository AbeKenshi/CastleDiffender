#ifndef _TOWERDIFFENCE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _TOWERDIFFENCE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "text.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"
#include "braveAttackCollision.h"
#include "enemyAttackCollision.h"
#include "fire.h"
#include "map.h"
#include "castle.h"
#include "enemy.h"
#include "midBoss.h"
#include "dashboard.h"
#include "rect.h"
#include "barricade.h"
#include "braveIcon.h"
#include "castleIcon.h"
#include "hpTextImage.h"
#include "mpTextImage.h"
#include <string>

namespace towerDiffenceNS
{
	const char FONT[] = "Arial Bold";	// �t�H���g
	const int FONT_BIG_SIZE = 256;		// �t�H���g�̍���
	const int FONT_SCORE_SIZE = 48;
	// �̗̓o�[�̈ʒu
	const int BRAVE_HEALTH_BAR_X = 100;
	const int BRAVE_HEALTH_BAR_Y = 0;
	const int BRAVE_MP_BAR_X = BRAVE_HEALTH_BAR_X;
	const int BRAVE_MP_BAR_Y = 25;
	const int CASTLE_HEALTH_BAR_X = 830;
	const int CASTLE_HEALTH_BAR_Y = 0;
	const int COUNT_DOWN_X = GAME_WIDTH / 2 - FONT_BIG_SIZE / 4;
	const int COUNT_DOWN_Y = GAME_HEIGHT / 2 - FONT_BIG_SIZE / 2;
	const int ROUND_TIME = 5;           // �V�������E���h���J�n����܂ł̎���
	const int ENEMY_NUM = 1;  // �G���G�̐�
}

//==========================================================
// Game�N���X���p������TowerDiffence�N���X���쐬
//==========================================================
class TowerDiffence : public Game
{
private:
	// �Q�[���A�C�e��
	TextDX  fontBig;									// �Q�[���o�i�[��DirectX�t�H��
	Text    *fontCK;									// sprite based font
	TextureManager menuTexture;							// �^�C�g���̃e�N�X�`��
	Image menu;											// �^�C�g���摜
	TextureManager resultTexture;                       // ���U���g�̃e�N�X�`��
	Image result;                                       // ���U���g�摜
	TextureManager braveTexture;						// �E�҂̃e�N�X�`��
	Brave brave;										// �E��
	TextureManager braveIconTexture;					// �E�҂̃A�C�R���̃e�N�X�`��
	BraveIcon braveIcon;								// �E�҂̃A�C�R��
	TextureManager attackCollisionTexture;				// �E�҂̍U���̓����蔻��p�̃e�N�X�`��
	BraveAttackCollision braveAttackCollision;			// �E�҂̍U���̓����蔻��p
	EnemyCollision enemyAttackCollision[towerDiffenceNS::ENEMY_NUM]; // �G���G�̍U���̓����蔻��p
	EnemyCollision midBossAttackCollision;		// ���{�X�̍U���̓����蔻��p
	TextureManager tileTexture;							// �^�C���̃e�N�X�`��
	Map map;											// �^�C���摜
	TextureManager barricadeTexture;					// �o���P�[�h�̃e�N�X�`��
	Barricade barricades[mapNS::BARRICADE_NUM];         // �o���P�[�h�̔z��
	TextureManager castleTexture;						// ��̃e�N�X�`��
	Castle castle;										// ��
	TextureManager castleIconTexture;					// ��̃A�C�R���̃e�N�X�`��
	CastleIcon castleIcon;								// ��̃A�C�R��
	TextureManager fireTexture;							// ���̃e�N�X�`��
	Fire fire;											// ��
	TextureManager enemyTexture;						// �G���G�̃e�N�X�`��
	Enemy enemy[towerDiffenceNS::ENEMY_NUM];	    	// �G���G
	TextureManager midBossTexture;						// ���{�X�̃e�N�X�`��
	MidBoss midBoss;									// ���{�X
	TextureManager dashboardTextures;					// �_�b�V���{�[�h�e�N�X�`��
	BarGraph braveHealthBar;							// �E�҂̗̑̓o�[
	BarGraph braveMpBar;								// �E�҂�MP�o�[
	BarGraph castleHealthBar;							// ��̗̑̓o�[
	TextureManager textTexture;							// �e�L�X�g�i�l�o�A�g�o�j�̃e�N�X�`��
	HpTextImage braveHpText;							// �E�҂̂g�o�e�L�X�g
	MpTextImage braveMpText;							// �E�҂̂l�o�e�L�X�g
	HpTextImage castleHpText;							// ��̂g�o�e�L�X�g
	Rect *rect;											// Rect�ւ̃|�C���^�[
	bool menuOn;										// ���j���[�t���O
	float remainingTime;								// �Q�[�����̎c�莞��
	bool    roundOver;									// ���E���h���I�������ꍇ�Atrue
	float   roundTimer;									// �V�������E���h���J�n����܂ł̎���
	int a = 0;
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
