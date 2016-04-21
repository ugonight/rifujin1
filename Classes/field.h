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

	void pauseEventListener();
	void resumeEventListener();

public:
	//virtual bool init() override;
	virtual void update(float delta);

	bool getExistObject(std::string objName);

	void FadeOut();
	void FadeIn();

	virtual void chengedField();	//現在のフィールドに切り替わった時のイベント

	CREATE_FUNC(Field);
};