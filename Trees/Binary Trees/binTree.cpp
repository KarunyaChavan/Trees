#include "iostream"
#include "stack"
#include "queue"
using namespace std;

class node{
public:
    int data;
    node* Rchild;
    node* Lchild;
    node(int val):data(val), Rchild(NULL), Lchild(NULL){}
};

class binaryTree{
public:
    node* root;

    binaryTree():root(NULL){}//Initailly no data , so tree is empty

    node* buildTree(){ 
        int data;
        cout<<"Enter Data = "; //Asking data for new node
        cin>>data;
        node* temp = new node(data);//Creating node with input data
        if(data==-1) //BASE CASE
            return NULL;//To end the path
        cout<<"Enter data for left part of "<<data<<endl;
        temp->Lchild = buildTree();//Will continue until data!=-1
        cout<<"Enter data for right part of "<<data<<endl;
        temp->Rchild = buildTree();
        return temp;
    }

    node* buildTreeFromLevelOrder(node*){
        queue<node*> q;
        int data;
        cout<<"Enter Data for Root = ";
        cin>>data;
        root = new node(data);
        q.push(root);
        while(!q.empty()){
            node* temp = q.front();
            q.pop();
            cout<<"Enter Left Node for "<<temp->data<<" = ";
            int leftData;
            cin>>leftData;
            if(leftData!=-1){
                temp->Lchild = new node(leftData);
                q.push(temp->Lchild);
            }
            cout<<"Enter Right Node for "<<temp->data<<" = ";
            int rightData;
            cin>>rightData;
            if(rightData!=-1){
                temp->Rchild = new node(rightData);
                q.push(temp->Rchild);
            }
        } 
        return root;
    }

    void breadthFirstTraversal(){
        queue<node*> q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            node* temp = q.front();
            q.pop();
            if(temp==NULL){
                cout<<endl;//Prints newline 
                if(!q.empty()) q.push(NULL);
            }
            else{
                cout<<temp->data<<" ";
                if(temp->Lchild)
                    q.push(temp->Lchild);
                if(temp->Rchild)
                    q.push(temp->Rchild);
            }
        }
    }

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->Lchild); //L
        cout<<root->data<<" ";          //D
        inorderTraversal(root->Rchild); //R
    }

    void preorderTravesal(node* root){
        if(root==NULL)
            return;
        cout<<root->data<<" ";         //D
        preorderTravesal(root->Lchild);//L
        preorderTravesal(root->Rchild);//R
    }

    void postTravesal(node* root){
        if(root==NULL)
            return;
        postTravesal(root->Lchild);//L
        postTravesal(root->Rchild);//R
        cout<<root->data<<" ";     //D
    }
};

int main(){
    binaryTree b;
    //b.root = b.buildTree();
    b.root = b.buildTreeFromLevelOrder(b.root);
    cout<<"\nBreadth First Traversal"<<endl;
    b.breadthFirstTraversal();
    cout<<"\nInorder Traversal = ";
    b.inorderTraversal(b.root);
    cout<<endl;
    //1 3 5 7 -1 -1 11 -1 -1 17 -1 -1 -1
    return 0;
}