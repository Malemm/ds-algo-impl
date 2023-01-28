#include <iostream>

using namespace std;

struct node
{
    int key;
    node *leftChild;
    node *rightChild;
};

class BinarySearchTree
{
private:
    struct node *root;
    struct node *deleteKey(struct node *, int);
    struct node *insertKey(struct node *, int);
    struct node *findNextInOrder(struct node *);
    void traverseInOrder(struct node *);

public:
    void insertKey(int);
    void deleteKey(int);
    void printInOrder();
    BinarySearchTree();
};

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

struct node *BinarySearchTree::findNextInOrder(struct node *ptr)
{
    struct node *current = ptr;
    while (current && current->leftChild != nullptr)
    {
        current = current->leftChild;
    }
    return current;
}

// recursive method to find the key and delete
// https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
struct node *BinarySearchTree::deleteKey(struct node *ptr, int key)
{
    // base case
    if (ptr == nullptr)
    {
        return ptr;
    }

    // key is smaller, go to the left subtree
    if (key < ptr->key)
    {
        ptr->leftChild = deleteKey(ptr->leftChild, key);
    }
    // key is larger, go to the right subtree
    else if (key > ptr->key)
    {
        ptr->rightChild = deleteKey(ptr->rightChild, key);
    }
    // key is found in this node
    else
    {
        // node does not have a child, simply delete it
        if (ptr->leftChild == nullptr && ptr->rightChild == nullptr)
        {
            delete ptr;
            return nullptr;
        }
        // node only has left child
        else if (ptr->leftChild == nullptr)
        {
            struct node *temp = ptr->rightChild;
            delete ptr;
            return temp;
        }
        // node only has right child
        else if (ptr->rightChild == nullptr)
        {
            struct node *temp = ptr->leftChild;
            delete ptr;
            return temp;
        }
        // node has both left and right children
        else
        {
            // get the inorder successor which is the smaller in the right subtree
            struct node *temp = findNextInOrder(ptr->rightChild);
            ptr->key = temp->key;
            // delete the inorder successor
            ptr->rightChild = deleteKey(ptr->rightChild, temp->key);
        }
    }

    // return the unchanged pointer
    return ptr;
}

void BinarySearchTree::deleteKey(int key)
{
    root = deleteKey(root, key);
}

// recursive method to insert the key as a leaf node
struct node *BinarySearchTree::insertKey(struct node *ptr, int key)
{
    // base case
    if (ptr == nullptr)
    {
        ptr = new node;
        ptr->key = key;
        ptr->leftChild = nullptr;
        ptr->rightChild = nullptr;
        return ptr;
    }

    if (key < ptr->key)
    {
        ptr->leftChild = insertKey(ptr->leftChild, key);
    }
    else
    {
        ptr->rightChild = insertKey(ptr->rightChild, key);
    }

    // return the unchanged pointer
    return ptr;
}

void BinarySearchTree::insertKey(int key)
{
    if (root == nullptr)
    {
        root = new node;
        root->key = key;
        root->leftChild = nullptr;
        root->rightChild = nullptr;
        return;
    }

    this->insertKey(root, key);
}

void BinarySearchTree::traverseInOrder(struct node *ptr)
{
    // base case
    if (ptr == nullptr)
    {
        return;
    }
    traverseInOrder(ptr->leftChild);
    cout << ptr->key << "  ";
    traverseInOrder(ptr->rightChild);
}

void BinarySearchTree::printInOrder()
{
    cout << "In order traversal: ";
    traverseInOrder(root);
    cout << endl;
}

main()
{
    BinarySearchTree bst;

    int ops = 0;
    int key;
    while (true)
    {
        cout << "1 = insert; 2 = delete; 3 = exit program" << endl;
        cin >> ops;
        switch (ops)
        {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            bst.insertKey(key);
            bst.printInOrder();
            break;

        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            bst.deleteKey(key);
            bst.printInOrder();
            break;

        case 3:
            return 0;

        default:
            cout << "Invalid input!" << endl;
        }
    }
}