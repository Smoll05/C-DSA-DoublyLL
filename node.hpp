struct Node {
    int val;
    Node* next;
    Node* prev;

    Node(int val) : val(val), next(nullptr), prev(nullptr) {}
};