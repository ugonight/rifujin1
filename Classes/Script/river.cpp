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

	auto waterfalls = ObjectN::create();
	waterfalls->setArea(Rect(770, 0, 110, 240));
	waterfalls->setFieldChangeEvent("waterfalls");
	waterfalls->setCursor(3);
	addObject(waterfalls, "waterfalls", 2, false);

	auto fishing = ObjectN::create();
	fishing->setArea(Rect(355, 255, 155, 225));
	fishing->setMsg("川だ。釣りができそうだ。");
	fishing->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "stick" &&
			Control::me->getField("AboutItem")->getObject("stick")->getState() == 2 &&
			mObjectList["fishing"]->getState() == 0) {
			//pauseEventListener();

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
		addChild(mObjectList["waterfalls"], 3, "waterfalls");

		//pauseEventListener();

		auto novel = Novel::create();

		novel->setCharaR("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「色がついて、ここで動けるようになったよ」");

		novel->setEndTask();
		this->addChild(novel, 0, "novel");

		/*}), NULL)));*/
	}
}

void WaterFalls::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("waterfalls.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "waterfalls", 0, true);

	auto river = ObjectN::create();
	river->setArea(Rect(0, 100, 100, 250));
	river->setFieldChangeEvent("river");
	river->setCursor(4);
	addObject(river, "river", 2, true);

	auto paddy = ObjectN::create();
	paddy->setArea(Rect(750, 100, 100, 250));
	paddy->setFieldChangeEvent("paddy");
	paddy->setCursor(3);
	addObject(paddy, "paddy", 2, false);


	auto stone = ObjectN::create();
	stone->setArea(Rect(20, 390, 120, 90));
	stone->setTexture("stone1.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 1,2,4 };
		switchStone(switchList);
	}));
	addObject(stone, "stone1", 3, true);

	stone = ObjectN::create();
	stone->setArea(Rect(170, 390, 120, 90));
	stone->setOpacity(0.0f);
	stone->setTexture("stone2.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 2,4,6 };
		switchStone(switchList);
	}));
	addObject(stone, "stone2", 3, true);

	stone = ObjectN::create();
	stone->setArea(Rect(320, 390, 120, 90));
	stone->setOpacity(0.0f);
	stone->setTexture("stone3.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 3,5,2 };
		switchStone(switchList);
	}));
	addObject(stone, "stone3", 3, true);

	stone = ObjectN::create();
	stone->setArea(Rect(470, 390, 120, 90));
	stone->setOpacity(0.0f);
	stone->setTexture("stone4.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 4,6,5 };
		switchStone(switchList);
	}));
	addObject(stone, "stone4", 3, true);

	stone = ObjectN::create();
	stone->setArea(Rect(610, 390, 120, 90));
	stone->setTexture("stone5.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 5,1,3 };
		switchStone(switchList);
	}));
	addObject(stone, "stone5", 3, true);

	stone = ObjectN::create();
	stone->setArea(Rect(740, 390, 120, 90));
	stone->setOpacity(0.0f);
	stone->setTexture("stone6.png");
	stone->setTouchEvent(CallFunc::create([this] {
		int switchList[3] = { 6,3,1 };
		switchStone(switchList);
	}));
	addObject(stone, "stone6", 3, true);


	auto waterfalls_ = ObjectN::create();
	waterfalls_->setTexture("waterfalls_.png");
	waterfalls_->setArea(Rect(300, 130, 300, 170));
	waterfalls_->setPosition(visibleSize / 2);
	waterfalls_->setOpacity(0.0f);
	waterfalls_->setMsg("滝だ");
	waterfalls_->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "scroll") {
			//pauseEventListener();

			auto novel = Novel::create();
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaR("chara/tuguru1.png");
			novel->addSentence("継「呪文を唱えてみよう」");
			novel->addSentence("継「アブラカタブラナンマイダー！」");
			novel->setCharaL("chara/bandana1.png");
			novel->addSentence("バンダナ「見事な呪文のダサさに驚きを隠せない」");
			novel->setFontColor(Color3B::BLACK);
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->deleteItem("scroll");
				mObjectList["waterfalls_"]->runAction(FadeIn::create(4.0f));
				mObjectList["waterfalls_"]->setState(1);
			}));
			novel->addSentence("ゴゴゴゴゴゴゴゴ…");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("バンダナ「おおおお！！呪文はともかく仕掛けはすげえ！！！」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
		else if (mObjectList["waterfalls_"]->getState() == 1) {
			Item::sharedItem()->getItem("sword", Point(440, 180));
			Control::me->showMsg("伝説の剣を手に入れた");
			mObjectList["waterfalls_"]->setState(2);
		}
	}));
	addObject(waterfalls_, "waterfalls_", 3, true);

	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用
}

void WaterFalls::changedField() {
	if (getChildByName("first")) {
		//pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaR("chara/tuguru1.png");
		novel->addSentence("継「飛び石の間隔が広すぎて渡れない…」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「飛び石を出し入れすることができるみたいですね」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「上手く全部の飛び石を出すことができるかな…？」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}

void WaterFalls::switchStone(int *list) {
		std::stringstream name;
		for (int i = 0; i < 3; i++) {
			name.str(""); name.clear();
			name << "stone"  << list[i];
			Action* action = DelayTime::create(0.0);	//何もしない
			if (mObjectList[name.str()]->getOpacity() == 0 || mObjectList[name.str()]->getOpacity() == 255) {	//完全に切り替わってたら
				if (mObjectList[name.str()]->getOpacity() > 0) {
					action = FadeOut::create(0.3f);
				}
				else {
					action = FadeIn::create(0.3f);
				}
			}

			if (i == 0) {
				mObjectList[name.str()]->runAction(Sequence::create(
					(FiniteTimeAction*)action, 
					CallFunc::create(CC_CALLBACK_0(WaterFalls::judge,this)),
					NULL));
			}
			else {
				mObjectList[name.str()]->runAction(action);
			}
		}
}

void WaterFalls::judge() {
		bool complete = true;
		std::stringstream name;
		for (int i = 1; i < 7; i++) {
			//std::string name = "stone" + std::to_string(i);
			name.str(""); name.clear();
			name << "stone" << i;
			if ((int)mObjectList[name.str()]->getOpacity() < 200) complete = false;
		}

		if (complete && !getChildByName("paddy")) {
			//pauseEventListener();

			auto novel = Novel::create();
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaR("chara/tuguru1.png");
			novel->addSentence("継「飛び石を全部出せたよ！」");
			novel->setCharaL("chara/bandana1.png");
			novel->addSentence("バンダナ「これで先に進めるな！」");
			novel->addEvent(CallFunc::create([this] {
				addChild(mObjectList["paddy"], 3, "paddy");
			}));

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
}