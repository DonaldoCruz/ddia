// "#include" is a preprocessor directive that tells the compiler to include the standard Input/Output stream library in my program.
// the "<>" angle brackets tell the compiler to look for the file within the standard system directories and not my local project folder.
#include <iostream> 
#include <string>

// using namespace std; // This is adding the "std" namespace to the list of namespaces that the compiler searches for names in. We are currently in the global namespace.

std::string get(std::string data) {
    std::string msg = "You are in the 'get' function.\nYou provided the following data:" + data;
    std::cout << msg;
    return msg;
}

int main() {
    std::string data;
    std::cin >> data;

    std::string ex = get(data);
    std::cout << "get function output:" + ex;
    return 0;
}

