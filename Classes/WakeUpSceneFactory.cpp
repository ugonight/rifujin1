#include "WakeUpSceneFactory.h"
#include "Title.h"

USING_NS_CC;

cocos2d::Scene* WakeUpSceneFactory::create() {

	auto scene = Scene::create();

	auto *Title = Title::create();
	scene->addChild(Title, 1, "title");

	return scene;
}