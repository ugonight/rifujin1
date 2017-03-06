#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Field1::initField() {
	//if (!Layer::init())
	//{
	//	return false;
	//}
	//scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("forest1_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg,"forest_", 0, true);
	bg = ObjectN::create();
	bg->setTexture("forest1.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "forest", 0, false);

	auto area = ObjectN::create();
	area->setArea(Rect(650, 300, 100, 100));
	area->setItemGetEvent("crayon_g");
	area->setMsg("クレヨン（緑）を手に入れた");
	//this->addChild(area, 1, "crayon_g");
	area->setTouchEvent(CallFunc::create([this] {
		pauseEventListener();
	
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/tuguru1.png");
		novel->addSentence("継「アイテムを手に入れたよ」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「では、アイテムの使い方をご説明します」");
		novel->setCharaR("");
		novel->setCharaC("tutorial3.png");
		novel->addSentence("セリーヌ「左上にあるピンクの枠をタップすると取得しているアイテムの一覧が出てきます」");
		novel->addSentence("セリーヌ「そのまま左にスライドして使いたいアイテムの上で離します」");
		novel->addSentence("セリーヌ「ピンクの枠にアイテムがセットされますので、画面上の使いたい場所でタップするとアイテムが使えます」");
		novel->setCharaC("tutorial4.png");
		novel->addSentence("セリーヌ「また、ピンクの枠の上で長押しすると、アイテムを拡大して見ることができます。」");
		novel->addSentence("セリーヌ「拡大したアイテムにアイテムを使うことができるときがありますので、お試しください。」");
		novel->setCharaC("");
		novel->setCharaR("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「よし、早速使ってみよう」");
		novel->addSentence("継「あそこの樹に張り付いてる画用紙に使えないかな？」");

		novel->setEndTask();
		this->addChild(novel, 0, "novel");
	}));
	addObject(area, "crayon_g", 1, true);

	auto campus = ObjectN::create();
	campus->setArea(Rect(365, 230, 90, 55));
	campus->setFieldChangeEvent("campus");
	//this->addChild(area, 1, "crayon_g");
	addObject(campus, "campus", 1, true);

	auto forest2 = ObjectN::create();
	forest2->setArea(Rect(0, 0, 80, 480));
	forest2->setFieldChangeEvent("forest2");
	forest2->setCursor(4);
	addObject(forest2, "forest2", 2, false);

	auto river = ObjectN::create();
	river->setArea(Rect(770, 0, 80, 480));
	river->setFieldChangeEvent("river");
	river->setCursor(3);
	addObject(river, "river", 2, false);

	//return true;
}

void Field1::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (Control::me->getExistObject("campus","green") && getChildByName("forest_")) {
		auto bg = getChildByName("forest_");
		bg->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
		bg = mObjectList["forest"];
		bg->setOpacity(0.0f);
		bg->runAction(FadeIn::create(0.5f));
		addChild(bg, 0, "forest");
		addChild(mObjectList["forest2"], 2, "forest2");
		addChild(mObjectList["river"], 2, "river");

		//this->runAction(Sequence::create(
		//	FadeIn::create(1.0f),
		//	CallFunc::create(CallFunc::create([this] {
			pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::RED);
			novel->setCharaC("chara/suama1.png");
			novel->addSentence("寿甘「辺りに色がついたよ！」");
			novel->addSentence("寿甘「身体も自由に動かせられる！」");
			novel->setCharaR("chara/tuguru1.png");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「この調子で辺りを散策してみよう」");

			novel->setEndTask();
			this->addChild(novel, 0, "novel");

		/*}), NULL)));*/
	}
}

void Field2::initField() {
	//if (!Layer::init())
	//{
	//	return false;
	//}
	scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("campus.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	auto line = Sprite::create("campus_line.png");
	line->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(line, 10);

	auto green = ObjectN::create();
	green->setTexture("campus_g.png");
	green->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addObject(green, "green", 1, false);

	auto blue = ObjectN::create();
	blue->setTexture("campus_b.png");
	blue->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addObject(blue, "blue", 1, false);

	auto back = ObjectN::create();
	back->setArea(Rect(0, 400, 854, 80));
	back->setFieldChangeEvent("forest1");
	back->setCursor(2);
	//this->addChild(area, 1, "crayon_g");
	addObject(back, "back", 2, true);

	auto draw = ObjectN::create();
	draw->setArea(Rect(10, 80, 844, 220));
	draw->setMsg("絵が描かれている");
	draw->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "crayon_g") {
			mObjectList["green"]->setOpacity(0.0f);
			mObjectList["green"]->runAction(FadeIn::create(0.5f));
			addChild(mObjectList["green"], 1, "green");
			Item::sharedItem()->deleteItem("crayon_g");

			Control::me->showMsg("絵に緑のクレヨンで色を塗った");
		}
		else if (Item::sharedItem()->getSelectedItem() == "crayon_b") {
			mObjectList["blue"]->setOpacity(0.0f);
			mObjectList["blue"]->runAction(FadeIn::create(0.5f));
			addChild(mObjectList["blue"], 1, "blue");
			Item::sharedItem()->deleteItem("crayon_b");

			Control::me->showMsg("絵に青のクレヨンで色を塗った");
		}
	}));
	addObject(draw, "draw", 2, 1);


	//return true;
}

void Field2::changedField() {}