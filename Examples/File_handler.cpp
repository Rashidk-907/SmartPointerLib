#include <iostream>
#include <fstream>
#include "SmartPointerLib/Include/UniquePtr.h"
// RAII File Wrapper using your UniquePtr
class FileHandler
{
private:
    UniquePtr<std::fstream> file;

public:
    FileHandler(const std::string &filename)
    {
        file.reset(new std::fstream(filename, std::ios::out));
        if (!file->is_open())
        {
            throw std::runtime_error("Failed to open file");
        }
    }

    void write(const std::string &content)
    {
        *file << content;
    }

    // No need for explicit destructor! File automatically closes
};

void demo_file_management()
{
    std::cout << "=== File Management Demo ===\n";

    try
    {
        FileHandler writer("test.txt");
        writer.write("Hello, Smart Pointers!\n");
        writer.write("This is automatic resource management.\n");

        // file automatically closes when writer goes out of scope
        std::cout << "File written and automatically closed\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}

main()
{
    demo_file_management();
}