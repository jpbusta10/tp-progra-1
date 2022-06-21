#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 100
typedef struct
{
char nombre_ingrediente[20];
float cantidad; //en kg o en litro segun el tipo de ingrediente
char tipo[20]; /// "liquido" "solido"
float costo; ///costo por kg o por litro según corresponda
}StockIngrediente;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
}Preparacion;
///prototipados
void despersistenciaStock(StockIngrediente[],int*);
void mostrarStock(StockIngrediente);
void muestraListaStock(StockIngrediente[],int);
void despercistenciaDemanda (Preparacion[],int*);
void muestraDemanda(Preparacion);
void muestraListaDemanda(Preparacion[],int);




int main()
{
int opcion;
char continuar;
int validosStock;
int validosDemanda;
StockIngrediente lista [TAM_MAX];
StockIngrediente p;
Preparacion listaDemanda [TAM_MAX];
Preparacion P;

despersistenciaStock(lista,&validosStock);
mostrarStock(p);
muestraListaStock(lista,validosStock);
despercistenciaDemanda (listaDemanda,&validosDemanda);
muestraDemanda(P);
muestraListaDemanda(listaDemanda,validosDemanda);

do
{
printf ("Ingrese opcion:\n");
printf ("1. Ver ingredientes no utilizados\n");
printf ("2. Ver productos no vendidos\n");
printf ("3. Ver ingreso total del dia\n");
printf ("4. Ver ganancia total del dia\n");
scanf ("%i",&opcion);

    switch (opcion)
    {
    case 1:
        printf ("1. Ingredientes no utilizados\n");
        break;
    case 2:
        printf ("2. Productos no vendidos\n");
        break;
    case 3:
        printf ("3. Ingreso total del dia\n");
        break;
    case 4:
        printf ("4. Ganancia total del dia\n");
        break;
    default:
        printf ("La opcion ingresada no existe\n");
        break;
    }

printf("Desea continuar?\n");
fflush(stdin);
scanf("%c",&continuar);

system ("PAUSE");
system ("cls");

}while (continuar == 's' || continuar == 'S');


////SUBMENU ventas
//printf ("Ingrese la operacion que desea realizar:\n");
////Cargar los precios de los preparados
//printf ("1. Modificar precio de preparado\n");
//printf ("2. Ingresar una nueva venta\n");
//printf ("3. Devolucion de venta\n");


    return 0;
}

void despersistenciaStock(StockIngrediente lista [],int*validos)
{
    FILE* fp;
    int i=0;
    fp=fopen("stockingredientes.bin","rb");

    if(fp!=NULL)
    {
        while(fread(&lista[i],sizeof(StockIngrediente),1,fp)>0)
        {
            i++;
        }
        (*validos)=i;
    }

}
void mostrarStock(StockIngrediente p)
{
    printf("[");
    printf("NOMBRE: %s \n",p.nombre_ingrediente);
    printf("CANRIDAD: %f \n",p.cantidad);
    printf("TIPO: %s \n",p.tipo);
    printf("COSTO: %f \n",p.costo);
    printf("]\n");
}
void muestraListaStock(StockIngrediente lista[],int validos)
{
    for(int i=0;i<validos;i++)
    {
        mostrarStock(lista[i]);
    }
}

void despercistenciaDemanda (Preparacion listaDemanda[],int* validos)
{
    FILE* fp;
    fp = fopen("demanda.bin","rb");
    int i=0;
    if (fp != NULL)
    {
        while(fread(&listaDemanda[i],sizeof(Preparacion),1,fp) > 0)
        {
            i++;
        }
        *validos=i;
        fclose(fp);
    }
}

void muestraDemanda(Preparacion P)
{
    printf("Producto: %s\n",P.nombre_preparacion);
    printf("Cantidad: %i\n",P.cantidad);
}

void muestraListaDemanda(Preparacion listaDemanda[],int validos)
{
    for (int i=0;i < validos; i++)
    {
        muestraDemanda(listaDemanda[i]);
    }
}

