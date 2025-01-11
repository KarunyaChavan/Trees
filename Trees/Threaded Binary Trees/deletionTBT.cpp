#include"iostream"
#include"queue"
using namespace std;

class node{
public:
    int key;
    node *left, *right;
    int l,r;
    node(int data):left(NULL),right(NULL),l(0),r(0),key(data){}
    node():left(NULL),right(NULL),l(0),r(0),key(-1){}
};

class TBT{
public:
    node *root, *head;
    TBT(){
        head = new node;
        head->left = head;
        head->right = head;
        head->r = 1;
        root = NULL;
    }

    node* buildTree(){ 
        char data;
        cout<<"Enter Data = "; //Asking data for new node
        cin>>data;
        node* temp = new node(data);//Creating node with input data
        if(data=='-') //BASE CASE
            return NULL;//To end the path
        cout<<"Enter data for left part of "<<data<<endl;
        temp->left = buildTree();//Will continue until data!=-1
        cout<<"Enter data for right part of "<<data<<endl;
        temp->right = buildTree();
        return temp;
    }

    void insert(int data){
        node* new_node = new node(data);
        if(root==NULL){
            root = new_node;
            root->left = head;
            root->right = head;
            head->left=root;
            head->l = 1;
        }
        else{
            node* temp = root;
            while(temp){
                if(new_node->key < temp->key){
                    if(temp->l==0){
                        new_node->left = temp->left;
                        new_node->right = temp;
                        temp->l=1;
                        temp->left = new_node;
                        return;
                    }
                    temp = temp->left;
                }else{
                    if(temp->r==0){
                        new_node->right = temp->right;
                        new_node->left = temp;
                        temp->r=1;
                        temp->right = new_node;
                        return;
                    }
                    temp = temp->right;
                }
            }
        }
    }

    void BFS(){
        queue<node* > q;
        if(root==NULL) return;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
                node* temp = q.front();
                q.pop();
                if(temp==NULL){
                    cout<<endl;
                    if(!q.empty()) q.push(NULL);
                }
                else{
                    cout<<temp->key<<"  ";
                    if(temp->l==1) q.push(temp->left);
                    if(temp->r==1) q.push(temp->right);
                }
        }
    }

    node* inorderSucc(node* ptr){
        node* temp = ptr->right;
        if(ptr->r==1){
            while(temp->l==1){
                temp = temp->left;
            }
        }
        return temp;
    }

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->left); //L
        cout<<root->key<<" ";          //D
        inorderTraversal(root->right); //R
    }

    void inorder(){
        node* temp = head;
        if(root==NULL){
            cout<<"\nTree is Empty"<<endl;
            return;
        }
        do{
            temp = inorderSucc(temp);
            if(temp!=head){
                cout<<temp->key<<" ";
            }
        }while(temp!=head);
        cout<<endl;
    }

    node* inSucc(node* delNode){
        node* successor = delNode->right;
        node* successorParent = successor;
        if(delNode->r==1){
            while(successor->l){
                successorParent = successor;
                successor = successor->left;
            }
        }
        if(successor!=delNode->right){
            if(successor->r)
                successorParent->left = successor->right;
            successor->right = delNode->right;
        }
        return successor;
    }

    node* inPred(node* curr){
        node* pre = (curr->left);
        if(curr->l!=0){
            while(pre->r!=0)
                pre = pre->right;
        }
        return pre;
    }

    bool deleteNode(int key){
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
            curr = curr->left;
        }
        else{
            isLeftChild = false;
            curr = curr->right;
        }
       
        if(curr==NULL){
            cout<<"Key to be deleted Not Found"<<endl;
            return false;
        }
    }
    //Case 1: Leaf Node Deletion
    if(curr->l==0 && curr->r==0){
        if(curr==root){
            root = NULL;
            head->l = 0;
        }
        else if(isLeftChild){
            parent->l = 0;
            parent->left = curr->left;
        }
        else{
            parent->r = 0;
            parent->right = curr->right;
        }
    }

    //Case 2 : Single Child Deletion
    //If node to be deleted has a left child
    else if(curr->r==0){
        node* s = inSucc(curr);
        node* p = inPred(curr);
        if(curr==root){
            head->left = root->left;
            root = curr->left;
        }
        else if(isLeftChild){
            parent->left = curr->left;
        }
        else{
            parent->right = curr->left;
        }
        p->right = s;
    }
    //If node to be deleted has a right child
    else if(curr->l==0){
        node* s = inSucc(curr);
        node* p = inPred(curr);
        if(curr==root){
            head->right = root->right;
            root = curr->right;
        }
        else if(isLeftChild){
            parent->left = curr->right;
        }
        else{
            parent->right = curr->right;
        }
        s->left = p;
    }

    //Case 3 : Fully Internal node deletion
    else{
        //Step 1 : Get Inorder Successor
        node* successor = inSucc(curr);
        if(curr==root){
            node* pred = inPred(root);
            head->left = successor;
            pred->right = successor;
            successor->left = root->left;
            successor->l = 1;
            if(successor!=root->right){
                successor->right->l = 0;
                successor->right = root->right;
                successor->r = 1;
            }
            root = successor;
            free(curr);
            return true;
        }
        //If node to be deleted was left child
        else if(isLeftChild)
            parent->left = successor;
        else   
            parent->right = successor;
        //Dispatch subtree and connect it to the
        if(successor->l==0){
            successor->l = 1;
            curr->left->right = successor;
            successor->left = curr->left;
        }
    }
    free(curr);
    cout<<"\nDELETED"<<endl;
    return true;
}
};

int main(){
    TBT t;
    int d;
    for(int i=0;i<7;i++){
        cout<<"KEY - ";
        cin>>d;
        t.insert(d);
    }
    // t.root = t.buildTree();
    // cout<<t.root->key<<endl;
    // t.inorderTraversal(t.root);
    t.BFS();
    t.inorder();
    t.deleteNode(30);
    t.BFS();
    t.inorder();
    return 0;
}