#include"iostream"
#include"queue"
using namespace std;

class node{
public:
    int key;
    int l,r;
    node *right, *left;
    node(int data):key(data),right(NULL),left(NULL),l(1),r(1){}
    node(){}
};

class TBT{
public:
    node *root, *head;
    TBT(){
        head = new node;
        head->right = head;
        head->left = head;
        head->l = 1;
        head->r = 0;
        root = NULL;
    }

    void create(){
        node *temp, *curr;
        char ans;
        int d;
        do{
            cout<<"Enter Data : ";
            cin>>d; 
            curr = new node(d);
            if(root==NULL){
                root = curr;
                root->right = head;
                root->left = head;
                head->left = root;
                head->l = 0;
            }else{
                temp = root;
                while(true){
                    if(curr->key < temp->key){
                        if(temp->l==1){
                            curr->left = temp->left;
                            curr->right = temp;
                            temp->l = 0;
                            temp->left = curr;
                            break;
                        }
                        temp = temp->left;
                    }else{
                       if(temp->r==1){
                            curr->right = temp->right;
                            curr->left = temp;
                            temp->r = 0;
                            temp->right = curr;
                            break;
                        }
                        temp = temp->right; 
                    }
                }
            }
            cout<<"Press Y to continue = ";
            cin>>ans;
        }while(ans=='y' || ans=='Y');
    }

    node* inorderSucc(node* ptr){
        node* temp = ptr->right;
        if(ptr->r==0){
            while(temp->l==0){
                temp = temp->left;
            }
        }
        return temp;
    }

    void inorder(){
        node* temp = head;
        do{
            temp = inorderSucc(temp);
            if(temp!=head){
                cout<<temp->key<<" ";
            }
        }while(temp!=head);
    }
    
};

int main(){
    TBT t;
    t.create();
    t.inorder();
    return 0;
}