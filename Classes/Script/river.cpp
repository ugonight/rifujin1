#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void River::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("river_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "river_", 0, true);
	bg = ObjectN::create();
	bg->setTexture("river.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "river", 0, false);

	auto forest1 = ObjectN::create();
	forest1->setArea(Rect(0, 260, 70, 120));
	forest1->setFieldChangeEvent("forest1");
	forest1->setCursor(4);
	addObject(forest1, "forest1", 2, true);
}

void River::changedField() {

}
