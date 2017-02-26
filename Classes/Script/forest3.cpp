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
	forest2->setArea(Rect(200, 430, 400, 50));
	forest2->setFieldChangeEvent("forest2");
	forest2->setCursor(2);
	addObject(forest2, "forest2", 2, true);

	auto matsu = ObjectN::create();
	matsu->setArea(Rect(540, 200, 280, 100));
	matsu->setTouchEvent(CallFunc::create([this] {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「いたっ」");
		novel->addSentence("継「なにか頭に刺さった…」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/celine1.png");
		novel->addSentence("セリーヌ「これは…松の葉みたいですね」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「使えるかもしれないから持っておこうか」");
		novel->addEvent(CallFunc::create([this] {
			Item::sharedItem()->getItem("matsu", Point(680, 250));
			removeChildByName("matsu");
		}));
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("松の葉を手に入れた");

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}));
	addObject(matsu, "matsu", 2, true);

	auto stick = ObjectN::create();
	stick->setTexture("stick.png");
	stick->setArea(Rect(520, 390, 140, 60));
	stick->setItemGetEvent("stick");
	stick->setMsg("木の棒を手に入れた");
	addObject(stick, "stick", 3, true);
}

void Forest3::changedField() {

}
