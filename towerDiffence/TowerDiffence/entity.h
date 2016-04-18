//==========================================================
/// @file
/// @brief    Entityクラス
/// @author   阿部拳之
///
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください

#ifndef _ENTITY_H               // このファイルが複数の箇所でインクルードされる場合に、 
#define _ENTITY_H               // 多重に定義されることを防ぎます。
#define WIN32_LEAN_AND_MEAN

class Entity;

#include "image.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
	enum COLLISION_TYPE { NONE, CIRCLE, BOX, ROTATED_BOX };
	const float GRAVITY = 6.67428e-11f;         // 重力定数
}

class Entity : public Image
{
	// Entityプロパティ
protected:
	entityNS::COLLISION_TYPE collisionType;
	VECTOR2 center;				// エンティティの中心
	float   radius;				// 円の衝突判定の大きさ
	VECTOR2 distSquared;		// 円の衝突判定の計算に使用
	float   sumRadiiSquared;
	RECT    edge;				// BOXとROTATED_BOXの衝突判定用のボックス
	VECTOR2 corners[4];			// ROTATED_BOXの衝突判定用
	VECTOR2 edge01, edge03;		// 投影用のエッジ
	// このエンティティのボックスをedge01とedge03に投影した場合の最大と最小の投影
	float   entA01min, entA01max, entA03min, entA03max;
	// 相手のボックスをedge01とedge03に投影した場合の最大と最小の投影
	float   entB01min, entB01max, entB03min, entB03max;
	VECTOR2 velocity;			// 速度
	VECTOR2 deltaV;				// 次にupdate()が呼び出されたときの加速度
	float   mass;				// エンティティの質量
	float   health;				// 体力（0~100）
	float   rr;					// このエンティティと相手のエンティティまでの距離
	float   force;				// エンティティに働く力
	float   gravity;			// ゲーム世界での重力定数
	Input   *input;				// 入力システムへのポインタ
	Audio   *audio;				// オーディオシステムへのポインタ
	HRESULT hr;					// 標準の戻り値
	bool    active;				// trueのときのみエンティティの衝突判定が有効
	bool    rotatedBoxReady;    // 回転した衝突判定用のボックスが準備できた場合、true
	int tileX, tileY;			// 自分が存在するタイルの位置
	bool isDamaged;				// ダメージを受けている状態かどうか
	bool drawFlag;				// 描画フラグ、true時に描画
	float damagePer;            // ダメージを受ける時に掛ける割合
	float damageTimer;					// ダメージ時のアニメーション用のタイマー
	float totalDamageTime;				// ダメージ時のアニメーション用のタイマー

	// 円の衝突判定メソッド
	// collision()によって呼び出される、デフォルトの衝突判定メソッド
	// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
	// 衝突している場合は、collisionVectorを設定
	virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
	// 軸平行境界ボックスの衝突判定メソッド
	// collision()によって呼び出される、デフォルトの衝突判定メソッド
	// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
	// 衝突している場合は、collisionVectorを設定
	virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
	// 回転するボックスの衝突判定メソッド
	// collision()によって呼び出される、デフォルトの衝突判定メソッド
	// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
	// 衝突している場合は、collisionVectorを設定
	// 分離軸テストを使用して衝突を判定
	// 分離軸テスト：
	// 2つのボックスは、特定の直線への投影が重なっていなければ衝突していない
	virtual bool collideRotatedBox(Entity &ent, VECTOR2 &collisionVector);
	// 回転するボックスと円の衝突判定メソッド
	// collision()によって呼び出される、デフォルトの衝突判定メソッド
	// ボックスの辺と円の半径で分離軸テストを使用
	// 円の中心が衝突ボックスの各辺を伸ばした直線の外側
	// （ボロノイ領域）にある場合、ボックスの最も近い頂点と
	// 衝突がないかを距離のチェックで判定します。
	// 最も近い頂点は、重なりのテストから判断できます。
	// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
	// 衝突している場合は、collisionVectorを設定
	virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
	// 回転するボックスの頂点、投影線、投影の最小値と最大値を計算
	void computeRotatedBox();
	// 相手のボックスを、このエンティティのedge01およびedge03に投影
	// collideRotateBos()によって呼び出される
	// 実行後：投影が重なっている場合はtrue、それ以外の場合はfalseを戻す
	bool projectionsOverlap(Entity &ent, VECTOR2 &collisionVector);
	// ボックスの頂点が円と衝突していないかを、距離のチェックを使用して判定
	// collideRotateBosCircle()によって呼び出される
	// 実行後：衝突している場合はtrue、していない場合はfalseを戻す
	// 衝突している場合は、collisionVectorを設定
	bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);
public:
	// コンストラクタ
	Entity();
	// デストラクタ
	virtual ~Entity() {}

	////////////////////////////////////////
	//           getter                   //
	////////////////////////////////////////

	// 画面上でのエンティティの中心の座標を戻す
	virtual const VECTOR2* getCenter()
	{
		center = VECTOR2(getCenterX(), getCenterY());
		return &center;
	}

	// 円の衝突判定の大きさを戻す
	virtual float getRadius() const { return radius; }

	// BOXとROTATED_BOXの衝突判定用のボックスを戻す
	virtual const RECT& getEdge() const { return edge; }
	
	// ROTATED_BOXの衝突判定用のボックスの頂点の座標を戻す
	virtual const VECTOR2* getCorner(UINT c) const
	{
		if (c >= 4)
			c = 0;
		return &corners[c];
	}

	// 速度ベクトルを戻す
	virtual const VECTOR2 getVelocity() const { return velocity; }

	// エンティティがアクティブかどうかを戻す
	virtual bool  getActive()         const { return active; }

	// 質量を戻す
	virtual float getMass()           const { return mass; }

	// 重力定数を戻す
	virtual float getGravity()        const { return gravity; }

	// 体力を戻す
	virtual float getHealth()         const { return health; }

	// 衝突判定の種類を戻す(NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual entityNS::COLLISION_TYPE getCollisionType() { return collisionType; }
	
	// 自分が存在するタイルのX位置を戻す
	int getTileX() { return tileX; }
	
	// 自分が存在するタイルのY位置を戻す
	int getTileY() { return tileY; }
	
	////////////////////////////////////////
	//           setter                   //
	////////////////////////////////////////

	// 速度をセット
	virtual void  setVelocity(VECTOR2 v) { velocity = v; }

	// 次の更新での加速度をセット
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }

	// エンティティがアクティブかどうかをセット
	virtual void  setActive(bool a) { active = a; }

	// 体力をセット
	virtual void setHealth(float h) { health = h; }

	// 質量をセット
	virtual void  setMass(float m) { mass = m; }

	// 重力定数をセット。デフォルトは6.67428e-11
	virtual void  setGravity(float g) { gravity = g; }

	// 円の衝突判定用の半径をセット
	virtual void setCollisionRadius(float r) { radius = r; }

	// 衝突判定の種類をセット(NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
	{
		collisionType = ctype;
	}


	// BOXとROTATED_BOXの衝突判定用のボックスをセット
	virtual void setEdge(RECT e) { edge = e; }

	// 回転した衝突判定用のボックスが準備できているかをセット
	virtual void setRotatedBoxReady(bool r) { rotatedBoxReady = r; }

	// タイル上での位置をセットする関数
	void setTileX(int x) { tileX = x; }

	// タイル上での位置をセットする関数
	void setTileY(int y) { tileY = y; }

	// ダメージを受けるときに掛ける割合をセット
	void setDamagePer(float per) { damagePer = per; }

	////////////////////////////////////////
	//         その他の関数               //
	////////////////////////////////////////

	// update
	// 通常、フレームごとに1回呼び出す
	// frameTimeは、移動とアニメーションの速さを制御するために使用
	virtual void update(float frameTime);

	// 描画関数、描画フラグがオンのときのみ描画をする
	virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);

	// エンティティを更新
	// アニメーションを毎時間更新したくない場合はこのメソッドを使用する。
	virtual void updateWithoutImage(float frameTime);

	// アニメーションのみ更新するメソッド
	// アニメーションを毎時間更新したくない場合はこのメソッドを使用する。
	virtual void updateOnlyImage(float frameTime);

	// パラメータリセット
	virtual void reset();

	// Entityを初期化
	// 実行前：*gamePtr = Gameオブジェクトへのポインタ
	//		   width = Imageの幅（ピクセル単位）（0 = テクスチャ全体の幅を使用）
	//		   height = Imageの高さ（ピクセル単位）（0 = テクスチャ全体の高さを使用）
	//         ncols = テクスチャ内の列数（1からnまで）（0は1と同じ）
	//         *textureM = Texturemanagerオブジェクトへのポインタ
	// 実行後：成功した場合はtrue、失敗した場合はfalseを戻す
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);

	// エンティティをアクティブ化
	virtual void activate();

	// AI（人工知能）
	// 通常、フレームごとに1回呼び出す
	// 人工知能計算を実行、entは相互作用のために渡される
	virtual void ai(float frameTime, Entity &ent);

	// このエンティティが指定された矩形の外側にあるか
	virtual bool outsideRect(RECT rect);

	// このエンティティともう一方のエンティティが衝突しているか
	virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	// damage
	// このエンティティが、武器によってダメージを受ける
	// 継承する側のクラスでこの関数をオーバーライド
	virtual void damage(int weapon);

	// 他のエンティティとの衝突後の跳ね返り
	void bounce(VECTOR2 &collisionVector, Entity &ent);

	// 相手のエンティティからこのエンティティへの重力
	// 重力をこのエンティティの速度ベクトルに加算
	void gravityForce(Entity *other, float frameTime);

	// タイル上での位置を初期化する関数
	void initTileXY();
};

#endif
