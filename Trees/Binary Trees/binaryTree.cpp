#include "iostream"
#include "stack"
#include "queue"
using namespace std;

class node{
public:
    int data;
    node* Lchild;
    node* Rchild;
    node(int val){
        data = val;
        Lchild = NULL;
        Rchild = NULL;
    }
};

node* buildTree(node* root){
    int data;
    cout<<"Enter Data = ";
    cin>>data;
    root = new node(data);
    if(data==-1)
        return NULL;
    cout<<"Enter Data for Left Part of "<<data<<endl;
    root->Lchild = buildTree(root->Lchild);
    cout<<"Enter Data for Right Part of "<<data<<endl;
    root->Rchild = buildTree(root->Rchild);
    return root;
}

void breadthFirst(node* root){ //LevelOrderTraversal
    queue<node*> q;
    q.push(root);
    q.push(NULL);//separator
    while(!q.empty()){
        node* front = q.front();
        q.pop();
        if(front==NULL){ //previous level comletely traversed
            cout<<endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout<<front->data<<"  ";
            if(front->Lchild)
                q.push(front->Lchild);
            if(front->Rchild)
                q.push(front->Rchild);
        }
    }
}

void inorderTravesal(node* root){
    if(root==NULL)
        return;
    inorderTravesal(root->Lchild);
    cout<<root->data<<" ";
    inorderTravesal(root->Rchild);
}

void inorderTravesalCount(node* root, int &count){
    if(root==NULL)
        return;
    inorderTravesalCount(root->Lchild, count);
    if(root->Lchild == NULL && root->Rchild==NULL)
        count++;
    inorderTravesalCount(root->Rchild, count);
}

void preorderTravesal(node* root){
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    preorderTravesal(root->Lchild);
    preorderTravesal(root->Rchild);
}

void postTravesal(node* root){
    if(root==NULL)
        return;
    postTravesal(root->Lchild);
    postTravesal(root->Rchild);
    cout<<root->data<<" ";
}

node* buildFromLevelOrder(node* root){
    queue<node*> q;
    cout<<"Enter Data for Root = ";
    int data;
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

int leafNodeCount(node* root){
    int cnt = 0;
    inorderTravesalCount(root,cnt);
    return cnt;
}

int main(){
    node* root = NULL;
   // root = buildFromLevelOrder(root);
    
    root = buildTree(root);
    cout<<"Level Traversal : "<<endl;
    breadthFirst(root);
    cout<<"Number of Lead Nodes = "<<leafNodeCount(root)<<endl;
    // cout<<"\nInorder Traversal : "<<endl;
    // inorderTravesal(root);
    // cout<<"\nPreorder Traversal : "<<endl;
    // preorderTravesal(root);
    // cout<<"\nPostorder Traversal : "<<endl;
    // postTravesal(root);
    return 0;
}