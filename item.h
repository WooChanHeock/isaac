#pragma once
#include "gameNode.h"

enum itemVal
{
	EMPTY,
	PASSIVE,
	ACTIVE
};

class item :
    public gameNode
{
protected:
	// �̹��� �̸�
	image* _imageName;
	// ��ǥ
	float _x;
	float _y;
	float _itemY;
	// ������ ǥ��
	int _count;
	// ������ �̸�
	const char* _itemName;
	// ��Ʈ
	RECT _rc;
	RECT _itemRect;
	// ������ ����
	itemVal _itemVal;
	// 
	int _itemFrameCount;
public:
	item() {}
	~item() {}

	virtual HRESULT init(const char* itemName, float x, float y, itemVal it = EMPTY);
	virtual void release();
	virtual void update();
	virtual void render();

	// getter setter
	void setItemFrameCount(int ifc) { _itemFrameCount = ifc; }
	inline int getIfc() { return _itemFrameCount; }
	inline RECT getRect() { return _rc; }
	inline const char* getItemName() { return _itemName; }
	void setIv(itemVal iv) { _itemVal = iv; }
	inline itemVal getIv() { return _itemVal; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getMiddle() { return (_rc.bottom + _rc.top) / 2; }
};

