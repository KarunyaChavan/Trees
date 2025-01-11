#include "iostream"
#include "stack"
#include "queue"
using namespace std;

class node{
public:
    string key;
    node *Lchild, *Rchild;
    node(string val):key(val),Lchild(NULL),Rchild(NULL){}
};

class BST{
public:
    node* root;
    BST():root(NULL){}
    void insertNode(string key);
    bool deleteNode(string key);
    node* search(string key);
    bool isEmpty(){
        if(root==NULL){
            return true;
        }else return false;
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

    void getHeight(){
        node* temp = root;
        int rh=0,lh=0;
        
        while(temp){
            if(temp->Lchild==NULL && temp->Rchild!=NULL)
                temp = temp->Rchild;
            else temp=temp->Lchild;
            lh++;
        }
        temp = root;
        while(temp){
            if(temp->Lchild!=NULL && temp->Rchild==NULL)
                temp = temp->Lchild;
            else temp=temp->Rchild;
            rh++;
        }
        if(lh>=rh){
            cout<<"Height = "<<lh-1<<endl;
            temp = root;
            while(temp){
                cout<<temp->key<<" ";
                if(temp->Lchild==NULL && temp->Rchild!=NULL)
                    temp = temp->Rchild;
                else temp=temp->Lchild;
            }
        }else{
            cout<<"Height = "<<rh-1<<endl;
            temp = root;
            while(temp){
                cout<<temp->key<<" ";
                if(temp->Lchild!=NULL && temp->Rchild==NULL)
                    temp = temp->Lchild;
                else temp=temp->Rchild;
            }
        }
    }

    int getHeightR(node* root){
        int hl, hr;
        if(root==NULL)
            return 0;
        if(root->Lchild==NULL && root->Rchild==NULL)
            return 0;
        hl = getHeightR(root->Lchild);
        hr = getHeightR(root->Rchild);
        if(hr>hl)
            return(hr+1);
        return(hl+1);
    }

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->Lchild);
        cout<<root->key<<" ";
        inorderTraversal(root->Rchild);
    }

    void DecinorderTraversal(node* root){ //Decreasing Inorder
        if(root==NULL) return;
        //cout<<root->key<<" ";
        DecinorderTraversal(root->Rchild);
        cout<<root->key<<" ";
        DecinorderTraversal(root->Lchild);
    }

    void preorderTravesal(node* root){
        if(root==NULL)
            return;
        cout<<root->key<<" ";         //D
        preorderTravesal(root->Lchild);//L
        preorderTravesal(root->Rchild);//R
    }

    node* getSuccessor(node* delNode){
        node* successorParent = delNode;
        node* successor = delNode;
        node* current = delNode->Rchild;
        while(current){
            successorParent = successor;
            successor = current;
            current = current->Lchild;
        }
        if(successor!=delNode->Rchild){
            successorParent->Lchild = successor->Rchild;
            successor->Rchild = delNode->Rchild;
        }
        return successor;
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
    
    node* minVal(node* root){
        if(root==NULL){
            cout<<"Tree is empty"<<endl;
            return root;
        }
        node* temp = root;
        while(temp->Lchild!=NULL){
            temp = temp->Lchild;
        }
        return temp;
        //cout<<"Minimum Value is "<<temp->key<<endl;
    }
};

void BST::insertNode(string key){
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

node* BST::search(string key){
    node* temp = root;
    while(temp){
        if(temp->key==key){
            cout<<"\nFOUND"<<endl;
            return temp;
        }
        else if(temp->key > key){
            temp = temp->Lchild;
        }
        else{
            temp = temp->Rchild;
        }
    }
    cout<<"\nNOT FOUND"<<endl;
    return NULL;
}

bool BST::deleteNode(string key){
    if(root==NULL){
        cout<<"\nEmpty BST"<<endl;
        return true;
    }
    node* curr = root;
    node* parent = root;
    bool isLeftChild = true;
    //Step 1 : Search Key.
    while(curr->key!=key){
        parent = curr;
        //Finding whether key to be deleted is left child or right child
        if(key < curr->key){
            isLeftChild = true;
            curr = curr->Lchild;
        }
        else{
            isLeftChild = false;
            curr = curr->Rchild;
        }
       
        if(curr==NULL){
            cout<<"Key to be deleted Not Found"<<endl;
            return false;
        }
    }
    //Case 1: Leaf Node Deletion
    if(curr->Lchild==NULL && curr->Rchild==NULL){
        if(curr==root){
            root = NULL;
        }
        else if(isLeftChild){
            parent->Lchild = NULL;
        }
        else{
            parent->Rchild = NULL;
        }
    }

    //Case 2 : Single Child Deletion
    //If node to be deleted has a left child
    else if(curr->Rchild==NULL){
        if(curr==root){
            root = curr->Lchild;
        }
        else if(isLeftChild){
            parent->Lchild = curr->Lchild;
        }
        else{
            parent->Rchild = curr->Lchild;
        }
    }
    //If node to be deleted has a right child
    else if(curr->Lchild==NULL){
        if(curr==root){
            root = curr->Rchild;
        }
        else if(isLeftChild){
            parent->Lchild = curr->Rchild;
        }
        else{
            parent->Rchild = curr->Rchild;
        }
    }

    //Case 3 : Fully Internal node deletion
    else{
        //Step 1 : Get Inorder Successor
        node* successor = getSuccessor(curr);

        //OR Step 1 : Get Inorder Predecessor
        //node* successor = (curr->Lchild);

        if(curr==root)
            root = successor;
        //If node to be deleted was left child
        else if(isLeftChild)
            parent->Lchild = successor;
        else   
            parent->Rchild = successor;
        //Dispatch subtree and connect it to the
        successor->Lchild = curr->Lchild;

        //Manipulation for Predecessor
        // if(successor->Rchild)
        //     successor->Rchild->Rchild = curr->Rchild;
        // else
        // successor->Rchild = curr->Rchild;
        
    }
    free(curr);
    cout<<"DELETED"<<endl;
    return true;
}

int main(){
    BST b;
    string data;
    for(int i=0;i<12;i++){
        cout<<"Enter Data "<<i+1<<" = ";
        cin>>data;
        b.insertNode(data);
    }
    b.display();
    b.preorderTravesal(b.root);
    //b.deleteNode(16);
    //b.display();
    b.breadthFirstTraversal();
    // b.display();
    // b.deleteNode(11);
    // b.display();
    // //b.getHeight();
    // b.breadthFirstTraversal();
    // cout<<endl;
    // b.DecinorderTraversal(b.root);
}
