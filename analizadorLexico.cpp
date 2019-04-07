#include "analizadorLexico.h"


AnalizadorLexico::AnalizadorLexico(){
	creaAutomatas();
}

void AnalizadorLexico::creaAutomatas(){
	Afn[0] = conjuncion();
	Afn[1] = disjuncion();
	Afn[2] = negacion();
	Afn[3] = condicional();
	Afn[4] = bicondicional();
	Afn[5] = parentesisIzq();
	Afn[6] = parentesisDer();
	Afn[7] = alfabeto();
	Afn[8] = espacioBlanco();
}

Automata *AnalizadorLexico::conjuncion(){
	return new Automata('&');
}

Automata *AnalizadorLexico::disjuncion(){
	return new Automata('|');
}

Automata *AnalizadorLexico::negacion(){
	return new Automata('!');
}

Automata *AnalizadorLexico::condicional(){
	Automata *linea = new Automata('-');
	Automata *mayorQue = new Automata('>');
	return linea->concatenar(mayorQue);
}

Automata *AnalizadorLexico::bicondicional(){
	Automata *menorQue = new Automata('<');
	Automata *cond = condicional();
	return menorQue->concatenar(cond);
}

Automata *AnalizadorLexico::parentesisIzq(){
	return new Automata('(');
}

Automata *AnalizadorLexico::parentesisDer(){
	return new Automata(')');
}

Automata *AnalizadorLexico::alfabeto(){
	Automata *A[26];
	const int abc = 65;
	for(int i = 0; i < 26; i++){
		A[i] = new Automata((char)abc+i);
	}
	for(int i = 1; i < 26; i++)
		A[0]->unir(A[i]);
	return A[0];
}

Automata *AnalizadorLexico::espacioBlanco(){
	return new Automata(' ');
}

Lista<Token*> AnalizadorLexico::getTokens(string cadena){
	string cadAux = cadena;
	string cadStack;
	Lista<Token*> Tokens;
	Token *tok;
	int pCad = 0;
	for(int i=0; i<cadAux.size(); i++){
		cadStack += cadAux[pCad];
		tok = clasificaToken(cadStack);
		if(tok->getTipo()!=0){
			cadStack.clear();
			if(tok->getTipo()!=Token::EspacioBlanco)			
				Tokens.pushFin(tok);			
		}
		pCad++;
	}
	return Tokens;
}

Token *AnalizadorLexico::clasificaToken(string cadena){
	Token *tok = new Token();
	if(Afn[0]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Conjuncion);
		tok->setNombre(cadena);
	}
	if(Afn[1]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Disjuncion);
		tok->setNombre(cadena);
	}
	if(Afn[2]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Negacion);
		tok->setNombre(cadena);
	}
	if(Afn[3]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Condicional);
		tok->setNombre(cadena);
	}
	if(Afn[4]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Bicondicional);
		tok->setNombre(cadena);
	}
	if(Afn[5]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::ParentesisIzq);
		tok->setNombre(cadena);
	}
	if(Afn[6]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::ParentesisDer);
		tok->setNombre(cadena);
	}
	if(Afn[7]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::Proposicion);
		tok->setNombre(cadena);
	}
	if(Afn[8]->evaluaCadena(cadena)){ 
		tok->setTipo(Token::EspacioBlanco);
		tok->setNombre(cadena);
	}
	return tok;
}






