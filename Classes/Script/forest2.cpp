#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Forest2::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("forest2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "forest2");

	auto forest1 = ObjectN::create();
	forest1->setArea(Rect(774, 240, 80, 240));
	forest1->setFieldChangeEvent("forest1");
	forest1->setCursor(3);
	addObject(forest1, "forest1", 2, true);

	auto forest3 = ObjectN::create();
	forest3->setArea(Rect(150, 180, 150, 120));
	forest3->setFieldChangeEvent("forest3");
	forest3->setCursor(6);
	addObject(forest3, "forest3", 2, true);

	auto egg = ObjectN::create();
	egg->setArea(Rect(760, 200, 80, 50));
	egg->setTexture("egg.png");
	egg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg->setTouchEvent(CallFunc::create([this] {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaL("chara/suama1.png");
		novel->addSentence("寿甘「あー！みてみて！鳥のたまごがあるよ！！」");
		novel->addSentence("寿甘「…って」");
		novel->setCharaC("chara/scene1.png");
		novel->addSentence("寿甘「キャーー！！ヘビーーーー！！！」");
		novel->addSentence("寿甘「だ、誰かやっつけてよぉ…」");
		novel->setCharaL("chara/tuguru1.png");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「とりあえず、一旦たまごを退避させておこうか…」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("egg");
			addChild(mObjectList["egg_"], 3, "egg_");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}));
	addObject(egg, "egg", 3, true);

	auto egg_ = ObjectN::create();
	egg_->setArea(Rect(760, 200, 80, 50));
	egg_->setTexture("egg.png");
	egg_->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg_->setItemGetEvent("egg");
	egg_->setMsg("鳥のたまごを手に入れた");
	addObject(egg_, "egg_", 3, false);

	auto mushroom = ObjectN::create();
	mushroom->setArea(Rect(40, 370, 50, 90));
	mushroom->setTexture("mushroom.png");
	mushroom->setPosition(visibleSize / 2);
	mushroom->setItemGetEvent("mushroom");
	mushroom->setMsg("キノコを手に入れた");
	addObject(mushroom, "mushroom", 3, true);

	auto rafflesia = ObjectN::create();
	rafflesia->setArea(Rect(300, 360, 160, 100));
	rafflesia->setTouchEvent(CallFunc::create([this] {
		pauseEventListener();

		auto novel = Novel::create();

		novel->addEvent(CallFunc::create([this] {
			removeChildByName("rafflesia");
			addChild(mObjectList["rafflesia_"], 3, "rafflesia_");
		}));
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/bandana1.png");
		novel->addSentence("バンダナ「この花の中にカギがあるみたいだ」");
		novel->addSentence("バンダナ「臭いがキツいけど…俺、取ってくるよ」");
		novel->setFontColor(Color3B::BLACK);
		novel->setCharaC("chara/scene2.png");
		novel->addSentence("がちんっ");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("バンダナ「おわっ」");
		novel->addSentence("バンダナ「引いてなければ、手がちょん切れるとこだったぜ…」");
		novel->addSentence("バンダナ「これじゃ取れないな…どうするか…」");

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}));
	addObject(rafflesia, "rafflesia", 3, true);
	rafflesia = ObjectN::create();
	rafflesia->setArea(Rect(300, 360, 160, 100));
	rafflesia->setMsg("大きな花がある");
	rafflesia->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "matsu" &&
			((ObjectN*)(Control::me->getField("AboutItem")->getObject("matsu")))->getState() == 1 &&
			mObjectList["rafflesia_"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/bandana1.png");
			novel->addSentence("バンダナ「この松の葉…針金みたいに曲がるぞ…」");
			novel->addSentence("バンダナ「フック状にして中にあるカギを取ってみよう」");
			novel->addEvent(CallFunc::create([this] {
				mObjectList["rafflesia_"]->setState(1);
				Item::sharedItem()->getItem("key", Point(380, 80));
			}));
			novel->addSentence("バンダナ「よし、取れた」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(rafflesia, "rafflesia_", 3, false);
 
	auto ladder = ObjectN::create();
	ladder->setTexture("ladder_.png");
	ladder->setArea(Rect(630, 50, 100, 35));
	ladder->setMsg("はしごが上がっている");
	ladder->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "stick" && mObjectList["ladder"]->getState() == 0) {
			pauseEventListener();

			auto novel = Novel::create();
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「この棒で何とかはしごを降ろせないかな…」");
			novel->addSentence("継「よっ！…ほっ！…うーん、届かない…」");
			novel->setFontColor(Color3B::RED);
			novel->setCharaR("chara/suama1.png");
			novel->addSentence("寿甘「あはは、何やってんのよー！バンダナ、肩車してあげなさい。」");
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/bandana1.png");
			novel->addSentence("バンダナ「えー、俺ー？お前の方がデカいからやれよー」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「あ゛？」");
			novel->setCharaC("chara/scene3.png");
			novel->addSentence("寿甘「誰がデブだって…？」");
			novel->addSentence("寿甘「つーかお前男だろ。女にやらせるとかどういうことよ？」");
			novel->setFontColor(Color3B::BLACK);
			novel->setCharaC("");
			novel->addSentence("ガンッ…ガラガラ…");
			novel->addEvent(CallFunc::create([this] {
				getChildByName("ladder_")->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(), NULL));
				addChild(mObjectList["ladder"], 3, "ladder");
				mObjectList["ladder"]->setOpacity(0.0f); mObjectList["ladder"]->runAction(FadeIn::create(0.3f));
				mObjectList["door"]->setMsg("カギがかかっている");
			}));
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("バンダナ「ええ…」");
			
			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(ladder, "ladder_", 3, true);

	ladder = ObjectN::create();
	ladder->setTexture("ladder.png");
	ladder->setArea(Rect(640, 70, 100, 380));
	ladder->setMsg("はしごが下がっている");
	addObject(ladder, "ladder", 3, false);

	auto door = ObjectN::create();
	door->setArea(Rect(630, 0, 100, 50));
	door->setMsg("はしごが上がっていて入れない");
	door->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["door"]->getState() == 0) {
			if (getChildByName("ladder") &&
				Item::sharedItem()->getSelectedItem() == "key") {
				Control::me->showMsg("カギを開けた");
				Item::sharedItem()->deleteItem("key");
				mObjectList["door"]->setState(1);
				mObjectList["door"]->setFieldChangeEvent("treehouse");
				mObjectList["door"]->setMsg("ツリーハウスの中に入った");
			}
		}
	}));
	addObject(door, "door", 3, true);

	auto girl = ObjectN::create();
	addObject(girl, "girl", 0, true);	//フラグ用
}

void Forest2::changedField() {
	if (getChildByName("girl")) {
		pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「森の中に入ってきたね」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「薄暗くて気味が悪いよ…闇雲に動いたってしょうがなくない？引き返そうよー」");
		novel->addSentence("寿甘「それに後ろからなんとなく気配が…」");
		novel->setCharaC("chara/girl1.png");
		novel->addSentence("寿甘「！」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「えっ、女の子…？」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「ねえ、君はこの世界の子なのかな？…そうだ、紫の長い髪の子見なかった？」");
		novel->addSentence("謎の少女「・・・」");
		novel->addSentence("謎の少女「あなたたちは…だれ…？」");
		novel->addSentence("寿甘「え！…あー、私たちはその子の友達…みたいな感じ…かな？それで、捜してるの！」");
		novel->addSentence("謎の少女「！……そう…」");
		novel->addSentence("謎の少女「じゃあ、ついてきて…」");
		novel->setCharaC("");
		novel->addSentence("寿甘「消えた？…ってもうあんなところに！ほうきで飛んで追いかけよう！早くしないと見失っちゃう！」");
		novel->setCharaL("chara/celine1.png");
		novel->addSentence("セリーヌ「それは、できません。ここには魔力を制御するハンコの力が及びませんので、魔法は使えないみたいです。」");
		novel->addSentence("セリーヌ「手がかりを見つけながら追いかけましょう」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("girl");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}
