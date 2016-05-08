#pragma once

#include "field.h"

class Field1 : public Field { 
public:
	virtual void initField(); 
	virtual void chengedField();
	CREATE_FUNC(Field1);
};

class Field2 : public Field {
public:
	virtual void initField();
	CREATE_FUNC(Field2);
};