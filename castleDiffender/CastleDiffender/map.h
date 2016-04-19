//==========================================================
/// @file
/// @brief    Map�N���X
/// @author   �������V
///
/// @attention  ���̃t�@�C���̗��p�́A������README�ɂ���
///             ���p�����ɏ]���Ă�������

#ifndef _MAP_H		// ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA
#define _MAP_H		// ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <iostream>
#include <string>
#include <sstream> //�����X�g���[��
#include "gameError.h"

using namespace std;

// Map�N���X�̒萔
// �Q�[�����ł̃X�e�[�^�X�ȊO�������ɋL�q
namespace mapNS
{
	const int TEXTURE_SIZE = 32;  // �摜�T�C�Y�i1�^�C�����j
	const int TEXTURE_COLS = 16;  // �s��
	const int MAP_HEIGHT = 23;    // �}�b�v�̍���
	const int MAP_WIDTH = 40;     // �}�b�v�̕�
	const int BARRICADE_NUM = 8;  // �����o���P�[�h�̐�
}

class Map : public Entity
{
private:
	// �}�b�v
	int mMapData[mapNS::MAP_HEIGHT][mapNS::MAP_WIDTH];
	// �����蔻��̃f�[�^�A�Q�[����ʂ��Ĉړ��ł��Ȃ��ӏ���1��2�ɐݒ肷��A���1�ɁA���2�ɂ���
	int mColData[mapNS::MAP_HEIGHT][mapNS::MAP_WIDTH];
	int mColDataInit[mapNS::MAP_HEIGHT][mapNS::MAP_WIDTH];
	// �}�b�v��̃I�u�W�F�N�g�f�[�^�A0 -> �o���P�[�h
	int mObjData[mapNS::MAP_HEIGHT][mapNS::MAP_WIDTH];
public:
	// �R���X�g���N�^
	Map();

	// �p�����ꂽ�����o�֐�
	virtual void draw();
	virtual void update(float frameTime);

	// �V�����ǉ����郁���o�֐�
	// �}�b�v�f�[�^�̎擾�@�����͎擾���������W�̃C���f�b�N�X
	int getMapData(int x, int y)
	{
		return mMapData[x][y];
	}

	// �}�b�v�����蔻��̍X�V �������͎擾���������W�̃C���f�b�N�X
	int getMapCol(int x, int y)
	{
		return mColData[x][y];
	}

	// �}�b�v��̃I�u�W�F�N�g�f�[�^�X�V�@�����͎擾���������W�̃C���f�b�N�X
	int getMapObj(int x, int y)
	{
		return mObjData[x][y];
	}


	// �}�b�v�f�[�^�̍X�V�@�����͍X�V���������W�l�ƍX�V����l
	void updateMapData(float x, float y, int val);
	// �}�b�v�����蔻��̍X�V �����͍X�V���������W�l�ƍX�V����l
	// val -> 0 : ����Ȃ��@val -> 1 : ���肠��
	void updateMapCol(float x, float y, int val);
	// �}�b�v��̃I�u�W�F�N�g�f�[�^�X�V�@�����͍X�V���������W�l�ƍX�V����l
	void updateMapObj(float x, float y, int val);
	// �}�b�v��̃I�u�W�F�N�g�f�[�^�X�V�@�����͍X�V���������W�l�ƍX�V����l
	void updateMapObjInt(int y, int x, int val);
	// �}�b�v��̓����蔻��f�[�^���ׂĂ����Z�b�g����֐�
	void resetMapCol() {
		for (int i = 0; i < mapNS::MAP_HEIGHT; ++i)
		{
			for (int j = 0; j < mapNS::MAP_WIDTH; ++j)
			{
				mColData[i][j] = mColDataInit[i][j];
			}
		}
	}
	// �w�肳�ꂽ�}�b�v�̓����蔻��f�[�^�����Z�b�g����
	void resetMapCol(int y, int x) {
		if (x < 0 || x >= mapNS::MAP_WIDTH || y < 0 || y >= mapNS::MAP_HEIGHT) { return; }
		mColData[y][x] = mColDataInit[y][x];
	}

	// �w�肳�ꂽ�X�e�[�W�̃}�b�v�f�[�^��ǂݍ���
	void readMapFile(int stageNum);
};

#endif