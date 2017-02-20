#include "../System/control.h"

#include "fieldDef.h"

void Control::initField() {
	mFieldList["forest1"] = Field1::create();
	mFieldList["campus"] = Field2::create();
	mFieldList["forest2"] = Forest2::create();
	mFieldList["forest3"] = Forest3::create();

	mFieldList["AboutItem"] = AboutItem::create();

	for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
		it->second->retain();
	}

}