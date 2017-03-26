#pragma once

#include "cocos2d.h"

class Field;

class Control : public cocos2d::Scene {
private:
	std::map<std::string, Field*> mFieldList;
	
	void initField();
	void save(cocos2d::Ref* pSender);

public:
	virtual ~Control();

	void setCursor(int num);
	void changeField(std::string field);
	void showMsg(std::string msg);
	void showAI(std::string itemName);
	void deleteAI();
	
	void pauseField();
	void resumeField();

	bool getExistObject(std::string field, std::string obj);
	Field* getField(std::string field);

	virtual bool init();
	virtual void update(float delta);

	void load();

	static Control* me;

	CREATE_FUNC(Control);
};
