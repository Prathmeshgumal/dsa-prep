# OOPS + DMA — My Mental Model

**Every box has a value (inside) and an address (below).**

## Class basics

### The code (from classes.cpp)

![code](diagrams/code.svg)

### Class & object creation

![class](diagrams/class.svg)

### Constructors: default & parameterized

![constructors](diagrams/constructors.svg)

- Same name as the class, no return type.
- If you write a parameterized ctor, C++ does **not** give you a default one. Add `Student() {}` if you need `Student s;`.

### Copy constructor

![copy](diagrams/copy.svg)

### Methods & destructor

![lifecycle](diagrams/lifecycle.svg)

Inside a method, `this` → the object that called it (`A.study()` → `this` = A).

---

# DMA

## 1. Pointer

![pointer](diagrams/pointer.svg)

- `&a` = **address of variable a**
- `a  = 5` (value inside) | `&a = 602` (where it is)
- `*` is the **dereference operator**: `*ptr` = go to the address in ptr and use that box.

## 2. Putting a value into dynamic memory

![new int](diagrams/new-int.svg)

![put value](diagrams/put-value.svg)

Shortcut: `int *ptr = new int(50);` does both steps in one line.

## 3. Dynamic memory allocation (objects)

![dma](diagrams/dma.svg)

`new` makes the object and gives back its address → the pointer stores that address.

## Remember

- Pointer box ≠ object box. They are two separate boxes.
- Object → `.` | Pointer → `->`
- `new` → `delete` | `new[]` → `delete[]`
