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
#include "hitEffect.h"
#include "attackEffect.h"
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
	const int ROUND_TIME = 3;           // �V�������E���h���J�n����܂ł̎���
	const int ENEMY_NUM = 10;  // �G���G�̐�
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
	TextureManager stageSelectTexture;					// �X�e�[�W�I����ʂ̃e�N�X�`��
	Image stageSelect;									// �X�e�[�W�I����ʂ̉摜
	TextureManager resultTexture;                       // ���U���g�̃e�N�X�`��
	Image result;                                       // ���U���g�摜
	TextureManager stageClearTexture;					// �X�e�[�W�N���A��ʂ̃e�N�X�`��
	Image stageClear;									// �X�e�[�W�N���A�摜
	TextureManager descriptionTexture;                  // ��������̃e�N�X�`��
	Image description;                                  // ��������摜
	TextureManager braveTexture;						// �E�҂̃e�N�X�`��
	Brave brave;										// �E��
	TextureManager attackEffectTexture;					// �U���̏Ռ��g�̃e�N�X�`��
	TextureManager braveIconTexture;					// �E�҂̃A�C�R���̃e�N�X�`��
	BraveIcon braveIcon;								// �E�҂̃A�C�R��
	TextureManager attackCollisionTexture;				// �E�҂̍U���̓����蔻��p�̃e�N�X�`��
	BraveAttackCollision braveAttackCollision;			// �E�҂̍U���̓����蔻��p
	TextureManager tileTexture;							// �^�C���̃e�N�X�`��
	Map map;											// �^�C���摜
	TextureManager barricadeTexture;					// �o���P�[�h�̃e�N�X�`��
	Barricade barricades[mapNS::BARRICADE_NUM];         // �o���P�[�h�̔z��
	TextureManager hitEffectTexture;					// �U�����q�b�g�����Ƃ��̃A�j���[�V�����摜�̃e�N�X�`��
	TextureManager castleTexture;						// ��̃e�N�X�`��
	Castle castle;										// ��
	TextureManager castleIconTexture;					// ��̃A�C�R���̃e�N�X�`��
	CastleIcon castleIcon;								// ��̃A�C�R��
	TextureManager fireTexture;							// ���̃e�N�X�`��
	Fire fire;											// ��
	TextureManager enemyTexture;						// �G���G�̃e�N�X�`��
	Enemy **enemy;	    								// �G�ւ̃|�C���^�̔z��
	float *enemyX;										// �G�̏����ʒuX�̔z��
	float *enemyY;										// �G�̏����ʒuY�̔z��
	TextureManager midBossTexture;						// ���{�X�̃e�N�X�`��
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
	bool stageSelectOn;									// �X�e�[�W�I���t���O
	bool descriptionOn;                                 // ��������t���O
	float remainingTime;								// �Q�[�����̎c�莞��
	bool    roundOver;									// ���E���h���I�������ꍇ�Atrue
	bool clearedStage;									// �X�e�[�W���N���A�����ꍇ�Atrue
	float   roundTimer;									// �V�������E���h���J�n����܂ł̎���
	int enemyNum;										// �X�e�[�W��ɑ��݂���G�̐�
	int stageNum;										// �I�����Ă���X�e�[�W�̔ԍ�
	int enemyWaveNum;									// ���݂̓G�̔g�̔ԍ��i���g�A���g�A�A�A�j
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
	// �G�̐����`�F�b�N���A�}�b�v��ɓG�����Ȃ���ΐV���ɐ���
	void checkCurrentEnemyNum();

	void consoleCommand();	// �R���\�[���R�}���h������

	// �O���t�B�b�N�X�f�o�C�X�����������ꍇ
	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽�߁A
	// �\�񂳂�Ă����r�f�I�����������ׂĉ��
	void releaseAll();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�ꍇ
	// ���ׂẴT�[�t�F�C�X���č쐬
	void resetAll();

	// �w�肳�ꂽ�X�e�[�W�̓G�f�[�^��ǂݍ���
	bool readEnemyFile(int stageNum, int enemyWave);

	// �w�肳�ꂽ�X�e�[�W�A�h�̓G�f�[�^��ǂݍ��ݓG������������
	void initializeEnemies(int stageNum, int enemyWave);

	// �Q�[���I�[�o�[���ɌĂяo��
	void gameOver();

	// �X�e�[�W�N���A���ɌĂяo��
	void clearStage();
};
#endif
