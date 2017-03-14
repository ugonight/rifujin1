#include "cursor.h"

USING_NS_CC;

bool Cursor::init() {

	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mCursorNum = mTouchNow = 0;

	//画像
	//for (int i = 0; i < CURSOR_NUM; i++) {
	//	auto rect = Rect(80 * i, 0, 80, 80);
	//	auto sprite = Sprite::create("cursor.png", rect);
		auto rect = Rect(80 * 0, 0, 80, 80);
		auto sprite = Sprite::create("cursor.png", rect);
		

		sprite->setOpacity(0.0f);
		sprite->setPosition(0,0);
		sprite->setAnchorPoint(Vec2(0.5f,0.0f));
		this->addChild(sprite, 0, 0);
	/*}*/


	//タッチイベント
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Cursor::touchEvent, this);
	listener->onTouchMoved = CC_CALLBACK_2(Cursor::moveEvent, this);
	listener->onTouchEnded = CC_CALLBACK_2(Cursor::endEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;

}

bool Cursor::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto sprite = this->getChildByTag(mCursorNum);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = this->getChildByTag(0);
	int y = (touch->getLocation().y + 60 > visibleSize.height) ? visibleSize.height - 40 : touch->getLocation().y + 20;
	sprite->setPosition(Vec2(touch->getLocation().x, y));
	sprite->runAction(FadeIn::create(0.2f));

	mTouchNow = 1;

	return true;
}

bool Cursor::moveEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto sprite = this->getChildByTag(mCursorNum);
	auto sprite = this->getChildByTag(0);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int y = (touch->getLocation().y + 60 > visibleSize.height) ? visibleSize.height - 40 : touch->getLocation().y + 20;
	sprite->setPosition(Vec2(touch->getLocation().x, y));

	return true;
}

bool Cursor::endEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	//auto sprite = this->getChildByTag(mCursorNum);
	auto sprite = this->getChildByTag(0);
	sprite->runAction(FadeOut::create(0.2f));

	mTouchNow = 0;

	return true;
}

void Cursor::setCursorNum(int i) {
	//Sprite* sprite1; 
	//if (mTouchNow) { 
	//	sprite1 = (Sprite *)this->getChildByTag(mCursorNum);
	//	sprite1->runAction(FadeOut::create(0.1f)); 
	//}

	auto rect = Rect(80 * i, 0, 80, 80);
	auto sprite = (Sprite*)this->getChildByTag(0);

	sprite->setTextureRect(rect);

	mCursorNum = i;

	//Sprite* sprite2;
	//if (mTouchNow) {
	//	sprite2 = (Sprite *)this->getChildByTag(mCursorNum);
	//	sprite2->runAction(FadeIn::create(0.1f));
	//	sprite2->setPosition(Vec2(sprite1->getPosition()));
	//}
}

int Cursor::getCursorNum() { return mCursorNum; }