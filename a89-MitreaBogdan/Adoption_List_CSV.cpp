#include "Adoption_List_CSV.h"

void Adoption_list_CSV::write_to_file()
{
	ofstream open_file(this->filePath);

	if (!open_file.is_open())
		throw exception("The file couldn't be opened!");

	for (auto dog : this->adoptions)
	{
		open_file << dog;
	}
	open_file.close();
}

void Adoption_list_CSV::display_adoption_list()
{
	//ShellExecuteA(NULL, NULL, "c:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", this->filePath.c_str(), NULL, SW_SHOWMAXIMIZED);
}
