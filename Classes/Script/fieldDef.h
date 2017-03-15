#pragma once

#include "../System/field.h"

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 
//ÉÅÉìÉoÇí«â¡Ç≈Ç´ÇÈÇÊÇ§Ç…}ÇÕíËã`ÇµÇ»Ç¢

CREATE_FIELD(Field1)};
CREATE_FIELD(Field2)};
CREATE_FIELD(Forest2)};
CREATE_FIELD(Forest3)};
CREATE_FIELD(Cave)};
CREATE_FIELD(CaveIn) private: int mCount; };
CREATE_FIELD(CaveEnd)};
CREATE_FIELD(Cliff)};
CREATE_FIELD(Passward)};
CREATE_FIELD(TreeHouse) private: cocos2d::Layer* puzzle(); bool touchPiece(cocos2d::Touch *touch, cocos2d::Event *event); };
CREATE_FIELD(River)};
CREATE_FIELD(WaterFalls) private: void switchStone(int *switchList); void judge(); };
CREATE_FIELD(Paddy)};
CREATE_FIELD(Garden)};
CREATE_FIELD(DeadForest)};
CREATE_FIELD(Ruins)};
CREATE_FIELD(Living)};
CREATE_FIELD(Room) private: void turnPage(); };
CREATE_FIELD(Passward2)};

CREATE_FIELD(AboutItem)
	void setAboutItem(std::string itemName);
};

//class Field1 : public Field { 
//public:
//	virtual void initField(); 
//	virtual void chengedField();
//	CREATE_FUNC(Field1);
//};
//
//class Field2 : public Field {
//public:
//	virtual void initField();
//	CREATE_FUNC(Field2);
//};