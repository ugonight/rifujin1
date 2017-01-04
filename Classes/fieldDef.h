#pragma once

#include "field.h"

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 
//メンバを追加できるように}は定義しない

CREATE_FIELD(Field1)};
CREATE_FIELD(Field2)};

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