#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_MAX 20
typedef struct
{
    char nombre_ingrediente[20];
    float cantidad; //en kg o en litro segun el tipo de ingrediente
    char tipo[20]; /// "liquido" "solido"
    float costo; ///costo por kg o por litro según corresponda
} StockIngrediente;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
} Preparacion;
typedef struct
{
    char nombre_ingrediente[20];
    float cantidad; ///puede ser en litro o en kg
} IngredienteXReceta;
typedef struct
{
    char nombre_preparacion[20];
    IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
    int cantIngredientes; ///los validos de ingredientes
} Receta;

typedef struct
{
    char nombre_preparacion[20];
    float precio_venta; ///precio por unidad
} PrecioPreparacion;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;
} PedidoPreparacion;

typedef struct
{
    int idVenta;
    PedidoPreparacion items_pedido[20]; ///puedo pedir hasta 20 items
    int cantItems; ///los validos del arreglo de items_pedido
    float valor_total; ///valor total a pagar
    int baja;
} Venta;
typedef struct
{
    char nombre_preparacion[20];
    int cantidad; ///por unidad, no hay por peso
} PreparacionVenta;


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
void preparar(Receta[],int, StockIngrediente[],int, PreparacionVenta[],int*);
void mostrarPreparado(PreparacionVenta);
void mostrarListapreparado(PreparacionVenta[],int);
void cargarPreciosPreparados (PrecioPreparacion[],int,Receta[]);
void mostrarPrecios(PrecioPreparacion);
void muestraListaPrecios(PrecioPreparacion[],int);
void modificarPrecioPreparado(Receta[],int);
void ingresarNuevaVenta(int*,Receta[],int);
//void depersistenciaVentas (Venta[],PedidoPreparacion[],int,int,PrecioPreparacion[],int);
float costoTotalVenta (PedidoPreparacion[],int,int,PrecioPreparacion[],int);
void mostrarVenta (Venta);
void mostrarListaVentas (Venta[],int);
void devolucionVenta (Venta[],int);
void persistenciaStock(StockIngrediente[],int);
void descontarStockPreparados ();
void persistenciaPreparados(PreparacionVenta[],int);
void muestraVentas();
void despecistenciaPreparados(PreparacionVenta[],int*);



int main()
{
    FILE* parch;
    int opcion=0;
    char continuar;
    char control;
    int validosStock=0;
    int validosDemanda=0;
    int validosRecetas=0;
    int validosId=0;
    int validosPreparados=0;
    int validosVenta=0;
    int item=0;
    StockIngrediente stock [TAM_MAX];
    Receta recetas[TAM_MAX];
    PrecioPreparacion preciosPrep [TAM_MAX];
    PedidoPreparacion pedidoPrep [TAM_MAX];
    PreparacionVenta preparados [TAM_MAX];
    Venta ventaLista [TAM_MAX];
    despersistenciaStock(stock,&validosStock);
    despersistenciaReceta(recetas,&validosRecetas);
    //mostrarListapreparado(preparados,validosPreparados);
    printf("desea preparar la demanda?\n");
    fflush(stdin);
    scanf("%c",&continuar);
    if(continuar=='s'||continuar=='S')
    {
        preparar(recetas,validosRecetas,stock,validosStock,preparados,&validosPreparados);
        persistenciaPreparados(preparados,validosPreparados);
    }
    else
    {
        despecistenciaPreparados(preparados,&validosPreparados);
    }
    fflush(stdin);
    while(true)
    {
        printf ("Ingrese opcion:\n");
        printf ("1. Ver ingredientes no utilizados\n");
        printf ("2. Ver productos no vendidos\n");
        printf ("3. Ver ingreso total del dia\n");
        printf ("4. Ver ganancia total del dia\n");
        printf("5. Menu ventas\n");
        scanf ("%i",&opcion);

        switch (opcion)
        {
        case 1:
            printf ("1. Ingredientes no utilizados\n");
            muestraListaStock(stock,validosStock);
            printf("desea persistir el stock? s/n\n");
            fflush(stdin);
            scanf("%c",&continuar);
            if(continuar=='s'||continuar=='S')
            {
                persistenciaStock(stock,validosStock);
            }
            continuar='j';
            system ("PAUSE");
            system ("cls");
            break;
        case 2:
            printf ("2. Productos no vendidos\n");
            despecistenciaPreparados(preparados,&validosPreparados);
            mostrarListapreparado(preparados,validosPreparados);
            printf("desea persistir los preparados? s/n\n");
            fflush(stdin);
            scanf("%c",&continuar);
            if(continuar=='s'||continuar=='S')
            {
                persistenciaPreparados(preparados,validosPreparados);
            }
            continuar = 'j';
            system ("PAUSE");
            system ("cls");
            break;
        case 3:
            printf ("3. Ingreso total del dia\n");
            system ("PAUSE");
            system ("cls");
            break;
        case 4:
            printf ("4. Ganancia total del dia\n");
            system ("PAUSE");
            system ("cls");
            break;
        case 5:
            system ("PAUSE");
            system ("cls");
            while (true)
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

                    cargarPreciosPreparados (preciosPrep,validosRecetas,recetas);
                    system ("PAUSE");
                    system ("cls");
                    break;
                case 2:
                    muestraListaPrecios(preciosPrep,validosRecetas);
                    system ("PAUSE");
                    system ("cls");
                    break;
                case 3:
                    modificarPrecioPreparado (recetas,validosRecetas);
                    system ("PAUSE");
                    system ("cls");
                    break;
                case 4:
                    ingresarNuevaVenta(validosVenta,recetas,validosRecetas);
                    descontarStockPreparados ();
                    break;
                case 5:
                    muestraVentas();
                    system ("PAUSE");
                    system ("cls");
                    break;
                case 6:
                    devolucionVenta (ventaLista,validosId);
                    system ("PAUSE");
                    system ("cls");
                    break;

                default:
                    printf ("usted esta volviendo a la opcion anterior");
                    break;
                }

            default:
                printf ("usted esta volviendo al menu principal\n");
                break;
            }

            system ("PAUSE");
            system ("cls");

        }


    }




//SUBMENU VENTAS

    /*system ("PAUSE");
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

            cargarPreciosPreparados (preciosPrep,validosRecetas,recetas);
            break;
        case 2:
            muestraListaPrecios(preciosPrep,validosRecetas);
            break;
        case 3:
            modificarPrecioPreparado ();
            break;
        case 4:
            //ingresarNuevaVenta (pedidoPrep,&validosId,&item);
            descontarStockPreparados ();
            //depersistenciaVentas (ventaLista,pedidoPrep,validosId,item,preciosPrep,validosRecetas);
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
    */
    return 0;
}
void despecistenciaPreparados(PreparacionVenta preparados[],int* validosPreparados)
{
    FILE* fp;
    fp=fopen("stockPreparados.bin","rb");
    int i=0;
    if(fp!=NULL)
    {
        while(fread(&preparados[i],sizeof(PreparacionVenta),1,fp)>0)
        {
            i++;
        }
        (*validosPreparados)=i;
    }
    fclose(fp);
}
void persistenciaStock(StockIngrediente stock [],int validosStock)
{
    FILE* fp;
    fp=fopen("stockingredientes.bin","wb");
    if(fp!=NULL)
    {

        fwrite(stock,sizeof(StockIngrediente),validosStock,fp);

    }
    fclose(fp);
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
    fclose(fp);
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
    for(int i=0; i<validos; i++)
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
    for (int i=0; i < validos; i++)
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
    for(int i=0; i < r.cantIngredientes; i++)
    {
        printf("Ingrediente: %s\n",r.ingredientes[i].nombre_ingrediente);
        printf("Kilos o Litros: %.2f\n",r.ingredientes[i].cantidad);
    }
    printf("cantidad ingredientes: %i \n",r.cantIngredientes);
    printf("\n");
}

void muestraListaRecetas(Receta list[],int validosRecetas)
{
    for(int i=0; i<validosRecetas; i++)
    {
        muestraReceta(list[i]);
    }
}
int busquedaReceta(Receta lista[],int validosReceta,char nombrePreparacion[])//retorna el indice de la receta a buscar por el nombre
{
    int busqueda=0;
    for(int i=0; i<validosReceta; i++)
    {
        if(strcmpi(lista[i].nombre_preparacion,nombrePreparacion)==0)
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
            preparados=0;
            maxim=0;
            flagRec=0;
            while(preparados < p.cantidad && maxim == 0)
            {
                flag=0;
                for(int j=0; j < recetas[indice].cantIngredientes; j++)
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
    for(int i=0; i <= validos; i++)
    {
        mostrarPreparado(preparado[i]);
    }
}

int busquedaStock(StockIngrediente stock[],int validosStock,char ingrediente[])
{
    int indice=0;
    for(int i=0; i<validosStock; i++)
    {
        if(strcmpi(stock[i].nombre_ingrediente,ingrediente)==0)
        {
            indice=i;
        }
    }
    return indice;
}

void persistenciaPreparados(PreparacionVenta preparados[],int validos)
{
    FILE* fp;
    fp=fopen("stockPreparados.bin","wb");
    if(fp != NULL)
    {
        fwrite(preparados,sizeof(PreparacionVenta),validos,fp);
        fclose(fp);
    }
}

void modificarPrecioPreparado(Receta recetas[],int validosReceta)
{
    FILE* parch;
    parch=fopen ("precios.bin","r+b");
    PrecioPreparacion precios[TAM_MAX];
    char nombre [TAM_MAX];
    int validosPrecios;
    float precio;
    if (parch!=NULL)
    {
        printf("de la siguiente lista: \n");
        for(int i=0; i<validosReceta; i++)
        {
            printf("%s\n",recetas[i].nombre_preparacion);
        }
        printf("Ingrese el nombre de la preparacion que desea cambiar el precio\n");
        fflush(stdin);
        gets(nombre);
        fseek(parch,0,SEEK_END);
        validosPrecios=ftell(parch)/sizeof(PrecioPreparacion);
        fseek(parch,0,SEEK_SET);
        for (int i=0; i<validosPrecios; i++)
        {
            fread(&precios[i],sizeof(PrecioPreparacion),1,parch);

            if (strcmpi(nombre,precios[i].nombre_preparacion)==0)
            {
                printf("Ingrese el precio de: %s\n",precios[i].nombre_preparacion);
                scanf("%f",&precio);
                precios[i].precio_venta=precio;
                fseek(parch,-1*(sizeof(PrecioPreparacion)),SEEK_CUR);
                fwrite(&precios[i],sizeof(PrecioPreparacion),1,parch);
                fseek(parch,sizeof(PrecioPreparacion),SEEK_CUR);
            }
        }
    }
    fclose (parch);
}

void cargarPreciosPreparados (PrecioPreparacion preciosPrep[],int validosRecetas,Receta list[])
{
    FILE* parch;
    parch=fopen ("precios.bin","wb");
    float precio;
    if (parch!=NULL)
    {
        for (int i=0; i<validosRecetas; i++)
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
    printf("El precio de %s es %.2f\n",precioP.nombre_preparacion,precioP.precio_venta);
    printf("\n");
}
void muestraListaPrecios(PrecioPreparacion preciosPrep[],int validosRecetas)
{
    FILE* fp;
    fp=fopen("precios.bin","rb");
    if(fp!=NULL)
    {
        fread(preciosPrep,sizeof(PrecioPreparacion),validosRecetas,fp);
        fclose(fp);
    }
    for(int i=0; i<validosRecetas; i++)
    {
        mostrarPrecios(preciosPrep[i]);
    }
}


void ingresarNuevaVenta (int* validosVentas,Receta recetas[],int validosRecetas)
{
    char nombre [TAM_MAX];
    char cont;
    int item=0;
    int contador=0;
    int validosPrecios=0;
    PrecioPreparacion precios[TAM_MAX];
    int cantidad=0;
    int indicePrecio=0;
    float acumulador=0;
    float valorItem=0;
    Venta v;
    FILE* fp;
    fp=fopen("precios.bin","rb");
    if(fp!=NULL)
    {
        while(fread(&precios,sizeof(PrecioPreparacion),1,fp)>0)
        {
            validosPrecios++;
        }
    }
    fclose(fp);

    do
    {
        printf("de las siguientes preparaciones:\n");
        for(int i=0; i<validosRecetas; i++)
        {
            printf("%s\n",recetas[i].nombre_preparacion);
        }
        printf("\nIngresar preparacion a vender: \n");
        fflush(stdin);
        gets (nombre);
        strcpy (v.items_pedido[item].nombre_preparacion,nombre);
        printf("Ingrese la cantidad a vender: \n");
        scanf("%i",&cantidad);
        for(int i=0; i<validosPrecios; i++)
        {
            if(strcmp(precios[i].nombre_preparacion,nombre)==0)
            {
                indicePrecio=i;
            }
        }
        valorItem=cantidad*precios[indicePrecio].precio_venta;
        printf("el valor de su pedido es de %.2f\n",valorItem);

        v.items_pedido[item].cantidad=cantidad;
        item++;
        v.valor_total=acumulador+valorItem;
        acumulador=acumulador+valorItem;
        (*validosVentas)++;
        printf("Desea agregar mas items? s/n \n");
        fflush(stdin);
        scanf("%c",&cont);
        contador++;
        printf("el total de la venta es: %.2f\n",acumulador);
    }
    while (cont=='s' || cont=='S' && item<=20);
    v.cantItems=item;
    printf("valor item %i\n",item);
    FILE* jp;
    Venta vent[TAM_MAX];
    jp=fopen("ventas.bin","rb");
    if(jp!=NULL)
    {
        int val=0;
        fseek(jp,0,SEEK_END);
        val=ftell(jp)/sizeof(Venta);
        fseek(jp,0,SEEK_SET);
        v.idVenta=val+1;
    }
    fclose(jp);
    FILE*kk;
    kk=fopen("ventas.bin","ab");
    if(kk!=NULL)
    {
        fwrite(&v,sizeof(Venta),1,kk);
    }
    fclose(kk);

}
void muestraVentas()
{
    FILE* fp;
    Venta ventas[TAM_MAX];
    int val=0;
    fp=fopen("ventas.bin","rb");
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        val=ftell(fp)/sizeof(Venta);
        fseek(fp,0,SEEK_SET);
        fread(&ventas,sizeof(Venta),val,fp);
    }
    fclose(fp);
    mostrarListaVentas(ventas,val);
}
/*

void persistenciaVentas (Venta ventaLista[],PedidoPreparacion pedidoPrep[],int validosId,int item,PrecioPreparacion preciosPrep[],int validosRecetas)
{
    FILE* pa;
    char identificacion [TAM_MAX];
    char cont;
    int cantidad=0;
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
        }
        while (cont=='s' || cont=='S');


    }
    fclose(pa);
}
*/
float costoTotalVenta (PedidoPreparacion pedidoPrep[],int validosId,int item,PrecioPreparacion preciosPrep[],int validosRecetas)
{
    float valor=0;
    int j=0;

    do
    {
        for (int i=0; i<validosRecetas; i++)
        {
            if (strcmpi(pedidoPrep[item].nombre_preparacion,preciosPrep[i].nombre_preparacion)==0)
            {
                valor+=(preciosPrep[i].precio_venta)*(pedidoPrep[item].cantidad);
                j++;
            }
        }

    }
    while (j<item);

    return valor;
}

void mostrarVenta (Venta v)
{
    printf("Id Venta: %i\n",v.idVenta);
    for (int i=0; i<v.cantItems; i++)
    {
        printf("Pedido: -Preparacion: %s     -Cantidad: %i \n",v.items_pedido[i].nombre_preparacion,v.items_pedido[i].cantidad);
    }
    printf("Cantidad items: %i\n",v.cantItems);
    printf("Valor total venta: %f\n",v.valor_total);
}

void mostrarListaVentas(Venta ventaLista[],int validosId)
{
    for(int i=0; i<validosId; i++)
    {
        mostrarVenta(ventaLista[i]);
    }
}

void devolucionVenta (Venta ventaLista[],int validosId)
{
    char Id [TAM_MAX];
    printf("Ingrese el Id de la venta que quiere dar de baja\n");
    gets(Id);
    for (int i=0; i<validosId; i++)
    {
        if (strcmpi(Id,ventaLista[i].idVenta)==0)
        {
            ventaLista[i].baja=0;
            printf("Se ha dado de baja la venta\n");
        }
    }

}


void descontarStockPreparados ()/// necesito "stockventa", stock de preaprados para la venta,se puede quedar sin stock
{
    FILE* fpa;
    Venta ventas[TAM_MAX];
    int valVentas=0;
    fpa=fopen("ventas.bin","rb");
    if(fpa!=NULL)
    {
        fseek(fpa,0,SEEK_END);
        valVentas=ftell(fpa)/sizeof(Venta);
        fseek(fpa,0,SEEK_SET);

        //val = cantidad de ventas realizadas

        fread(&ventas,sizeof(Venta),valVentas,fpa);

        //leo las ventas en el arreglo "ventas"


    }
    fclose(fpa);


    //------------------

    FILE*pfile;
    int valPrep=0;
    PreparacionVenta preparados [TAM_MAX];
    pfile=fopen("stockventa.bin","r+b");
    if(pfile!=NULL)
    {
        fseek(pfile,0,SEEK_END);
        valPrep=ftell(pfile)/sizeof(PreparacionVenta);
        fread(&preparados,sizeof(PreparacionVenta),valPrep,pfile);

        //leo cantidad de preparados

        fseek(pfile,0,SEEK_SET);

            for (int i=0;i<valVentas;i++)
            {
               for (int j=0;j<valPrep;j++)
                {
                    fread(&preparados,sizeof(PreparacionVenta),1,pfile);
                    if (strcmpi(&ventas[i].items_pedido.nombre_preparacion,&preparados[j].nombre_preparacion)==0)
                    {
                          (&preparados[j].cantidad)-=(&ventas[i].items_pedido.cantidad);
                          fseek(pfile,-1*sizeof(PreparacionVenta),SEEK_CUR);
                          fwrite(&preparados[j].cantidad,sizeof(PreparacionVenta),1,pfile);
                    }
                }
            }

    }
    fclose(pfile);
    mostrarListapreparado(preparados,valPrep);
}
