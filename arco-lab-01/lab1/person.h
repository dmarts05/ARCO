#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Person {
private:
  string name;
  string surname;
  int age;
  int id;

public:
  Person(string name, string surname, int age, int id);
  ~Person(void);

  int getAge();
  void setAge(int newAge);

  string getName();
  void setName(string newName);

  string getSurname();
  void setSurname(string newSurname);

  int getId();
  void setId(int newId);
};

#endif // PERSON_H
