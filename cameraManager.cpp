#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init(int width, int height)
{	
	//backDC�� frontDCũ�� ����
	_backWidth = width;
	_backHeight = height;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;
	//ȭ�� Rect ����
	_screen = RectMake(0, 0, WINSIZEX, WINSIZEY);

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::updateScreen(float standardX, float standardY, float ratioX, float ratioY)
{
	//�÷��̾� �������� ȭ��(_screen)����
	//playground.cpp�� update()���� ��� �������ָ� ��
	//�μ��� ������ �Ǵ� ��ü�� x, y��ǥ�� ����(����� player�� x, y)

	//X�� (��, ��)
	if (standardX - _frontWidth * ratioX < 0)
		standardX = 0;
	else if (standardX + _frontWidth * (1 - ratioX) > _backWidth)
		standardX = _backWidth - _frontWidth;
	else
		standardX -= _frontWidth * ratioX;
	//Y�� (��, ��)
	if (standardY - _frontHeight * ratioY < 0)
		standardY = 0;
	else if (standardY + _frontHeight * (1 - ratioY) > _backHeight)
		standardY = _backHeight - _frontHeight;
	else
		standardY -= _frontHeight * ratioY;

	//����
	_screen = RectMake(standardX, standardY, _frontWidth, _frontHeight);
}

void cameraManager::render(HDC frontDC, int destX, int destY, HDC backDC, bool map, bool mini)
{
	/********* �μ� ���� *********/ /*
	HDC frontDC: ���縦 ���� DC (������ �츮�� ���� ȭ��)
	int destX: �츮�� ���� ȭ�鿡�� ������� x��ǥ
	int destY: �츮�� ���� ȭ�鿡�� ������� y��ǥ
	HDC backDC: ������ �� DC (������ �츮�� �׸��� ȭ��)
	bool map: true�� ��ü�� ���, false�� �� ���
	bool mini: true�� �̴ϸ� ���, false�� �� ���
	*/

	if (map) {
		StretchBlt(
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			backDC,
			0,
			0,
			_backWidth,
			_backHeight,
			SRCCOPY);
	}
	//�̴ϸ� ������ true�� ��ũ���� ������ܿ� �̴ϸ� ���
	else if (mini) {
		StretchBlt(
			backDC,
			_screen.right - _frontWidth / 4,
			_screen.top,
			_frontWidth / 4,
			_frontHeight / 5,
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			SRCCOPY);
	}
	//DC�������� ��Ӻ��縦 ����(ȭ�� ������ ����)
	BitBlt(
		frontDC,				//����޴� DC
		destX,					//����޴� ��ǥ(left)
		destY,					//����޴� ��ǥ(top)
		_frontWidth,			//����Ǵ� ����ũ��
		_frontHeight,			//����Ǵ� ����ũ��
		backDC,					//����Ǵ� DC
		_screen.left, _screen.top,	//����Ǵ� ������ǥ(left, top)
		SRCCOPY);				//�״�� �����ؿ���(���)
}