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
			pauseEventListener();
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
	//if (itemName=="crayon_g") {
	//	addChild(mObjectList["crayon_g"]);
	//}
	//else if (itemName == "egg") {
	//	addChild(mObjectList["egg"]);
	//}
	//else if (itemName == "mushroom") {
	//	addChild(mObjectList["mushroom"]);
	//}
	//else if (itemName == "matsu") {
	//	addChild(mObjectList["matsu"]);
	//}

	addChild(mObjectList[itemName]);

	//同時に二つ以上表示する場合はitemName == で書く
	
}