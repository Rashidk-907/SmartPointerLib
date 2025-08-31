#include "SharedPtr.h"
#include "UniquePtr.h"

template <typename T, typename arg>
SharedPtr<T> MakeShared(arg value)
{
    return SharedPtr<T>(new T(value));
}

template <typename T, typename Arg>
UniquePtr<T> MakeUnique(Arg value)
{
    return UniquePtr<T>(new T(value));
}

int main()
{
    SharedPtr<testing> a = MakeShared<testing>('A');
    UniquePtr<testing> b = MakeUnique<testing>('B');
    return 0;
}

