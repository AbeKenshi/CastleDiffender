//==========================================================
/// @file
/// @brief    Entity�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _ENTITY_H               // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA 
#define _ENTITY_H               // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

class Entity;

#include "image.h"
#include "input.h"
#include "game.h"

// Entity�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace entityNS
{
	enum COLLISION_TYPE { NONE, CIRCLE, BOX, ROTATED_BOX };	// �Փ˔���̎��
	const float GRAVITY = 6.67428e-11f;						// �d�͒萔
}

class Entity : public Image
{
	// Entity�v���p�e�B
protected:
	entityNS::COLLISION_TYPE mCollisionType;	// �Փ˔���̎��
	VECTOR2 mCenter;				// �G���e�B�e�B�̒��S
	float   mRadius;				// �~�̏Փ˔���̑傫��
	VECTOR2 mDistSquared;			// �~�̏Փ˔���̌v�Z�Ɏg�p
	float   mSumRadiiSquared;
	RECT    mEdge;					// BOX��ROTATED_BOX�̏Փ˔���p�̃{�b�N�X
	VECTOR2 mCorners[4];			// ROTATED_BOX�̏Փ˔���p
	VECTOR2 mEdge01, mEdge03;		// ���e�p�̃G�b�W
	// ���̃G���e�B�e�B�̃{�b�N�X��edge01��edge03�ɓ��e�����ꍇ�̍ő�ƍŏ��̓��e
	float   mEntA01min, mEntA01max, mEntA03min, mEntA03max;
	// ����̃{�b�N�X��edge01��edge03�ɓ��e�����ꍇ�̍ő�ƍŏ��̓��e
	float   mEntB01min, mEntB01max, mEntB03min, mEntB03max;
	VECTOR2 mVelocity;				// ���x
	VECTOR2 mDeltaV;				// ����update()���Ăяo���ꂽ�Ƃ��̉����x
	float   mMass;					// �G���e�B�e�B�̎���
	float   mHealth;				// �̗́i0~100�j
	float   mRr;					// ���̃G���e�B�e�B�Ƒ���̃G���e�B�e�B�܂ł̋���
	float   mForce;					// �G���e�B�e�B�ɓ�����
	float   mGravity;				// �Q�[�����E�ł̏d�͒萔
	Input   *mInput;				// ���̓V�X�e���ւ̃|�C���^
	Audio   *mAudio;				// �I�[�f�B�I�V�X�e���ւ̃|�C���^
	HRESULT mHr;					// �W���̖߂�l
	bool    mActive;				// true�̂Ƃ��̂݃G���e�B�e�B�̏Փ˔��肪�L��
	bool    mRotatedBoxReady;		// ��]�����Փ˔���p�̃{�b�N�X�������ł����ꍇ�Atrue
	int mTileX, mTileY;				// ���������݂���^�C���̈ʒu
	bool mIsDamaged;				// �_���[�W���󂯂Ă����Ԃ��ǂ���
	bool mDrawFlag;					// �`��t���O�Atrue���ɕ`��
	float mDamagePer;			    // �_���[�W���󂯂鎞�Ɋ|���銄��
	float mDamageTimer;				// �_���[�W���̃A�j���[�V�����p�̃^�C�}�[
	float mTotalDamageTime;			// �_���[�W���̃A�j���[�V�����p�̃^�C�}�[

	// �~�̏Փ˔��胁�\�b�h
	// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
	// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
	// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
	virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
	// �����s���E�{�b�N�X�̏Փ˔��胁�\�b�h
	// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
	// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
	// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
	virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
	// ��]����{�b�N�X�̏Փ˔��胁�\�b�h
	// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
	// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
	// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
	// �������e�X�g���g�p���ďՓ˂𔻒�
	// �������e�X�g�F
	// 2�̃{�b�N�X�́A����̒����ւ̓��e���d�Ȃ��Ă��Ȃ���ΏՓ˂��Ă��Ȃ�
	virtual bool collideRotatedBox(Entity &ent, VECTOR2 &collisionVector);
	// ��]����{�b�N�X�Ɖ~�̏Փ˔��胁�\�b�h
	// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
	// �{�b�N�X�̕ӂƉ~�̔��a�ŕ������e�X�g���g�p
	// �~�̒��S���Փ˃{�b�N�X�̊e�ӂ�L�΂��������̊O��
	// �i�{���m�C�̈�j�ɂ���ꍇ�A�{�b�N�X�̍ł��߂����_��
	// �Փ˂��Ȃ����������̃`�F�b�N�Ŕ��肵�܂��B
	// �ł��߂����_�́A�d�Ȃ�̃e�X�g���画�f�ł��܂��B
	// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
	// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
	virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
	// ��]����{�b�N�X�̒��_�A���e���A���e�̍ŏ��l�ƍő�l���v�Z
	void computeRotatedBox();
	// ����̃{�b�N�X���A���̃G���e�B�e�B��edge01�����edge03�ɓ��e
	// collideRotateBos()�ɂ���ČĂяo�����
	// ���s��F���e���d�Ȃ��Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
	bool projectionsOverlap(Entity &ent, VECTOR2 &collisionVector);
	// �{�b�N�X�̒��_���~�ƏՓ˂��Ă��Ȃ������A�����̃`�F�b�N���g�p���Ĕ���
	// collideRotateBosCircle()�ɂ���ČĂяo�����
	// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
	// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
	bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);
public:
	// �R���X�g���N�^
	Entity();
	// �f�X�g���N�^
	virtual ~Entity() {}

	////////////////////////////////////////
	//           getter                   //
	////////////////////////////////////////

	// ��ʏ�ł̃G���e�B�e�B�̒��S�̍��W��߂�
	virtual const VECTOR2* getCenter()
	{
		mCenter = VECTOR2(getCenterX(), getCenterY());
		return &mCenter;
	}

	// �~�̏Փ˔���̑傫����߂�
	virtual float getRadius() const { return mRadius; }

	// BOX��ROTATED_BOX�̏Փ˔���p�̃{�b�N�X��߂�
	virtual const RECT& getEdge() const { return mEdge; }
	
	// ROTATED_BOX�̏Փ˔���p�̃{�b�N�X�̒��_�̍��W��߂�
	virtual const VECTOR2* getCorner(UINT c) const
	{
		if (c >= 4)
			c = 0;
		return &mCorners[c];
	}

	// ���x�x�N�g����߂�
	virtual const VECTOR2 getVelocity() const { return mVelocity; }

	// �G���e�B�e�B���A�N�e�B�u���ǂ�����߂�
	virtual bool  getActive()         const { return mActive; }

	// ���ʂ�߂�
	virtual float getMass()           const { return mMass; }

	// �d�͒萔��߂�
	virtual float getGravity()        const { return mGravity; }

	// �̗͂�߂�
	virtual float getHealth()         const { return mHealth; }

	// �Փ˔���̎�ނ�߂�(NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual entityNS::COLLISION_TYPE getCollisionType() { return mCollisionType; }
	
	// ���������݂���^�C����X�ʒu��߂�
	int getTileX() { return mTileX; }
	
	// ���������݂���^�C����Y�ʒu��߂�
	int getTileY() { return mTileY; }
	
	////////////////////////////////////////
	//           setter                   //
	////////////////////////////////////////

	// ���x���Z�b�g
	virtual void  setVelocity(VECTOR2 v) { mVelocity = v; }

	// ���̍X�V�ł̉����x���Z�b�g
	virtual void  setDeltaV(VECTOR2 dv) { mDeltaV = dv; }

	// �G���e�B�e�B���A�N�e�B�u���ǂ������Z�b�g
	virtual void  setActive(bool a) { mActive = a; }

	// �̗͂��Z�b�g
	virtual void setHealth(float h) { mHealth = h; }

	// ���ʂ��Z�b�g
	virtual void  setMass(float m) { mMass = m; }

	// �d�͒萔���Z�b�g�B�f�t�H���g��6.67428e-11
	virtual void  setGravity(float g) { mGravity = g; }

	// �~�̏Փ˔���p�̔��a���Z�b�g
	virtual void setCollisionRadius(float r) { mRadius = r; }

	// �Փ˔���̎�ނ��Z�b�g(NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
	{
		mCollisionType = ctype;
	}


	// BOX��ROTATED_BOX�̏Փ˔���p�̃{�b�N�X���Z�b�g
	virtual void setEdge(RECT e) { mEdge = e; }

	// ��]�����Փ˔���p�̃{�b�N�X�������ł��Ă��邩���Z�b�g
	virtual void setRotatedBoxReady(bool r) { mRotatedBoxReady = r; }

	// �^�C����ł̈ʒu���Z�b�g����֐�
	void setTileX(int x) { mTileX = x; }

	// �^�C����ł̈ʒu���Z�b�g����֐�
	void setTileY(int y) { mTileY = y; }

	// �_���[�W���󂯂�Ƃ��Ɋ|���銄�����Z�b�g
	void setDamagePer(float per) { mDamagePer = per; }

	////////////////////////////////////////
	//         ���̑��̊֐�               //
	////////////////////////////////////////

	// update
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
	virtual void update(float frameTime);

	// �`��֐��A�`��t���O���I���̂Ƃ��̂ݕ`�������
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);

	// �G���e�B�e�B���X�V
	// �A�j���[�V�����𖈎��ԍX�V�������Ȃ��ꍇ�͂��̃��\�b�h���g�p����B
	virtual void updateWithoutImage(float frameTime);

	// �A�j���[�V�����̂ݍX�V���郁�\�b�h
	// �A�j���[�V�����𖈎��ԍX�V�������Ȃ��ꍇ�͂��̃��\�b�h���g�p����B
	virtual void updateOnlyImage(float frameTime);

	// �p�����[�^���Z�b�g
	virtual void reset();

	// Entity��������
	// ���s�O�F*gamePtr = Game�I�u�W�F�N�g�ւ̃|�C���^
	//		   width = Image�̕��i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̕����g�p�j
	//		   height = Image�̍����i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̍������g�p�j
	//         ncols = �e�N�X�`�����̗񐔁i1����n�܂Łj�i0��1�Ɠ����j
	//         *textureM = Texturemanager�I�u�W�F�N�g�ւ̃|�C���^
	// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);

	// �G���e�B�e�B���A�N�e�B�u��
	virtual void activate();

	// AI�i�l�H�m�\�j
	// �ʏ�A�t���[�����Ƃ�1��Ăяo��
	// �l�H�m�\�v�Z�����s�Aent�͑��ݍ�p�̂��߂ɓn�����
	virtual void ai(float frameTime, Entity &ent);

	// ���̃G���e�B�e�B���w�肳�ꂽ��`�̊O���ɂ��邩
	virtual bool outsideRect(RECT rect);

	// ���̃G���e�B�e�B�Ƃ�������̃G���e�B�e�B���Փ˂��Ă��邩
	virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	// damage
	// ���̃G���e�B�e�B���A����ɂ���ă_���[�W���󂯂�
	// �p�����鑤�̃N���X�ł��̊֐����I�[�o�[���C�h
	virtual void damage(int weapon);

	// ���̃G���e�B�e�B�Ƃ̏Փˌ�̒��˕Ԃ�
	void bounce(VECTOR2 &collisionVector, Entity &ent);

	// ����̃G���e�B�e�B���炱�̃G���e�B�e�B�ւ̏d��
	// �d�͂����̃G���e�B�e�B�̑��x�x�N�g���ɉ��Z
	void gravityForce(Entity *other, float frameTime);

	// �^�C����ł̈ʒu������������֐�
	void initTileXY();
};

#endif
