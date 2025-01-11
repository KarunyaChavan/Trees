#include"bits/stdc++.h"
using namespace std;

class node{
public:
    int key;
    node *left, *right;
    bool isT;
    node(int data):key(data),left(NULL),right(NULL){}
};

class BST{
public:
    node* root;
    BST():root(NULL){}

    void insertNode(int key){
    node* new_node = new node(key);
    if(root==NULL){
        root = new_node;
        return;
    }
    node* temp = root;
    while(temp!=NULL){
        if(temp->key > key){
            if(temp->left==NULL){
                temp->left = new_node;
                return;
            }
            temp = temp->left;
        }
        else{
            if(temp->right==NULL){
                temp->right = new_node;
                return;
            }
            temp = temp->right;
        }
    }
}

    void fillQueue(node* temp, queue<node* >* q){
        if(temp==NULL) return;
        if(temp->left)
            fillQueue(temp->left, q);
        q->push(temp);
        if(temp->right)
            fillQueue(temp->right,q);
    }

    void threadIt(node* temp, queue<node* >* q){
        if(temp==NULL) 
            return;
        if(temp->left)
            threadIt(temp->left,q);
        q->pop();
        if(temp->right)
            threadIt(temp->right,q);
        else{
            temp->right = q->front();
            temp->isT = true;
        }
    }

    void createThreads(node* root){
        queue<node* > q;
        fillQueue(root, &q);
        threadIt(root, &q);
    }

    node* leftMost(node* root){
        while(root && root->left)
            root = root->left;
        return root;
    }

    void inorder(){
        if(root==NULL) 
            return;
        node* cur = leftMost(root);
        while(cur!=NULL){
            cout<<cur->key<<" ";
            if(cur->isT)
                cur = cur->right;
            else
                cur = leftMost(cur->right);
        }
    }

};



int main(){
    BST b;
    int d;
    for(int i=0;i<7;i++){
        cout<<"Enter Key - ";
        cin>>d;
        b.insertNode(d);
    }
    //b.BFS();
    b.createThreads(b.root);
    b.inorder();
    return 0;
}