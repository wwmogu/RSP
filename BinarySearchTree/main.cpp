#include <iostream>
using namespace std ;

struct Node {
    int data;
    Node *left, *right, *parent;
    Node() {};
    Node(int x) {
        data = x;
        parent = nullptr;
        left = nullptr;
    }
};

class BST {
public:
    Node *root;
    BST() ;
    void Insert(int x) ;
    void PreTraversal(Node *st) ;
    void InTraversal(Node *st) ;
    void PostTraversal(Node *st) ;
    Node* Search(int x) ;
    void Delete(int x) ;
    Node* Minimum(Node *st) ;
    ~BST();
};

void test_insert_traversal() ;
void test_search() ;
void test_min() ;
void test_delete();

int main()
{
    // test_insert_traversal() ;
    // test_search();
    // test_min() ;
    test_delete();
    return 0 ;
}

BST::BST() {

}
void BST::Insert(int x) {
    Node *newnode = new Node(x) ;

    // BST is empty
    if (this->root == nullptr) {
        this->root = newnode;
        return ;
    }

    // BST is not empty
    Node *dummy = this->root, *dummy_parent = nullptr;
    while (dummy != nullptr) {
        if (x > dummy->data) {
            dummy_parent = dummy ;
            dummy = dummy->right;
        }
        else if (x < dummy->data) {
            dummy_parent = dummy ;
            dummy = dummy->left;
        }
        else if (x == dummy->data) {
            return ;
        }
    }

    newnode->parent = dummy_parent;
    
    if(x < newnode->parent->data) {
        dummy_parent->left = newnode;
    }
    else if (x > newnode->parent->data){
        dummy_parent->right = newnode;
    }
    return ;
}

void BST::PreTraversal(Node *st) {
    if (st) {
        cout << st->data << " ";
        PreTraversal(st->left);
        PreTraversal(st->right);
    }
}
void BST::InTraversal(Node *st) {
    if (st) {
        InTraversal(st->left);
        cout << st->data << " ";
        InTraversal(st->right);
    }
}
void BST::PostTraversal(Node *st) {
    if (st) {
        PostTraversal(st->left);
        PostTraversal(st->right);
        cout << st->data << " ";
    }
}
Node* BST::Search(int x) {
    if (this->root) {
        Node *dummy = this->root;
        while (dummy != nullptr) {
            if (x == dummy->data) {
                return dummy ;
            }
            else if (x < dummy->data) {
                dummy = dummy->left;
            }
            else if(x > dummy->data) {
                dummy = dummy->right ;
            }
        }
    }
    return nullptr ;
}

Node* BST::Minimum(Node *st) {
    Node *dummy = st;
    while (dummy->left != nullptr) {
        dummy = dummy->left;
    }
    return dummy;
}


// this Deletion is not elegent but correct.
// The idea behind is just find the node to be delete, and check whether it has 0, 1 or 2 children then do the corrspanding operation
// Since it is a "linkedList" so, I need to find the predecessor when delete the node. So "parent" handle this.
void BST::Delete(int x) {
    // code for search....
    Node *del = this->Search(x) ;
    cout << "deleting: " << del-> data << endl;
    
    // no child
    if (del->left==nullptr && del->right==nullptr) {
        Node *tmp = del;
        Node *del_parent = del->parent;
        if (del_parent->left && del_parent->left->data == x) del_parent->left = nullptr;
        else del_parent->right = nullptr;
        del = nullptr;
        delete tmp;
    }
    // one child
    else if (del->right==nullptr || del->left==nullptr) {
        Node *tmp = del;
        Node *del_parent = del->parent;

        // right
        if (del_parent->right && del_parent->right->data == x){
            // right
            if (del->right) {
                del_parent->right = del->right;
            }
            // left
            else {
                del_parent->right = del->left;
            }
        }
        // left
        else {
            // right
            if (del->right) {
                del_parent->left = del->right;
            }
            // left
            else {
                del_parent->left = del->left;
            }
        }
        delete tmp;
    }
    // two children
    else {
        Node * tmp;
        Node *rightMin = this->Minimum(del->right) ;
        del->data = rightMin->data;
        tmp = rightMin;
        if (rightMin->right == nullptr) {
            if (rightMin->parent->left && rightMin->parent->left->data == rightMin->data) {
                rightMin->parent->left = nullptr;
            }
            else {
                rightMin->parent->right = nullptr;
            }
        }
        else {
            if (rightMin->parent->left && rightMin->parent->left->data == rightMin->data) {
                rightMin->parent->left = rightMin->right;
            }
            else {
                rightMin->parent->right = rightMin->right;
            }
        }
        delete tmp ;
    }
}
BST::~BST() {

}

void test_delete() {
    BST *bst = new BST();
    bst->Insert(2);
    bst->Insert(1);
    bst->Insert(7);
    bst->Insert(4);
    bst->Insert(8);
    bst->Insert(3);
    bst->Insert(6);
    bst->Insert(5);
    bst->InTraversal(bst->root);
    cout << endl ;
//              2
//      1              7
//                  4       8
//              3       6
//                  5

    // bst->Delete(3) ;    // 0
    // bst->Delete(6) ;    // 1
    bst->Delete(4) ;    // 2
    bst->InTraversal(bst->root);
    cout << endl;

}

void test_min() {
    BST *bst = new BST();
    bst->Insert(3);
    bst->Insert(2);
    bst->Insert(4);
    bst->Insert(1);
    bst->Insert(5);
    
    Node *node = bst->Minimum(bst->root) ;
    cout << node->data << endl;
    
    node = bst->Minimum(bst->root->right) ;
    cout << node->data << endl;
    
    node = bst->Minimum(bst->root->left->left) ;
    cout << node->data << endl;
}
void test_search() {
    BST *bst = new BST();
    bst->Insert(3);
    bst->Insert(2);
    bst->Insert(4);
    bst->Insert(1);
    bst->Insert(5);

    Node *node = bst->Search(3);
    cout << node->left->data << endl;
    cout << node->right->data << endl;

    node = bst->Search(9);
    if(node == nullptr) cout << "node doesn't exist\n";

    node = bst->Search(2);
    cout << node->left->data << endl;
    cout << node->parent->data << endl;
}

void test_insert_traversal() {
    BST *bst = new BST();
    bst->Insert(3);
    bst->Insert(2);
    bst->Insert(4);
    bst->Insert(1);
    bst->Insert(5);
    bst->PreTraversal(bst->root);
    cout << endl;
    bst->InTraversal(bst->root);
    cout << endl;
    bst->PostTraversal(bst->root);
    cout << endl;
    return ;
}