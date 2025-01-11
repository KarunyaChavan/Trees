
#include"iostream"
using namespace std;

class node{
public:
    int val;
    node *right, *left;
    int thread;
    node(int data):val(data),right(NULL),left(NULL),thread(0){}
};

class TBT{
public:
    node* root;
    TBT():root(NULL){}

    node* insert(node* root,int val, node* rt){
        node* new_node = new node(val);
        if(root==NULL){
            root = new_node;
            if(rt){
                root->right = rt;
                root->thread = 1;
            }
        }else{
            if(val < root->val){
                root->left = insert(root->left,val,root);
            }else{
                if(root->thread==1){
                    root->right = insert(NULL,val,rt);
                    root->thread = 0;
                }else{
                    root->right = insert(root->right,val,rt);
                }
            }
        }
    }

    node* create(){
        node* temp = root;
        int num;
        cout<<"Enter Elements, Press -1 to terminate ";
        cin>>num;
        while(num!=-1){
            temp = new node(num);
            root = insert(root,num,NULL);
            cout<<"Enter Next Element ";
            cin>>num;
        }
        return root;
    }

    void inorder(node* root){
        node *temp =root, *prev;
        do{
            while(temp){
                prev = temp;
                temp = temp->left;
            }
            if(prev){
                cout<<prev->val<<" ";
                temp = prev->right;
                while(prev!=NULL && prev->thread){
                    cout<<temp->val<<" ";
                    prev = temp;
                    temp = temp->right;
                }
            }
        }while(temp);
    }

};

int main(){
    TBT t;
    t.create();
    t.insert(t.root,10,NULL);
    t.insert(t.root,14,NULL);
    t.inorder(t.root);
    return 0;
}