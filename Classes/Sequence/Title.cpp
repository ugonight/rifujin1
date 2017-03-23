#include "Title.h"
#include "prologue.h"
#include "extra.h"
#include "SimpleAudioEngine.h"

#include "System/control.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Title::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Title::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Title::init() {

	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// タイトルロゴ
	auto logo = Sprite::create("title/logo.png");
	logo->setPosition(Vec2(display.width / 2 + origin.x, display.height / 2 + origin.y));
	logo->setOpacity(0.0f);
	auto seq = Sequence::create(
		FadeIn::create(1.0f),
		NULL
		);
	logo->runAction(seq);
	this->addChild(logo, 1, "logo");

	//背景
	auto bg = Sprite::create("title/back.png");
	bg->setPosition(Vec2(display.width / 2 + origin.x, display.height / 2 + origin.y));
	this->addChild(bg, 0, "bg");

	// メニュー
	auto menu = Menu::create();
	//menu->setPosition(Vec2::ZERO);
	menu->setPosition(Vec2(origin.x, origin.y));
	menu->setOpacity(0.0f);
	menu->runAction(FadeIn::create(1.0f));
	this->addChild(menu, 2);

	//はじめる
	auto startBtn = MenuItemImage::create(
		"title/start_off.png",
		"title/start_on.png",
		"title/start_off.png",
		CC_CALLBACK_1(Title::startBtnCallback, this)
		);
	startBtn->setPosition(Vec2(140, 250));
	menu->addChild(startBtn);

	//つづきから
	auto continueBtn = MenuItemImage::create(
		"title/continue_off.png",
		"title/continue_on.png",
		"title/continue_void.png",
		CC_CALLBACK_1(Title::continueBtnCallback, this)
		);
	continueBtn->setPosition(Vec2(420, 250));
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "saveData.plist";
	continueBtn->setEnabled(FileUtils::getInstance()->isFileExist(file));
	menu->addChild(continueBtn);

	//おまけ
	auto extraBtn = MenuItemImage::create(
		"title/extra_off.png",
		"title/extra_on.png",
		"title/extra_void.png",
		CC_CALLBACK_1(Title::extraBtnCallback, this)
	);
	extraBtn->setPosition(Vec2(700, 260));
	extraBtn->setEnabled(UserDefault::getInstance()->getBoolForKey("clear"));
	menu->addChild(extraBtn);

	//キャラクター
	auto chara = Sprite::create();
	chara->setPosition(Vec2(854 + 200 + origin.x, 125 + origin.y));
	auto animation = Animation::create();
	animation->addSpriteFrameWithFileName("title/walk1.png");
	animation->addSpriteFrameWithFileName("title/walk2.png");
	animation->setDelayPerUnit(1.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto action = Animate::create(animation);
	chara->runAction(action);
	auto seq2 = Sequence::create(
		MoveTo::create(20.0f,Vec2(-200 + origin.x,125 + origin.y)),
		MoveTo::create(0.0f, Vec2(854 + 200 + origin.x, 125 + origin.y)),
		NULL
		);
	auto repeat = RepeatForever::create(seq2);
	chara->runAction(repeat);
	this->addChild(chara, 1, "chara");

	//BGM
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/title.ogg"); //WakeUpSceneFactoryへ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/days.ogg");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/dream.ogg");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/misery.ogg");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/color.ogg");
	playBGM = 0;
	
	//SE
	SimpleAudioEngine::getInstance()->preloadEffect("SE/se1.ogg");
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.8f);
	SimpleAudioEngine::getInstance()->preloadEffect("SE/po.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("SE/get.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("SE/set.ogg");


	return true;
}

void Title::startBtnCallback(Ref* pSender){
	//SE
	SimpleAudioEngine::getInstance()->playEffect("SE/se1.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Prologue::create(), Color3B::WHITE));
}
void Title::continueBtnCallback(Ref* pSender) {
	//SE
	SimpleAudioEngine::getInstance()->playEffect("SE/se1.ogg");
	//BGM
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/dream.ogg", true);
	auto control = Control::create();
	control->load();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, control, Color3B::WHITE));
}

void Title::extraBtnCallback(Ref* pSender) {
	//SE
	SimpleAudioEngine::getInstance()->playEffect("SE/se1.ogg");
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Extra::create(), Color3B::WHITE));
}

void Title::update(float delta) {
	if (!playBGM) {
		playBGM++;
		SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/title.ogg", true);
	}
}