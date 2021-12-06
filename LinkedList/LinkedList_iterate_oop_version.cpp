#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int data ;
    Node *next ;
    Node(){};
    Node(int x){
        data = x;
        next = nullptr;
    }
};

class LinkedList {
public:
    Node *head;
    LinkedList();
    LinkedList(Node* head);
    LinkedList(vector<int> arr) ;
    void Print();
    Node* Search(int x);
    void InsertAtFront(int x);
    void Delete(int x);
    ~LinkedList();
};

void test_insert() ;
void test_search() ;
void test_delete() ;

int main()
{
    // LinkedList InsertAtFront works
    //test_insert() ;

    // LinkedList Search works
    // test_search();

    //LinkedList Delete works
    // test_delete();
    return 0 ;
}

// LinkedList implementation
LinkedList::LinkedList() {
    this->head = nullptr;
}

LinkedList::LinkedList(Node* head) {
    this->head = head;
}

LinkedList::LinkedList(vector<int> arr) {
    reverse(arr.begin(), arr.end());
    for(auto i : arr) {
        Node * item = new Node(i);
        if (this->head == nullptr) {
            this->head = item;
            continue ;
        }
        item->next = this->head;
        this->head = item;
    }
}

void LinkedList::InsertAtFront(int x) {
    Node * new_node = new Node(x);
    new_node->next = this->head;
    this->head = new_node;
}

void LinkedList::Print() {
    Node *dummy = this->head;
    while(dummy) {
        cout << dummy->data << ' ';
        dummy = dummy->next;
    }
    cout << endl ;
    return ;
}

Node* LinkedList::Search(int x) {
    if (this->head != nullptr) {
        Node * dummy = this->head;
        while (dummy != nullptr) {
            if (dummy->data == x) {
                cout << "found: " << x << endl;
                return dummy ;
            }
            dummy = dummy->next ;
        }
        return nullptr;
    }
    return nullptr;
}

void LinkedList::Delete(int x) {
    // 1. if the list is empty we do nothing
    if (this->head == nullptr) return ;

    // 2. if the node we want to delete is the first element
    //    change the head of list
    if (this->head->data == x) {
        Node* del = this->head;
        this->head = this->head->next;
        delete del ;
        return ;
    }

    // 3. the node at other place
    //    just go to it's predecessor then let it's predecessor point to it's next node
    Node *dummy = this->head;
    while (dummy->next != nullptr) {
        // we found it's predecessor which is dummy
        if (dummy->next->data == x) {
            Node *del = dummy->next;
            dummy->next = dummy->next->next;
            delete del;
            return ;
        }
        dummy = dummy->next;
    }
    printf("No matching Node!\n");
}

LinkedList::~LinkedList() {

}



// test function implementation
void test_insert() {
    LinkedList *linked_list = new LinkedList;
    linked_list->InsertAtFront(1);
    linked_list->InsertAtFront(1);
    linked_list->InsertAtFront(2);
    linked_list->InsertAtFront(1);
    linked_list->InsertAtFront(1);
    linked_list->Print();

    return;
}

void test_search() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,-1} ;
    LinkedList *linked_list = new LinkedList(arr);
    linked_list->Print() ;
    Node *new_list_head = linked_list->Search(9) ;

    LinkedList *new_list = new LinkedList(new_list_head) ;
    new_list->Print();
}

void test_delete() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9} ;
    LinkedList *linked_list = new LinkedList(arr);
    linked_list->Print() ;
    linked_list->Delete(1) ;
    linked_list->Print() ;

    linked_list->Delete(9) ;
    linked_list->Print() ;

    linked_list->Delete(5) ;
    linked_list->Print() ;
}