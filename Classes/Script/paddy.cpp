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
	waterfalls->setArea(Rect(290, 400, 590, 80));
	waterfalls->setFieldChangeEvent("waterfalls");
	waterfalls->setCursor(2);
	addObject(waterfalls, "waterfalls", 2, true);

	auto garden = ObjectN::create();
	garden->setArea(Rect(360, 170, 280, 150));
	garden->setFieldChangeEvent("garden");
	garden->setCursor(6);
	addObject(garden, "garden", 2, false);

	auto scarecrow = ObjectN::create();
	scarecrow->setArea(Rect(80, 150, 190, 150));
	scarecrow->setMsg("かかしがある");
	scarecrow->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "pen" &&
			mObjectList["scarecrow"]->getState() == 0) {
			//pauseEventListener();

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

	auto malice = ObjectN::create();
	malice->setTexture("chara/malice1.png");
	malice->setScale(0.5f);
	malice->setPosition(500, 250);
	malice->setOpacity(0.0f);
	addObject(malice, "malice", 3, false);
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

		//pauseEventListener();

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
		novel->addSentence("モゾモゾモゾモゾ…");
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
		this->addChild(novel, 10, "novel");

		/*}), NULL)));*/
	}
	else if (Control::me->getField("room")->getObject("pass")->getState() == 1 &&
		!getChildByName("malice")) {
		mObjectList["malice"]->runAction(FadeIn::create(0.2f));
		mObjectList["malice"]->runAction(ScaleBy::create(10.0f, 2.0f));
		addChild(mObjectList["malice"], 3, "malice");
		mObjectList["garden"]->setMsg("戻っている場合ではない");
		mObjectList["garden"]->setFieldChangeEvent("");
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

	auto forestD = ObjectN::create();
	forestD->setArea(Rect(300, 50, 300, 180));
	forestD->setFieldChangeEvent("forestD");
	forestD->setCursor(6);
	addObject(forestD, "forestD", 2, false);

	auto girl = ObjectN::create();
	girl->setTexture("girl_hurt.png");
	girl->setPosition(visibleSize / 2);
	girl->setArea(Rect(250, 50, 300, 350));
	girl->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() != "" ) {
			if (Item::sharedItem()->getSelectedItem() == "sword") {
				//pauseEventListener();

				auto novel = Novel::create();
				novel->setFontColor(Color3B::BLUE);
				novel->setCharaR("chara/bandana1.png");
				novel->addSentence("バンダナ「…ここは俺が引き受ける」");
				novel->addSentence("バンダナ「おぅら！！かかってこいや！！！」");
				novel->setCharaR("");
				novel->setFontColor(Color3B::BLACK);
				novel->setBg("chara/scene5.png");
				novel->addSentence("");
				novel->addSentence("カキーン！");
				novel->setFontColor(Color3B::BLUE);
				novel->addSentence("バンダナ「クソッ…なんだその玉は！卑怯なもん使いやがって…！」");
				novel->addSentence("バンダナ「俺様をなめんじゃねぇぇええええ！！！！」」");
				novel->addSentence("バンダナ「つぐるん！早くその子を連れて逃げろ！！」");
				novel->addSentence("継「うん、わかった。あとは頼むよ…！」");
				novel->addEvent(CallFunc::create([this] {
					Item::sharedItem()->deleteItem("sword");
					mObjectList["girl"]->setState(1);
					mObjectList["girl"]->runAction(Sequence::create(FadeOut::create(2.0f), RemoveSelf::create(), NULL));
					addChild(mObjectList["forestD"], 2, "forestD");
				}));

				novel->setEndTask();
				this->addChild(novel, 10, "novel");
			}
			else {
				Control::me->showMsg("さすがにそれでは太刀打ちできない");
			}
		}
		else {
			if (mObjectList["girl"]->getState() == 0)Control::me->showMsg("少女が襲われている");
		}
	}));
	addObject(girl, "girl", 3, true);

	auto malice = ObjectN::create();
	malice->setTexture("chara/malice1.png");
	malice->setScale(0.5f);
	malice->setPosition(visibleSize / 2);
	malice->setOpacity(0.0f);
	addObject(malice, "malice", 3, false);

	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用
	auto second = ObjectN::create();
	addObject(second, "second", 0, true);	//フラグ用
}

void Garden::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (getChildByName("first")) {
		//pauseEventListener();

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
	}else if (Control::me->getField("room")->getObject("pass")->getState() == 1 &&
		getChildByName("second")) {
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("ドカッ");
		novel->setCharaR("chara/malice1.png");
		novel->addSentence("モゾモゾモゾ…");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/bandana1.png");
		novel->addSentence("バンダナ「うぐ…ッ」");
		novel->addSentence("バンダナ「な、なんだコイツ…埒があかねえ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaC("chara/tuguru1.png");
		novel->addSentence("継「無事かー！バンダナー！！」");
		novel->addSentence("バンダナ「くッ…遅かったじゃねえか！早くいくぞ！」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("second");
			mObjectList["malice"]->runAction(FadeIn::create(0.2f));
			mObjectList["malice"]->runAction(ScaleBy::create(10.0f, 2.0f));
			addChild(mObjectList["malice"], 3, "malice");
			mObjectList["forestD"]->setMsg("戻っている場合ではない");
			mObjectList["forestD"]->setFieldChangeEvent("");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}


void DeadForest::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();
	bg->setTexture("deadforest.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "deadforest", 0, true);

	auto paddy = ObjectN::create();
	paddy->setArea(Rect(320, 420, 280, 60));
	paddy->setFieldChangeEvent("garden");
	paddy->setCursor(2);
	addObject(paddy, "garden", 2, true);

	auto ruins = ObjectN::create();
	ruins->setArea(Rect(0, 130, 250, 150));
	ruins->setFieldChangeEvent("ruins");
	ruins->setCursor(6);
	addObject(ruins, "ruins", 2, true);

	auto tongs = ObjectN::create();
	tongs->setArea(Rect(500, 340, 160, 90));
	tongs->setItemGetEvent("tongs");
	tongs->setMsg("トングが落ちていた");
	addObject(tongs, "tongs", 2, true);


	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用
	auto second = ObjectN::create();
	addObject(second, "second", 0, true);	//フラグ用
}

void DeadForest::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (getChildByName("first")) {
		//pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/girl1.png");
		novel->addSentence("少女「はぁ…はぁ…」");
		novel->setCharaC("chara/celine1.png");
		novel->addSentence("セリーヌ「大丈夫ですか…？」");
		novel->addSentence("セリーヌ「ひとまずここまでくれば安全でしょう。…少し休みましょう。」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「大分景色が変わってきたね…さっきのはなんだったんだろう」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("少女「…あいつが…この世界を壊しているの……」");
		novel->addSentence("少女「私には………せめて形だけでも繕って…………慰めることしかできないのに………」");
		novel->addSentence("少女「それに気付いたあいつが暴走して…………」");
		novel->addSentence("少女「………私……結局、なんにもできないんだ………無力でしかないんだ…………」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「君はずっと一人で頑張ってきたんだ。何一つ、無駄なことなんてないよ。」");
		novel->addSentence("継「…僕たちにできることならなんでもする。力になるよ。」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("少女「このままだと………もうじきこの世界も私も消えてしまう…………」");
		novel->addSentence("少女「私には………もう、色を教えてあげることができない…………」");
		novel->addSentence("少女「だから…………お願い、最後のクレヨンを見つけて………この世界に朝を迎えさせてほしいの………」");
		novel->addSentence("少女「そうすればきっと…………うぅ………」");
		novel->addSentence("セリーヌ「継様と寿甘様は先にクレヨンを探しに行ってください。私は、ここでこの子の看病をしています」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「頼むよ…行こう、寿甘」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/suama1.png");
		novel->addSentence("寿甘「うん！」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
			Control::me->getField("forest1")->removeChildByName("celine");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
	else if (Control::me->getField("room")->getObject("pass")->getState() == 1 &&
		getChildByName("second")) {
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「クレヨンを見つけて来たよ」");
		novel->addSentence("継「その子の容態は大丈夫？」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaC("chara/celine1.png");
		novel->addSentence("セリーヌ「ケガは大したことはなくて大丈夫そうです。しかし…」");
		novel->setCharaR("chara/girl2.png");
		novel->addSentence("少女「……」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「か、体が…透けて…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("少女「…マリアちゃんの日記を読んできたのね…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「うん、全部理解できたよ。君のことも、彼女の過去も。」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("少女「…そう…あなたには…マリアちゃんを救う覚悟はできているのね…これから先も…ずっと……」");
		novel->addSentence("少女「私には…もう合わせる顔がない……ここから先はあなたたちだけで行って……」");
		novel->addSentence("少女「マリアちゃんに…色を教えてあげられるのは……もうあなたたちだけ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「それは違うよ」");
		novel->addSentence("継「マリアちゃんに君が教えた色を、思い出をかき消すことなんてできないよ。」");
		novel->addSentence("継「僕たちには、思い出させて、色褪せないようにすることしかできないんだ。」");
		novel->addSentence("継「…行こう、一緒に。僕が背負って行くよ」");
		novel->addSentence("継「う…お」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「へーつぐるんまで女の子に重いなんて言っちゃうんだー」");
		novel->addSentence("寿甘「私がやるよ、こう見えて力はあるし。」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「いや、それじゃあ申し訳ないよ…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("セリーヌ「状況は察しましたわ、継様。記憶の中を少々拝見させていただきました。」");
		novel->addSentence("セリーヌ「…私は先に現実世界へ戻っています。少し考えがあるので…」"); 
		novel->addSentence("セリーヌ「最後まで彼女たちを守ってくださいね。継様。」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「わかったよ…！急ごう、時間がない」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("second");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}
