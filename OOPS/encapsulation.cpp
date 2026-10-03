#include<iostream>
using namespace std;

class Student
{

private:
    //Attr
    int id;
    int age;
    string name;
    int nos;

    //Attr
    int *gpa;
    string girlfriend;

public:
    //parameterized constructor
    Student(int id, int age, string name, int nos, int gpa, string girlfriend)
    {
        cout<< "Student ka parameterized ctor called"<<endl;
        this->id = id;
        this->age = age;
        this->name = name;
        this->nos = nos;

        this->gpa = new int(gpa);
        this->girlfriend = girlfriend;
    }

    //getter methods
    void getId(){
        cout<< "ID of "<< this->name <<" is: "<< this->id <<endl;
    }

    void getGpa(){
        cout<< "GPA of "<< this->name <<" is: "<< *(this->gpa) <<endl;
    }

    //setter methods
    void setId(int id){
        // authorization check
        
        this->id = id;
    }

    void setGpa(int gpa){
        *(this->gpa) = gpa;
    }

    //methods
    void study(){
        cout<< this->name <<" is Studying"<<endl;
    }

    void sleep(){
        cout<< this->name <<" is Sleeping"<<endl;
    }

    void bunk(){
        cout<< this->name <<" is Bunking"<<endl;
    }
private:
    void chatting(){
        cout<< this->name <<" is Chatting with "<< this->girlfriend <<endl;
    }

public:
    //destructor
    ~Student()
    {
        cout<< "Student ka destructor called"<<endl;
        delete this->gpa;
    }
};

int main(){

    Student A(1, 20, "Alice", 5, 3, "Harshali");
    // A.id = 5; // This will give an error because id is private
    A.getGpa();
    A.getId();

    A.setId(10);
    A.setGpa(4);
    A.getGpa();
    A.getId();
    return 0;
}