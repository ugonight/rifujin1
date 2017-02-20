#pragma  execution_character_set("utf-8")

#include "novel.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
	//for (int i = 0; i < 3; i++) {
	//	mLabel[i] = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 24);
	//	mLabel[i]->setPosition(Vec2(origin.x + 50,
	//		origin.y + visibleSize.height - 340 - i * 30));
	//	mLabel[i]->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	//	mLabel[i]->setColor(Color3B::BLUE);
	//	this->addChild(mLabel[i], 3);
	//}
	auto label = Label::createWithTTF("", "fonts/APJapanesefontT.ttf", 24);
	label->setPosition(Vec2(origin.x + 50,
				origin.y + visibleSize.height - 340));
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setColor(Color3B::BLUE);
	label->enableOutline(Color4B::WHITE, 2);
	label->setDimensions(750, 130);
	this->addChild(label, 3, "label");

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Novel::touchEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//バックログ
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.plist";

	if (FileUtils::getInstance()->isFileExist(file)) {
		mLog = FileUtils::getInstance()->getValueVectorFromFile(file);
	}

	auto log = Sprite::create("log.png");
	log->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	log->setPosition(Vec2(visibleSize.width -15 + origin.x, -15 + origin.y + visibleSize.height));
	addChild(log, 1, "log");

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Novel::logEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, log);


	return true;
}

void Novel::func() { 
	mNovelNum = 1;
	auto label = (Label*)this->getChildByName("label");
	label->setString(mSentense[mNovelNum]);
	setDelayAnime();
}

bool Novel::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto label = (Label*)this->getChildByName("label");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (touch->getLocation().y < visibleSize.height / 2) {

		if (endCheck()) {	//文がすべて表示されていたら
			//バックログに記録
			if (this->getOpacity() == 255) mLog.push_back(Value(mSentense[mNovelNum]));
			if (mSentense.size() - 1 > mNovelNum) {	//文リストの最後でなければ
				//次の分をセット
				mNovelNum++;
				label->setString(mSentense[mNovelNum]);
				setDelayAnime();
			}
			else if (mSentense.size() - 1 == mNovelNum && this->getOpacity() == 255) {	//文リストの最後なら
				this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create(CC_CALLBACK_0(Novel::end, this)),/* RemoveSelf::create(true),*/ NULL));
				//スプライト全部をフェードアウトする
				Sprite* spr;
				for (auto child : this->getChildren()) {
					spr = (Sprite*)child;
					spr->runAction(FadeOut::create(1.0f));
				}

				//ログを保存
				mLog.push_back(Value(""));
				auto path = FileUtils::getInstance()->getWritablePath();
				auto file = path + "speak.plist";
				FileUtils::getInstance()->writeValueVectorToFile(mLog, file);

			}
		}
		else {
			for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
				auto AChar = label->getLetter(i);
				if (nullptr != AChar) {
					AChar->setOpacity(255);
					AChar->stopAllActions();
				}
			}
		}
		
	}

	return true;
}

void Novel::end(){	
	mEndFlag = 1;
}

void Novel::update(float delta) {
	//int len;
	//int num = 90;
	//for (int i = 0; i < 3; i++) {
	//	len = (mCount > num * (i + 1)) ? num * (i + 1) : mCount - num * i;
	//	len = len < 0 ? 0 : len;
	//	if (mSentense[mNovelNum].size() < num * i) break;
	//	mLabel[i]->setString(mSentense[mNovelNum].substr(num * i, len));
	//}


	//if (mNovelNum > 0) mCount++;

	updateImg();
	updateColor();
	updateFunc();
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

	FTask ftsk = { -1, NULL };
	mFuncTask.push_back(ftsk);

	updateImg();
	updateColor();
	updateFunc();
}

void Novel::updateColor() {
	if (mColorTask[0].num == mNovelNum) {
		//for (int i = 0; i < 3; i++)mLabel[i]->setColor(mColorTask[0].color);
		auto label = (Label*)this->getChildByName("label");
		label->setTextColor((Color4B)mColorTask[0].color);
		mColorTask.erase(mColorTask.begin());
	}
}

void Novel::updateFunc() {
	if (mFuncTask[0].num == mNovelNum) {
		this->runAction(mFuncTask[0].func);
		mFuncTask.erase(mFuncTask.begin());
	}
}

void Novel::setFontColor(cocos2d::Color3B c) {
	CTask tsk = {mNovelSetNum, c};
	mColorTask.push_back(tsk);
}

void Novel::addEvent(cocos2d::CallFunc* func) {
	FTask tsk = {mNovelNum, func};
	mFuncTask.push_back(tsk);
}

bool Novel::endCheck() {
	auto label = (Label*)getChildByName("label");
	for (int i = 0; i < label->getStringLength() + label->getStringNumLines(); i++) {
		auto AChar = label->getLetter(i);
		if (nullptr != AChar) {
			if (AChar->getOpacity() < 255) {
				return false;
			}
		}
	}
	return true;
}

void Novel::setDelayAnime() {
	auto label1 = (Label*)getChildByName("label");

	for (int i = 0; i < label1->getStringLength() + label1->getStringNumLines(); i++) {
		auto AChar = label1->getLetter(i);
		mCharNum = 0;
		if (nullptr != AChar) {
			mCharNum++;
			AChar->setOpacity(0.0f);
			AChar->runAction(
				Sequence::create(
					DelayTime::create(0.05f*i),
					FadeIn::create(0.05f),
					CallFunc::create([this]() {	if (mCharNum % 4 == 0) SimpleAudioEngine::getInstance()->playEffect("SE/po.ogg"); }),	//全角の最初で鳴らす
					NULL
				));
		}
	}
}

bool Novel::logEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	if (targetBox.containsPoint(touchPoint))
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto layer = Layer::create();
		this->addChild(layer, 5, "layer_l");

		//背景
		Rect rect = Rect(0, 0, visibleSize.width, visibleSize.height);
		Sprite* square = Sprite::create();
		square->setTextureRect(rect);
		square->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		square->setColor(Color3B(0, 0, 0));
		square->setOpacity(128);
		layer->addChild(square, 0, "back_l");
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			mLogScrollX = touch->getLocation().x;
			mLogScrollY = touch->getLocation().y;
			return true; 
		};
		listener->onTouchMoved = [this](Touch* touch, Event* event) {
			auto label = (Label*)this->getChildByName("layer_l")->getChildByName("label");
			auto height = Director::getInstance()->getVisibleSize().height;
			label->setPosition(label->getPositionX() + touch->getLocation().x - mLogScrollX,label->getPositionY() + touch->getLocation().y - mLogScrollY);
			if (label->getPositionY() > label->getDimensions().height + height) {
				label->setPositionY(label->getDimensions().height + height);
			}
			else if (label->getPositionY() < 0) {
				label->setPositionY(0.0f);
			}
			mLogScrollY = touch->getLocation().y;
			if (label->getPositionX() < -label->getDimensions().width) {
				label->setPositionX(-label->getDimensions().width);
			}
			else if (label->getPositionX() > 20) {
				label->setPositionX(20.0f);
			}
			mLogScrollX = touch->getLocation().x;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, square);

		//文字
		std::stringstream str;
		for (auto s : mLog) {
			str << s.asString() << "\n";
		}

		auto label = Label::createWithTTF(str.str(), "fonts/APJapanesefontT.ttf", 24);
		label->setPosition(Vec2(origin.x + 20 ,origin.y + visibleSize.height - 20));
		label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		label->setColor(Color3B::WHITE);
		label->setDimensions(visibleSize.width * 3, label->getLineHeight() * (label->getStringNumLines() + 1));
		label->setPositionY(label->getDimensions().height);
		layer->addChild(label, 3, "label");

		//閉じる
		auto close = Sprite::create("log_.png");
		close->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		close->setPosition(Vec2(visibleSize.width - 15 + origin.x, -15 + origin.y + visibleSize.height));
		layer->addChild(close, 1, "close");
		listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) { return true; };
		listener->onTouchEnded =[this](Touch* touch, Event* event) {
			auto target = (Sprite*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				this->removeChildByName("layer_l");
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, close);
	}
	return true;
}