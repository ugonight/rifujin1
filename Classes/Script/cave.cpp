#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Cave::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("cave.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "cave");

	auto forest3 = ObjectN::create();
	forest3->setArea(Rect(130, 430, 390, 50));
	forest3->setFieldChangeEvent("forest3");
	forest3->setCursor(2);
	addObject(forest3, "forest3", 2, true);
}

void Cave::changedField() {

}
