#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;
int n, m, kraw;
int *visited, tofind;

struct list
{
    int value;
    struct list *next;
};
typedef struct list slistEl;

struct list2
{
    int v1;
    int v2;
    struct list2 *next;
};
typedef struct list2 sedgeList;

struct BFSl
{
    struct BFSl *next;
    int value;
};
typedef struct BFSl BFS_list;

void adjmatrix_gen(int n, int *adjmatrix[])     //generowanie macierzy sasiedztwa
{
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if ((((i+j) % 2) == 1) && (i<j))
            {
                adjmatrix[i][j] = 1;         //macierz gornotrojkatna
                m+=1;
            }
            else adjmatrix[i][j] = 0;
        }
    }
}



void adjmatrix_print(int n, int *adjmatrix[])      //wyswietlanie macierzy sasiedztwa
{
    printf("\nMACIERZ SASIEDZTWA: \n");
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%d\t",adjmatrix[i][j]);
        }
        printf("\n");
    }
}

void DFS_adjmatrix(int* adjmatrix[], int w)
{
    visited[w] = 1;
    printf("%d ",w);
    for (i=0; i<n; i++)
    {
        if ((adjmatrix[w][i] == 1) && (visited[i] == 0)) DFS_adjmatrix(adjmatrix, i);
    }
}

void adjList_gen(int n, int* adjlist, int** adjmatrix, int* indeg)      //tworzenie listy sasiedztwa
{
    slistEl *newEl;
    for (i=0; i<n; i++)
    {
        adjlist[i] = NULL;
    }
    for (i=0; i<n; i++)
    {
        for (j=n-1; j>0; j--)
        {
            if (adjmatrix[i][j] == 1)
            {
                newEl = (slistEl*)malloc(sizeof(slistEl));
                newEl->value = j;
                newEl->next = adjlist[i];
                adjlist[i] = newEl;
                indeg[j]++;
            }
        }
    }
}

void adjList_gen2(int* adjlist, int** edgeTab, int* indeg)      //tworzenie listy sasiedztwa
{
    slistEl *newEl;
    for (i=0; i<n; i++)
    {
        adjlist[i] = NULL;
    }
    for (i=0; i<kraw; i++)
    {
                newEl = (slistEl*)malloc(sizeof(slistEl));
                newEl->value = edgeTab[i][1];
                newEl->next = adjlist[edgeTab[i][0]];
                adjlist[edgeTab[i][0]] = newEl;
                indeg[edgeTab[i][1]]++;
    }
}

void adjList_print(int n, int* adjlist)         //wyswietlanie listy sasiedztwa
{
    slistEl *currEl;
    printf("\nLISTA SASIEDZTWA: \n");
    for (i=0; i<n; i++)
    {
        printf("%d | ",i);
        currEl = adjlist[i];
        while(currEl)
        {
            printf("%d ",currEl->value);
            currEl = currEl->next;
        }
        printf("\n");
    }
}

void DFS_adjlist2(int* L)
{
int nS3, S3[n+1], color[n+1];
for(i = 0; i <= n; i++)
  {color[i] = 0;}
int v;
  for( v = 0; v < n; v++)
    if(color[v] == 0)
    {
      tsDFS(v,L,nS3,S3,color);
    }

for(i = nS3 - 1; i >= 0; i--){printf("%d ",S3[i]);}
}

void DFS_adjlist(int* adjlist[], int w)
{
    slistEl *tmp;
    visited[w] = 1;
    printf("%d ",w);
    tmp = adjlist[w];
    while(tmp)
    {
        if (visited[tmp->value] == 0) DFS_adjlist(adjlist, tmp->value);
        tmp = tmp->next;
    }
}

void tsDFS(int v,int* L,int nS3, int* S3, int* color)
{
  color[v] = 1;
  slistEl *p = L[v];
  while(p)
  {
    switch(color[p->value])
    {
      case 1  : return;
      case 0  : tsDFS(p->value,L,nS3,S3,color);
                     break;
    }
    p = p->next;
  }
  color[v] = 2;
  S3[nS3++] = v;
}

void BFS(int* L,int* indeg)
{
// stos na wierzcholki o stw=0

  int nS1 = 0, S1[n + 1];

// szukamy tych ze stw=0
  int v;
  for(v = 0; v < n; v++) if(!indeg[v]) S1[nS1++] = v;

// stos na posortowane wierzcholki

  int nS2 = 0, S2[n + 1];

// sortowanie

  while(nS1)
  {
    int v = S1[--nS1];
    slistEl *p = L[v];
    while(p)
    {
      if(!(--indeg[p->value])) S1[nS1++] = p->value;
      p = p->next;
    }
    S2[nS2++] = v;
  }
  for( i = 0; i < n; i++){printf("%d ",S2[i]);}
}

void edgeList_gen(int n, int **edgeTab, int **adjmatrix)
{
    kraw = 0;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (adjmatrix[i][j] == 1)
            {
                edgeTab[kraw][0] = i;
                edgeTab[kraw][1] = j;
                kraw++;
            }
        }
    }
}

void edgeList_print(int **edgeTab)        //wyswietlanie listy krawedzi
{
    printf("\nLISTA KRAWEDZI: \n");
    for (i=0; i<m; i++)
    {
        printf("%d->%d\n",edgeTab[i][0],edgeTab[i][1]);
    }
}

void DFS_edgelist(int **edgeTab, int w)
{
    visited[edgeTab[w][0]] = 1;
    printf("%d ",edgeTab[w][0]);
    tofind = edgeTab[w][1];
    for (i=0; i<m; i++)
    {
        if ((edgeTab[i][0] == tofind) && (visited[tofind] == 0)) DFS_edgelist(edgeTab, i);
    }
    if(visited[tofind] == 0)
    {
        printf("%d ",tofind);
        visited[tofind] = 1;
    }
}

int main()
{
    srand(time(NULL));
    printf("Podaj liczbe wierzcholkow: \n");
    scanf("%d",&n);
    visited = (int*)malloc(n*sizeof(int));
    m = 0;

    //INICJALIZACJA TABLICY n x n - macierz sasiedztwa
    int **adjmatrix;
    adjmatrix = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++)
    {
        adjmatrix[i] = (int*)malloc(n*sizeof(int));
    }

    //MACIERZ SASIEDZTWA
    adjmatrix_gen(n, adjmatrix);
    adjmatrix_print(n, adjmatrix);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----DFS----\n");
    DFS_adjmatrix(adjmatrix, 0);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("\n----BFS----\n");
    slistEl ** adjlist2;
    adjlist2 = (slistEl*)malloc(n*sizeof(slistEl));
    int indeg2[n+1];
    for(i = 0; i <= n; i++)indeg2[i] = 0;
    adjList_gen(n, adjlist2, adjmatrix, indeg2);
    BFS(adjlist2, indeg2);
    printf("\n-----------\n");

    //INICJALIZACJA - lista sasiedztwa
    slistEl ** adjlist;
    slistEl *newEl, *toDel, *currEl;
    adjlist = (slistEl*)malloc(n*sizeof(slistEl));
    int indeg[n+1];
     for(i = 0; i <= n; i++)indeg[i] = 0;

    //LISTA SASIEDZTWA
    adjList_gen(n, adjlist, adjmatrix, indeg);
    adjList_print(n, adjlist);

    printf("----DFS----\n");
    for (i=0; i<n; i++) visited[i] = 0;
    DFS_adjlist(adjlist, 0);

    printf("\n----BFS----\n");
    BFS(adjlist, indeg);
    printf("\n-----------\n");

    //INICJALIZACJA -lista krawedzi
    int edgeTab[m];
    for (i=0; i<m; i++)
    {
        edgeTab[i] = (int*)malloc(2*sizeof(int));
    }

    //LISTA KRAWEDZI
    edgeList_gen(n, edgeTab, adjmatrix);
    edgeList_print(edgeTab);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----DFS----\n");
    DFS_edgelist(edgeTab, 0);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("\n----BFS----\n");
    slistEl ** adjlist3;
    adjlist3 = (slistEl*)malloc(n*sizeof(slistEl));
    int indeg3[n+1];
    for(i = 0; i <= n; i++)indeg3[i] = 0;
    adjList_gen2(adjlist3, edgeTab, indeg3);
    BFS(adjlist3, indeg3);
    printf("\n-----------\n");

    //ZWALNIANIE PAMIECI
    for (i=0; i<n; i++) free(adjmatrix[i]);
    free(adjmatrix);

    for (i=0; i<n; i++)
    {
        currEl = adjlist[i];
        while(currEl)
        {
            toDel = currEl;
            currEl = currEl->next;
            free(toDel);
        }
    }

    /*
    currEE = head;
    sedgeList *tmp;
    while (currEE)
    {
        tmp = currEE->next;
        free(currEE);
        currEE = tmp;
    }*/

}
