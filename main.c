#include <stdio.h>
#include <stdlib.h>

typedef struct elempar {
    int p,r;
} Elempar;

typedef struct data {
    int n;
    Elempar c[];
} Data;

int randomgen (int also, int felso)
{
    return (rand() % (felso - also + 1)) + also;
}

Elempar *createRandom (int n)
{
    Elempar *a;
    a = (Elempar*) malloc(n * sizeof(Elempar));

    for (int i=0; i<n; i++)
    {
        a[i].p = randomgen(1,9);
        a[i].r = randomgen(1,9);

        // ellenorizni kell, hogy ne legyenek azonos elemek
        for (int j=0; j<i; j++)
            while ( (a[i].p == a[j].p) && (a[i].r == a[j].r) )
            {
                a[i].p = randomgen(1,9);
                a[i].r = randomgen(1,9);
            }
    }

    return a;
}

void print (Elempar *h, int n)
{
    printf("{ ");
    for (int i=0; i<n-1; i++)
        printf("(%d, %d), ", h[i].p, h[i].r);
    printf("(%d, %d) } \n", h[n-1].p, h[n-1].r);
}

void printdata (Data *d)
{
    printf("{ ");
    for (int i=0; i<d->n-1; i++)
        printf("(%d, %d), ", d->c[i].p, d->c[i].r);
    printf("(%d, %d) } \n\n", d->c[d->n-1].p, d->c[d->n-1].r);
}

Data *natural_join (Elempar *a, Elempar *b, int n)
{
    Data *data = (Data*) malloc(n*n * sizeof(Data));
    data->n = 0;

    printf("\n");
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (b[i].r == a[j].p)
            {
                data->c[data->n].p = b[i].p;
                data->c[data->n].r = a[j].r;

                printf("[%d] : (%d,%d) o (%d,%d) -> (%d,%d)\n", data->n, b[i].p, b[i].r, a[j].p, a[j].r, data->c[data->n].p, data->c[data->n].r );

                data->n++;
            }
    printf("\n");

    return data;
}

Elempar *transpose (Elempar *a, int n)
{
    Elempar *data = (Elempar*) malloc(n * sizeof(Elempar));

    for (int i=0; i<n; i++)
    {
        data[i].p = a[i].r;
        data[i].r = a[i].p;
    }

    return data;
}

Data *remove_dupes(Data *data)
{
    for (int i=0; i<data->n; i++)
        for (int j=i+1; j<data->n; j++)
            if ( (data->c[i].p == data->c[j].p) && (data->c[i].r == data->c[j].r) )
            {
                data->n--;

                for (int k=j; k<data->n; k++)
                {
                    data->c[k].p = data->c[k+1].p;
                    data->c[k].r = data->c[k+1].r;
                }
                j--;
            }

    return data;
}

int main()
{
    int n = 8;

    Data *c = malloc(n*n * sizeof(Data));
    Elempar *inv = malloc(n * sizeof(Elempar));

    Elempar *a[n], *b[n];
    *a = createRandom(n);
    *b = createRandom(n);

    print(*a,n);
    print(*b,n);
    printf("\n");

    printf("a o b = ");
    c = natural_join(*a, *b, n);
    c = remove_dupes(c);
    printdata(c);
    printf("\n");

    printf("b ^ -1 = ");
    inv = transpose(*b, n);
    print(inv,n);
    printf("\n");

    printf("a ^ 2 = ");
    c = natural_join(*a, *a, n);
    c = remove_dupes(c);
    printdata(c);

    free(*a);
    free(*b);
    free(c);

    return 0;
}
