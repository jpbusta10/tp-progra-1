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
void preparar(Receta[],int, StockIngrediente[],int, PreparacionVenta[],int*,float*);
void mostrarPreparado(PreparacionVenta);
void mostrarListapreparado(PreparacionVenta[],int);
void cargarPreciosPreparados (PrecioPreparacion[],int,Receta[]);
void mostrarPrecios(PrecioPreparacion);
void muestraListaPrecios(PrecioPreparacion[],int);
void modificarPrecioPreparado(Receta[],int);
void ingresarNuevaVenta(Receta[],int);
float costoTotalVenta (PedidoPreparacion[],int,int,PrecioPreparacion[],int);
void mostrarVenta (Venta);
void mostrarListaVentas (Venta[],int);
void devolucionVenta ();
void persistenciaStock(StockIngrediente[],int);
int descontarStockPreparados ();
void persistenciaPreparados(PreparacionVenta[],int);
void despecistenciaPreparados(PreparacionVenta[],int*);
void despecistenciaVentas(Venta[],int*);
int busquedaId(FILE*,int,Venta*);
void ganancia(float costo);
float ingresos();



int main()
{
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
    float costo=0;
    StockIngrediente stock [TAM_MAX];
    Receta recetas[TAM_MAX];
    PrecioPreparacion preciosPrep [TAM_MAX];
    PedidoPreparacion pedidoPrep [TAM_MAX];
    PreparacionVenta preparados [TAM_MAX];
    Venta ventaLista [TAM_MAX];
    despersistenciaStock(stock,&validosStock);
    despersistenciaReceta(recetas,&validosRecetas);
    while(true)
    {
        printf ("Ingrese opcion:\n");
        printf("1. Preparar demanda\n");
        printf ("2. Ver ingredientes no utilizados\n");
        printf ("3. Ver productos no vendidos\n");
        printf ("4. Ver ingreso total del dia\n");
        printf ("5. Ver ganancia total del dia\n");
        printf("6. Menu ventas\n");
        scanf ("%i",&opcion);

        switch (opcion)
        {
        case 1:
            printf("desea preparar la demanda?\n");
            fflush(stdin);
            scanf("%c",&continuar);
            if(continuar=='s'||continuar=='S')
            {
                preparar(recetas,validosRecetas,stock,validosStock,preparados,&validosPreparados,&costo);
            }
            else
            {
                despecistenciaPreparados(preparados,&validosPreparados);
            }
            fflush(stdin);
            system ("PAUSE");
            system ("cls");
            break;

        case 2:
            printf ("2. Ingredientes no utilizados\n");
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
        case 3:
            printf ("3. Productos no vendidos\n");
            despecistenciaPreparados(preparados,&validosPreparados);
            mostrarListapreparado(preparados,validosPreparados);
            printf("desea persistir los preparados? s/n\n");
            fflush(stdin);
            scanf("%c",&continuar);
            if(continuar=='s'||continuar=='S')
            {
                persistenciaPreparados(preparados,validosPreparados);
            }
            fflush(stdin);
            system ("PAUSE");
            system ("cls");
            break;
        case 4:
            printf ("4. Ingreso total del dia\n");
            ingresos();
            system ("PAUSE");
            system ("cls");
            break;
        case 5:
            printf ("5. Ganancia total del dia:\n");
            printf("costo: %.2f\n",costo);
            ganancia(costo);
            system ("PAUSE");
            system ("cls");
            break;
        case 6:
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
                    ingresarNuevaVenta(recetas,validosRecetas);
                    break;
                case 5:
                    despecistenciaVentas(ventaLista,&validosVenta);
                    mostrarListaVentas(ventaLista,validosVenta);
                    system ("PAUSE");
                    system ("cls");
                    break;
                case 6:
                    devolucionVenta ();
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
void preparar(Receta recetas[],int validosRecetas, StockIngrediente stock[],int validosStock, PreparacionVenta preparadosListos[],int* validosPreparados,float* acumuladorCosto)
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
    int n=0;
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
                        (*acumuladorCosto)=(*acumuladorCosto)+(aModificar*stock[indicS].costo);
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
                strcpy(preparadosListos[n].nombre_preparacion,recetas[indice].nombre_preparacion);
                preparadosListos[n].cantidad=preparados;
                n++;
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


void ingresarNuevaVenta (Receta recetas[],int validosRecetas)
{
    int flag=0;
    char nombre [TAM_MAX];
    char cont;
    int item=0;
    int contador=0;
    int validosPrecios=0;
    PrecioPreparacion precios[TAM_MAX];
    int cantidad=0;
    int indicePrecio=0;
    int indicePreparados=0;
    float acumulador=0;
    float valorItem=0;
    PreparacionVenta stockPreparados[TAM_MAX];
    int validosPreparados=0;
    Venta v;
    FILE* fp;
    fp=fopen("precios.bin","rb");
    if(fp!=NULL)
    {
        while(fread(&precios,sizeof(PrecioPreparacion),1,fp)>0)
        {
            validosPrecios++;
        }

        fclose(fp);
    }

    despecistenciaPreparados(stockPreparados,&validosPreparados);
    do
    {
        printf("de las siguientes preparaciones:\n");
        for(int i=0; i<validosPreparados; i++)
        {
            printf("%s\n",stockPreparados[i].nombre_preparacion);
        }
        printf("\nIngresar preparacion a vender: \n");
        fflush(stdin);
        gets (nombre);
        strcpy (v.items_pedido[item].nombre_preparacion,nombre);

        //hay stock preparados la venta??

        //flag=descontarStockPreparados ();


        for(int i=0; i<validosPrecios; i++)
        {
            if(strcmp(precios[i].nombre_preparacion,nombre)==0) //Busca el indice del item pedido en el arreglo de precios.
            {
                indicePrecio=i;
            }
        }
        for(int i=0; i<validosPreparados; i++)
        {
            if(strcmpi(stockPreparados[i].nombre_preparacion,nombre)==0)
            {
                indicePreparados=i;
            }
        }
        printf("Ingrese la cantidad a vender: \n");
        printf("tenemos: %i %s\n",stockPreparados[indicePreparados].cantidad,stockPreparados[indicePreparados].nombre_preparacion);
        scanf("%i",&cantidad);

        while(stockPreparados[indicePreparados].cantidad<cantidad)
        {
            printf("la cantidad tiene que ser menor o igula a %i\n",stockPreparados[indicePreparados].cantidad);
            scanf("%i",&cantidad);
        }
        stockPreparados[indicePreparados].cantidad=stockPreparados[indicePreparados].cantidad-cantidad;
        persistenciaPreparados(stockPreparados,validosPreparados);
        valorItem=cantidad*precios[indicePrecio].precio_venta;
        printf("el valor de su pedido es de %.2f\n",valorItem);
        v.items_pedido[item].cantidad=cantidad;
        item++;
        v.valor_total=acumulador+valorItem;
        acumulador=acumulador+valorItem;
        printf("Desea agregar mas items? s/n \n");
        fflush(stdin);
        scanf("%c",&cont);
        contador++;
        printf("el total de la venta es: %.2f\n",acumulador);
    }
    while (cont=='s' || cont=='S' && item<=20);
    v.cantItems=item;
    FILE* jp;
    Venta vent[TAM_MAX];
    jp=fopen("ventas.bin","rb");
    int val=0;
    if(jp!=NULL)
    {
        fseek(jp,0,SEEK_END);
        val=ftell(jp)/sizeof(Venta);
        fseek(jp,0,SEEK_SET);
        v.idVenta=val;
        fread(vent,sizeof(Venta),val,jp);
    }
    fclose(jp);
    if(val==0)
    {
        vent[val].idVenta=0;
    }
    else
    {
        vent[val].idVenta=v.idVenta;
    }
    vent[val].cantItems=v.cantItems;
    for(int i=0; i<vent[val].cantItems; i++)
    {
        strcpy(vent[val].items_pedido[i].nombre_preparacion,v.items_pedido[i].nombre_preparacion);
        vent[val].items_pedido[i].cantidad=v.items_pedido[i].cantidad;
    }
    vent[val].valor_total=v.valor_total;
    vent[val].baja=0;
    mostrarVenta(vent[val]);
    FILE*kk;
    kk=fopen("ventas.bin","wb");
    if(kk!=NULL)
    {
        fwrite(vent,sizeof(Venta),(val+1),kk);
    }
    fclose(kk);

}


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
    printf("Valor total venta: %.2f\n",v.valor_total);
    //printf("baja: %i\n",v.baja);
}

void mostrarListaVentas(Venta ventaLista[],int validosId)
{
    for(int i=0; i<validosId; i++)
    {

        mostrarVenta(ventaLista[i]);

    }
}

void devolucionVenta()
{
    int id=0;
    Venta ventas[TAM_MAX];
    Venta v;
    int validosVentas;
    int indiceVenta=0;
    int i=0;
    printf("Ingrese el Id de la venta que quiere dar de baja\n");
    scanf("%i",&id);
    FILE* fp;
    fp=fopen("ventas.bin","r+b");
    if(fp!=NULL)
    {
        if(busquedaId(fp,id,&v)==1)
        {
            v.baja=1;
            fseek(fp,sizeof(Venta)*-1,SEEK_CUR);
            fwrite(&v,sizeof(Venta),1,fp);

        }
        printf("usted a dado de baja la venta %i\n",id);

        fclose(fp);

    }

}
void despecistenciaVentas(Venta ventas[],int* validosVentas)
{
    FILE* fp;
    fp=fopen("ventas.bin","rb");
    int i=0;
    if(fp!=NULL)
    {
        while(fread(&ventas[i],sizeof(Venta),1,fp)>0)
        {
            if(ventas[i].baja==0)
                i++;
        }
        (*validosVentas)=i;
    }
}
int busquedaId(FILE* fp,int id,Venta* v)
{
    int flag=0;
    while(fread(v,sizeof(Venta),1,fp)>0&&id!=(*v).idVenta);
    if(ftell(fp)>0&&id==(*v).idVenta)
    {
        flag=1;
    }
    return flag;
}
float ingresos()
{
    Venta ventas[TAM_MAX];
    int validosVentas=0;
    float suma=0;
    despecistenciaVentas(ventas,&validosVentas);
    for(int i=0;i<validosVentas;i++)
    {
        suma=suma+ventas[i].valor_total;
    }
    printf("los ingresos totales son %.2f\n",suma);
    return suma;
}
void ganancia(float costo)
{
    float ing=0;
    float gan=0;
    ing=ingresos();
    gan=ing-costo;
    printf("La ganancia total es de %.2f\n",gan);

}
