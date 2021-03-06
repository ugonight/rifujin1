#include "field.h"

USING_NS_CC;

Field::~Field() {
	for (auto obj : mObjectList) {
		CC_SAFE_RELEASE_NULL(obj.second);
	}
}


bool Field::init() {
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();

	initField();

	return true;
}

void Field::initField() {
	//オブジェクトを配置したり
}

void Field::update(float delta) {
	//ノベルの表示が終わっていたらタッチイベントを有効にする
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			//resumeEventListener();
			removeChild(novel);
		}
		else {
			Control::me->setCursor(7);
		}
	}
}

void Field::addObject(ObjectN* obj, std::string s, int z, bool addchild){
	mObjectList[s] = obj;
	obj->retain();	
	obj->setZOrder(z);
	if (addchild) this->addChild(obj, z, s);
}

bool Field::getExistObject(std::string s) {
	return mObjectList[s]->getReferenceCount() > 1;
}

ObjectN* Field::getObject(std::string s) {
	return mObjectList[s];
}

void Field::FadeOut(){
	this->setCascadeOpacityEnabled(true);
	this->pauseEventListener();
	this->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
}

void Field::FadeIn() {
	this->setCascadeOpacityEnabled(true);
	//this->resumeEventListener();
	this->setOpacity(0.0f);
	this->runAction(Sequence::create(FadeIn::create(0.5f),
		CallFunc::create([this] {
		this->resumeEventListener();
		this->scheduleUpdate();
		for (auto it : this->getChildren()) {
			it->scheduleUpdate();
		}
	}), CallFunc::create(CC_CALLBACK_0(Field::changedField, this)), NULL));
	
}

void Field::changedField() {
	//現在のフィールドに移動したときに呼び出される処理を書く
}

void Field::pauseEventListener() {
	//for (auto it : this->getChildren()) {
	//	//it->second->setEventListenerEnabled(false);
	//	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//	dispatcher->pauseEventListenersForTarget(it);
	//}
	for (auto it : mObjectList) {
		it.second->getEventDispatcher()->setEnabled(false);
	}
}

void Field::resumeEventListener() {
	//for (auto it : this->getChildren()) {
	//	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//	dispatcher->resumeEventListenersForTarget(it);
	//}
	for (auto it : mObjectList) {
		it.second->getEventDispatcher()->setEnabled(true);
	}
}

cocos2d::ValueMap Field::saveField() {
	ValueMap data;
	for (auto obj : mObjectList) {
			data[obj.first + "_visible"] = getChildByName(obj.first);//obj.second->getReferenceCount() > 1;		//addChild()されてるか
			data[obj.first + "_state"] = obj.second->getState();					//状態
			data[obj.first + "_msg"] = obj.second->getMsg();						//メッセージ
			data[obj.first + "_texture"] = obj.second->getTexture()->getPath();			//イメージ
			data[obj.first + "_field"] = obj.second->getField();	//移動先フィールド
			data[obj.first + "_opacity"] = (float)obj.second->getOpacity();	//透明度
	}
	return data;
}

void Field::loadField(cocos2d::ValueMap data) {
	for (auto obj : mObjectList) {
		if (data[obj.first + "_visible"].asBool()) {
			if (!this->getChildByName(obj.first)) {	//初期状態で消えている時
				addChild(obj.second, obj.second->getLocalZOrder(), obj.first);
			}
		}
		else {
			if (data[obj.first + "_visible"].isNull()) continue;	//セーブデータに登録されてなかったら無視
			if (this->getChildByName(obj.first)) {	//初期状態で表示されている時
				removeChild(obj.second);
			}
		}
		//状態
		obj.second->setState(data[obj.first + "_state"].asInt());
		//メッセージ
		obj.second->setMsg(data[obj.first + "_msg"].asString());
		//イメージ
		obj.second->setTexture(data[obj.first + "_texture"].asString());
		//フィールド
		obj.second->setFieldChangeEvent(data[obj.first + "_field"].asString());
		//透明度
		obj.second->setOpacity(data[obj.first + "_opacity"].asFloat());
	}
}