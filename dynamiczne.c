#include <stdio.h>
#include <stdlib.h>

int C,n;
typedef FILE* plik;
plik dane;

void print_tab(int tab[n+1][C+1],int C, int n){
    int i,j;
for(i=0;i<=n;i++){
    for(j=0;j<=C;j++){
        printf("%d  ",tab[i][j]);
    }
    printf("\n");
    }
    printf("\n");
}

int maximum(int a, int b){
if(a>b){return a;}else
    {return b;}
}

void create_tab(int tab[n+1][C+1], int tab1[n+1][2],int C, int n){
    int i,j;
    for(i=0;i<=C;i++){
        tab[0][i]=0;
    }
    for(i=0;i<=n;i++){
        tab[i][0]=0;
    }
for(i=1;i<=n;i++){
     for(j=1;j<=C;j++){
     if(tab1[i][1]>j){
     tab[i][j]=tab[i-1][j];
     }else{
     tab[i][j]=maximum(tab[i-1][j],tab[i-1][j-tab1[i][1]]+tab1[i][0]);
     }}
}}

void pd(int tab[n+1][C+1],int tab1[n][2]){
    int i,j;
    i=n;
    j=C;
    while(i>0 && j>0){
while(tab[i][j]==tab[i-1][j]){
    i=i-1;
}
printf("%d ",i);
j=j-tab1[i][1];
i=i-1;
}
}


void bf(int tab1[n][2]){


}

int main()
{
    srand(time(NULL));
    int p,w,i;
    dane=fopen("dane.txt","w");
    C=20;
    n=10;
    //fprintf(dane,"%d\n%d\n",C,n);
    for(i=0;i<10000;i++){
    p=rand()%10+1;
    w=rand()%10+1;
        fprintf(dane,"%d %d\n",p,w);
    }
    dane=fopen("dane.txt","r");
    //fscanf(dane,"%d\n",&C);
    //fscanf(dane,"%d\n",&n);
    int tab1[n+1][2];
    for(i=1;i<=n;i++){
    fscanf(dane,"%d ",&tab1[i][0]);
    fscanf(dane,"%d\n",&tab1[i][1]);
    printf("%d %d\n",tab1[i][0],tab1[i][1]);
    }
    printf("\n");
    int tab[n+1][C+1];
    create_tab(tab,tab1,C,n);
    print_tab(tab,C,n);
    pd(tab,tab1);
    bf(tab1);
    fclose(dane);
}
