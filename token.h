#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
using namespace std;

class Token{
	private:
		int Tipo;
		int Valor;
		string Nombre;
	public:
		static const int Conjuncion;
		static const int Disjuncion;
		static const int Negacion;
		static const int Condicional;
		static const int Bicondicional;
		static const int ParentesisIzq;
		static const int ParentesisDer;
		static const int Proposicion;
		static const int EspacioBlanco;
		Token();
		Token(const int tipo);
		Token(const int tipo, int valor, char nom);
		// Metodos Get
		int getTipo() const;
		int getValor() const;
		string getNombre() const;
		// Metodos Set
		void setTipo(int tipo);
		void setValor(int valor);
		void setNombre(string nom);
};

#endif

