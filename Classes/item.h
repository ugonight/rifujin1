#pragma once
#include "cocos2d.h"

#include "object.h"

class Item : public cocos2d::Layer {
public:
	virtual bool init();
	virtual void update(float delta);

	void getItem(std::string itemName,cocos2d::Point point);

	void deleteItem(std::string itemName);
	std::string getSelectedItem();

	static Item* sharedItem();



	CREATE_FUNC(Item);
private:
	class ItemObj{
		std::string imgName;
		bool getFlag = 0;
		cocos2d::Layer* aiLayer;	//AIで表示するオブジェクトを配置するレイヤー

	public:
		ItemObj(std::string imageName) {
			imgName = imageName;
		}

		std::string getImage() { return imgName; };
		void setGetFlag(bool i) { getFlag = i; };
		
		//aiLayerのinit()を定義する関数（？）を作る
		//わざわざアイテムごとにクラスを作るのがめんどうなので、簡単に定義できるようにしたい。

	};

	std::map<std::string, ItemObj*> mItemList;
	void initItem();

	bool mShowWindow;
	bool mShowAboutItem;
	int mWindowW;
	int mTouchTime;
	std::string mSelectedItem;

	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void moveEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void endEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void showAboutItem();
};
