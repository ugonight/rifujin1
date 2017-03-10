#include "../System/control.h"

#include "fieldDef.h"

void Control::initField() {
	mFieldList["forest1"] = Field1::create();
	mFieldList["campus"] = Field2::create();
	mFieldList["forest2"] = Forest2::create();
	mFieldList["forest3"] = Forest3::create();
	mFieldList["cave"] = Cave::create();
	mFieldList["cave_in"] = CaveIn::create();
	mFieldList["cave_end"] = CaveEnd::create();
	mFieldList["cliff"] = Cliff::create();
	mFieldList["treehouse"] = TreeHouse::create();
	mFieldList["river"] = River::create();

	mFieldList["AboutItem"] = AboutItem::create();

	for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
		it->second->retain();
	}

}