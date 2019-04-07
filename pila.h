#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Nodo{
	private:
		T Info;	
		Nodo<T> *ApSig;
	public:
		Nodo();
		Nodo(T inf);
		T getInfo();
		void setInfo(T inf);
		Nodo<T> *getApSig();
		void setApSig(Nodo<T> *Ap);
};
template <typename T>
Nodo<T>::Nodo(){
	ApSig = NULL;
};
template <typename T>
Nodo<T>::Nodo(T inf){
	ApSig = NULL;
	Info = inf;
};
template <typename T>
T Nodo<T>::getInfo(){
	return Info;
};
template <typename T>
void Nodo<T>::setInfo(T inf){
	Info = inf;
};
template <typename T>
Nodo<T> *Nodo<T>::getApSig(){
	return ApSig;
};
template <typename T>
void Nodo<T>::setApSig(Nodo<T> *Ap){
	ApSig = Ap;
};



template <typename T>
class Pila{
	private:
		Nodo<T> *Tope;
	public:
		Pila();
		bool push(T inf);
		bool pop(T &inf);
		bool estaVacia();
		int numElementos();
};
template <typename T>
Pila<T>::Pila(){
	Tope = NULL;
};
template <typename T>
bool Pila<T>::push(T inf){
	Nodo<T> *Ap = new Nodo<T>;
	Ap->setInfo(inf);
	Ap->setApSig(Tope);
	Tope = Ap;
	return true;
};
template <typename T>
bool Pila<T>::pop(T &inf){
	if(estaVacia()){
		inf = NULL;
		return false;
	};
	inf = Tope->getInfo();
	Nodo<T> *Ap = new Nodo<T>;
	Ap->setApSig(Tope);
	Tope = Tope->getApSig();
	delete Ap;
	return true;
};
template <typename T>
bool Pila<T>::estaVacia(){
	return (Tope==NULL) ? true : false;
};
template <typename T>
int Pila<T>::numElementos(){
	if(estaVacia()) return 0;
	Nodo<T> *Ap = Tope;
	int cantidad = 1;
	while(1){
		if(Ap->getApSig()==NULL) break;
		cantidad++;
		Ap = Ap->getApSig();
	}
	return cantidad;
};


#endif









