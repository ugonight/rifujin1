#pragma once

#include "field.h"

class Field1 : public Field { 
public:
	virtual bool init(); 
	virtual void chengedField();
	CREATE_FUNC(Field1);
};

class Field2 : public Field {
public:
	virtual bool init();
	CREATE_FUNC(Field2);
};