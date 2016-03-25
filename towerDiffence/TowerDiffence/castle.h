#ifndef _CASTLE_H		// このファイルが複数の箇所でインクルードされる場合に、
#define _CASTLE_H		// 多重に定義されることを防ぎます。

#include "entity.h"
#include "constants.h"

namespace castleNS
{
	const int WIDTH = 96;			// 画像の幅（各フレーム）
	const int HEIGHT = 96;			// 画像の高さ
	const int X = 18.3 * 30;	// 初期位置
	const int Y = 9.5 * 30;
	const int COLLISION_RADIUS = 10;// 円の衝突判定	
	const int START_FRAME = 0;
}

class Castle : public Entity		// Entityクラスを継承
{
public:
	// コンストラクタ
	Castle();

	// 継承されたメンバー関数
	void update(float frameTime);
};

#endif // !_CASTLE_H
