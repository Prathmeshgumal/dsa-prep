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

    // parameterized constructor
    Student(int id, int age, string name, int nos)
    {
        this->id = id;
        this->age = age;
        this->name = name;
        this->nos = nos;

        cout<< "Student ka parameterized ctor called"<<endl;
    }

    // copy constructor
    Student(const Student &obj)
    {
        this->id = obj.id;
        this->age = obj.age;
        this->name = obj.name;
        this->nos = obj.nos;

        cout<< "Student ka copy constructor called"<<endl;
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
    Student A(1, 23, "Prathmesh", 6);      //  -> each of them is a object of Student class
    Student B(2, 24, "Rahul", 7);
    Student C(3, 25, "Ramesh", 8);
    Student D(4, 26, "Suresh", 9);

    cout<< "Student A ka name: "<<A.name<<endl;  //  -> access the attributs of a object
    cout<< "Student B ka name: "<<B.name<<endl;
    cout<< "Student C ka name: "<<C.name<<endl;
    cout<< "Student D ka name: "<<D.name<<endl;


    Student Rahul(B);  // copy constructor called

    cout<< "Rahul ka name: "<<Rahul.name<<endl;
    cout<< "Rahul ka id: "<<Rahul.id<<endl;
    cout<< "Rahul ka age: "<<Rahul.age<<endl;
    cout<< "Rahul ka nos: "<<Rahul.nos<<endl;

    
    return 0;
}