#pragma once
#include "gameNode.h"
#include "isaac.h"

class gameUI :
	public gameNode
{
private:
	// �����ۿ� ���� ���� ����
	isaac* _isaac;
	// ��Ʈ UI �̹���
	image* _heartUI;
	//  ���� �� UI �̹���
	image* _chargebarUI;
	// �Ⱦ� �������� ������
	image* _pickUpItemIcon;
	// stat ������
	image* _statIcon;
	// ���� 
	image* _number;
	// ��
	image* _dot;
	// ������ �׸�
	image* _chargeGreen;

	image* _deathUI;

	int  _deathCount;

	// ü�¹� �̹���
	image* _progressBarTop;
	image* _progressBarBottom;

public:
	gameUI();
	~gameUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// �����ۿ� ���� �����͸� �̾ƿ�
	void updateIsaac(isaac* iac) { _isaac = iac; }
	// ��Ʈ UI �׷��ֱ�
	void heartRender();
	// ������ UI �׷��ֱ�
	void chargedbarRender();
	// �Ⱦ������� UI �׷��ֱ�
	void pickUpItemRender();
	// ���� UI �׷��ֱ�
	void statRender();
	void spaceItemRender();
	void deathUIRender();
	void bossHeath();
};

