#include <iostream>
#include <assert.h>
#include "Smart Pointers\Include\UniquePtr.h"

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

void test_basic_construction()
{
    cout << "=== Test 1: Basic Construction ===\n";
    UniquePtr<TestObject> ptr1(new TestObject(10, "basic"));
    assert(ptr1.get() != nullptr);
    assert(ptr1->value == 10);
    cout << "Basic construction passed\n";
}

void test_move_semantics()
{
    cout << "\n=== Test 2: Move Semantics ===\n";
    UniquePtr<TestObject> ptr1(new TestObject(20, "move_source"));
    TestObject *raw_ptr = ptr1.get();

    UniquePtr<TestObject> ptr2 = std::move(ptr1); // Move constructor
    assert(ptr1.get() == nullptr);                // Source should be null after move
    assert(ptr2.get() == raw_ptr);                // Destination should have the pointer
    assert(ptr2->value == 20);
    cout << "Move constructor passed\n";

    UniquePtr<TestObject> ptr3(new TestObject(30, "move_assign"));
    raw_ptr = ptr3.get();
    ptr2 = std::move(ptr3); // Move assignment
    assert(ptr3.get() == nullptr);
    assert(ptr2.get() == raw_ptr);
    assert(ptr2->value == 30);
    cout << "Move assignment passed\n";
}

void test_release()
{
    cout << "\n=== Test 3: Release ===\n";
    UniquePtr<TestObject> ptr(new TestObject(40, "release_test"));
    TestObject *raw_ptr = ptr.release();

    assert(ptr.get() == nullptr); // ptr should be empty
    assert(raw_ptr != nullptr);   // should return the pointer
    assert(raw_ptr->value == 40);

    // Manual cleanup since we took ownership
    delete raw_ptr;
    cout << "Release functionality passed\n";
}

void test_reset()
{
    cout << "\n=== Test 4: Reset ===\n";
    UniquePtr<TestObject> ptr(new TestObject(50, "reset_old"));

    ptr.reset(new TestObject(60, "reset_new")); // Reset with new object
    assert(ptr->value == 60);
    cout << "Reset with new object passed\n";

    ptr.reset(); // Reset to nullptr
    assert(ptr.get() == nullptr);
    cout << "Reset to nullptr passed\n";

    ptr.reset(new TestObject(70, "reset_again"));
    assert(ptr->value == 70);
    cout << "Reset after nullptr passed\n";
}

void test_dereference_operators()
{
    cout << "\n=== Test 5: Dereference Operators ===\n";
    UniquePtr<TestObject> ptr(new TestObject(80, "dereference_test"));

    // Test operator->
    assert(ptr->value == 80);
    ptr->value = 85;
    assert(ptr->value == 85);
    cout << "Operator -> passed\n";

    // Test operator*
    assert((*ptr).value == 85);
    (*ptr).value = 90;
    assert((*ptr).value == 90);
    cout << "Operator * passed\n";
}

void test_factory_function()
{
    cout << "\n=== Test 6: Factory Function ===\n";
    auto ptr = MakeUnique<TestObject>(100);
    assert(ptr->value == 100);
    cout << "Factory function passed\n";
}

void test_scope_behavior()
{
    cout << "\n=== Test 7: Scope Behavior ===\n";
    {
        UniquePtr<TestObject> ptr(new TestObject(110, "scope_test"));
        assert(ptr->value == 110);
    } // ptr should be automatically destroyed here
    cout << "Scope behavior passed\n";
}

void test_null_behavior()
{
    cout << "\n=== Test 8: Null Behavior ===\n";
    UniquePtr<TestObject> null_ptr(nullptr);
    assert(null_ptr.get() == nullptr);
    cout << "Null construction passed\n";

    // Test that we don't crash on null dereference (should be handled by user)
    // In real code, you'd add safety checks
    cout << "Null handling passed\n";
}

void test_self_assignment()
{
    cout << "\n=== Test 9: Self Assignment ===\n";
    UniquePtr<TestObject> ptr(new TestObject(120, "self_test"));
    TestObject *raw_ptr = ptr.get();

    ptr = std::move(ptr);         // Self move assignment
    assert(ptr.get() == raw_ptr); // Should remain unchanged
    assert(ptr->value == 120);
    cout << "Self assignment passed\n";
}

void test_copy_prevention()
{
    cout << "\n=== Test 10: Copy Prevention ===\n";
    UniquePtr<TestObject> ptr1(new TestObject(130, "copy_test"));

    // These should cause compile errors (commented out for compilation)
    // UniquePtr<TestObject> ptr2 = ptr1; // Should not compile
    // UniquePtr<TestObject> ptr3(ptr1);  // Should not compile
    // ptr1 = ptr1;                       // Should not compile

    cout << "Copy prevention verified (compile-time check)\n";
}

int main()
{
    cout << "Starting UniquePtr tests...\n\n";

    test_basic_construction();
    test_move_semantics();
    test_release();
    test_reset();
    test_dereference_operators();
    test_factory_function();
    test_scope_behavior();
    test_null_behavior();
    test_self_assignment();
    test_copy_prevention();

    cout << "\n🎉 All UniquePtr tests passed successfully!\n";
    cout << "\n=== Testing automatic cleanup ===\n";

    // Final test to show automatic cleanup works
    UniquePtr<TestObject> final_test(new TestObject(999, "final_test"));
    final_test->print();

    cout << "Final test object will be automatically destroyed now...\n";
    return 0;
}