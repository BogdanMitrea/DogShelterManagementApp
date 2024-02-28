#include "Repository.h"



Repository::Repository(Adoption_List_File* adoption_list)
{
	this->users_list = adoption_list;
}

Repository::Repository()
{
	/*Adoption_List_File* file_list = nullptr;
	file_list = new Adoption_list_CSV("Adoption_List.csv");
	this->users_list = file_list;*/
}

void Repository::add_dog_repo(Dogs new_dog)
{
	DogValidator validator;
	validator.validate_dog(new_dog);
	this->dogs_list.push_back(new_dog);
}

int Repository::get_size() const
{
	return this->dogs_list.size();
}

Dogs Repository::get_dog_from_position(int position)
{
	return this->dogs_list.at(position);
}

void Repository::remove_dog(int position)
{
	if (position == this->dogs_list.size() - 1)
		this->dogs_list.pop_back();
	else
		this->dogs_list.erase(this->dogs_list.begin() + position);
}


vector<Dogs> Repository::get_all_dogs_repo()
{
	return this->dogs_list;
}

void Repository::update_dog(int position, Dogs new_dog)
{
	DogValidator validator;
	validator.validate_dog(new_dog);
	this->dogs_list.erase(this->dogs_list.begin() + position);
	this->dogs_list.insert(this->dogs_list.begin() + position, new_dog);
}

void Repository::add_dog_user_list(const Dogs& dog)
{
	this->users_list->add_adoption(dog);
}

vector<Dogs> Repository::get_all_dogs_user()
{
	return this->users_list->get_list();
}

void Repository::save_to_file(const string filename)
{
	ofstream open_file(filename);
	for (auto dog : dogs_list)
	{
		open_file << dog;
	}
	open_file.close();
}

void Repository::load_from_file(const string filename)
{
	ifstream open_file(filename);
	Dogs dog;
	while (open_file >> dog)
		this->add_dog_repo(dog);
	open_file.close();
}

void Repository::save_adoption_list()
{
	this->users_list->write_to_file();
}

void Repository::display_adoption_list() const
{
	this->users_list->display_adoption_list();
}


