# SmartPointerLib 🚀

A modern C++ implementation of smart pointers for educational purposes.

## Features
- ✅ `Unique_Ptr` - Exclusive ownership
- ✅ `Shared_Ptr` - Shared ownership with reference counting  
- ✅ `Weak_Ptr` - Non-owning references
- ✅ Factory functions (`MakeUnique`, `MakeShared`)
- ✅ Exception safety guarantees
- ✅ STL-compatible interface

## Usage
```cpp
#include "smart_ptr/unique_ptr.hpp"

auto ptr = MakeUnique<int>(42);