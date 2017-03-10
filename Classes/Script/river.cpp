#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void River::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("river_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "river_", 0, true);
	bg = ObjectN::create();
	bg->setTexture("river.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "river", 0, false);

	auto forest1 = ObjectN::create();
	forest1->setArea(Rect(0, 260, 70, 220));
	forest1->setFieldChangeEvent("forest1");
	forest1->setCursor(4);
	addObject(forest1, "forest1", 2, true);

	auto fishing = ObjectN::create();
	fishing->setArea(Rect(355, 255, 155, 225));
	fishing->setMsg("川だ。釣りができそうだ。");
	fishing->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "stick" &&
			Control::me->getField("AboutItem")->getObject("stick")->getState() == 2 &&
			mObjectList["fishing"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::BLACK);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("ぽちゃん…");
			novel->setCharaR("chara/suama1.png");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「…なにしてるの」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「いや、何か釣れるかなーと思って…」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「のんきに釣りなんかしてる場合！？」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「あ、なんかかかった」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「え、うそ！？」");
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->getItem("key2", Point(450, 130));
				mObjectList["fishing"]->setState(1);
			}));
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「カギが釣れたよ」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「うそーー！？！？」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(fishing, "fishing", 2, false);
}

void River::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (Control::me->getExistObject("campus", "blue") && getChildByName("river_")) {
		auto bg = getChildByName("river_");
		bg->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
		bg = mObjectList["river"];
		bg->setOpacity(0.0f);
		bg->runAction(FadeIn::create(0.5f));
		addChild(bg, 0, "river");
		addChild(mObjectList["fishing"], 3, "fishing");

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
