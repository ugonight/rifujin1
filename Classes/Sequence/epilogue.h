#pragma once

#include "cocos2d.h"
#include "System/novel.h"

class Epilogue : public cocos2d::Scene {

private:
	int playBGM;

public:
	//static cocos2d::Scene* create();
	//static cocos2d::Scene* createScene();

	virtual bool init();
	//virtual void update(float delta);


	CREATE_FUNC(Epilogue);
};