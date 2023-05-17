#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq){
        this -> left = this -> right = NULL;
        this -> data = data;
        this -> freq = freq;
    }
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    // Array of minheap node pointers
    MinHeapNode** array;

    MinHeap(unsigned capacity){
        this -> size = 0;
        this -> array = new MinHeapNode*;
        this -> capacity = capacity;
    }
};

void minHeapify(MinHeap* minHeap, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx){
        swap(minHeap->array[smallest], minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap){
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap,MinHeapNode* minHeapNode){
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void printArr(int arr[], int n){
    for (int i = 0; i < n; ++i)
        cout << arr[i];
    cout << "\n";
}

MinHeap* createAndBuildMinHeap(char data[],int freq[], int size){
    MinHeap* minHeap = new MinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = new MinHeapNode(data[i], freq[i]);
    minHeap-> size = size;
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

MinHeapNode* buildHuffmanTree(char data[],int freq[], int size){
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1){
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[],int top){
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        cout << root->data << ": ";
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size){
    // Construct Huffman Tree
    MinHeapNode* root = buildHuffmanTree(data, freq, size);
    // Print Huffman codes using the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

int main(){
    char arr[] = { 'a', 'b', 'c','d','e'};
    int freq[] = {  4,   2,   2,  1,  1};
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
