#pragma once
#include "gameNode.h"

class mainMenu :
    public gameNode
{
private:
	// ���̵��� �ƿ�
	BYTE _fadeCount;
	bool _isFade;
	// �� �޴� ���
	int _selectNum;
	// Ű���� �ν� ����
	int _term;
	
	// �ε� ī��Ʈ
	int _loadingCount;
	
	// �̹��� ���� ������
	image* _mainMenu;		// ���θ޴� �̹���
	image* _menuWord;		// �޴� ���� �̹���
	image* _bgBlack;		// ���̵� �� �ƿ� ó���� �̹���
	image* _menuSelector;	// �޴� ��Ͽ��� ���õǾ����� Ȯ���� ȭ��ǥ
	image* _loading;		// �ε� �̹���
public:
	mainMenu();
	~mainMenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

