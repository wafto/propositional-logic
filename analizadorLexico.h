#ifndef ANALIZADORLEXICO_H
#define ANALIZADORLEXICO_H

#include "automata.h"
#include "token.h"

class AnalizadorLexico{
	private:
		Automata *Afn[9];
		void creaAutomatas();
		Automata *conjuncion();
		Automata *disjuncion();
		Automata *negacion();
		Automata *condicional();
		Automata *parentesisIzq();
		Automata *parentesisDer();
		Automata *bicondicional();
		Automata *alfabeto();
		Automata *espacioBlanco();
	public:
		AnalizadorLexico();
		Lista<Token*> getTokens(string cadena);
		Token *clasificaToken(string cadena); 
		bool evalua(string cadena);
};

#endif

