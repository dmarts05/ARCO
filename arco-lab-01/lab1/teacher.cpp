#include "teacher.h"

Teacher::Teacher(string name, string surname, int age, int id)
    : Person(name, surname, age, id) {}

Teacher::~Teacher() {}

void Teacher::addStudent(string name, string surname, int age, int id) {
  Student *student = new Student(name, surname, age, id);
  this->students.push_back(*student);
}

vector<Student> Teacher::getStudents() { return this->students; }

void Teacher::setStudentMark(int id, float mark) {
  if (mark < 0.0 || mark > 10.0) {
    throw invalid_argument("Marks must have a value between 0.0 and 10.0!");
  }

  for (auto &student : this->students) {
    if (student.getId() == id) {
      vector<float> marks = {mark};
      student.setMarks(marks);
      break;
    }
  }
}

void Teacher::setStudentMark(int id, float mark1, float mark2) {
  if (mark1 < 0.0 || mark1 > 10.0 || mark2 < 0.0 || mark2 > 10.0) {
    throw invalid_argument("Marks must have a value between 0.0 and 10.0!");
  }

  for (auto &student : this->students) {
    if (student.getId() == id) {
      vector<float> marks = {mark1, mark2};
      student.setMarks(marks);
      break;
    }
  }
}

void Teacher::setStudentMark(int id, float mark1, float mark2, float mark3) {
  if (mark1 < 0.0 || mark1 > 10.0 || mark2 < 0.0 || mark2 > 10.0 ||
      mark3 < 0.0 || mark3 > 10.0) {
    throw invalid_argument("Marks must have a value between 0.0 and 10.0!");
  }

  for (auto &student : this->students) {
    if (student.getId() == id) {
      vector<float> marks = {mark1, mark2, mark3};
      student.setMarks(marks);
      break;
    }
  }
}

float Teacher::getAverage() {
  float sumMarks = 0.0;
  int numMarks = 0;

  for (auto student : this->students) {
    for (auto mark : student.getMarks()) {
      sumMarks += mark;
      numMarks++;
    }
  }

  return numMarks == 0 ? -1 : sumMarks / numMarks;
}

int Teacher::getBestStudentId() {
  int id = -1;
  float bestAverage = -1;

  for (auto student : this->students) {
    if (student.getNumMarks() == 3) {
      float average = student.getAverage();
      id = average > bestAverage ? student.getId() : id;
      bestAverage = average > bestAverage ? average : bestAverage;
    }
  }

  return id;
}

void Teacher::printStudentData(int id) {
  for (auto student : this->students) {
    if (student.getId() == id) {
      student.printData();
      break;
    }
  }
}

void Teacher::printBestStudentData() {
  int bestStudentId = getBestStudentId();
  if (bestStudentId != -1) {
    cout << "Mejor ";
    this->printStudentData(bestStudentId);
  }
}

void Teacher::printData() {
  cout << "PROFESOR: " << this->getName() << " " << this->getSurname() << endl;
  cout << "DNI: " << this->getId() << endl;
  cout << "Edad: " << this->getAge() << endl;

  float average = this->getAverage();
  if (average == -1) {
    cout << "Nota media de los alumnos: " << endl;
  } else {
    cout << fixed << setprecision(2) << "Nota media de los alumnos: " << average
         << endl;
    cout << "----------------------------------" << endl;
  }

  for (auto student : this->students) {
    printStudentData(student.getId());
  }
  cout << endl;
  this->printBestStudentData();
}
