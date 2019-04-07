#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "estado.h"
#include "lista.h"
#include "pila.h"

class Automata {
	private:
		string Nombre;
		Estado *edoInicial;
		Estado *edoAceptacion;
	public:
		// Constructores
		Automata();
		Automata(char simbolo);
		Automata(string Nom, Estado *Inicial, Estado *Aceptacion);
		// Destructor
		~Automata();
		// Modifcaciones sobre automatas
		Automata *unir(Automata *afn);
		Automata *concatenar(Automata *afn);
		Automata *cerraduraPositiva();
		Automata *cerraduraEstrella();
		Automata *cerraduraInterrogacion();
		// Metodos de despliegue
		void displayTerminal();
		void displayAfdTabular();
		// Metodos de ayuda
		Estado *buscarEstado(int EdoId);
		Lista<Estado*> cerraduraEpsilon(Lista<int> EdoId);
		Lista<Estado*> cerraduraEpsilon(Lista<Estado*> Edos);
		Lista<Estado*> moverA(Lista<Estado*> E, char Simbolo);
		Lista<Estado*> Dtran(Lista<Estado*> E, char Simbolo);
		bool sonIguales(Lista<Estado*> L1, Lista<Estado*> L2);
		bool listaTiene(Lista< Lista<Estado*> > LE, Lista<Estado*> L);
		int listaEstaEn(Lista< Lista<Estado*> > LE, Lista<Estado*> L);
		Lista<char> getSimbolos();
		// Metodo de evaluacion
		bool evaluaCadena(string cadena);
		// Metodos Set
		void setEdoInicial(Estado *Inicial);
		void setEdoAceptacion(Estado *Aceptacion);
		void setNombre(string Nom);
		// Metodos Get
		Estado *getEdoInicial() const;
		Estado *getEdoAceptacion() const;
		string getNombre() const;
};


#endif

