/*********************/
/* Name: Mohimenoul Islam
/* ID: 1430187
/* CSC306 , Section 01 , Autumn 2016
/* Assignment: 03
/* Prim's Minimum Spanning Tree (stable)
/*********************/
#include<bits/stdc++.h>
using namespace std;

struct Label{
    int cost,parent;
    bool included;
};

void displayArray(int** data,int node)
{
    for(int i=0;i<node;i++)
    {
        for(int j=0;j<node;j++)
            cout<<left<<setw(4)<<data[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void populateAdMat(int** &data,int node,int par,Label* &label)
{
    srand(time(0));
    int x,ones,counter=0;vector<int>my;
    label=new Label[node];
    int conn=(node*node-node)/2;
    ones=((conn*par)/100)+1;
    for(int i=0;i<conn;i++)
    {
        if(i<ones) my.push_back(1);
        else my.push_back(0);
    }
    random_shuffle(my.begin(),my.end());
    /*  // view random connections
    for(int i=0;i<conn;i++)
    {
        cout<<my.at(i)<<" ";

    }*/
    data=new int* [node];
    for(int i=0;i<node;i++)
        data[i]=new int [node];
    for(int i=0;i<node;i++)
    {
        label[i].cost=-1;
        label[i].included=false;
        label[i].parent=-1;
        for(int j=i;j<node;j++)
        {
            if(i==j) data[i][j]=1;
            else{
                x=my.at(counter++);
                data[i][j]=x;
                data[j][i]=x;
            }
        }
    }
}
void assignWeight(int **data,int node)
{
    srand(time(0));
    int x=0;
    for(int i=0;i<node;i++)
    {
        for(int j=i;j<node;j++)
        {
            if(i==j)
            {
                data[i][j]=0;
                continue;
            }
            else if(data[i][j]==1)
            {
                x=rand()%100;
                data[i][j]=x;
                data[j][i]=x;
            }
            else
            {
                data[i][j]=-1;
                data[j][i]=-1;
            }
        }
    }
}
void displayMST(queue<int>res,Label *label)
{
    int total=0;
    int c=0;
    cout<<"Minimum Spanning Tree for Above Graph Using Prim's Algorithm is: (Node No. are in Decimal)\n";
    cout<<"From --> To   : Cost\n";
    cout<<"====================\n";
    while(!res.empty())
    {
        int x=res.front();
        res.pop();
        if(c==0){c++;continue;}
        else cout<<setw(4)<<label[x].parent+1<<" --> "<<setw(4)<<x+1<< " : "<<setw(4)<<label[x].cost<<endl;
        total+=label[x].cost;
    }
    cout<<"Minimum Cost for MST is: "<<total<<endl;
}
int smallestNode(int **data,int node,int* min,Label *label)
{
    int minimum=INT_MAX;
    int vertex;
    queue<int> visited;
    for(int i=0;i<node;i++)
        if(label[i].included==true)
            visited.push(i);

    while(!visited.empty())
    {
        vertex=visited.front();
        visited.pop();
        for(int i=0;i<node;i++)
        {
            if(label[i].included==false && data[vertex][i]!=0 && data[vertex][i]<minimum)
            {
                if(data[vertex][i]!=-1)
                {
                    minimum=data[vertex][i];
                    min[0]=vertex;
                    min[1]=i;
                }
            }
        }
    }
}
void primAlgoForMST(int **data,int node,Label *label)
{
    int min[2];
    queue<int> res;
    label[0].cost=0;
    label[0].parent=-1;
    label[0].included=true;
    res.push(0);
    for(int i=0;i<node-1;i++)
    {
        smallestNode(data,node,min,label);
        label[min[1]].included=true;
        label[min[1]].parent=min[0];
        label[min[1]].cost=data[min[0]][min[1]];
        res.push(min[1]);
        min[0]=0;min[1]=0;
    }
    displayMST(res,label);
}

int main()
{
    int **aMat, node, par;
    Label *label;
    cout<<"Number of Nodes: ";cin>>node;
    cout<<"Connectivity Percentage(at least): ";cin>>par;
    populateAdMat(aMat,node,par,label);
    assignWeight(aMat,node);
    cout<<"Adjacency Matrix for graph is: \n\n";
    displayArray(aMat,node);
    primAlgoForMST(aMat,node,label);
}
