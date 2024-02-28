#pragma once
#include "Adoption_list_File.h"
#include <fstream>
//#include <windows.h>

class Adoption_list_HTML : public Adoption_List_File
{
public:
	Adoption_list_HTML(const string& filePath) : Adoption_List_File(filePath) {};
	~Adoption_list_HTML() {};

	void write_to_file() override;
	void display_adoption_list() override;
};
