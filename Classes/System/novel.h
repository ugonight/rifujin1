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

	//�o�b�N���O
	bool logEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void end();
	bool endCheck();
	void setDelayAnime();

	//�摜�X�V
	void updateImg();
	//�F�X�V
	void updateColor();
	//�C�x���g���s
	void updateFunc();

public:
	virtual ~Novel();

	virtual bool init();
	virtual void update(float delta);

	
	//�I���t���O
	bool getEndFlag();

	//���ǉ�
	void addSentence(std::string s);
	//�w�i�ݒ�
	void setBg(std::string s);
	//�L�����N�^�[�E�Z���^�[
	void setCharaC(std::string s);
	//�L�����N�^�[�E���t�g
	void setCharaL(std::string s);
	//�L�����N�^�[�E���C�g
	void setCharaR(std::string s);

	//�^�X�N�̏I���
	void setEndTask();

	//�����F�ύX
	void setFontColor(cocos2d::Color3B c);

	//�C�x���g�^�X�N�ǉ�
	void addEvent(cocos2d::CallFunc* func);

	//���O�����\�����郂�[�h
	void setLogOnly();

	CREATE_FUNC(Novel);
};