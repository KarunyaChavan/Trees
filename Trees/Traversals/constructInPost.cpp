#include "iostream"
#include "stack"
#include "queue"
#include "map"
using namespace std;

class node{
public:
    int key;
    node *Lchild, *Rchild;
    node(int val):key(val),Lchild(NULL),Rchild(NULL){}
};

class BST{
public:
    node* root;
    BST():root(NULL){}
    void insertNode(int key);
    
    bool isEmpty(){
        if(root==NULL){
            return true;
        }else return false;
    }

    void createMapping(int in[], map<int, int> &nodeToIndex, int n){
        for(int i=0;i<n;i++){
            nodeToIndex[in[i]] = i;
        }
    }

    void breadthFirstTraversal(){
        queue<node*> q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            node* temp = q.front();
            q.pop();
            if(temp==NULL){
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }else{
                cout<<temp->key<<" ";
                if(temp->Lchild)
                    q.push(temp->Lchild);
                if(temp->Rchild)
                    q.push(temp->Rchild);
            }
        }
    }

    void display(){
        stack<node*> s;
        s.push(root);
        int nb = 32;
        cout<<"-----------------------------------------------------------"<<endl;
        bool isRowEmpty = false;
        while(isRowEmpty==false){
            stack<node*> s1;
            isRowEmpty = true;
            for(int j=0;j<nb;j++){
                cout<<" ";
            }
            while(s.empty()==false){
                node* temp = s.top();
                s.pop();
                if(temp!=NULL){
                    cout<<temp->key;
                    s1.push(temp->Lchild);
                    s1.push(temp->Rchild);
                    if(temp->Lchild != NULL || temp->Rchild != NULL)
                        isRowEmpty = false;
                }
                else{
                    cout<<"--";
                    s1.push(NULL);
                    s1.push(NULL);
                }
                for(int j=0;j<nb*2-2;j++){
                    cout<<" ";
                } 
                }
                cout<<endl;
                nb /= 2;
                while(s1.empty()==false){
                    s.push(s1.top());
                    s1.pop();
                }
            }
            cout<<"-----------------------------------------------------------"<<endl;
        }

    node* buildTreeFromTraversal(int in[], int pre[],int n);
    node* solve(int in[], int pre[], int &index, int inorderStart, int inorderEnd,int n, map<int,int> k);    
};

node* BST::solve(int in[], int post[], int &index, int inorderStart, int inorderEnd, int n,map<int,int> nodeToIndex){
    if(index < 0 || inorderStart>inorderEnd) 
        return NULL;
    int element = post[index--];
    node* temp = new node(element);
    int pos = nodeToIndex[element];
    temp->Rchild = solve(in,post,index,pos+1,inorderEnd,n,nodeToIndex);
    temp->Lchild = solve(in,post,index,inorderStart,pos-1,n,nodeToIndex);
    return temp;
}

node* BST::buildTreeFromTraversal(int in[], int post[],int n){
    int postOrderIndex = n-1;
    map<int,int> nodeToIndex;
    createMapping(in, nodeToIndex, n);
    node* ans = solve(in, post, postOrderIndex, 0, n-1, n,nodeToIndex);
    return ans;
}

void BST::insertNode(int key){
    node* new_node = new node(key);
    if(root==NULL){
        root = new_node;
        return;
    }
    node* temp = root;
    while(temp!=NULL){
        if(temp->key > key){
            if(temp->Lchild==NULL){
                temp->Lchild = new_node;
                return;
            }
            temp = temp->Lchild;
        }
        else{
            if(temp->Rchild==NULL){
                temp->Rchild = new_node;
                return;
            }
            temp = temp->Rchild;
        }
    }
}

int main(){
    BST b;
    int in[] = {9,5,1,7,2,12,8,4,3,11};
    int post[] = {9,1,2,12,7,5,3,11,4,8};
    b.root = b.buildTreeFromTraversal(in,post,10);
    b.display();
}