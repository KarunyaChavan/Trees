#include "iostream"
using namespace std;
#define max 20
string leaf[max];
int i,j,k,l,min, n, r[max][max];
float p[max], q[max], w[max][max], c[max][max];

void OBST(){
	for(i=0;i<n;i++)
	  { //Initialisation
		c[i][i]=0.0;
		r[i][i]=0;
		w[i][i]=q[i];
		// for j-i=1 ----> j=i+1
		w[i][i+1]=w[i][i]+q[i+1]+p[i+1];
		c[i][i+1]=w[i][i+1];
		r[i][i+1]=i+1;
	  }
	c[n][n]=0.0;
	r[n][n]=0;
	w[n][n]=q[n];
	//for j-i=2,3,4....,n
	for(i=2;i<=n;i++){
		for(j=0;j<=n-i;j++){
			w[j][j+i]=q[j+i]+p[j+i]+w[j][j+i-1];
			c[j][j+i]=9999;
			for(l=j+1;l<=j+i;l++){
				if(c[j][j+i]>(c[j][l-1]+c[l][j+i]))
				  {
					c[j][j+i]=c[j][l-1]+c[l][j+i];
					r[j][j+i]=l;
				  }
			  }
			c[j][j+i]+=w[j][j+i];
		  }
	  }
  }

void print_tab(){
    cout<<"\nOUTPUT : "<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    for(i=0;i<=n;i++){
        cout<<"w"<<i<<i<<" = 0"<<w[i][i]<<"\t";
    }
    cout<<endl;
    for(i=0;i<=n;i++){
        cout<<"c"<<i<<i<<" = 0"<<c[i][i]<<"\t";
    }
    cout<<endl;
    for(i=0;i<=n;i++){
        cout<<"r"<<i<<i<<" = 0"<<r[i][i]<<"\t";
    }
    cout<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    k = 1;
    while(k<=n){
        cout<<"\n-------------------------------------------------------------------------"<<endl;
        for(i=0;j=i+k,i<n,j<=n;i++,j++){
            if(r[i][j]<9)
                cout<<"r"<<i<<j<<" = 0"<<w[i][j]<<"\t";
            else
                cout<<"r"<<i<<j<<" = "<<w[i][j]<<"\t";
        }
        cout<<endl;
        for(i=0;j=i+k,i<n,j<=n;i++,j++){
            if(r[i][j]<9)
                cout<<"r"<<i<<j<<" = 0"<<c[i][j]<<"\t";
            else
                cout<<"r"<<i<<j<<" = "<<c[i][j]<<"\t";
        }
        cout<<endl;
        for(i=0;j=i+k,i<n,j<=n;i++,j++){
            if(r[i][j]<9)
                cout<<"r"<<i<<j<<" = 0"<<r[i][j]<<"\t";
            else
                cout<<"r"<<i<<j<<" = "<<r[i][j]<<"\t";
        }
        cout<<"\n-------------------------------------------------------------------------"<<endl;
        k++;
    }
    cout<<"\n\nOptimal BST is :: ";
	cout<<"\nw[0]["<<n<<"] :: "<<w[0][n];
	cout<<"\nc[0]["<<n<<"] :: "<<c[0][n];
	cout<<"\nr[0]["<<n<<"] :: "<<r[0][n];
    
}

void print(int l, int rr){
    if(l>=rr)
        return;
    if(r[l][r[l][rr]-1]!=0){
        cout<<"\nLeft Child of "<<leaf[r[l][rr]]<<" = "<<leaf[r[l][r[l][rr]-1]];
    }
    if(r[r[l][rr]][rr]!=0){
        cout<<"\nRight Child of "<<leaf[r[l][rr]]<<" = "<<leaf[r[r[l][rr]][rr]];
    }
    print(l,r[l][rr]-1);
    print(r[l][rr],rr);
    return;
}

int main(){
    cout<<"\nEnter Number of Nodes = ";
    cin>>n;
    int i;
    for(i=1;i<=n;i++){
        cout<<"Enter Node Label "<<"for node "<<(i)<<" = ";
        cin>>leaf[i];
    }
    cout<<"\nEnter Probabilities of Successful Search "<<endl;
    for(i=1;i<=n;i++){
        cout<<"p["<<(i)<<"] = ";
        cin>>p[i];
    }
    cout<<"\nEnter Probabilities of Unsuccessful Search "<<endl;
    for(i=0;i<=n;i++){
        cout<<"q["<<(i)<<"] = ";
        cin>>q[i];
    }
    cout<<endl;
    cout<<"p[1:"<<n<<"] = [";
    for(i=0;i<n;i++){
        cout<<p[i]<<" , ";
    }cout<<"]"<<endl;
    cout<<"q[0:"<<n<<"] = [";
    for(i=0;i<=n;i++){
        cout<<q[i]<<" , ";
    }cout<<"]"<<endl;
    OBST();
    print_tab();
    cout<<endl;
    cout<<"\nRoot : "<<leaf[r[0][n]]<<endl;
    print(0,n);

    return 0;
}