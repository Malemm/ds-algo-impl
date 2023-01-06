#define HASH_SPACE_SIZE 10

class HashMap
{
public:
    HashMap();
    void add(std::string, std::string);
    std::string getValue(std::string);

private:
    struct linkedListNode
    {
        std::string key;
        std::string value;
        linkedListNode *next;
    };

    linkedListNode* linkedListNodeArray[HASH_SPACE_SIZE] = {NULL};

    int getIndex(std::string);
    linkedListNode* createNewNode(std::string, std::string);
};