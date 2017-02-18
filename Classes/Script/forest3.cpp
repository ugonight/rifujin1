#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Forest3::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("forest3.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "forest3");

	auto forest2 = ObjectN::create();
	forest2->setArea(200, 430, 400, 50);
	forest2->setFieldChangeEvent("forest2");
	forest2->setCursor(2);
	addObject(forest2, "forest2", 2, true);
}

void Forest3::changedField() {

}
