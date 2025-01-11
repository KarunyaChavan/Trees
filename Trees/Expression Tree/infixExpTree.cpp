#include "iostream"
#include "queue"
#include "stack"
using namespace std;

class node{
public:
    char key;
    node *Lchild, *Rchild;
    node(int val):key(val),Lchild(NULL),Rchild(NULL){}
};

class BST{
public:
    node* root;
    BST():root(NULL){}
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

    void inorderTraversal(node* root){
        if(root==NULL) return;
        inorderTraversal(root->Lchild);
        cout<<root->key<<" ";
        inorderTraversal(root->Rchild);
    }

    node* createExp(string exp);
};

int getPrior(char c){
    if(c=='^'){
        return 3;
    }
    else if(c=='*' || c=='/'){
        return 2;
    }
    else if(c=='+' || c=='-'){
        return 1;
    }
    else{
        return -1;
    }
}

string infixToPostfix(string infix){
    stack<char> s;
    string postfix; //Declaring a string to store postfix expression
    //Phase 1:- Iterating infix expression
    for(int i=0;i<infix.length();i++){
        //Case 1 - Checking for a operand by checking range lies between ASCII values or not
        if((infix[i]>='a' && infix[i]<='z') || (infix[i]>='A' && infix[i]<='Z') || (infix[i]>='0' && infix[i]<='9')){
            //Adding operands directly to the postfix
            postfix += infix[i];
        }
        //Case 2 - Opening braces encountered
        else if(infix[i]=='('){
            //Add directly to the postfix
            s.push(infix[i]);
        }
        
        //Case 2.2 - Closing braces encountered
        else if(infix[i]==')'){
            //Pop unitl opening bracket is encountered
            while((!s.empty()) && (s.top()!='(')){
                postfix += s.top(); //Add the element at top to the postfix
                s.pop();
            }
            //Discard opening bracket wihtout adding it to postfix
            s.pop();
        }
        //Case 3 - Operators
        else{
            while((!s.empty()) && ((getPrior(s.top())) >= (getPrior(infix[i])))){ //infix[i] = incoming and st[top] = top
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
    }
    //Phase 2: If stack is not empty
    while((!s.empty())){
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

node* BST::createExp(string exp){
    stack<node*> s;
    node* temp;
    for(int i=0;exp[i]!='\0';i++){
        if((exp[i]>='a' && exp[i]<='z') || (exp[i]>='A' && exp[i]<='Z') || (exp[i]>='0' && exp[i]<='9')){
            node* n = new node(exp[i]);
            s.push(n);
        }
        else if(exp[i]=='+' || exp[i]=='-' || exp[i]=='/' || exp[i]=='^' || exp[i]=='%' || exp[i]=='*'){
            temp = new node(exp[i]);
            node* t1 = s.top();
            s.pop();
            node* t2 = s.top();
            s.pop();
            temp->Lchild = t2;
            temp->Rchild = t1; 
            s.push(temp);
        }
    }
    return temp;
}

int main(){
    string infix = "(a+b*c)/d";
    string p = infixToPostfix(infix);
    cout<<p<<endl;
    BST t;
    p = "ab-cd+*";
    t.root = t.createExp(p);
    //cout<<t.root->key<<endl;
    t.breadthFirstTraversal();
    t.inorderTraversal(t.root);
}