#include <iostream>
#include <fstream>
#include "SmartPointerLib/Include/SharedPtr.h"
#include <vector>

// RAII File Wrapper using your UniquePtr
// Shape hierarchy demonstrating shared_ptr with polymorphism
// ListNode with shared_ptr for next pointer
template <typename T>
class ListNode
{
public:
    T data;
    SharedPtr<ListNode<T>> next;

    ListNode(T val) : data(val), next(nullptr) {}
};

void demo_linked_list()
{
    std::cout << "\n=== Linked List Demo ===\n";

    // Create linked list: 1 -> 2 -> 3
    auto node1 = MakeShared<ListNode<int>>(1);
    auto node2 = MakeShared<ListNode<int>>(2);
    auto node3 = MakeShared<ListNode<int>>(3);

    node1->next = node2;
    node2->next = node3;

    // Traverse list
    SharedPtr<ListNode<int>> current = node1;
    while (current != nullptr)
    {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "null\n";

    // Shared ownership demonstration
    auto another_ref = node2;                                  // Now node2 has 2 owners
    std::cout << "Node2 ref count: " << node2.count() << "\n"; // 2
}

main()
{
    demo_linked_list();
}