/*********************/
/* Name: Mohimenoul Islam
/* ID: 1430187
/* CSC306 , Section 01 , Autumn 2016
/* Assignment: 04
/* Kruskal's Minimum Spanning Tree (stable)
/*********************/
#include<bits/stdc++.h>
using namespace std;

struct Label{
    int parent;
};
struct edge{
    int from,to,cost;
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
void displayMST(vector<edge> mst,vector<edge> cycle,int c)
{
    int total=0;
    int size1=mst.size();
    int size2=cycle.size();
    cout<<"Minimum Spanning Tree for Above Graph Using Kruskal's Algorithm is: (Node No. are in Decimal)\n";
    cout<<"From --> To   : Cost\n";
    cout<<"====================\n";
    for(int i=0;i<size1;i++)
    {
        edge ee=mst.at(i);
        total+=ee.cost;
        cout<<setw(5)<<ee.from+1<<"--> "<<setw(4)<<ee.to+1<<" : "<<ee.cost<<endl;
    }
    cout<<"Total Cost to Form the MST is: "<<total<<endl<<endl<<c<<" Edge(s) is/are Ignored due to Cycle Formation:\n";
    cout<<"From --> To   : Cost\n";
    cout<<"====================\n";
    for(int i=0;i<size2;i++)
    {
        edge ii=cycle.at(i);
        cout<<setw(5)<<ii.from+1<<"--> "<<setw(4)<<ii.to+1<<" : "<<ii.cost<<endl;
    }

}
void kruskalAlgoForMST(int **graph,int node,Label *label)
{
    int** data=graph;
    vector<edge> mst;
    vector<edge> cycle;
    int taken=0,min;
    int u,v,f,t,c=0;
    while(taken<node-1)
    {
        min=INT_MAX;
        for(int i=0;i<node;i++)
        {
            for(int j=0;j<node;j++)
            {
                if(data[i][j]!=0 && data[i][j]!=-1)
                {
                    if(data[i][j]<min)
                    {
                        min=data[i][j];
                        u=f=i; v=t=j;
                    }
                }
            }
        }
        //cout<<min<<endl;
        while(label[u].parent!=-1)
        {
            u=label[u].parent;
        }
        while(label[v].parent!=-1)
        {
            v=label[v].parent;
        }
        if(v!=u)
        {
            taken++;
            edge ee;
            ee.from=u;
            ee.to=v;
            ee.cost=graph[u][v];
            mst.push_back(ee);
            label[t].parent=f;
            data[u][v]=INT_MAX;
            data[v][u]=INT_MAX;
        }
        else
        {
            edge ii;
            ii.from=f;
            ii.to=t;
            ii.cost=graph[f][t];
            cycle.push_back(ii);
            c++;
            data[f][t]=INT_MAX;
            data[t][f]=INT_MAX;
        }
    }
    displayMST(mst,cycle,c);
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
    kruskalAlgoForMST(aMat,node,label);
}
