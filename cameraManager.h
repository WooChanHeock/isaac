#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	//ī�޶� ���ߴ� ȭ�� ũ��(WINSIZEX, WINSIZEY)�� ��ǥ(left, right, top, bottom)
	RECT _screen;
	int _backWidth, _backHeight;	//backDC ũ��
	int _frontWidth, _frontHeight;	//frontDC ũ��

public:
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	void release();

	//ī�޶� ��ġ ����
	void updateScreen(float standardX, float standardY,
		float ratioX = 0.5f, float ratioY = 0.5f);
	//ī�޶� ���
	void render(HDC frontDC, int destX, int destY, HDC backDC, bool map = false, bool mini = false);
};

