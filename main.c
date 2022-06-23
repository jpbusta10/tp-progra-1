
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct
{
char nombre_preparacion[20];
float precio_venta; ///precio por unidad
}PrecioPreparacion;

typedef struct
{
char nombre_preparacion[20];
int cantidad;
}PedidoPreparacion;

typedef struct
{
int idVenta;
PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
int cantItems; ///los validos del arreglo de items_pedido
float valor_total; ///valor total a pagar
int baja;
}Venta;

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
int busquedaStock(StockIngrediente[],int,char[]);
void preparacion(Receta[],int, StockIngrediente[],int);
void cargarPreciosPreparados (FILE*,PrecioPreparacion[],int,Receta[]);
void mostrarPrecios(PrecioPreparacion);
void muestraListaPrecios(PrecioPreparacion[],int);
void modificarPrecioPreparado (FILE*,PrecioPreparacion[],int,Receta[]);
void ingresarNuevaVenta (PedidoPreparacion[]);
//void descontarStockPreparados (PedidoPreparacion[]);/// necesito "stock preparados"
//void devolucionVenta ();///se agrega baja en struct venta




int main()
{
FILE* parch;
int opcion;
char continuar;
char control;
int validosStock;
int validosDemanda;
int validosRecetas;
StockIngrediente lista [TAM_MAX];
StockIngrediente p;
Preparacion listaDemanda [TAM_MAX];
Preparacion P;
Receta list[TAM_MAX];
Receta r;
PrecioPreparacion preciosPrep [TAM_MAX];
PrecioPreparacion precioP;
PedidoPreparacion pedidoPrep [TAM_MAX];
PedidoPreparacion pP;

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


//SUBMENU VENTAS

system ("PAUSE");
system ("cls");

do
{
printf ("VENTAS:\n");
printf ("\n");
printf ("Ingrese la operacion que desea realizar:\n");
printf ("1. Cargar precios preparados\n");
printf ("2. Mostrar lista precios\n");
printf ("3. Modificar precio de preparado\n");
printf ("4. Ingresar una nueva venta\n");
printf ("5. Devolucion de venta\n");

scanf ("%i",&opcion);

    switch (opcion)
    {
    case 1:

        cargarPreciosPreparados (parch,preciosPrep,validosRecetas,list);
        break;
    case 2:
        mostrarPrecios(precioP);
        muestraListaPrecios(preciosPrep,validosRecetas);
        break;
    case 3:
        modificarPrecioPreparado (parch,preciosPrep,validosRecetas,list);
        break;
//    case 4:
//        ingresarNuevaVenta (pedidoPrep);
//        descontarStockPreparados (pedidoPrep,)/// necesito "stock preparados"
//        break;
//    case 5:
//        devolucionVenta ();///se agrega baja en struct venta
//        break;
    default:
        printf ("La opcion ingresada no existe\n");
        break;
    }

printf("Desea continuar?\n");
fflush(stdin);
scanf("%c",&control);

system ("PAUSE");
system ("cls");

}while (control == 's' || continuar == 'S');


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
void preparacion(Receta recetas[],int validosRecetas, StockIngrediente stock[],int validosStock)
{
    FILE* fp;
    int validosDemanda=0;
    Preparacion p;
    int indice=0;///indice recetas
    int indicS=0;//indice stock
    float aModificar=0;

    char ingrediente [TAM_MAX];
    fp=fopen("demanda.bin","rb");
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        validosDemanda=ftell(fp)/sizeof(Preparacion);
        fseek(fp,0,SEEK_SET);
        for(int i=0; i<validosDemanda; i++)
        {
            fread(&p,sizeof(Preparacion),1,fp);
            indice=busquedaReceta(recetas,validosRecetas,p.nombre_preparacion);
            //printf("indice: %i  nombre: %s \n",indice,p.nombre_preparacion);
            for(int j=0; j<recetas[indice].cantIngredientes; j++)
            {
                strcpy(ingrediente,recetas[indice].ingredientes[j].nombre_ingrediente);
                indicS=busquedaStock(stock,validosStock,ingrediente);
                //printf("indice stock:%i ingrediente:%s\n",indicS,ingrediente);
                aModificar=(p.cantidad)*(recetas[indice].ingredientes[j].cantidad);///meto todo en una variable para hacelo mas facil de leer
                if(stock[indicS].cantidad>=aModificar)
                {
                    stock[indicS].cantidad=stock[indicS].cantidad-aModificar;
                }
            }

        }
    }
    fclose(fp);
}
int busquedaStock(StockIngrediente stock[],int validosStock,char ingrediente[])
{
    int indice=0;
    for(int i=0;i<validosStock;i++)
    {
        if(strcmp(stock[i].nombre_ingrediente,ingrediente)==0)
        {
            indice=i;
        }
    }
    return indice;
}

//void devolucionVenta

void ingresarNuevaVenta (PedidoPreparacion pedidoPrep[])
{
    FILE* pa;
    char nombre [TAM_MAX];
    int i=0;
    char cont;
    int cantidad;
    pa=fopen("ventas.bin","ab");
        if (pa!=NULL)
        {
            do
            {
                printf("Ingresar preparacion a vender: \n");
                fflush(stdin);
                gets (nombre);
                strcpy (pedidoPrep[i].nombre_preparacion,nombre);
                fwrite (&pedidoPrep[i].nombre_preparacion,sizeof(char),1,pa);
                printf("Ingrese la cantidad a vender: \n");
                fflush(stdin);
                scanf("%i",&cantidad);
                pedidoPrep[i].cantidad=cantidad;
                fwrite(&pedidoPrep[i].cantidad,sizeof(int),1,pa);
                printf("Desea continuar? s/n \n");
                fflush(stdin);
                scanf("%c",&cont);
            }while (cont=='s' || cont=='S');


        }
}

void modificarPrecioPreparado (FILE* parch,PrecioPreparacion preciosPrep[],int validosRecetas,Receta list[])
{
  parch=fopen ("precios.bin","r+b");
  char nombre [TAM_MAX];
  float precio;
    if (parch!=NULL)
    {
        printf("Ingrese el nombre de la preparacion que desea cambiar el precio\n");
        fflush(stdin);
        gets(nombre);
        for (int i=0;i<validosRecetas;i++)
       {
           if (fread(list[i].nombre_preparacion,sizeof(char),1,parch)>0);//sizeof????
           if (strcmp(nombre,list[i].nombre_preparacion)==0)
           {
             printf("Ingrese el precio de: %s",list[i].nombre_preparacion);
             printf("\n");
             fflush(stdin);
             scanf("%f",&precio);
            preciosPrep[i].precio_venta=precio;
            fwrite(&preciosPrep[i].precio_venta,sizeof(float),1,parch);
           }
        }
    }
fclose (parch);
}

void cargarPreciosPreparados (FILE* parch,PrecioPreparacion preciosPrep[],int validosRecetas,Receta list[])
{
parch=fopen ("precios.bin","wb");
float precio;
    if (parch!=NULL)
    {
        for (int i=0;i<validosRecetas;i++)
       {
        strcpy (preciosPrep[i].nombre_preparacion,list[i].nombre_preparacion);
        fwrite(preciosPrep[i].nombre_preparacion,sizeof(list[i].nombre_preparacion),1,parch);
        printf("Ingrese el precio de: %s",list[i].nombre_preparacion);
        printf("\n");
        fflush(stdin);
        scanf("%f",&precio);
        preciosPrep[i].precio_venta=precio;
        fwrite(&preciosPrep[i].precio_venta,sizeof(float),1,parch);
       }
    }
  else
  {
      printf("Error al ingresar los datos \n");
  }
fclose (parch);
}

void mostrarPrecios(PrecioPreparacion precioP)
{
    printf("El precio de %s es %f\n",precioP.nombre_preparacion,precioP.precio_venta);
    printf("\n");
}
void muestraListaPrecios(PrecioPreparacion preciosPrep[],int validosRecetas)
{
    for(int i=0;i<validosRecetas;i++)
    {
        mostrarPrecios(preciosPrep[i]);
    }
}

