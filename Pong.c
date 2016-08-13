//pong hecho en c tomado del curso repaso, juegos en c
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#define  V 21
#define  H 75

void Borde(char Campo[V][H])
{
    int i, j;

    for(i=0; i<V; i++)
    {
        for(j=0; j<H; j++)
        {
            if(i==0 || i==V-1)
            {
                Campo[i][j] = '-';
            }//if
            else if(j==0 || j==H-1)
            {
                Campo[i][j] = '|';
            }//else if
            else
            {
                Campo[i][j] = ' ';
            }//else
        }//for anidado
    }//for

}//funcio para el borde

void RaquetaJugador(char Campo[V][H], int IniJug, int FinJug)
{
    int i, j;

    for(i=IniJug; i<=FinJug; i++)
    {
        for(j=2; j<=3; j++)
        {
            Campo[i][j] = 'X';

        }//for anidado
    }//for

}//barra jugador

void RaquetaIA(char Campo[V][H], int IniIa, int FinIa)
{
    int i, j;

    for(i=IniIa; i<=FinIa; i++)
    {
        for(j=H-4; j<=H-3; j++)
        {
            Campo[i][j] = 'X';

        }//for anidado
    }//for

}//barra maquina

void Pelota(char Campo[V][H], int pelX, int pelY)
{
    Campo[pelY][pelX] = 'O';
}//pelota

void LeerCamp(char Campo[V][H])
{
    int i, j;

    for(i=0; i<V; i++)
    {
        for(j=0; j<H; j++)
        {
            printf("%c", Campo[i][j]);
        }//for anidado
        printf("\n"); //salto de linea
    }//for
}//imprimir campo de juego

void Draw(char Campo[V][H])
{
    system("cls"); //limpiar la pantalla
    LeerCamp(Campo); //llamada a la funcion de arriba

}//primer funcion de la rutina

void Input(char Campo[V][H],int *pelX,int *pelY,int *IniJug,int *FinJug,int *IniIa,int *FinIa,int *ModX,int *ModY,int *ModIA, int *Gol)
{
    int  i; //contador
    char key; //tecla a capturar

    //verificacion
    if(*pelY == 1 || *pelY == V-2)  //chocando con escenario
    {
        *ModY *= -1;
    }//if
    if(*pelX == 1 || *pelX == H-2) //chocando con escenario
    {
        *Gol = 1;
    }//if

    if(*pelX == 4) //chocando con las raquetas
    {
        for(i = (*IniJug); i <= (*FinJug); i++)
        {
            if(i==(*pelY))
            {
              *ModX *= -1;
            }//if
        }//for
    }//if

    if(*pelX == H-5) //chocando con las raquetas
    {
        for(i=(*IniIa); i<=(*FinIa); i++)
        {
            if(i==(*pelY))
            {
              *ModX *= -1;
            }//if
        }//for
    }//if

    if(*IniIa==1 || *FinIa==V-1)
    {
        *ModIA *= -1;
    }//if

    //modificacion

    if(*Gol==0)
    {
       //Pelota
       *pelX += (*ModX);
       *pelX += (*ModY);

       //Raqueta de la maquina
       *IniIa += (*ModIA);
       *FinIa += (*ModIA);

       //Raqueta del jugador
       if(kbhit()==1) //provisional
       {
           key = getch(); //lo mismo que scanf sin enter

           if(key=='8')
           {
               if(*IniJug!=1)
               {
                   *IniJug -= 1;
                   *FinJug -= 1;
               }//if anidado
           }//if key
           if(key == '2')
           {
               if(*FinJug!=V-2)
               {
                   *IniJug += 1;
                   *FinJug += 1;
               }//if anidado
           }//if key
       }//if
    }//if

}//segunda funcion de la rutina

void Update(char Campo[V][H], int pelX, int pelY, int IniJug, int FinJug, int IniIa, int FinIa)
{
    Borde(Campo);
    RaquetaJugador(Campo, IniJug, FinJug);
    RaquetaIA(Campo, IniIa, FinIa);
    Pelota(Campo, pelX, pelY);
}//funcion casi identica a inicio

void GameLoop(char Campo[V][H],int pelX,int pelY,int IniJug,int FinJug,int IniIa,int FinIa,int ModX,int ModY,int ModIA)
{
    int Gol;
    Gol = 0;

    do{

        Draw(Campo);     //dibujar en la pantalla
        Input(Campo, &pelX, &pelY, &IniJug, &FinJug, &IniIa, &FinIa, &ModX, &ModY, &ModIA, &Gol);   //Modificar las posisciones
        Update(Campo, pelX, pelY, IniJug, FinJug, IniIa, FinIa); //Actualizar la matriz Campo[][]
        Sleep(10);
    }while(Gol == 0);

}//rutina del juego

void inicio(char Campo[V][H], int pelX, int pelY, int IniJug, int FinJug, int IniIa, int FinIa)
{
    //Declaracion de las funciones para el inicio del juego
    Borde(Campo);
    RaquetaJugador(Campo, IniJug, FinJug);
    RaquetaIA(Campo, IniIa, FinIa);
    Pelota(Campo, pelX, pelY);
}//funcion de inicio

int main()
{
    //variables de posicion
    int  pelX, pelY, IniJug, FinJug, IniIa, FinIa;
    char Campo[V][H];

    //variables de modificacion
    int ModX, ModY, ModIA;

    //posicion
    pelX   = 37;
    pelY   = 10;

    IniJug = 8;
    FinJug = 12;

    IniIa  = 8;
    FinIa  = 12;

    //modificacion
    ModX  = -1;
    ModY  = -1;
    ModIA = -1;

    inicio(Campo, pelX, pelY, IniJug, FinJug, IniIa, FinIa);
    GameLoop(Campo, pelX, pelY, IniJug, FinJug, IniIa, FinIa, ModX, ModY, ModIA);
    //0LeerCamp(Campo);
    system("pause");
    return 0;
}//main
