#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;
  
int max(int a, int b) {
    
    if(a>b)
        return a;
    else return b;
    
}
  

int Bazgashti(int C, int w[], int v[], int i)
{
      
if (i == 0 || C == 0)
    return 0;
  

if (w[i-1] > C)
    return Bazgashti(C, w, v, i-1);
  

else return max( v[i-1] + Bazgashti(C-w[i-1], w, v, i-1),
                Bazgashti(C, w, v, i-1) );
}
int Dynamic(int C,int w[],int v[],int i)
{
    int Dyno[i+1][C+1];
    for(int j=0;j<=i;j++)
    {
        for(int cap=0;cap<=C;cap++)
        {
            if(j==0 || cap==0)
            {
                Dyno[j][cap]=0;
            }
            else if (cap>=w[j-1])
            {
                Dyno[j][cap]=max(v[j-1]+Dyno[j-1][cap-w[j-1]],Dyno[j-1][cap]);

            }
            else
                Dyno[j][cap]=Dyno[j-1][cap];
        }
    }
    return Dyno[i][C];
}
void Merge(int *a,int *v,int *w, int low, int high, int mid)
{
    int i, j, k, temp[high-low+1], temp1[high-low+1], temp2[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;
 
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            temp[k] = a[i];
            temp1[k]=v[i];
            temp2[k]=w[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            temp1[k]=v[j];
            temp2[k]=w[j];
            k++;
            j++;
        }
    }
 
    while (i <= mid)
    {
        temp[k] = a[i];
        temp1[k]=v[i];
        temp2[k]=w[i];
        k++;
        i++;
    }
 
    while (j <= high)
    {
        temp[k] = a[j];
        temp1[k]=v[j];
        temp2[k]=w[j];
        k++;
        j++;
    }
 
 
    for (i = low; i <= high; i++)
    {
        a[i] = temp[i-low];
        v[i]= temp1[i-low];
        w[i]= temp2[i-low];
        
    }
}
 
void MergeSort(int *a,int *v,int *w, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        MergeSort(a,v,w, low, mid);
        MergeSort(a,v,w, mid+1, high);
 
        Merge(a,v,w ,low, high, mid);
    }
}

 int Greedy(int C,int w[], int v[], int i)
{
     int val=0,wei=0;
     int gred[i];
     for(int j=0;j<i;j++)
     {
         gred[j]=v[j]/w[j];
     }
     MergeSort(gred,v,w, 0, i-1);

     for(int j=0;j<i;j++)
     {
         if(C>=(wei+w[j])){
             wei=wei+w[j];
             val=val+v[j];
         }
         
     }
     return val;
    }
int promising(int C,int w[],int v[],int i,int j)
{
    int capacity=C;
    int backtrack[3][i];
    int promis=0;
    for(int j=0;j<i;j++)
    {
        backtrack[1][j]=w[j];
        backtrack[0][j]=v[j];
        backtrack[2][j]=(v[j]/w[j]);

    }
    while(capacity>backtrack[1][j]){
        capacity=capacity-backtrack[1][j];
        promis=promis+backtrack[0][j];
        j++;
    }
    promis=promis+(capacity*backtrack[2][j]);
    return promis;
}
int BackTrack(int C,int w[],int v[],int i){
    int capacity=0;
    int profit = 0,flag=0,flag1=0;
    int item[i];
    int max_profit=0;
    capacity=C;
    int gred[i];
    for(int p=0;p<i;p++)
    {
        gred[p]=v[p]/w[p];
    }
    MergeSort(gred,v,w, 0, i-1);
    
    int j=0;
  while(true)
  {
      
      while(max_profit<(promising(capacity, w, v, i, j)+profit)&&flag==0)
      {
          
          if(capacity>=w[j]){
            
              profit=profit+v[j];
              capacity=capacity-w[j];
              item[j]=1;
          }
          else{
              
              item[j]=0;
          }
          j++;
          if(profit>max_profit)
              {
                  
                  max_profit=profit;
              }
          if(j==i)
          {
              flag=1;
              break;;
          }
      }
      
      
          while(item[j]==0)
          {
              j--;
              if(j==-1)
                  flag1=-1;
                  break;
             
          
      }
      if(flag1==-1){
          break;
          
      }
      else {
          item[j]=0;
         capacity=capacity+w[j];
        profit=profit-v[j];
      }
  }
    return max_profit;
}


int main()
{
    int i,C=50;
    cout<<"how many items do you want to add?";
    cin>>i;
    i=3;
    int v[i];
    int w[i];

        for(int j=0;j<i;j++)
        {
            cout<<"Enter the value of "<<j<<" item:";
            cin>>v[j];
            cout<<"Enter the weight of "<<j<<" item:";
            cin>>w[j];
        }
        
        cout<<"Enter the capacity of Knapsack:";
        cin>>C;
    auto start = high_resolution_clock::now();
    cout<<Bazgashti(C, w, v, i)<<endl;
    auto stop = high_resolution_clock::now();
    auto bazgashti = duration_cast<nanoseconds>(stop - start);
    
     start = high_resolution_clock::now();
    cout<<Greedy(C, w, v, i)<<endl;
     stop = high_resolution_clock::now();
    auto greedy = duration_cast<nanoseconds>(stop - start);
    
    start = high_resolution_clock::now();
    cout<< BackTrack(C,w,v,i)<<endl ;
    stop = high_resolution_clock::now();
   auto Backtrack = duration_cast<nanoseconds>(stop - start);
    
    start = high_resolution_clock::now();

    cout<<Dynamic(C, w, v, i)<<endl;
    stop = high_resolution_clock::now();
    auto dyno = duration_cast<nanoseconds>(stop - start);

   
    cout <<"Duration:   Bazgashti      Greedy       Backtrack      Dynamic" << endl;
    cout<<"              "<<bazgashti.count()<<"         "<<greedy.count()<<"           "<<Backtrack.count()<<"        "<<dyno.count()<<endl;
    return 0;
}


