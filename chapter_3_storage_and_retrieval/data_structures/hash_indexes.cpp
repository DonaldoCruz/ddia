// "#include" is a preprocessor directive that tells the compiler to include the standard Input/Output stream library in my program.
// the "<>" angle brackets tell the compiler to look for the file within the standard system directories and not my local project folder.
#include <iostream> 
#include <string>
#include <fstream>

// using namespace std; // This is adding the "std" namespace to the list of namespaces that the compiler searches for names in. We are currently in the global namespace.

std::string get(std::string data) {
    std::string msg = "You are in the 'get' function.\nYou provided the following data:" + data;
    std::cout << msg;
    return msg;
}

void put(std::string filename, std::string data) {
    std::ofstream file; // Stream that we will write the data to. Output streams go like: Stream buffer (RAM) -> flush -> OS -> file/terminal/network/etc
    // Input streams go like: OS -> buffer (RAM) -> flush -> RAM(variable in different location)
    file.open(filename);
    file.write(data.c_str(), data.size()); // data.c_str gives a pointer to an array that contains a null-terminated sequence of characters.
    file.flush();
    file.close();
}

int main() {
    std::string data;
    std::cin >> data;
    put("test.txt", data);

    std::string ex = get(data);
    return 0;
}

