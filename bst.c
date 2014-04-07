
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,size,n;

struct bst
{
    struct bst *left;
    struct bst *right;
    int val, bf;
};
typedef struct bst bstNode;

void losuj(int *tab)
{
    srand(time(NULL));
    int i,tmp,random;
    for (i=0; i<size; i++) tab[i] = i;
    for (i=size-1; i>0; i--)
    {
        random = rand()%i;
        tmp = tab[random];
        tab[random] = tab[i];
        tab[i] = tmp;
    }
}

void wyswietl(int *tab)
{
    int i;
    for (i=0; i<(int)size; i++) printf("%d\t",tab[i]);
}

/////////////////BST///////////////

bstNode *newNode(int value)  /////tworzenie nowego wezla
{
    bstNode *node = (bstNode*) malloc(sizeof(bstNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bstNode*  searchNode(bstNode *wezel, int wartosc)
{
 if (wezel == NULL || wartosc == wezel->val)
          return wezel;

 if (wartosc < wezel->val)
          return searchNode(wezel->left, wartosc);
 else
          return searchNode(wezel->right, wartosc);
}

void insertBST(bstNode **root, int value)
{
    if (*root == NULL)
    {
        bstNode *toInsert = newNode(value);
        *root = toInsert;
        return;
    }
    bstNode *curr;
    curr = *root;
    if (value <= curr->val)
    {
        if (curr->left == NULL)
        {
            bstNode *toInsert = newNode(value);
            curr->left = toInsert;
        }
        else
        {
            curr = curr->left;
            insertBST(&curr, value);
        }
    }
    else
    {
        if (curr->right == NULL)
        {
            bstNode *toInsert = newNode(value);
            curr->right = toInsert;
        }
        else
        {
            curr = curr->right;
            insertBST(&curr, value);
        }
    }
}

void deleteBST(bstNode *wezel)
 {
 bstNode *pom;
 if (wezel != NULL)  {
            deleteBST(wezel -> left);
            deleteBST(wezel -> right);
            pom=wezel;
        wezel=NULL;
        free(pom);
 }
}

void preOrder(bstNode *root)    ////wyœwietlanie w porzadku preorder
{
    if (root == NULL) return;
    printf("%d\t",root->val);
    preOrder(root->left);
    preOrder(root->right);
}

int heightBST(bstNode *root)
{
 if(root==NULL)return 0;
 int h1 = heightBST(root->left);
 int h2 = heightBST(root->right);
 if (h1>h2) return 1+h1;
 else return 1+h2;
}

void inOrder(bstNode *root, int *tab, int *i)    ////wyœwietlanie w porzadku inorder
{
    if (root == NULL) return;
    inOrder(root->left, tab, i);
    tab[*i] = root->val;
    (*i)++;
    inOrder(root->right, tab, i);
}

int main()
{
    int toFind, toInsert;

    ////Tablica
    printf("Podaj liczbe elementow: ");
    scanf("%d",&size);
    n=size;
    size=size+size/10;
    int *tab = (int*)malloc(sizeof(int)*size);
    losuj(tab);
    printf("losowo ulozona tablica:\n");
    wyswietl(tab);
    printf("\n-----------------\n");

    //BST
    bstNode *bstRoot = newNode(tab[0]);
    for(i=1;i<n;i++){
    insertBST(&bstRoot,tab[i]);
    }

    printf("drzewo BST preorder:\n");
    preOrder(bstRoot);

    //////szukanie elementu
    printf("\nPodaj wartosc ktora chcesz znalesc: ");
    scanf("%d",&toFind);
    bstNode *Found = searchNode(bstRoot,toFind);
    printf("\nZnaleziony element: %d\n",Found->val);

    printf("\nWysokosc drzewa: %d\n",heightBST(bstRoot));

    //////dodawanie elementu
    printf("\n------DODAWANIE POZOSTALYCH ELEMENTOW--------\n");
    for(i=n;i<size;i++){
    insertBST(&bstRoot,tab[i]);
    }

    int *tab2 = (int*)malloc(sizeof(int)*size);
    int tmp = 0;
    inOrder(bstRoot, tab2, &tmp);
    printf("\nINORDER:\n");
    wyswietl(tab2);
    printf("\n------USUWANIE CALEGO DRZEWA--------\n");
    deleteBST(bstRoot);
    free(tab);
    free(tab2);

}
