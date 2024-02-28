#pragma once
#include "Repository.h"
#include "Service.h"
#include <string>

using namespace std;

class Service {
private:
	Repository repo;
public:
	Service(const Repository& repository) : repo{ repository }
	{ 
		this->repo = repository;
		this->repo.load_from_file("Dogs_List.txt");
		//this->generate_random_entries();
	};
	Service();
	void add_dog_service(string id, string breed, string name, string age, string photograph);
	int get_size_service() const;
	Dogs get_dog__position_serivce(int position);
	void remove_dog_service(string id);
	void generate_random_entries();
	vector<Dogs> get_all_dogs_service();
	void update_dog_service(string id, string breed, string name, string age, string photograph);

	bool add_dog_user_list(const Dogs& dog);
	vector<Dogs> get_all_dogs_user();
	vector<Dogs> filter_breed_and_age(string breed, int age);

	void save_to_file(string filename);
	void load_from_file(string filename);

	void save_adoption_list();
	void display_adoption_list() const;
};
