#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class Mode {
    DO_ENCRYPT,
    DO_DECRYPT,
    DO_UNKNOWN,
};


static void printUsageInfo() 
{
    std::cout << "Usage: cipher (-e | -d) <key> FILE1 [FILE2 [...]]" 
              << std::endl
              << "Where   -e     encrypt the files." 
              << std::endl
              << "        -d     decrypt the files."
              << std::endl
              << "        <key>  the encryption/decryption key."
              << std::endl;
}


static Mode getModeFromArguments(char* token)
{
    std::string mode_switch(token);
    
    if (mode_switch == "-e")
    {
        return Mode::DO_ENCRYPT;
    }
    
    if (mode_switch == "-d")
    {
        return Mode::DO_DECRYPT;
    }
    
    return Mode::DO_UNKNOWN;
}

// The precondition of this function is that the value of 'argc' is at least 3.
std::vector<std::string> getFileNames(int argc, char* argv[])
{
    std::vector<std::string> fileNameVector(argc - 3);
    
    for (size_t i = 3; i < argc; ++i) 
    {
        fileNameVector.push_back(std::string(argv[i]));
    }
    
    return fileNameVector;
}

static void throwOnBadKey(std::string token) 
{
    std::stringstream sstream;
    sstream << "Cannot parse \"" 
            << token
            << "\" as a decimal or hexadecimal integer.";

    throw std::runtime_error(sstream.str());
}

uint32_t getCipherKey(char* s) 
{
    std::string str(s);
    std::istringstream ss(str);
    uint32_t key = 0;
    
    if (str.length() >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        ss >> std::hex >> key;
        
        if (ss.fail())
        {
            throwOnBadKey(str);
        }
        
        return key;
    }
    
    ss >> key;
    
    if (!ss.fail())
    {
        throwOnBadKey(str);
    }
    
    return key;
}

int main(int argc, char** argv) {
    if (argc < 4) 
    {
        printUsageInfo();
        return 0;
    }
    
    try {
        Mode mode = getModeFromArguments(argv[1]);
        uint32_t cipher_key = getCipherKey(argv[2]);
        std::vector<std::string> file_name_vector = getFileNames(argc, argv);

        std::cout << "Key: " << cipher_key << std::endl;
        
        switch (mode) 
        {
            case Mode::DO_ENCRYPT:
                std::cout << "Encrypt op" << std::endl;
                break;

            case Mode::DO_DECRYPT:

                std::cout << "Decrypt op" << std::endl;
                break;

            case Mode::DO_UNKNOWN:

                std::cout << "Unknown op" << std::endl;
                break;
        }
        
        for (auto& a : file_name_vector)
        {
            std::cout << a << std::endl;
        }
    }
    catch (std::runtime_error& error)
    {
        std::cerr << "ERROR: " << error.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

