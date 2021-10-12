#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	// fadein out ȿ���� ���� ����
	IMAGEMANAGER->addImage("�������", "image/ui/bgblack.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255), true);
	SCENEMANAGER->addScene("���θ޴�", new mainMenu);
	SCENEMANAGER->addScene("�븻��������", new nomalStage);
	SCENEMANAGER->addScene("���۽�������", new startStage);
	SCENEMANAGER->addScene("��������1", new stage1);
	SCENEMANAGER->addScene("��������2", new stage2);
	SCENEMANAGER->addScene("��������3", new stage3);
	SCENEMANAGER->addScene("��������4", new stage4);
	SCENEMANAGER->addScene("��������5", new stage5);
	SCENEMANAGER->addScene("��������6", new stage6);
	SCENEMANAGER->addScene("������������", new bossStage);
	SCENEMANAGER->addScene("������Ʈ��", new bossIntro);
	SCENEMANAGER->setScene("���θ޴�");
	// ����Ʈ �߰�
	EFFECTMANAGER->addEffect("teareffect7", "image/tear/effect/teareffect7.bmp", 1680, 105, 105, 105, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodteareffect3", "image/tear/effect/bloodteareffect3.bmp", 1536, 96, 96, 96, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("coin1effect", "image/item/effect/coin1effect.bmp", 768, 128, 128, 128, 1, 0.3f, 20);
	EFFECTMANAGER->addEffect("poof_large", "image/effect/poof_large.bmp", 1530, 91, 102, 91, 1, 0.6f, 20);
	EFFECTMANAGER->addEffect("bloodpoof1", "image/effect/bloodpoof1.bmp", 1536, 128, 128, 128, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodpoofalt1", "image/effect/bloodpoofalt1.bmp", 2048, 128, 128, 128, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodpoof3", "image/effect/bloodpoof3.bmp", 3840, 200, 320, 200, 1, 0.5f, 20);
	EFFECTMANAGER->addEffect("bombeffect", "image/effect/bombeffect.bmp", 2304, 192, 192, 192, 1, 0.4f, 10);
	EFFECTMANAGER->addEffect("item_poof", "image/effect/item_poof.bmp", 2048, 128, 128, 128, 1, 0.4f, 20);
	EFFECTMANAGER->addEffect("mini_poof", "image/effect/mini_poof.bmp", 1024, 64, 64, 64, 1, 0.1f, 20);
	EFFECTMANAGER->addEffect("poof_boss", "image/effect/poof_boss.bmp", 4096, 256, 256, 256, 1, 0.5f, 20);

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('R')) {
		EFFECTMANAGER->release();
		init();
		SCENEMANAGER->restart();
		SCENEMANAGER->setScene("���۽�������");
	}
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//==================================================
	//���⵵ �ǵ�������
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
