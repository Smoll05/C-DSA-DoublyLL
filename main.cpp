#include <iostream>
#include "doubly.cpp"

using namespace std;

int main() {
    List* list = new Doubly();

    char op;
    int value, pos, element, result;

    do {
        cout << "Op: ";
        cin >> op;

        switch(op) {
            case 'a':   
                cin >> value;
                list->addHead(value);
                break;

            case 'A':
                list->removeHead();
                break;
            
            case 't':
                cin >> value;
                list->addTail(value);
                break;

            case 'T':
                list->removeTail();

            case '@':
                cin >> value;
                cin >> pos;
                list->addAt(value, pos);
                break;

            case '#':
                cin >> pos;
                cout << "Removed Element - " << list->removeAt(pos) << endl;
                break;

            case '$':
                cin >> value;
                cout << "Number of Elements Removed: " << list->removeAll(value) << endl;
                break;

            case 'g':
                cin >> pos;
                element = list->get(pos);
                if(element != -1) {
                    cout << "Element at position " << pos << " is " << element << endl;
                } else {
                    cout << "Invalid Postion" << endl;
                }
                break;

            case 'r':
                cin >> value;
                cout << "Number of elements less than " << value << " removed: " << list->retain(value) << endl;
                break;

            case 'c':
                cin >> value;
                cin >> pos;
                result = list->corner(value, pos);
                if(result != -1) {
                    cout << "Removed " << result << " element/s" << endl;
                } else {
                    cout << "Invalid input" << endl;
                }
                break;

            case '~':
                list->reverse();
                break;

            case 'p':
                list->print();
                break;

            case 'x':
                cout << "Exiting..." << endl;
                break;

            default:
                break;
        }
    } while(op != 'x');
}