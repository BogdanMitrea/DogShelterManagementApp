#pragma once
#include "Dog_Domain.h"
class ValidationError : exception
{
private:
    string message;
public:
    ValidationError(const string& message)
    {
        this->message = message;
    }
    virtual const char* what()
    {
        return message.c_str();
    }
};

class DogValidator
{
public:
    DogValidator();
    ~DogValidator();
    void validate_dog(Dogs& dog);
};