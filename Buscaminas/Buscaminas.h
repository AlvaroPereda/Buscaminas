#ifndef BUSCAMINAS_H
#define BUSCAMINAS_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class tablero
{
    protected:
        int filas,columnas;
        vector<vector<char>> planoSinMinas;
    public:
        tablero();

        void setFilas(int f);
        void setColumnas(int c);
        void setPlanoSinMinas(vector<vector<char>>&plano);

        int getFilas() const;
        int getColumnas() const;
        vector<vector<char>>getPlanoSinMinas() const;

        friend ostream& operator<<(ostream&os, const tablero &t);
};
class tableroMinas: public tablero
{
private:
    int minas;
    vector<vector<char>> planoMinas;
    vector<vector<bool>> visitado;
public:
    tableroMinas();

    void setMinas(int m);
    int getMinas() const;

    void iniciarPlano();
    int introducirDato(int d1, int d2, int victoria, bool ponerBandera);
    int calcularMinasAlrededro(int fila,int columna);
    void mostrarCeldasContiguas(vector<vector<char>> &almacen, vector<vector<bool>>&visitado, int fila, int columna, int &victoria);
};
bool menu(string const &respuestaRepetir);
int menuDificultad(string const &nomJugador);
void validarPersonalizado(int& filas, int& columnas, int& minas);
void guardarArchivoTexto(const vector <string> &almacenNombres,const vector <int> &almacenPuntos);
void leerPuntuaciones();
void inicializarArchivoTexto();
bool comprobarNombre(const vector <string> &almacenNombres,string const &nomJugador);

#endif // BUSCAMINAS_H
