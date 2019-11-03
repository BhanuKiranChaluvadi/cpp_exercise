// RUN: g++ -std=c++17 find.cpp && ./a.out

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

class Identity
{
    string _name;
    int _age;
    double _height;
public:
    Identity(string name, int age, double height) : _name(name), _age(age), _height(height) {}
    auto get_name() const -> decltype(_name)  { return _name; }
    // string get_name() const { return _name; }
    int get_age() const { return _age; }
    double get_height() const { return _height; }
};


int main() {

    int n1 = 3;
    int n2 = 5;

    vector<int> v{0, 1, 2, 3, 4};

    auto result1 = std::find(std::begin(v), std::end(v), n1);
    auto result2 = std::find(std::begin(v), std::end(v), n2);

    if (result1 != std::end(v))
        std::cout << "v contains: " << n1 << std::endl;
    else
        std::cout << "v does not contains: " << n1 << std::endl;

    if (result2 != std::end(v))
        std::cout << "v contains: " << n2 << std::endl;
    else
        std::cout << "v does not contains: " << n2 << std::endl;

    vector<Identity> identities;
    identities.emplace_back("bhanu", 28, 164);
    identities.emplace_back("ragini", 26, 162);

    string test_string = "bhanu";
    auto result3 = std::find_if(begin(identities), end(identities), [&test_string](const Identity &identity){ return identity.get_name() == test_string; });
    if (result3 != std::end(identities)) {
        std::cout << "identities contains: " <<  test_string << std::endl;
        std::cout << "name: " << result3->get_name() << std::endl;
        std::cout << "age: " << result3->get_age() << std::endl;
        std::cout << "height: " << result3->get_height() << std::endl;
    }
    else
        std::cout << "identities does not contains: " << test_string << std::endl;
    

    auto result4 = std::find_if_not(begin(identities), end(identities), [&test_string](const Identity &identity){ return identity.get_name() == test_string; });
    if (result4 != std::end(identities)) {
        std::cout << "identities doesn't contains: " <<  test_string << std::endl;
        std::cout << "name: " << result4->get_name() << std::endl;
        std::cout << "age: " << result4->get_age() << std::endl;
        std::cout << "height: " << result4->get_height() << std::endl;
    }
    else
        std::cout << "all identies contains: " << test_string << std::endl;

    return 0;
}