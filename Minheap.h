#include <stdio.h>
#include <stdlib.h>
typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    int *Elements;
    int *Index;
    int Capacity;
    int Size;
};
typedef struct {
    int Min;
    int Sec;
    int Path;
    int SecPath;
    int InQueue;
}Node;
Node* node;
PriorityQueue Initialize( int MaxElements ){ 
     PriorityQueue  H; 
     H = (PriorityQueue)malloc( sizeof ( struct HeapStruct ) ); 
     H->Elements = (int *)malloc(( MaxElements + 1 ) * sizeof(int)); 
     H->Index = (int *)malloc(( MaxElements + 1 ) * sizeof(int)); 
     H->Capacity = MaxElements; 
     H->Size = 0; 
     H->Elements[0] = -1; 
     return  H; 
}
void PercolateUp( int p, PriorityQueue H ){
    int num=p;
    int temp;
    while(H->Elements[num]<H->Elements[num/2]){
        temp=H->Elements[num];
        H->Elements[num]=H->Elements[num/2];
        H->Elements[num/2]=temp;
        temp=H->Index[num];
        H->Index[num]=H->Index[num/2];
        H->Index[num/2]=temp;
        num=num/2;
    }
}
int min(int a,int b,PriorityQueue H ){
    if(b>H->Size){
        return a;
    }
    if(H->Elements[a]<H->Elements[b]){
        return a;
    }
    return b;
}
void PercolateDown( int p, PriorityQueue H ){
    int num=p;
    int temp;
    while((2*num<=H->Size)&&H->Elements[num]>H->Elements[min(2*num,2*num+1,H)]){
        int minnum=min(2*num,2*num+1,H);
        temp=H->Elements[num];
        H->Elements[num]=H->Elements[minnum];
        H->Elements[minnum]=temp;
        temp=H->Index[num];
        H->Index[num]=H->Index[minnum];
        H->Index[minnum]=temp;
        num=minnum;
        // printf("%d %d\n",num,H->Elements[num]);
    }
}
void EnQueue( int X, PriorityQueue H ,int Ind) 
{
    if(!node[Ind].InQueue){
        Insert(X,H,Ind);
        node[Ind].InQueue=1;
    }
}

void Insert( int X, PriorityQueue H ,int Ind) 
{
    // printf("Insert:%d Index:%d\n",X,Ind);
    int p = ++H->Size;
    H->Elements[p] = X;
    H->Index[p] = Ind;
    
    PercolateUp( p, H );
}

int DeleteMin( PriorityQueue H ) 
{ 

    int MinElement = H->Index[1];
    H->Index[1] = H->Index[H->Size];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    node[MinElement].InQueue=0;
    // printf("Del:%d",MinElement);

    return MinElement;
}
// int main()
// {
//     int n, i, op, X,m=0;
//     PriorityQueue H;

//     scanf("%d", &n);
//     H = Initialize(n);
//     for ( i=0; i<n; i++ ) {
//         scanf("%d", &op);
//         switch( op ) {
//         case 1:
//             scanf("%d", &X);
//             Insert(X, H,++m);
//             break;
//         case 0:
//             printf("%d ", DeleteMin(H));
//             break;
//         }
//     }
//     printf("\nInside H:");
//     for ( i=1; i<=H->Size; i++ )
//         printf(" %d", H->Elements[i]);
//     return 0;
// }