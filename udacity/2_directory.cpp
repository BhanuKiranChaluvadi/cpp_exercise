// RUN: g++ -std="c++17"  -Wall -Wextra 2_directory.cpp  && ./a.out

#include<iostream>
#include<dirent.h>

using std::cout;
using std::cin;
using std::endl;


int main() 
{
    DIR *dirPtr = nullptr;
    dirPtr = opendir("/proc/");

    struct dirent *pent = nullptr;

    if(dirPtr == nullptr) {
        cout << "\nERROR! directory pointer could not be initialised correctly";
        exit (3);
    }

    while (pent = readdir(dirPtr)) {
        if(pent == nullptr) {
            cout << "\nERROR! pent could not be initialised correctly";
            exit (3);
        }
        // otherwise, it was initialised correctly. Let's print it on the console:
        cout << pent->d_name << endl;
    }

    // finally, let's close the directory
    closedir (dirPtr);
    
    return 0;
}
