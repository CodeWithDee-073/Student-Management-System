#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
{
  string r, n, p, c, a; // Roll, Name, Parent's Name, Class, Address
  fstream file;

public:
  void add();
  void view();
  void search();
  void update();
};

void Student::add()
{
  cout << "\nEnter Roll No., Name, Parent's Name, Class, Address:\n";
  getline(cin, r); 
  getline(cin, n); 
  getline(cin, p); 
  getline(cin, c); 
  getline(cin, a); 

  file.open("data.txt", ios::app);                                   
  file << r << "|" << n << "|" << p << "|" << c << "|" << a << endl; 
  file.close();
  cout << "Record added successfully!\n\n";
}

void Student::view()
{
  file.open("data.txt", ios::in); 
  if (!file)
  {
    cout << "No records found.\n";
    return;
  }

  while (getline(file, r, '|') && getline(file, n, '|') &&
         getline(file, p, '|') && getline(file, c, '|') &&
         getline(file, a))
  {
    cout << "Roll No: " << r << ", Name: " << n
         << ", Parent's Name: " << p
         << ", Class: " << c
         << ", Address: " << a << endl;
  }

  file.close();
}

void Student::search()
{
  cout << "Enter Roll No. to search: ";
  string sr; // search roll
  getline(cin, sr);

  file.open("data.txt", ios::in);
  bool found = false;

  while (getline(file, r, '|') && getline(file, n, '|') &&
         getline(file, p, '|') && getline(file, c, '|') &&
         getline(file, a))
  {
    if (r == sr)
    {
      cout << "Roll No: " << r << ", Name: " << n
           << ", Parent's Name: " << p
           << ", Class: " << c
           << ", Address: " << a << endl;
      found = true;
      break;
    }
  }

  if (!found)
    cout << "No student found with Roll Number: " << sr << endl;

  file.close();
}

void Student::update()
{
  cout << "Enter Roll No. to update: ";
  string sr, nn, nf, na; 
  getline(cin, sr);

  fstream temp;
  file.open("data.txt", ios::in);
  temp.open("temp.txt", ios::out);

  bool found = false;

  while (getline(file, r, '|') && getline(file, n, '|') &&
         getline(file, p, '|') && getline(file, c, '|') &&
         getline(file, a))
  {
    if (r == sr)
    {
      cout << "Enter new details (Name, Parent's Name, Class, Address):\n";
      getline(cin, nn); // New Name
      getline(cin, nf); // New Parent's Name
      getline(cin, na); // New Address

      temp << r << "|" << nn << "|" << nf << "|" << c << "|" << na << endl;
      cout << "Record updated successfully!\n";
      found = true;
    }
    else
    {
      temp << r << "|" << n << "|" << p << "|" << c << "|" << a << endl;
    }
  }

  if (!found)
    cout << "No student found with Roll Number: " << sr << endl;

  file.close();
  temp.close();

  // Replace original file with the updated one
  remove("data.txt");
  rename("temp.txt", "data.txt");
}

int main()
{
  Student obj;
  char ch;
  do
  {
    cout << "\n=================================\n";
    cout << "    STUDENT MANAGEMENT SYSTEM     \n";
    cout << "=================================\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";

    cin >> ch;
    cin.ignore(); 
    switch (ch)
    {
    case '1':
      obj.add();
      break;
    case '2':
      obj.view();
      break;
    case '3':
      obj.search();
      break;
    case '4':
      obj.update();
      break;
    case '5':
      return 0;
    default:
      cout << "Invalid choice, try again.\n";
    }
  } while (true);
}
