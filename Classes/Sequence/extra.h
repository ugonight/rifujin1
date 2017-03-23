#pragma once

#include "cocos2d.h"
#include "System/novel.h"

class Extra : public cocos2d::Scene {

private:
	void menu();
	void character();
	void music();
	void afterword();

	void transition(cocos2d::CallFunc *func);

public:
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Extra);
};