#pragma  execution_character_set("utf-8")

#include "control.h"

#include "cursor.h"
#include "field.h"
#include "item.h"
#include "fieldDef.h"

USING_NS_CC;

Control* Control::me;

bool Control::init() {
	if (!Scene::init())
	{
		return false;
	}
	scheduleUpdate();

	me = this;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

//	auto closeItem = MenuItemImage::create(
//		"CloseNormal.png",
//		"CloseSelected.png",
//		[](Ref*sender) {
//		Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//		exit(0);
//#endif
//	});
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
//		origin.y + closeItem->getContentSize().height / 2));
//	// create menu, it's an autorelease object
//	auto menu = Menu::create(closeItem, NULL);
//	menu->setPosition(Vec2::ZERO);
//	this->addChild(menu, 1);

	auto cursor = Cursor::create();
	this->addChild(cursor, 4, "cursor");

	auto resetCursor = Layer::create();
	this->addChild(resetCursor, 10);

	initField();

	//auto field = Field::create();
	//this->addChild(field, 0);
	this->addChild(mFieldList["forest1"], 0, "field");

	auto item = Item::create();
	this->addChild(item, 2);

	auto msg = Label::create("", "fonts/APJapanesefontT.ttf", 30);
	msg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 50));
	msg->setColor(Color3B::WHITE);
	msg->setOpacity(0.0f);
	this->addChild(msg, 3, "msg");
	auto msgArea = Sprite::create("msgArea.png");
	msgArea->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	msgArea->setOpacity(0.0f);
	this->addChild(msgArea, 2, "msgArea");

	//カーソルの状態をリセットする
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event) {  setCursor(0); return true; };
	listener->onTouchMoved = [=](Touch* touch, Event* event) {	setCursor(0);};	
	listener->onTouchEnded = [=](Touch* touch, Event* event) {};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, resetCursor);

	return true;
}

void Control::update(float delta) {
	
}

void Control::setCursor(int num) {
	auto cursor = (Cursor*)this->getChildByName("cursor");
	if (num != cursor->getCursorNum()) cursor->setCursorNum(num);
}

void Control::changeField(std::string s) {
	auto field = (Field*)getChildByName("field");
	field->FadeOut();
	mFieldList[s]->FadeIn();
	addChild(mFieldList[s], 0, "field");
}

void Control::showMsg(std::string s) {
	auto msg = (Label*)getChildByName("msg");
	auto msgArea = getChildByName("msgArea");

	msg->setString(s);
	msg->runAction(Sequence::create(FadeIn::create(0.5f), FadeIn::create(3.0f), FadeOut::create(0.5f), NULL));
	msgArea->runAction(Sequence::create(FadeIn::create(0.5f), FadeIn::create(3.0f), FadeOut::create(0.5f), NULL));
}

void Control::showAI(std::string itemName) {
	auto ai = (AboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}

void Control::deleteAI() { removeChildByName("AboutItem"); }

bool Control::getExistObject(std::string field, std::string obj) {
	return mFieldList[field]->getExistObject(obj);
}

void Control::pauseField() {
	auto field = (Field*)getChildByName("field");
	field->pauseEventListener();
}

void Control::resumeField() {
	auto field = (Field*)getChildByName("field");
	field->resumeEventListener();
}