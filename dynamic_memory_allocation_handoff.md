# C++ Dynamic Memory Allocation — Mental Models & Handoff

## Purpose

This note captures the exact mental models used to understand:

- variables and memory addresses
- pointers
- `&` and `*`
- dynamic memory allocation
- `new` and `delete`
- dynamically allocated arrays
- objects created with `new`
- `.` vs `->`
- the `this` pointer
- constructor use of `this->`

The most important part is **not the syntax**. It is the **boxes + addresses mental model**.

---

# 1. Mental Model #1: Memory is a collection of numbered boxes

Imagine memory as a huge collection of boxes.

Every box has:

1. an address — where the box is
2. a value — what is currently inside it

For learning, we use made-up addresses such as `612`, `4112`, and `7000`.

Example:

```text
Address 612
    ↓
┌─────────┐
│    5    │
└─────────┘
```

Think:

> **Address = where the box is.**
>
> **Value = what is inside the box.**

The actual addresses in a real program are not guaranteed to be these numbers.

---

# 2. Mental Model #2: A normal variable gives us a name for a box

Consider:

```cpp
int a = 5;
```

Use this picture:

```text
        a
        ↓
Address 612
    ↓
┌─────────┐
│    5    │
└─────────┘
```

`a` is the name we use to access that integer.

Two expressions are especially important:

```cpp
a
&a
```

They answer different questions.

```text
a
↓
"What value is in a?"
↓
5
```

and:

```text
&a
↓
"Where is a?"
↓
612
```

So, in our imaginary example:

```text
a  = 5
&a = 612
```

---

# 3. Mental Model #3: A pointer is ALSO a box

This is the most important pointer mental model.

A pointer is **not the thing it points to**.

A pointer is itself a variable, and therefore it also occupies storage.

Its value happens to be an address.

Consider:

```cpp
int a = 5;
int *ptr = &a;
```

Imagine:

```text
Address 612
    ↓
┌─────────┐
│    5    │
└─────────┘
    ↑
    a


Address 4112
    ↓
┌─────────┐
│   612   │
└─────────┘
    ↑
   ptr
```

There are TWO boxes:

```text
a
↓
box containing 5


ptr
↓
box containing 612
```

And the `612` stored inside `ptr` happens to be the address of `a`.

This is the central pointer model:

```text
POINTER
┌────────────┐
│  ADDRESS   │
└────────────┘
      │
      │ points to
      ↓
TARGET OBJECT
┌────────────┐
│   VALUE    │
└────────────┘
```

---

# 4. `&` means "give me the address"

For:

```cpp
int a = 5;
```

this:

```cpp
&a
```

means:

> Give me the address of `a`.

Mental picture:

```text
        a
        ↓
Address 612
┌─────────┐
│    5    │
└─────────┘
```

So:

```text
&a → 612
```

---

# 5. `*` has an important pointer meaning: follow the address

Given:

```cpp
int *ptr = &a;
```

`ptr` contains:

```text
612
```

Therefore:

```cpp
*ptr
```

means:

> Take the address stored inside `ptr`, go there, and access the value.

Follow the boxes:

```text
ptr
 ↓
┌─────────┐
│   612   │
└─────────┘
     │
     │ go to address 612
     ↓
┌─────────┐
│    5    │
└─────────┘
```

Therefore:

```cpp
*ptr
```

gives:

```text
5
```

---

# 6. The four expressions to keep straight

For:

```cpp
int a = 5;
int *ptr = &a;
```

remember:

```text
a
↓
value inside a
↓
5
```

```text
&a
↓
address of a
↓
612
```

```text
ptr
↓
value inside ptr
↓
612
```

```text
*ptr
↓
follow ptr's address
↓
value there
↓
5
```

So:

```text
a   = 5
&a  = 612
ptr = 612
*ptr = 5
```

And therefore:

```cpp
ptr == &a
```

is true.

---

# 7. Mental Model #4: `new` creates/obtains a new box dynamically

Now we reach dynamic memory allocation.

Consider:

```cpp
int *ptr = new int;
```

Do NOT think:

> "`new` creates a pointer."

Instead think:

> "`new` obtains a new piece of dynamically allocated memory for an `int` and gives me its address."

Suppose the dynamically allocated memory is at address `7000`.

```text
Address 7000
    ↓
┌─────────┐
│    ?    │
└─────────┘
```

`new int` gives us the address:

```text
7000
```

Then that address is stored in `ptr`.

Suppose the pointer itself is at address `4112`:

```text
Address 4112
    ↓
┌─────────┐
│  7000   │
└─────────┘
    ↑
   ptr


Address 7000
    ↓
┌─────────┐
│    ?    │
└─────────┘
```

This picture is the core mental model for dynamic allocation:

```text
POINTER BOX
┌─────────────┐
│    7000     │
└─────────────┘
       │
       │ address
       ↓
DYNAMIC MEMORY BOX
┌─────────────┐
│      ?      │
└─────────────┘
```

---

# 8. Putting a value into dynamically allocated memory

After:

```cpp
int *ptr = new int;
```

we can write:

```cpp
*ptr = 50;
```

Follow the pointer:

```text
ptr
 ↓
┌─────────┐
│  7000   │
└─────────┘
     │
     ↓
Address 7000
┌─────────┐
│    ?    │
└─────────┘
```

`*ptr = 50` means:

> Follow the address stored in `ptr` and put `50` into that box.

Now:

```text
ptr
 ↓
┌─────────┐
│  7000   │
└─────────┘
     │
     ↓
Address 7000
┌─────────┐
│   50    │
└─────────┘
```

Therefore:

```cpp
cout << *ptr;
```

prints:

```text
50
```

---

# 9. `new` with initialization

Instead of:

```cpp
int *ptr = new int;
*ptr = 50;
```

we can write:

```cpp
int *ptr = new int(50);
```

The result is conceptually:

```text
ptr
 ↓
┌─────────┐
│  7000   │
└─────────┘
     │
     ↓
Address 7000
┌─────────┐
│   50    │
└─────────┘
```

---

# 10. Mental Model #5: Pointer and pointed-to memory are different things

This distinction is critical.

For:

```cpp
int *ptr = new int(50);
```

there are two separate things:

### The pointer

```text
ptr
┌─────────┐
│  7000   │
└─────────┘
```

### The dynamically allocated integer

```text
Address 7000
┌─────────┐
│   50    │
└─────────┘
```

Together:

```text
          ptr
           ↓
      ┌─────────┐
      │  7000   │
      └─────────┘
           │
           │
           ↓
      ┌─────────┐
      │   50    │
      └─────────┘
```

Never mentally merge these into one thing.

The pointer stores the address.

The address leads to the dynamically allocated object.

---

# 11. Why `delete` exists

Memory obtained with `new` must eventually be released.

For:

```cpp
int *ptr = new int(50);
```

we use:

```cpp
delete ptr;
```

Mental model before deletion:

```text
ptr
 ↓
┌─────────┐
│  7000   │
└─────────┘
     │
     ↓
Address 7000
┌─────────┐
│   50    │
└─────────┘
```

After:

```cpp
delete ptr;
```

the dynamically allocated object/memory is released.

The pointer variable itself is not the dynamically allocated object.

After deletion, the pointer should not be dereferenced.

A common defensive habit is:

```cpp
delete ptr;
ptr = nullptr;
```

Now the pointer explicitly represents "points to nothing."

---

# 12. Dynamic arrays

For one object:

```cpp
int *ptr = new int(50);
```

use:

```cpp
delete ptr;
```

For an array:

```cpp
int *arr = new int[5];
```

the mental model is:

```text
arr
 ↓
┌─────┬─────┬─────┬─────┬─────┐
│  ?  │  ?  │  ?  │  ?  │  ?  │
└─────┴─────┴─────┴─────┴─────┘
```

`arr` stores the address associated with the first element.

Release it with:

```cpp
delete[] arr;
```

The matching rule is:

```text
new T       → delete
new T[n]    → delete[]
```

---

# 13. Why dynamic allocation can be useful

Consider:

```cpp
int arr[5];
```

The size is fixed at compile time in this ordinary array form.

If the number of elements is known only while the program is running:

```cpp
int n;
cin >> n;

int *arr = new int[n];
```

the program can dynamically obtain storage based on the runtime value.

If:

```text
n = 3
```

the conceptual picture is:

```text
arr
 ↓
┌─────┬─────┬─────┐
│     │     │     │
└─────┴─────┴─────┘
```

Modern C++ normally prefers containers such as `std::vector` for this use case, but understanding `new[]` is important for understanding pointers and dynamic allocation.

---

# 14. Automatic object vs dynamic object

Do not think:

> "The pointer is on the heap."

That is too imprecise.

Consider:

```cpp
void test()
{
    int *p = new int(5);
}
```

There are two different lifetimes/storage questions:

```text
p
↓
local pointer variable
```

and:

```text
*p
↓
dynamically allocated integer
```

The pointer variable `p` is a local automatic variable.

The integer created by `new int(5)` is dynamically allocated.

A correct mental picture is:

```text
LOCAL / AUTOMATIC STORAGE

p
↓
┌─────────┐
│ address │
└─────────┘
     │
     │
     ↓

DYNAMICALLY ALLOCATED STORAGE

┌─────────┐
│    5    │
└─────────┘
```

The pointer and the thing it points to can have different lifetimes.

---

# 15. Classes: normal object

Consider:

```cpp
class Student
{
public:
    string name;
    int age;
};
```

Now:

```cpp
Student s1;
```

means `s1` is the actual Student object.

Mental model:

```text
s1
 ↓
┌─────────────────────┐
│ Student object      │
├─────────────────────┤
│ name                │
│ age                 │
└─────────────────────┘
```

Since `s1` is the object itself, use:

```cpp
s1.name
s1.age
```

The `.` operator means:

> Access a member of this object.

---

# 16. Classes: dynamically allocated object

Now:

```cpp
Student* s3 = new Student("Charlie", 21, "DEF School", 103, 11);
```

Again there are two separate things:

1. `s3` — a pointer
2. the dynamically allocated `Student` object

Imagine:

```text
Address 5000
    ↓
┌─────────┐
│  8000   │
└─────────┘
    ↑
   s3


Address 8000
    ↓
┌──────────────────────────────┐
│ Student object               │
├──────────────────────────────┤
│ name     = "Charlie"         │
│ age      = 21                │
│ school   = "DEF School"      │
│ rollno   = 103               │
│ standard = 11                │
└──────────────────────────────┘
```

The core model is:

```text
s3
 ↓
address
 ↓
Student object
```

---

# 17. Mental Model #6: `.` vs `->`

This is a very important distinction.

## Object

```cpp
Student s1;
```

Use:

```cpp
s1.name;
s1.study();
```

Mental model:

```text
s1
 ↓
Student object
 ↓
member
```

Therefore:

```text
OBJECT → .
```

---

## Pointer to object

```cpp
Student *s3;
```

Use:

```cpp
s3->name;
s3->study();
```

Mental model:

```text
s3
 ↓
address
 ↓
Student object
 ↓
member
```

Therefore:

```text
POINTER TO OBJECT → ->
```

The rule to memorize:

```text
OBJECT
   ↓
   .

POINTER TO OBJECT
   ↓
   ->
```

---

# 18. What `->` actually means

This:

```cpp
s3->name
```

is shorthand for:

```cpp
(*s3).name
```

Follow it step by step:

```text
s3
 ↓
address
 ↓
*s3
 ↓
Student object
 ↓
.name
 ↓
name member
```

Therefore:

```cpp
s3->name
```

means:

> Follow `s3` to the Student object, then access its `name`.

Likewise:

```cpp
s3->study();
```

is equivalent to:

```cpp
(*s3).study();
```

The arrow operator is simply convenient member access through a pointer.

---

# 19. Why `(*s3)` needs parentheses

These are equivalent:

```cpp
s3->name
```

and:

```cpp
(*s3).name
```

The parentheses matter because we first want to dereference `s3` and then use `.` on the resulting object.

Do not casually rewrite it as:

```cpp
*s3.name
```

That has different operator parsing.

For practical use, remember:

```cpp
pointer->member
```

is the clean syntax.

---

# 20. The `this` pointer

Inside a non-static member function, C++ provides a special pointer:

```cpp
this
```

Mental model:

```text
CURRENT OBJECT
      ↑
      │
     this
```

Suppose:

```cpp
Student s1("Alice", 20);
s1.study();
```

While `study()` is running:

```text
this
 ↓
s1
 ↓
Student object containing Alice
```

If:

```cpp
Student s2("Bob", 22);
s2.study();
```

then during that call:

```text
this
 ↓
s2
 ↓
Student object containing Bob
```

So the same member function can work with different objects because `this` points to the object whose member function is currently executing.

---

# 21. Why `this->name` appears in the constructor

Suppose the class contains:

```cpp
string name;
```

and the constructor parameter is also named:

```cpp
Student(string name)
```

There are now two different `name`s.

The member belonging to the current object is:

```cpp
this->name
```

The constructor parameter is:

```cpp
name
```

Therefore:

```cpp
this->name = name;
```

means:

```text
current Student object's name
        =
constructor parameter name
```

For:

```cpp
Student s1("Alice", 20);
```

the constructor effectively establishes:

```text
s1 object's name = "Alice"
```

---

# 22. Full Student example using the boxes + addresses model

```cpp
class Student
{
public:
    string name;
    int age;

    Student(string name, int age)
    {
        this->name = name;
        this->age = age;
    }

    void study()
    {
        cout << this->name << " is studying" << endl;
    }
};

int main()
{
    Student s1("Alice", 20);

    Student* s2 = new Student("Bob", 22);

    cout << s1.name << endl;
    cout << s2->name << endl;

    s1.study();
    s2->study();

    delete s2;
}
```

Conceptually:

```text
AUTOMATIC OBJECT

s1
 ↓
┌─────────────────┐
│ name = Alice    │
│ age  = 20       │
└─────────────────┘


POINTER

s2
 ↓
┌─────────────────┐
│ address = 8000  │
└─────────────────┘
        │
        ↓

DYNAMIC OBJECT

Address 8000
 ↓
┌─────────────────┐
│ name = Bob      │
│ age  = 22       │
└─────────────────┘
```

Therefore:

```cpp
s1.name
```

uses `.` because `s1` is the object.

```cpp
s2->name
```

uses `->` because `s2` is a pointer to the object.

---

# 23. A translation table for reading C++ code

When you see:

```cpp
&a
```

translate it mentally as:

> "Where is `a`?"

When you see:

```cpp
ptr
```

translate it as:

> "What address is stored inside `ptr`?"

When you see:

```cpp
*ptr
```

translate it as:

> "Go to the address stored in `ptr`."

When you see:

```cpp
new int
```

translate it as:

> "Dynamically obtain storage for an integer and give me its address."

When you see:

```cpp
delete ptr
```

translate it as:

> "Release the dynamically allocated object that `ptr` points to."

When you see:

```cpp
object.member
```

translate it as:

> "Access this member directly from the object."

When you see:

```cpp
pointer->member
```

translate it as:

> "Follow the pointer to the object, then access this member."

When you see:

```cpp
this
```

translate it as:

> "Pointer to the current object."

When you see:

```cpp
this->member
```

translate it as:

> "Access this member through the current-object pointer."

---

# 24. One master mental model

Keep this picture in your head whenever you encounter a pointer:

```text
                 POINTER
              ┌───────────┐
              │  ADDRESS  │
              └───────────┘
                    │
                    │ follow
                    ↓
              TARGET OBJECT
           ┌────────────────┐
           │ data            │
           │ data            │
           │ data            │
           └────────────────┘
```

For a normal object:

```text
s1 ───────────────→ Student object
```

For a pointer to an object:

```text
s3 ──→ address ──→ Student object
```

For:

```cpp
s3->name
```

think:

```text
s3
 ↓
address
 ↓
Student object
 ↓
name
```

For:

```cpp
this->name
```

think:

```text
this
 ↓
current Student object
 ↓
name
```

---

# 25. Final concept map

The concepts form one chain:

```text
VARIABLE
   │
   │ has a
   ↓
ADDRESS
   │
   │ can be obtained using
   ↓
&
   │
   │ stored inside a
   ↓
POINTER
   │
   │ followed using
   ↓
*
   │
   ├───────────────┐
   │               │
   ↓               ↓
existing object   dynamic memory
                  │
                  │ created/obtained using
                  ↓
                 new
                  │
                  │ released using
                  ↓
                delete
```

For classes:

```text
Student object
      │
      ├── object.member
      │       ↓
      │       .
      │
      └── pointer-to-object
              ↓
          pointer->member
              ↓
              ->
```

And inside a member function:

```text
current object
      ↑
      │
     this
      │
      ↓
this->member
```

---

# 26. What to learn next

Once this mental model feels natural, the next useful sequence is:

1. Pointer vs reference
2. References (`T&`)
3. Stack vs heap in more detail
4. Object lifetime
5. Constructors and destructors
6. RAII
7. `std::unique_ptr`
8. `std::shared_ptr`
9. `std::weak_ptr`
10. Dynamic data structures such as linked lists and trees

Do not skip the boxes + addresses model. It is the foundation that makes the later concepts much easier.

---

# 27. The one picture to reconstruct from memory

If you forget everything, draw this:

```text
pointer variable
┌─────────────┐
│   ADDRESS   │
└─────────────┘
       │
       │
       ↓
actual object
┌─────────────────┐
│ data            │
│ data            │
│ data            │
└─────────────────┘
```

Then ask yourself two questions:

> **What is inside the pointer box?**

and:

> **Where does that address lead?**

If you can answer those two questions, you can usually decode the pointer-related C++ syntax in front of you.
