#pragma once
#include "cocos2d.h"

class Title : public cocos2d::Layer {
private:
	int playBGM;

public:
	//static cocos2d::Scene* create();
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void update(float delta);

	void startBtnCallback(Ref* pSender);
	void continueBtnCallback(Ref* pSender);
	void extraBtnCallback(Ref* pSender);

	CREATE_FUNC(Title);
};