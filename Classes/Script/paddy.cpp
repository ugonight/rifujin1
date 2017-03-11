#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Paddy::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("paddy_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "paddy_", 0, true);
	bg = ObjectN::create();
	bg->setTexture("paddy.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "paddy", 0, false);

	auto waterfalls = ObjectN::create();
	waterfalls->setArea(Rect(290, 370, 590, 110));
	waterfalls->setFieldChangeEvent("waterfalls");
	waterfalls->setCursor(2);
	addObject(waterfalls, "waterfalls", 2, true);
}

void Paddy::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (Control::me->getExistObject("campus", "yellow") && getChildByName("paddy_")) {
		auto bg = getChildByName("paddy_");
		bg->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
		bg = mObjectList["paddy"];
		bg->setOpacity(0.0f);
		bg->runAction(FadeIn::create(0.5f));
		addChild(bg, 0, "paddy");
		//addChild(mObjectList["fishing"], 3, "fishing");
		//addChild(mObjectList["waterfalls"], 3, "waterfalls");

		pauseEventListener();

		auto novel = Novel::create();

		novel->setCharaR("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「色がついて、ここで動けるようになったよ」");

		novel->setEndTask();
		this->addChild(novel, 0, "novel");

		/*}), NULL)));*/
	}
}
