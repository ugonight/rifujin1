#pragma  execution_character_set("utf-8")
#include "novel.h"

USING_NS_CC;

bool Novel::init() {

	if (Layer::init() == false)
		return false;

	this->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mNovelNum  = mCount = 0;
	mNovelSetNum = 1;
	mEndFlag = 0;
	
	mSentense.push_back("");

	//背景
	auto bg = Sprite::create();
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "bg");

	//キャラクター・センター
	auto charaC = Sprite::create();
	charaC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaC, 1, "charaC");

	//キャラクター・レフト
	auto charaL = Sprite::create();
	charaL->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaL, 1, "charaL");

	//キャラクター・ライト
	auto charaR = Sprite::create();
	charaR->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(charaR, 1, "charaR");

	//メッセージボックス
	auto msg = Sprite::create("msg.png");
	msg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	msg->setOpacity(0.0f);
	auto seq = Sequence::create(
		FadeIn::create(0.5f),
		//CallFunc::create(this, callfunc_selector(Novel::func)),
		CallFunc::create(this, callfunc_selector(Novel::func)),
		NULL);
	msg->runAction(seq);
	this->addChild(msg, 2);

	//文字
	for (int i = 0; i < 3; i++) {
		mLabel[i] = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 24);
		mLabel[i]->setPosition(Vec2(origin.x + 50,
			origin.y + visibleSize.height - 340 - i * 30));
		mLabel[i]->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		mLabel[i]->setColor(Color3B::BLUE);
		this->addChild(mLabel[i], 3);
	}


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Novel::touchEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void Novel::func() { mNovelNum = 1; }

bool Novel::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) { 
	if (mSentense.size() - 1 > mNovelNum) {	//文リストの最後でなければ
		if (mSentense[mNovelNum].size() < mCount) {	//文がすべて表示されていたら
			mNovelNum++;
			mCount = 0;
			for (int i = 0; i < 3; i++) mLabel[i]->setString("");
		}
		else {
			mCount = mSentense[mNovelNum].size();
		}
	}
	else if (mSentense.size() - 1 == mNovelNum) {	//文リストの最後なら
		if (mSentense[mNovelNum].size() < mCount) {	//文がすべて表示されていたら
			this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create(CC_CALLBACK_0(Novel::end, this)),/* RemoveSelf::create(true),*/ NULL));
			//スプライト全部をフェードアウトする
			Sprite* spr;
			for (auto child : this->getChildren()) {
				spr = (Sprite*)child;
				spr->runAction(FadeOut::create(1.0f));
			}
		}
		else {
			mCount = mSentense[mNovelNum].size();
		}
	}
	

	return true; 
}

void Novel::end(){	
	mEndFlag = 1;
}

void Novel::update(float delta) {
	int len;
	int num = 90;
	for (int i = 0; i < 3; i++) {
		len = (mCount > num * (i + 1)) ? num * (i + 1) : mCount - num * i;
		len = len < 0 ? 0 : len;
		if (mSentense[mNovelNum].size() < num * i) break;
		mLabel[i]->setString(mSentense[mNovelNum].substr(num * i, len));
	}


	if (mNovelNum > 0) mCount++;

	updateImg();
	updateColor();
}

void Novel::addSentence(std::string s) {
	mSentense.push_back(s);
	mNovelSetNum++;
}

void Novel::updateImg() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int num = 0;
	if (mTask[num].num == mNovelNum) {
		if ( mTask[num].imgPos == IMG_BG) {
			auto old = this->getChildByName("bg");
			old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
			
			if (mTask[num].imgName != "") {
				auto newOne = Sprite::create(mTask[num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.5f));
				this->addChild(newOne, 0, "bg");
			}
			else {
				auto bg = Sprite::create();
				bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(bg, 0, "bg");
			}
		}
		else if ( mTask[num].imgPos == IMG_CENTER) {
			auto old = this->getChildByName("charaC");
			old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
			
			if (mTask[num].imgName != "") {
				auto newOne = Sprite::create(mTask[num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.5f));
				this->addChild(newOne, 1, "charaC");
			}
			else {
				auto charaC = Sprite::create();
				charaC->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaC, 1, "charaC");
			}
		}
		else if (mTask[num].imgPos == IMG_LEFT) {
			auto old = this->getChildByName("charaL");
			old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
			
			if (mTask[num].imgName != "") {
				auto newOne = Sprite::create(mTask[num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.5f));
				this->addChild(newOne, 1, "charaL");
			}
			else {
				auto charaL = Sprite::create();
				charaL->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaL, 1, "charaL");
			}
		}
		else if (mTask[num].imgPos == IMG_RIGHT) {
			auto old = this->getChildByName("charaR");
			old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
			
			if (mTask[num].imgName != "") {
				auto newOne = Sprite::create(mTask[num].imgName);
				newOne->setPosition(old->getPosition());
				newOne->setOpacity(0.0f);

				newOne->runAction(FadeIn::create(0.5f));
				this->addChild(newOne, 1, "charaR");
			}
			else {
				auto charaR = Sprite::create();
				charaR->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
				this->addChild(charaR, 1, "charaR");
			}
		}
		mTask.erase(mTask.begin());
	}
}

bool Novel::getEndFlag(){return mEndFlag;}

void Novel::setBg(std::string s) {
	/*
	auto old = this->getChildByName("bg");
	auto newOne = Sprite::create(s);
	newOne->setPosition(old->getPosition());
	old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
	newOne->runAction(FadeIn::create(0.5f));
	this->addChild(newOne, 0, "bg");
	*/
	Task tsk = { mNovelSetNum,IMG_BG,s };
	mTask.push_back(tsk);
}

void Novel::setCharaC(std::string s) {
	/*
	auto old = this->getChildByName("charaC");
	auto newOne = Sprite::create(s);
	newOne->setPosition(old->getPosition());
	old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
	newOne->runAction(FadeIn::create(0.5f));
	this->addChild(newOne, 1, "charaC");
	*/
	Task tsk = { mNovelSetNum,IMG_CENTER,s };
	mTask.push_back(tsk);
}

void Novel::setCharaL(std::string s) {
	//auto old = this->getChildByName("charaL");
	//auto newOne = Sprite::create(s);
	//newOne->setPosition(old->getPosition());
	//old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
	//newOne->runAction(FadeIn::create(0.5f));
	//this->addChild(newOne, 1, "charaL");
	Task tsk = { mNovelSetNum,IMG_LEFT,s };
	mTask.push_back(tsk);
}

void Novel::setCharaR(std::string s) {
	//auto old = this->getChildByName("charaR");
	//auto newOne = Sprite::create(s);
	//newOne->setPosition(old->getPosition());
	//old->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(true), NULL));
	//newOne->runAction(FadeIn::create(0.5f));
	//this->addChild(newOne, 1, "charaR");
	Task tsk = { mNovelSetNum,IMG_RIGHT,s };
	mTask.push_back(tsk);
}

void Novel::setEndTask() {
	Task tsk = {-1,IMG_NONE,""};
	mTask.push_back(tsk);

	CTask ctsk = { -1, Color3B::BLACK};
	mColorTask.push_back(ctsk);

	updateImg();
	updateColor();
}

void Novel::updateColor() {
	if (mColorTask[0].num == mNovelNum) {
		for (int i = 0; i < 3; i++)mLabel[i]->setColor(mColorTask[0].color);
		mColorTask.erase(mColorTask.begin());
	}
}

void Novel::setFontColor(cocos2d::Color3B c) {
	CTask tsk = {mNovelSetNum, c};
	mColorTask.push_back(tsk);
}