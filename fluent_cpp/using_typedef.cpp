/*
** RUN: g++ -std=c++17 using_typedef.cpp && ./a.out
** Simple example explaining 
** Older - typedef
** Newer - Using  -- Athough serve same purpose , "using" works best with templates. 
** A template declaration cannot appear at block scope {}.
** We can put type (typedef && using with out template) alias every where we wish - in namespace/in class / in bocks {}
** Alias templates on other hand follow the same rules of any other templated thing in C++: they cannot appear inside a block. 
** They are actual template declarations, after all!
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

using std::cout;
using std::endl;

typedef int pixel;
// using pixel = int ;

pixel getScreenWidth() {
    return 720;
}

template<typename key, typename values>
using Map = std::map<key, std::vector<values> > ;

template<typename Iterator>
bool wasAlreadyInTheMap (std::pair<Iterator, bool> const& insertionResult) {
    return !insertionResult.second;
}

int main() {

    // typedef std::map<std::string, std::vector<std::string>> Map;
    // using Map = std::map<std::string, std::vector<std::string> >;
    // Map map;
    Map <std::string, std::string> map;
    Map <int, int> map2;
    Map <std::string, int> map3;


    // directly
    std::pair<Map<std::string, std::string>::iterator, bool> insertionResult = map.insert({"Chaluvadi", std::vector<std::string>{"Bhanu", "Kiran"} });
    if (!insertionResult.second) {
        cout << "The element already exists in the map." << endl;
    }

    // using auto for type deduction
    auto insertionResult2 = map.insert({"Chaluvadi", std::vector<std::string>{"Bhanu", "Kiran"} });
    auto const wasAlreadyInTheSet = !insertionResult2.second;
    if (wasAlreadyInTheSet) {
        cout << "The element was already in the map." << endl;
    }

    // c++17 - structured bindings
    auto const [position, hasBeenInserted]  = map.insert({"Chaluvadi", std::vector<std::string>{"Bhanu", "Kiran"} });
    if (!hasBeenInserted) {
        cout << "The element was already in the map." << endl;
    }

    // using auto with function
    auto insertionResult3 = map.insert({"Chaluvadi", std::vector<std::string>{"Bhanu", "Kiran"} });
    if(wasAlreadyInTheMap(insertionResult3)) {
        cout << "The element was already in the map." << endl;
    }


    return 0;
}
