#include "field.h"

USING_NS_CC;

//bool Field::init() {
//	if (!Layer::init())
//	{
//		return false;
//	}
//
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//	auto bg = Sprite::create("forest1.png");
//	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//	this->addChild(bg, 0);
//
//	auto area = ObjectN::create();
//	area->setArea(650, 300, 100, 100);
//	area->setItemGetEvent("crayon_g");
//	this->addChild(area, 1, "crayon_g");
//
//	return true;
//}

void Field::update(float delta) {
	//ノベルの表示が終わっていたらタッチイベントを有効にする
	Novel* novel = (Novel*)(this->getChildByTag(10));	//ノベルのタグ:10
	if (novel) {
		if (novel->getEndFlag()) {
			resumeEventListener();
			removeChild(novel);
		}
	}
}

void Field::addObject(ObjectN* obj, std::string s, int z, bool addchild){
	mObjectList[s] = obj;
	obj->retain();
	if (addchild) this->addChild(obj, z, s);
}

bool Field::getExistObject(std::string s) {
	return mObjectList[s]->getReferenceCount() > 1;
}

void Field::FadeOut(){
	this->setCascadeOpacityEnabled(true);
	this->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
}

void Field::FadeIn() {
	this->setCascadeOpacityEnabled(true);
	this->setOpacity(0.0f);
	this->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create(CC_CALLBACK_0(Field::chengedField, this)), NULL));
	
	this->scheduleUpdate();
	for (auto it : this->getChildren()) {
		it->scheduleUpdate();
	}
}

void Field::chengedField() {
	//現在のフィールドに移動したときに呼び出される処理を書く
}

void Field::pauseEventListener() {
	for (auto it : this->getChildren()) {
		//it->second->setEventListenerEnabled(false);
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->pauseEventListenersForTarget(it);
	}
}

void Field::resumeEventListener() {
	for (auto it : this->getChildren()) {
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->resumeEventListenersForTarget(it);
	}
}
