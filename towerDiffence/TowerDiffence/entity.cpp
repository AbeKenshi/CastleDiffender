//==========================================================
/// @file
/// @brief    entity.h�̎���
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#include "entity.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Entity::Entity() : Image()
{
    radius = 1.0;
    edge.left = -1;
    edge.top = -1;
    edge.right = 1;
    edge.bottom = 1;
    mass = 1.0;
    velocity.x = 0.0;
    velocity.y = 0.0;
    deltaV.x = 0.0;
    deltaV.y = 0.0;
    active = true;                  // �G���e�B�e�B�̓A�N�e�B�u
    rotatedBoxReady = false;
    collisionType = entityNS::CIRCLE;
    health = 100;
    gravity = entityNS::GRAVITY;
	isDamaged = false;
	drawFlag = true;
	damagePer = 1.0f;
}

//==========================================================
// �p�����[�^������
//==========================================================
void Entity::reset()
{
	rotatedBoxReady = false;
	active = true;
	health = 100;
	isDamaged = false;
	drawFlag = true;
	damagePer = 1.0f;
	Image::reset();
}

//=============================================================================
// Entity��������
// ���s�O�F*gamePtr = Game�I�u�W�F�N�g�ւ̃|�C���^
//		   width = Image�̕��i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̕����g�p�j
//		   height = Image�̍����i�s�N�Z���P�ʁj�i0 = �e�N�X�`���S�̂̍������g�p�j
//         ncols = �e�N�X�`�����̗񐔁i1����n�܂Łj�i0��1�Ɠ����j
//         *textureM = Texturemanager�I�u�W�F�N�g�ւ̃|�C���^
// ���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//=============================================================================
bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM)
{
    input = gamePtr->getInput();                // ���̓V�X�e��
    audio = gamePtr->getAudio();                // �I�[�f�B�I�V�X�e��
    return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// �G���e�B�e�B���A�N�e�B�u��
//=============================================================================
void Entity::activate()
{
    active = true;
}

//=============================================================================
// update
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//=============================================================================
void Entity::update(float frameTime)
{
    velocity += deltaV;
    deltaV.x = 0;
    deltaV.y = 0;
    Image::update(frameTime);
    rotatedBoxReady = false;    // rotateBox�̏Փ˔���̂���
}

//==========================================================
// �G���e�B�e�B���X�V 
// �A�j���[�V�����𖈎��ԍX�V�������Ȃ��ꍇ�͂��̃��\�b�h���g�p����B
// frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
//==========================================================
void Entity::updateWithoutImage(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	rotatedBoxReady = false;	// rotateBox�̏Փ˔���̂���
}

//==========================================================
// �A�j���[�V�����̂ݍX�V���郁�\�b�h
// �A�j���[�V�����𖈎��ԍX�V�������Ȃ��ꍇ�͂��̃��\�b�h���g�p����B
//==========================================================
void Entity::updateOnlyImage(float frameTime)
{
	Image::update(frameTime);
}

//=============================================================================
// AI�i�l�H�m�\�j
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// �l�H�m�\�v�Z�����s�Aent�͑��ݍ�p�̂��߂ɓn�����
//=============================================================================
void Entity::ai(float frameTime, Entity &ent)
{}

//=============================================================================
// ���̃G���e�B�e�B�Ƃ�������̃G���e�B�e�B�̏Փ˂𔻒�
// �e�G���e�B�e�B�͕K��1��ނ̏Փ˂��g�p���܂��B
// �Փ˂̎�ނ𕡐��K�v�Ƃ��镡�G�Ȑ}�`�́A
// �e������ʌ̃G���e�B�e�B�Ƃ��Ĉ������Ƃɂ�菈���ł��܂��B
// �ʏ�A�t���[�����Ƃ�1��Ăяo��
// �Փ˂̎�ށFCIRCLE�ABOX�AROTATED_BOX
//			   �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//=============================================================================
bool Entity::collidesWith(Entity &ent, VECTOR2 &collisionVector)
{ 
	// �ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�Փ˂͋N����Ȃ�
    if (!active || !ent.getActive())    
        return false;

	// �����̃G���e�B�e�B��CIRCLE�Փ˂ł���ꍇ
    if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
        return collideCircle(ent, collisionVector);
	// �����̃G���e�B�e�B��BOX�Փ˂ł���ꍇ
    if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
        return collideBox(ent, collisionVector);
	// ���̂��ׂĂ̑g�ݍ��킹���g�p���镪�����e�X�g
	// �ǂ���̃G���e�B�e�B��CIRCLE�Փ˂��g�p���Ȃ��ꍇ
    if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
        return collideRotatedBox(ent, collisionVector);
    else    // �ǂ��炩1�̃G���e�B�e�B���~�̏ꍇ
		// ���̃G���e�B�e�B��CIRCLE�Փ˂��g�p����ꍇ
        if (collisionType == entityNS::CIRCLE)
        {
            // Check for collision from other box with our circle
            bool collide = ent.collideRotatedBoxCircle(*this, collisionVector); 
            // Put the collision vector in the proper direction
            collisionVector *= -1;              // reverse collision vector
            return collide;
        }
        else    // ��������̃G���e�B�e�B��CIRCLE�Փ˂��g�p����ꍇ
            return collideRotatedBoxCircle(ent, collisionVector);
    return false;
}

//=============================================================================
// �~�̏Փ˔��胁�\�b�h
// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//=============================================================================
bool Entity::collideCircle(Entity &ent, VECTOR2 &collisionVector)
{
	// ���S�ƒ��S�̊Ԃ̍�
    distSquared = *getCenter() - *ent.getCenter();
    distSquared.x = distSquared.x * distSquared.x;      // ����2��
    distSquared.y = distSquared.y * distSquared.y;

	// ���a�̍��v���v�Z�i�g��k���̔{���𒲐��j
    sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
    sumRadiiSquared *= sumRadiiSquared;                 // 2�悷��

	// �G���e�B�e�B���Փ˂��Ă���ꍇ
    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
		// �Փ˃x�N�g����ݒ�
        collisionVector = *ent.getCenter() - *getCenter();
        return true;
    }
    return false;   // �Փ˂��Ă��Ȃ��ꍇ
}

//=============================================================================
// �����s���E�{�b�N�X�̏Փ˔��胁�\�b�h
// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//=============================================================================
bool Entity::collideBox(Entity &ent, VECTOR2 &collisionVector)
{
	// �ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�Փ˂͓{��Ȃ�
    if (!active || !ent.getActive())
        return false;

	// �����s���E�{�b�N�X���g���ďՓ˂��`�F�b�N
    if( (getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) && 
        (getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
        (getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) && 
        (getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()) )
    {
		// �Փ˃x�N�g����ݒ�
        collisionVector = *ent.getCenter() - *getCenter();
        return true;
    }
    return false;
}

//=============================================================================
// ��]����{�b�N�X�̏Փ˔��胁�\�b�h
// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
// �������e�X�g���g�p���ďՓ˂𔻒�
// �������e�X�g�F
// 2�̃{�b�N�X�́A����̒����ւ̓��e���d�Ȃ��Ă��Ȃ���ΏՓ˂��Ă��Ȃ�
//=============================================================================
bool Entity::collideRotatedBox(Entity &entB, VECTOR2 &collisionVector)
{
    float overlap01, overlap03;
    computeRotatedBox();                    // ��]����{�b�N�X������
    entB.computeRotatedBox();               // ��]����{�b�N�X������
    if (projectionsOverlap(entB, collisionVector) && entB.projectionsOverlap(*this, collisionVector))
    {
        // If we get to here the entities are colliding. The edge with the
        // smallest overlapping section is the edge where the collision is
        // occuring. The collision vector is created perpendicular to the
        // collision edge. The projection edges are 01 and 03.
        //
        //                    entA01min
        //                   /     entB01min
        //                  /     / entA01max 
        //                 /     / /  entB01max
        //                /     / /  /
        //            0--------------------1
        // entB03min..|          ____  
        // entA03min..|    _____|_ B | 
        //            |   | A   | |  |
        // entA03max..|   |_____|_|  |
        // entB03max..|         |____|
        //            | 
        //            |   
        //            3
        //            

        if (entA01min < entB01min)   // if A left of B
        {
            overlap01 = entA01max - entB01min;
            collisionVector = corners[1] - corners[0];
        }
        else    // else, A right of B
        {
            overlap01 = entB01max - entA01min;
            collisionVector = corners[0] - corners[1];
        }
        if (entA03min < entB03min)   // if A above B
        {
            overlap03 = entA03max - entB03min;
            if (overlap03 < overlap01)
                collisionVector = corners[3] - corners[0];
        }
        else    // else, A below B
        {
            overlap03 = entB03max - entA03min;
            if (overlap03 < overlap01)
                collisionVector = corners[0] - corners[3];
        }
        return true;
    }
    return false;
}

//=============================================================================
// ����̃{�b�N�X���A���̃G���e�B�e�B��edge01�����edge03�ɓ��e
// collideRotateBos()�ɂ���ČĂяo�����
// ���s��F���e���d�Ȃ��Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
//=============================================================================
bool Entity::projectionsOverlap(Entity &entB, VECTOR2 &collisionVector)
{
	float projection;

	// ����̃{�b�N�X��edge01�ɓ��e
	projection = graphics->Vector2Dot(&edge01, entB.getCorner(0));
	// ���_0�𓊉e
	entB01min = projection;
	entB01max = projection;
	// �c��̒��_���ꂼ�������
	for (int c = 1; c < 4; c++)
	{
		// ���_��edge01�ɓ��e
		projection = graphics->Vector2Dot(&edge01, entB.getCorner(c));
		if (projection < entB01min)
			entB01min = projection;
		else if (projection > entB01max)
			entB01max = projection;
	}
	// ���e���d�Ȃ�Ȃ��ꍇ
	if (entB01min > entA01max || entB01max < entA01min)
		return false;                       // �Փ˂̉\���Ȃ�
	// ����̃{�b�N�X��edge03�ɓ��e
	projection = graphics->Vector2Dot(&edge03, entB.getCorner(0));
	// ���_0�𓊉e
	entB03min = projection;
	entB03max = projection;
	// �c��̒��_���ꂼ�������
	for (int c = 1; c < 4; c++)
	{
		// ���_��edge03�ɓ��e
		projection = graphics->Vector2Dot(&edge03, entB.getCorner(c));
		if (projection < entB03min)
			entB03min = projection;
		else if (projection > entB03max)
			entB03max = projection;
	}
	// ���e���d�Ȃ�Ȃ��ꍇ
	if (entB03min > entA03max || entB03max < entA03min)
		return false;                       // �Փ˂̉\���Ȃ�
	return true;                            // ���e���d�Ȃ��Ă���ꍇ
}

//=============================================================================
// ��]����{�b�N�X�Ɖ~�̏Փ˔��胁�\�b�h
// collision()�ɂ���ČĂяo�����A�f�t�H���g�̏Փ˔��胁�\�b�h
// �{�b�N�X�̕ӂƉ~�̔��a�ŕ������e�X�g���g�p
// �~�̒��S���Փ˃{�b�N�X�̊e�ӂ�L�΂��������̊O��
// �i�{���m�C�̈�j�ɂ���ꍇ�A�{�b�N�X�̍ł��߂����_��
// �Փ˂��Ȃ����������̃`�F�b�N�Ŕ��肵�܂��B
// �ł��߂����_�́A�d�Ȃ�̃e�X�g���画�f�ł��܂��B
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//
//   Voronoi0 |   | Voronoi1
//         ---0---1---
//            |   |
//         ---3---2---
//   Voronoi3 |   | Voronoi2
//
// ���s�O�F���̃G���e�B�e�B�͕K���{�b�N�X�A����̃G���e�B�e�B�ient�j�͕K���~
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//=============================================================================
bool Entity::collideRotatedBoxCircle(Entity &entB, VECTOR2 &collisionVector)
{
    float center01, center03, overlap01, overlap03;

    computeRotatedBox();                    // ��]����{�b�N�X������

	// �~�̒��S��edge01�ɓ��e
    center01 = graphics->Vector2Dot(&edge01, entB.getCenter());
	// �ŏ��l�ƍő�l�͒��S����̔��a
    entB01min = center01 - entB.getRadius()*entB.getScale();
    entB01max = center01 + entB.getRadius()*entB.getScale();
    if (entB01min > entA01max || entB01max < entA01min) // ���e���d�Ȃ�Ȃ��ꍇ
        return false;                       // �Փ˂̉\���Ȃ�
        
	// �~�̒��S��edge03�ɓ��e
    center03 = graphics->Vector2Dot(&edge03, entB.getCenter());
	// �ŏ��l�ƍő�l�͒��S����̔��a
    entB03min = center03 - entB.getRadius()*entB.getScale();
    entB03max = center03 + entB.getRadius()*entB.getScale();
    if (entB03min > entA03max || entB03max < entA03min) // ���e���d�Ȃ�Ȃ��ꍇ
        return false;                       // �Փ˂̉\���Ȃ�

	// �~�̓��e���{�b�N�X�̓��e�ɏd�Ȃ�ꍇ
	// �~���Փ˃{�b�N�X�̃{���m�C�̈�ɂ��邩�ǂ������`�F�b�N

	// ���S��Voronoi0�ɂ���ꍇ
    if(center01 < entA01min && center03 < entA03min)
        return collideCornerCircle(corners[0], entB, collisionVector);
	// ���S��Voronoi1�ɂ���ꍇ
    if(center01 > entA01max && center03 < entA03min)
        return collideCornerCircle(corners[1], entB, collisionVector);
	// ���S��Voronoi2�ɂ���ꍇ
    if(center01 > entA01max && center03 > entA03max)
        return collideCornerCircle(corners[2], entB, collisionVector);
	// ���S��Voronoi3�ɂ���ꍇ
    if(center01 < entA01min && center03 > entA03max)
        return collideCornerCircle(corners[3], entB, collisionVector);

    // Circle not in voronoi region so it is colliding with edge of box.
    // The edge with the smallest overlapping section is the edge where the
    // collision is occuring. The collision vector is created perpendicular
    // to the collision edge. The projection edges are 01 and 03.
    //
    //                    entA01min
    //                   /   entB01min
    //                  /   /    entB01max 
    //                 /   /    /  entA01max
    //                /   /    /  /
    //            0--------------------1
    // entB03min..|        ___  
    // entA03min..|    ___/ B \__  
    // entB03max..|   |   \___/  |
    //            |   | A        |
    // entA03max..|   |__________|
    //            |         
    //            | 
    //            |   
    //            3
    //            
    if (entA01min < entB01min)   // if A left of B
    {
        overlap01 = entA01max - entB01min;
        collisionVector = corners[1] - corners[0];
    }
    else    // else, A right of B
    {
        overlap01 = entB01max - entA01min;
        collisionVector = corners[0] - corners[1];
    }
    if (entA03min < entB03min)   // if A above B
    {
        overlap03 = entA03max - entB03min;
        if (overlap03 < overlap01)
            collisionVector = corners[3] - corners[0];
    }
    else    // else, A below B
    {
        overlap03 = entB03max - entA03min;
        if (overlap03 < overlap01)
            collisionVector = corners[0] - corners[3];
    }
    return true;
}

//=============================================================================
// �{�b�N�X�̒��_���~�ƏՓ˂��Ă��Ȃ������A�����̃`�F�b�N���g�p���Ĕ���
// collideRotateBosCircle()�ɂ���ČĂяo�����
// ���s��F�Փ˂��Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false��߂�
// �Փ˂��Ă���ꍇ�́AcollisionVector��ݒ�
//=============================================================================
bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector)
{
    distSquared = corner - *ent.getCenter();            // ���_ - �~
    distSquared.x = distSquared.x * distSquared.x;      // ����2��
    distSquared.y = distSquared.y * distSquared.y;

    // ���a�̍��v���v�Z���Ă���A�����2��
	sumRadiiSquared = ent.getRadius()*ent.getScale();   // (0 + �~�̔��a)
    sumRadiiSquared *= sumRadiiSquared;                 // 2�悷��

	// ���_�Ɖ~���Փ˂��Ă���ꍇ
    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
		// �Փ˃x�N�g����ݒ�
        collisionVector = *ent.getCenter() - corner;
        return true;
    }
    return false;
}

//=============================================================================
// ��]����{�b�N�X�̒��_�A���e���A���e�̍ŏ��l�ƍő�l���v�Z
// 0---1  ���_�̔ԍ�
// |   |
// 3---2
//=============================================================================
void Entity::computeRotatedBox()
{
    if(rotatedBoxReady)
        return;
    float projection;

    VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
    VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));

    const VECTOR2 *center = getCenter();
    corners[0] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.top*getScale());
    corners[1] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.top*getScale());
    corners[2] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.bottom*getScale());
    corners[3] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.bottom*getScale());

    // corners[0]����_�Ƃ��Ďg�p
	// corners[0]�ɐڂ���2�ӂ𓊉e���Ƃ��Ďg�p
    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
    graphics->Vector2Normalize(&edge01);
    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
    graphics->Vector2Normalize(&edge03);

	// ���̃G���e�B�e�B�𓊉e����ɓ��e�����Ƃ��̍ŏ��l�ƍő�l
    projection = graphics->Vector2Dot(&edge01, &corners[0]);
    entA01min = projection;
    entA01max = projection;
	// edge01�ւ̓��e
    projection = graphics->Vector2Dot(&edge01, &corners[1]);
    if (projection < entA01min)
        entA01min = projection;
    else if (projection > entA01max)
        entA01max = projection;
	// edge03�ւ̓��e
    projection = graphics->Vector2Dot(&edge03, &corners[0]);
    entA03min = projection;
    entA03max = projection;
    projection = graphics->Vector2Dot(&edge03, &corners[3]);
    if (projection < entA03min)
        entA03min = projection;
    else if (projection > entA03max)
        entA03max = projection;

    rotatedBoxReady = true;
}

//=============================================================================
// ���̃G���e�B�e�B���w�肳�ꂽ��`�̊O���ɂ��邩
// ���s��F��`�̊O���ɂ���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
//=============================================================================
bool Entity::outsideRect(RECT rect)
{
    if( spriteData.x + spriteData.width*getScale() < rect.left || 
        spriteData.x > rect.right ||
        spriteData.y + spriteData.height*getScale() < rect.top || 
        spriteData.y > rect.bottom)
        return true;
    return false;
}

//=============================================================================
// damage
// ���̃G���e�B�e�B���A����ɂ���ă_���[�W���󂯂�
// �p�����鑤�̃N���X�ł��̊֐����I�[�o�[���C�h
//=============================================================================
void Entity::damage(int weapon)
{}

//=============================================================================
// ���̃G���e�B�e�B�Ƃ̏Փˌ�̒��˕Ԃ�
//=============================================================================
void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
{
    float cUVdotVdiff;
    VECTOR2 Vdiff = ent.getVelocity() - velocity;
    VECTOR2 cUV = collisionVector;              // �Փ˒P�ʃx�N�g��
    Graphics::Vector2Normalize(&cUV);
    if(collisionType == entityNS::ROTATED_BOX)  // if ROTATED_BOX collision
        // The collision vector is perpendicular to the edge. 
        cUVdotVdiff = 1.0f;                 // do not change velocity
    else
        cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);   // use velocity difference
    float massRatio = 2.0f;
    if (getMass() != 0)
        massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
    if(massRatio < 0.1f)
        massRatio = 0.1f;

	// �G���e�B�e�B��collisionVector�ɉ����ė��������Ɉړ�
    VECTOR2 cv;
    int count=10;   // loop limit
    do
    {
        setX(getX() - cUV.x);
        setY(getY() - cUV.y);
        rotatedBoxReady = false;
        count--;
    } while( this->collidesWith(ent, cv) && count);

    // bounce
    deltaV += ((massRatio * cUVdotVdiff) * cUV);
}

//=============================================================================
// ����̃G���e�B�e�B���炱�̃G���e�B�e�B�ւ̏d��
// �d�͂����̃G���e�B�e�B�̑��x�x�N�g���ɉ��Z
// force = GRAVITY * m1 * m2 / r*r
//                    2              2
//  r*r  =   (Ax - Bx)   +  (Ay - By)
//=============================================================================
void Entity::gravityForce(Entity *ent, float frameTime)
{
	// �ǂ��炩�̃G���e�B�e�B���A�N�e�B�u�łȂ��ꍇ�A�d�͂̉e���͂Ȃ�
    if (!active || !ent->getActive())
        return ;

    rr = pow((ent->getCenterX() - getCenterX()),2) + 
            pow((ent->getCenterY() - getCenterY()),2);
    force = gravity * ent->getMass() * mass/rr;

    // --- �x�N�g���v�Z���g���ďd�̓x�N�g�����쐬 ---
    // �G���e�B�e�B�Ԃ̃x�N�g�����쐬
    VECTOR2 gravityV(ent->getCenterX() - getCenterX(),
                        ent->getCenterY() - getCenterY());
    // �x�N�g���𐳋K��
    Graphics::Vector2Normalize(&gravityV);
	// �d�͂ŏ�Z���āA�d�̓x�N�g�����쐬
    gravityV *= force * frameTime;
	// �d�̓x�N�g�����A�ړ����̑��x�x�N�g���ɉ��Z���āA������ς���
    velocity += gravityV;
}

//==========================================================
// �^�C����ł̈ʒu������������֐�
//==========================================================
void Entity::initTileXY()
{
	tileX = (int)spriteData.x / 32;
	tileY = (int)spriteData.y / 32;
}