#pragma once
#include "enemy.h"

// ��ģ�� ���ڴ�� �����δ�
// �׸��� ������Ʈ�� ƨ��

class dip :
	public enemy
{
public:
	dip() {};
	~dip() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

