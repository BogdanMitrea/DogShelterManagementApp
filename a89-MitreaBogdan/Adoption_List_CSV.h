#pragma once
#include "Adoption_list_File.h"
#include <fstream>
#include <iostream>
//#include <Windows.h>

class Adoption_list_CSV : public Adoption_List_File
{
public:
	Adoption_list_CSV(const string& filePath) : Adoption_List_File(filePath) {};
	~Adoption_list_CSV() {};

	void write_to_file() override;
	void display_adoption_list() override;
};
