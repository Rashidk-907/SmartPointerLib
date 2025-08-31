#include <iostream>
#include "D:\Coding\Github\Smart Pointers\Include\SharedPtr.h"

using namespace std;

class TestObject
{
public:
    int value;
    string name;

    TestObject(int v = 0, string n = "default") : value(v), name(n)
    {
        cout << "Constructed: " << name << " (" << value << ")\n";
    }

    ~TestObject()
    {
        cout << "Destroyed: " << name << " (" << value << ")\n";
    }

    void print() const
    {
        cout << "Object: " << name << ", Value: " << value << "\n";
    }
};

void test_basic_functionality()
{
    cout << "=== Test 1: Basic Functionality ===\n";
    SharedPtr<TestObject> ptr1(new TestObject(10, "first"));
    cout << "Count: " << ptr1.count() << "\n"; // Should be 1
    ptr1->print();
}

void test_copy_semantics()
{
    cout << "\n=== Test 2: Copy Semantics ===\n";
    SharedPtr<TestObject> ptr1(new TestObject(20, "second"));
    cout << "ptr1 count: " << ptr1.count() << "\n"; // 1

    SharedPtr<TestObject> ptr2 = ptr1;                           // Copy constructor
    cout << "After copy - ptr1 count: " << ptr1.count() << "\n"; // 2
    cout << "ptr2 count: " << ptr2.count() << "\n";              // 2

    ptr2->value = 999;                             // Should affect both pointers
    cout << "ptr1 value: " << ptr1->value << "\n"; // Should be 999
}

void test_assignment_operator()
{
    cout << "\n=== Test 3: Assignment Operator ===\n";
    SharedPtr<TestObject> ptr1(new TestObject(30, "third"));
    SharedPtr<TestObject> ptr2(new TestObject(40, "fourth"));

    cout << "Before assignment:\n";
    cout << "ptr1 count: " << ptr1.count() << "\n"; // 1
    cout << "ptr2 count: " << ptr2.count() << "\n"; // 1

    ptr2 = ptr1; // Assignment operator

    cout << "After assignment:\n";
    cout << "ptr1 count: " << ptr1.count() << "\n"; // 2
    cout << "ptr2 count: " << ptr2.count() << "\n"; // 2
}

void test_move_semantics()
{
    cout << "\n=== Test 4: Move Semantics ===\n";
    SharedPtr<TestObject> ptr1(new TestObject(50, "fifth"));
    cout << "Before move - ptr1 count: " << ptr1.count() << "\n"; // 1

    SharedPtr<TestObject> ptr2 = std::move(ptr1); // Move constructor
    cout << "After move:\n";
    cout << "ptr1 count: " << ptr1.count() << "\n"; // 0 (moved from)
    cout << "ptr2 count: " << ptr2.count() << "\n"; // 1

    ptr2->print();
}

void test_factory_function()
{
    cout << "\n=== Test 5: Factory Function ===\n";
    auto ptr = MakeShared<TestObject>(1);
    cout << "Count: " << ptr.count() << "\n"; // 1
    ptr->print();
}

void test_scope_behavior()
{
    cout << "\n=== Test 6: Scope Behavior ===\n";
    SharedPtr<TestObject> outer_ptr(new TestObject(70, "outer"));
    cout << "Outer count: " << outer_ptr.count() << "\n"; // 1

    {
        SharedPtr<TestObject> inner_ptr = outer_ptr;
        cout << "Inner scope - count: " << outer_ptr.count() << "\n"; // 2
    } // inner_ptr destroyed here

    cout << "Back to outer - count: " << outer_ptr.count() << "\n"; // 1
} // outer_ptr destroyed here, object deleted

void test_null_behavior()
{
    cout << "\n=== Test 7: Null Behavior ===\n";
    SharedPtr<TestObject> null_ptr(nullptr);
    cout << "Null ptr count: " << null_ptr.count() << "\n"; // 0 or 1?

    SharedPtr<TestObject> another_ptr = null_ptr;
    cout << "Copied null count: " << another_ptr.count() << "\n";
}

int main()
{
    test_basic_functionality();
    test_copy_semantics();
    test_assignment_operator();
    test_move_semantics();
    test_factory_function();
    test_scope_behavior();
    test_null_behavior();

    cout << "\n=== All tests completed ===\n";
    return 0;
}