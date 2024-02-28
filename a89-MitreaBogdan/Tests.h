#pragma once
#include "FakeRepository.h"
#include "Service.h"
#include <cassert>

class TestAdd
{
public:
	TestAdd();
	void add_ValidID(string id, string breed, string name, string age, string photograph);
	void add_ExistentID_ThrowException(string id, string breed, string name, string age, string photograph);
};