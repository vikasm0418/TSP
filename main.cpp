#include <iostream>
#include <string>
#include <vector>
#include "bits/stdc++.h"

using namespace std;


//to find the number of lines that can cross all the zeros of matrix
int check(vector<vector <int> >& cost,vector<vector <int> >& m2,int *sr,int *sc,int row,int col,int n,int tot){
  cout << col <<" " << row << " "<< n << " " << tot << endl;
  if(row>=n)
    return tot;
  for(int i=row;i<n;i++){
    for(int j=col;j<n;j++){
      if(!cost[i][j] && !sr[i] && !sc[j]){
        sr[i] = 1;
        int val1,val2;
        val1 = check(cost,m2,sr,sc,i+1,0,n,tot+1);
        sr[i] = 0;
        sc[j] = 1;
        if(j==n-1)
          val2 = check(cost,m2,sr,sc,i+1,0,n,tot+1);
        else
          val2 = check(cost,m2,sr,sc,i,j+1,n,tot+1);
        sc[j] = 0;
        if(val1<val2){
          m2[i][j] = -1;
        }
        else
          m2[i][j] = 1;
        return min(val1,val2);
      }  
    }
    col=0;
  }
}

int main()
{
  int min,l,m,flag[20][20]={0},i,j,k,rf[20],cf[20],n;
  
  int nrz[20],ncz[20],cn,a,noz,nrz1[20],ncz1[20],counter =0;
  cout << "Enter the total number of assignments:"<< endl;
  
  cin >> n;
  vector<vector<int> > cost(n, vector<int>(n));
  vector<vector<int> > m2(n, vector<int>(n));
  cost[0][0]=999;cost[0][1]=4;cost[0][2]=9;cost[0][3]=5;
  cost[1][0]=6;cost[1][1]=999;cost[1][2]=4;cost[1][3]=8;
  cost[2][0]=9;cost[2][1]=4;cost[2][2]=999;cost[2][3]=9;
  cost[3][0]=5;cost[3][1]=8;cost[3][2]=9;cost[3][3]=999;
              
  // /* Enter the cost matrix*/
  // cout << "Enter the cost matrix"<< endl;
  // for(i=0;i<n;i++){
  //    printf("\n");
  //    for(j=0;j<n;j++){
  //       cout << "cost["<<i<<"]["<<j<<"] = ";
  //       cin >> cost[i][j];
  //     }
  // }

  cout << endl;
  
  /* Display the entered cost matrix*/
  cout << "Cost matrix:"<< endl;
  for(i=0;i<n;i++){
      for(j=0;j<n;j++)
        cout << cost[i][j] << " ";
      cout << endl;
  }
  
  /* operation on rows*/
  for(i=0;i<n;i++)
  {
    min=cost[i][0];
    /* find the minmum element in each row*/
    for(j=0;j<n;j++){
        if(min>cost[i][j])
        min=cost[i][j];
    }
    /*subtract the minimum element from each element of the respective rows*/
    for(j=0;j<n;j++)
      cost[i][j]=cost[i][j]-min;
  }

  /* operation on colums*/
  for(i=0;i<n;i++)
  {
    min=cost[0][i];
    /* find the minimum element in each column*/
    for(j=0;j<n;j++){
      if(min>cost[j][i])
        min=cost[j][i];
    }
    /*subtract the minimum element from each element of the respective columns*/
    if(min>0){
      for(j=0;j<n;j++)
        cost[j][i]=cost[j][i]-min;
    }
  }

  cout << endl;
  
  cout << "Cost matrix after row & column operation:" << endl;
  for(i=0;i<n;i++){ 
    for(j=0;j<n;j++)
      cout << cost[i][j] << " ";
    cout << endl;
  }

  loop:;
  int sr[n] = {0},sc[n] = {0};

  /*Draw minimum number of horizontal and vertical lines to cover all zeros in
  resulting matrix*/
  a =0;
  a = check(cost,m2, sr, sc,0,0,n,0);
  for(i=0;i<n;i++){
    sr[i]=0;
    sc[i]=0;
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(m2[i][j]==1){
        sr[i] = 1;
      }
      else if(m2[i][j]==-1){
        sc[i] = -1;
      }
    }
  }

  /* If minimum number of lines, a is equal to the order of the matrix n then
  assignment can be optimally completed.*/

  if(a==n){
    cout << endl;
    cout << "Assignments completed in order!!" << endl;
    /* Display the order in which assignments will be completed*/
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(flag[i][j]==2)
        cout << i+1 << " "<<j+1<<endl;
      }
    }
    exit(0);   
  }
  else{
    int min =999;
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(!sr[i] && !sc[j]){
          if(min>cost[i][j]){
            min = cost[i][j];
          }
        } 
      }
    }

    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(sr[i] && sc[j]){
          cost[i][j] += min; 
        }
        else if(!sr[i] && !sc[j]){
          cost[i][j] -= min; 
        } 
      }
    }
  }
  if (counter < 10){
    counter = counter+1; 
    cout << "Intermediate Matrix: "<<endl;
    for(i=0;i<n;i++){           
      for(j=0;j<n;j++)
        cout << cost[i][j] << " ";
      cout <<endl;
    }
  }
  else{
    cout << "Optimal solution to given problem is not possible" << endl;
    return 0;
  }
  goto loop;
}
