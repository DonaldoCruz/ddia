// "#include" is a preprocessor directive that tells the compiler to include the standard Input/Output stream library in my program.
// the "<>" angle brackets tell the compiler to look for the file within the standard system directories and not my local project folder.
#include <iostream> 
#include <string>
#include <fstream>
#include <unordered_map>
#include <typeinfo>

// using namespace std; // This is adding the "std" namespace to the list of namespaces that the compiler searches for names in. We are currently in the global namespace.

char* get(std::string filename, std::string key, std::unordered_map<std::string, int> index) {
    // Declaring variables
    std::streampos position; 
    uint32_t key_size;
    uint32_t value_size;
    char* value = new char();

    // step 0: Open file in input mode.
    std::ifstream file;
    file.open(filename);

    // Step 1: In the hash index, find the key, it returns the position in the file
    position = index[key];
    std::cout << "Position for key: " << position << std::endl;

    // Step 2: Go to that position in the file
    file.seekg(position);

    // step 3: read 4 bytes, gives you key size, read 4 more bytes, it gives you the value size
    file.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));
    std::cout << "Key size Value (bytes): " << key_size << std::endl;
    
    // step 4: move past key size position onto the beginning of value size..
    file.read(reinterpret_cast<char*>(&value_size), sizeof(value_size));
    std::cout << "Value size Value (bytes): " << value_size << std::endl;

    // step 5: move past key value
    file.seekg(key_size, std::ios_base::cur);

    // step 6: Move past key
    file.read(value, value_size);
    std::cout << "value inside get: " << value << std::endl;

    return value;
}
std::streampos put(std::string filename, std::string key, std::string value) {
    std::ofstream file; // Stream that we will write the data to. Output streams go like: Stream buffer (RAM) -> flush -> OS -> file/terminal/network/etc
    // Input streams go like: OS -> buffer (RAM) -> flush -> RAM(variable in different location)
    file.open(filename, std::ofstream::app | std::ofstream::binary);

    // Getting position before write, since it will tell us where the value that we are searching for begins.
    std::streampos position = file.tellp();

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
std::unordered_map<std::string, std::streampos> rebuild_index(std::string file_name) {
    std::ifstream file;
    std::streampos current_position;
    std::streampos end_position;
    std::unordered_map<std::string, std::streampos> index;

    // Opening file.
    file.open(file_name);

    // Getting last position.
    file.seekg(0, std::ios_base::end);
    end_position = file.tellg();
    std::cout << "end position: " << end_position << std::endl;
    
    // Going to beginning position
    file.seekg(0, std::ios_base::beg);
    

    // The order is [key_size(4 bytes, unsigned 32 bit int)][value_size(4 bytes, unsigned 32 bit int)][key_value][value]

    for (std::streampos position = file.tellg(); position != end_position; position = file.tellg()) {
        uint32_t key_size;
        uint32_t value_size;

        file.read(reinterpret_cast<char*>(&key_size), sizeof(uint32_t));
        file.read(reinterpret_cast<char*>(&value_size), sizeof(uint32_t));
        
        // Get actual key.
        std::string key (key_size, '\0');
        file.read(key.data(), key_size);
        std::cout << "Key size: " << key_size << ", Key Value:" << key << std::endl;
        std::cout << "Value size: " << value_size << std::endl;

        // Skip value
        file.seekg(value_size, std::ios_base::cur);

        // Populate index.
        index[key] = position;
        std::cout << "Key: " << key << ", Position: " << position << std::endl; 

    }
    
    return index;
    


}

int main() {
    std::unordered_map<std::string, int> index; // Represents the index in RAM.

    // Making a lambda function that will allow us to print the contents of a map.
    auto print_key_values = [](const auto& key, const auto& value) {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

//    std::string key;
//    std::cout << "Enter key: ";
//    std::getline(std::cin, key);
//    std::cout << std::endl;
//
//    std::string data;
//    std::getline(std::cin, data);
//    int position = put("test.log", key, data);
//
//    std::cout << "Position before write is: " << position << std::endl;
//    index[key] = position;
//
//    for (const auto& [index_key, index_value] : index) {
//        print_key_values(index_key, index_value);
//    }
//
//    /* Retrieval portion*/
//
//    char* my_value = get("test.log", key, index);
//    std::cout << "My Final value, index Finished: " << my_value << std::endl;
//    
//    delete my_value;
//    std::cout << "value should be garbage: " << my_value << std::endl;

    std::unordered_map<std::string, std::streampos> new_index = rebuild_index("test.log");
    for (const auto& [index_key, index_value] : new_index) {
       print_key_values(index_key, index_value);
    }
    return 0;
}

