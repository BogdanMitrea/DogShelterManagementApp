#include "Adoption_list.h"

Adoption_List::Adoption_List()
{
}

void Adoption_List::add_adoption(const Dogs& dog)
{
	this->adoptions.push_back(dog);
}

int Adoption_List::get_size()
{
	return this->adoptions.size();
}

vector<Dogs> Adoption_List::get_list()
{
	return this->adoptions;
}
