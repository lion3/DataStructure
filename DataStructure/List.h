#ifndef _LIST_H_
#define _LIST_H_

#include <string.h>
#include "Support.h"

#pragma region SqList

#define ListInitSize 100
#define ListIncrement 10

template <class T>
class SqList {
private:
	T* elem;
	int length;
	int listsize;
public:
	SqList();
	~SqList();
	Status InitList_Sq(SqList &L);
	Status ListInsert_Sq(SqList &L, int i, T e);
	Status ListDelete_Sq(SqList &L, int i, T &e);
	Status ClearList(SqList &L);
	Status GetElem(SqList &L, int i, T &e);
	int LocateElem(SqList L, T e, bool(*cmp)(T, T));
	int ListLength(SqList L);
	bool ListEmpty(SqList L);
	bool equal(T a, T b);
	Status PriorElem(SqList L, T cur_e, T& pre_e);
	Status NextElem(SqList L, T cur_e, T& pre_e);
	Status ListTraverse(SqList L, Status(*visit)(T &e));
};

#pragma region SqList Implemention
template <class T>
SqList<T>::SqList() {
	elem = NULL;
	length = 0;
	listsize = 0;
}

template <class T>
SqList<T>::~SqList() {
	if (elem != NULL) {
		delete elem;
		elem = NULL;
	}
}
template <class T>
Status SqList<T>::InitList_Sq(SqList &L) {
	L.elem = new T[ListInitSize];
	if (L.elem == NULL) return M_OVERFLOW;
	L.length = 0;
	L.listsize = ListInitSize;
	return OK;
}
template <class T>
Status SqList<T>::ListInsert_Sq(SqList &L, int i, T e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length >= L.listsize) {
		T* temp_elem = new T[L.listsize + ListIncrement];
		if (temp_elem == NULL) return M_OVERFLOW;
		memmove(temp_elem, L.elem, L.length);
		delete L.elem;
		L.elem = temp_elem;
		temp_elem = NULL;
		L.listsize += ListIncrement;
	}
	T* ptr_insert = &L.elem[i - 1];
	for (T* ptr = &L.elem[L.length - 1]; ptr >= ptr_insert; --ptr) {
		*(ptr + 1) = *ptr;
	}
	*ptr_insert = e;
	++L.length;
	return OK;
}
template <class T>
Status SqList<T>::ListDelete_Sq(SqList &L, int i, T &e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	for (T* ptr = &L.elem[i - 1]; ptr < &L.elem[L.length - 1]; ptr++) {
		*ptr = *(ptr + 1);
	}
	--L.length;
	return OK;
}
template <class T>
Status SqList<T>::ClearList(SqList &L) {
	if (L.elem != NULL) {
		delete L.elem;
		L.elem = NULL;
		L.length = 0;
		L.listsize = 0;
		return OK;
	}
	else {
		return ERROR;
	}
}
template <class T>
Status SqList<T>::GetElem(SqList &L, int i, T &e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}
template <class T>
int SqList<T>::LocateElem(SqList L, T e, bool(*cmp)(T, T)) {
	int index = 0;
	T* ptr = &L.elem[0];
	while (cmp(*ptr, e) != true && index < L.length) {
		ptr++;
		index++;
	}
	if (index == L.length) {
		index = -1;
	}
	++index;
	return index;
}
template <class T>
int SqList<T>::ListLength(SqList L) {
	return L.length;
}
template <class T>
bool SqList<T>::ListEmpty(SqList L) {
	return (L.length == 0);
}
template <class T>
bool SqList<T>::equal(T a, T b) {
	return (a == b);
}
template <class T>
Status SqList<T>::PriorElem(SqList L, T cur_e, T& pre_e) {
	int index = LocateElem(L, cur_e, equal);
	int status = OK;
	if (index == 0) {
		status = ERROR;
	}
	else {
		if (GetElem(L, index - 1, pre_e) != OK) {
			status = ERROR;
		}
	}
	return status;
}
template <class T>
Status	SqList<T>::NextElem(SqList L, T cur_e, T& pre_e) {
	int index = LocateElem(L, cur_e, equal);
	int status = OK;
	if (index == 0) {
		status = ERROR;
	}
	else {
		if (GetElem(L, index + 1, pre_e) != OK) {
			status = ERROR;
		}
	}
	return status;
}

template<class T>
Status SqList<T>::ListTraverse(SqList L, Status(*visit)(T &e))
{
	Status status = OK;
	if (L.elem != NULL) {
		for (int i = 0; i < L.length; i++) {
			status = visit((L.elem[i]));
			if (status == ERROR) break;
		}
	}
	else {
		status = ERROR;
	}
	return status;
}
#pragma endregion 

#pragma endregion SqList

#pragma region LinkList
template <class T>
struct LNode {
	T elem;
	LNode *next;
};
template <class T>
class LinkList {
private:
	LNode *head;
	int length;
public:
	LinkList();
	~LinkList();
	Status ClearList(LinkList &L);
	Status ListInsert_Link(LinkList &L, int i, T e);
	Status ListDelete_Link(LinkList &L, int i, T &e);
	Status GetElem(LinkList &L, int i, T &e);
};


template<class T>
LinkList<T>::LinkList()
{
	head = NULL;
	length = 0;
}

template<class T>
LinkList<T>::~LinkList()
{
	if (head != NULL) {
		this->ClearList(*this);
		head = NULL;
		length = 0;
	}
}

template<class T>
Status LinkList<T>::ClearList(LinkList & L)
{
	if (L.head != NULL) {
		LNode *temp = L.head;
		LNode *temp_prior;
		for (int i = 0; i < L.length; i++) {
			temp_prior = temp;
			temp = temp->next;
			delete temp_prior;
			temp_prior = NULL;
		}
		L.head = temp;
		delete L.head;
		L.head = NULL;
		L.length = 0;
	}
	return OK;
}

template<class T>
Status LinkList<T>::ListInsert_Link(LinkList & L, int index, T e)
{
	if (index < 1 || index > L.length + 1) return ERROR;
	if (L.length == 0) {
		LNode *temp = new LNode();
		temp->elem = e;
		temp->next = NULL;
		head->next = temp;
		++L.length;
	}
	else {
		LNode *temp = L.head;
		LNode *temp_prior;
		for (int i = 0; i < index; i++) {
			temp_prior = temp;
			temp = temp->next;
		}
		LNode *temp_new = new LNode();
		temp_new->elem = e;
		temp_prior->next = temp_new;
		temp_new->next = temp;
		++L.length;
	}

}

template<class T>
Status LinkList<T>::ListDelete_Link(LinkList & L, int i, T & e)
{
	if (index < 1 || index > L.length) return ERROR;
	LNode *temp = L.head;
	LNode *temp_prior;
	for (int i = 0; i < index; i++) {
		temp_prior = temp;
		temp = temp->next;
	}
	temp_prior->next = temp->next;
	delete temp;
	temp = NULL;
	--L.length;
	return OK;
}

template<class T>
Status LinkList<T>::GetElem(LinkList & L, int index, T & e)
{
	if (index < 1 || index > L.length) return ERROR;
	LNode *temp = L.head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	e = temp->elem;
	return OK;
}

#pragma endregion LinkList

#endif