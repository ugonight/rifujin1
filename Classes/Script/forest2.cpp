#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Forest2::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("forest2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "forest2");

	auto forest1 = ObjectN::create();
	forest1->setArea(774, 240, 80, 240);
	forest1->setFieldChangeEvent("forest1");
	forest1->setCursor(3);
	addObject(forest1, "forest1", 2, true);

	auto forest3 = ObjectN::create();
	forest3->setArea(150, 180, 150, 120);
	forest3->setFieldChangeEvent("forest3");
	forest3->setCursor(6);
	addObject(forest3, "forest3", 2, true);

	auto egg = ObjectN::create();
	egg->setArea(760, 200, 80, 50);;
	egg->setTexture("egg.png");
	egg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg->setTouchEvent(CallFunc::create([this] {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/suama1.png");
		novel->addSentence("寿甘「あー！みてみて！鳥のたまごがあるよ！！」");
		novel->addSentence("寿甘「…って」");
		novel->setCharaC("chara/scene1.png");
		novel->addSentence("寿甘「キャーー！！ヘビーーーー！！！」");
		novel->addSentence("寿甘「だ、誰かやっつけてよぉ…」");
		novel->setCharaL("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「とりあえず、一旦たまごを退避させておこうか…」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("egg");
			addChild(mObjectList["egg_"], 3, "egg_");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}));
	addObject(egg, "egg", 3, true);

	auto egg_ = ObjectN::create();
	egg_->setArea(760, 200, 80, 50);;
	egg_->setTexture("egg.png");
	egg_->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg_->setItemGetEvent("egg");
	egg_->setMsg("鳥のたまごを手に入れた");
	addObject(egg_, "egg_", 3, false);

	auto mushroom = ObjectN::create();
	mushroom->setArea(40, 370, 50, 90);
	mushroom->setTexture("mushroom.png");
	mushroom->setPosition(visibleSize / 2);
	mushroom->setItemGetEvent("mushroom");
	mushroom->setMsg("キノコを手に入れた");
	addObject(mushroom, "mushroom", 3, true);

}

void Forest2::changedField() {

}
