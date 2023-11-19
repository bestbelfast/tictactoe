#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

typedef struct {
    int Known;
    int Min;
    int Sec;
    int Path;
    int SecPath;
}Node;
int add(int num1,int num2){
    if(num1==INT_MAX||num2==INT_MAX){
        return INT_MAX;
    }
    return num1+num2;
}
int FindMin(Node * node,int size){
    int min=INT_MAX;
    int num=INT_MAX;
    for(int i=1;i<=size;i++){
        if(node[i].Known==0&&node[i].Min<min){
            num=node[i].Min;
            min=i;
        }
    }
    return min;
}
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    Node* node=(Node*)malloc(sizeof(Node)*(m+1));
    for(int i=1;i<=m;i++){
        node[i].Min=node[i].Sec=INT_MAX;
        node[i].Known=node[i].Path=node[i].SecPath=0;
    }
    int Edge[m+1][m+1],A,B,D;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            Edge[i][j]=INT_MAX;
        }
    }
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&A,&B,&D);
        Edge[A][B]=Edge[B][A]=D;
    }
    node[1].Min=node[1].Sec=node[1].Path=0;
    while(1){
        int Vertex=FindMin(node,m);
        if(Vertex==INT_MAX){
            break;
        }
        node[Vertex].Known=1;
        for(int i=1;i<=m;i++){
            if(!node[i].Known){
                int sum=add(node[Vertex].Min,Edge[i][Vertex]);
                if(sum<node[i].Min){
                    node[i].Sec=node[i].Min;
                    node[i].Min=sum;
                    node[i].SecPath=node[i].Path;
                    node[i].Path=Vertex;
                } else if(sum!=node[i].Min&&sum<node[i].Sec){
                    node[i].Sec=sum;
                    node[i].SecPath=Vertex;
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        printf("%d %d %d %d %d\n",i,node[i].SecPath,node[i].Path,node[i].Sec,node[i].Min);
        
    }
    printf("%d ",node[m].Sec);
    int Path[m],p=0,q=m;
        Path[p++]=q;
        q=node[q].SecPath;
    while(q){
        Path[p++]=q;
        q=node[q].Path;
    }
    while(p){
        printf("%d ",Path[--p]);
    }
}