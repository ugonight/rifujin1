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

	auto sign = ObjectN::create();
	sign->setArea(Rect(700, 190, 70, 190));
	sign->setMsg("でこぼこしている");
	sign->setOpacity(0.0f);
	sign->setTexture("sign.png");
	sign->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "mushroom") {
			mObjectList["sign"]->runAction(FadeIn::create(1.0f));
			mObjectList["sign"]->setMsg("矢印が浮かび上がっている");
			Item::sharedItem()->deleteItem("mushroom");
			Control::me->showMsg("岩肌にきのこの胞子を付けた");
		}
	}));
	addObject(sign, "sign", 2, true);

	auto web = ObjectN::create();
	web->setArea(Rect(240, 85, 60, 35));
	web->setMsg("クモの巣だ。糸がかなり頑丈なようだ。");
	web->setTouchEvent(CallFunc::create([this] {
		auto stick = Control::me->getField("AboutItem")->getObject("stick");
		if (Item::sharedItem()->getSelectedItem() == "stick" &&
			stick->getState() == 0) {
			stick->setTexture("item/stick_yarn_a.png");
			stick->setState(1);
			Control::me->showMsg("木の棒にクモの糸を付けた");
		}
	}));
	addObject(web, "web", 2, true);

	auto entrance = ObjectN::create();
	entrance->setArea(Rect(255, 170, 215, 190));
	entrance->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "lamp") {
			if (Control::me->getField("AboutItem")->getObject("lamp")->getState() == 1) {
				Control::me->changeField("cave_in");
			}
			else {
				Control::me->showMsg("ランプが消えている");
			}
		}
		else {
			Control::me->showMsg("暗くて入るのは危険だ");
		}
	}));
	addObject(entrance, "entrance", 2, true);

	auto girl = ObjectN::create();
	addObject(girl, "girl", 0, true);	//フラグ用
}

void Cave::changedField() {
	if (getChildByName("girl")) {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「流石にここに入るのは…」");
		novel->setCharaC("chara/girl1.png");
		novel->addSentence("寿甘「あ…」");
		novel->addSentence("謎の少女「…こっち」");
		novel->setCharaC("");
		novel->addSentence("寿甘「ちょ…まっ…！」");
		novel->addSentence("寿甘「…行くしかないのね…」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("girl");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}


void CaveIn::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("cave_in.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "bg");

	auto entrance = ObjectN::create();
	entrance->setArea(Rect(60, 430, 660, 50));
	entrance->setFieldChangeEvent("cave");
	entrance->setCursor(2);
	addObject(entrance, "cave", 2, true);

	auto left = ObjectN::create();
	left->setArea(Rect(60, 145, 120, 175));
	left->setTouchEvent(CallFunc::create([this] {
		getChildByName("bg")->runAction(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), NULL));
		if (mCount == 3) {
			mCount++;
		}
		else {
			mCount = 0;
		}
	}));
	addObject(left, "left", 2, true);

	auto forward = ObjectN::create();
	forward->setArea(Rect(360, 120, 150, 180));
	forward->setTouchEvent(CallFunc::create([this] {
		getChildByName("bg")->runAction(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), NULL));
		if (mCount == 2) {
			mCount++;
		}
		else {
			mCount = 0;
		}
	}));
	addObject(forward, "forward", 2, true);

	auto right = ObjectN::create();
	right->setArea(Rect(700, 120, 120, 175));
	right->setTouchEvent(CallFunc::create([this] {
		if (mCount == 0 || mCount == 1) {
			getChildByName("bg")->runAction(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), NULL));
			mCount++;
		}
		else if (mCount == 4) {
			Control::me->changeField("cave_end");
		}
		else {
			getChildByName("bg")->runAction(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), NULL));
			mCount = 0;
		}
	}));
	addObject(right, "right", 2, true);

}

void CaveIn::changedField() {
	mCount = 0;
}

void CaveEnd::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("cave_end.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "bg");

	auto entrance = ObjectN::create();
	entrance->setArea(Rect(60, 430, 660, 50));
	entrance->setFieldChangeEvent("cave");
	entrance->setCursor(2);
	addObject(entrance, "cave", 2, true);

	auto keyhole = ObjectN::create();
	keyhole->setArea(Rect(225, 230, 85, 60));
	keyhole->setMsg("鍵穴らしきものがある");
	keyhole->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "key2") {
			Item::sharedItem()->getItem("seed", Point(270, 260));
			Control::me->showMsg("中に植物のタネが入っていた");
			Item::sharedItem()->deleteItem("key2");
		}
	}));
	addObject(keyhole, "keyhole", 2, true);

	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用
}

void CaveEnd::changedField() {
	if (getChildByName("first")) {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/bandana1.png");
		novel->addSentence("バンダナ「行き止まり！？」");
		novel->addSentence("バンダナ「ここにきてそんなのって…・」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}
