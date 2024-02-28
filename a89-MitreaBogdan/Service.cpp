#include "Service.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

bool isNumber(const string& string_to_check)
{
	if (string_to_check.size()==0)
		return false;
	for (char const& character : string_to_check) {
		if (isdigit(character) == 0)
			return false;
	}
	return true;
}

Service::Service()
{
	/*Adoption_List_File* file_list = nullptr;
	file_list = new Adoption_list_CSV("Adoption_List.csv");
	Repository repo(file_list);
	this->repo = repo;*/
}

void Service::add_dog_service(string id, string breed, string name, string age, string photograph)
{
	Dogs new_dog;
	int int_age, int_id;
	if (isNumber(age))
		int_age = stoi(age);
	else
		throw invalid_argument("Age must be an integer larger than 0\n");
	if (isNumber(id))
		int_id = stoi(id);
	else
		throw invalid_argument("ID must be an integer\n");

	new_dog.Initialize_Dog(breed, name, int_age, photograph, int_id);
	vector<Dogs> dogs_list = this->repo.get_all_dogs_repo();
	const int new_dog_id = new_dog.Get_id();

	auto found_iterator = find_if(dogs_list.begin(), dogs_list.end(), [new_dog_id](Dogs i) {return (i.Get_id() == new_dog_id); });

	if (found_iterator != dogs_list.end())// A dog with the same ID was found
	{
		throw RepositoryException("A dog with the same id already exists");
	}
	this->repo.add_dog_repo(new_dog);
}

void Service::generate_random_entries()
{
	Dogs newdog;
	newdog.Initialize_Dog("Poodle", "Lucy", 3, "https://puppyintraining.com/wp-content/uploads/How-Big-Do-Toy-Poodles-Get.jpg", 1);
	this->repo.add_dog_repo(newdog);
	newdog.Initialize_Dog("Golden-Retriever", "Goldie", 5, "https://images.dog.ceo/breeds/retriever-golden/nina.jpg", 2);
	this->repo.add_dog_repo(newdog);

	newdog.Initialize_Dog("Boxer", "Danny", 1, "https://images.dog.ceo/breeds/boxer/n02108089_1859.jpg", 3);
	this->repo.add_dog_repo(newdog);
	newdog.Initialize_Dog("Setter", "Bailey", 10, "https://images.dog.ceo/breeds/setter-english/n02100735_7575.jpg", 4);
	this->repo.add_dog_repo(newdog);

	newdog.Initialize_Dog("Greyhound", "Smoky", 7, "https://images.dog.ceo/breeds/greyhound-italian/n02091032_551.jpg", 5);
	this->repo.add_dog_repo(newdog);
	newdog.Initialize_Dog("Briard", "Fluffy", 2, "https://images.dog.ceo/breeds/briard/n02105251_6300.jpg", 6);
	this->repo.add_dog_repo(newdog);

	newdog.Initialize_Dog("Springer", "Sophie", 3, "https://images.dog.ceo/breeds/springer-english/n02102040_2481.jpg", 7);
	this->repo.add_dog_repo(newdog);
	newdog.Initialize_Dog("Bichon-Frise", "Bella", 8, "https://images.dog.ceo/breeds/frise-bichon/stevebaxter_bichon_frise.jpg", 8);
	this->repo.add_dog_repo(newdog);

	newdog.Initialize_Dog("Malinois", "Rocky", 1, "https://images.dog.ceo/breeds/malinois/n02105162_9934.jpg", 9);
	this->repo.add_dog_repo(newdog);
	newdog.Initialize_Dog("Saint-Bernard", "George", 9, "https://images.dog.ceo/breeds/stbernard/n02109525_14297.jpg", 10);
	this->repo.add_dog_repo(newdog);
}

int Service::get_size_service() const
{
	return this->repo.get_size();
}

Dogs Service::get_dog__position_serivce(int position)
{
	return this->repo.get_dog_from_position(position);
}

void Service::remove_dog_service(string id)
{
	int int_id;
	if (isNumber(id))
		int_id = stoi(id);
	else
		throw invalid_argument("ID must be an integer\n");
	vector<Dogs> dogs_list = this->repo.get_all_dogs_repo();
	auto found_iterator = find_if(dogs_list.begin(), dogs_list.end(), [int_id](Dogs i) {return (i.Get_id() == int_id); });

	if (found_iterator == dogs_list.end()) // The dog with the specified id is not in the list
	{
		throw RepositoryException("The dog with the specified ID could not be found");
	}
	this->repo.remove_dog(found_iterator - dogs_list.begin());
}

vector<Dogs> Service::get_all_dogs_service()
{
	return this->repo.get_all_dogs_repo();
}

void Service::update_dog_service(string id, string breed, string name, string age, string photograph)
{
	Dogs new_dog;
	int int_age, int_id;
	if (isNumber(age))
		int_age = stoi(age);
	else
		throw invalid_argument("Age must be an integer larger than 0\n");
	if (isNumber(id))
		int_id = stoi(id);
	else
		throw invalid_argument("ID must be an integer\n");
	new_dog.Initialize_Dog(breed, name, int_age, photograph, int_id);

	vector<Dogs> dogs_list = this->repo.get_all_dogs_repo();
	auto found_iterator = find_if(dogs_list.begin(), dogs_list.end(), [int_id](Dogs i) {return (i.Get_id() == int_id); });

	if (found_iterator == dogs_list.end()) // The dog with the specified id is not in the list
	{
		throw RepositoryException("The dog with the specified ID could not be found");
	}
	this->repo.update_dog(found_iterator - dogs_list.begin(), new_dog);
}

bool Service::add_dog_user_list(const Dogs& dog)
{
	vector<Dogs> dogs_list = this->repo.get_all_dogs_user();
	Dogs new_dog = dog;
	const int new_dog_id = new_dog.Get_id();

	auto found_iterator = find_if(dogs_list.begin(), dogs_list.end(), [new_dog_id](Dogs i) {return (i.Get_id() == new_dog_id); });

	if (found_iterator != dogs_list.end())
	{
		return false; // A dog with the same ID was found
	}

	this->repo.add_dog_user_list(dog);
	return true;
}

vector <Dogs> Service::get_all_dogs_user()
{
	return this->repo.get_all_dogs_user();
}

vector<Dogs> Service::filter_breed_and_age(string breed, int age)
{
	vector<Dogs> list_copy = this->repo.get_all_dogs_repo();
	vector<Dogs> filtered_list(list_copy.size());
	auto filter_iterator = copy_if(list_copy.begin(), list_copy.end(), filtered_list.begin(), [breed, age](Dogs dog) {return (dog.Get_Breed() == breed && dog.Get_Age() < age); });
	filtered_list.resize(distance(filtered_list.begin(), filter_iterator));
	return filtered_list;
}

void Service::save_to_file(string filename)
{
	this->repo.save_to_file(filename);
}

void Service::load_from_file(string filename)
{
	this->repo.load_from_file(filename);
}

void Service::save_adoption_list()
{
	this->repo.save_adoption_list();
}

void Service::display_adoption_list() const
{
	this->repo.display_adoption_list();
}
