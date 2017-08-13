/*********************/
/* Name: Mohimenoul Islam
/* ID: 1430187
/* CSC306 , Section 01 , Autumn 2016
/* Assignment: 05
/* Money Change with Minimum Currency
/*********************/
#include<bits/stdc++.h>
using namespace std;

void takeCurrency(int c,int* &curr)
{
    curr=new int[c];
    for(int i=0;i<c;i++)
    {
        cout<<i+1<<"th currency: ";
        cin>>curr[i];
    }
}
void allocateMemory(int* &minimum,int* &sol,int n)
{
    minimum=new int[n+1];
    sol=new int[n+1];
}
void calculate(int* minimum,int* sol,int* curr,int c,int n)
{
    int min,coin;
    minimum[0]=0;
    sol[0]=0;
    for(int p=1;p<=n;p++){
         min=INT_MAX; coin=0;
         for(int i=0;i<c;i++){
            if(curr[i]<=p){
                if(1+minimum[p-curr[i]]<min){
                    min=1+minimum[p-curr[i]];
                    coin=i+1;
                }
            }
         }
        minimum[p]=min;
        sol[p]=coin;
    }
}
void displayResult(int* sol,int* curr,int n,int min)
{
    int counter=1;
    cout<<"Result:\nMinimum currency needed to give change: "<<min<<endl;
    cout<<"Change with minimum currency is: ";
    while(n>0){
        if(counter<min){
            cout<<curr[sol[n]-1]<<" + ";
            n=n-curr[sol[n]-1]; counter++;
        }
        else{
            cout<<curr[sol[n]-1];
            n=n-curr[sol[n]-1]; counter++;
        }
    }
}

int main()
{
    int currency,n, *curr,*minimum,*sol;
    cout<<"Total different currencies: ";cin>>currency;
    takeCurrency(currency,curr);
    cout<<"Amount to be changed: ";cin>>n;
    allocateMemory(minimum,sol,n);
    calculate(minimum,sol,curr,currency,n);
    displayResult(sol,curr,n,minimum[n]);
    /*for(int i=0;i<n+1;i++)
        cout<<minimum[i]<<" ";
        cout<<endl;
    for(int i=0;i<n+1;i++)
        cout<<sol[i]<<" ";*/

}
