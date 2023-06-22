#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Student : public Person {
private:
  vector<float> marks;

public:
  Student(string name, string surname, int age, int id);
  ~Student(void);

  vector<float> getMarks();
  void setMarks(vector<float> newMarks);

  int getNumMarks();

  float getAverage();

  string marksToString();

  void printData();
};

#endif // STUDENT_H
