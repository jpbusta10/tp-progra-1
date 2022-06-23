
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
void preparar(Receta[],int,StockIngrediente[],int,PreparacionVenta[],int*);
void mostrarPreparado(PreparacionVenta);
void mostrarListapreparado(PreparacionVenta[],int);
void cargarPreciosPreparados (FILE*,PrecioPreparacion[],int,Receta[]);
void mostrarPrecios(PrecioPreparacion);
void muestraListaPrecios(PrecioPreparacion[],int);
void modificarPrecioPreparado (FILE*,PrecioPreparacion[],int,Receta[]);
void ingresarNuevaVenta (PedidoPreparacion[],int*,int*);
void depersistenciaVentas (Venta[],PedidoPreparacion[],int,int,PrecioPreparacion[],int);
float costoTotalVenta (PedidoPreparacion[],int,int,PrecioPreparacion[],int);
void mostrarVenta (Venta,int);
void mostrarListaVentas (Venta[],int);
void devolucionVenta (Venta[],int);
//void descontarStockPreparados (PedidoPreparacion[]);/// necesito "stock preparados"




int main()
{
FILE* parch;
int opcion;
char continuar;
char control;
int validosStock;
int validosDemanda;
int validosRecetas;
int validosId;
int item=0;
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
Venta ventaLista [TAM_MAX];
Venta v;

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
printf ("5. Mostrar ventas\n");
printf ("6. Devolucion de venta\n");

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
    case 4:
        ingresarNuevaVenta (pedidoPrep,&validosId,&item);
//        descontarStockPreparados (pedidoPrep,)/// necesito "stock preparados"
        depersistenciaVentas (ventaLista,pedidoPrep,validosId,item,preciosPrep,validosRecetas);
        break;
    case 5:
        mostrarListaVentas (ventaLista,validosId);
        break;
    case 6:
        devolucionVenta (ventaLista,validosId);
        break;
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
void preparar(Receta recetas[],int validosRecetas, StockIngrediente stock[],int validosStock, PreparacionVenta preparadosListos[],int* validosPreparados)
{
    FILE* fp;
    int validosDemanda=0;
    Preparacion p;
    int indice=0;///indice recetas
    int indicS=0;//indice stock
    float aModificar=0;
    int preparados=0;
    int flag;
    int flagRec;
    int maxim;
    int n=-1;
    char ingrediente [CANT_MAX];
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
            preparados=0;
            maxim=0;
            flagRec=0;
            while(preparados < p.cantidad && maxim == 0)
            {
                flag=0;
                for(int j=0; j < recetas[indice].cantIngredientes;j++)
                {
                    strcpy(ingrediente,recetas[indice].ingredientes[j].nombre_ingrediente);
                    indicS=busquedaStock(stock,validosStock,ingrediente);
                    if((stock[indicS].cantidad>0) && (stock[indicS].cantidad >= recetas[indice].ingredientes[j].cantidad))
                    {
                    aModificar=(recetas[indice].ingredientes[j].cantidad);
                    stock[indicS].cantidad=stock[indicS].cantidad-aModificar;
                        flag++;
                    }
                }
                    flagRec=flag;
                if(flagRec == recetas[indice].cantIngredientes)
                {
                preparados++;
                }
                else
                {
                    maxim++;
                }
                flagRec=0;
            }
            if(preparados!=0)
            {
                n++;
                strcpy(preparadosListos[n].nombre_preparacion,recetas[indice].nombre_preparacion);
                preparadosListos[n].cantidad=preparados;
            }
        }
    }
    *validosPreparados=n;
    fclose(fp);
}

void mostrarPreparado(PreparacionVenta preparado)
{
    printf("%s: %i\n",preparado.nombre_preparacion,preparado.cantidad);
}

void mostrarListapreparado(PreparacionVenta preparado[],int validos)
{
    for(int i=0;i < validos;i++)
    {
        mostrarPreparado(preparado[i]);
    }
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


void ingresarNuevaVenta (PedidoPreparacion pedidoPrep[],int* validosId,int* item)
{
    char nombre [TAM_MAX];
    char cont;
    int cantidad;

            do
            {
                printf("Ingresar preparacion a vender: \n");
                fflush(stdin);
                gets (nombre);
                strcpy (pedidoPrep[item].nombre_preparacion,nombre);
                printf("Ingrese la cantidad a vender: \n");
                fflush(stdin);
                scanf("%i",&cantidad);
                pedidoPrep[item].cantidad=cantidad;
                item++;
                printf("Desea continuar? s/n \n");
                fflush(stdin);
                scanf("%c",&cont);
            }while (cont=='s' || cont=='S' && item<=20);
    (*validosId)++;
}
        else
        {
            printf("Error-no se pudo abrir el archivo ventas.bin\n");
        }

        fclose(pa);
}


void depersistenciaVentas (Venta ventaLista[],PedidoPreparacion pedidoPrep[],int validosId,int item,PrecioPreparacion preciosPrep[],int validosRecetas)
{
    FILE* pa;
    char identificacion [TAM_MAX];
    char cont;
    int cantidad;
    float valorTotal;
    int altaVenta=1;
    pa=fopen("ventas.bin","ab");
        if (pa!=NULL)
        {
            do
            {
                printf("Ingresar identificacion del comprador: \n");
                fflush(stdin);
                gets (nombre);
                strcpy (ventaLista[validosId].idVenta,nombre);
                fwrite (&ventaLista[validosId].idVenta,sizeof(char),1,pa);

                strcpy (ventaLista.items_pedido[validosId].nombre_preparacion,pedidoPrep[validosId].nombre_preparacion);
                fwrite (&ventaLista.items_pedido[validosId].nombre_preparacion,sizeof(char),1,pa);

                ventaLista.items_pedido[validosId].cantidad=pedidoPrep[validosId].cantidad;
                fwrite (&ventaLista.items_pedido[validosId].cantidad,sizeof(int),1,pa);

                ventaLista[validosId].cantItems=item;
                fwrite (&ventaLista[validosId].cantItems,sizeof(int),1,pa);

                valorTotal=costoTotalVenta (pedidoPrep,validosId,item,preciosPrep,validosRecetas);
                ventaLista[validosId].valor_total=valorTotal;
                fwrite (&ventaLista[validosId].valor_total,sizeof(float),1,pa);

                ventaLista[validosId].baja=altaVenta;
                fwrite (&ventaLista[validosId].baja,sizeof(int),1,pa);

                printf("Desea continuar? s/n \n");
                fflush(stdin);
                scanf("%c",&cont);
            }while (cont=='s' || cont=='S');


        }
}

float costoTotalVenta (PedidoPreparacion pedidoPrep[],int validosId,int item,PrecioPreparacion preciosPrep[],int validosRecetas)
{
    float valor=0;
    int j=0;

        do
        {
            for (int i=0;i<validosRecetas;i++)
            {
                if (strcmpi(pedidoPrep[item].nombre_preparacion,preciosPrep[i].nombre_preparacion)==0)
                {
                    valor+=(preciosPrep[i].precio_venta)*(pedidoPrep[item].cantidad);
                    j++;
                }
            }

        }while (j<item);

    return valor;
}

void mostrarVenta (Venta v,int item)
{
    printf("Id Venta: %s\n",v.idVenta);
    for (int i=0;i<item;i++)
    {
      printf("Pedido: -Preparacion: %s     -Cantidad: %i \n",v.items_pedido[i].nombre_preparacion,v.items_pedido[i].cantidad);
    }
    printf("Cantidad items: %i\n",v.cantItems);
    printf("Valor total venta: %f\n",v.valor_total);
}

void mostrarListaVentas (Venta ventaLista[],int validosId)
{
    for(int i=0;i<validosId;i++)
    {
        mostrarVenta(ventaLista[i]);
    }
}

void devolucionVenta (Venta ventaLista[],int validosId)
{
char Id [TAM_MAX];
    printf("Ingrese el Id de la venta que quiere dar de baja\n");
    gets(Id);
        for (int i=0;i<validosId;i++)
        {
            if (strcmpi(Id,ventaLista[i].idVenta)==0)
            {
                ventaLista[i].baja=0;
                printf("Se ha dado de baja la venta\n");
            }
        }

}


//void descontarStockPreparados (pedidoPrep,)/// necesito "stockventa", stock de preaprados para la venta,se puede quedar sin stock




