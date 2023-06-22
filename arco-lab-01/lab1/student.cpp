#include "student.h"

Student::Student(string name, string surname, int age, int id)
    : Person(name, surname, age, id) {}

Student::~Student() {}

vector<float> Student::getMarks() { return this->marks; }

void Student::setMarks(vector<float> newMarks) {
  this->marks.clear();
  for (auto newMark : newMarks) {
    this->marks.push_back(newMark);
  }
}

int Student::getNumMarks() { return this->marks.size(); }

float Student::getAverage() {
  float sum = 0;
  int numMarks = this->getNumMarks();

  for (auto mark : this->marks) {
    sum += mark;
  }

  return numMarks == 0 ? -1 : sum / numMarks;
}

string Student::marksToString() {
  stringstream marksStream;
  marksStream << fixed << setprecision(2);

  for (auto mark : this->marks) {
    marksStream << mark << " ";
  }

  return marksStream.str();
}

void Student::printData() {
  cout << "Estudiante: " << this->getName() << " " << this->getSurname()
       << endl;
  cout << "Edad: " << this->getAge() << endl;
  cout << "DNI: " << this->getId() << endl;
  cout << "Notas: " << this->marksToString() << endl;

  float average = this->getAverage();
  if (average == -1) {
    cout << "Nota media: " << endl;
  } else {
    cout << fixed << setprecision(2) << "Nota media: " << average << endl;
  }

  cout << "----------------------------------" << endl;
}
