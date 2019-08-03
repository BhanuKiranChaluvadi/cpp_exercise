// RUN: g++ -std="c++17"  -Wall -Wextra 3_processParser.cpp  && ./a.out

#include<iostream>
#include<dirent.h>
#include<fstream>
#include<sstream>
#include<vector>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;

// wrapper for creating streams
void getStream(std::string path, std::ifstream& stream){
    stream.open (path, std::ifstream::in);
    if (!stream && !stream.is_open()){
        stream.close();
        throw std::runtime_error("Non - existing PID");
    }
}

string  getVmSize(string pid){
    string key = "VmData";
    float value;

    string path = "/proc/"+pid+"/status";
    std::ifstream ifs;
    getStream(path, ifs);
    string line;
    while(getline(ifs, line)) {
        if(line.compare(0, key.size(), key) == 0) {
            std::istringstream iss(line);
            std::vector<string> words(std::istream_iterator<string>{iss}, std::istream_iterator<string>());
            std::for_each(words.begin(), words.end(), [](string &word){cout << word << endl;});
            value = stof(words[1])/float(1024);
            break;
        }
    }
    return std::to_string(value);
}

int getNumberOfCores() {
    string name = "cpu cores";
    string result = "";
    // path
    string path = std::string("/proc/") + "cpuinfo";
    ifstream ifs;
    getStream(path, ifs);
    string line;
    while(getline(ifs, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            std::for_each(values.begin(), values.end(), [](string &word){cout << word << endl;});
            result = values[3];
            return stoi(result);
        }
    }
    cout << "result: " << result << endl;
    return 0;
}

string getOSName(){
    string path = "/etc/os-release";
    string name = "PRETTY_NAME=";
    string result = "";
    ifstream stream;
    getStream(path, stream);
    string line;
    while(getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            // remove quotes
            result = line.substr (name.size()+1);
            result.erase(std::remove(begin(result), end(result), '"'), result.end());
            cout << "result: " << result << endl;
            return result;
        }
    }
    return result;
}

void test_lambda() {
    vector<string> pid{"1", "2", "3"};
    int result=0;
    for_each(begin(pid), end(pid), [&result](const string &pid){
        result++;
    });
    cout << "result: " << result << endl;
}


int main() 
{
    // string vmSize = getVmSize("8397");
    // cout << "vmsize: " << vmSize << endl;

    getNumberOfCores();
    getOSName();
    test_lambda();
    return 0;
}
