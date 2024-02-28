#pragma once
#include <vector>
#include "Dog_Domain.h"
using namespace std;

class Adoption_List
{
public:
	vector<Dogs> adoptions;
	Adoption_List();
	void add_adoption(const Dogs& dog);
	int get_size();
	vector<Dogs> get_list();
};