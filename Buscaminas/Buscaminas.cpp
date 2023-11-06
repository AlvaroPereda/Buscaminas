#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include "Buscaminas.h"

using namespace std;

bool menu(const string &respuestaRepetir)
{
    int opcion;
    do
    {
        do//Bucle que repite hasta que el usuario elija una opción valida
        {
            system("cls");
            try
            {
                cout << "\n\n\tBienvenido al juego del Buscaminas\n";
                cout << "\n1.- Iniciar juego.";
                cout << "\n2.- Reglas.";
                cout << "\n3.- Puntuaciones.";
                cout << "\n4.- Salir del juego. \n\n";
                cout << "Selecciona una opcion: ";
                cin>>opcion;
                if(opcion<1 || opcion>4)
                    throw 1;
            }
            catch (int)
            {
                cout << "\nERROR, la opcion que has introducido no existe.\n\n";
                system("pause");
            }

        }while(opcion<1 || opcion>4);

        system("cls");
        switch(opcion)
        {
            case 2:
                cout << "\n\n\tReglas. \n";
                cout <<"\n1. Al iniciar el juego, se muestra un tablero cuadrado con un numero de casillas ocultas.";
                cout <<"\n2. El objetivo es despejar todas las casillas que no contengan minas, haciendo clic sobre ellas.";
                cout <<"\n3. Si una casilla que no tiene mina, se mostrara un numero que indica la cantidad de minas que hay en las casillas adyacentes a esa casilla. Si la casilla no tiene minas adyacentes, se revelaran como un guion '-' ";
                cout <<"\n4. Si haces clic sobre una casilla que tiene una mina, perderas el juego.";
                cout <<"\n5. Para marcar una casilla que creas que contiene una mina, utiliza la opcion de colocar una bandera. Esto marcara la casilla con una 'B'.";
                cout <<"\n6. Si todas las casillas que no contienen minas estan descubiertas y todas las casillas que contienen minas están marcadas con banderas, habras ganado el juego.";
                cout <<"\n7. La eleccion de dificultad sera esta: Facil (tablero 6 * 6, 5 minas) o Experto (tablero 9 * 9, 10 minas).\n\n";
                system("pause");
                break;
            case 3:
                if(respuestaRepetir=="no")
                    cout<<"No hay puntuaciones registradas.\n\n";
                else
                    leerPuntuaciones();
                system("pause");
                break;
            case 4:
                return true;
                break;
        }
    }while(opcion!=1);
    return false;
}
int menuDificultad(string const &nomJugador)
{
    int opcion;
    do
    {
        system("cls");
        cout <<"\n"<<nomJugador <<" introduce el nivel de dificultad (1,2,3)\n\n";
        try
        {
            cout<<"\t1.- Nivel facil.\n";
            cout<<"\t2.- Nivel experto.\n";
            cout<<"\t3.- Nivel personalizado.\n";
            cin>>opcion;
            if(opcion<1 || opcion>3)
                throw 1;
        }
        catch (int)
        {
            cout<<"\nERROR, al seleccionar el nivel de dificultad\n\n";
            system("pause");
        }
    }while(opcion<1 || opcion>3);
    return opcion;
}
void validarPersonalizado(int& filaPerso, int& colPerso, int& minasPerso)
{
    bool confirmar;
    do
    {
        confirmar=false;
        system("cls");
        try
        {
            do
            {
                cout<<"\n\tEscribe el numero de filas: ";
                cin>>filaPerso;
                if(filaPerso < 1)
                {
                    confirmar=true;;
                    throw 1;
                }
            }while (filaPerso < 1);
            do
            {
                cout<<"\n\tEscribe el numero de columnas: ";
                cin>>colPerso;
                if(colPerso < 1)
                {
                    confirmar=true;;
                    throw 1;
                }
            }while (colPerso < 1);
            do
            {
                cout<<"\n\tEscribe el numero de minas: ";
                cin>>minasPerso;
                if(minasPerso < 1)
                {
                    confirmar=true;;
                    throw 1;
                }
                else if(minasPerso > (filaPerso*colPerso)-1)
                {
                    confirmar=true;;
                    throw 2;
                }
            }while (minasPerso < 1 || minasPerso > (filaPerso*colPerso)-1);
            }
        catch (int error)
        {
            if (error==1)
                cout<<"\nERROR, el numero no puede ser menor que 1\n\n";
            else if(error==2)
                cout<<"\nERROR, el numero de minas no puede ser mayor que el numero del tablero\n\n";
            system("pause");
        }
    }while(confirmar);
}
tablero::tablero()
{
    filas=0;
    columnas=0;
}
tableroMinas::tableroMinas()
{
    minas=0;
}
void tablero::setFilas(int f) {
    filas=f;
}
void tablero::setColumnas(int c) {
    columnas=c;
}
void tableroMinas::setMinas(int m) {
    minas=m;
}
int tablero::getFilas() const {
    return filas;
}
int tablero::getColumnas() const {
    return columnas;
}
int tableroMinas::getMinas() const {
    return minas;
}
vector<vector<char>> tablero::getPlanoSinMinas() const
{
    return planoSinMinas;
}
void tablero::setPlanoSinMinas(vector<vector<char>>&plano)
{
    planoSinMinas=plano;
}
void tableroMinas::iniciarPlano() {
    srand(time(NULL));
    vector<vector<char>> almacen;
    vector<char> aux;
    vector<bool> auxV;
    int minasColocadas{0}, minasAlrededor{0};

    for(int i{0}; i<getFilas(); i++)
    {
        planoMinas.push_back(aux);
        for(int j{0}; j<getColumnas(); j++) {
            planoMinas.at(i).push_back('_');
        }
    }

    for(int i{0}; i<getFilas(); i++)
    {
        almacen.push_back(aux);
        for(int j{0}; j<getColumnas(); j++) {
            almacen.at(i).push_back('.');
        }
    }

    for(int i{0}; i<getFilas(); i++)
    {
        visitado.push_back(auxV);
        for(int j{0}; j<getColumnas(); j++) {
            visitado.at(i).push_back(false);
        }
    }

    setPlanoSinMinas(almacen);

    do
    {
        int randomF=rand() % getFilas();
        int randomC=rand() % getColumnas();
        if(planoMinas.at(randomF).at(randomC)!='*')
        {
            planoMinas.at(randomF).at(randomC)='*';
            minasColocadas++;
        }
    }while(minasColocadas!=minas);

    for(int i{0}; i<getFilas(); i++)
    {
        for(int j{0}; j<getColumnas(); j++)
        {
            if(planoMinas.at(i).at(j)!='*')
            {
                minasAlrededor=calcularMinasAlrededro(i,j);
                string minasAlrededorString= to_string(minasAlrededor);
                if(minasAlrededorString=="0")
                    minasAlrededorString="-";
                planoMinas.at(i).at(j)=minasAlrededorString.at(0);
            }
        }
    }
}

int tableroMinas::introducirDato(int d1, int d2, int victoria, bool ponerBandera)
{

    vector<vector<char>> almacen=getPlanoSinMinas();

    if(ponerBandera==true)
    {
        try
        {
            if(almacen.at(d1).at(d2)=='.')//esta comparación sirve para ver si se puede colocar una bandera en una casilla ya selecionada
            {
                almacen.at(d1).at(d2)='B';
                setPlanoSinMinas(almacen);
            }
            else if(almacen.at(d1).at(d2)=='B')
                throw 1;
            else
                throw 2;

        }
        catch (int error)
        {
            if (error==1)
                cout<<"ERROR, la casilla ya tiene una bandera\n";
            if (error==2)
                cout<<"ERROR, la casilla ya se ha revelado\n";
        }
    }
    else
    {
        if(planoMinas.at(d1).at(d2)=='*')
        {
            for(int i{0};i<getFilas();i++)
            {
                for(int j{0};j<getColumnas();j++)
                {
                    if(planoMinas.at(i).at(j)=='*')
                    {
                        almacen.at(i).at(j)=planoMinas.at(i).at(j);
                        setPlanoSinMinas(almacen);
                    }
                }
          }
            return -1;
        }
        else
        {
            try
            {
                if(almacen.at(d1).at(d2)=='.' || almacen.at(d1).at(d2)=='B')
                {
                    if(planoMinas.at(d1).at(d2)=='-')//esta opción sirve para descubrir las celdas alrededor que no tengan minas en las celdas contiguas hasta llegar los límites del tablero o celdas con números
                    {
                        mostrarCeldasContiguas(almacen,visitado,d1,d2,victoria);
                        setPlanoSinMinas(almacen);
                    }
                    else if(almacen.at(d1).at(d2)=='.' || almacen.at(d1).at(d2)=='B')
                    {
                        almacen.at(d1).at(d2)=planoMinas.at(d1).at(d2);
                        visitado.at(d1).at(d2)=true;//marcamos la casilla como visitada
                        setPlanoSinMinas(almacen);
                        victoria++;
                    }

                }
                else
                    throw 1;
            }
            catch (int)
            {
                cout<<"ERROR, la casilla ya se ha seleccionado anteriormente\n";
            }
        }
    }

    return victoria;
}
void tableroMinas::mostrarCeldasContiguas(vector<vector<char> > &almacen, vector<vector<bool>>&visitado, int fila, int columna,int &victoria)
{
    if (fila < 0 || fila >= getFilas() || columna < 0 || columna >= getColumnas() || visitado.at(fila).at(columna)==true)
            return;
    visitado.at(fila).at(columna)=true;//marcamos la casilla como vista

    almacen.at(fila).at(columna)=planoMinas.at(fila).at(columna);//revelamos la casilla que hay en el plano minas

    if(almacen.at(fila).at(columna)!='-')//si la casilla contiene un número o bomba se termina la función
    {
        if(almacen.at(fila).at(columna)=='*')
            return;
        else
        {
            victoria++;
            return;
        }
    }
    else
    {
            victoria++;
            mostrarCeldasContiguas(almacen,visitado, fila-1, columna,victoria); // Arriba
            mostrarCeldasContiguas(almacen,visitado, fila+1, columna,victoria); // Abajo
            mostrarCeldasContiguas(almacen,visitado, fila, columna-1,victoria); // Izquierda
            mostrarCeldasContiguas(almacen,visitado, fila, columna+1,victoria); // Derecha
            mostrarCeldasContiguas(almacen,visitado, fila-1, columna-1,victoria); // Abajo izquierda
            mostrarCeldasContiguas(almacen,visitado, fila-1, columna+1,victoria); // Abajo derecha
            mostrarCeldasContiguas(almacen,visitado, fila+1, columna+1,victoria); // Arriba derecha
            mostrarCeldasContiguas(almacen,visitado, fila+1, columna-1,victoria); // Arriba izquierda
    }

}
ostream& operator<<(ostream& os, const tablero& t)
{
    os<<"  ";

    for(int i{0};i<t.columnas;i++)
    {
        os<<i<<" ";
    }

    os<<"\n";

    for(int i{0};i<t.filas;i++)
    {
        os<<i<<" ";
        for(int j{0};j<t.columnas;j++)
        {
            os<<t.planoSinMinas.at(i).at(j)<<" ";
        }
        os<<"\n";
    }

    os<<endl;
    return os;
}

int tableroMinas::calcularMinasAlrededro(int fila, int columna) {
    int minasAlrededor {0};
    for (int i = fila-1; i <= fila+1; i++)
    {
        for (int j = columna-1; j <= columna+1; j++)
        {
            if (i >= 0 && i < getFilas() && j >= 0 && j < getColumnas() && !(i == fila && j == columna))
            {
                if (planoMinas.at(i).at(j) == '*')
                    minasAlrededor++;
            }
        }
    }
    return minasAlrededor;
}
void guardarArchivoTexto(const vector<string> &almacenNombres, const vector<int> &almacenPuntos)
{
    ofstream puntuaciones;

    puntuaciones.open("puntuaciones.txt");
    puntuaciones<<"\n\t\t\t\t\tPuntuaciones"<<endl;
    for (int i{0};i<almacenNombres.size();i++)
    {
        puntuaciones<<almacenNombres.at(i)<<": "<<almacenPuntos.at(i)<<" puntos"<<endl;
    }
    puntuaciones.close();

}
void leerPuntuaciones()
{
    ifstream leer;
    string frase;

    leer.open("puntuaciones.txt");
    while(!leer.eof())//mientras no sea el final del archivo
    {
        getline(leer,frase);
        cout<<frase<<endl;
    }

    leer.close();
}
void inicializarArchivoTexto()
{
    ofstream puntuaciones;
    puntuaciones.open("puntuaciones.txt");
    puntuaciones.close();
}
bool comprobarNombre(const vector <string> &almacenNombres, const string &nomJugador)
{

    for(int i{0};i<almacenNombres.size();i++)
    {
        if(almacenNombres.at(i)==nomJugador)
            return false;//el nombre ya esta en el almacen
    }
    return true;//el nombre no esta en el almacen
}
