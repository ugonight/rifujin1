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
	//�I�u�W�F�N�g��z�u������
}

void Field::update(float delta) {
	//�m�x���̕\�����I����Ă�����^�b�`�C�x���g��L���ɂ���
	Novel* novel = (Novel*)(this->getChildByName("novel"));
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
	this->resumeEventListener();
	this->setOpacity(0.0f);
	this->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create(CC_CALLBACK_0(Field::changedField, this)), NULL));
	
	this->scheduleUpdate();
	for (auto it : this->getChildren()) {
		it->scheduleUpdate();
	}
}

void Field::changedField() {
	//���݂̃t�B�[���h�Ɉړ������Ƃ��ɌĂяo����鏈��������
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

cocos2d::ValueMap Field::saveField() {
	ValueMap data;
	for (auto obj : mObjectList) {
			data[obj.first + "_visible"] = getChildByName(obj.first);//obj.second->getReferenceCount() > 1;		//addChild()����Ă邩
			data[obj.first + "_state"] = obj.second->getState();					//���
			data[obj.first + "_msg"] = obj.second->getMsg();						//���b�Z�[�W
			data[obj.first + "_texture"] = obj.second->getTexture()->getPath();			//�C���[�W
			data[obj.first + "_field"] = obj.second->getField();	//�ړ���t�B�[���h
			data[obj.first + "_opacity"] = (float)obj.second->getOpacity();	//�����x
	}
	return data;
}

void Field::loadField(cocos2d::ValueMap data) {
	for (auto obj : mObjectList) {
		if (data[obj.first + "_visible"].asBool()) {
			if (!this->getChildByName(obj.first)) {	//������Ԃŏ����Ă��鎞
				addChild(obj.second, obj.second->getLocalZOrder(), obj.first);
			}
		}
		else {
			if (data[obj.first + "_visible"].isNull()) continue;	//�Z�[�u�f�[�^�ɓo�^����ĂȂ������疳��
			if (this->getChildByName(obj.first)) {	//������Ԃŕ\������Ă��鎞
				removeChild(obj.second);
			}
		}
		//���
		obj.second->setState(data[obj.first + "_state"].asInt());
		//���b�Z�[�W
		obj.second->setMsg(data[obj.first + "_msg"].asString());
		//�C���[�W
		obj.second->setTexture(data[obj.first + "_texture"].asString());
		//�t�B�[���h
		obj.second->setFieldChangeEvent(data[obj.first + "_field"].asString());
		//�����x
		obj.second->setOpacity(data[obj.first + "_opacity"].asFloat());
	}
}