#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void Ruins::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("ruins.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "ruins", 0, true);

	auto forestD = ObjectN::create();
	forestD->setArea(Rect(50, 430, 530, 50));
	forestD->setFieldChangeEvent("forestD");
	forestD->setCursor(2);
	addObject(forestD, "forestD", 2, true);


	auto door = ObjectN::create();
	door->setArea(Rect(390, 290, 170, 120));
	door->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["door"]->getState() == 0) {
			//pauseEventListener();

			auto novel = Novel::create();
			novel->setFontColor(Color3B::RED);
			novel->setCharaR("chara/suama1.png");
			novel->addSentence("寿甘「ここが…マリアちゃんのおうちかな…」");
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「表札にミルフィーユって書いてあるね」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「きっとここにあるはずよね、クレヨン。」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「ちょっと怖いけど、入ろう。」");
			novel->addEvent(CallFunc::create([this] {
				mObjectList["door"]->setState(1);
				mObjectList["door"]->setFieldChangeEvent("living");
			}));
			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(door, "door", 2, true);

	auto letter = ObjectN::create();
	letter->setArea(Rect(680, 430, 70, 50));
	letter->setItemGetEvent("letter");
	letter->setMsg("中に手紙が入っていた");
	addObject(letter, "letter", 2, true);

	auto box = ObjectN::create();
	box->setArea(Rect(100, 380, 100, 60));
	box->setItemGetEvent("box");
	box->setMsg("草むらに木箱が落ちていた");
	addObject(box, "box", 2, true);

}

void Ruins::changedField() {
}

void Living::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("living.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "living", 0, true);
	bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("living_.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "living_", 0, false);

	auto ruins = ObjectN::create();
	ruins->setArea(Rect(0, 430, 500, 50));
	ruins->setFieldChangeEvent("ruins");
	ruins->setCursor(2);
	addObject(ruins, "ruins", 2, true);

	auto room = ObjectN::create();
	room->setArea(Rect(800, 0, 54, 400));
	room->setFieldChangeEvent("room");
	room->setCursor(3);
	addObject(room, "room", 2, true);


	auto fireplace = ObjectN::create();
	fireplace->setArea(Rect(120,300,110,100));
	fireplace->setMsg("暖炉だ");
	fireplace->setTouchEvent(CallFunc::create([this] {
		if (Item::sharedItem()->getSelectedItem() == "lamp" &&
			!getChildByName("living_")) {
			mObjectList["living_"]->setOpacity(0.0f);
			mObjectList["living_"]->runAction(FadeIn::create(3.0f));
			addChild(mObjectList["living_"], 1, "living_");
			mObjectList["living"]->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL));
			Control::me->showMsg("暖炉に火をつけた");
		}
		else if (Item::sharedItem()->getSelectedItem() == "box" &&
			getChildByName("living_") &&
			mObjectList["fireplace"]->getState() == 0) {
			Item::sharedItem()->deleteItem("box");
			Control::me->showMsg("暖炉の中に木箱を入れた");
			mObjectList["fireplace"]->setState(1);
		}
		else if (mObjectList["fireplace"]->getState() == 1) {
			if (Item::sharedItem()->getSelectedItem() == "tongs") {
				Item::sharedItem()->getItem("key3", Point(180, 120));
				Control::me->showMsg("焼けた木箱の中にカギが入っていた");
				Item::sharedItem()->deleteItem("tongs");
				mObjectList["fireplace"]->setState(2);
			}
			else {
				Control::me->showMsg("素手では取れない");
			}
		}
		else if (Item::sharedItem()->getSelectedItem() == "letter" &&
			getChildByName("living_") && 
			Control::me->getField("AboutItem")->getObject("letter_")->getState()== 0) {
			Control::me->showMsg("暖炉の火であぶり出しをした");
			Control::me->getField("AboutItem")->getObject("letter_")->setState(1);
		}
	}));
	addObject(fireplace, "fireplace", 2, true);

	auto closet = ObjectN::create();
	closet->setArea(Rect(620, 270, 60, 80));
	closet->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["closet"]->getState() == 0) {
			if (Item::sharedItem()->getSelectedItem() == "key3") {
				Item::sharedItem()->deleteItem("key3");
				Control::me->showMsg("カギを開けた");
				mObjectList["closet"]->setState(1);
			}
			else {
				Control::me->showMsg("カギがかかっている");
			}
		}
		else {
			auto spr = Sprite::create("hint3.png");
			spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
			spr->setOpacity(0.0f);
			spr->runAction(FadeIn::create(0.3f));
			addChild(spr, 5, "hint3");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				auto target = (Label*)event->getCurrentTarget();
				Rect targetBox = target->getBoundingBox();
				Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
				if (targetBox.containsPoint(touchPoint))
				{
					getChildByName("hint3")->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(), NULL));
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spr);
		}
	}));
	addObject(closet, "closet", 3, true);

	auto carpet = ObjectN::create();
	carpet->setArea(Rect(300, 370, 140, 70));
	carpet->setMsg("カーペットをめくった");
	carpet->setTouchEvent(CallFunc::create([this] {
		auto spr = Sprite::create("hint2.png");
		spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
		spr->setOpacity(0.0f);
		spr->runAction(FadeIn::create(0.3f));
		addChild(spr, 5, "hint2");
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			auto target = (Label*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				getChildByName("hint2")->runAction(Sequence::create(FadeOut::create(0.3f), RemoveSelf::create(), NULL));
				return true;
			}
			return false;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spr);
	}));
	addObject(carpet, "carpet", 3, true);

}

void Living::changedField() {
}

void Room::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = ObjectN::create();	//セーブで管理するものは背景でもObjectNで
	bg->setTexture("mariasroom.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addObject(bg, "room", 0, true);

	auto living= ObjectN::create();
	living->setArea(Rect(50, 450, 530, 30));
	living->setFieldChangeEvent("living");
	living->setCursor(2);
	addObject(living, "living", 2, true);

	auto book = Sprite::create("book1.png");
	book->setPosition(Director::getInstance()->getVisibleSize() / 2);
	book->setOpacity(0.0f);
	addChild(book, 5, "book");

	auto diary = ObjectN::create();
	diary->setArea(Rect(170, 50, 80, 200));
	diary->setTouchEvent(CallFunc::create([this] {
		//pauseEventListener();

		auto novel = Novel::create();
		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「ここにあるのはマリアちゃんの日記かな」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「女の子の日記を勝手に見るのは申し訳ないけど、何かわかるかもしれない。読んでみよう」");
		novel->setCharaR("");
		novel->setCharaL("");
		novel->addEvent(CallFunc::create([this] { getChildByName("book")->runAction(FadeIn::create(0.5f)); }));
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("マリアの日記");
		novel->addSentence("４がつ３にち（かようび）　まりあ４さい");
		novel->addSentence("きょうわおともだちのさくらちゃんとあそびました");
		novel->addSentence("もりでかくれんぼおしたり　かわでみずあそびしたり　すごくたのかったです");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("６がつ１７にち（げつようび）　まりあ５さい");
		novel->addSentence("さくらちゃんとわとてもなかよし　いつもいっしょにあそんでます");
		novel->addSentence("きょうわきのぼりおしてあそびました");
		novel->addSentence("きにりんごがなっていたので　わたしわとってたべようとしました");
		novel->addSentence("すると　さくらちゃんわあわててそれおたたきおとしてきました");
		novel->addSentence("さくらちゃんわ　どくりんごだからたべたらしんじゃうよといいました");
		novel->addSentence("わたしわ　どのりんごもいっしょじゃんよといいました");
		novel->addSentence("さくらちゃんわ　いろ　がちがうからたべちゃだめだといいました");
		novel->addSentence("わたしわ　さくらちゃんのゆうことが　わかりませんでした");
		novel->addSentence("きょうわけんかしてかえってきちゃったけど　あしたまたあえるよね　だってなかよしだもん");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("７月２３日（木よう日）　マリア７才");
		novel->addSentence("今日はサクラちゃんと花畑でピクニックをしました");
		novel->addSentence("「色」のこともなんとなくわかってきて、まいにちがもっとたのしくなった気がします");
		novel->addSentence("空の色、海の色、花の色…サクラちゃんがいっしょうけんめいに教えてくれました");
		novel->addSentence("ありがとう、サクラちゃん。ずっといっしょにいてね。");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("９月１２日（日よう日）　マリア９才");
		novel->addSentence("今日は学校の図工の時間に写生をしました");
		novel->addSentence("みんなが私の絵を「色づかいがすてき」といってほめてくれました");
		novel->addSentence("色の一つ一つにはサクラちゃんとの思い出が詰まっているので、大切にかきました");
		novel->addSentence("サクラちゃんとはちがうクラスになってしまったけれど、絵のおかげでお友達がたくさん作れそうです");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("３月９日（金曜日）　マリア１２才");
		novel->addSentence("今日は卒業式。これで、学校のみんなとはお別れです。");
		novel->addSentence("卒業式のあとで、体育館のうらでサクラちゃんに遠くへ引っこしてしまうことをこくはくされました。");
		novel->addSentence("私は「なんでそんな大切なことをもっと早く言ってくれなかったの」とおこりました");
		novel->addSentence("でも、サクラちゃんは私とお別れするのが悲しくてどうしても言い出せなかったと言って泣いてしまいました");
		novel->addSentence("私だって苦しいよ…");
		novel->addSentence("明日はサクラちゃんの旅立ちの日。また会えるといいな");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("１０月２０日（水曜日）　マリア１３歳");
		novel->addSentence("桜ちゃんとの思い出を忘れないように、私は美術部に入って毎日絵を描いている。");
		novel->addSentence("ネクラなんて言われても気にしない。もとから大人しい性格なんだし勝手にさせてよ。");
		novel->addSentence("部活では上手くいってる。先生にもコンクールで入賞を狙えるって言ってもらえた");
		novel->addSentence("私は大丈夫だよ、桜ちゃん");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("１２月１３日（金曜日）　マリア１５歳");
		novel->addSentence("最近絵の出来が悪いと言われる。色あせてるだなんて言われる。");
		novel->addSentence("この学校に来てから、友達と遊ぶなんてことはほとんどなくなった。所詮みんなうわべだけの関係。");
		novel->addSentence("なんだか視界がぼやけてきた、疲れてるのかな…");
		novel->addSentence("早く会いたいよ、桜ちゃん…");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("４月２４日（月曜日）　マリア１６歳");
		novel->addSentence("新しい環境に慣れ始めて来ても、私は相変わらずひとりぼっち");
		novel->addSentence("休み時間はずっと絵に没頭、周りなんて気にしない");
		novel->addSentence("学校は大丈夫？なんてパパとママは言うけど、心配なんてかけられないもんね");
		novel->addSentence("今に見てなさいよ！昔みたいにみんなに絵を見せたら、たちまち人気者なんだから");
		novel->addEvent(CallFunc::create(CC_CALLBACK_0(Room::turnPage, this)));
		novel->addSentence("６月４日（火曜日）　マリア１６歳");
		novel->addSentence("今日、隣の席の子に絵を見せた");
		novel->addSentence("その子はまるで怪物を見るような目で私を見てきた");
		novel->addSentence("他の子に見せても「色がヘン」「気持ち悪い」って");
		novel->addSentence("みんな私の才能に嫉妬しているのかと思って、今度は先生に似顔絵を描いて見せた。");
		novel->addSentence("「バカにしてるのか」なんて怒られた");
		novel->addSentence("なんでなんで！あの頃はあんなに褒められたのに！！どうして私を否定するの？");
		novel->addSentence("色！？色ってなんだっけ…桜ちゃんに教えてもらった色…");
		novel->addSentence("思えば今は目を開けて見る景色なんてちっとも綺麗じゃない");
		novel->addSentence("思い出せない…大切な色のこと…思い出せない…怖い…");
		novel->addSentence("みんなが私を貶す声が聞こえる…どうして！私はただ受け入れてほしいだけなのに…");
		novel->addSentence("怖いよぉ…色のない世界なんて嫌だよぉ…");
		novel->addSentence("助けて…桜ちゃん…");
		novel->addEvent(CallFunc::create([this] { getChildByName("book")->runAction(FadeOut::create(0.5f)); }));
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「日記はここで終わっている」");
		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「マリアちゃん…こんなことになってたんて…ごめんね…気付かなくて……うっ…うぅ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「今は彼女を救い出すことを考えよう。この日記の中にクレヨンを見つけるヒントがあったはずだよ。」");

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}));
	addObject(diary, "diary", 2, true);

	auto pass = ObjectN::create();
	pass->setArea(Rect(340, 130, 100, 70));
	pass->setTouchEvent(CallFunc::create([this] {
		Field* passward = Control::me->getField("pass2");
		if (passward->getObject("num1")->getState() == 1 &&
			passward->getObject("num2")->getState() == 7 &&
			passward->getObject("num3")->getState() == 4 &&
			passward->getObject("num4")->getState() == 0 &&
			mObjectList["pass"]->getState() == 0) {
			//pauseEventListener();

			auto novel = Novel::create();

			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「これで合ってるはず」");
			novel->addEvent(CallFunc::create([this] {
				Item::sharedItem()->getItem("crayon_r", Point(445, 280));
				mObjectList["pass"]->setState(1);
				mObjectList["pass"]->setMsg("もう何もない");
			}));
			novel->addSentence("継「よし、赤いクレヨンを手に入れたよ」");
			novel->setFontColor(Color3B::RED);
			novel->setCharaR("chara/suama1.png");
			novel->addSentence("寿甘「みんなと合流して、画用紙に色を塗りに行こう！」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");

		}
		else if (mObjectList["pass"]->getState() == 0) {
			Control::me->changeField("pass2");
		}
	}));
	addObject(pass, "pass", 3, true);


	auto first = ObjectN::create();
	addObject(first, "first", 0, true);	//フラグ用

}

void Room::changedField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (getChildByName("first")) {
		//pauseEventListener();

		auto novel = Novel::create();

		novel->setFontColor(Color3B::RED);
		novel->setCharaR("chara/suama1.png");
		novel->addSentence("寿甘「なに…これ…」");
		novel->setFontColor(Color3B::BLUE);
		novel->setCharaL("chara/tuguru1.png");
		novel->addSentence("継「ここが彼女の部屋かな…すごい数の画用紙が散らばっているね」");
		novel->addSentence("継「マリアちゃんは絵を描くのが好きだったのかな」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「…よく見て」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「…？」");
		novel->setBg("chara/scene6.png");
		novel->addSentence("継「これは…色が不自然だね…」");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("寿甘「な、なんのためにこんな気持ち悪い絵を描くのよ…！」");
		novel->setFontColor(Color3B::BLUE);
		novel->addSentence("継「他人の趣向を否定するのはよくないよ…でも一体どうしてわざわざ違う色で絵を描いていたのか…不思議だね」");
		novel->addEvent(CallFunc::create([this] {
			removeChildByName("first");
		}));

		novel->setEndTask();
		this->addChild(novel, 10, "novel");
	}
}

void Room::turnPage() {
		auto _animation = Animation::create();
		_animation->addSpriteFrameWithFile("book1.png");
		_animation->addSpriteFrameWithFile("book2.png");
		_animation->addSpriteFrameWithFile("book3.png");
		_animation->addSpriteFrameWithFile("book4.png");
		_animation->setDelayPerUnit(0.1f); //アニメの動く時間を設定
		_animation->setRestoreOriginalFrame(true);
		getChildByName("book")->stopAllActions();
		getChildByName("book")->runAction(Animate::create(_animation));
}

void Passward2::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("pass2.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "pass");

	auto room = ObjectN::create();
	room->setArea(Rect(0, 320, 850, 160));
	room->setFieldChangeEvent("room");
	room->setCursor(2);
	addObject(room, "room", 2, true);

	//1
	auto num = ObjectN::create();
	addObject(num, "num1", 2, false);
	auto label = Label::createWithTTF("0", "fonts/APJapanesefontT.ttf", 100);
	label->setPosition(Vec2(240, 340));
	label->setTextColor(Color4B::BLACK);
	addChild(label, 3, "label1");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			int num = mObjectList["num1"]->getState();
			num++;
			if (num >= 10) num = 0;

			mObjectList["num1"]->setState(num);
			std::stringstream s;
			s << num;
			target->setString(s.str());

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	//2
	num = ObjectN::create();
	addObject(num, "num2", 2, false);
	label = Label::createWithTTF("0", "fonts/APJapanesefontT.ttf", 100);
	label->setPosition(Vec2(360, 340));
	label->setTextColor(Color4B::BLACK);
	addChild(label, 3, "label2");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			int num = mObjectList["num2"]->getState();
			num++;
			if (num >= 10) num = 0;

			mObjectList["num2"]->setState(num);
			std::stringstream s;
			s << num;
			target->setString(s.str());

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	//3
	num = ObjectN::create();
	addObject(num, "num3", 2, false);
	label = Label::createWithTTF("0", "fonts/APJapanesefontT.ttf", 100);
	label->setPosition(Vec2(470, 340));
	label->setTextColor(Color4B::BLACK);
	addChild(label, 3, "label3");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			int num = mObjectList["num3"]->getState();
			num++;
			if (num >= 10) num = 0;

			mObjectList["num3"]->setState(num);
			std::stringstream s;
			s << num;
			target->setString(s.str());

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	//4
	num = ObjectN::create();
	addObject(num, "num4", 2, false);
	label = Label::createWithTTF("0", "fonts/APJapanesefontT.ttf", 100);
	label->setPosition(Vec2(590, 340));
	label->setTextColor(Color4B::BLACK);
	addChild(label, 3, "label4");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			int num = mObjectList["num4"]->getState();
			num++;
			if (num >= 10) num = 0;

			mObjectList["num4"]->setState(num);
			std::stringstream s;
			s << num;
			target->setString(s.str());

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
}

void Passward2::changedField() {

}