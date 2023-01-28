#include <iostream>
#include <cmath>

using namespace std;

class MinHeap
{
private:
    static const int MAXSIZE = 1000;
    static const int ROOT = 1;
    int size = 0;
    int heap[MAXSIZE];

    int parent(int);
    void swap(int, int);
    int leftChild(int);
    int rightChild(int);
    void minHeapify();

public:
    void insert(int value);
    int extractMin();
    void printTree();
};

int MinHeap::parent(int index)
{
    if (index == ROOT)
    {
        return ROOT;
    }
    return index / 2;
}

void MinHeap::swap(int x, int y)
{
    int temp = heap[x];
    heap[x] = heap[y];
    heap[y] = temp;
}

int MinHeap::leftChild(int index)
{
    return index * 2;
}

int MinHeap::rightChild(int index)
{
    return index * 2 + 1;
}

void MinHeap::minHeapify()
{
    int offset = 0;

    for (int index = ROOT; index < size; index = leftChild(index) + offset)
    {
        if (rightChild(index) <= size) // right child exists
        {
            if (heap[leftChild(index)] < heap[rightChild(index)])
            {
                swap(index, leftChild(index));
                offset = 0; // to follow the left child in next iteration
            }
            else if (heap[index] > heap[rightChild(index)])
            {
                swap(index, rightChild(index));
                offset = 1; // to follow the right child in next iteration
            }
            else
            {
                break;
            }
        }
        else if (leftChild(index) <= size) // only left child exists
        {
            if (heap[index] > heap[leftChild(index)])
            {
                swap(index, leftChild(index));
                offset = 0;
            }
            else
            {
                break;
            }
        }
        else // no children exists
        {
            break;
        }
    }
}

void MinHeap::insert(int value)
{
    if (size >= MAXSIZE)
    {
        cout << "Error: heap is full." << endl;
        return;
    }

    heap[++size] = value;

    int current = size;
    while (heap[current] < heap[parent(current)])
    {
        swap(current, parent(current));
        current = parent(current);
    }
}

int MinHeap::extractMin()
{
    if (size == 0)
    {
        cout << "Error: heap is empty." << endl;
        return -1;
    }

    int min = heap[ROOT];
    heap[ROOT] = heap[size--];
    minHeapify();
    return min;
}

void MinHeap::printTree()
{
    int whitespace = 2;
    int parser = 1;
    int totalLevel = floor(log2(size)) + 1;
    cout << endl;
    for (int level = 1; level <= totalLevel; level++)
    {
        int whitespaceLen;
        if (level == 1)
        {
            whitespaceLen = totalLevel * 2;
        }
        else if (level == totalLevel)
        {
            whitespaceLen = 1;
        }
        else
        {
            whitespaceLen = (totalLevel - level) * 2;
        }

        for (int i = 0; i < whitespace - 1; i++)
        {

            for (int w = 0; w < whitespaceLen; w++)
            {
                cout << " ";
            }
            if (parser <= size)
            {
                cout << heap[parser++];
            }
        }

        whitespace = whitespace * 2 - 1;
        cout << endl;
    }
    cout << endl;
}

int main()
{
    MinHeap minHeap;

    minHeap.insert(8);
    minHeap.insert(7);
    minHeap.insert(6);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(1);
    minHeap.insert(8);
    minHeap.insert(7);
    minHeap.insert(6);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(1);
    minHeap.insert(8);
    minHeap.insert(7);
    minHeap.insert(6);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(1);
    minHeap.printTree();

    int ops = 0;
    while (true)
    {
        cout << "1 = insert; 2 = extract min; 3 = exit program" << endl;
        cin >> ops;
        switch (ops)
        {
        case 1:
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            minHeap.insert(value);
            minHeap.printTree();
            break;

        case 2:
            value = minHeap.extractMin();
            cout << "Extracted Value: " << value << endl;
            minHeap.printTree();
            break;

        case 3:
            return 0;

        default:
            cout << "Invalid input!" << endl;
        }
    }
}
