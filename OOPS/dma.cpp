#include<iostream>
using namespace std;

class Student
{
public:
    // Attr
    string name;
    int age;
    string school;
    int rollno;
    int standard;

    // parameterized constructor

    Student(string name, int age, string school, int rollno, int standard)
    {
        this->name = name;
        this->age = age;
        this->school = school;
        this->rollno = rollno;
        this->standard = standard;

        cout<< "Student ka parameterized ctor called"<<endl;
    }

    // methods
    void study(){
        cout<< this->name <<" is Studying"<<endl;
    }

    void sleep(){
        cout<< this->name <<" is Sleeping"<<endl;
    }

    void bunk(){
        cout<< this->name <<" is Bunking"<<endl;
    }
};

int main(){
    Student s1("Alice", 20, "ABC School", 101, 10);
    Student s2("Bob", 22, "XYZ School", 102, 12);

    s1.study();
    s1.sleep();
    s1.bunk();

    s2.study();
    s2.sleep();
    s2.bunk();


    // DMA (Dynamic Memory Allocation) for Student objects

    Student* s3 = new Student("Charlie", 21, "DEF School", 103, 11);

    cout<< "Student s3 ka name: " << s3->name << endl;
    s3->study();

    // Deallocate memory
    delete s3;
}