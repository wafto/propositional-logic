#include "analizadorSintactico.h"

AnalizadorSintactico::AnalizadorSintactico(Lista<Token*> Tokens){
	for(int i=0; i<Tokens.numElem(); i++){
		Toks.pushFin(Tokens.getInfoAt(i));
	}
	aceptable  = E(&resultado);
}

int AnalizadorSintactico::Aceptable() const{
	return aceptable;
}

bool AnalizadorSintactico::Resultado() const{
	return resultado;
}

bool AnalizadorSintactico::E(bool *ApV){
	if(T(ApV)) return Ep(ApV);
	return 0;
}

bool AnalizadorSintactico::Ep(bool *ApV){
	bool Aux;
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Condicional){
			if(T(&Aux)){
				*ApV = (*ApV==true && Aux==false) ? false : true;
				return Ep(ApV); 
			}
			return 0;
		}
		Toks.pushIni(Tok);
	}
	return 1;
}

bool AnalizadorSintactico::T(bool *ApV){
	if(F(ApV)) return Tp(ApV);
	return 0;
}

bool AnalizadorSintactico::Tp(bool *ApV){
	bool Aux;
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Bicondicional){
			if(F(&Aux)){
				*ApV = ((*ApV)==Aux) ? true : false;
				return Tp(ApV);
			}
			return 0;
		}
		Toks.pushIni(Tok);
	}
	return 1;	
}

bool AnalizadorSintactico::F(bool *ApV){
	if(H(ApV)) return Fp(ApV);
	return 0;
}

bool AnalizadorSintactico::Fp(bool *ApV){
	bool Aux;
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Disjuncion){
			if(H(&Aux)){
				*ApV = ( *ApV || Aux );
				return Fp(ApV);
			}
			return 0;
		}
		Toks.pushIni(Tok);
	}
	return 1;
}

bool AnalizadorSintactico::H(bool *ApV){
	if(I(ApV)) return Hp(ApV);
	return 0;
}

bool AnalizadorSintactico::Hp(bool *ApV){
	bool Aux;
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Conjuncion){
			if(I(&Aux)){
				*ApV = ( *ApV && Aux );
				return Hp(ApV);
			}
			return 0;
		}
		Toks.pushIni(Tok);
	}
	return 1;
}

bool AnalizadorSintactico::I(bool *ApV){
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Negacion){
			flags.push(false);
		}
		if(Tok->getTipo()!=Token::Negacion){
			Toks.pushIni(Tok);
		}
		if(K(ApV)){
			while(!flags.estaVacia()){
				bool aux;
				*ApV = !*ApV;
				flags.pop(aux);
			}
			return 1;
		}
	}
	return 0;
}

bool AnalizadorSintactico::K(bool *ApV){
	Token *Tok;
	Toks.popIni(Tok);
	if(Tok!=NULL){
		if(Tok->getTipo()==Token::Proposicion){
			*ApV = Tok->getValor();
			return 1;
		}
		if(Tok->getTipo()==Token::ParentesisIzq){
			if(E(ApV)){
				Toks.popIni(Tok);
				if(Tok->getTipo()==Token::ParentesisDer){
					return 1;
				}
			}
		}
	}
	return 0;
}











