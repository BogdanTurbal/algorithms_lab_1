#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Node {
public:
    int value;
    Node* next;

    // constructor: 2 operations (assignment, nullptr assignment)
    Node(int value) : value(value), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    // 1 op
    LinkedList() : head(nullptr) {}

    // Append: if first => 4, else 105 operations (due to the while loop for traversal)
    void append(int value) {
        if (!head) { // 1 operation
            head = new Node(value); // 3 operations
        } else {
            Node* current = head; // 1 operation
            // traversal: average case for traversal is roughly 50 operations,
            // with each iteration counting as 1 for the check and 1 for the assignment,
            // => 100
            while (current->next) {
                current = current->next;
            }
            current->next = new Node(value); // 3 ops
        }
    }

    // getChainLength: 151 operations
    int getChainLength() {
        Node* current = head; // 1 operation
        int length = 0; // 1 operation
        while (current) { // average 51 operations
            length += 1; // 50 operations
            current = current->next; // 50 operations
        }
        return length; // 1 operation
    }
};

// initializeHashTable: N / 100 operations
vector<LinkedList*> initializeHashTable(int size) {
    return vector<LinkedList*>(size, nullptr); // N / 100 operations
}

// insertIntoHashTable: 105 operations
void insertIntoHashTable(vector<LinkedList*>& hashTable, int key, int value) {
    if (!hashTable[key]) { // 1 operation
        hashTable[key] = new LinkedList(); // 2 operations
    }
    hashTable[key]->append(value); // if first then 4, else 105 operations
}

tuple<int, int, double> measureChainsAndTime(int N) { //
    int tableSize = N / 100; // 1 operation
    auto hashTable = initializeHashTable(tableSize); // 105 operations

    clock_t startTime = clock(); // 1 operation

    srand((unsigned)time(nullptr)); // 1

    for (int i = 0; i < N; ++i) { // N + 1 operations for loop check
        int randomNumber = rand() % (N * 10); // N operations
        int key = randomNumber % tableSize; // N operations
        insertIntoHashTable(hashTable, key, randomNumber); // N * 105 operations
    }

    int longestChain = 0; // 1 operation
    int shortestChain = N; // 1 operation
    for (int i = 0; i < tableSize; ++i) { // N / 100 + 1 operations for loop check
        int chainLength = hashTable[i] ? hashTable[i]->getChainLength() : 0; // 151 * N / 100 operations
        if (chainLength > longestChain) longestChain = chainLength; // N / 100 operations
        if (chainLength < shortestChain) shortestChain = chainLength; // N / 100 operations
    }

    double executionTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC; // 1 operation

    return {longestChain, shortestChain, executionTime}; // 1 operation
}

int f_a(int n){
    return int(110 * n + 109);
}
int main() {
    int Ns[] = {1000, 10000, 100000, 1000000};

    for (int N : Ns) {
        auto [longestChain, shortestChain, executionTime] = measureChainsAndTime(N);
        cout << "N = " << N << ": Longest Chain: " << longestChain << ", Shortest Chain: " << shortestChain << ", Execution Time: " << executionTime << " seconds" << endl;
        // Additional operations for output not explicitly counted
        int num_ops = f_a(N);
        cout << "Time per operation: " << executionTime / num_ops << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
