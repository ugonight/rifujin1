#include "item.h"

#include "control.h"

USING_NS_CC;

static Item* instanceOfItem;

Item* Item::sharedItem() {
	return instanceOfItem;
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
	auto rect = CCRectMake(64 * 0, 0, 64, 64);
	auto window = Sprite::create("itemWindow.png",rect);
	window->setPosition(Vec2(15 + origin.x, -15 + origin.y + visibleSize.height));
	window->setAnchorPoint(Vec2(0.0f, 1.0f));
	addChild(window, 2, "window");

	//アイテムリストウィンドウ
	rect = CCRectMake(64, 0, 64 * 0, 64);
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
	listener->onTouchBegan = CC_CALLBACK_2(Item::touchEvent, this);
	listener->onTouchMoved = CC_CALLBACK_2(Item::moveEvent, this);
	listener->onTouchEnded = CC_CALLBACK_2(Item::endEvent, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Item::update(float delta) {
		auto possession = getChildByName("possession");
		auto window = (Sprite*)getChildByName("listWindow");

	if (mShowWindow) {
		if (mWindowW < 64 * possession->getChildrenCount()) mWindowW += 16;
	}
	else {
		if (mWindowW > 0) mWindowW -= 16;
	}

	auto rect = CCRectMake(64, 0, mWindowW, 64);
	window->setTextureRect(rect);

	int i = 0;
	for (auto item : possession->getChildren()) {
		if (mWindowW >= 64 * i) item->setPositionX(window->getPositionX() + mWindowW - (possession->getChildrenCount() - i) * 64);
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

}

void Item::deleteItem(std::string s) {
	auto possession = getChildByName("possession");
	possession->removeChild(possession->getChildByName(s));
	mSelectedItem = "";
	auto item = (Sprite*)getChildByName("selectItem");
	item->setTextureRect(Rect(0, 0, 0, 0));
}

std::string Item::getSelectedItem() { return mSelectedItem; }

bool Item::touchEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto window = getChildByName("window");
	auto targetBox = window->getBoundingBox();
	auto touchPoint = touch->getLocation();
	if (targetBox.containsPoint(touchPoint)) {
		mShowWindow = 1;
	}

	mTouchTime = 1;

	return true;
}

void Item::moveEvent(cocos2d::Touch* touch, cocos2d::Event* event) {
	mTouchTime = 0;

	if (mShowWindow) {
		auto possession = getChildByName("possession");
		auto frame = getChildByName("frame");

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
	if (mSelectedItem != "") item->setTexture(mItemList[mSelectedItem]->getImage());

}

void Item::showAboutItem() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Control::me->pauseField();

	auto aboutItem = Sprite::create("aboutItem.png");
	aboutItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(aboutItem, 2);

}