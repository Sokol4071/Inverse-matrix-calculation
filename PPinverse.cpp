#include <iostream>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
using namespace std;
#define N 11
void getCfactor(int M[N][N], int t[N][N], int p, int q, int n) {
   int i = 0, j = 0;

   for (int r= 0; r< n; r++) {
      for (int c = 0; c< n; c++) //Copy only those elements which are not in given row r and column c: {
         if (r != p && c != q) { t[i][j++] = M[r][c]; //If row is filled increase r index and reset c index
            if (j == n - 1) {
               j = 0; i++;
            }
         }
      }
   }

int DET(int M[N][N], int n) //to find determinant
{
   int D = 0;
   if (n == 1)
      return M[0][0];
   int t[N][N]; //store cofactors
   int s = 1; //store sign multiplier //To Iterate each element of first row

   for(int f = 0; f < n; f++) {
      //For Getting Cofactor of M[0][f] dodo getCfactor(M, t, 0, f, n);
      getCfactor(M, t, 0, f, n);
      D += s * M[0][f] * DET(t, n - 1);
      s = -s;
   }

   return D;
}
void ADJ(int M[N][N],int adj[N][N])
//to find adjoint matrix
{
   if (N == 1) {
      adj[0][0] = 1; return;
   }
   int s = 1,
   t[N][N];
   #pragma omp parallel for
   for (int i=0; i<N; i++) {
      for (int j=0; j<N; j++) {
         //To get cofactor of M[i][j]
         getCfactor(M, t, i, j, N);
         s = ((i+j)%2==0)? 1: -1; //sign of adj[j][i] positive if sum of row and column indexes is even.
         adj[j][i] = (s)*(DET(t, N-1)); //Interchange rows and columns to get the transpose of the cofactor matrix
      }
   }

}
bool INV(int M[N][N], float inv[N][N]) {
   int det = DET(M, N);
   if (det == 0) {
      cout << "can't find its inverse";
      return false;
   }

   int adj[N][N]; ADJ(M, adj);
#pragma omp parallel for
   for (int i=0; i<N; i++) for (int j=0; j<N; j++) inv[i][j] = adj[i][j]/float(det);
   return true;
}
template<class T> void print(T A[N][N]) //print the matrix.
{
   for (int i=0; i<N; i++) { for (int j=0; j<N; j++) cout << A[i][j] << " "; cout << endl; }
}
int main() {
    //srand(time(0));

     omp_set_num_threads(2);
   cout<<omp_get_num_procs();
   int ID=omp_get_thread_num();

int M[N][N],i,j;

 for( int i = 0; i < N; ++i)
  {for( int j = 0;  j < N; ++j)
     {M[i][j] = rand();}
  }

   float inv[N][N];
   //cout<<r;
   //cout << "\n"<<"\nInput matrix is :\n"; print(M);
   cout << "\nThe Inverse is :\n"; if (INV(M, inv)) cout<<"Matrix found";


   return 0;

}
