#pragma once
#include "cocos2d.h"

class Novel : public cocos2d::Layer {

private:
	enum ImagePos {
		IMG_NONE,
		IMG_BG,
		IMG_CENTER,
		IMG_LEFT,
		IMG_RIGHT
	};

	typedef struct Task {
		int num;
		ImagePos imgPos;
		std::string imgName;
	} Task;

	typedef struct CTask {
		int num;
		cocos2d::Color3B color;
	} CTask;

	typedef struct FTask {
		int num;
		cocos2d::CallFunc* func;
	} FTask;

	int mNovelNum, mNovelSetNum, mCount, mCharNum;
	int mTouchTime; bool mHideMsg;
	bool mEndFlag;
	bool mLogOnly;
	std::vector<std::string> mSentense;
	std::vector<Task> mTask;
	std::vector<CTask> mColorTask;
	std::vector<FTask> mFuncTask;
	//cocos2d::Label mLabel[];
	cocos2d::ValueVector mLog;
	int mLogScrollX, mLogScrollY;

	void func();
	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	//バックログ
	bool logEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void end();
	bool endCheck();
	void setDelayAnime();

	//画像更新
	void updateImg();
	//色更新
	void updateColor();
	//イベント実行
	void updateFunc();

public:
	virtual ~Novel();

	virtual bool init();
	virtual void update(float delta);

	
	//終了フラグ
	bool getEndFlag();

	//文追加
	void addSentence(std::string s);
	//背景設定
	void setBg(std::string s);
	//キャラクター・センター
	void setCharaC(std::string s);
	//キャラクター・レフト
	void setCharaL(std::string s);
	//キャラクター・ライト
	void setCharaR(std::string s);

	//タスクの終わり
	void setEndTask();

	//文字色変更
	void setFontColor(cocos2d::Color3B c);

	//イベントタスク追加
	void addEvent(cocos2d::CallFunc* func);

	//ログだけ表示するモード
	void setLogOnly();

	CREATE_FUNC(Novel);
};