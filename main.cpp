#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
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
              << "        <key>  the encription key."
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

int main(int argc, char** argv) {
    if (argc < 4) 
    {
        printUsageInfo();
        return 0;
    }
    
    Mode mode = getModeFromArguments(argv[1]);
    
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
    
    std::istringstream ss(argv[2]);
    uint32_t cipher_key;
    ss >> std::hex;
    ss >> cipher_key;
    
    if (ss.fail())
    {
        std::cerr << "ERROR: \""
                  << argv[2] 
                  << "\" is not an integer." 
                  << std::endl; 
    } 
    else
    {
        std::cout << cipher_key << std::endl;
    }
    
    return 0;
}

