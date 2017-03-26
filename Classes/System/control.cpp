#pragma  execution_character_set("utf-8")

#include "control.h"

#include "cursor.h"
#include "field.h"
#include "item.h"
#include "novel.h"
#include "Script/fieldDef.h"

USING_NS_CC;

Control* Control::me;

Control::~Control() {
	for (auto field : mFieldList) {
		CC_SAFE_RELEASE_NULL(field.second);
	}
}

bool Control::init() {
	if (!Scene::init())
	{
		return false;
	}
	scheduleUpdate();

	me = this;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto cursor = Cursor::create();
	this->addChild(cursor, 4, "cursor");

	auto resetCursor = Layer::create();
	this->addChild(resetCursor, 10);

	auto save = MenuItemImage::create(
		"save.png",
		"save2.png",
		CC_CALLBACK_1(Control::save, this));
	save->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	save->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y));
	auto menu = Menu::create(save, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1, "save");

	auto novel = Novel::create();
	novel->addSentence("");
	novel->setEndTask();
	novel->setLogOnly();
	addChild(novel, 1, "log");

	initField();

	//auto field = Field::create();
	//this->addChild(field, 0);
	this->addChild(mFieldList["forest1"], 0, "field");

	auto item = Item::create();
	this->addChild(item, 2, "item");

	auto msg = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 30);
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
	auto field = getChildByName("field");
	if (field->getChildByName("novel") && ((MenuItemImage*)getChildByName("save"))->getOpacity() >= 255) {
		((MenuItemImage*)getChildByName("save"))->setOpacity(0.0f);
		
		removeChildByName("log");
	}
	else if (!field->getChildByName("novel")) {
		((MenuItemImage*)getChildByName("save"))->setOpacity(255.0f);
		
		if (!getChildByName("log")) {
			auto novel = Novel::create();
			novel->addSentence("");
			novel->setEndTask();
			novel->setLogOnly();
			addChild(novel, 1, "log");
		}
	}
}

void Control::save(cocos2d::Ref* pSender) {
	if ((getChildByName("save"))->getOpacity() >= 255) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto path = FileUtils::getInstance()->getWritablePath();

		//現在いるフィールド&取得しているアイテム
		auto file = path + "saveData.plist";
		ValueMap data;

		for (auto field : mFieldList) {
			if (field.second->getReferenceCount() > 1 && field.first != "AboutItem") {
				data["currentField"] = field.first;
				break;
			}
		}
		auto item = (Item*)getChildByName("item");
		item->saveItem(&data);

		if (FileUtils::getInstance()->writeToFile(data, file))
		{
			CCLOG("データを%sに書き出しました。", file.c_str());
		}
		else
		{
			CCLOG("Ops!");
		}

		//フィールドごとのオブジェクトの状態
		for (auto field : mFieldList) {
			file = path + field.first + ".plist";
			if (FileUtils::getInstance()->writeToFile(((Field*)field.second)->saveField(), file))
			{
				CCLOG("データを%sに書き出しました。", file.c_str());
			}
			else
			{
				CCLOG("Ops!");
			}
		}

		auto label = Label::createWithTTF("セーブが完了しました", "fonts/APJapanesefontT.ttf", 20);
		label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		label->setPosition(Vec2(origin.x + visibleSize.width - 15 - 64, origin.y));
		label->setTextColor(Color4B::WHITE);
		label->enableOutline(Color4B::BLACK, 2);
		label->setOpacity(0.0f);
		label->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(3.0f), FadeOut::create(0.5f), NULL));
		addChild(label, 5, "saveText");
	}
}

void Control::load() {
	auto path = FileUtils::getInstance()->getWritablePath();

	//現在いるフィールド&取得しているアイテム
	auto file = path + "saveData.plist";

	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);
	if (data["currentField"].asString() != "forest1")
		changeField(data["currentField"].asString());

	auto item = (Item*)getChildByName("item");
	item->loadItem(data);

	//フィールドごとのオブジェクトの状態
	for (auto field : mFieldList) {
		file = path + field.first + ".plist";
		data.clear();
		data = FileUtils::getInstance()->getValueMapFromFile(file);
		field.second->loadField(data);
	}
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

Field* Control::getField(std::string field) {
	return mFieldList[field];
}

void Control::pauseField() {
	auto field = (Field*)getChildByName("field");
	field->pauseEventListener();
}

void Control::resumeField() {
	auto field = (Field*)getChildByName("field");
	field->resumeEventListener();
}