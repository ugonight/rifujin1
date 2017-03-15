#pragma  execution_character_set("utf-8")

#include "Script/fieldDef.h"

USING_NS_CC;

void AboutItem::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//オブジェクトを作っておく
	//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

	//クレヨン（緑）
	auto crayon = ObjectN::create();
	crayon->setTexture("item/crayon_g.png");
	crayon->setMsg("緑のクレヨンだ");
	crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	crayon->setArea(crayon->getBoundingBox());
	addObject(crayon, "crayon_g", 1, false);

	//クレヨン（青）
	crayon = ObjectN::create();
	crayon->setTexture("item/crayon_b.png");
	crayon->setMsg("青のクレヨンだ");
	crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	crayon->setArea(crayon->getBoundingBox());
	addObject(crayon, "crayon_b", 1, false);

	//クレヨン（黄）
	crayon = ObjectN::create();
	crayon->setTexture("item/crayon_y.png");
	crayon->setMsg("黄のクレヨンだ");
	crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	crayon->setArea(crayon->getBoundingBox());
	addObject(crayon, "crayon_y", 1, false);

	//クレヨン（赤）
	crayon = ObjectN::create();
	crayon->setTexture("item/crayon_r.png");
	crayon->setMsg("赤のクレヨンだ");
	crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	crayon->setArea(crayon->getBoundingBox());
	addObject(crayon, "crayon_r", 1, false);

	//卵
	auto egg = ObjectN::create();
	egg->setTexture("item/egg.png");
	egg->setMsg("鳥のたまごだ");
	egg->setScale(2.0f);
	egg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	egg->setArea(egg->getBoundingBox());
	addObject(egg, "egg", 1, false);

	//きのこ
	auto mushroom = ObjectN::create();
	mushroom->setTexture("item/mushroom_a.png");
	mushroom->setMsg("キノコだ。胞子がたくさんついている");
	mushroom->setPosition(visibleSize / 2);
	mushroom->setArea(mushroom->getBoundingBox());
	addObject(mushroom, "mushroom", 1, false);

	//松の葉
	auto matsu = ObjectN::create();
	matsu->setTexture("item/matsu_a.png");
	matsu->setMsg("松の葉の先を曲げた");
	matsu->setArea(matsu->getBoundingBox());
	matsu->setTouchEvent(CallFunc::create([this] {
		auto obj = (ObjectN*)mObjectList["matsu"];
		if (obj->getState() == 0) {
			obj->setTexture("item/matsu2_a.png");
			obj->setMsg("松の葉の先を曲げてある");
			obj->setState(1);
		}
	}));
	addObject(matsu, "matsu", 1, false);

	//木の棒
	auto stick = ObjectN::create();
	stick->setTexture("item/stick_a.png");
	stick->setMsg("木の棒だ");
	stick->setArea(stick->getBoundingBox());
	stick->setTouchEvent(CallFunc::create([this] {
		auto obj = (ObjectN*)mObjectList["stick"];
		if (obj->getState() == 1 &&
			Item::sharedItem()->getSelectedItem() == "matsu" &&
			mObjectList["matsu"]->getState() == 1) {
			Item::sharedItem()->deleteItem("matsu");
			obj->setTexture("item/stick_yarn_matsu_a.png");
			obj->setMsg("釣り竿を作った");
			obj->setState(2);
			Control::me->showMsg("釣り竿を作った");
		}
	}));
	addObject(stick, "stick", 1, false);

	//カギ
	auto key = ObjectN::create();
	key->setTexture("item/key_a.png");
	key->setMsg("ツリーハウスのカギだろう");
	key->setArea(key->getBoundingBox());
	addObject(key, "key", 1, false);

	//カギ2
	key = ObjectN::create();
	key->setTexture("item/key2_a.png");
	key->setMsg("石でできている。洞窟で使うカギだろうか");
	key->setArea(key->getBoundingBox());
	addObject(key, "key2", 1, false);

	//カギ3
	key = ObjectN::create();
	key->setTexture("item/key3_a.png");
	key->setMsg("さび付いている。戸棚に使えそうだ");
	key->setArea(key->getBoundingBox());
	addObject(key, "key3", 1, false);

	//ランプ
	auto lamp = ObjectN::create();
	lamp->setTexture("item/lamp_a.png");
	lamp->setMsg("ランプが消えている");
	lamp->setArea(lamp->getBoundingBox());
	lamp->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "board" &&
			mObjectList["board"]->getState() == 1 &&
			mObjectList["lamp"]->getState() == 0) {
			Item::sharedItem()->deleteItem("board");
			mObjectList["lamp"]->setTexture("item/lamp_on.png");
			mObjectList["lamp"]->setState(1);
			mObjectList["lamp"]->setMsg("ランプがついている");
			Control::me->showMsg("ランプに火を灯した");
		}
	}));
	addObject(lamp, "lamp", 1, false);

	//木版
	auto board = ObjectN::create();
	board->setTexture("item/board_a.png");
	board->setMsg("木版だ");
	board->setArea(board->getBoundingBox());
	board->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "stick" && mObjectList["board"]->getState() == 0) {
			//pauseEventListener();
			auto novel = Novel::create();
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「これで火を起こせるかな…」");
			novel->setFontColor(Color3B::BLACK);
			novel->addSentence("ゴシゴシゴシ…");
			novel->addSentence("ゴシゴシ…");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「む、無理…魔法がないとこんなに大変なんて…」");
			novel->setCharaR("chara/bandana1.png");
			novel->addSentence("バンダナ「貸してみ？」");
			novel->addSentence("バンダナ「うおおおおお」");	
			novel->addEvent(CallFunc::create([this] {
				mObjectList["board"]->setTexture("item/board_stick_a.png");
				mObjectList["board"]->setState(1);
				mObjectList["board"]->setMsg("火を起こした");
			}));
			novel->addSentence("継「あ！煙が出てきた！」");
			novel->addSentence("バンダナ「ふん、俺はいつでも魔法に頼りっきりって訳じゃじゃねえからな」");
			novel->addSentence("継「助かったよ、早くランプに火を移そう」");
			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(board, "board", 1, false);

	//種
	auto seed = ObjectN::create();
	seed->setTexture("item/seed_a.png");
	seed->setMsg("大きなタネだ");
	seed->setArea(seed->getBoundingBox());
	addObject(seed, "seed", 1, false);

	//ペン
	auto pen = ObjectN::create();
	pen->setTexture("item/pen_a.png");
	pen->setMsg("マジックペンだ");
	pen->setArea(pen->getBoundingBox());
	addObject(pen, "pen", 1, false);

	//巻物
	auto scroll = ObjectN::create();
	scroll->setTexture("item/scroll_a.png");
	scroll->setMsg("滝の中に入るための呪文が書かれている");
	scroll->setArea(scroll->getBoundingBox());
	addObject(scroll, "scroll", 1, false);

	//剣
	auto sword = ObjectN::create();
	sword->setTexture("item/sword_a.png");
	sword->setMsg("強そうな剣だ");
	sword->setArea(sword->getBoundingBox());
	addObject(sword, "sword", 1, false);

	//手紙
	auto letter = ObjectN::create();
	letter->setTexture("item/letter1_a.png");
	letter->setMsg("何も書かれていない");
	letter->setArea(letter->getBoundingBox());
	letter->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "lamp") {
			Control::me->showMsg("ランプの火であぶり出しをした");
			addChild(mObjectList["letter_"], 2, "letter_");
			mObjectList["letter_"]->setOpacity(0.0f);
			mObjectList["letter_"]->runAction(FadeIn::create(1.0f));
			mObjectList["letter_"]->setState(1);
			mObjectList["letter"]->runAction(Sequence::create(DelayTime::create(1.0f),RemoveSelf::create(),NULL));
		}
	}));
	addObject(letter, "letter", 1, false);
	letter = ObjectN::create();
	letter->setTexture("item/letter2_a.png");
	letter->setMsg("文字が浮かび上がっている");
	letter->setArea(letter->getBoundingBox());
	addObject(letter, "letter_", 1, false);

	//トング
	auto tongs = ObjectN::create();
	tongs->setTexture("item/tongs_a.png");
	tongs->setMsg("トングだ");
	tongs->setArea(tongs->getBoundingBox());
	addObject(tongs, "tongs", 1, false);

	//木箱
	auto box = ObjectN::create();
	box->setTexture("item/box_a.png");
	box->setMsg("接着剤で頑丈に閉められていて開かない");
	box->setArea(box->getBoundingBox());
	addObject(box, "box", 1, false);



}
void AboutItem::changedField(){}
void AboutItem::setAboutItem(std::string itemName) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->removeAllChildren();

	this->scheduleUpdate();
	for (auto it : this->getChildren()) {
		it->scheduleUpdate();
	}

	//ここにAboutItemの処理を書いていく
	//同時に二つ以上表示する場合はitemName == で書く
	if (itemName == "letter") {
		if (mObjectList["letter_"]->getState() == 1) {
			addChild(mObjectList["letter_"], 2, "letter_");
		}
		else {
			addChild(mObjectList["letter"], 1, "letter");
		}
	}
	else {
		addChild(mObjectList[itemName]);	//基本的に登録名と同じオブジェクトを表示
	}
}