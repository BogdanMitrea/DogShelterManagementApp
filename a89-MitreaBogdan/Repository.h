#pragma once
#include <vector>
#include "Dog_Domain.h"
#include "DogValidator.h"
#include "Adoption_list_File.h"
#include "Adoption_List_CSV.h"
#include "Adoption_List_HTML.h"
#include <iostream>
#include <fstream>


class RepositoryException : exception
{
private:
	string message;
public:
	RepositoryException(const string& message)
	{
		this->message = message;
	}
	virtual const char* what()
	{
		return message.c_str();
	}
	string get_message()
	{
		return this->message;
	}
};


class Repository
{
private:
	vector<Dogs> dogs_list;
protected:
	Adoption_List_File* users_list;
public:
	Repository(Adoption_List_File* adoption_list);
	Repository();

	//functions for administrator
	virtual void add_dog_repo(Dogs new_dog);
	int get_size() const;
	Dogs get_dog_from_position(int position);
	void remove_dog(int position);
	vector<Dogs> get_all_dogs_repo();
	void update_dog(int position, Dogs new_dog);

	//functions for user
	void add_dog_user_list(const Dogs& dog);
	vector<Dogs> get_all_dogs_user();

	//functions working with different files
	void save_to_file(const string filename);
	void load_from_file(const string filename);

	void save_adoption_list();
	void display_adoption_list() const;
};