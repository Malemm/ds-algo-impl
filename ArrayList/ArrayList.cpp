#include <iostream>
#include <string>
#include <limits>
#include <math.h>

using namespace std;

int *inputInsertAtIndex();
int inputAppend();

class ArrayList
{
private:
    int *dynamicArray;
    int contentLength = 0;
    int actualLength = 1;

    int *doubleArraySize(int);

public:
    int add(int value, int index);
    int append(int value);
    int length();
    void printContent(); // @TODO make this iterable instead
};

int ArrayList::add(int value, int index)
{
    if (index < 0 || index > contentLength)
    {
        return 4; // error
    }

    // if it is going to be full with this new addition, expand the array to double its size
    if (contentLength + 1 == actualLength)
    {
        int *newArray = doubleArraySize(actualLength * 2);
        if (!newArray)
        {
            return 4; // cannot expand array further
        }

        for (int i = contentLength; i >= 0; i--) // i>=0 to covers the case when index=0
        {
            if (i == index)
            {
                *(newArray + i) = value;
                break;
            }
            else
            {
                // shift the proceeding elements to right by one
                *(newArray + i) = *(dynamicArray + (i - 1));
            }
        }

        for (int i = 0; i < index; i++)
        {
            // copy the prceeding elements to the new array
            *(newArray + i) = *(dynamicArray + i);
        }

        delete dynamicArray;
        dynamicArray = newArray;
        actualLength *= 2;
        contentLength += 1;

        return 0;
    }

    for (int i = contentLength; i >= 0; i--) // i>=0 to covers the case when index=0
    {
        if (i == index)
        {
            *(dynamicArray + i) = value;
            break;
        }
        else
        {
            // shift the proceeding elements to the right by one
            *(dynamicArray + i) = *(dynamicArray + (i - 1));
        }
    }
    contentLength += 1;

    return 0;
}

int ArrayList::append(int value)
{
    // expand the array to double its size if it is going to be full with this new addition
    if (contentLength + 1 >= actualLength)
    {
        int *newArray = doubleArraySize(actualLength * 2);
        if (!newArray)
        {
            return 4; // cannot expand array further
        }

        for (int i = 0; i < contentLength; i++)
        {
            // copy the elements to the new array
            *(newArray + i) = *(dynamicArray + i);
        }

        // append the new element
        *(newArray + contentLength) = value;

        delete dynamicArray;
        dynamicArray = newArray;
        actualLength *= 2;
        contentLength += 1;

        return 0;
    }

    // append the new element
    *(dynamicArray + contentLength) = value;
    contentLength += 1;

    return 0;
}

int *ArrayList::doubleArraySize(int size)
{
    if (size > INT_MAX)
    {
        return NULL;
    }
    return new int[size];
}

int ArrayList::length()
{
    return contentLength;
}

void ArrayList::printContent()
{
    std::cout << endl
              << "[";
    for (int i = 0; i < contentLength; i++)
    {
        if (i == contentLength - 1)
        {
            std::cout << *(dynamicArray + i); // add closing bracket later
        }
        else
        {
            std::cout << *(dynamicArray + i) << ", "; // comma separated
        }
    }
    std::cout << "]" << endl;
    std::cout << "Actual length: " << actualLength << endl;
}

int main()
{
    std::cout << "~ ArrayList Implementation ~" << std::endl;
    std::cout << "Press Ctrl+C to exit" << std::endl;

    ArrayList arrayList;

    while (true)
    {
        int operation;
        std::cout << std::endl
                  << "Enter 1 to append a value to ArrayList" << endl
                  << "Enter 2 to insert a value at a position" << std::endl;
        scanf("%d", &operation);
        while ((getchar()) != '\n')
            ;

        if (operation == 1) // append
        {
            int value = inputAppend();
            int status = arrayList.append(value); // status 0=success, 4=failure
            std::cout << std::endl
                      << "Append " << (status == 0 ? "successful" : "failed");
        }
        else if (operation == 2) // insert in position
        {

            int *inputAddr = inputInsertAtIndex();
            int value = *inputAddr;
            int index = *(inputAddr + 1);
            int status = arrayList.add(value, index);
            std::cout << std::endl
                      << "Add " << (status == 0 ? "successful" : "failed");
        }
        else
        {
            std::cout << std::endl
                      << "Invalid input!";
        }

        std::cout << std::endl
                  << "ArrayList length: " << arrayList.length();
        std::cout << std::endl
                  << "ArrayList content:" << std::endl;
        arrayList.printContent();
    }
}

int *inputInsertAtIndex()
{
    static int input[2];
    std::cout << std::endl
              << "Value[integer]: ";
    std::cin >> input[0];
    std::cout << "Index[integer]: ";
    std::cin >> input[1];

    return input;
}

int inputAppend()
{
    int value;
    std::cout << "Value[integer]: ";
    std::cin >> value;

    return value;
}