template <typename T>
class UniquePtr
{
private:
    T *pointer;

public:
    UniquePtr(T *ptr = nullptr) : pointer(ptr) {}

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other)
    {
        pointer = other.pointer;
        other.pointer = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other)
    {
        if (this != &other)
        {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }

    T *get()
    {
        return pointer;
    }

    T &operator*()
    {
        return *pointer;
    }

    T *operator->()
    {
        return pointer;
    }

    T *release()
    {
        T *ptr = pointer;
        pointer = nullptr;
        return ptr;
    }

    void reset(T *ptr = nullptr)
    {
        delete pointer;
        pointer = ptr;
    }
    
    ~UniquePtr()
    {
        delete pointer;
    }
};

template <typename T, typename Arg>
UniquePtr<T> MakeUnique(Arg value)
{
    return UniquePtr<T>(new T(value));
}

