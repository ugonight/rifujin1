#pragma once
#include "cocos2d.h"

#define CURSOR_NUM 8

class Cursor : public cocos2d::Layer {
private:
	//cocos2d::Sprite* mCursorImg[CURSOR_NUM];
	int mCursorNum;
	bool mTouchNow;

	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	bool moveEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	bool endEvent(cocos2d::Touch* touch, cocos2d::Event* event);

public:
	virtual bool init();

	void setCursorNum(int i);
	int getCursorNum();

	CREATE_FUNC(Cursor);
};