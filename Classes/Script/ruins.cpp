#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Ruins::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("ruins.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "ruins", 0, true);

	auto forestD = ObjectN::create();
	forestD->setArea(Rect(50, 430, 530, 50));
	forestD->setFieldChangeEvent("forestD");
	forestD->setCursor(2);
	addObject(forestD, "forestD", 2, true);


	auto door = ObjectN::create();
	door->setArea(Rect(390, 290, 170, 120));
	door->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["door"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();
			novel->setFontColor(Color3B::RED);
			novel->setCharaR("chara/suama1.png");
			novel->addSentence("寿甘「ここが…マリアちゃんのおうちかな…」");
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「表札にミルフィーユって書いてあるね」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「きっとここにあるはずよね、クレヨン。」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「ちょっと怖いけど、入ろう。」");
			novel->addEvent(CallFunc::create([this] {
				mObjectList["door"]->setState(1);
				mObjectList["door"]->setFieldChangeEvent("living");
			}));
			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(door, "door", 2, true);

	auto letter = ObjectN::create();
	letter->setArea(Rect(680, 430, 70, 50));
	letter->setItemGetEvent("letter");
	letter->setMsg("中に手紙が入っていた");
	addObject(letter, "letter", 2, true);

	auto box = ObjectN::create();
	box->setArea(Rect(100, 380, 100, 60));
	box->setItemGetEvent("box");
	box->setMsg("草むらに木箱が落ちていた");
	addObject(box, "box", 2, true);

}

void Ruins::changedField() {
}

void Living::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("living.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "living", 0, true);
	bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("living_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "living_", 0, false);

	auto ruins = ObjectN::create();
	ruins->setArea(Rect(0, 430, 500, 50));
	ruins->setFieldChangeEvent("ruins");
	ruins->setCursor(2);
	addObject(ruins, "ruins", 2, true);

	auto room = ObjectN::create();
	room->setArea(Rect(800, 0, 54, 400));
	room->setFieldChangeEvent("room");
	room->setCursor(3);
	addObject(room, "room", 2, true);

}

void Living::changedField() {
}

void Room::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("mariasroom.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "room", 0, true);

	auto living= ObjectN::create();
	living->setArea(Rect(50, 450, 530, 30));
	living->setFieldChangeEvent("living");
	living->setCursor(2);
	addObject(living, "living", 2, true);


	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用

}

void Room::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (getChildByName("first")) {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「なに…これ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「ここが彼女の部屋かな…すごい数の画用紙が散らばっているね」");
		novel->addSentence("継「マリアちゃんは絵を描くのが好きだったのかな」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「…よく見て」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「…？」");
		novel->setBg("chara/scene6.png");
		novel->addSentence("継「これは…色が不自然だね…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「な、なんのためにこんな気持ち悪い絵を描くのよ…！」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「他人の趣向を否定するのはよくないよ…でも一体どうしてわざわざ違う色で絵を描いていたのか…不思議だね」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}