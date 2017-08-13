/*********************/
/* Name: Mohimenoul Islam
/* ID: 1430187
/* CSC306 , Section 01 , Autumn 2016
/* Assignment: 06
/* All Permutations of a String
/*********************/
#include<bits/stdc++.h>
using namespace std;

/*void swap(char& a , char& b)
{
    char temp=a;
    a=b;
    b=temp;
}*/

void allStrings (string input, int left , int right, set<string>& all)
{
    static int total=0;
    if(left==right)
        all.insert(input);
    else
    {
        for(int i=left;i<=right;i++)
        {
            swap(input[i],input[left]);
            allStrings (input,left+1,right,all);
        }
    }
}

int main()
{
    set<string>all;
    string input; cout<<"Enter the String: ";getline(cin,input);
    int len = input.length();
    allStrings(input,0,len-1,all);
    for(set<string>::iterator itor=all.begin();itor!=all.end();itor++ )
    {
        cout<<*itor<<"\t";
    }
    cout<<"\nTotal parmutations are: "<<all.size();
}
