#include <iostream>
#include <string>
//#include "HashMap.hpp"
#include "HashMap.cpp"

using namespace std;

string *inputNewKeyValuePair();
string inputKey();

int main()
{
    std::cout << "~HashMap Implementation~" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;
    std::cout << std::endl;

    HashMap hashmap;

    while (true)
    {
        int operation;
        std::cout << "Enter 1 to add key-value pair; enter 2 to get the 'value' of a 'key'" << std::endl;
        std::cin >> operation;

        if (operation == 1) // add key-value pair
        {
            string *inputAddr = inputNewKeyValuePair();
            string key = *inputAddr;
            string value = *(inputAddr + 1);

            hashmap.add(key, value);
        }
        else if (operation == 2) // get the value of a given key
        {
            string key = inputKey();
            string value = hashmap.getValue(key);
            std::cout << "value: " + value << std::endl;
        }
        else
        {
            std::cout << "Invalid input!" << std::endl;
        }
    }
}

string *inputNewKeyValuePair()
{
    static string input[2];
    std::cout << "Add key[string]-value[string] pair" << std::endl;
    std::cout << "key[string]: ";
    std::cin >> input[0];
    std::cout << std::endl;
    std::cout << "value[string]: ";
    std::cin >> input[1];
    std::cout << std::endl;

    return input;
}

string inputKey()
{
    string key;
    std::cout << "key[string]: ";
    std::cin >> key;
    std::cout << std::endl;

    return key;
}