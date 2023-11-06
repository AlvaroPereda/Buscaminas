//Alvaro Pereda Sanchez y Pedro Zuñeda Diego. main.cpp
#include <iostream>
#include <string>
#include <vector>
#include "Buscaminas.h"

using namespace std;

int main()
{
    vector <string> almacenNombres;
    vector <int> almacenPuntos;
    string nomJugador,bandera,respuestaRepetir{"no"};
    bool ponerBandera{false};
    int filaPerso,colPerso,minasPerso;

    inicializarArchivoTexto();//sirve para reiniciar el archivo de texto para que no se muestren las puntuaciones de partidas anteriores

    do//bucle que repite todo el juego si el usuario lo desea
    {
        tableroMinas tab;
        int coordenadaF,coordenadaC,victoria{0};
        if(menu(respuestaRepetir))//se muestra el menú principal
            break;//el juego acaba cuando el usuario elige la opcion 4
        system("cls");
        cout << "\n\n\tPor favor, introduce tu nombre: ";
        cin >> nomJugador;

        system("cls");
        switch(menuDificultad(nomJugador))
        {
            case 1:
                tab.setFilas(6);
                tab.setColumnas(6);
                tab.setMinas(5);
                break;
            case 2:
                tab.setFilas(9);
                tab.setColumnas(9);
                tab.setMinas(10);
                break;
            case 3:
                validarPersonalizado(filaPerso,colPerso,minasPerso);//valida los datos personalizados, y pasa los datos por referencia
                tab.setFilas(filaPerso);
                tab.setColumnas(colPerso);
                tab.setMinas(minasPerso);
                break;
            default:
                break;
        }
            system("cls");
            tab.iniciarPlano();
            cout<<tab;//se muestra el tablero
        do//Bucle del mecanismo del Buscaminas
        {
            cout << "Quieres poner una bandera(si/no): ";
            cin >> bandera;
            do//Bucle para que introduzca una posición del tablero correcta
            {
                cout<<nomJugador<<" escribe la coordenada que quieras revelar: \n";
                try
                {
                    cin>>coordenadaF;
                    cin>>coordenadaC;
                    if(coordenadaF<0 || coordenadaF>tab.getFilas()-1 || coordenadaC<0 || coordenadaC>tab.getColumnas()-1)
                        throw 1;
                }
                catch (int)
                {
                    cout << "\nERROR, la coordenada que ha seleccionado no se ecuentra en el tablero\n\n";
                    system("pause");
                    system("cls");
                    cout<<tab;
                }


            }while(coordenadaF<0 || coordenadaF>tab.getFilas()-1 || coordenadaC<0 || coordenadaC>tab.getColumnas()-1);

            system("cls");

            if(bandera=="Si" || bandera=="si" || bandera=="sI" || bandera=="SI" || bandera=="s" || bandera=="S")
                ponerBandera=true;

            victoria=tab.introducirDato(coordenadaF,coordenadaC,victoria,ponerBandera);//vitoria calcula cuantos movimientos acertados a relizado el usuario

            if(victoria==-1)//si victoria es -1 significa que el usuario ha encontrado una mina
            {
                cout<<tab;
                break;
            }
            cout<<tab;
            ponerBandera=false;

        }while(victoria!=(tab.getFilas()*tab.getColumnas())-tab.getMinas());

        if(comprobarNombre(almacenNombres,nomJugador))
        {
            almacenNombres.push_back(nomJugador);
            almacenPuntos.push_back(0);
        }

        if(victoria==(tab.getFilas()*tab.getColumnas())-tab.getMinas())//comprobación para ver si ha ganado
        {
            cout<<"\nFELICIDADES, HAS GANADO AL BUSCAMINAS.\n";
            for(int i{0};i<almacenNombres.size();i++)
            {
                if(almacenNombres.at(i)==nomJugador)
                    almacenPuntos.at(i)=almacenPuntos.at(i)+1;
            }
        }
        else if (victoria==-1)//comprobación para ver si ha perdido
            cout<<"\nHas encontrado una mina. Has perdido.\n";

        guardarArchivoTexto(almacenNombres,almacenPuntos);//guarda los nombres y puntuaciones de los jugadores

        cout<<"Quieres volver a jugar(si/no): ";
        cin>>respuestaRepetir;

    }while(respuestaRepetir=="si" || respuestaRepetir=="Si" || respuestaRepetir=="sI" || respuestaRepetir=="SI" || respuestaRepetir=="s" || respuestaRepetir=="S");

    cout<<"Gracias por jugar al buscaminas\n\n";
    return 0;
}


