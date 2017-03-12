#pragma  execution_character_set("utf-8")

#include "fieldDef.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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

	auto garden = ObjectN::create();
	garden->setArea(Rect(360, 170, 280, 210));
	garden->setFieldChangeEvent("garden");
	garden->setCursor(6);
	addObject(garden, "garden", 2, false);

	auto scarecrow = ObjectN::create();
	scarecrow->setArea(Rect(80, 150, 190, 150));
	scarecrow->setMsg("かかしがある");
	scarecrow->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "pen" &&
			mObjectList["scarecrow"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();
			novel->setCharaR("chara/suama1.png");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「この子顔がないよ、描いてあげよう」");
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->deleteItem("pen");
				mObjectList["scarecrow"]->setState(1);
				mObjectList["face"]->runAction(FadeIn::create(0.5f));
				addChild(mObjectList["garden"], 3, "garden");
			}));
			novel->setCharaC("chara/bandana1.png");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("バンダナ「ハンサムだなおい」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「お礼に道案内してくれるって！」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("バンダナ「まんざらでもないのな」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「これで先に進めるね！」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(scarecrow, "scarecrow", 2, true);

	auto face = ObjectN::create();
	face->setTexture("face.png");
	face->setPosition(visibleSize / 2);
	face->setOpacity(0.0f);
	addObject(face, "face", 2, true);

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

		novel->setCharaL("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「色がついて、ここで動けるようになったよ」");
		novel->setCharaC("chara/girl1.png");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("謎の少女「ようやくここまで来たのね」");
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「あー！忘れた頃にー！どこ行ってたのよー！」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「もうそろそろ教えてくれてもいいんじゃないかな、君がだれなのか、何をしたいのか」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("謎の少女「そうね…私はマリアちゃんのお友達、やりたいことは…おそらくあなたたちと一緒」");
		novel->addSentence("寿甘「マリアちゃんのこと知ってるの！？…それにしても、こんな子学校にいたかな…」");
		novel->addSentence("謎の少女「…ああ。行かなきゃ」");
		novel->setCharaC("");
		novel->addSentence("寿甘「あーもう！だから待ってってばー！！」");
		novel->setCharaL("");
		novel->setCharaR("");
		novel->setBg("bg/black.png");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("　");
		novel->setCharaR("chara/malice1.png");
		novel->addSentence("？？？「…」");
		novel->setBg("");
		novel->setCharaR("chara/suama1.png");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「ちょっと…いつまで歩くのよ…」");
		novel->addSentence("寿甘「ていうか、戻ってきてない？」");
		novel->setCharaL("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「あれ、おかしいな…」");

		novel->setEndTask();
		this->addChild(novel, 0, "novel");

		/*}), NULL)));*/
	}
}

void Garden::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();
	bg->setTexture("garden.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "garden", 0, true);

	auto paddy = ObjectN::create();
	paddy->setArea(Rect(320, 420, 280, 60));
	paddy->setFieldChangeEvent("paddy");
	paddy->setCursor(2);
	addObject(paddy, "paddy", 2, true);

	auto girl = ObjectN::create();
	girl->setTexture("girl_hurt.png");
	girl->setPosition(visibleSize / 2);
	girl->setArea(Rect(250, 50, 300, 350));
	girl->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() != "") {
			Control::me->showMsg("さすがにそれでは太刀打ちできない");
		}
	}));
	addObject(girl, "girl", 3, true);


	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用
}

void Garden::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (getChildByName("first")) {
		pauseEventListener();

		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/misery.ogg",true);

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「キャーーーーー！！！」");
		novel->addSentence("寿甘「あの子が倒れてる！…ていうかなんなのよ！この怪物…！」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("？？？「ﾋｿﾋｿ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「早く助けてあげないと…ど、どうしよう…」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}
