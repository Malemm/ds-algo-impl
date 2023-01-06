#include <iostream>
#include <string>
// #include "HashMap.hpp"
#include "HashMap.cpp"

using namespace std;

string *inputNewKeyValuePair();
string inputKey();

int main()
{
    std::cout << "~ HashMap Implementation ~" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;

    HashMap hashmap;

    while (true)
    {
        int operation;
        std::cout << std::endl
                  << "Enter 1 to add key-value pair" << endl << "Enter 2 to display the 'value' of a 'key'" << std::endl;
        scanf("%d", &operation);
        while ((getchar()) != '\n');

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
            std::cout << std::endl
                      << "value: " << value;
        }
        else
        {
            std::cout << std::endl
                      << "Invalid input!";
        }

        std::cout << std::endl;
    }
}

string *inputNewKeyValuePair()
{
    static string input[2];
    std::cout << std::endl
              << "Enter key-value pair" << std::endl;
    std::cout << "key[string]: ";
    std::cin >> input[0];
    std::cout << "value[string]: ";
    std::cin >> input[1];

    return input;
}

string inputKey()
{
    string key;
    std::cout << "key[string]: ";
    std::cin >> key;

    return key;
}