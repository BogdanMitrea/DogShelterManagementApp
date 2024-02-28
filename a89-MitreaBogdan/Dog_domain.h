#pragma once
#include <string>
#include <sstream>

using namespace std;

class Dogs
{
private:
	string breed;
	string name;
	int age;
	string photograph;
	int id;
public:
	Dogs();
	~Dogs();
	Dogs(const Dogs& dog);

	void Initialize_Dog(string breed, string name, int age, string photograph, int id);

	string Get_Name();

	string Get_Breed();

	int Get_Age();

	int Get_id();

	string Get_Photograph();

	string toString();

	friend ostream& operator<<(ostream& dogs_output_stream, const Dogs& dog);

	friend istream& operator>>(istream& dogs_input_stream, Dogs& dog);
};