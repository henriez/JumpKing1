#pragma once

template <typename TL>
class Lista
{
private:

	template <typename TE>
	class Elemento
	{
	private:
		Elemento* pNext;
		Elemento* pPrev;
		TE info;

	public:
		Elemento();
		~Elemento();

		void setNext(Elemento* pNext);
		void setPrev(Elemento* pPrev);
		void setInfo(TE inf);

		Elemento* getNext() const;
		Elemento* getPrev() const;
		TE getInfo() const;
	};

	Elemento<TL>* first;
	Elemento<TL>* last;
	Elemento<TL>* now;

public:
	Lista();
	~Lista();

	void add(TL info);
	void clear();
	void remove(TL info);

	TL begin();
	TL next();
};

template <typename TL>
template <typename TE>
Lista<TL>::Elemento<TE>::Elemento() :pNext(nullptr), pPrev(nullptr), info(NULL){

}

template <typename TL>
template <typename TE>
Lista<TL>::Elemento<TE>::~Elemento(){

}

template <typename TL>
template <typename TE>
void Lista<TL>::Elemento<TE>::setNext(Elemento* pNext){
	this->pNext = pNext;
}

template <typename TL>
template <typename TE>
void Lista<TL>::Elemento<TE>::setPrev(Elemento* pPrev){
	this->pPrev = pPrev;
}

template <typename TL>
template <typename TE>
void Lista<TL>::Elemento<TE>::setInfo(TE inf){
	info = inf;
}

template <typename TL>
template <typename TE>
Lista<TL>::Elemento<TE>* Lista<TL>::Elemento<TE>::getNext() const{
	return pNext;
}

template <typename TL>
template <typename TE>
Lista<TL>::Elemento<TE>* Lista<TL>::Elemento<TE>::getPrev() const{
	return pPrev;
}

template <typename TL>
template <typename TE>
TE Lista<TL>::Elemento<TE>::getInfo() const{
	return info;
}



template<typename TL>
Lista<TL>::Lista() :first(), now(), last(){
}

template<typename TL>
Lista<TL>::~Lista(){
	clear();
}

template<typename TL>
void Lista<TL>::add(TL info){
	Elemento<TL>* aux = nullptr;
	aux = new Elemento<TL>;
	aux->setInfo(info);

	if (!first){
		last = aux;
		first = aux;
	}
	else{
		last->setNext(aux);
		aux->setPrev(last);

		last = aux;
	}

}

template<typename TL>
void Lista<TL>::clear(){
	Elemento<TL>* aux = nullptr;
	aux = last;

	while (aux){
		last = last->getPrev();
		delete aux;
		aux = last;
	}
	last = nullptr;
	first = nullptr;
}

template<typename TL>
void Lista<TL>::remove(TL info){
	Elemento<TL>* aux = nullptr;
	aux = first;

	while (aux != nullptr && aux->getInfo() != info)
		aux = aux->getNext();
	//stops at the info pointer given

	if (aux) {
		if (aux->getPrev())
			aux->getPrev()->setNext(aux->getNext());
		else
			first = aux->getNext();


		if (aux->getNext())
			aux->getNext()->setPrev(aux->getPrev());
		else
			last = aux->getPrev();
	}
	
	delete aux;

}

template<typename TL>
TL Lista<TL>::begin(){
	now = first;
	if (!now) return nullptr;
	return now->getInfo();
}

template<typename TL>
TL Lista<TL>::next(){
	now = now->getNext();
	if (!now) return nullptr;
	return now->getInfo();
}