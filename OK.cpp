#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
int n; //liczba wierzcholkow w grafie

void adjmatrix_gen(int *adj_matrix[]){
int i,j,m=0;
srand(time(NULL));
for (i=0; i<n; i++){
    for (j=0; j<n; j++){
        if(i==j){
        adj_matrix[i][j] = 0;
        }else{
        adj_matrix[i][j] = -1;
        }
    }
}
for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if(adj_matrix[i][j] == -1 && i!=j){
                m = rand()%2;
                adj_matrix[i][j] = m;
                adj_matrix[j][i] = m;
                printf("%d  ",m);
            }else{printf("%d  ",adj_matrix[i][j]);}
        }
        printf("\n");
    }
}

void count_degree(int i,int *adjmatrix[],int *vertex_degree){
int j;
for(j=0; j<n ; j++){
		if ( adjmatrix[i][j] == 1) {
		vertex_degree[i] = vertex_degree[i] + 1;  // ka¿dorazowe wystapienie sasiada zwieksza wartosc
		} //obliczamy stopien wyjsciowy kazdego wierzcholka
}
}

int main()
{
int i,j;
printf("Podaj liczbe wierzcholkow n\n");
scanf("%d",&n);
printf("\n");
int nv, nn, deg; //nv = nr wierzcholka grafu, nn = nr sasiada wierzcholka, deg = stopien wierzcholka
int vertex_color[n]; // tablica okreslajaca numery kolorow kolejnych wierzcholkow. vertex_color[i] - kolor itego wierzcholka
int colornum = 0,colornum2 = 0,colornum3 = 0;
int **adjmatrix;
    adjmatrix = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++) adjmatrix[i] = (int*)malloc(n*sizeof(int)); // macierz sasiedztwa wierzcholkow

bool color[n]; //tablica logiczna dostepnosci kolorow, 0 - kolor niewykorzystany, 1 - kolor zajety
int vertex_tab[n]; //tablica z nr wierzcho³ków grafu
int *vertex_degree; // tablica wskazujaca stopien kazdego wierzcho³ka
vertex_degree = (int*)malloc(n*sizeof(int*));
//tworzenie macierzy sasiedztwa
adjmatrix_gen(adjmatrix);
printf("\n");
//LF COLOR
printf("LF COLOR:\n");
for (i=0; i<n; i++) {
	vertex_tab[i] = 0; //umieszczenie numeru wierzcholka w tablicy vertex_tab
	vertex_degree[i] = 0; //zerujemy stopien wyjsciowy kazdego itego wierzcholka

count_degree(i,adjmatrix,vertex_degree);
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

for (i=0; i<n; i++) vertex_color[i] =  -1;  //brak przypisanego koloru

vertex_color[vertex_tab[0]] = 0;  //pierwszemu wierzcholkowi przypisujemy pierwszy kolor
int y;

for(i=1; i<n; i++)  //przypisanie koloru pozostalym wierzcholkom
{
    //kazdy kolor jest dostepny - dla kazdego wierzcholka tworzymy tablice dostpenych colorow
	for (j=0; j<n; j++)color[j] = 0;

	//kolor sasiada oznaczamy jako zajety
	for (nn=0; nn<n; nn++) {
		if (adjmatrix[vertex_tab[i]][vertex_tab[nn]] == 1) {
			if (vertex_color[vertex_tab[nn]] != -1 )
			{
				y  = vertex_color[vertex_tab[nn]];
				color[y] = 1;
			}
		}
	}
        int z=0;
        //szukanie dostepnego koloru
        while (color[z] == 1)z++;
        vertex_color[vertex_tab[i]] = z;
        if(z>colornum)colornum=z;
}

for(i=0; i<n; i++){
printf(" %d = %d \n",vertex_tab[i],vertex_color[vertex_tab[i]]);
}
printf("Ilosc zuzytych kolorow: %d\n\n",colornum+1);
//GREEDY-COLOR
printf("Greedy COLOR:\n");
for (i=0; i<n; i++) vertex_tab[i] = i;
for (i=0; i<n; i++) vertex_color[i] = -1;  //brak przypisanego koloru
for (i=0; i<n; i++)  //przypisanie koloru wierzcholkom
{
    //kazdy kolor jest dostepny - dla kazdego wierzcholka tworzymy tablice dostpenych colorow
	for (j=0; j<n; j++)color[j] = 0;

	//kolor sasiada oznaczamy jako zajety
	for (nn=0; nn<n; nn++) {
		if (adjmatrix[vertex_tab[i]][vertex_tab[nn]] == 1) {
			if (vertex_color[vertex_tab[nn]] != -1 )
			{
				y  = vertex_color[vertex_tab[nn]];
				color[y] = 1;
			}
		}
	}
        int z=0;
        //szukanie dostepnego koloru
        while (color[z] == 1)z++;
        vertex_color[vertex_tab[i]] = z;
        if(z>colornum2)colornum2=z;
}

for(i=0; i<n; i++){
printf(" %d = %d \n",vertex_tab[i],vertex_color[vertex_tab[i]]);
}
printf("Ilosc zuzytych kolorow: %d\n\n",colornum2+1);
//RS COLOR like a Greedy COLOR
printf("RS COLOR:\n");
bool used[n]; //czy dany wierzcholek zostal wylosowany do tablicy
for (i=0; i<n; i++ ) used[i] =  0;
for (i=0; i<n; i++ ){
    srand(time(NULL));
    j=rand()%n;
    while(used[j]==1)j=rand()%n;
    used[j]=1;
    vertex_tab[i] = j;
}
for (i=0; i<n; i++) vertex_color[i] =  -1;  //brak przypisanego koloru
for (i=0; i<n; i++)  //przypisanie koloru wierzcholkom
{
    //kazdy kolor jest dostepny - dla kazdego wierzcholka tworzymy tablice dostpenych colorow
	for (j=0; j<n; j++)color[j] = 0;

	//kolor sasiada oznaczamy jako zajety
	for (nn=0; nn<n; nn++) {
		if (adjmatrix[vertex_tab[i]][vertex_tab[nn]] == 1) {
			if (vertex_color[vertex_tab[nn]] != -1 )
			{
				y  = vertex_color[vertex_tab[nn]];
				color[y] = 1;
			}
		}
	}
        int z=0;
        //szukanie dostepnego koloru
        while (color[z] == 1)z++;
        vertex_color[vertex_tab[i]] = z;
        if(z>colornum3)colornum3=z;
}

for(i=0; i<n; i++){
printf(" %d = %d \n",vertex_tab[i],vertex_color[vertex_tab[i]]);
}
printf("Ilosc zuzytych kolorow: %d\n\n",colornum3+1);


cout<<"BF COLOR:"<<endl;

int b,bc,*tabkolor;
  unsigned long long licznikprob;         // Licznik prób
  bool test;
 tabkolor = new int [n];
  licznikprob = 0;

  for(i = 0; i < n; i++) tabkolor[i] = 0; // Inicjujemy licznik

  b = 2;                          // Zliczanie rozpoczynamy przy podstawie 2
  bc = 0;                         // Liczba najstarszych cyfr

  while(true)
  {
    if(bc)                        // Kombinację sprawdzamy, gdy zawiera najstarszą cyfrę
    {
      test = true;
      licznikprob++;                      // Zwiększamy liczbę prób
      for(i= 0; i < n; i++)      // Przeglądamy wierzchołki grafu
      {
        for(j=0;j<n;j++) // Przeglądamy sąsiadów wierzchołka v
          if (adjmatrix[i][j]==1 &&i<j)
          {if(tabkolor[i] == tabkolor[j])   // Testujemy pokolorowanie
          {
            test = false;         // Zaznaczamy porażkę
            break;                // Opuszczamy pętlę for
          }
        if(!test) break;   }       // Opuszczamy pętlę for
      }
      if(test) break;             // Kombinacja znaleziona, kończymy pętlę główną
    }

    while(true)                   // Pętla modyfikacji licznika
    {
       for(i = 0; i < n; i++)
       {
         tabkolor[i]++;                 // Zwiększamy cyfrę
         if(tabkolor[i] == b - 1) bc++;
         if(tabkolor[i] < b) break;
         tabkolor[i] = 0;               // Zerujemy cyfrę
         bc--;
       }

       if(i < n) break;           // Wychodzimy z pętli zwiększania licznika
       b++;                       // Licznik się przewinął, zwiększamy bazę
    }
  }


for(i = 0; i < n; i++)
    cout <<  " " << i << " = " << tabkolor[i] << endl;
  cout << "Ilosc zuzytych kolorow: " << b << endl;

return 0;
}
