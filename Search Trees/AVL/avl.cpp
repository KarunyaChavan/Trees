#include "iostream"
#include "queue"
using namespace std;

class node{
public:
    int val;
    int balance;
    node *left, *right;
    node(int v):val(v),left(NULL),right(NULL),balance(0){}
    node():val(0),left(NULL),right(NULL),balance(0){}
};

class AVL{
    node* root;
public:
    AVL():root(NULL){}

    void BFS(node* root){
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
                cout<<temp->val<<" ";
                if(temp->left)
                    q.push(temp->left);
                if(temp->right)
                    q.push(temp->right);
            }
        }
    }

    node* insert(int data,node* ptr, bool *ht_inc){
        node *aptr, *bptr;
        if(ptr==NULL){
            ptr = new node(data);
            *ht_inc = true;
            return ptr;
        }
        if(data < ptr->val){
            ptr->left = insert(data,ptr->left,ht_inc);
            if(*ht_inc){
                switch(ptr->balance){
                    case -1://Right Heavy
                        ptr->balance = 0;
                        *ht_inc = false;
                        break;

                    case 0:
                        ptr->balance = 1;
                        break;

                    case 1:
                        aptr = ptr->left;
                        if(aptr->balance==1){
                            cout<<"Left to Left Rotation"<<endl;
                            ptr->left = aptr->right;
                            aptr->right = ptr;
                            ptr->balance = 0;
                            aptr->balance = 0;
                            ptr = aptr;
                        }
                        else{
                            cout<<"Left to Right Rotation"<<endl;
                            bptr = aptr->right;
                            aptr->right = bptr->left;
                            bptr->left = aptr;
                            ptr->left = bptr->right;
                            bptr->right = ptr;
                            if(bptr->balance==1){
                                ptr->balance = -1;
                            }else{
                                ptr->balance = 0;
                            }
                            if(bptr->balance==-1){
                                aptr->balance = 1;
                            }else{
                                aptr->balance = 0;
                            }
                            bptr->balance = 0;
                            ptr = bptr;
                        }
                        *ht_inc = false;
                        break;
                }
            }
        }
        else if(data > ptr->val){
            ptr->right = insert(data,ptr->right,ht_inc);
            if(*ht_inc){
                switch(ptr->balance){
                    case 1://Left Heavy
                        ptr->balance = 0;
                        *ht_inc = false;
                        break;

                    case 0:
                        ptr->balance = -1;
                        break;

                    case -1://Right heavy
                        aptr = ptr->right;
                        if(aptr->balance==-1){
                            cout<<"Right to Right Rotation"<<endl;
                            ptr->right = aptr->left;
                            aptr->left = ptr;
                            ptr->balance = 0;
                            aptr->balance = 0;
                            ptr = aptr;
                        }
                        else{
                            cout<<"Right to Left Rotation"<<endl;
                            bptr = aptr->left;
                            aptr->left = bptr->right;
                            bptr->right = aptr;
                            ptr->right = bptr->left;
                            bptr->left = ptr;
                            if(bptr->balance==-1){
                                ptr->balance = 1;
                            }else{
                                ptr->balance = 0;
                            }
                            if(bptr->balance==1){
                                aptr->balance = -1;
                            }else{
                                aptr->balance = 0;
                            }
                            bptr->balance = 0;
                            ptr = bptr;
                        }
                        *ht_inc = false;
                        break;
                }
            }
        }
        return ptr;
    }

    void display(node* ptr, int level){
        int i;
        if(ptr!=NULL){
            display(ptr->right,level+1);
            cout<<endl;
            for(i=0;i<level;i++)
                cout<<"  ";
            cout<<ptr->val;
            display(ptr->left,level+1);
        }
    }

    void inorder(node* ptr){
        if(ptr!=NULL){
            inorder(ptr->left);
            cout<<ptr->val<<"  ";
            inorder(ptr->right);
        }
    }
};

int main(){
    AVL avl;
    bool ht_inc;
    int data,opt=1;
    node* root = new node();
    root = NULL;
    while(opt==1){
        cout<<"Enter data = ";
        cin>>data;
        root = avl.insert(data,root,&ht_inc);
        cout<<"Press 1 to continue = ";
        cin>>opt;
    }
    avl.BFS(root);
    avl.inorder(root);
}