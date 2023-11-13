//
// Created by leeyoungjun on 2023/11/13.
//
#include <stdio.h>

#define MAX_NODES 10
#define INF 10000
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
	int n;
	int cost[MAX_NODES][MAX_NODES];
} GraphType;

GraphType G = { 6,
{{0,5,3,7,INF,INF},
{5,0,4,INF,7,9},
{3,4,0,3,8,INF},
{7,INF,3,0,4,INF},
{INF,7,8,4,0,2},
{INF,9,INF,INF,2}}
};


int distance[MAX_NODES];
int found[MAX_NODES];

void print_status(GraphType* g, int step){

    printf("STEP %d\n",step);
    printf("         distance: ");
    for(int i=0;i<g->n;i++){
        if(distance[i]==INF){
            printf("* ");
        } else {
            printf("%d ",distance[i]);
        }
    }
    printf("\n");
    printf("         found: ");
    for(int i=0;i<g->n;i++){
        printf("%d ",found[i]);
    }
    printf("\n");

}
int choose(int distance[],int n,int found[]){
    //found에 false인 정점 중에, 최소 distance를 가지는 것 u
    int ans = INF;
    int count = 0;
    for(int i =0;i<n;i++){
        if(found[i]==FALSE){
            if(distance[i]!=0 && ans>distance[i]){
                count = i;
                ans = distance[count];
            }

        }
    }
    found[count] = TRUE;
    return count;
}

void shortest_path(GraphType* g, int start_node){
    for(int i = 0;i<g->n;i++){
        distance[i] = g->cost[start_node][i];
    }
    int step = 0;

    while(step<g->n){
        print_status(g,step);
        int u = choose(distance,g->n,found);
        //s in u
        printf("cho : %d\n",u);
        for(int i = 0;i<g->n;i++){
            if(distance[u]+g->cost[u][i] < distance[i]){
                distance[i] = distance[u]+g->cost[u][i];
            }
        }

        step++;
    }
}

int main(void){
    int start_node_index = 0;
    GraphType G2 = {4,
                    {{0,1,20,23},
                     {1,0,10,INF},
                     {20,10,0,18},
                     {23,INF,18,0}}
    };
    //shortest_path(&G2,start_node_index);

    GraphType G3 = {6,
                    {{0,5,3,7,INF,INF},
                    {5,0,4,INF,7,9},
                     {3,4,0,3,8,INF},
                     {7,INF,3,4,INF},
                     {INF,7,8,4,2},
                     {INF,9,INF,INF,2}}};
    //shortest_path(&G3,start_node_index);

    GraphType G4 = {7,
                    {{0,7,INF,INF,3,10,INF},
                     {7,0,4,10,2,6,INF},
                     {INF,4,0,2,INF,INF,INF},
                     {INF,10,2,0,11,9,4},
                     {3,2,INF,11,0,INF,5},
                     {10,6,INF,9,INF,0,INF},
                     {INF,INF,INF,4,5,INF,0}}};

    shortest_path(&G4,start_node_index);
    return 0;
}