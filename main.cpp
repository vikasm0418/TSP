#include <iostream>
#include <string>
#include <vector>
#include "bits/stdc++.h"

using namespace std;
int lines=99999;

//find next minimum number
int find_next(vector<vector <int> >& cost,int minimum){
  int low=99999;
  for(int i=0;i<cost.size();i++){
    for(int j=0;j<cost[0].size();j++){
      if(low>cost[i][j] && cost[i][j]>minimum)
        low = cost[i][j];
    }
  }
  return low;
}

bool ans(vector<vector <int> >& cost,int row,int minimum,vector<int>& out,int tot ){
  for(int j=0;j<cost[0].size();j++){
    if(cost[row][j]<=minimum){
      if(tot == cost.size() && j==0)
        return true;
      if(find(out.begin(), out.end(),j)==out.end()){
        out.push_back(j);
        tot++;
        if(!ans(cost,j,minimum,out,tot)){
          out.pop_back();
          tot--;
        }
        else
          return true;
      }
    }
  }
  cout << endl;
  return false;
}

void update(vector<vector <int> >& cost){
  // operation on rows
  int i,j,min,n =cost.size() ;
  for(i=0;i<n;i++)
  {
    min=cost[i][0];
    // finding minimum element in each row
    for(j=0;j<n;j++){
        if(min>cost[i][j])
        min=cost[i][j];
    }
    //subtract the minimum element from each element of the respective rows
    for(j=0;j<n;j++)
      cost[i][j]=cost[i][j]-min;
  }

  // operation on colums
  for(i=0;i<n;i++)
  {
    min=cost[0][i];
    // find the minimum element in each column
    for(j=0;j<n;j++){
      if(min>cost[j][i])
        min=cost[j][i];
    }
    //subtract the minimum element from each element of the respective columns
    if(min>0){
      for(j=0;j<n;j++)
        cost[j][i]=cost[j][i]-min;
    }
  }
}
//to find the number of lines that can cross all the zeros of matrix
int check(vector<vector <int> >& cost,vector<vector <int> >& cross,int *sr,int *sc,int row,int col,int n,int tot){
  // cout << row <<" " << col << " "<< n << " " << tot << endl;
  if(row>=n){

      // cout << tot << " "<< lines;
      // cout << endl;
      // for(int i=0;i<n;i++){
      //   cout << sr[i]<<" ";
      // }
      // cout << endl;
      // cout << endl;
      // for(int i=0;i<n;i++){
      //   cout << sc[i]<<" ";
      // }
      // cout << endl;
      // cout << endl;
          
    if(lines>=tot){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          cross[i][j]=0;
        }
      }
      lines = tot;
      for(int i=0;i<n;i++){
        if(sr[i]){
          for(int j=0;j<n;j++){
            if(cross[i][j]==-1)
              cross[i][j] = 2;
            else
              cross[i][j] = 1;
          }
        }
      }
      for(int i=0;i<n;i++){
        if(sc[i]){
          for(int j=0;j<n;j++){
            if(cross[j][i]==1)
              cross[j][i] = 2;
            else
              cross[j][i] = -1;
          }
        }
      }
    }
    // cout << endl;

    return tot;
  }
  for(int i=row;i<n;i++){
    for(int j=col;j<n;j++){
      if(!cost[i][j] && !sr[i] && !sc[j]){
        sr[i] = 1;
        int val1,val2;
        val1 = check(cost,cross,sr,sc,i+1,0,n,tot+1);
        sr[i] = 0;
        sc[j] = 1;
        if(j==n-1)
          val2 = check(cost,cross,sr,sc,i+1,0,n,tot+1);
        else
          val2 = check(cost,cross,sr,sc,i,j+1,n,tot+1);
        sc[j] = 0;
        return min(val1,val2);
      }  
    }
    col=0;
  }
}

int main()
{
  int i,j,n,a,counter =0;
  cout << "Enter the total number of assignments:"<< endl;
  cin >> n;
  vector<vector<int> > cost(n, vector<int>(n));
  vector<vector<int> > cross(n, vector<int>(n));
  // cost[0][0]=99999;cost[0][1]=5;cost[0][2]=8;cost[0][3]=4;cost[0][4]=5;
  // cost[1][0]=5;cost[1][1]=99999;cost[1][2]=7;cost[1][3]=4;cost[1][4]=5;
  // cost[2][0]=8;cost[2][1]=7;cost[2][2]=99999;cost[2][3]=8;cost[2][4]=6;
  // cost[3][0]=4;cost[3][1]=4;cost[3][2]=8;cost[3][3]=99999;cost[3][4]=8;
  // cost[4][0]=5;cost[4][1]=5;cost[4][2]=6;cost[4][3]=8;cost[4][4]=99999;            
  
  /* Enter the cost matrix*/
  cout << "Enter the cost matrix"<< endl;
  for(i=0;i<n;i++){
     printf("\n");
     for(j=0;j<n;j++){
        cout << "cost["<<i<<"]["<<j<<"] = ";
        cin >> cost[i][j];
      }
  }
  cout << endl;
  
  // Entered cost matrix
  cout << "Cost matrix:"<< endl;
  for(i=0;i<n;i++){
      for(j=0;j<n;j++)
        cout << cost[i][j] << " ";
      cout << endl;
  }
  
  update(cost);
  
  cout << endl;
  cout << "Cost matrix after row & column operation:" << endl;
  for(i=0;i<n;i++){ 
    for(j=0;j<n;j++)
      cout << cost[i][j] << " ";
    cout << endl;
  }
  
  
  loop:;

  int sr[n] = {0},sc[n] = {0};
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      cross[i][j]=0;
    }
  }

  /*Draw minimum number of horizontal and vertical lines to cover all zeros in
  resulting matrix*/
  a = 0;
  a = check(cost,cross, sr, sc,0,0,n,0);

  cout << endl;
  cout << "Minimum lines crossing all the zeroes shown below(2 = intersection point)"<<endl;
  cout << "Minimum no. of lines :"<<a <<endl;
  lines = 99999;

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      cout << cross[i][j] << " ";
    }
    cout << endl;
  }

  /* If minimum number of lines, a is equal to the order of the matrix n then
  assignment can be optimally completed.*/

  if(a==n){
    vector<int> out;
    int minimum = 0;
    out.push_back(0);
    repeat:;
    if(ans(cost,0,minimum,out,1)){
      cout << "Assignments completed!!" << endl;
      cout << "Most Optimal cyclic Path for the Salesman is : " << endl;
      /* Display the order in which assignments will be completed*/
      for(i=0;i<n;i++){
          cout << out[i]+1 << "-->";
      }
      cout << "1";
      cout << endl;
      cout << endl;
      return 0;
    }
    else{
      cout << "No Optimal with current minimum, Let's check for next minimum"<<endl;
      minimum = find_next(cost,minimum);  
      goto repeat;
    }
       
  }
  else{
    int min =99999;
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(!cross[i][j]){
          if(min>cost[i][j]){
            min = cost[i][j];
          }
        } 
      }
    }
    cout << min;
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(cross[i][j]==2){
          cost[i][j] += min; 
        }
        else if(cross[i][j]==0){
          cost[i][j] -= min; 
        } 
      }
    }
  }
  cout << endl;
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
