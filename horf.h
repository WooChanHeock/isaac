#pragma once
#include "enemy.h"

// �� ģ���� ��������
// Ž�� �����ȿ� �������� ��� �ý� ������ ����

class horf :
	public enemy
{
public:
	horf() {}
	~horf() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

