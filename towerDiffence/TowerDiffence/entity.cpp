//==========================================================
/// @file
/// @brief    entity.hの実装
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#include "entity.h"

//=============================================================================
// コンストラクタ
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
    active = true;                  // エンティティはアクティブ
    rotatedBoxReady = false;
    collisionType = entityNS::CIRCLE;
    health = 100;
    gravity = entityNS::GRAVITY;
	isDamaged = false;
	drawFlag = true;
	damagePer = 1.0f;
}

//==========================================================
// パラメータ初期化
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
// Entityを初期化
// 実行前：*gamePtr = Gameオブジェクトへのポインタ
//		   width = Imageの幅（ピクセル単位）（0 = テクスチャ全体の幅を使用）
//		   height = Imageの高さ（ピクセル単位）（0 = テクスチャ全体の高さを使用）
//         ncols = テクスチャ内の列数（1からnまで）（0は1と同じ）
//         *textureM = Texturemanagerオブジェクトへのポインタ
// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
//=============================================================================
bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM)
{
    input = gamePtr->getInput();                // 入力システム
    audio = gamePtr->getAudio();                // オーディオシステム
    return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// エンティティをアクティブ化
//=============================================================================
void Entity::activate()
{
    active = true;
}

//=============================================================================
// update
// 通常、フレームごとに1回呼び出す
// frameTimeは、移動とアニメーションの速さを制御するために使用
//=============================================================================
void Entity::update(float frameTime)
{
    velocity += deltaV;
    deltaV.x = 0;
    deltaV.y = 0;
    Image::update(frameTime);
    rotatedBoxReady = false;    // rotateBoxの衝突判定のため
}

//==========================================================
// エンティティを更新 
// アニメーションを毎時間更新したくない場合はこのメソッドを使用する。
// frameTimeは、移動とアニメーションの速さを制御するために使用
//==========================================================
void Entity::updateWithoutImage(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	rotatedBoxReady = false;	// rotateBoxの衝突判定のため
}

//==========================================================
// アニメーションのみ更新するメソッド
// アニメーションを毎時間更新したくない場合はこのメソッドを使用する。
//==========================================================
void Entity::updateOnlyImage(float frameTime)
{
	Image::update(frameTime);
}

//=============================================================================
// AI（人工知能）
// 通常、フレームごとに1回呼び出す
// 人工知能計算を実行、entは相互作用のために渡される
//=============================================================================
void Entity::ai(float frameTime, Entity &ent)
{}

//=============================================================================
// このエンティティともう一方のエンティティの衝突を判定
// 各エンティティは必ず1種類の衝突を使用します。
// 衝突の種類を複数必要とする複雑な図形は、
// 各部分を別個のエンティティとして扱うことにより処理できます。
// 通常、フレームごとに1回呼び出す
// 衝突の種類：CIRCLE、BOX、ROTATED_BOX
//			   衝突している場合は、collisionVectorを設定
//=============================================================================
bool Entity::collidesWith(Entity &ent, VECTOR2 &collisionVector)
{ 
	// どちらかのエンティティがアクティブでない場合、衝突は起こらない
    if (!active || !ent.getActive())    
        return false;

	// 両方のエンティティがCIRCLE衝突である場合
    if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
        return collideCircle(ent, collisionVector);
	// 両方のエンティティがBOX衝突である場合
    if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
        return collideBox(ent, collisionVector);
	// 他のすべての組み合わせが使用する分離軸テスト
	// どちらのエンティティもCIRCLE衝突を使用しない場合
    if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
        return collideRotatedBox(ent, collisionVector);
    else    // どちらか1つのエンティティが円の場合
		// このエンティティがCIRCLE衝突を使用する場合
        if (collisionType == entityNS::CIRCLE)
        {
            // Check for collision from other box with our circle
            bool collide = ent.collideRotatedBoxCircle(*this, collisionVector); 
            // Put the collision vector in the proper direction
            collisionVector *= -1;              // reverse collision vector
            return collide;
        }
        else    // もう一方のエンティティがCIRCLE衝突を使用する場合
            return collideRotatedBoxCircle(ent, collisionVector);
    return false;
}

//=============================================================================
// 円の衝突判定メソッド
// collision()によって呼び出される、デフォルトの衝突判定メソッド
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
//=============================================================================
bool Entity::collideCircle(Entity &ent, VECTOR2 &collisionVector)
{
	// 中心と中心の間の差
    distSquared = *getCenter() - *ent.getCenter();
    distSquared.x = distSquared.x * distSquared.x;      // 差を2乗
    distSquared.y = distSquared.y * distSquared.y;

	// 半径の合計を計算（拡大縮小の倍率を調整）
    sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
    sumRadiiSquared *= sumRadiiSquared;                 // 2乗する

	// エンティティが衝突している場合
    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
		// 衝突ベクトルを設定
        collisionVector = *ent.getCenter() - *getCenter();
        return true;
    }
    return false;   // 衝突していない場合
}

//=============================================================================
// 軸平行境界ボックスの衝突判定メソッド
// collision()によって呼び出される、デフォルトの衝突判定メソッド
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
//=============================================================================
bool Entity::collideBox(Entity &ent, VECTOR2 &collisionVector)
{
	// どちらかのエンティティがアクティブでない場合、衝突は怒らない
    if (!active || !ent.getActive())
        return false;

	// 軸平行境界ボックスを使って衝突をチェック
    if( (getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) && 
        (getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
        (getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) && 
        (getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()) )
    {
		// 衝突ベクトルを設定
        collisionVector = *ent.getCenter() - *getCenter();
        return true;
    }
    return false;
}

//=============================================================================
// 回転するボックスの衝突判定メソッド
// collision()によって呼び出される、デフォルトの衝突判定メソッド
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
// 分離軸テストを使用して衝突を判定
// 分離軸テスト：
// 2つのボックスは、特定の直線への投影が重なっていなければ衝突していない
//=============================================================================
bool Entity::collideRotatedBox(Entity &entB, VECTOR2 &collisionVector)
{
    float overlap01, overlap03;
    computeRotatedBox();                    // 回転するボックスを準備
    entB.computeRotatedBox();               // 回転するボックスを準備
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
// 相手のボックスを、このエンティティのedge01およびedge03に投影
// collideRotateBos()によって呼び出される
// 実行後：投影が重なっている場合はtrue、それ以外の場合はfalseを戻す
//=============================================================================
bool Entity::projectionsOverlap(Entity &entB, VECTOR2 &collisionVector)
{
	float projection;

	// 相手のボックスをedge01に投影
	projection = graphics->Vector2Dot(&edge01, entB.getCorner(0));
	// 頂点0を投影
	entB01min = projection;
	entB01max = projection;
	// 残りの頂点それぞれを処理
	for (int c = 1; c < 4; c++)
	{
		// 頂点をedge01に投影
		projection = graphics->Vector2Dot(&edge01, entB.getCorner(c));
		if (projection < entB01min)
			entB01min = projection;
		else if (projection > entB01max)
			entB01max = projection;
	}
	// 投影が重ならない場合
	if (entB01min > entA01max || entB01max < entA01min)
		return false;                       // 衝突の可能性なし
	// 相手のボックスをedge03に投影
	projection = graphics->Vector2Dot(&edge03, entB.getCorner(0));
	// 頂点0を投影
	entB03min = projection;
	entB03max = projection;
	// 残りの頂点それぞれを処理
	for (int c = 1; c < 4; c++)
	{
		// 頂点をedge03に投影
		projection = graphics->Vector2Dot(&edge03, entB.getCorner(c));
		if (projection < entB03min)
			entB03min = projection;
		else if (projection > entB03max)
			entB03max = projection;
	}
	// 投影が重ならない場合
	if (entB03min > entA03max || entB03max < entA03min)
		return false;                       // 衝突の可能性なし
	return true;                            // 投影が重なっている場合
}

//=============================================================================
// 回転するボックスと円の衝突判定メソッド
// collision()によって呼び出される、デフォルトの衝突判定メソッド
// ボックスの辺と円の半径で分離軸テストを使用
// 円の中心が衝突ボックスの各辺を伸ばした直線の外側
// （ボロノイ領域）にある場合、ボックスの最も近い頂点と
// 衝突がないかを距離のチェックで判定します。
// 最も近い頂点は、重なりのテストから判断できます。
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
//
//   Voronoi0 |   | Voronoi1
//         ---0---1---
//            |   |
//         ---3---2---
//   Voronoi3 |   | Voronoi2
//
// 実行前：このエンティティは必ずボックス、相手のエンティティ（ent）は必ず円
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
//=============================================================================
bool Entity::collideRotatedBoxCircle(Entity &entB, VECTOR2 &collisionVector)
{
    float center01, center03, overlap01, overlap03;

    computeRotatedBox();                    // 回転するボックスを準備

	// 円の中心をedge01に投影
    center01 = graphics->Vector2Dot(&edge01, entB.getCenter());
	// 最小値と最大値は中心からの半径
    entB01min = center01 - entB.getRadius()*entB.getScale();
    entB01max = center01 + entB.getRadius()*entB.getScale();
    if (entB01min > entA01max || entB01max < entA01min) // 投影が重ならない場合
        return false;                       // 衝突の可能性なし
        
	// 円の中心をedge03に投影
    center03 = graphics->Vector2Dot(&edge03, entB.getCenter());
	// 最小値と最大値は中心からの半径
    entB03min = center03 - entB.getRadius()*entB.getScale();
    entB03max = center03 + entB.getRadius()*entB.getScale();
    if (entB03min > entA03max || entB03max < entA03min) // 投影が重ならない場合
        return false;                       // 衝突の可能性なし

	// 円の投影がボックスの投影に重なる場合
	// 円が衝突ボックスのボロノイ領域にあるかどうかをチェック

	// 中心がVoronoi0にある場合
    if(center01 < entA01min && center03 < entA03min)
        return collideCornerCircle(corners[0], entB, collisionVector);
	// 中心がVoronoi1にある場合
    if(center01 > entA01max && center03 < entA03min)
        return collideCornerCircle(corners[1], entB, collisionVector);
	// 中心がVoronoi2にある場合
    if(center01 > entA01max && center03 > entA03max)
        return collideCornerCircle(corners[2], entB, collisionVector);
	// 中心がVoronoi3にある場合
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
// ボックスの頂点が円と衝突していないかを、距離のチェックを使用して判定
// collideRotateBosCircle()によって呼び出される
// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
// 衝突している場合は、collisionVectorを設定
//=============================================================================
bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector)
{
    distSquared = corner - *ent.getCenter();            // 頂点 - 円
    distSquared.x = distSquared.x * distSquared.x;      // 差を2乗
    distSquared.y = distSquared.y * distSquared.y;

    // 半径の合計を計算してから、それを2乗
	sumRadiiSquared = ent.getRadius()*ent.getScale();   // (0 + 円の半径)
    sumRadiiSquared *= sumRadiiSquared;                 // 2乗する

	// 頂点と円が衝突している場合
    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
		// 衝突ベクトルを設定
        collisionVector = *ent.getCenter() - corner;
        return true;
    }
    return false;
}

//=============================================================================
// 回転するボックスの頂点、投影線、投影の最小値と最大値を計算
// 0---1  頂点の番号
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

    // corners[0]を基点として使用
	// corners[0]に接する2辺を投影線として使用
    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
    graphics->Vector2Normalize(&edge01);
    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
    graphics->Vector2Normalize(&edge03);

	// このエンティティを投影線上に投影したときの最小値と最大値
    projection = graphics->Vector2Dot(&edge01, &corners[0]);
    entA01min = projection;
    entA01max = projection;
	// edge01への投影
    projection = graphics->Vector2Dot(&edge01, &corners[1]);
    if (projection < entA01min)
        entA01min = projection;
    else if (projection > entA01max)
        entA01max = projection;
	// edge03への投影
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
// このエンティティが指定された矩形の外側にあるか
// 実行後：矩形の外側にある場合はtrue、それ以外の場合はfalseを戻す
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
// このエンティティが、武器によってダメージを受ける
// 継承する側のクラスでこの関数をオーバーライド
//=============================================================================
void Entity::damage(int weapon)
{}

//=============================================================================
// 他のエンティティとの衝突後の跳ね返り
//=============================================================================
void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
{
    float cUVdotVdiff;
    VECTOR2 Vdiff = ent.getVelocity() - velocity;
    VECTOR2 cUV = collisionVector;              // 衝突単位ベクトル
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

	// エンティティをcollisionVectorに沿って離れる方向に移動
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
// 相手のエンティティからこのエンティティへの重力
// 重力をこのエンティティの速度ベクトルに加算
// force = GRAVITY * m1 * m2 / r*r
//                    2              2
//  r*r  =   (Ax - Bx)   +  (Ay - By)
//=============================================================================
void Entity::gravityForce(Entity *ent, float frameTime)
{
	// どちらかのエンティティがアクティブでない場合、重力の影響はない
    if (!active || !ent->getActive())
        return ;

    rr = pow((ent->getCenterX() - getCenterX()),2) + 
            pow((ent->getCenterY() - getCenterY()),2);
    force = gravity * ent->getMass() * mass/rr;

    // --- ベクトル計算を使って重力ベクトルを作成 ---
    // エンティティ間のベクトルを作成
    VECTOR2 gravityV(ent->getCenterX() - getCenterX(),
                        ent->getCenterY() - getCenterY());
    // ベクトルを正規化
    Graphics::Vector2Normalize(&gravityV);
	// 重力で乗算して、重力ベクトルを作成
    gravityV *= force * frameTime;
	// 重力ベクトルを、移動中の速度ベクトルに加算して、方向を変える
    velocity += gravityV;
}

//==========================================================
// タイル上での位置を初期化する関数
//==========================================================
void Entity::initTileXY()
{
	tileX = (int)spriteData.x / 32;
	tileY = (int)spriteData.y / 32;
}