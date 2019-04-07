#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class NodoL{
	private:
		T Info;
		NodoL<T> *ApAnt;
		NodoL<T> *ApSig;
	public:
		NodoL();
		NodoL(T inf);
		T getInfo();
		NodoL<T> *getApAnt();
		NodoL<T> *getApSig();
		void setInfo(T inf);
		void setApAnt(NodoL<T> *ApA);
		void setApSig(NodoL<T> *ApS);
};
template <typename T>
NodoL<T>::NodoL(){
	ApAnt = ApSig = NULL;
};
template <typename T>
NodoL<T>::NodoL(T inf){
	Info = inf;
	ApAnt = ApSig = NULL;
};
template <typename T>
T NodoL<T>::getInfo(){
	return Info;
};
template <typename T>
NodoL<T> *NodoL<T>::getApAnt(){
	return ApAnt;
};
template <typename T>
NodoL<T> *NodoL<T>::getApSig(){
	return ApSig;
};
template <typename T>
void NodoL<T>::setInfo(T inf){
	Info = inf;
};
template <typename T>
void NodoL<T>::setApAnt(NodoL<T> *ApA){
	ApAnt = ApA;
};
template <typename T>
void NodoL<T>::setApSig(NodoL<T> *ApS){
	ApSig = ApS;
};

template <typename T>
class Lista{
	private:
		NodoL<T> *ApInicio;
		NodoL<T> *ApFin;
		int NumElem;
	public:
		Lista();
		bool pushIni(T inf);
		bool pushFin(T inf);
		bool popIni(T &inf);
		bool popFin(T &inf);
		bool estaVacia();
		int numElem();
		bool contiene(T inf);
		int iContiene(T inf);
		T getInfoAt(int i);
		bool operator==(const T &) const;
		bool operator!=(const T &) const;
};
template <typename T>
Lista<T>::Lista(){
	ApFin = ApInicio = NULL;
	NumElem = 0;
};
template <typename T>
bool Lista<T>::pushIni(T inf){
	NodoL<T> *Ap = new NodoL<T>;
	Ap->setInfo(inf);
	if(estaVacia()){
		ApFin = ApInicio = Ap; NumElem++;
		return true;
	}
	Ap->setApSig(ApInicio);
	Ap->getApSig()->setApAnt(Ap);
	ApInicio = Ap;
	NumElem++;
	return true;
};
template <typename T>
bool Lista<T>::pushFin(T inf){
	NodoL<T> *Ap = new NodoL<T>;
	Ap->setInfo(inf);
	if(estaVacia()){
		ApFin = ApInicio = Ap; NumElem++;
		return true;
	}
	Ap->setApAnt(ApFin);
	Ap->getApAnt()->setApSig(Ap);
	ApFin = Ap;
	NumElem++;
	return true;
};
template <typename T>
bool Lista<T>::popIni(T &inf){
	if(estaVacia()){
		inf = NULL;
		return false;
	}
	NodoL<T> *ApAux = new NodoL<T>;
	ApAux = ApInicio;
	inf = ApAux->getInfo();
	if(NumElem!=1){
		ApInicio = ApInicio->getApSig();
		ApInicio->setApAnt(NULL);
	}
	if(NumElem==1){
		ApInicio = ApFin = NULL;
	}
	delete ApAux;
	NumElem--;
	return true;
};
template <typename T>
bool Lista<T>::popFin(T &inf){
	if(estaVacia()){
		inf = NULL;
		return false;
	}
	NodoL<T> *ApAux = new NodoL<T>;
	ApAux = ApFin;
	inf = ApAux->getInfo();
	if(NumElem!=1){
		ApFin = ApFin->getApAnt();
		ApFin->setApSig(NULL);
	}
	if(NumElem==1){
		ApInicio = ApFin = NULL;
	}
	delete ApAux;
	NumElem--;
	return true;
};
template <typename T>
bool Lista<T>::estaVacia(){
	if(ApInicio==NULL && ApFin==NULL) return true;
	return false;
};
template <typename T>
int Lista<T>::numElem(){
	return NumElem;
};
template <typename T>
bool Lista<T>::contiene(T inf){
	T InfoAux = inf;
	NodoL<T> *ApAux;
	ApAux = ApInicio;
	for(int i=0; i<NumElem; i++){
		if(ApAux->getInfo()==InfoAux) return true;
		ApAux = ApAux->getApSig();
		if(ApAux==NULL) break;
	};
	return false;
};
template <typename T>
int Lista<T>::iContiene(T inf){
	T InfoAux = inf;
	NodoL<T> *ApAux;
	ApAux = ApInicio;
	for(int i=0; i<NumElem; i++){
		if(ApAux->getInfo()==InfoAux) return i;
		ApAux = ApAux->getApSig();
		if(ApAux==NULL) break;
	};
	return -1;
};

template <typename T>
T Lista<T>::getInfoAt(int i){
	NodoL<T> *Ap = NULL;
	if(i<0 || i>=NumElem) return Ap->getInfo();
	int j = 0;
	Ap = ApInicio;
	while(j!=i){
		Ap = Ap->getApSig();
		j++;
	}
	return Ap->getInfo();
};
template <typename T>
bool Lista<T>::operator==(const T &derecha) const{
	if(NumElem!=derecha.numElem()) return false;
	for(int i=0; i<NumElem; i++){
		if(!contiene(derecha.getInfoAt(i))) return false;
	}
	return true;
};
template <typename T>
bool Lista<T>::operator!=(const T &derecha) const{
	if(NumElem!=derecha.numElem()) return true;
	for(int i=0; i<NumElem; i++){
		if(!contiene(derecha.getInfoAt(i))) return true;
	}
	return false;
};


#endif

