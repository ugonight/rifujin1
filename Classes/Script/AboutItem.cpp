#pragma  execution_character_set("utf-8")

#include "Script/fieldDef.h"

USING_NS_CC;

void AboutItem::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//オブジェクトを作っておく

	//クレヨン（緑）
	auto crayon = ObjectN::create();
	crayon->setTexture("item/crayon_g.png");
	crayon->setMsg("緑のクレヨンだ");
	crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	crayon->setArea(crayon->getBoundingBox());
	addObject(crayon, "crayon_g", 1, false);

	//卵
	auto egg = ObjectN::create();
	egg->setTexture("item/egg.png");
	egg->setMsg("鳥のたまごだ");
	egg->setScale(2.0f);
	egg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg->setArea(egg->getBoundingBox());
	addObject(egg, "egg", 1, false);

	//きのこ
	auto mushroom = ObjectN::create();
	mushroom->setTexture("item/mushroom_a.png");
	mushroom->setMsg("キノコだ。胞子がたくさんついている");
	mushroom->setPosition(visibleSize / 2);
	mushroom->setArea(mushroom->getBoundingBox());
	addObject(mushroom, "mushroom", 1, false);

	//松の葉
	auto matsu = ObjectN::create();
	matsu->setTexture("item/matsu_a.png");
	matsu->setMsg("松の葉の先を曲げた");
	matsu->setArea(matsu->getBoundingBox());
	matsu->setTouchEvent(CallFunc::create([this] {
		auto obj = (ObjectN*)mObjectList["matsu"];
		if (obj->getState() == 0) {
			obj->setTexture("item/matsu2_a.png");
			obj->setMsg("松の葉の先を曲げてある");
			obj->setState(1);
		}
	}));
	addObject(matsu, "matsu", 1, false);

}
void AboutItem::changedField(){}
void AboutItem::setAboutItem(std::string itemName) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->removeAllChildren();

	//ここにAboutItemの処理を書いていく
	if (itemName=="crayon_g") {
		addChild(mObjectList["crayon_g"]);
	}
	else if (itemName == "egg") {
		addChild(mObjectList["egg"]);
	}
	else if (itemName == "mushroom") {
		addChild(mObjectList["mushroom"]);
	}
	else if (itemName == "matsu") {
		addChild(mObjectList["matsu"]);
	}
}