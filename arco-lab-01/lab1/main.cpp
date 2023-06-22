#include "teacher.h" //
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isStrNumeric(string str) {
  for (string::size_type i = 0; i < str.length(); i++) {
    if (isdigit(str[i]) == false) {
      return false;
    }
  }
  return true;
}

void Calificando() {
  vector<Teacher> teachers;

  // Teacher 1
  Teacher *teacher1 = new Teacher("Silvia", "Martínez", 36, 8763564);

  // Teacher 1 students
  teacher1->addStudent("Andrés", "García", 18, 8763566);
  teacher1->setStudentMark(8763566, 3.25, 4.75, 4.0);

  teacher1->addStudent("Darío", "Díaz", 21, 8763569);
  teacher1->setStudentMark(8763569, 7.25, 8.95);

  teacher1->addStudent("Alicia", "Campos", 20, 8763570);
  teacher1->setStudentMark(8763570, 10.0);

  teachers.push_back(*teacher1);

  // Teacher 2
  Teacher *teacher2 = new Teacher("María", "Fernández", 38, 8763565);

  // Teacher 2 students
  teacher2->addStudent("Raúl", "Entreríos", 34, 8763567);
  teacher2->setStudentMark(8763567, 5.5, 5.5, 5.0);

  teacher2->addStudent("Diego", "Lorenzana", 26, 8763568);
  teacher2->setStudentMark(8763568, 6.0, 5.0, 7.0);

  teacher2->addStudent("Roberto", "Fernández", 21, 8763571);
  teacher2->setStudentMark(8763571, 3.0, 6.0);

  teachers.push_back(*teacher2);

  for (auto teacher : teachers) {
    cout << endl << "**********************************" << endl << endl;
    teacher.printData();
  }

  // Start ID search loop
  while (true) {
    int id = -1;
    string idStr;
    cout << endl << "||||||||||||||||||||||||||||||||||" << endl << endl;
    cout << "Por favor, introduzca un DNI (7 dígitos) sin letra o 0 para salir "
            "del programa: ";
    cin >> idStr;
    cout << endl;

    // Check if user input is a number
    if (isStrNumeric(idStr)) {
      id = stoi(idStr);
    } else {
      cout << "El DNI no puede contenter letras, vuelva a intentarlo..."
           << endl;
      continue;
    }

    // Check if the user wants to exit the ID search loop
    if (id == 0) {
      cout << "Saliendo del programa..." << endl;
      break;
    }

    // Search ID and print person data if the ID exists
    bool found = false;
    for (auto teacher : teachers) {
      // Search teachers
      if (teacher.getId() == id) {
        teacher.printData();
        found = true;
        break;
      } else {
        // Search students of that teacher
        vector<Student> students = teacher.getStudents();
        for (auto student : students) {
          if (student.getId() == id) {
            student.printData();
            found = true;
            break;
          }
        }
      }
    }

    if (!found) {
      cout << "El DNI introducido no pertenece a ningún alumno o profesor, "
              "vuelva a intentarlo..."
           << endl;
    }
  }

  delete teacher1;
  delete teacher2;
}

int main() {
  Calificando();
  return 0;
}
