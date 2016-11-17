#include "WakeUpSceneFactory.h"
#include "Title.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene* WakeUpSceneFactory::create() {

	auto scene = Scene::create();

	auto *Title = Title::create();
	scene->addChild(Title, 1, "title");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/title.ogg");

	return scene;
}