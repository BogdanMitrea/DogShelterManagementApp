#include "Dog_Domain.h"
#include <cstring>
#include <iostream>


using namespace std;

Dogs::Dogs()
{
	this->breed = "";
	this->name = "";
	this->age = 0;
	this->photograph = "";
	this->id = 0;
}

Dogs::~Dogs()
{

}

Dogs::Dogs(const Dogs& dog)
{
	this->breed = dog.breed;
	this->name = dog.name;
	this->age = dog.age;
	this->photograph = dog.photograph;
	this->id = dog.id;
}

void Dogs::Initialize_Dog(string breed, string name, int age, string photograph, int id)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
	this->id = id;
}

string Dogs::Get_Name()
{
	return this->name;
}

string Dogs::Get_Breed()
{
	return this->breed;
}

int Dogs::Get_Age()
{
	return this->age;
}

string Dogs::Get_Photograph()
{
	return this->photograph;
}

int Dogs::Get_id()
{
	return this->id;
}

string Dogs::toString()
{
	std::stringstream print_dog;
	print_dog << "Dog: " << this->name << ", ID: " << this->id << ", Breed: " << this->breed << ",  Aged: " << this->age << ",  Photo: " << this->photograph << "\n\n";

	return print_dog.str();
}

ostream& operator<<(ostream& dogs_output_stream, const Dogs& dog)
{
	dogs_output_stream << dog.id << "," << dog.name << "," << dog.breed << "," << dog.age << "," << dog.photograph << "\n";
	return dogs_output_stream;
}

istream& operator>>(istream& dogs_input_stream, Dogs& dog)
{
	string id, name, breed, age, photograph;
	if (getline(dogs_input_stream, id, ',') && getline(dogs_input_stream, name, ',') && getline(dogs_input_stream, breed, ',') && getline(dogs_input_stream, age, ',') && getline(dogs_input_stream, photograph))
	{
		dog.Initialize_Dog(breed, name, stoi(age), photograph, stoi(id));
	}
	return dogs_input_stream;
}