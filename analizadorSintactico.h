#ifndef ANALIZADORSINTACTICO_H
#define ANALIZADORSINTACTICO_H

#include "analizadorLexico.h"


class AnalizadorSintactico{
	private:
		int aceptable;
		bool resultado;
		Lista<Token*> Toks;
		Pila<bool> flags;
	public:
		AnalizadorSintactico(Lista<Token*> Tokens);
		int Aceptable() const;
		bool Resultado() const;
		bool E(bool *ApV);
		bool Ep(bool *ApV);
		bool T(bool *ApV);
		bool Tp(bool *ApV);
		bool F(bool *ApV);
		bool Fp(bool *ApV);
		bool H(bool *ApV);
		bool Hp(bool *ApV);
		bool I(bool *ApV);
		bool K(bool *ApV);
};

#endif


