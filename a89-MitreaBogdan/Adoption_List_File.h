#pragma once
#include "Adoption_list.h"


class Adoption_List_File : public Adoption_List
{
protected:
	std::string filePath;
public:
	Adoption_List_File(const std::string& filePath)
	{
		this->filePath = filePath;
	}
	virtual ~Adoption_List_File() {}

	virtual void write_to_file() = 0;
	virtual void display_adoption_list() = 0;
};