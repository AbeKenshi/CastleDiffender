//==========================================================
/// @file
/// @brief    CastleDiffence�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _CASTLE_DIFFENDER_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _CASTLE_DIFFENDER_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
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
#include "stage.h"

// CastleDiffender�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace castleDiffenderNS
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
// Game�N���X���p������CastleDiffender�N���X���쐬
//==========================================================
class castleDiffender : public Game
{
private:
	// �Q�[���A�C�e��
	Stage mStage;										// �X�e�[�W���
	TextDX  mFontBig;									// �Q�[���o�i�[��DirectX�t�H��
	Text*    mFontCK;									// sprite based font
	TextureManager mMenuTexture;						// �^�C�g���̃e�N�X�`��
	TextureManager mStageSelectTexture;					// �X�e�[�W�I����ʂ̃e�N�X�`��
	TextureManager mResultTexture;                      // ���U���g�̃e�N�X�`��
	TextureManager mStageClearTexture;					// �X�e�[�W�N���A��ʂ̃e�N�X�`��
	TextureManager mDescriptionTexture;                 // ��������̃e�N�X�`��
	TextureManager mBraveTexture;						// �E�҂̃e�N�X�`��
	TextureManager mAttackEffectTexture;				// �U���̏Ռ��g�̃e�N�X�`��
	TextureManager mBraveIconTexture;					// �E�҂̃A�C�R���̃e�N�X�`��
	TextureManager mAttackCollisionTexture;				// �E�҂̍U���̓����蔻��p�̃e�N�X�`��
	TextureManager mTileTexture;						// �^�C���̃e�N�X�`��
	TextureManager mBarricadeTexture;					// �o���P�[�h�̃e�N�X�`��
	TextureManager mHitEffectTexture;					// �U�����q�b�g�����Ƃ��̃A�j���[�V�����摜�̃e�N�X�`��
	TextureManager mCastleTexture;						// ��̃e�N�X�`��
	TextureManager mCastleIconTexture;					// ��̃A�C�R���̃e�N�X�`��
	TextureManager mFireTexture;						// ���̃e�N�X�`��
	TextureManager mEnemyTexture;						// �G���G�̃e�N�X�`��
	TextureManager mMidBossTexture;						// ���{�X�̃e�N�X�`��
	TextureManager mDashboardTextures;					// �_�b�V���{�[�h�e�N�X�`��
	TextureManager mTextTexture;						// �e�L�X�g�i�l�o�A�g�o�j�̃e�N�X�`��
	Image mMenu;										// �^�C�g���摜
	Image mStageSelect;									// �X�e�[�W�I����ʂ̉摜
	Image mResult;                                      // ���U���g�摜
	Image mStageClear;									// �X�e�[�W�N���A�摜
	Image mDescription;                                 // ��������摜
	BraveIcon mBraveIcon;								// �E�҂̃A�C�R��
	CastleIcon mCastleIcon;								// ��̃A�C�R��
	BarGraph mBraveHealthBar;							// �E�҂̗̑̓o�[
	BarGraph mBraveMpBar;								// �E�҂�MP�o�[
	BarGraph mCastleHealthBar;							// ��̗̑̓o�[
	HpTextImage mBraveHpText;							// �E�҂̂g�o�e�L�X�g
	MpTextImage mBraveMpText;							// �E�҂̂l�o�e�L�X�g
	HpTextImage mCastleHpText;							// ��̂g�o�e�L�X�g
	Rect* mRect;										// Rect�ւ̃|�C���^�[
	bool mMenuOn;										// ���j���[�t���O
	bool mStageSelectOn;								// �X�e�[�W�I���t���O
	bool mDescriptionOn;                                // ��������t���O
	float   mRoundTimer;								// �V�������E���h���J�n����܂ł̎���
	int mHighScores[3];									// �e�X�e�[�W�̃n�C�X�R�A
public:
	// �R���X�g���N�^
	castleDiffender();

	// �f�X�g���N�^
	virtual ~castleDiffender();

	// �Q�[����������
	// �G���[����GameError���X���[
	void initialize(HWND hwnd);

	// Game����̏������z�֐����I�[�o�[���C�h����K�v������
	// ���ׂẴQ�[���A�C�e�����X�V
	void update();
	// �l�H�m�\
	void ai();
	// �Փ˂�����
	void collisions();
	// �Q�[���A�C�e���������_�[
	// �v���C���̃��C���[�F�}�b�v�����w�i�����̑��A�C�e���̏�
	void render();

	// �v���C�̐V�������E���h���J�n
	void roundStart();

	// �R���\�[���R�}���h������
	// �f�o�b�O�p
	void consoleCommand();

	// �O���t�B�b�N�X�f�o�C�X�����������ꍇ
	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g�\�ɂ��邽�߁A
	// �\�񂳂�Ă����r�f�I�����������ׂĉ��
	void releaseAll();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�ꍇ
	// ���ׂẴT�[�t�F�C�X���č쐬
	void resetAll();


	// �Q�[���I�[�o�[���ɌĂяo��
	void gameOver();

	// �X�e�[�W�N���A���ɌĂяo��
	void clearStage();

	// �G�̃e�N�X�`��������������
	void initializeEnemiesTexture();
	
	//
	void loadHighScore();
};
#endif
