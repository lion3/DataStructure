#include <iostream>

#include "List.h"
using namespace std;

Status SqPrintElem(int &t) {
	cout << "elem: " << t << endl;
	return OK;
}
int main() {
	SqList<int>* sq = new SqList<int>();
	sq->InitList_Sq(*sq);
	int cnt = 5;
	for (int i = 0; i < cnt; i++) {
		sq->ListInsert_Sq(*sq, 1, i);
	}
	sq->ListTraverse(*sq, &SqPrintElem);
	system("pause");
}