
#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 20
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
typedef struct
{
char nombre_ingrediente[20];
float cantidad; ///puede ser en litro o en kg
}IngredienteXReceta;
typedef struct
{
char nombre_preparacion[20];
IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
int cantIngredientes; ///los validos de ingredientes
}Receta;

///prototipados
void despersistenciaStock(StockIngrediente[],int*);
void mostrarStock(StockIngrediente);
void muestraListaStock(StockIngrediente[],int);
void despercistenciaDemanda (Preparacion[],int*);
void muestraDemanda(Preparacion);
void muestraListaDemanda(Preparacion[],int);
void despersistenciaReceta(Receta[],int*);
void muestraReceta(Receta);
void muestraListaRecetas(Receta[],int);
int busquedaReceta(Receta[],int,char[]);



int main()
{
int opcion;
char continuar;
int validosStock;
int validosDemanda;
int validosRecetas;
StockIngrediente lista [TAM_MAX];
StockIngrediente p;
Preparacion listaDemanda [TAM_MAX];
Preparacion P;
Receta list[TAM_MAX];
Receta r;

despersistenciaStock(lista,&validosStock);
mostrarStock(p);
muestraListaStock(lista,validosStock);
despercistenciaDemanda (listaDemanda,&validosDemanda);
muestraDemanda(P);
muestraListaDemanda(listaDemanda,validosDemanda);
despersistenciaReceta(list,&validosRecetas);
muestraReceta(r);
muestraListaRecetas(list,validosRecetas);

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
    char string [] = "liquido";
    printf("NOMBRE: %s \n",p.nombre_ingrediente);
    if(strcmp(p.tipo,string)==0)
    {
        printf("Cantidad: %.2f litros \n",p.cantidad);
    }
    else
    {
        printf("cantidad: %.2f kilos \n",p.cantidad);
    }
    printf("COSTO: %.2f\n",p.costo);
    printf("\n");
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
        printf("\n");
    }
}

void despersistenciaReceta(Receta list[],int*validosRecetas)
{
    FILE* fp;
    int i=0;
    fp=fopen("recetas.bin","rb");

    if(fp!=NULL)
    {
        while(fread(&list[i],sizeof(Receta),1,fp)>0)
        {
            i++;
        }
        (*validosRecetas)=i;
    }
}

void muestraReceta(Receta r)
{
    printf("RECETA: %s \n",r.nombre_preparacion);
    printf("\n");
    for(int i=0;i < r.cantIngredientes;i++)
    {
        printf("Ingrediente: %s\n",r.ingredientes[i].nombre_ingrediente);
        printf("Kilos o Litros: %.2f\n",r.ingredientes[i].cantidad);
    }
    printf("cantidad ingredientes: %i \n",r.cantIngredientes);
    printf("\n");
}

void muestraListaRecetas(Receta list[],int validosRecetas)
{
    for(int i=0;i<validosRecetas;i++)
    {
        muestraReceta(list[i]);
    }
}
int busquedaReceta(Receta lista[],int validosReceta,char nombrePreparacion[])//retorna el indice de la receta a buscar por el nombre 
{
    int busqueda=0;
    for(int i=0;i<validosReceta;i++)
    {
        if(strcmp(lista[i].nombre_preparacion,nombrePreparacion)==0)
        {
            busqueda=i;
        }
    }
    return busqueda;
}
void preparar(Receta lista[],StockIngrediente stock[],int validosStock,int validosReceta)
{
    FILE*fp;
    Preparacion p;
    int indice=0;
    int validosDemanda=0;
    int i=0;
    int k=0;
    int indiceStock=0;
    fp=fopen("demanda.bin","rb");
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        validosDemanda = ftell(fp)/sizeof(Preparacion);
        fseek(fp,0,SEEK_SET);
        while(k<validosDemanda)///iteramos hasta que se termine el archivo
        {
        fread(&p,sizeof(Preparacion),1,fp);
        indice=busquedaReceta(lista,validosReceta,p.nombre_preparacion); ///buscamos el indice en la receta
        while(i<lista[indice].cantIngredientes) ///siclo while para iterar los ingredientes
        {
            indiceStock=busquedaStock(stock,validosStock,lista[indice].ingredientes[i].nombre_ingrediente); /// buscamos el indice en el stock
            stock[indiceStock].cantidad=(stock[indiceStock].cantidad)-(p.cantidad)*(lista[indice].ingredientes[i].cantidad); /// cambiamos el stock
            i++;
        }
        k++;
        }
    }
    fclose(fp);

}
int busquedaStock(StockIngrediente stock[],int validosStock,char ingrediente[])
{
    int indice=0;
    for(int i;i<validosStock;i++)
    {
        if(strcmp(stock[i].nombre_ingrediente,ingrediente)==0)
        {
            indice=i;
        }
    }
    return indice;
}
