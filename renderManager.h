#pragma once
#include "singletonBase.h"
using namespace std;

struct renderInfo 
{
	//�׷��� ��ǥ
	float x, y;
	// ��Ʈ�� Ű
	const char* strkey;
	//leftTop�ΰ�?
	bool leftTop;
	// ���� �Ұ��ΰ�?
	bool blend;
	// �������̹��� �ΰ�?
	bool isFrame;
	// ���� ��
	BYTE alpha;
	// ������ ����
	// ������ ��
	int frameX;
	int frameY;
	// �ִϸ��̼� ���� �ΰ�?
	bool isAni;
	image* img;
	animation* ani;

};


class renderManager : public singletonBase<renderManager>
{
private:
	//first �׸����� �߾Ӱ��� ������ float
	//second �׷��� ����
	typedef vector<pair<float, renderInfo>>				renderList;
	typedef vector<pair<float, renderInfo>>::iterator	renderIter;
private:
	renderList _mRenderList;

	float _cameraX;
	float _cameraY;
public:
	renderManager() {}
	~renderManager() {}

	void mergeSort(vector<pair<float, renderInfo>>& v, int s, int e);
	void merge(vector<pair<float, renderInfo>>& v, int s, int e, int m);

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	
	void pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop = true, bool blend = false, BYTE alpha = 255);
	void pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y, int frameX, int frameY, bool leftTop = true, bool blend = false, BYTE alpha = 255);
	void pushBackRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop = true, bool blend = false,  BYTE alpha = 255);
	void pushBackAniRenderInfo(float middle, image* imgname, float x, float y, animation* ani, bool leftTop = true, bool blend = false, BYTE alpha = 255);

	void setCameraX(float num) { _cameraX = num; }
	float getCameraX() { return _cameraX; }
	void setCameraY(float num) { _cameraY = num; }
	float getCameraY() { return _cameraY; }

	
};

