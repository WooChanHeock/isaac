#pragma once
#include "gameNode.h"
#include "pickUpItem.h"
#include "coin.h"
#include "bomb.h"
#include "sparkBomb.h"
#include "key.h"
#include "heart.h"
#include "isaac.h"
#include "item.h"

class itemManager : public gameNode
{
private:
    // �Ⱦ��������� ����
    vector<pickUpItem*>				_vPick;
    vector<pickUpItem*>::iterator	_viPick;
    // �������� ����
    vector<item*>                   _vItem;
    vector<item*>::iterator         _viItem;
    // �Ͷ߸� ��ź�� ����
    vector<pickUpItem*>             _vBomb;
    vector<pickUpItem*>::iterator   _viBomb;
    // �浹ó���� ��Ʈ
    RECT _temp;

    //
    bool _spaceItem;
public:
    itemManager() {}
    ~itemManager() {}

    virtual HRESULT init();
    virtual void release();
    virtual void update(isaac* _isaac);
    virtual void render();

    // �Ⱦ� ������ �浹 ó��
    void isPickCollision(isaac* _isaac);
    // ������ �浹 ó��
    void isItemCollision(isaac* _isaac);
    // �浹ó���� ��ź �迭 �ѱ涧 ���
    vector<pickUpItem*>* getVBomb() { return &_vBomb; }
    // ��Ƽ�� ������ ȿ�� ó��
    void activeItemEffect(const char* itemName);
    void setCoin(int x, int y);
    void setBomb(int x, int y);
    void setKey(int x, int y);
    void setHeart(int x, int y);
    void setItem(const char* itemName, int x, int y, itemVal iv);
    void setItem(int x, int y);
    void setSparkBomb(int x, int y);
};

