#include <iostream>
#include "node.hpp"
#include "list.hpp"

using namespace std;

class Doubly : public List {
private:
    Node* head;
    Node* tail;
    int size;

    void addBetween(Node* curr, Node* node) {
        node->next = curr;
        node->prev = curr->prev;
        curr->prev->next = node;
        curr->prev = node;
    }


    int removeBetween(Node* curr) {
        int elem = curr->val;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        return elem;
    }


    Node* traverseTail(int pos) {
        Node* curr = tail;
        pos = size - (pos - 1);
        while(--pos) {
            curr = curr->prev;
        }
        return curr;
    }


    Node* traverseHead(int pos) {
        Node* curr = head;
        while(--pos) {
            curr = curr->next;
        }
        return curr;
    }


public:
    Doubly() : size(0), head(nullptr), tail(nullptr) {}

    void addHead(int num) {
        Node* node = new Node(num);
        if(head == nullptr) {
            head = node;
            tail = node;
            size++;
            return;
        }

        node->next = head;
        head->prev = node;
        head = node;
        size++;
    }


    void addTail(int num) {
        Node* node = new Node(num);
        if(tail == nullptr) {
            head = node;
            tail = node;
            size++;
            return;
        }

        tail->next = node;
        node->prev = tail;
        tail = node;
        size++;
    }


    int removeHead() {
        if(head == nullptr) {
            return -1;
        } 
        
        int elem = head->val;

        if(head == tail) {
            delete head;
            head = tail = nullptr;
            size--;
            return elem;
        } 

        Node* temp = head;
        head = head->next;
        delete temp;
        head->prev = nullptr;
        size--;
        return elem;
    }


    int removeTail() {
        if(tail == nullptr) {
            return -1;
        }

        int elem = tail->val;
        if(tail == head) {
            delete tail;
            tail = head = nullptr;
            size--;
            return elem;
        }

        Node* temp = tail;
        tail = tail->prev;
        delete temp;
        tail->next = nullptr;
        size--;
        return elem;
    }


    void addAt(int num, int pos) {
        if(pos < 1 || pos > size + 1) return;

        if(pos == 1) {
            cout << "From Head: " << endl;
            addHead(num);
            return;
        }
        
        if(pos == size + 1) {
            cout << "From Tail: " << endl;
            addTail(num);
            return;
        }

        Node* node = new Node(num);
        Node* curr = nullptr;

        if(pos <= size / 2) {
            cout << "From Head: " << endl;
            curr = traverseHead(pos);
        } else {
            cout << "From Tail: " << endl;
            curr = traverseTail(pos);
        }

        addBetween(curr, node);
        size++;
    }


    int removeAt(int pos) {
        if(size == 0 || pos < 1 || pos > size) return -1;

        if(pos == 1) {
            cout << "From Head: ";
            return removeHead();
        }

        if(pos == size) {
            cout << "From Tail: ";
            return removeTail();
        }

        Node* curr = nullptr;

        if(pos <= size / 2) {
            cout << "From Head: ";
            curr = traverseHead(pos);
        } else {
            cout << "From Tail: ";
            curr = traverseTail(pos);
        }

        size--;
        return removeBetween(curr);
    }


    int removeAll(int num) {
        if(size == 0) return -1;

        int count = 0;
        Node* curr = head;
        
        while(curr) {
            if(curr->val == num) {
                count++;
                if(curr == head) {
                    removeHead();
                    curr = head;
                } else if(curr == tail) {
                    removeTail();
                    curr = nullptr;
                } else {
                    Node* temp = curr;
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr = curr->next;
                    delete temp;
                    size--;
                }
            } else {
                curr = curr->next;
            }
        }
        return count;
    }


    int get(int pos) {
        if(pos < 1 || pos > size) return -1;

        Node* curr = head;
        
        int mid = 0;
        if(size % 2 == 0) {
            mid = size / 2;
        } else {
            mid = size / 2 + 1;
        }

        int countPos = 1;
        int ret;

        if(pos <= mid) {
            Node* curr = head;
            while(--pos) {
                curr = curr->next;
                countPos++;
            }
            cout << "From Head, number of comparisons: " << countPos << endl;
            return curr->val;
        } else {
            Node* curr = tail;
            pos = size - (pos - 1);
            while(--pos) {
                curr = curr->prev;
                countPos++;
            }
            cout << "From Tail, number of comparisons: " << countPos << endl;
            return curr->val;
        }
    }


    // No need to free or delete the removed nodes here <3
    int retain(int num) {
        if(size == 0) return -1;

        int count = 0;
        Node* curr = head;

        while(curr) {
            if(curr->val < num) {
                count++;
                if(curr == head) {
                    head = head->next;
                    head->prev = nullptr;
                    curr = head;
                } else if(curr == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                    curr = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr = curr->next;
                }
                size--;
            } else {
                curr = curr->next;
            }
        }
        return count;
    }


    int corner(int left, int right) {
        if(left < 0 || left > size || right < 0 || right > size) return -1;

        if(left == 0 && right == 0) return 0;
        
        int ret = size - (left + right);
        size = left + right;

        Node* currLeft = head;
        while(--left) {
            currLeft = currLeft->next;
        }

        Node* currRight = tail;
        while(--right) {
            currRight = currRight->prev;
        }
        currLeft->next = currRight;
        currRight->prev = currLeft;

        return ret;
    }


    void reverse() {
        if(size == 0 || size == 1) return;

        Node* prev = head, *curr = head->next;

        prev->next = nullptr;
        prev->prev = curr;

        tail = head;
        while(curr) {
            curr->prev = curr->next;
            curr->next = prev;
            prev = curr;
            curr = curr->prev;
        }
        head = prev;
    }


    void print() {
        Node* curr = head;

        cout << "Size: " << size << endl;
        cout << "From HEAD: ";

        while(curr) {
            cout << curr->val;
            if(curr->next != nullptr) {
                cout << " -> ";
            }
            curr = curr->next;
        }
        cout << endl;

        cout << "From TAIL: ";
        curr = tail;

        while(curr) {
            cout << curr->val;
            if(curr->prev != nullptr) {
                cout << " <- ";
            }
            curr = curr->prev;
        }
        cout << endl;
    }
};