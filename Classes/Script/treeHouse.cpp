#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

#define PIECE_X 6
#define PIECE_Y 3

void TreeHouse::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("treehouse.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0, "treehouse");

	auto forest2 = ObjectN::create();
	forest2->setArea(Rect(650, 420, 200, 60));
	forest2->setFieldChangeEvent("forest2");
	forest2->setCursor(2);
	addObject(forest2, "forest2", 2, true);

	auto lamp = ObjectN::create();
	lamp->setTexture("lamp.png");
	lamp->setArea(Rect(270, 430, 90, 50));
	lamp->setItemGetEvent("lamp");
	lamp->setMsg("ランプを手に入れた");
	addObject(lamp, "lamp", 2, true);

	auto floorHole = ObjectN::create();
	floorHole->setArea(Rect(550, 420, 100, 60));
	floorHole->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["floorHole"]->getState() == 0) {
			pauseEventListener();
			auto novel = Novel::create();
			novel->addEvent(CallFunc::create([this] {
				mObjectList["floorHole"]->setTexture("floorhole.png");
				mObjectList["floorHole"]->setState(1);
				mObjectList["floorHole"]->setMsg("床板が抜けている");
				Item::sharedItem()->getItem("board", Point(600, 30));
			}));
			novel->setFontColor(Color3B::BLACK);
			novel->addSentence("ボキッ…");
			novel->setFontColor(Color3B::RED);
			novel->setCharaL("chara/suama1.png");
			novel->addSentence("寿甘「ギャーーーー」");
			novel->addSentence("寿甘「床板が抜けたわ…」");
			novel->setFontColor(Color3B::BLUE);
			novel->setCharaR("chara/bandana1.png");
			novel->addSentence("バンダナ「やっぱりデ…」");
			novel->setFontColor(Color3B::RED);
			novel->addSentence("寿甘「殺す」");
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("バンダナ「ギャーーーー」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(floorHole, "floorHole", 2, true);

	auto _puzzle = ObjectN::create();
	_puzzle->setArea(Rect(210, 210, 190, 100));
	_puzzle->setTouchEvent(CallFunc::create([this] {
		if (mObjectList["_puzzle"]->getState() == 0) { 
			addChild(puzzle(), 10, "puzzle"); 
		}
		else if (mObjectList["_puzzle"]->getState() == 1) {
			pauseEventListener();
			auto novel = Novel::create();

			novel->setFontColor(Color3B::BLUE);
			novel->setCharaL("chara/tuguru1.png");
			novel->addSentence("継「ふぅ…パズルを解いたよ。」");
			novel->addSentence("継「これは…川の写真かな？」");
			novel->setFontColor(Color3B::RED);
			novel->setCharaR("chara/celine1.png");
			novel->addSentence("セリーヌ「中に何か入ってるようですね」");
			novel->addEvent(CallFunc::create([this] {
				mObjectList["_puzzle"]->setState(2);
				mObjectList["_puzzle"]->setMsg("パズルは解いてある");
				Item::sharedItem()->getItem("crayon_b", Point(300, 250));
			}));
			novel->setFontColor(Color3B::BLUE);
			novel->addSentence("継「クレヨンだ！これで川を渡ることができそうだね」");

			novel->setEndTask();
			this->addChild(novel, 10, "novel");
		}
	}));
	addObject(_puzzle, "_puzzle", 2, true);


}

cocos2d::Layer* TreeHouse::puzzle() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto layer = Layer::create();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {return true;};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
	layer->setCascadeOpacityEnabled(true);
	layer->setOpacity(0.0f);
	layer->runAction(FadeIn::create(0.3f));

	auto bg = Sprite::create("puzzle.png");
	bg->setPosition(visibleSize / 2);
	layer->addChild(bg, 0);

	const int x = PIECE_X, y = PIECE_Y;
	const int w = visibleSize.width / x, h = visibleSize.height / y;
	const int x0 = origin.x + visibleSize.width / 2 - visibleSize.width / 4, y0 = origin.y + visibleSize.height / 2 + visibleSize.height / 4;
	Sprite* piece[x][y];

	//枠線
	auto draw = DrawNode::create();
	for (int i = 0; i <= x; i++) {
		draw->drawSegment(Vec2(x0 + (w / 2 + 1)*i, y0), Vec2(x0 + (w / 2 + 1)*i, y0 - visibleSize.height / 2 - y/2), 1.0f, Color4F::BLACK);
	}
	for (int j = 0; j <= y; j++) {
		draw->drawSegment(Vec2(x0, y0 - (h / 2 + 1)*j), Vec2(x0 + visibleSize.width / 2 + x/2, y0 - (h / 2 + 1)*j), 1.0f, Color4F::BLACK);	
	}
	layer->addChild(draw, 3);

	//ピース生産
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			piece[i][j] = Sprite::create("river.png", Rect(w*i, h*j, w, h));
			piece[i][j]->setScale(0.5f);
			piece[i][j]->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			piece[i][j]->setPosition(Vec2(x0 + (w/2 + 1)*i, y0 - (h/2 + 1)*j));
			layer->addChild(piece[i][j], 2, j * x + i + 1);
			if (i == x - 1 && j == y - 1) {	//空白ピース
				piece[i][j]->setOpacity(0.0f);
				piece[i][j]->setZOrder(1);
			}

			//タッチイベント
			listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = CC_CALLBACK_2(TreeHouse::touchPiece, this);
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, piece[i][j]);
		}
	}

	//シャッフル
	int x1, y1, x2, y2;
	Vec2 p;
	for (int i = 0; i < 100; i++) {
		//x1 = random(0, x - 1); x2 = random(0, x - 1);
		//y1 = random(0, y - 1); y2 = random(0, y - 1);
		x1 = piece[x - 1][y - 1]->getPositionX(); y1 = piece[x - 1][y - 1]->getPositionY();
		switch (random(0,3))	//スペースを動かす方向を決める
		{
		case 0:	//→
			x2 = x1 + (w / 2 + 1);
			y2 = y1;
			break;
		case 1:	//←
			x2 = x1 - (w / 2 + 1);
			y2 = y1;
			break;
		case 2:	//↑
			x2 = x1;
			y2 = y1 + (h / 2 + 1);
			break;
		case 3:	//↓
			x2 = x1;
			y2 = y1 - (h / 2 + 1);
			break;
		default:
			break;
		}
		//移動方向にあるピースを検索
		int i2, j2;
		bool loop = true;
		for (j2 = 0; j2 < y && loop; j2++) {
			for ( i2 = 0; i2 < x && loop; i2++) {
				if (piece[i2][j2]->getPosition() == Vec2(x2, y2)) {
					//入れ替え
					piece[i2][j2]->setPosition(Vec2(x1, y1));
					piece[x - 1][y - 1]->setPosition(Vec2(x2, y2));
					loop = false;
				}
			}	
		}

		//p = piece[x1][y1]->getPosition();
		//piece[x1][y1]->setPosition(piece[x2][y2]->getPosition());
		//piece[x2][y2]->setPosition(p);
	}


	//戻るボタン
	auto back = Label::create("戻る", "fonts/APJapanesefontT.ttf", 40);
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(Vec2(origin.x, origin.y));
	back->setTextColor(Color4B::WHITE);
	back->enableOutline(Color4B::BLACK, 2);
	layer->addChild(back, 3, "back");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			getChildByName("puzzle")->runAction(Sequence::create(FadeOut::create(0.3f),RemoveSelf::create(),NULL));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, back);

	return layer;
}

bool TreeHouse::touchPiece(Touch *touch, Event *event) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	const int x = PIECE_X, y = PIECE_Y;
	const int w = visibleSize.width / x, h = visibleSize.height / y;
	const int x0 = origin.x + visibleSize.width / 2 - visibleSize.width / 4, y0 = origin.y + visibleSize.height / 2 + visibleSize.height / 4;

	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	if (targetBox.containsPoint(touchPoint))
	{
		//移動
		auto layer = getChildByName("puzzle");
		auto space = layer->getChildByTag(x * y);
		auto spaceP = space->getPosition();
		auto me = target->getPosition();
		if ((spaceP.x == me.x + (w / 2 + 1) && spaceP.y == me.y )||	//→
			(spaceP.x == me.x - (w / 2 + 1) && spaceP.y == me.y) ||	//←
			(spaceP.y == me.y + (h / 2 + 1) && spaceP.x == me.x) ||	//↑
			(spaceP.y == me.y - (h / 2 + 1) && spaceP.x == me.x)) {	//↓
			target->runAction(MoveTo::create(0.1f, spaceP));
			space->runAction(MoveTo::create(0.1f, me));
		}

		//判定	
		bool complete = true;
		for (int j = 0; j < y && complete; j++) {
			for (int i = 0; i < x && complete; i++) {
				if (layer->getChildByTag(j * x + i + 1)->getPosition() != Vec2(x0 + (w / 2 + 1)*i, y0 - (h / 2 + 1)*j))
				{
					if (layer->getChildByTag(j * x + i + 1)->getPosition() == me) { 
						if (spaceP == Vec2(x0 + (w / 2 + 1)*i, y0 - (h / 2 + 1)*j)) break;
					}
					else if (layer->getChildByTag(j * x + i + 1)->getPosition() == spaceP) {
						if (me == Vec2(x0 + (w / 2 + 1)*i, y0 - (h / 2 + 1)*j)) break;
					}
					complete = false;
				}
			}
		}
		if (complete) {
			((ObjectN*)this->getChildByName("_puzzle"))->setState(1);
			getChildByName("puzzle")->runAction(Sequence::create(DelayTime::create(1.0f), FadeOut::create(0.3f), RemoveSelf::create(), NULL));
		}
		return true;
	}
	return false;
}

void TreeHouse::changedField() {

}
