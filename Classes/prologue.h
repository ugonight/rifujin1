#pragma once
#include "cocos2d.h"
#include "novel.h"

class Prologue  : public cocos2d::Scene {

private:
	int playBGM;

	typedef void(Prologue::*State)();

	State mState;

	void scene1();
	void scene1_();
	void scene1__();
	void scene2();
	void scene3();
	void scene4();
	void scene5();
	void scene5_();

public:
	//static cocos2d::Scene* create();
	//static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);


	CREATE_FUNC(Prologue);
};