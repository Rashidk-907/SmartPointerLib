template <typename T>
class SharedPtr
{
    struct block
    {
        T *ptr;
        int count;
        block(T *p) : count(1), ptr(p) {}
    };

    block *ctrl;

    void cleanup()
    {
        if (ctrl)
        {
            ctrl->count--;
            if (ctrl->count == 0)
            {
                delete ctrl->ptr;
                delete ctrl;
            }
            ctrl = nullptr;
        }
    }

public:
    SharedPtr(T *ptr = nullptr) : ctrl(ptr ? new block(ptr) : nullptr) {}

    SharedPtr(const SharedPtr &other) : ctrl(other.ctrl)
    {
        if (ctrl)
            ctrl->count++;
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this != &other)
        {
            cleanup();
            ctrl = other.ctrl;
            if (ctrl)
                ctrl->count++;
        }
        return *this;
    }

    SharedPtr(SharedPtr &&other) noexcept : ctrl(other.ctrl)
    {
        other.ctrl = nullptr;
    }

    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
        if (this != &other)
        {
            cleanup();
            ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    T *operator->()
    {
        return ctrl ? ctrl->ptr : nullptr;
    }

    T &operator*()
    {
        return *ctrl->ptr;
    }

    const T *operator->() const
    {
        return ctrl ? ctrl->ptr : nullptr;
    }

    const T &operator*()
        const { return *ctrl->ptr; }

    int count() const
    {
        return ctrl ? ctrl->count : 0;
    }

    T *get() const
    {
        return ctrl ? ctrl->ptr : nullptr;
    }

    ~SharedPtr() { cleanup(); }
};

template <typename T, typename arg>
SharedPtr<T> MakeShared(arg value)
{
    return SharedPtr<T>(new T(value));
}