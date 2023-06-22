#include "person.h"

Person::Person(string name, string surname, int age, int id) {
  this->setName(name);
  this->setSurname(surname);
  this->setId(id);
  this->setAge(age);
}

Person::~Person() {}

int Person::getAge() { return this->age; }

void Person::setAge(int newAge) {
  if (newAge > 0) {
    this->age = newAge;
  } else {
    throw invalid_argument("Age must be greater than 0!");
  }
}

string Person::getName() { return this->name; }

void Person::setName(string newName) {
  if (newName.length() > 0) {
    this->name = newName;
  } else {
    throw invalid_argument("Name must at least have one character!");
  }
}

string Person::getSurname() { return this->surname; }

void Person::setSurname(string newSurname) {
  if (newSurname.length() > 0) {
    this->surname = newSurname;
  } else {
    throw invalid_argument("Surname must at least have one character!");
  }
}

int Person::getId() { return this->id; }

void Person::setId(int newId) {
  int digits = 1;
  int aux = newId;
  while (aux /= 10) {
    digits++;
  }

  if (digits == 7) {
    this->id = newId;
  } else {
    throw invalid_argument("ID must contain 7 digits in total!");
  }
}
