#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include"Minheap.h"
int add(int num1,int num2){
    if(num1==INT_MAX||num2==INT_MAX){
        return INT_MAX;
    }
    return num1+num2;
}
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    node=(Node*)malloc(sizeof(Node)*(m+1));
    for(int i=1;i<=m;i++){
        node[i].Min=node[i].Sec=INT_MAX;
        node[i].InQueue=node[i].Path=node[i].SecPath=node[i].isCircle=0;
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

    node[1].Min=node[1].SecPath=node[1].Path=0;
    PriorityQueue H = Initialize(m);

    Insert(0,H,1);
    while(H->Size){
        int Vertex=DeleteMin(H);
        for(int i=1;i<=m;i++){
                int sum=add(node[Vertex].Min,Edge[i][Vertex]);
                if(sum<node[i].Min){
                    node[i].Sec=node[i].Min;
                    node[i].Min=sum;
                    node[i].SecPath=node[i].Path;
                    node[i].Path=Vertex;
                    node[i].isCircle=0;
                    EnQueue(node[i].Min,H,i);
                } else if(sum!=node[i].Min&&sum<node[i].Sec){
                    node[i].Sec=sum;
                    node[i].SecPath=Vertex;
                    node[i].isCircle=0;
                    EnQueue(node[i].Min,H,i);
                } 
                if(Vertex!=i&&add(add(sum,Edge[i][Vertex]),Edge[i][Vertex])<node[i].Sec){
                    node[i].Sec=add(add(sum,Edge[i][Vertex]),Edge[i][Vertex]);
                    node[i].SecPath=Vertex;
                    node[i].isCircle=1;
                    printf("%d %d Circle!\n",Vertex,i);
                    EnQueue(node[i].Min,H,i);
                }
        }
    }
        for(int i=1;i<=m;i++){
            printf("%d %d %d %d %d\n",i,node[i].Min,node[i].Sec,node[i].Path,node[i].SecPath);
        }

    // for(int i=0;i<m;i++)
    printf("%d ",node[m].Sec);
    int Path[m+3],p=0,q=m;
        Path[p++]=q;
        q=node[q].SecPath;
    while(q){
        Path[p++]=q;
        q=node[q].Path;
    }
    while(p>1){
        if(node[--p].isCircle){
            printf("%d %d ",Path[p],Path[node[p].SecPath]);
        }
        printf("%d ",Path[p]);
    }
        printf("%d ",Path[--p]);

}