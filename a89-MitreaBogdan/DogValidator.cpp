#include "DogValidator.h"
#include <regex>

bool isLink(std::string str) {
    std::regex link_pattern("\\s*(http|https)://[a-zA-Z0-9\\./_-]+");

    return std::regex_match(str, link_pattern);
}

DogValidator::DogValidator()
{
}

DogValidator::~DogValidator()
{
}

void DogValidator::validate_dog(Dogs& dog)
{
    if (dog.Get_Breed().empty())
    {
        throw ValidationError("Breed cannot be empty\n");
    }
    if (dog.Get_Name().empty()) {
        throw ValidationError("Name cannot be empty\n");
    }
    if (dog.Get_Photograph().empty()) {
        throw ValidationError("Photograph cannot be empty\n");
    }

    //if (isLink(dog.Get_Photograph()) == false)
        //throw ValidationError("Invalid link for the photograph\n");

    if (dog.Get_Age() < 0) {
        throw ValidationError("Age must be an integer larger than 0\n");
    }

}
