#include "automata.h"


// Constructores
Automata::Automata(){
	Nombre = "Sin Nombre";
	edoInicial = NULL;
	edoAceptacion = NULL;
}
Automata::Automata(string Nom, Estado *Inicial, Estado *Aceptacion){
	Nombre = Nom;
	edoInicial = Inicial;
	edoAceptacion = Aceptacion;
}
Automata::Automata(char simbolo){
	Nombre = simbolo;
	edoInicial = new Estado();
	edoAceptacion = new Estado();
	edoInicial->setTransicion1(edoAceptacion);
	edoInicial->setSimbolo1(simbolo);
}

// Destructor
Automata::~Automata(){
	Nombre = "Sin Nombre";
	edoInicial = edoAceptacion = NULL;
}

// Modifcaciones sobre automatas
Automata *Automata::unir(Automata *afn){
	if(afn->getEdoInicial()==NULL || afn->getEdoAceptacion()==NULL) 
		return NULL;
	Nombre = Nombre+"|"+afn->getNombre();
	Estado *EdoAux1 = new Estado();
	Estado *EdoAux2 = new Estado();
	EdoAux1->setTransicion1(edoInicial);
	EdoAux1->setTransicion2(afn->getEdoInicial());
	afn->getEdoAceptacion()->setTransicion1(EdoAux2);
	this->getEdoAceptacion()->setTransicion1(EdoAux2);
	edoInicial = EdoAux1;
	edoAceptacion = EdoAux2;
	delete afn;
	return this;
}
Automata *Automata::concatenar(Automata *afn){
	if(afn->getEdoInicial()==NULL || afn->getEdoAceptacion()==NULL) 
		return NULL;
	Nombre = Nombre + afn->getNombre();
	Estado *Aux = afn->getEdoInicial();
	if(Aux->getTransicion1()!=NULL){
		edoAceptacion->setTransicion1(Aux->getTransicion1());
		edoAceptacion->setSimbolo1(Aux->getSimbolo1());
	}
	if(Aux->getTransicion2()!=NULL){
		edoAceptacion->setTransicion2(Aux->getTransicion2());
		edoAceptacion->setSimbolo2(Aux->getSimbolo2());
	}
	edoAceptacion = afn->getEdoAceptacion();
	delete Aux;
	delete afn;
	return this;
}
Automata *Automata::cerraduraPositiva(){
	if(edoInicial==NULL || edoAceptacion==NULL) return NULL;
	Nombre = "("+Nombre+")"+"+";
	Estado *EdoAux1 = new Estado();
	Estado *EdoAux2 = new Estado();
	edoAceptacion->setTransicion1(EdoAux2);
	edoAceptacion->setTransicion2(edoInicial);
	EdoAux1->setTransicion1(edoInicial);
	edoInicial = EdoAux1;
	edoAceptacion = EdoAux2;
	return this;
}
Automata *Automata::cerraduraEstrella(){
	string nomAux = Nombre;
	if(cerraduraPositiva()==NULL) return NULL;
	Nombre = "("+nomAux+")"+"*";
	edoInicial->setTransicion2(edoAceptacion);
	return this;
}
Automata *Automata::cerraduraInterrogacion(){
	if(edoInicial==NULL || edoAceptacion==NULL) return NULL;
	Nombre = "("+Nombre+")"+"?";
	Estado *EdoAux1 = new Estado();
	Estado *EdoAux2 = new Estado();
	EdoAux1->setTransicion1(edoInicial);
	edoAceptacion->setTransicion1(EdoAux2);
	EdoAux1->setTransicion2(EdoAux2);
	edoInicial = EdoAux1;
	edoAceptacion = EdoAux2;
	return this;
}

// Metodos de despliegue
void Automata::displayTerminal(){
	if(edoInicial==NULL || edoAceptacion==NULL){
		cout<<"\tAutomata Vacio"<<endl;
		return;
	}
	cout<<"\tNombre : "<<Nombre<<endl;
	cout<<"\tEstado Inicial : "<<edoInicial->getId()<<endl;
	cout<<"\tEstado Aceptacion : "<<edoAceptacion->getId()<<endl<<endl;
}
void Automata::displayAfdTabular(){
	Lista<char> letras = getSimbolos();
	int numLetras = letras.numElem();
	Lista<Estado*> Inicial, Obtenido, Aux;
	Lista< Lista<Estado*> > Contenedor;
	Inicial.pushFin(edoInicial);
	Inicial = cerraduraEpsilon(Inicial);
	Contenedor.pushFin(Inicial);
	int estado = 0;
	for(int e=0; e<Contenedor.numElem();e++){
		Inicial = Contenedor.getInfoAt(e);
		for(int i=0 ; i<numLetras; i++){
			Obtenido = Dtran(Inicial,letras.getInfoAt(i));
			if(listaTiene(Contenedor,Obtenido)) continue;
			Contenedor.pushFin(Obtenido);	
		}
	}
	cout<<"\tEstado AFD";
	for(int i=0; i<numLetras; i++) cout<<"\t"<<letras.getInfoAt(i);
	cout<<"\tEdo Aceptacion?"<<endl<<endl;
	for(int i=0; i<Contenedor.numElem(); i++){
		cout<<"\tEstado["<<i<<"]";
		Aux = Contenedor.getInfoAt(i);
		for(int j=0; j<numLetras; j++){
			cout<<"\t";
			Obtenido = Dtran(Aux,letras.getInfoAt(j));;
			cout<< listaEstaEn(Contenedor,Obtenido);
		}
		cout<<"\t"<< Aux.contiene(edoAceptacion) <<endl;
	}
}

// Metodos de ayuda
Estado *Automata::buscarEstado(int EdoId){
	Pila<Estado*> P;
	Lista<Estado*> Visitados;
	Estado *e, *eT1, *eT2;
	P.push(edoInicial);
	while(!P.estaVacia()){
		P.pop(e);
		Visitados.pushFin(e);
		if(e->getId()==EdoId) return e;
		if(e->getTransicion1()!=NULL){ 
			eT1 = e->getTransicion1();
			if(!Visitados.contiene(eT1)) P.push(eT1);
		} 
		if(e->getTransicion2()!=NULL){
			eT2 = e->getTransicion2();
			if(!Visitados.contiene(eT2)) P.push(eT2);
		}	
	}
	return NULL;
}
Lista<Estado*> Automata::cerraduraEpsilon(Lista<int> EdoId){
	Pila<Estado*> P;
	Lista<Estado*> S;
	Estado *Aux, *AuxT1, *AuxT2;
	int id;
	for(int i=0; i<EdoId.numElem(); i++){
		id = EdoId.getInfoAt(i);
		Aux = buscarEstado(id); 
		if(Aux!=NULL) P.push(Aux);
	};
	while(!P.estaVacia()){
		P.pop(Aux);
		if(S.contiene(Aux)) continue;
		S.pushFin(Aux);
		AuxT1 = Aux->getTransicion1();
		AuxT2 = Aux->getTransicion2();
		if(AuxT1!=NULL && Aux->getSimbolo1()==EPSILON) P.push(AuxT1);
		if(AuxT2!=NULL && Aux->getSimbolo2()==EPSILON) P.push(AuxT2);
	};
	return S;
}
Lista<Estado*> Automata::cerraduraEpsilon(Lista<Estado*> Edos){
	Pila<Estado*> P;
	Lista<Estado*> S;
	Estado *Aux, *Aux2, *AuxT1, *AuxT2;
	for(int i=0; i<Edos.numElem(); i++){
		Aux = Edos.getInfoAt(i);
		Aux2 = buscarEstado(Aux->getId());
		if(Aux!=NULL && Aux2!=NULL) P.push(Aux2);
	};
	while(!P.estaVacia()){
		P.pop(Aux);
		if(S.contiene(Aux)) continue;
		S.pushFin(Aux);
		AuxT1 = Aux->getTransicion1();
		AuxT2 = Aux->getTransicion2();
		if(AuxT1!=NULL && Aux->getSimbolo1()==EPSILON) P.push(AuxT1);
		if(AuxT2!=NULL && Aux->getSimbolo2()==EPSILON) P.push(AuxT2);
	};
	return S;
}
Lista<Estado*> Automata::moverA(Lista<Estado*> E, char Simbolo){
	Lista<Estado*> Sn;
	Estado *Ed, *EdT1, *EdT2;
	for(int i=0; i<E.numElem(); i++){
		Ed = E.getInfoAt(i);
		Ed = buscarEstado(Ed->getId());
		if(Ed!=NULL){
			EdT1 = Ed->getTransicion1();
			EdT2 = Ed->getTransicion2();
			if(EdT1!=NULL && Ed->getSimbolo1()==Simbolo) 
				Sn.pushFin(EdT1);
			if(EdT2!=NULL && Ed->getSimbolo2()==Simbolo)
				Sn.pushFin(EdT2);
		} 
	}
	return Sn;
}
Lista<Estado*> Automata::Dtran(Lista<Estado*> E, char Simbolo){
	return cerraduraEpsilon(moverA(E,Simbolo));
}
bool Automata::sonIguales(Lista<Estado*> L1, Lista<Estado*> L2){
	if(L1.numElem()!=L2.numElem()) return false;
	for(int i=0; i<L1.numElem(); i++)
		if(!L1.contiene(L2.getInfoAt(i))) return false;
	return true;
}
bool Automata::listaTiene(Lista< Lista<Estado*> > LE, Lista<Estado*> L){
	for(int i=0; i<LE.numElem(); i++)
		if(sonIguales(LE.getInfoAt(i), L)) return true;
	return false;
}
int Automata::listaEstaEn(Lista< Lista<Estado*> > LE, Lista<Estado*> L){
	for(int i=0; i<LE.numElem(); i++)
		if(sonIguales(LE.getInfoAt(i), L)) return i;
	return -1;
}
Lista<char> Automata::getSimbolos(){
	Lista<char> S;
	Pila<Estado*> P;
	Lista<Estado*> Visitados;
	Estado *e, *eT1, *eT2;
	P.push(edoInicial);
	while(!P.estaVacia()){
		P.pop(e);
		Visitados.pushFin(e);
		if(e->getTransicion1()!=NULL){ 
			eT1 = e->getTransicion1();
			if(!Visitados.contiene(eT1)) P.push(eT1);
		} 
		if(e->getTransicion2()!=NULL){
			eT2 = e->getTransicion2();
			if(!Visitados.contiene(eT2)) P.push(eT2);
		}
		if(e->getSimbolo1()!=EPSILON && !S.contiene(e->getSimbolo1())) 
			S.pushIni(e->getSimbolo1());
		if(e->getSimbolo2()!=EPSILON && !S.contiene(e->getSimbolo2()))
			S.pushIni(e->getSimbolo2());
	}
	return S;
}

// Metodo de evaluacion
bool Automata::evaluaCadena(string cadena){
	string cadenaAux = cadena;
	Lista<Estado *> Sn;
	Sn.pushFin(edoInicial);
	Sn = cerraduraEpsilon(Sn);
	for(int i=0; i<cadenaAux.size(); i++){
		Sn = cerraduraEpsilon(moverA(Sn,cadena[i]));
	}
	return Sn.contiene(edoAceptacion);
}

// Metodos Set
void Automata::setEdoInicial(Estado *Inicial){
	edoInicial = Inicial;
}
void Automata::setEdoAceptacion(Estado *Aceptacion){
	edoAceptacion = Aceptacion;
}
void Automata::setNombre(string Nom){
	Nombre = Nom;
}

// Metodos Get
Estado *Automata::getEdoInicial() const{
	return edoInicial;
}
Estado *Automata::getEdoAceptacion() const{
	return edoAceptacion;
}
string Automata::getNombre() const{
	return Nombre;
}




