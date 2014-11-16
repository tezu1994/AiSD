#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
int n; //liczba wierzcholkow w grafie
printf("podaj liczbe wierzcholkow n\n");
scanf("%d",&n);
int nv; //nr wierzcholka grafu
int nn; //nr sasiada wierzcholka
int deg; // stopien wierzcholka
int vertex_color[n]; // tablica okreslajaca numery kolorow kolejnych wierzcholkow. vertex_color[i] - kolor itego wierzcholka
int adj_matrix[n][n] ; // macierz sasiedztwa wierzcholkow
bool color[n]; //tablica logiczna dostepnosci kolorow, 0 - kolor niewykorzystany, 1 - kolor zajety
int vertex_tab[n]; //tablica z nr wierzcho³ków grafu
int vertex_degree[n]; // tablica wskazujaca stopien kazdego wierzcho³ka
int i,j,m=0;
//tworzenie macierzy sasiedztwa
srand(time(NULL));
for (i=0; i<n; i++){
    for (j=0; j<n; j++){
            if(i==j){
                adj_matrix[i][j] = 0;
            }else{
        adj_matrix[i][j] = -1;
    }}
}
for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if(adj_matrix[i][j] == -1 && i!=j){
                m= rand()%2;
                adj_matrix[i][j] = m;
                adj_matrix[j][i] = m;
                printf("%d  ",m);
            }else{
            printf("%d  ",adj_matrix[i][j]);
            }
        }
        printf("\n");
    }

//dla ka¿dego wierzcholka
for ( i = 0; i< n; i++ ) {

	vertex_tab[i] = 0; //umieszczenie numeru wierzcholka w tablicy vertex_tab
	vertex_degree[i] = 0; //zerujemy stopien wyjsciowy kazdego itego wierzcholka

	//count_degree
for( j = 0; j < n ; j++){
		if ( adj_matrix[i][j] == 1) {
		vertex_degree[i] = vertex_degree[i] + 1;  // ka¿dorazowe wystapienie sasiada zwieksza wartosc
		} //obliczamy stopien wyjsciowy kazdego wierzcholka
}
	//przypisujemy do zmiennej deg stopien wierzcholka i,
	deg = vertex_degree[i];
	int x = i;

	//szukamy pozycji dla wierzcholka w posortowanej tablicy
	while ( (x>0) && (vertex_degree[x-1] < deg)) {
		vertex_degree[x] = vertex_degree[x-1];
		vertex_tab[x]=vertex_tab[x-1];
		x = x-1; 	//cofamy sie o jedna pozycje
	}
	//jezeli poprzedzajace elementy sa wieksze to:
	vertex_degree[x] = deg;
	vertex_tab[x] = i;

}
//brak przypisanego koloru
for (i = 0 ; i < n ; i++ )
{
	vertex_color[i] =  -1;
}

//pierwszemu wierzcho³kowi przypisujemy pierwszy kolor
vertex_color[vertex_tab[0]] = 0;
int y;

//przypisanie koloru pozostalym wierzcholkom
for( i = 1; i < n; i++)
{
	//kazdy kolor jest dostepny - dla kazdego wierzcholka tworzymy tablice dostpenych colorow
	for ( j = 0; j < n; j++)
	{
		color[j] = 0;
	}
	//kolor sasiada oznaczamy jako zajety
	for ( nn = 0; nn < n ; nn++) {
		if (adj_matrix[i][nn] == 1) {
			if (vertex_color[vertex_tab[nn]] != -1 )
			{
				y  = vertex_color[vertex_tab[nn]];
				color[y] = 1;
			}

	int z = 0;
	//szukanie dostepnego koloru
	while (color[z] == 1){z++;}
	vertex_color[vertex_tab[i]] = z;
	}
    }
}


for(i=0;i<n;i++){
    printf("%d %d = %d \n",vertex_degree[i],vertex_tab[i],vertex_color[vertex_tab[i]]);
}

return 0;
}