#pragma once
#include "cocos2d.h"

#include "object.h"
#include "item.h"
#include "control.h"
#include "novel.h"

class Field : public cocos2d::Layer {
protected:
	std::map<std::string, ObjectN*> mObjectList;
	void addObject(ObjectN* obj,std::string objName, int ZOder, bool addChild);

	//void pauseEventListener();
	//void resumeEventListener();



public:
	//virtual bool init() override;
	virtual bool init();
	virtual void update(float delta);

	bool getExistObject(std::string objName);

	void FadeOut();
	void FadeIn();

	void pauseEventListener();
	void resumeEventListener();

	virtual void changedField();	//���݂̃t�B�[���h�ɐ؂�ւ�������̃C�x���g
	virtual void initField();		//�t�B�[���h�ɃI�u�W�F�N�g��z�u
	
	
	CREATE_FUNC(Field);
};