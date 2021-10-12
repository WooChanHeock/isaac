#pragma once
#include "gameNode.h"
#include "tear.h"

#define SECOND 3
// �������� Center Rect


enum isaacState 
{
	STNONE,
	STDMG,
	STDEATH,
	STITEM
};

class isaac :
	public gameNode
{
private:
	// �������� ���ȿ� ���� ��� ����
	int _maxHeart;
	int _heart;
	float _range;
	float _speed;
	float _tear;
	float _shotspeed;
	float _damage;
	// �������� ������ ������
	int _chargebarMax;
	int _chargebar;
	int _coin;
	int _bomb;
	int _key;
	const char* _spaceItem;
	// �������� ����
	isaacState _ist;
	// ���¿� ���� ī��Ʈ ����
	int _atkFrameCount;
	int _itemFrameCount;
	// �������� ���� �� ��ġ
	string _currentStage;
	
	

	float _x, _y;
	
	
	bool _isMoved;
	int _tearnum;
	float _tearX;
	float _tearY;
	float _tearinter;
	int _second;
	moveState _st;
	int _time;
	list<moveState> lastTearKey;
	int _count;
	int _countMax;
	int _defencetime;
	int _onionFrameX;
	int _onionFrameY;
	int _currentFrameX;
	int _currentFrameY;
	string _tearName;
	isaacTear* _isaacTear;
	
	RECT _rc;
	image* _isaacbody;
	image* _isaachead;
	image* _isaacmotion;
	const char* _isaacheadkey;
	image* _isaacshadow;
	image* _isaaconion;
	image* _isaacinnereye;

	// ������ ������ ���� ���� ������
	bool _isaac_onion;
	bool _isaac_innereye;
	bool _isaac_lokishorns;
	bool _isaac_wirehanger;
	bool _isaac_jesusjuice;
	bool _isaac_mutantspider;
	bool _isaac_halo;
public:
	isaac();
	~isaac();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void imageInit();
	// �÷��̾ �����̴� �Լ�
	void playerMove();
	// �÷��̾ ������ ��� �Լ�
	void playerShot();
	// ���ǵ带 ����
	float getSpeed(float speed, int &time);
	// ���� �߻�
	void tearShot(moveState st);
	// �������� ������� ������ ȣ��
	void isaacDamage(int damage);
	//�������� �׾����� Ȯ��
	void isaacIsDeath() { if (_maxHeart - _heart >= _maxHeart) _ist = STDEATH; }



	//////////////////////////////////////
	//	������ �����ڴ� �̹ؿ� ������
	/////////////////////////////////////
	
	void setLastTearKey(list<moveState> lastTearKey) { this->lastTearKey = lastTearKey; }
	list<moveState> getLastTearKey() { return lastTearKey; }

	string getTearName() { return _tearName; }
	void setTearName(string name) { _tearName = name; }
	const char* getIsaacHead() { return _isaacheadkey; }
	int getSecond() { return _second; }
	void setSecond(int num) { _second = num; }
	// ������ ��� ����� �ֱ� ���Ѱ�
	void setIst(isaacState ist) { _ist = ist; }
	isaacState getIst() { return _ist; }
	int getDefenceTime() { return _defencetime; }
	void setItemFrameCount(int ifc) { _itemFrameCount = ifc; }
	int getItemFrameCount() { return _itemFrameCount; }
	// ��Ƽ�� ������ ���� �������� ������
	const char* getSpaceItem() { return _spaceItem; }
	void setSpaceItem(const char* itemName) { _spaceItem = itemName; }
	// 
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	int getHeart() { return _heart; }
	void setHeart(int num) { _heart = num; }
	int getMaxHeart() { return _maxHeart; }
	void setMaxHeart(int num) { _maxHeart = num; }
	int getChargebar() { return _chargebar; }
	void setChargebar(int num) { _chargebar = num; }
	int getChargebarMax() { return _chargebarMax; }
	void setChargebarMax(int num) { _chargebarMax = num; }
	int getCoin() { return _coin; }
	void setCoin(int num) { _coin = num; }
	int getBomb() { return _bomb; }
	void setBomb(int num) { _bomb = num; }
	int getKey() { return _key; }
	void setKey(int num) { _key = num; }
	float getRange() { return _range; }
	void setRange(float num) { _range = num; }
	float getSpeed() { return _speed; }
	void setSpeed(float num) { _speed = num; }
	float getTear() { return _tear; }
	void setTear(float tear) { _tear = tear; }
	float getShotspeed() { return _shotspeed; }
	void setShotspeed(float num) { _shotspeed = num; }
	float getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }
	int getMiddle() { return (_rc.bottom + _rc.top) / 2; }

	vector<tagTear>* getVTear() { return _isaacTear->getVTear(); }
	vector<tagTear>::iterator getViTear() { return _isaacTear->getViTear(); }
	// RECT ���� �� ��������
	inline RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }
	// ������ ���� �̹��� �Լ����� ���⿡
	void setHeadKey(const char* str) { _isaacheadkey = str; }
	void setCricketshead() { _isaacheadkey = "isaaccrickethead"; }
	void setOnion(bool is) { _isaac_onion = is; }
	bool getOnion() { return _isaac_onion; }
	
};

