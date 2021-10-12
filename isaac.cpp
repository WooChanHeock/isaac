#include "stdafx.h"
#include "isaac.h"

#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

isaac::isaac()
{
}

isaac::~isaac()
{
}

HRESULT isaac::init()
{
	lastTearKey.clear();
	imageInit();
	// ���¿� ���� Ÿ�̸� �ð�
	_itemFrameCount = _defencetime = 0;
	// �������� �ǰ�, ������ �̹��� �����ϱ����� ����
	_ist = STNONE;
	// ü��, �ִ� ü��
	_heart = _maxHeart = 6;	
	// ���� ������
	_chargebarMax = 6;
	_chargebar = 6;
	// ���� ��ġ
	_spaceItem = "";
	// �÷��̾� ��ġ �ʱ�ȭ ȭ�� �߾�
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	// ĳ���� ���ǵ�
	_speed = 1.00f;
	// ���� ���� �ӵ�
	_tear = 2.5f;
	// ���� ���� �ӵ��� ������ �����Ͽ� ��� �Ͽ��� ģ��
	_tearinter = _tear;
	// ������ �ӵ�
	_shotspeed = 1.00f;
	// �������� �����ư��� ������ ��⶧���� �װ� �����Ͽ� ������ ���糥�Ŵ�
	_tearnum = 0;
	// �������� ����
	_st = NONE;
	// ������ ��Ÿ�
	_range = 6.5f;
	// ������ ���ݷ�
	_damage = 3.5f;
	// �̵��ӵ� ����Ҷ� ���ӵ��� �и��� �ð��� ������� ģ�� �̴�.
	_time = 0;
	// �̹��� ������ ���� �� �̹��� ������ ī��Ʈ ����
	_atkFrameCount =_currentFrameX = _currentFrameY = _onionFrameX = _onionFrameY = _count = 0;
	// �ȴ� �ӵ��� ���� ��ȭ�ؾ� �Ǳ� ������ 
	_countMax = 8;
	// �������� ���� �ǰ� ���� ==  �׸����� ��Ʈ
	_rc = RectMakeCenter(_x, _y, 40, 10);
	// �������� space ������
	_spaceItem = "dice";
	_bomb = 1;
	// �������� �ʱ������ ���� �ʱ�ȭ
	_isaacTear = new isaacTear();
	_isaacTear->init("tear7","tearShadow7");
	return S_OK;
	
}

void isaac::release()
{
}

void isaac::update()
{
	if (_ist != STDEATH) 
	{
		// �÷��̾� �����̱�
		playerMove();
		playerShot();
		_isaacTear->update();
		/*if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (_isaacheadkey == "isaachead")
				_isaacheadkey = "isaaccrickethead";
			else if (_isaacheadkey == "isaaccrickethead")
				_isaacheadkey = "isaachead";
		}*/
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			isaacDamage(1);
		}
		_rc = RectMakeCenter(_x, _y, 40, 10);
	}
	_isaac_innereye = DATAMANAGER->getInnerEye();
	_isaac_lokishorns = DATAMANAGER->getLokisHorns();
	_isaac_wirehanger = DATAMANAGER->getWireHanger();
	_isaac_jesusjuice = DATAMANAGER->getJesusJuice();
	_isaac_mutantspider = DATAMANAGER->getMutantSpider();
	_isaac_halo = DATAMANAGER->getHalo();
	isaacIsDeath();
}

void isaac::render()
{
	_isaacTear->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	_count++;
	
	if (_time > 7)
		_countMax = 6;
	if (_time >= 14)
		_countMax = 5;
	if (_count % _countMax == 0)
	{
		_onionFrameY++;
		if (_onionFrameY > _isaaconion->getMaxFrameY()) _onionFrameY = 0;
		

		switch (_st)
		{
		case LEFT:
			
			if (_currentFrameX >= _isaacbody->getMaxFrameX() - 1) _currentFrameX = 0;
			
			_currentFrameY = 2;
			_currentFrameX++;
			
			_onionFrameX = 6;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(6);
			break;
		case RIGHT:
			if (_currentFrameX >= _isaacbody->getMaxFrameX() - 1) _currentFrameX = 0;
			_currentFrameY = 1;
			_currentFrameX++;

			_onionFrameX = 2;

			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(2);
			break;
		case UP:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;		
			_currentFrameX++;

			_onionFrameX = 4;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(4);
			break;
		case DOWN:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_currentFrameX++;

			_onionFrameX = 0;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(0);
			break;
		case NONE:
			_currentFrameY = 0;
			_currentFrameX = 0;

			_onionFrameX = 0;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(0);
			break;
		case LEFTUP:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_currentFrameX++;

			_onionFrameX = 4;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(4);
			break;
		case LEFTDOWN:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_currentFrameX++;

			_onionFrameX = 0;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(0);
			break;
		case RIGHTUP:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_currentFrameX++;

			_onionFrameX = 4;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(4);
			break;
		case RIGHTDOWN:
			if (_currentFrameX >= _isaacbody->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_currentFrameX++;

			_onionFrameX = 0;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(0);
			break;
		default:
			break;
		}
		_count = 0;
	}
	_isaacbody->setFrameY(_currentFrameY);
	_isaacbody->setFrameX(_currentFrameX);
	
	if (!lastTearKey.empty())
		switch (lastTearKey.back())
		{
		case LEFT:
			_onionFrameX = 6;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(6);
			break;
		case RIGHT:
			_onionFrameX = 2;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(2);
			break;
		case UP:
			_onionFrameX = 4;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(4);
			break;
		case DOWN:
			_onionFrameX = 0;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(0);
			break;
		default:
			break;
		}

	// ������ �������
	if (_tearinter <= 1) 
	{
		// ���Ͱ� ������� �����°� ����
		// �����߻��� ����
		if (!lastTearKey.empty())
		switch (lastTearKey.back()) 
		{
		case LEFT:
			_onionFrameX = 7;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(7);
			break;
		case RIGHT:
			_onionFrameX = 3;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(3);
			break;
		case UP:
			_onionFrameX = 5;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(5);
			break;
		case DOWN:
			_onionFrameX = 1;
			IMAGEMANAGER->findImage(_isaacheadkey)->setFrameX(1);
			break;
		default:
			break;
		}

	}

	//////////////////////////////////////////////
	// ���⼭���� ���
	//////////////////////////////////////////////

	//_isaacshadow->alphaRender(getMemDC(),_rc.left + 1, _rc.top, BYTE(150));

	// �ǰݾ� ��¦��¦ ȿ��
	if (_defencetime % 6 <= 2 || _ist == STDEATH)
	switch (_ist)
	{
	case STNONE: // �⺻ ����
		if (_isaac_onion)
		{
			_isaaconion->setFrameX(_onionFrameX);
			_isaaconion->setFrameY(_onionFrameY);
			RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaaconion", _rc.left - 24, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4) - 6, true);
		}
		if (_isaac_jesusjuice)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacjesusjuice", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4), _onionFrameX, 0, true);
		if (_isaac_mutantspider)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmutantspider", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4), _onionFrameX, 0, true);
		else if (_isaac_innereye)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacinnereye", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4), _onionFrameX, 0, true);
		if (_isaac_lokishorns)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaaclokishorns", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4), _onionFrameX, 0, true);
		if (_isaac_wirehanger)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacwirehanger", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() * 3/4), _onionFrameX, 0, true);
		if (_isaac_halo)
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaachalo", _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() * 3 / 4), _onionFrameX, 0, true);


		
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), _isaacheadkey, _rc.left - 12, _rc.bottom - _isaacbody->getFrameHeight() - (_isaacbody->getFrameHeight()) - (_isaachead->getFrameHeight() / 4), true);
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacbody", _rc.left, _rc.bottom - _isaacbody->getFrameHeight(), true);
		break;
	case STDMG : // �ǰ�
		if (_defencetime % 2 == 0)
			RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 + 2, _rc.bottom - 110, 2, 1, true);
		else
			RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 - 2, _rc.bottom - 110, 2, 1, true);
		break;
	case STDEATH: // ����
		if (_defencetime > 25)
			if (_defencetime % 4 <= 1)
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 + 2, _rc.bottom - 110, 0, 0, true);
			else
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 - 2, _rc.bottom - 110, 0, 0, true);
			
		else if (_defencetime > 20)
			if (_defencetime % 4 <= 1)
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 + 2, _rc.bottom - 110, 2, 1, true);
			else
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 50 - 2, _rc.bottom - 110, 2, 1, true);
		else 
			if (_defencetime % 4 <= 1)
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 40 + 2, _rc.bottom - 110, 3, 0, true);
			else
				RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 40 - 2, _rc.bottom - 110, 3, 0, true);
		break;
	case STITEM:
		// �������� ������ �ߵ� x
		// ������ �̹����� ���� �ѷ���� ��
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "isaacmotion", _rc.left - 45, _rc.bottom - 115, 1, 1, true);
		break;
	default:
		break;
	}
	
	RENDERMANAGER->pushBackRenderInfo(getMiddle(), "isaacshadow", _rc.left + 1, _rc.top, true, true, 150);

	if (_itemFrameCount == 1 && _ist != STDEATH)
		_ist = STNONE;
	if (_itemFrameCount > 0)
		_itemFrameCount--;
	// �ǰݽð� �� ������ 
	if (_defencetime == 1 && _ist != STDEATH)
		_ist = STNONE;
	if (_defencetime > 0)
		_defencetime--;
	
}

void isaac::imageInit()
{
	// ������ ��ü������ �̹����� �̰��� �ʱ�ȭ
	// ������ ���
	IMAGEMANAGER->addFrameImage("isaacmotion", "image/player/isaacmotion.bmp", 512, 384, 4, 3, true, RGB(255, 0, 255));
	_isaacmotion = IMAGEMANAGER->findImage("isaacmotion");
	// ������ ���׾Ƹ�
	IMAGEMANAGER->addFrameImage("isaacbody", "image/player/isaacbody.bmp", 400, 90, 10, 3, true, RGB(255, 0, 255));
	_isaacbody = IMAGEMANAGER->findImage("isaacbody");
	// ������ �밡��
	IMAGEMANAGER->addFrameImage("isaachead", "image/player/isaachead.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	_isaachead = IMAGEMANAGER->findImage("isaachead");
	// ������ ũ������� ���� �밡��
	IMAGEMANAGER->addFrameImage("isaaccrickethead", "image/item/effect/isaaccrickethead.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	_isaacheadkey = "isaachead";
	// ������ �׸���
	IMAGEMANAGER->addImage("isaacshadow", "image/player/shadow/isaacshadow.bmp", 38, 8, true, RGB(255, 0, 255), true);
	_isaacshadow = IMAGEMANAGER->findImage("isaacshadow");
	// ������ ���� ����Ʈ
	IMAGEMANAGER->addFrameImage("isaaconion", "image/item/effect/isaaconion.bmp", 704, 246, 8, 3, true, RGB(255, 0, 255));
	_isaaconion = IMAGEMANAGER->findImage("isaaconion");
	// ������ �̳� ����
	IMAGEMANAGER->addFrameImage("isaacinnereye", "image/item/effect/theinnereye.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	_isaacinnereye = IMAGEMANAGER->findImage("isaacinnereye");
	// ������ ��Ű ȥ
	IMAGEMANAGER->addFrameImage("isaaclokishorns", "image/item/effect/lokishorns.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	// ������ ���
	IMAGEMANAGER->addFrameImage("isaacwirehanger", "image/item/effect/wirehanger.bmp", 512, 128, 8, 1, true, RGB(255, 0, 255));
	// ������ �����ֽ�
	IMAGEMANAGER->addFrameImage("isaacjesusjuice", "image/item/effect/jesusjuice.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	// ����Ʈ �����̴�
	IMAGEMANAGER->addFrameImage("isaacmutantspider", "image/item/effect/mutantspider.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	// ���Ϸ�
	IMAGEMANAGER->addFrameImage("isaachalo", "image/item/effect/halo.bmp", 512, 128, 8, 1, true, RGB(255, 0, 255));

	// ������ ���� ������ �� �׿��ٰ� �ʱ�ȭ 
	// ������ �׸��� ��Ʈ
	IMAGEMANAGER->addImage("tear7", "image/tear/tear7.bmp", 25,25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tearShadow7", "image/tear/shadow/tearShadow7.bmp", 25, 5, true, RGB(255, 0, 255), true);
	// 
}

void isaac::playerMove()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_st == RIGHT || _st == RIGHTUP || _st == RIGHTDOWN)
		_time = 0;

		_isMoved = true;

		if (_st == LEFTUP || LEFTDOWN == _st)
			_x -= getSpeed(_speed, _time) - 2.2;
		else
			_x -= getSpeed(_speed, _time);

		if (_st == UP)
		{
			_st = LEFTUP;
			_second = SECOND;
		}
		else if (_st == DOWN)
		{
			_st = LEFTDOWN;
			_second = SECOND;
		}
		else if (_second < 0)
		{
			_st = LEFT;
		}
		if (_tearX > -1.5 && _tearX <= 0)
			_tearX -= 0.1;
	} 
	else 
	{
		if (_tearX < 0)
			_tearX += 0.1;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_st == LEFT || _st == LEFTUP || _st == LEFTDOWN)
		_time = 0;

		_isMoved = true;

		if (_st == RIGHTUP || RIGHTDOWN == _st)
			_x += getSpeed(_speed, _time) - 2.2;
		else
			_x += getSpeed(_speed, _time);

		if (_st == UP) {
			_st = RIGHTUP;
			_second = SECOND;
		}
		else if (_st == DOWN) {
			_st = RIGHTDOWN;
			_second = SECOND;
		}
		else if (_second < 0)
			_st = RIGHT;
		if (_tearX < 1.5 && _tearX >= 0)
			_tearX += 0.1;
	}
	else 
	{
		if (_tearX > 0)
			_tearX -= 0.1;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_st == DOWN || _st == LEFTDOWN || _st == RIGHTDOWN)
			_time = 0;
		_isMoved = true;
		if (_st == LEFTUP || RIGHTUP == _st)
			_y -= getSpeed(_speed, _time) - 2.2;
		else
			_y -= getSpeed(_speed, _time);
		if (_st == LEFT) {
			_st = LEFTUP;
			_second = SECOND;
		}
		else if (_st == RIGHT)
		{
			_st = RIGHTUP;
			_second = SECOND;
		}
		else if (_second < 0)
			_st = UP;
		if (_tearY > 0) _tearY = 0;
		if (_tearY > -1.5 && _tearY <= 0)
			_tearY -= 0.1;
	}
	else
	{
		if (_tearY < 0)
			_tearY += 0.1;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_st == UP || _st == LEFTUP || _st == RIGHTUP)
			_time = 0;
		_isMoved = true;
		if (_st == LEFTDOWN || RIGHTDOWN == _st)
			_y += getSpeed(_speed, _time) - 2.2;
		else
			_y += getSpeed(_speed, _time);
		if (_st == LEFT) {
			_st = LEFTDOWN;
			_second = SECOND;
		}
		else if (_st == RIGHT) {
			_st = RIGHTDOWN;
			_second = SECOND;
		}
		else if (_second < 0) {
			_st = DOWN;
		}
		if (_tearY < 0) _tearY = 0;
		if (_tearY < 1.5 && _tearY >= 0)
			_tearY += 0.1;
	}
	else
	{
		if (_tearY > 0)
			_tearY -= 0.1;
	}

	if (_isMoved)
	{
		if (_time < 14)
			_time = 14;
		else
			_time += 2;

	}
	else if (!_isMoved && 0 < getSpeed(_speed, _time))
	{
		_time -= _speed * 2.5;
		_tearX = 0;
		_tearY = 0;
		if (_st != NONE)
		{
			switch (_st)
			{
			case LEFT:
				_x -= getSpeed(_speed, _time);
				break;
			case RIGHT:
				_x += getSpeed(_speed, _time);
				break;
			case UP:
				_y -= getSpeed(_speed, _time);
				break;
			case DOWN:
				_y += getSpeed(_speed, _time);
				break;
			case LEFTUP:
				_x -= getSpeed(_speed, _time);
				_y -= getSpeed(_speed, _time);
				break;
			case LEFTDOWN:
				_x -= getSpeed(_speed, _time);
				_y += getSpeed(_speed, _time);
				break;
			case RIGHTUP:
				_x += getSpeed(_speed, _time);
				_y -= getSpeed(_speed, _time);
				break;
			case RIGHTDOWN:
				_x += getSpeed(_speed, _time);
				_y += getSpeed(_speed, _time);
				break;
			case NONE:
				break;
			}
		}
	}
	if (WINSIZEX < _x)
		_x = 0;
	if (0 > _x)
		_x = WINSIZEX;
	_isMoved = false;
	_second--;

	if (_time < 0)
		_st = NONE;
}

void isaac::playerShot()
{
	// �������� ����Ű�� �������� ���� if���� �⿬
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		lastTearKey.push_back(LEFT);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		lastTearKey.remove(LEFT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		lastTearKey.push_back(RIGHT);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		lastTearKey.remove(RIGHT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		lastTearKey.push_back(UP);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		lastTearKey.remove(UP);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		lastTearKey.push_back(DOWN);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		lastTearKey.remove(DOWN);
	}

	// ���� ��ƮŰ�� ������� �ʰ�, �÷��̾��� ���������� ��� �ִٸ� ��� �Ѵ�.
	
	if (!lastTearKey.empty() && _tearinter > 5.0 - _tear)
	{
		_tearinter = 0;
		tearShot(lastTearKey.back());
	}
	_tearinter += 0.1;
}

float isaac::getSpeed(float speed, int & time)
{
	if (time > 50)
		time = 50;
	speed = speed * speed * 1.5 + int(time * 0.1);
	return speed;
}

void isaac::tearShot(moveState st)
{
	if (_isaac_lokishorns && RND->getFromIntTo(0, 10) < 3) 
	{
		if (_isaac_mutantspider) 
		{
			switch (st)
			{
			case LEFT:
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 12, PI + 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2 + 8, PI + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2 - 8, PI - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 12, PI - 0.05, _shotspeed, _range, _tearX, _tearY);
				if (_isaac_innereye)
				{
					_isaacTear->fire(_rc.left - 8, (_rc.top + _rc.bottom) / 2 + 8, PI + 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.left - 8, (_rc.top + _rc.bottom) / 2 - 8, PI - 0.04, _shotspeed, _range, _tearX, _tearY);

				}

				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				break;
			case RIGHT:
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 12, 0 - 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2 + 8, 0 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2 - 8, 0 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 12, 0 + 0.05, _shotspeed, _range, _tearX, _tearY);
				if (_isaac_innereye)
				{
					_isaacTear->fire(_rc.right + 8, (_rc.top + _rc.bottom) / 2 + 8, 0 - 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.right + 8, (_rc.top + _rc.bottom) / 2 - 8, 0 + 0.04, _shotspeed, _range, _tearX, _tearY);
				}
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
				break;
			case UP:
				if (_isaac_innereye)
				{
					_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.top - 8, PI / 2 - 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top - 15, PI / 2, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.top - 8, PI / 2 + 0.04, _shotspeed, _range, _tearX, _tearY);
				}
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 12, _rc.top, PI / 2 - 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.top - 15, PI / 2 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.top - 15, PI / 2 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 12, _rc.top, PI / 2 + 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
				break;
			case DOWN:
				if (_isaac_innereye)
				{
					_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.bottom + 8, PI * 3 / 2 + 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom + 15, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.bottom + 8, PI * 3 / 2 - 0.04, _shotspeed, _range, _tearX, _tearY);
				}
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 12, _rc.bottom, PI * 3 / 2 + 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.bottom + 15, PI * 3 / 2 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.bottom + 15, PI * 3 / 2 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 12, _rc.bottom, PI * 3 / 2 - 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
				break;
			default:
				break;
			}
		}
		else if (_isaac_innereye) 
		{
			switch (st)
			{
			case LEFT:
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 5, PI + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 10, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 5, PI - 0.08, _shotspeed, _range, _tearX, _tearY);

				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 , 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				break;
			case RIGHT:
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 5, 0 - 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 10, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 5, 0 + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 , PI, _shotspeed, _range, _tearX, _tearY);
				break;
			case UP:
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.top, PI / 2 - 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top - 10, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.top, PI / 2 + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 , 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 , PI, _shotspeed, _range, _tearX, _tearY);
				break;
			case DOWN:
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.bottom, PI * 3 / 2 + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom + 10, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.bottom, PI * 3 / 2 - 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 , 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 , _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 , PI, _shotspeed, _range, _tearX, _tearY);
				break;
			default:
				break;
			}
			
			
			
			
		}
		else 
		{
			if (_tearnum == 0)
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 5, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);

				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 5, PI, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 1;
			}
			else
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 5, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);

				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 5, PI, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 0;
			}
		}
	}
	else {
		switch (st)
		{
		case LEFT:
			if (_isaac_mutantspider)
			{
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 12, PI + 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2+8, PI + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2-8, PI - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 12, PI - 0.05, _shotspeed, _range, _tearX, _tearY);
				if (_isaac_innereye)
				{
					_isaacTear->fire(_rc.left - 8, (_rc.top + _rc.bottom) / 2 + 8, PI + 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.left - 15, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.left - 8, (_rc.top + _rc.bottom) / 2 - 8, PI - 0.04, _shotspeed, _range, _tearX, _tearY);
					
				}
			}
			else if (_isaac_innereye)
			{
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 5, PI + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left - 10, (_rc.top + _rc.bottom) / 2, PI, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 5, PI - 0.08, _shotspeed, _range, _tearX, _tearY);
			}
			else if (_tearnum == 0)
			{

				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 + 5, PI, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 1;
			}
			else
			{
				_isaacTear->fire(_rc.left, (_rc.top + _rc.bottom) / 2 - 5, PI, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 0;
			}
			break;
		case RIGHT:
			
			if (_isaac_mutantspider)
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 12, 0 - 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2 + 8, 0 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2 - 8, 0 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 12, 0 + 0.05, _shotspeed, _range, _tearX, _tearY);
				if (_isaac_innereye) 
				{
					_isaacTear->fire(_rc.right + 8, (_rc.top + _rc.bottom) / 2 + 8, 0 - 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.right + 15, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire(_rc.right + 8, (_rc.top + _rc.bottom) / 2 - 8, 0 + 0.04, _shotspeed, _range, _tearX, _tearY);
				}
			}
			else if (_isaac_innereye)
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 5, 0 - 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right + 10, (_rc.top + _rc.bottom) / 2, 0, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 5, 0 + 0.08, _shotspeed, _range, _tearX, _tearY);
			}
			else if (_tearnum == 0)
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 + 5, 0, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 1;
			}
			else
			{
				_isaacTear->fire(_rc.right, (_rc.top + _rc.bottom) / 2 - 5, 0, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 0;
			}
			break;
		case UP:
			if (_isaac_mutantspider)
			{
				if (_isaac_innereye)
				{
					_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.top - 8, PI / 2 - 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top - 15, PI / 2, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.top - 8, PI / 2 + 0.04, _shotspeed, _range, _tearX, _tearY);
				}
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 12, _rc.top, PI / 2 - 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.top - 15, PI / 2 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.top - 15, PI / 2 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 12, _rc.top, PI / 2 + 0.05, _shotspeed, _range, _tearX, _tearY);
				
			}
			else if (_isaac_innereye)
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.top, PI / 2 - 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.top - 10, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.top, PI / 2 + 0.08, _shotspeed, _range, _tearX, _tearY);
			}
			else if (_tearnum == 0)
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 1;
			}
			else
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.top, PI / 2, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 0;
			}
			break;
		case DOWN:
			if (_isaac_mutantspider)
			{
				if (_isaac_innereye)
				{
					_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.bottom + 8, PI * 3 / 2 + 0.04, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom + 15, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
					_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.bottom + 8, PI * 3 / 2 - 0.04, _shotspeed, _range, _tearX, _tearY);
				}
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 12, _rc.bottom, PI * 3 / 2 + 0.05, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 8, _rc.bottom + 15, PI * 3 / 2 + 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 8, _rc.bottom + 15, PI * 3 / 2 - 0.01, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 12, _rc.bottom, PI * 3 / 2 - 0.05, _shotspeed, _range, _tearX, _tearY);
			}
			else if (_isaac_innereye)
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.bottom, PI * 3 / 2 + 0.08, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2, _rc.bottom + 10, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.bottom, PI * 3 / 2 - 0.08, _shotspeed, _range, _tearX, _tearY);
			}
			else if (_tearnum == 0)
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 + 5, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 1;
			}
			else
			{
				_isaacTear->fire((_rc.left + _rc.right) / 2 - 5, _rc.bottom, PI * 3 / 2, _shotspeed, _range, _tearX, _tearY);
				_tearnum = 0;
			}
			break;
		default:
			break;
		}
	}
}

void isaac::isaacDamage(int damage)
{
	// �ǰݽð������� ���¾�
	if (_defencetime == 0) {
		_heart -= damage;
		_ist = STDMG;
		_defencetime = 30;
	}
}
