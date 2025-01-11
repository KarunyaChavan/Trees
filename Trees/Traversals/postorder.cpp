#include "iostream"
#include "queue"
#include "stack"
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
    
    void insertNode(int key){
        node* new_node = new node(key);
        if(root==NULL){
            root = new_node;
            return;
        }
        node* temp = root;
        while(temp){
            if(temp->key>key){
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

    void search(int key){
        node* temp = root;
        int lvl = 0;
        while(temp){
            if(temp->key==key){
                cout<<"\nFound at level "<<lvl<<endl;
                return;
            }
            else if(temp->key < key){
                temp = temp->Rchild;
                lvl++;
            }
            else{
                temp = temp->Lchild;
                lvl++;
            }
        }
        cout<<"Not Found"<<endl;
        return;
    }

    void minVal(){
        if(root==NULL){
            cout<<"Tree is empty"<<endl;
            return;
        }
        node* temp = root;
        while(temp->Lchild!=NULL){
            temp = temp->Lchild;
        }
        cout<<"Minimum Value is "<<temp->key<<endl;
    }

    void postorderRec(node* root){
        if(root==NULL) return;
        postorderRec(root->Lchild);
        postorderRec(root->Rchild);
        cout<<root->key<<" ";
    }

    void postorderItr(){
        node* temp = root;
        stack<node* > s;
        stack<char > s1;
        char flag;
        while(true){
            while(temp){
                s.push(temp);
                s1.push('L');
                temp = temp->Lchild;
            }
            if(s.empty()) return;
            else{
                temp = s.top();
                s.pop();
                flag = s1.top();
                s1.pop();
                if(flag=='R'){
                    cout<<temp->key<<" ";
                    temp = NULL;
                }else{
                    s.push(temp);
                    s1.push('R');
                    temp = temp->Rchild;
                }
            }
        }
    }

    void breadthFirstTraversal(){
        cout<<"\n"<<endl;
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
};

int main(){
    BST b;
    int d;
    for(int i=0;i<10;i++){
        cout<<"Key - ";
        cin>>d;
        b.insertNode(d);
    }
    b.display();
    b.postorderRec(b.root);
    cout<<endl;
    b.postorderItr();
    cout<<endl;
    return 0;
}