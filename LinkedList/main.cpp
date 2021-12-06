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


void Print(Node *head) ;
Node *Search(Node *head, int x);
void InsertAtFront(Node **head, int x);
void Delete(Node **head, int x);

int main()
{
    Node *head = nullptr;

    cout << "---------------------------" << endl;cout << "---------------------------" << endl;
    cout << "insert" << endl;
    InsertAtFront(&head, 9);
    InsertAtFront(&head, 8);
    InsertAtFront(&head, 7);
    InsertAtFront(&head, 6);
    InsertAtFront(&head, 5);
    InsertAtFront(&head, 4);
    InsertAtFront(&head, 3);
    InsertAtFront(&head, 2);
    InsertAtFront(&head, 1);
    Print(head);

    cout << "---------------------------" << endl;cout << "---------------------------" << endl;
    cout << "search 4" << endl;
    Node *new_list_head = Search(head, 4) ;
    Print(new_list_head);

    cout << "---------------------------" << endl;cout << "---------------------------" << endl;
    cout << "before delete" << endl;
    
    Print(head) ;

    Delete(&head, 1) ;
    cout << "delete 1" << endl;
    Print(head) ;

    Delete(&head, 9) ;
    cout << "delete 9" << endl;
    Print(head) ;

    Delete(&head, 5) ;
    cout << "delete 5" << endl;
    Print(head) ;
    
    return 0 ;
}

Node *Search(Node *head, int x) {
    if(head == nullptr) {
        return nullptr;
    }

    if (head->data == x) {
        return head;
    }
    else {
        return Search(head->next, x) ;
    }
}

void InsertAtFront(Node **head, int x) {
    Node *new_node = new Node(x);
    new_node->next = *head;
    *head = new_node;
}

void Delete(Node **head, int x) {
    // Linked list is empty
    if (head == nullptr) {
        return ;
    }

    // if the node is the head of linkedList
    if ((*head)->data == x) {
        Node* del = (*head) ;
        (*head) = (*head)->next;
        delete del;
        return ;
    }

    // other node
    Node *dummy = *head;
    while (dummy->next != nullptr) {
        if (dummy->next->data == x) {
            Node * del = dummy->next;
            dummy->next = dummy->next->next;
            delete del;
            return ;
        }
        dummy = dummy->next ;
    }


    printf("Nothing matched\n") ;
}

void Print(Node *head) {
    Node *dummy = head;
    while(dummy) {
        cout << dummy->data << ' ';
        dummy = dummy->next;
    }
    cout << endl ;
    return ;
}
