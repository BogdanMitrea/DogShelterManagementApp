
#include "Adoption_list_HTML.h"

void Adoption_list_HTML::write_to_file()
{
	ofstream open_file(this->filePath);
	open_file << "<!DOCTYPE html>" << endl;
	open_file << "<html>" << endl;
	open_file << "<head>" << endl;
	open_file << "<title>My Dogs</title>" << endl;
	open_file << "</head>" << endl;
	open_file << "<body>" << endl;
	open_file << "<table border=\"1\">" << endl;
	open_file << "<tr>" << endl;
	open_file << "<td>ID</td>" << endl;
	open_file << "<td>Name</td>" << endl;
	open_file << "<td>Breed</td>" << endl;
	open_file << "<td>Age</td>" << endl;
	open_file << "<td>Photograph</td>" << endl;
	open_file << "</tr>" << endl;
	for (auto dog : this->adoptions)
	{
		open_file << "<tr>" << endl;
		open_file << "<td>" << dog.Get_id() << "</td>" << endl;
		open_file << "<td>" << dog.Get_Name() << "</td>" << endl;
		open_file << "<td>" << dog.Get_Breed() << "</td>" << endl;
		open_file << "<td>" << dog.Get_Age() << "</td>" << endl;
		open_file << "<td><img src=\"" << dog.Get_Photograph() << "\"></td>" << endl;
		open_file << "</tr>" << endl;
	}
	open_file << "</table>" << endl;
	open_file << "</body>" << endl;
	open_file << "</html>" << endl;
	open_file.close();
}

void Adoption_list_HTML::display_adoption_list()
{
	//ShellExecuteA(NULL, "open", this->filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
