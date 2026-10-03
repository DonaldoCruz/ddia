// "#include" is a preprocessor directive that tells the compiler to include the standard Input/Output stream library in my program.
// the "<>" angle brackets tell the compiler to look for the file within the standard system directories and not my local project folder.
#include <iostream> 
#include <string>
#include <fstream>
#include <unordered_map>
#include <typeinfo>

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

    uint32_t key_size = key.size();
    uint32_t value_size = value.size();

    // 1. writing key_size as raw binary bytes
    file.write(reinterpret_cast<char*>(&key_size), sizeof(key_size));

    // 2. writing value_size as raw binary bytes
    file.write(reinterpret_cast<char*>(&value_size), sizeof(value_size));

    // 3. writing actual key bytes
    file.write(key.c_str(), key.size());

    // 4. write the actual value bytes
    file.write(value.c_str(), value.size()); // data.c_str gives a pointer to an array that contains a null-terminated sequence of characters.

    file.flush();
    file.close();

    return position;
}

// Used to rebuild the index on startup.
void rebuild_index() {
}

int main() {
    std::hash<std::string> key_hasher;
    std::unordered_map<std::string, int> index; // Represents the index in RAM.
    //
    // Making a lambda function that will allow us to print the contents of a map.
    auto print_key_values = [](const auto& key, const auto& value) {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

    std::string key;
    std::cout << "Enter key: ";
    std::getline(std::cin, key);
    std::cout << std::endl;

    std::string data;
    std::getline(std::cin, data);
    int position = put("test.log", key, data);

    std::cout << "Position before write is: " << position << std::endl;
    index[key] = position;

    for (const auto& [index_key, index_value] : index) {
        print_key_values(index_key, index_value);
    }
    

//    std::cout << "ofstream app: " << std::ofstream::app;
//    std::cout << "\nofstream binary: " << std::ofstream::binary;
//
//    int result = std::ofstream::app | std::ofstream::binary;
//    std::cout << "\nbitwise OR: " << result;


    // std::string ex = get(data);
    return 0;
}

