#ifndef ESTADO_H
#define ESTADO_H

#define EPSILON '$'
#include <iostream>
#include <string>
using namespace std;

class Estado {
	private:
		static int contador;
		int Identificador;
		Estado *Transicion1;
		Estado *Transicion2;
		char Simbolo1;
		char Simbolo2;
	public:
		// Constructores
		Estado();
		Estado(Estado *e1, char simb1);
		Estado(Estado *e1, char simb1, Estado *e2, char simb2);
		// Destructor
		~Estado();
		// Metodos de despliegue
		void displayTerminal();
		// Metodos Set
		void setId(int id);
		void setTransicion1(Estado *estado);
		void setTransicion2(Estado *estado);
		void setSimbolo1(char simbolo);
		void setSimbolo2(char simbolo);
		// Metodos Get
		int getId() const;
		Estado *getTransicion1() const;
		Estado *getTransicion2() const;
		char getSimbolo1() const;
		char getSimbolo2() const;
};

#endif

