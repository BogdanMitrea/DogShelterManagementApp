#include "Tests.h"

TestAdd::TestAdd()
{
}

void TestAdd::add_ValidID(string id, string breed, string name, string age, string photograph)
{
	Adoption_List_File* file_list = nullptr;
	file_list = new Adoption_list_CSV("Adoption_List.csv");
	FakeRepository fakerepository(file_list);
	Service service(fakerepository);
	fakerepository.set_bool_value(false);
	try
	{
		service.add_dog_service(id,breed,name, age,photograph);
		assert(true);
	}
	catch (RepositoryException& repostiory_exception)
	{
		assert(false);
	}
}

void TestAdd::add_ExistentID_ThrowException(string id, string breed, string name, string age, string photograph)
{
	Adoption_List_File* file_list = nullptr;
	file_list = new Adoption_list_CSV("Adoption_List.csv");
	FakeRepository fakerepository(file_list);
	Service service(fakerepository);
	fakerepository.set_bool_value(true);
	try
	{
		service.add_dog_service(id, breed, name, age, photograph);
		assert(false);
	}
	catch (RepositoryException& repository_exception)
	{
		assert(true);
	}
}
