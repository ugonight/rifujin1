#pragma  execution_character_set("utf-8")

#include "Script/fieldDef.h"

USING_NS_CC;

void AboutItem::initField() {}	//最初は何も置かない
void AboutItem::changedField(){}
void AboutItem::setAboutItem(std::string itemName) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->removeAllChildren();

	//ここにAboutItemの処理を書いていく
	if (itemName=="crayon_g") {
		auto crayon = ObjectN::create();
		crayon->setTexture("item/crayon_g.png");
		crayon->setMsg("緑のクレヨンだ");
		crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		auto rect = crayon->getBoundingBox();
		crayon->setArea(rect.getMinX(), rect.getMinY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY());
		addObject(crayon, "crayon", 1, true);
	}
	else if (itemName == "egg") {
		auto egg = ObjectN::create();
		egg->setTexture("item/egg.png");
		egg->setMsg("鳥のたまごだ");
		egg->setScale(2.0f);
		egg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		auto rect = egg->getBoundingBox();
		egg->setArea(rect.getMinX(), rect.getMinY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY());
		addObject(egg, "egg", 1, true);
	}
}