#ifndef _TOWERDIFFENCE_H	// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _TOWERDIFFENCE_H	// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "brave.h"

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
