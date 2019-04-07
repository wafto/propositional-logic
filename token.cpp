#include "token.h"

const int Token::Conjuncion    = 100;
const int Token::Disjuncion    = 200;
const int Token::Negacion      = 300;
const int Token::Condicional   = 400;
const int Token::Bicondicional = 500;
const int Token::ParentesisIzq = 600;
const int Token::ParentesisDer = 700;
const int Token::Proposicion   = 800;
const int Token::EspacioBlanco = 900;

Token::Token(){
	Tipo = 0;
}

Token::Token(const int tipo){
	Tipo = tipo;
}

Token::Token(const int tipo, int valor, char nom){
	Tipo = tipo;
	Valor = valor;
	Nombre = nom;
}
// Metodos Get

int Token::getTipo() const{
	return Tipo;
}

int Token::getValor() const{
	return Valor;
}

string Token::getNombre() const{
	return Nombre;
}

// Metodos Set

void Token::setTipo(int tipo){
	Tipo = tipo;
}

void Token::setValor(int valor){
	Valor = valor;
}

void Token::setNombre(string nom){
	Nombre = nom;
}


