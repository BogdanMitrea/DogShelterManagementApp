#pragma once
#include <vector>
#include "Dog_Domain.h"
#include "DogValidator.h"
#include "Adoption_list_File.h"
#include "Adoption_List_CSV.h"
#include <iostream>
#include <fstream>
#include "Repository.h"

class FakeRepository: public Repository
{
public:
	bool DogIsInRepository;
	void set_bool_value(bool new_bool) {
		this->DogIsInRepository = new_bool;
	}
	FakeRepository(Adoption_List_File* adoption_list);
	void add_dog_repo(Dogs new_dog) override {
			if (DogIsInRepository == true)
				throw RepositoryException("Error\n");
	}
};