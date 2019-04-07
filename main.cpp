/**********************************************************************************
**
**	Instituto Politecnico Nacional
**	Escuela Superior de Computo, Mexico Distrito Federal
**
**	Inteligencia Artificial
**		Profesor: Benjamin Luna Benoso
**		Autor: Aftab Hussain Miranda
**		Grupo: 6CV4
**
**	Descripcion: Este pequeño programa analiza una cadena, y a partir de esta
**		     primero extrae los tokens de la cadena y de las proposiciones
**		     pide un valor verdadero o falso. Luego a partir de una
**		     gramatica procede a evaluar y regresar un valor verdadero o 
**		     falso segun sea el caso.
**
**	Compilacion: la manera mas facil para compilarlo es tener todos los
**		     archivos en una carpeta (no mezclado con otros archivos) y en
**		     la consola ejecutar:
**
**		     g++ *.cpp -o nombreDelPrograma
**
**		     Nota: en la consola recuerda estar en el directorio.
**
**********************************************************************************/

#include "analizadorSintactico.h"
#include <stdlib.h>

int main(){
	Token *Tok;
	Lista<char> Proposiciones;
	Lista<int> Valor;
	AnalizadorLexico *AnalizaLex = new AnalizadorLexico();
	string expresion;

	cout<<"\tModo de uso:"<<endl;
	cout<<"\t  - Conjuncion    :   &"<<endl;
	cout<<"\t  - Disjuncion    :   |"<<endl;
	cout<<"\t  - Negacion      :   !"<<endl;
	cout<<"\t  - Condicional   :   ->"<<endl;
	cout<<"\t  - Bicondicional :   <->"<<endl;
	cout<<"\t  - Tambien puede usar parentesis ( , )"<<endl;
	cout<<"\tEjemplo : A->B&!(C|A)<->B"<<endl;
	cout<<"\tNota: Para las negaciones !!P se debe escribir como:"<<endl;
	cout<<"\t      !(!P) o bien !(!(P)) ya que en la gramatica no"<<endl;
	cout<<"\t      acepta nagacion seguido de negacion."<<endl;

	cout<<"\tPor favor ingrese la expresion para su evaluacion"<<endl;
	cout<<"\tExpresion : "; cin>> expresion ;

	// Fase de Analisis Lexico

	Lista<Token*> tokens = AnalizaLex->getTokens(expresion);

	cout<<"\tPara las siguientes Proposiciones por favor ingrese"<<endl;
	cout<<"\t 0 para Falso"<<endl;
	cout<<"\t 1 para Verdadero"<<endl;

	// En esta Fase Ontenemos las Proposiciones diferentes y les ponemos valor

	for(int i=0; i<tokens.numElem(); i++){
		Tok = tokens.getInfoAt(i);
		if(Tok->getTipo()==Token::Proposicion){
			char Prop = Tok->getNombre()[0];
			if(Proposiciones.contiene(Prop)){
				int k = Proposiciones.iContiene(Prop);
				if(k==-1){
					cout<<"Ocurrio un Error!"<<endl;
					return -1;
				}
				Tok->setValor(Valor.getInfoAt(k));
			}
			if(!Proposiciones.contiene(Prop)){
				int tipo;
				cout<<"\t -> "<< Prop <<" : "; cin>> tipo;
				if(tipo>0) Tok->setValor(1);
				if(tipo<=0) Tok->setValor(0);
				Proposiciones.pushFin(Prop);
				Valor.pushFin(Tok->getValor());
			}
		}
	}
	
	// Fase de Analisis Sintactico
	/*
		La Gramatica utilizada para este caso en particular es:
		
			E   ->   E->T   | T
			T   ->   T<-> F   | F
			F   ->   F or H  | H
			H   ->   H & I  | I
			I   ->   K  |  !K
			K   ->   (E)  |  PROPOSICION
			
		De esta gramatica podemos ver que tiene recursividad en la izquierda
		por lo tanto se la quitamos para evitar ambiguedad y nuestra nueva 
		gramatica queda:
		
			E   ->  TE'
			E'  ->  ->TE' | epsilon
			T   ->  FT'
			T'  ->  <->FT' | epsilon
			F   ->  HF'
			F'  ->  orHF' | epsilon
			H   ->  IH'
			H'  ->  &IH' | epsilon
			I   ->  K | !K
 			K   ->  (E) | PROPOSICION
			
		Esto nos ayuda verificar que la cadena de entrada tenga sintaxis correcta
		y para aprovechar mejor el analizador sintactico, utilizamos esta para
		obtener el valor final, esto seria el "analisis semantico".
	
	*/
	
	AnalizadorSintactico *AS  = new AnalizadorSintactico(tokens); 	
	cout<<"\tLa cadena introducida es Sintacticamente: ";
	if(AS->Aceptable()==1){ cout<<"CORRECTA"<<endl;}
	if(AS->Aceptable()==0){ cout<<"INCORRECTA"<<endl; return 0;}

	cout<<"\tEl valor de la expresion despues de evaluarla es : ";
	if(AS->Resultado()) cout<<"VERDADERA"<<endl;
	if(!AS->Resultado()) cout<<"FALSA"<<endl;
	
	system("PAUSE");

}



