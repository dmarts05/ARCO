#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "student.h"
#include <iostream>
#include <vector>

using namespace std;

class Teacher : public Person {
private:
  vector<Student> students;

public:
  Teacher(string name, string surname, int age, int id);
  ~Teacher(void);

  void addStudent(string name, string surname, int age, int id);

  vector<Student> getStudents();

  void setStudentMark(int id, float mark);
  void setStudentMark(int id, float mark1, float mark2);
  void setStudentMark(int id, float mark1, float mark2, float mark3);

  float getAverage();

  int getBestStudentId();

  void printStudentData(int id);

  void printBestStudentData();

  void printData();
};

#endif // TEACHER_H
