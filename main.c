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


int main()
{
   
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

