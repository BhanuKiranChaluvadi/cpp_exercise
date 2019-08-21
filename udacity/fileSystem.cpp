// RUN: g++ --std=c++17 fileSystem.cpp -lstdc++fs && ./a.out

#include <experimental/filesystem>
#include <string>
#include <iostream>

namespace fs = std::experimental::filesystem;
using namespace std;

int main()
{
    ///
    std::string path = std::experimental::filesystem::current_path();
    std::cout << "current path = " << path << std::endl;
    ///
    fs::path aPath {"./path/to/file.txt"};
    cout << "Parent path: " << aPath.parent_path() << endl;
    cout << "Filename: " << aPath.filename() << endl;
    cout << "Extension: " << aPath.extension() << endl;
    ///
    cout << "Separator in my system " << fs::path::preferred_separator << endl;
    ///
    fs::path root {"/"};
    fs::path dir {"var/www/"};
    fs::path index {"index.html"};

    fs::path pathToIndex = root / dir / index;

    cout << pathToIndex << endl;
    /// 
    fs::create_directories("sandbox/a/b/index.html");
    fs::create_directories("sandbox/c/d");
    system("ls -la sandbox/*");
    ///
    cout << "Is path exsits? " << fs::exists("sandbox/a/b/index.html")
    ///
    cout << "Were directories removed? " << fs::remove_all("sandbox/a/b/index.html") << endl;
    cout << "Were directories removed? " << fs::remove_all("sandbox") << endl;

    system("ls -la sandbox/*");
 

    return 0;
}
