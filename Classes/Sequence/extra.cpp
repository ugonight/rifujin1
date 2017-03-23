#pragma  execution_character_set("utf-8")
#include "extra.h"
#include "Title.h"
#include "System/novel.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool Extra::init() {
	if (Scene::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg/bedroom.png");
	bg->setPosition(display / 2);
	addChild(bg, 0, "bg");

	auto layer = Layer::create();
	layer->setPosition(Vec2::ZERO);
	addChild(layer, 1, "layer");

	menu();

	return true;
}

void Extra::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			removeChild(novel);
		}
	}
}

void Extra::menu() {
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layer = getChildByName("layer");

	auto label = Label::createWithTTF("タイトルへ戻る", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("あとがき", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 2 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "afterword");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			afterword();
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("おんがく", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 3 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "music");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {music(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("キャラクター", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 4 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "character");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {character(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::character(){
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layer = getChildByName("layer");

	auto description = Sprite::create("title/chara.png");
	description->setPosition(display / 2);
	layer->addChild(description, 1, "description");

	auto label = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 20);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(Vec2(origin.x + 500, origin.y + 350));
	label->setTextColor(Color4B::BLACK);
	label->setDimensions(320, 330);
	layer->addChild(label, 3, "text");

	label = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 35);
	label->setPosition(Vec2(origin.x + 650, origin.y + 400));
	label->setTextColor(Color4B::BLACK);
	label->enableOutline(Color4B::WHITE, 2);
	layer->addChild(label, 3, "name");

	label = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 20);
	label->setPosition(Vec2(origin.x + 650, origin.y + 450));
	label->setTextColor(Color4B::BLACK);
	layer->addChild(label, 3, "phonetic");

	auto chara = Sprite::create();
	chara->setPosition(Vec2(origin.x + 350, origin.y + display.height / 2));
	layer->addChild(chara, 2, "image");


	label = Label::createWithTTF("戻る", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {menu(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("桜", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 2 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "sakura");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/sakura1.png");
			((Label*)layer->getChildByName("name"))->setString("朝星　桜");
			((Label*)layer->getChildByName("phonetic"))->setString("あさぼし　さくら");
			((Label*)layer->getChildByName("text"))->setString(" \
マリアの幼馴染。\n \
１２歳のころまで近所に住んでいたが、親の転勤で遠くの国へ引っ越してしまう。\n \
マリアとは対照的で明るい性格であり、友達想い。\n\
引っ越し先の国で重い病気にかかってしまい、国の魔法が発展途上であったため治す術がなかったが、セリーヌの機転により、魔法が発達した魔界王国の看護魔法で治療を施される。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("マリア", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 3 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "maria");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/maria1.png");
			((Label*)layer->getChildByName("name"))->setString("マリア・ミルフィーユ");
			((Label*)layer->getChildByName("phonetic"))->setString("まりあ・みるふぃーゆ");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
生まれた時から色が識別できない病気を持っていて、波動を使って生活していた\n \
幼馴染の桜に色を教えてもらううちに、桜の脳内から色のイメージを受け取り、病気は奇跡的に回復した。\n\
大人しい性格で、いつも一人で絵を描いたり本を読んで過ごしている。\n\
周囲とうまく馴染めず、次第に色を忘れていってしまう。学校でのハプニングが原因で塞ぎ込み、やがて意識の中から出られなくなってしまう。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("バンダナ", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 4 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "bandana");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/bandana1.png");
			((Label*)layer->getChildByName("name"))->setString("バイロン・ダイエナ");
			((Label*)layer->getChildByName("phonetic"))->setString("ばいろん・だいえな");
			((Label*)layer->getChildByName("text"))->setString(" \
継の友達\n \
魔法学校に通いながらも、魔法に頼らないという信念を持つ。\n \
剣術に長けており、ピンチの時はいつも継達を助けてくれる。\n\
ひょうきんな性格だが、優しいところもある。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("寿甘", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 5 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "suama");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/suama1.png");
			((Label*)layer->getChildByName("name"))->setString("立花　寿甘");
			((Label*)layer->getChildByName("phonetic"))->setString("たちばな　すあま");
			((Label*)layer->getChildByName("text"))->setString(" \
継の友達。\n \
動物や物の声を受け取ることができる特殊能力を持つ。\n \
おてんばな性格で、面倒見がいい。\n\
霊感が強いため、幽霊などを見てしまうことがある。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("セリーヌ", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 6 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "celine");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/celine1.png");
			((Label*)layer->getChildByName("name"))->setString("セリーヌ・ルトストレーム");
			((Label*)layer->getChildByName("phonetic"))->setString("せりーぬ・るとすとれーむ");
			((Label*)layer->getChildByName("text"))->setString(" \
継に仕えるメイド\n \
ほとんどの魔法をほぼ完璧にこなす。看護魔法が得意分野。\n \
常に冷静で、機転を利かせた行動をする。\n\
継からはドSと揶揄され、よくコントのような掛け合いをすることがある。\n\
年齢の話をすると人が変わったようにぶちギレる。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("継", "fonts/APJapanesefontT.ttf", 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 7 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "tuguru");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/tuguru1.png");
			((Label*)layer->getChildByName("name"))->setString("王国　継");
			((Label*)layer->getChildByName("phonetic"))->setString("おうこく　つぐる");
			((Label*)layer->getChildByName("text"))->setString(" \
今は亡き父、守の遺志を継いで魔界王国の国王になった。つぐるんの愛称で親しまれている\n \
政治のことはまだ勉強途中なので大臣などに任せっきりだが、王国の魔法を制御するハンコの管理と、大事な決め事などはできるだけこなしている。\n \
仕事と修行を両立させなきゃいけないため、魔法はあまり使えないが頭が切れるので、数々の問題事を片付けることができる。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::music(){
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layer = getChildByName("layer");

	auto label = Label::createWithTTF("戻る", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {menu(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("いのちのいろ", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 2 / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "color");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/color.ogg", true);
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("misery", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 3 / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "misery");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/misery.ogg", true);
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("dream", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 4 / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "dream");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/dream.ogg", true);

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("days", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 5 / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "days");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/days.ogg", true);

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("precious smile (inst short ver.)", "fonts/APJapanesefontT.ttf", 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 6 / 7));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "title");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/title.ogg", true);

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::afterword(){
	auto novel = Novel::create();
	novel->setFontColor(Color3B::BLACK);
	novel->addSentence("皆さん、こんにちわ。作者のｕｇｏｎｉｇｈｔです");
	novel->addSentence("エンドロールがｕｇｏｎｉｇｈｔだらけでイライラしたかもしれませんが、これで最後です。ご安心ください。");
	novel->addSentence("こんなに手作り感満載なアプリが果たして今まであったのだろうか、っていう感じですね。誰でも作れちゃうものなんです。自分でもびっくりしてます。");
	novel->addSentence("最後に歌が流れて来たのにもびっくりした方もいらっしゃるかもしれませんが、普段はこういうものを作ってます。書下ろしです。いかがでしたでしょうか。");
	novel->addSentence("実はこのゲーム、５年ぶりくらいの完全新作ゲームになります。その間に曲作ったり絵描いたりプログラミングの勉強をして、その集大成としてこのゲームを作ったのですが、あんまり成長してませんね…申し訳ない");
	novel->addSentence("前作は「テストクエスト３」というゲームで、下絵無家という物理世界の一般家庭の父子が魔界世界に迷い込んでしまうお話です。いきなりハンコって出て来て意味わかんねえよ！ってなった方はやってみてください");
	novel->addSentence("さて、いい加減に中身の話を…");
	novel->addSentence("システムの方は、操作が独特で分かりにくかったかもしれません。なるべく探索画面をスッキリさせようとした結果こうなりました。");
	novel->addSentence("我慢ならねえ！と言ったものがあったら☆１でもいいのでレビューに書いていただけるとありがたいです。次に生かします。");
	novel->addSentence("シナリオの方は、自分でもバランスが悪かったかなーと思ってます。もうちょっとボリュームがあれば感動ゲームにできたかもしれません…まあ短編なので許してください（泣）これも次頑張ります…");
	novel->addSentence("マリアちゃんの過去は自分を重ね合わせて作ってしまった部分もあります。自分も高校レビューとともにボッチ生活を満喫してます。でもやっぱり、自分を理解してくれる昔からの付き合いの友達がいると、とても心強いですね。");
	novel->addSentence("小説を書いたりするのはあまりやらないので、このあとがきも含め拙い文章になってしまいましたが、ちゃんと言いたいことは伝わりましたでしょうか");
	novel->addSentence("ぶっちゃけ、私は脱出ゲームはすぐに攻略見ちゃう人なので、ギミックなどは上手くなかったかもしれませんが、できるだけレベルを落としたつもりです。ゲーム自体が理不尽じゃどうしようもありませんからね（苦笑）");
	novel->addSentence("プログラムはシステムはほとんど自分で考えて書いたのですが、まだまだアマチュアなのでバグなどもあったかもしれません。見つけたら連絡お願いします…");
	novel->addSentence("なんか言い訳だらけになってしましましたが。それなりに心を込めて作ったのでここまでプレイしてもらえたら、本当にうれしいです。");
	novel->addSentence("レイ〇ン教授シリーズが好きで、ゲーム自体は似たようなものを目指して作りました。次があれば逆転〇判も目指そうかなと考えてたりしてます。");
	novel->addSentence("最後になりますが、理不尽ごっこ。お楽しみいただけたでしょうか。ここまでプレイしていただき、本当にありがとうございました！");
	novel->setEndTask();
	this->addChild(novel, 5, "novel");

}

void Extra::transition(cocos2d::CallFunc* func) {
	auto layer = getChildByName("layer");
	func->retain();
	layer->setCascadeOpacityEnabled(true);
	layer->getEventDispatcher()->setEnabled(false);
	layer->runAction(Sequence::create(
		FadeOut::create(0.5f),
		CallFunc::create([this] {
			getChildByName("layer")->getEventDispatcher()->setEnabled(true);
			getChildByName("layer")->removeAllChildren();
	}),	
		func,
		FadeIn::create(0.5f),
		NULL));
}