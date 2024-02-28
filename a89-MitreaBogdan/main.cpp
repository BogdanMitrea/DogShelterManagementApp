#include "a89MitreaBogdan.h"
#include <QtWidgets/QApplication>
//#include "GUI.h"
#include "Tests.h"
#include "a89MitreaBogdan.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
	string save_mode;
	Adoption_List_File* file_list = nullptr;
	/*while (save_mode != "CSV" && save_mode != "HTML")
	{
		QDialog ()
		if (save_mode == "CSV")
			file_list = new Adoption_list_CSV("Adoption_List.csv");
		if (save_mode == "HTML")
			file_list = new Adoption_list_HTML("Adoption_List.html");
	}*/
	TestAdd testadd;

	testadd.add_ValidID("100","breed1","name1","1","photo1");
	testadd.add_ExistentID_ThrowException("1","breed1","name1","1","photo1");
	
	file_list = new Adoption_list_CSV("Adoption_List.csv");
	Repository repo(file_list);
	Service service(repo);
	//GUI gui(service);
	//gui.show();
	a89MitreaBogdan gui{ service };
	gui.show();
    return application.exec();
}
