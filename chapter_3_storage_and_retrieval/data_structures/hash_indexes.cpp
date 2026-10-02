// "#include" is a preprocessor directive that tells the compiler to include the standard Input/Output stream library in my program.
// the "<>" angle brackets tell the compiler to look for the file within the standard system directories and not my local project folder.
#include <iostream> 
#include <string>
#include <fstream>
#include <unordered_map>

// using namespace std; // This is adding the "std" namespace to the list of namespaces that the compiler searches for names in. We are currently in the global namespace.

std::string get(std::string data) {
    std::string msg = "You are in the 'get' function.\nYou provided the following data:" + data;
    std::cout << msg;
    return msg;
}

int put(std::string filename, std::string key, std::string value) {
    std::ofstream file; // Stream that we will write the data to. Output streams go like: Stream buffer (RAM) -> flush -> OS -> file/terminal/network/etc

    // Input streams go like: OS -> buffer (RAM) -> flush -> RAM(variable in different location)
    file.open(filename, std::ofstream::app | std::ofstream::binary);

    // Getting position before write, since it will tell us where the value that we are searching for begins.
    int position = file.tellp();
    file.write(value.c_str(), value.size()); // data.c_str gives a pointer to an array that contains a null-terminated sequence of characters.

    file.flush();
    file.close();

    return position;
}

// Used to rebuild the index on startup.
void rebuild_index() {
}

int main() {
    std::unordered_map<std::string, int> index; // Represents the index in RAM.
    std::unordered_map<std::string, std::string> u = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"}
    };


//    std::string data;
//    std::getline(std::cin, data);
//    int position_end = put("test.log", data);
//
//    std::cout << "Position after write is: " << position_end;

//    std::cout << "ofstream app: " << std::ofstream::app;
//    std::cout << "\nofstream binary: " << std::ofstream::binary;
//
//    int result = std::ofstream::app | std::ofstream::binary;
//    std::cout << "\nbitwise OR: " << result;


    // std::string ex = get(data);
    return 0;
}

