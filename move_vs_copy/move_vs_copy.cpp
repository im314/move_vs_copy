#include "stdafx.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <conio.h> // _getch

using namespace std;


#define MOVE_ENABLED // флаг определяет, доступность операция перемещения



template <class T>
class my_vector
{
private:
	int sz;
	T	*pdata;

public:
	// default ctor
	my_vector() : sz(0), pdata(nullptr) { cout << "default ctor" << endl; }
	
	// dtor
	~my_vector()
	{
		cout << "dtor: " << sz << " objects";
		if(pdata)
		{
			cout << " DELETE [" << sz << "]";
			delete []pdata;
		}
		cout << endl;
	}

	// ctor with size and value
	my_vector(int n, T val) : sz(n)
	{
		pdata = new T[sz];
		std::fill(pdata, pdata + sz, val);
		cout << "ctor: " << sz << " objects NEW [" << sz << "]" << endl;
	}
	
	// copy ctor
	my_vector(const my_vector &a) : sz(a.sz)
	{
		pdata = new T[sz];
		std::copy(a.pdata, a.pdata + sz, pdata);
		cout << "ctor_copy: " << sz << " objects NEW [" << sz << "]" <<  endl;
	}

	// оператор присваивания
	my_vector& operator=(const my_vector &a)
	{
		cout << "operator=: ";
		if(pdata)
		{
			delete []pdata;
			cout << "DELETE[" << sz << "]";
		}
		sz = a.sz;
		pdata = new T[sz];
		std::copy(a.pdata, a.pdata + sz, pdata);
		
		cout << " NEW [" << sz << "]" << endl;
		return *this;		
	}

	size_t size() const { return sz; }
	T* data() const { return pdata; }

#ifdef MOVE_ENABLED

	// move ctor
	my_vector(my_vector &&a) : sz(a.sz)
	{
		pdata = a.pdata;
		a.pdata = nullptr;
		a.sz = 0;
		cout << "ctor_move: " << sz << " objects" << endl;
	}

	// оператор перемещения
	my_vector& operator=(my_vector &&a)
	{
		cout << "operator=(move): ";
		if(pdata)
		{
			cout << "DELETE[" << sz << "]";
			delete[]pdata;
		}

		sz = a.sz;
		pdata = a.pdata;

		a.pdata = nullptr;
		a.sz = 0;
		cout << " " << sz << " objects" << endl;
		return *this;
	}
#endif
};





template <class T>
my_vector<T> create_vect(size_t n, T value)
{
	my_vector<T> vm(n, value);
	return vm;
}






int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	{

		cout << "Создаём пустой вектор:" << endl;
		my_vector<string> myvec2;
		cout << endl;

		cout << "Создаём вектор с 1000 элементами:" << endl;
		my_vector<string> myvec(1000, "abc");
		cout << endl;

		cout << "Пытаемся переместить второй вектор в первый:" << endl;
		myvec2 = std::move(myvec);
		cout << endl;

		cout << "Создаём ещё один пустой вектор" << endl;
		my_vector<string> myvec3;
		cout << endl;

		cout << "Присваиваем ему результат функции:" << endl;
		myvec3 = create_vect<string>(100000, "komin");
		cout << endl;
	}


	cout << endl << "Press Any Key...";
	_getch();	
	return 0;
}

