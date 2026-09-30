#include<iostream>
#include<string>
using namespace std;

class Student
{
public:

    // Attributes: properties that belong to a object 
    int id;
    int age;
    string name;
    int nos;

    // constructor
    Student()
    {
        cout<<"Student ka default ctor called"<<endl;
    }

    // Behaviour(methods/functions)

    void study(){
        cout<< this->name <<" is Studying"<<endl;
    }

    void sleep(){
        cout<< this->name <<" is Sleeping"<<endl;
    }

    void bunk(){
        cout<< this->name <<" is Bunking"<<endl;
    }

    // destructor
    ~Student()
    {
        cout<< "Student ka default dtor called"<<endl;
    }
};

int main(){
    Student prathmesh;
    prathmesh.id = 1;
    prathmesh.age = 23;
    prathmesh.name = "Prathmesh";
    prathmesh.nos = 6;

    prathmesh.study();
    prathmesh.sleep();
    prathmesh.bunk();

    return 0;
}