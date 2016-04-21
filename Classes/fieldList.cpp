#include "control.h"

#include "fieldDef.h"

void Control::initField() {
	mFieldList["forest1"] = Field1::create();
	mFieldList["campus"] = Field2::create();


	for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
		it->second->retain();
	}
}