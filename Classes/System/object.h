#pragma once
#include "cocos2d.h"

	

class ObjectN : public cocos2d::Sprite {
	//bool mAreaFlag;	//�^�b�`�G���A�����݂��邩
	cocos2d::Rect mArea;
	int mCursorNum;
	int mState;	//��ԁE�t���O�I�Ȃ���

	std::string mGetItem;	//�^�b�`���ɓ��肷��A�C�e��
	std::string mField;		//�ړ���̃t�B�[���h
	std::string mMsg;		//�^�b�`���ɕ\�����郁�b�Z�[�W

	//�^�b�`���̃C�x���g
	//void(*mTouchEvent)();
	cocos2d::CallFunc *mTouchEvent;

	int mTouchTime;

	//�J�[�\���C�x���g
	void checkOn(cocos2d::Touch* touch, cocos2d::Event* event);
	bool touchOn(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchOff(cocos2d::Touch* touch, cocos2d::Event* event);

public:
	virtual ~ObjectN();

	virtual bool init();
	virtual void update(float delta);

	void setArea(cocos2d::Rect rect);	//(int x, int y, int w, int h)
	void setCursor(int cursorNum);
	void setState(int state);
	void setItemGetEvent(std::string itemName);
	void setFieldChangeEvent(std::string fieldName);
	void setMsg(std::string msg);

	//void setTouchEvent(void (*func)());
	void setTouchEvent(cocos2d::CallFunc *func);

	int getState();
	std::string getMsg();
	std::string getField();

	CREATE_FUNC(ObjectN);
};
