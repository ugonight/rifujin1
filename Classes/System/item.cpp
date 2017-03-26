#include "item.h"

#include "control.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

static Item* instanceOfItem;

Item* Item::sharedItem() {
	return instanceOfItem;
}

Item::~Item() {
	for (auto item : mItemList) {
		delete item.second;
	}
}

bool Item::init() {
	if (!Layer::init()) {
		return false;
	}

	scheduleUpdate();

	instanceOfItem = this;

	mShowWindow = 0;
	mShowAboutItem = 0;
	mWindowW = 0;
	mTouchTime = 0;
	mSelectedItem = "";

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//選択アイテムウィンドウ
	auto rect = Rect(64 * 0, 0, 64, 64);
	auto window = Sprite::create("itemWindow.png",rect);
	window->setPosition(Vec2(15 + origin.x, -15 + origin.y + visibleSize.height));
	window->setAnchorPoint(Vec2(0.0f, 1.0f));
	addChild(window, 2, "window");

	//アイテムリストウィンドウ
	rect = Rect(64, 0, 64 * 0, 64);
	window = Sprite::create("itemWindow.png", rect);
	window->setPosition(Vec2(15 + origin.x + 64, -15 + origin.y + visibleSize.height));
	window->setAnchorPoint(Vec2(0.0f, 1.0f));
	addChild(window, 0, "listWindow");

	//アイテム選択枠
	auto frame = Sprite::create("activeItem.png");
	frame->setPosition(Vec2(15 + origin.x, -15 + origin.y + visibleSize.height));
	frame->setAnchorPoint(Vec2(0.0f, 1.0f));
	addChild(frame, 1, "frame");

	//選択中アイテム
	auto selectItem = Sprite::create();
	selectItem->setPosition(Vec2(15 + origin.x, -15 + origin.y + visibleSize.height));
	selectItem->setAnchorPoint(Vec2(0.0f, 1.0f));
	addChild(selectItem, 3, "selectItem");

	initItem();

	//取得しているアイテム
	auto possession = Layer::create();
	addChild(possession, 1, "possession");

	//タッチイベント
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Item::touchEvent, this);
	listener->onTouchMoved = CC_CALLBACK_2(Item::moveEvent, this);
	listener->onTouchEnded = CC_CALLBACK_2(Item::endEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Item::update(float delta) {
	auto possession = getChildByName("possession");
	auto window = (Sprite*)getChildByName("listWindow");
	auto baseWindow = (Sprite*)getChildByName("window");

	if (mShowWindow) {
		if (mWindowW < 64 * possession->getChildrenCount()) mWindowW += 16;
	}
	else {
		if (mWindowW > 0) mWindowW -= 16;
	}

	auto rect = Rect(64, 0, mWindowW, 64);
	window->setTextureRect(rect);

	int i = 0;
	for (auto item : possession->getChildren()) {
		if (mWindowW > 64 * i) {
			item->setPositionX(window->getPositionX() + mWindowW - (possession->getChildrenCount() - i) * 64);		
			if (baseWindow->getPositionX() > item->getPositionX()) item->setPositionX(baseWindow->getPositionX());	//左に飛び出すのを防ぐ（突貫工事）
		}
		else {
			item->setPositionX(baseWindow->getPositionX());
		}
		i++;
	}

	//AI表示
	if (mTouchTime > 0) mTouchTime++;
	if (mTouchTime == 30 && mSelectedItem != "" && !mShowAboutItem) {
		showAboutItem();
		mShowAboutItem = 1;
	}
}

void Item::getItem(std::string s, Point p) {
	mItemList[s]->setGetFlag(1);

	auto item = Sprite::create(mItemList[s]->getImage());

	//登録
	auto possession = getChildByName("possession");
	auto window = getChildByName("window");
	item->setPosition(window->getPosition());
	item->setAnchorPoint(Vec2(0.0f, 1.0f));
	possession->addChild(item, 0, s);
	
	//jumpアニメ
	item = Sprite::create(mItemList[s]->getImage());
	item->setPosition(p);
	item->runAction(Sequence::create(JumpBy::create(0.5f, Vec2(0, 0), 200, 1),RemoveSelf::create(),NULL));
	addChild(item, 1);

	//パーティクル
	// Cocos2d-x v3.x
	auto size = Director::getInstance()->getWinSize();
	auto m_emitter = ParticleSystemQuad::createWithTotalParticles(100);
	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("spark.png"));

	// v2.x及びv3.xで使用することができます
	m_emitter->setDuration(0.2f);
	m_emitter->setGravity(Point(0, -240)); // v2.xでは CCPoint( 0, -240 )
	m_emitter->setAngle(90.0f);
	m_emitter->setAngleVar(90.0f);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosition(p);
	m_emitter->setPosVar(Point(0, 0));
	m_emitter->setLife(0.5f);
	m_emitter->setLifeVar(0.0f);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(255, 255, 255, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(40);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100);
	m_emitter->setSpeed(300.0f);
	m_emitter->setSpeedVar(100.0f);
	m_emitter->setAutoRemoveOnFinish(true);
	BlendFunc func;
	func.src = GL_SRC_ALPHA;
	func.dst = GL_ONE;
	m_emitter->setBlendFunc(func);
	addChild(m_emitter, 10);

	//SE
	SimpleAudioEngine::getInstance()->playEffect("SE/get.ogg");
}

void Item::deleteItem(std::string s) {
	auto possession = getChildByName("possession");
	possession->removeChild(possession->getChildByName(s));
	mSelectedItem = "";
	auto item = (Sprite*)getChildByName("selectItem");
	item->setTextureRect(Rect(0, 0, 0, 0));
	mItemList[s]->setGetFlag(0);
}

std::string Item::getSelectedItem() { return mSelectedItem; }

bool Item::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	bool validity = false;	//タッチイベントが有効になるか

	auto window = getChildByName("window");
	auto targetBox = window->getBoundingBox();
	auto touchPoint = touch->getLocation();
	if (targetBox.containsPoint(touchPoint)) {
		mShowWindow = 1;
		mTouchTime = 1;

		validity = true;
	}

	//AIが表示されているとき
	if (mShowAboutItem) {
		validity = true;
		auto AboutItem = getChildByName("AboutItem");
		auto targetBox2 = AboutItem->getBoundingBox();
		if (targetBox2.containsPoint(touchPoint)) {	//AIの枠の領域をタップしたか
		
		}
		else {
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			if (touchPoint.y < -15 - 64 + origin.y + visibleSize.height) {
				mShowAboutItem = 0;
				AboutItem->runAction(FadeOut::create(0.2f));
				AboutItem->runAction(Sequence::create(ScaleBy::create(0.2f, 0.5f), RemoveSelf::create(), NULL));
				//removeChild(AboutItem);
				//Control::me->resumeField();
				Control::me->deleteAI();
			}
		}
	}

	return validity;
}

void Item::moveEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto window = getChildByName("window");
	auto targetBox = window->getBoundingBox();
	auto touchPoint = touch->getLocation();	
	auto possession = getChildByName("possession");
	auto frame = getChildByName("frame");

	if (!targetBox.containsPoint(touchPoint)) {
		mTouchTime = 0;
	}

	if (mShowWindow && mWindowW >= 64 * possession->getChildrenCount()) {
		int i = 0;
		for (auto item : possession->getChildren()) {
			if (touch->getLocation().x > item->getPositionX() && touch->getLocation().x < item->getPositionX() + 64) {
				frame->setPositionX(item->getPositionX());
				mSelectedItem = item->getName();
			}
			i++;
		}
	}
}

void Item::endEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	mShowWindow = 0;
	mTouchTime = 0;

	auto window = getChildByName("window");
	auto frame = getChildByName("frame");
	auto item = (Sprite*)getChildByName("selectItem");

	frame->setPositionX(window->getPositionX());
	if (mSelectedItem != "") {
		item->setTexture(mItemList[mSelectedItem]->getImage());
	}
}

void Item::showAboutItem() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Control::me->pauseField();
	Control::me->showAI(mSelectedItem);

	auto aboutItem = Sprite::create("AboutItem.png");
	aboutItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	aboutItem->setOpacity(0.0f);
	//aboutItem->setScale(0.5f);
	aboutItem->runAction(FadeIn::create(0.2f));
	//aboutItem->runAction(ScaleBy::create(0.2f,2.0f));
	addChild(aboutItem, 2, "AboutItem");

	//SE
	SimpleAudioEngine::getInstance()->playEffect("SE/set.ogg");
}

void Item::saveItem(cocos2d::ValueMap* map) {	
	ValueMap data;
	for (auto item : mItemList) {
		//map->insert(item.first, item.second->getGetFlag());
		data[item.first] = item.second->getGetFlag();
	}
	map->insert(data.begin(), data.end());
}

void Item::loadItem(cocos2d::ValueMap map) {
	for (auto item : mItemList) {
		if (map[item.first].asBool()) {
			mItemList[item.first]->setGetFlag(1);
			auto item_ = Sprite::create(mItemList[item.first]->getImage());
			//登録
			auto possession = getChildByName("possession");
			auto window = getChildByName("window");
			item_->setPosition(window->getPosition());
			item_->setAnchorPoint(Vec2(0.0f, 1.0f));
			possession->addChild(item_, 0, item.first);
		}
	}
}

