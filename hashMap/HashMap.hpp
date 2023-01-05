#define HASH_SPACE_SIZE 1000

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

    int hashMap[HASH_SPACE_SIZE];
};