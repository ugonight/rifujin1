﻿#pragma  execution_character_set("utf-8")

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

	auto cave = ObjectN::create();
	cave->setArea(Rect(440, 220, 90, 140));
	cave->setFieldChangeEvent("cave");
	cave->setCursor(6);
	addObject(cave, "cave", 2, true);

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

	auto ivy = ObjectN::create();
	ivy->setArea(Rect(0, 435, 150, 45));
	ivy->setMsg("土が柔らかくなっている");
	ivy->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "seed" &&
			getChildByName("ivy")) {
			pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「タネを植えてみよう」");	
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->deleteItem("seed");
				removeChildByName("ivy");
				addChild(mObjectList["ivy1"], 3, "ivy1");
				mObjectList["ivy1"]->runAction(FadeIn::create(2.0f));
			}));
			novel->setCharaR("chara/bandana1.png");
			novel->addSentence("バンダナ「すっげえ成長の早さ…」");
			novel->addSentence("継「葉につかまっていれば上に上がれるかな、やってみよう。」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(ivy, "ivy", 3, true);

	ivy = ObjectN::create();
	ivy->setArea(Rect(0, 0, 150, 200));
	ivy->setTexture("ivy.png");
	ivy->setFieldChangeEvent("cliff");
	ivy->setOpacity(0.0f);
	auto _animation = Animation::create();
	_animation->addSpriteFrameWithFile("ivy.png");
	_animation->addSpriteFrameWithFile("ivy1.png");
	_animation->addSpriteFrameWithFile("ivy2.png");
	_animation->addSpriteFrameWithFile("ivy3.png");
	_animation->setDelayPerUnit(0.5f); //アニメの動く時間を設定
	_animation->setRestoreOriginalFrame(true);
	ivy->runAction(RepeatForever::create(Animate::create(_animation)));
	addObject(ivy, "ivy1", 3, false);

}

void Forest3::changedField() {
	//フィールド移動でアニメが消えてしまうのでこっちに定義
	auto _animation = Animation::create();
	_animation->addSpriteFrameWithFile("ivy.png");
	_animation->addSpriteFrameWithFile("ivy1.png");
	_animation->addSpriteFrameWithFile("ivy2.png");
	_animation->addSpriteFrameWithFile("ivy3.png");
	_animation->setDelayPerUnit(0.5f); //アニメの動く時間を設定
	_animation->setRestoreOriginalFrame(true);
	mObjectList["ivy1"]->runAction(RepeatForever::create(Animate::create(_animation)));
}


void Cliff::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("cliff.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "cliff");

	auto forest3 = ObjectN::create();
	forest3->setArea(Rect(0, 320, 150, 160));
	forest3->setFieldChangeEvent("forest3");
	forest3->setCursor(2);
	addObject(forest3, "forest3", 2, true);

	auto pen = ObjectN::create();
	pen->setArea(Rect(440, 340, 60, 20));
	pen->setItemGetEvent("pen");
	pen->setMsg("ペンが落ちていた");
	addObject(pen, "pen", 2, true);

	auto bird = ObjectN::create();
	bird->setArea(Rect(390, 430, 130, 50));
	bird->setMsg("鳥がいる");
	bird->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "egg" &&
			mObjectList["bird"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::RED);
			novel->setCharaL("chara/suama1.png");
			novel->addSentence("寿甘「あ！この鳥…もしかして…！」");
			novel->addSentence("寿甘「ちょっと話してくるねー！」");
			novel->setFontColor(Color3B::BLACK);
			novel->addSentence("寿甘は動物や物と話せる特殊能力を持っているのだ");
			novel->setCharaL("");
			novel->setBg("chara/scene4.png");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「もしかして、このタマゴ君のかな？」");
			novel->addSentence("寿甘「やっぱりそうなんだ！ヘビに食べられそうになってて危なかったんだよ～」");
			novel->addSentence("寿甘「ていうか、なんでまた危ないところに巣作ってるのよ…」");
			novel->addSentence("寿甘「お礼にこれを…ってクレヨン！？ありがとー！探してたからすっごく助かる～」");
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->deleteItem("egg");
				mObjectList["bird"]->setState(1);
				Item::sharedItem()->getItem("crayon_y", Point(580, 20));
			}));

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(bird, "bird", 2, true);

}

void Cliff::changedField() {

}