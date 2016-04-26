#pragma once

#include "cocos2d.h"

class Field;

class Control : public cocos2d::Scene {
private:
	std::map<std::string, Field*> mFieldList;
	
	void initField();

public:

	void setCursor(int num);
	void changeField(std::string field);
	void showMsg(std::string msg);
	
	void pauseField();
	void resumeField();

	bool getExistObject(std::string field, std::string obj);

	virtual bool init();
	virtual void update(float delta);



	static Control* me;

	CREATE_FUNC(Control);
};
