#pragma once
#include "gameNode.h"
#include "isaac.h"
#include "gameUI.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "grid.h"

class nomalStage : public gameNode
{


private:
	bool _settingFlag;
	// �Ʊ� ����
	vector<tagTear>					*_vTear;
	vector<tagTear>::iterator		_viTear;
	// ���� ����
	vector<tagTear>* _vETear;
	vector<tagTear>::iterator		_viETear;
	// ��ź
	vector<pickUpItem*>*             _vBomb;
	vector<pickUpItem*>::iterator   _viBomb;
	// Ŭ���� �޴���?
	bool							_isClear;
	int								_fadeCount;
	int								_middleValX;
	int								_middleValY;
	int _doorCount;
	// ������!	
	isaac*							_isaac;
	//������ �Ŵ���!
	itemManager*					_itemManager;
	//���ʹ� �Ŵ���
	enemyManager*					_enemyManager;
	// ���� UI	
	gameUI*							_gameUI;
	// �̹���	
	image*							_bgBlack;
	// �׸���
	grid*							_grid;
	//
	vector<enemy*>* _vEnemy;
	vector<enemy*>::iterator _viEnemy;

	tagTILE* _wall;
	tagTILE* _door;
	tagTILE* _tgrid;
	RECT _temp;

	float _targetX;
	float _targetY;
	float _increaseX;
	float _increaseY;

public:
	nomalStage();
	~nomalStage();

	virtual HRESULT init();
	virtual HRESULT init( isaac* _isaac, float ix, float iy, float tx, float ty);
	virtual void release();
	virtual void update();
	virtual void render();

	void wallCollision();
	void gridCollision();
	void doorCollision();
	void tearWallCollision();
	void isaacEnemyCollision();
	void EnemyTearCollision();
	void bombCollision();
	void EnemyDead();
	void stageClear();
	void moveCameraSetting(float increaseX, float increaseY, float targetX, float targetY);
	void doorMove();
	void moveCamera();
};

