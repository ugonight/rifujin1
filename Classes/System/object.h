#pragma once
#include "cocos2d.h"

	

class ObjectN : public cocos2d::Sprite {
	//bool mAreaFlag;	//タッチエリアが存在するか
	cocos2d::Rect mArea;
	int mCursorNum;
	int mState;	//状態・フラグ的なもの

	std::string mGetItem;	//タッチ時に入手するアイテム
	std::string mField;		//移動先のフィールド
	std::string mMsg;		//タッチ時に表示するメッセージ

	//タッチ時のイベント
	//void(*mTouchEvent)();
	cocos2d::CallFunc *mTouchEvent;

	int mTouchTime;

	//カーソルイベント
	void checkOn(cocos2d::Touch* touch, cocos2d::Event* event);
	bool touchOn(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchOff(cocos2d::Touch* touch, cocos2d::Event* event);

public:
	virtual ~ObjectN();

	virtual bool init();
	virtual void update(float delta);

	void setArea(cocos2d::Rect rect);	//(int x, int y, int w, int h)
	void setCursor(int cursorNum);
	void setState(int state);
	void setItemGetEvent(std::string itemName);
	void setFieldChangeEvent(std::string fieldName);
	void setMsg(std::string msg);

	//void setTouchEvent(void (*func)());
	void setTouchEvent(cocos2d::CallFunc *func);

	int getState();
	std::string getMsg();
	std::string getField();

	CREATE_FUNC(ObjectN);
};
