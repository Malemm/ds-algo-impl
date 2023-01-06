#include <iostream>
#include <string>
#include "HashMap.hpp"

HashMap::HashMap()
{
    std::cout << std::endl
              << "HashMap instantiated with hash space size: " << HASH_SPACE_SIZE;
}

void HashMap::add(std::string key, std::string value)
{
    std::cout << "HashMap::add -> "
                 "key: "
              << key << "; value: " << value;

    int index = getIndex(key);
    linkedListNode *head = linkedListNodeArray[index];

    if (head)
    {
        linkedListNode *iterator = head;
        linkedListNode *previous = head;
        // find the node containing the key; if found, overwrite the corresponding value
        while (iterator)
        {
            if (iterator->key == key)
            {
                iterator->value = value;
                return;
            }
            previous = iterator;
            iterator = iterator->next;
        }

        // insert new node
        previous->next = createNewNode(key, value);
    }
    else
    {
        // insert head
        linkedListNodeArray[index] = createNewNode(key, value);
    }
}

std::string HashMap::getValue(std::string key)
{
    std::string value;
    std::cout << "HashMap::getValue -> "
                 "key: "
              << key;

    int index = getIndex(key);
    linkedListNode *head = linkedListNodeArray[index];

    // find the node containing the key and return the value
    while (head)
    {
        if (head->key == key)
        {
            return head->value;
        }
        head = head->next;
    }

    return "";
}

int HashMap::getIndex(std::string key)
{
    unsigned int index = 1;
    for (int i = 0; i < key.length(); i++)
    {
        char element = (char)key[i];
        index *= (int)element;
    }
    index %= HASH_SPACE_SIZE;
    return index;
}

HashMap::linkedListNode *HashMap::createNewNode(std::string key, std::string value)
{
    // create a new node to store the key value pair
    HashMap::linkedListNode *newNode = new HashMap::linkedListNode;
    (*newNode).key = key;
    (*newNode).value = value;
    (*newNode).next = NULL;
    return newNode;
}
