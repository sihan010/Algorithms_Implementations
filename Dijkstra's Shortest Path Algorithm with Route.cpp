/*********************/
/* Name: Mohimenoul Islam
/* ID: 1430187
/* CSC306 , Section 01 , Autumn 2016
/* Assignment: 02
/* Dijkstra's Shortest Path Algorithm with Route (stable)
/*********************/
#include<bits/stdc++.h>
using namespace std;

struct Label{
    int dis,vis,pre;
};

void displayArray(int** data,int node)
{
    for(int i=0;i<node;i++)
    {
        for(int j=0;j<node;j++)
            cout<<left<<setw(4)<<data[i][j]<<" ";
        cout<<endl;
    }
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
        label[i].dis=-1;
        label[i].vis=0;
        label[i].pre=-1;
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
                x=rand()%1000;
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
void dijkstra(int **data,Label *label,int node, int source,int dest)
{
    queue<int>QQ;
    QQ.push(source);
    label[source].dis=0;
    label[source].pre=source;
    while(!QQ.empty())
    {
        int ss=QQ.front();
        QQ.pop();
        if(ss==dest) break;
        for(int i=0;i<node;i++)
        {
            if(data[ss][i]!=-1 && data[ss][i]!=0 && label[i].vis==0)
            {
                if(label[i].dis==-1 || (label[i].dis>(label[ss].dis+data[ss][i])))
                {
                    label[i].dis=label[ss].dis+data[ss][i];
                    label[i].pre=ss;
                    QQ.push(i);
                }
            }
        }
        label[ss].vis=1;
    }
}
void dispResult(Label *label,int source,int dest)
{
    cout<<"\nResult:\n";
    if(label[dest].dis==-1)
        cout<<"Destination Not Reachable";
    else{
        cout<<"Minimum Cost to Reach "<<dest+1<<"th Node from "<<source+1<<"th Node is: "<<label[dest].dis<<endl;
        stack<int>SS;
        int parent=label[dest].pre;
        SS.push(parent);
        while(parent!=source)
        {
            parent=label[parent].pre;
            SS.push(parent);
        }
        cout<<"Route is: ";
        while(!SS.empty())
        {
            cout<<SS.top()+1<<" --> ";
            SS.pop();
        }
        cout<<dest+1<<endl;
    }
}

int main()
{
    int **aMat, node, par, source, des;
    Label *label;
    cout<<"Number of Nodes: ";cin>>node;
    cout<<"Connectivity Percentage(at least): ";cin>>par;
    cout<<"Source Node(in decimal): ";cin>>source;
    cout<<"Destination Node(in decimal): ";cin>>des;
    populateAdMat(aMat,node,par,label);
    assignWeight(aMat,node);
    cout<<"Adjacency Matrix for graph is: \n";
    displayArray(aMat,node);
    dijkstra(aMat,label,node,source-1,des-1);
    dispResult(label,source-1,des-1);
}
