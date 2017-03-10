#include "object.h"

#include "control.h"
#include "item.h"

USING_NS_CC;

bool ObjectN::init(){
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();

	//mAreaFlag = 0;
	mCursorNum = 1;
	mState = 0;

	mGetItem = mField = mMsg = "";
	mTouchTime = 0;

	mArea = Rect(0, 0, 0, 0);

	mTouchEvent = CallFunc::create([]() {return; });
	mTouchEvent->retain();

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(ObjectN::touchOn, this); /*[&](Touch* touch, Event* event) {return true; };*/
	//listener->onTouchMoved = CC_CALLBACK_2(ObjectN::checkOn, this);
	//listener->onTouchEnded = CC_CALLBACK_2(ObjectN::touchOff, this);/* [=](Touch* touch, Event* event) {};*/
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//デフォルトで中央に表示
	this->setPosition(Director::getInstance()->getVisibleSize() / 2);

	return true;
}

void ObjectN::setArea(cocos2d::Rect rect) {
	mArea = rect; //Rect(x, y, w, h);
	//mAreaFlag = 1;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ObjectN::touchOn, this); /*[&](Touch* touch, Event* event) {return true; };*/
	listener->onTouchMoved = CC_CALLBACK_2(ObjectN::checkOn, this);
	listener->onTouchEnded = CC_CALLBACK_2(ObjectN::touchOff, this);/* [=](Touch* touch, Event* event) {};*/
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void ObjectN::checkOn(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
		Control::me->setCursor(mCursorNum);		
	}
	else {
		//Control::me->setCursor(0);
	}

}

bool ObjectN::touchOn(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
		Control::me->setCursor(mCursorNum);
		
		//範囲がタッチされた時
		mTouchTime = 1;

	}
	else {
		//Control::me->setCursor(0);
	}

	return true;	//カーソル変化の関係で無条件でタッチを拾う

}

void ObjectN::touchOff(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
		if (mTouchTime > 0 && mTouchTime < 30) {

			//フィールド移動イベント
			if (mField != "" && getParent()->getOpacity() == 255) {
				Control::me->changeField(mField);
			}
			
			//その他のイベント
			//mTouchEvent();
			runAction(mTouchEvent);	

			//メッセージイベント
			if (mMsg != "")Control::me->showMsg(mMsg);

			
			//アイテムゲットイベント
			if (mGetItem != "") {
				Item::sharedItem()->getItem(mGetItem, touch->getLocation());
				runAction(RemoveSelf::create());
				Control::me->setCursor(0);
			}
		}
	}

	mTouchTime = 0;
}

//void ObjectN::setTouchEvent(void (*event)()){
//	mTouchEvent = event;
//}

void ObjectN::setCursor(int i) { mCursorNum = i; }
void ObjectN::setState(int s) { mState = s; }
void ObjectN::setItemGetEvent(std::string s) { mGetItem = s; }
void ObjectN::setFieldChangeEvent(std::string s) { mField = s; }
void ObjectN::setMsg(std::string s) { mMsg = s; };

//void ObjectN::setTouchEvent(void func()) { mTouchEvent = func; }
void ObjectN::setTouchEvent(cocos2d::CallFunc *func) { mTouchEvent = func; mTouchEvent->retain(); }

int ObjectN::getState() { return mState; }
std::string ObjectN::getMsg() { return mMsg; }
std::string ObjectN::getField() { return mField; }

void ObjectN::update(float delta) {
	if (mTouchTime > 0) mTouchTime++;
}
