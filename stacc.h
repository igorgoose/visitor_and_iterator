#pragma once
#pragma once
#include <iostream>
#include <cstring>
using namespace std;


template<class type>
class Iterator;

template<class type>
class OddIterator;

template <class type> class stacc;

template <class type> class item;

template <class type> class visitor {
public:
	virtual type visit(const stacc<type>& st) = 0;
};

template <class type> class visitorMin : public visitor<type>{//ищет минимальный элемент
public:
	virtual type visit(const stacc<type>& st) {
		stacc<type> temp(st);
		item<type> min, cur;
		if (st.empty()) {
			throw "Стакк пуст!";
		}
		
		min = temp.pop();
		while (!temp.empty()) {
			cur = temp.pop();
			if (cur < min) {
				min = cur;
			}
		}
		return min.getVal();
	};
};

template <class type> class visitorMax : public visitor<type> {//ищет максимальный элемент
public:
	virtual type visit(const stacc<type>& st) {
		stacc<type> temp(st);
		item<type> max, cur;
		if (st.empty()) {
			throw "Стакк пуст!";
		}
		max = temp.pop();
		while (!temp.empty()) {
			cur = temp.pop();
			if (cur > max) {
				max = cur;
			}
		}
		return max.getVal();
	};
};

template <class type> class visitorIMax : public visitor<type> {//максимальный с итераторами
public:
	virtual type visit(const stacc<type>& st) {
		Iterator<type> it = st.begin();
		item<type> max, cur;
		if (st.empty()) {
			throw "Стакк пуст!";
		}
		max = *it;
		
		while (it != st.end()) {
			cur = *it;
			it++;
			if (cur > max) {
				max = cur;
			}
		}
		return max.getVal();
	};
};

template <class type> class visitorIMin : public visitor<type> {//минимальный с итераторами	
public:
	virtual type visit(const stacc<type>& st) {
		Iterator<type> it = st.begin();
		item<type> min, cur;
		if (st.empty()) {
			throw "Стакк пуст!";
		}
		min = *it;
		while (it != st.end()) {
			cur = *it;
			it++;
			if (cur < min) {
				min = cur;
			}
		}
		return min.getVal();
	};
};



template<class type> class item {
	friend class Iterator<type>;
private:
	type val;
	item* next;
public:
	item(type a) {
		val = a;
		next = 0;
	}
	item() {
		next = NULL;
	}
	type getVal()const;
	item* getNext()const {
		return next;
	}
	void setVal(type v) {
		val = v;
	}
	void setNext(item* obj) {
		next = obj;
	}
	~item() {}
	bool operator <(const item& item) {
		return val < item.getVal();
	}
	bool operator >(const item& item) {
		return val > item.getVal();
	}
	item& operator = (const item& item) {
		val = item.getVal();
		next = item.getNext();
		return *this;
	}
	
};

template<>
item<char*>&  item<char*> ::operator=(const item<char*>& item) {
	int length = strlen(item.val) + 1;
	val = new char[length];
	strcpy_s(val, length, item.val);
	next = 0;
	return *this;
}

template<>
item<char*>::item(char* str) {
	if (str == NULL || str[0] == 0) {
		throw "Invalid parameter\n";
	}
	int length = strlen(str) + 1;
	val = new char[length];
	strcpy_s(val, length, str);
	next = 0;
}

template<>
item<char*>::~item() {
	delete[] val;
	next = 0;
}

template<class type>
type item<type>::getVal()const {
	return val;
}

template<>
void item<char*>::setVal(char * str) {
	if (str == NULL || str[0] == 0) {
		throw "Invalid parameter\n";
	}
	delete[] val;
	int length = strlen(str) + 1;
	val = new char[length];
	strcpy_s(val, length, str);
}

template<>
bool item<char*>::operator<(const item<char*>& item) {
	return (strcmp(val, item.getVal()) == -1);
}

template<>
bool item<char*>::operator>(const item<char*>& item) {
	return (strcmp(val, item.getVal()) == 1);
}


template <class type> class stacc
{
	friend class Iterator<type>;
private:
	item<type>* first;
	void erase() {
		item<type> *p = first;
		while (p != 0) {
			item<type> *q = p;
			p = p->getNext();
			q->~item();
		}
		first = 0;
		return;
	};
	void clone(const stacc<type>& obj) {
		if (this == &obj) {
			return;
		}
		if (obj.first == 0) {
			first = 0;
			return;
		}
		item<type> *p = obj.first;
		item<type> *f = 0;
		while (p != 0)
		{
			item<type> *q = new item<type>(p->getVal());
			q->setNext(f);
			f = q;
			p = p->getNext();
		}
		while (f != 0) {
			item<type> *q = new item<type>(f->getVal());
			q->setNext(first);
			first = q;
			item<type> *t = f;
			f = f->getNext();
			t->~item();
		}
		return;
	}
public:
	stacc() {
		first = 0;
	}
	stacc(type* arr, int size) {
		first = 0;

		if (size < 1) {
			throw "Invalid parameter\n";
		}
		for (int i = 0; i < size; i++) {
			item<type> *p = new item<type>(arr[i]);
			p->setNext(first);
			first = p;
		}
	}
	explicit stacc(const stacc<type>& obj) {
		clone(obj);
	}
	~stacc() {
		erase();
	}
	void push(type val) {
		item<type> *p = new item<type>(val);
		p->setNext(first);
		first = p;
	}
	int size()const {
		int a = 0;
		item<type> *p = first;
		while (p != 0) {
			a++;
			p = p->next;
		}
		return a;
	}
	bool empty() const {
		return (first == 0);
	}
	item<type> pop() {
		item<type> *p = first;
		first = first->getNext();
		item<type> a(p->getVal());
		delete p;
		return a;
	}
	item<type> peekTop() {
		item<type> a(first->getVal());
		return a;
	}
	void show(ostream& os)const {
		item<type> *p = first;
		while (p != 0) {
			os << p->getVal() << "\t";
			p = p->getNext();
		}
		os << endl;
	}
	friend ostream& operator<<(ostream& os, const stacc<type>& obj) {
		obj.show(os);
		return os;
	}
	stacc<type>& operator=(const stacc<type>& obj) {
		erase();
		clone(obj);
		return *this;
	}
	item<type>* begin()const {
		return first;
	}
	item<type>* end()const {
		if (first == 0) {
			return first;
		}
		item<type>* p = first;
		while (p) {
			p = p->getNext();
		}
		return p;
	}
	type accept(visitor<type>& v) {
		return v.visit(*this);
	}
};

template<>
void stacc<char*>::clone(const stacc<char*>& obj) {
	if (this == &obj) {
		return;
	}
	if (obj.first == 0) {
		first = 0;
		return;
	}
	item<char*> *p = obj.first;
	item<char*> *f = 0;
	while (p != 0)
	{
		item<char*> *q = new item<char*>(p->getVal());
		q->setNext(f);
		f = q;
		p = p->getNext();
	}
	while (f != 0) {
		item<char*> *q = new item<char*>(f->getVal());
		q->setNext(first);
		first = q;
		item<char*> *t = f;
		f = f->getNext();
		t->~item();
	}
	return;
}

template<>
stacc<char*>& stacc<char*>::operator=(const stacc<char*>& obj) {
	if (this == &obj) {
		return *this;
	}
	erase();
	clone(obj);
	return *this;
}


template <class type>
class Iterator
{
	friend class item<type>;
	friend class stacc<type>;
	friend class OddIterator < type >;
private:

	item<type>* p;
public:
	Iterator(item<type>* st) {
		p = st;
	};
	Iterator(const Iterator& it);
	Iterator(const OddIterator<type>& it);
	bool operator!=(Iterator const& other) const;
	bool operator==(Iterator const& other) const;
	item<type> operator*() const;
	virtual bool is_Done()const;
	Iterator<type>& operator++(int);
	Iterator<type>& next();

};

template<class type>
inline Iterator<type>::Iterator(const Iterator & it)
{
	p = it.p;
}

template<class type>
inline Iterator<type>::Iterator(const OddIterator<type>& it)
{
	p = it.p;
}

template<class type>
inline bool Iterator<type>::operator!=(Iterator const & other) const
{
	return (p != other.p);
}

template<class type>
inline bool Iterator<type>::operator==(Iterator const & other) const
{
	return (p == other.p);
}

template<class type>
inline item<type> Iterator<type>::operator*() const
{
	if (!p) {
		throw "Выход за пределы стакка!";
	}
	return *p;
}

template<class type>
inline bool Iterator<type>::is_Done() const
{
	if (!p) return true;
	if (!p->getNext()) return true;
	return false;
}

template<class type>
inline Iterator<type>& Iterator<type>::operator++(int)
{
	if (!p) {
		throw "Выход за пределы стакка!";
	}
	Iterator<type>* it = new Iterator<type>(p);
	p = p->getNext();
	return *it;
}

template<class type>
inline Iterator<type>& Iterator<type>::next()
{
	if (!p) {
		throw "Выход за пределы стакка!";
	}
	p = p->getNext();
	return *this;
}

template<class type>
class OddIterator {
	friend class item<type>;
	friend class stacc<type>;
	friend class Iterator<type>;
private:

	item<type>* p;
public:
	OddIterator(item<type>* st) {
		p = st;
	};
	OddIterator(const OddIterator& it);
	OddIterator(const Iterator<type>& it);
	bool operator!=(OddIterator const& other) const;
	bool operator==(OddIterator const& other) const;
	type operator*() const;
	virtual bool is_Done()const;
	OddIterator<type>& operator++(int);
	OddIterator<type>& next();
};

template<class type>
inline OddIterator<type>::OddIterator(const OddIterator & it)
{
	p = it.p;
}

template<class type>
inline OddIterator<type>::OddIterator(const Iterator<type>& it)
{
	p = it.p;
}

template<class type>
inline bool OddIterator<type>::operator!=(OddIterator const & other) const
{
	return (p != other.p);
}

template<class type>
inline bool OddIterator<type>::operator==(OddIterator const & other) const
{
	return (p == other.p);
}

template<class type>
inline type OddIterator<type>::operator*() const
{
	if (!p) {
		throw "Выход за пределы стакка!";
	}
	return p->getVal();
}

template<class type>
inline bool OddIterator<type>::is_Done() const
{
	if (!p) return true;
	if (!p->getNext()) return true;
	if (!p->getNext()->getNext()) return true;
	return false;
}

template<class type>
inline OddIterator<type>& OddIterator<type>::operator++(int)
{
	if (!p || !p->getNext()) {
		throw "Выход за пределы стакка!";
	}
	OddIterator<type>* it = new OddIterator<type>(p);
	p = p->getNext()->getNext();
	return *it;
}

template<class type>
inline OddIterator<type>& OddIterator<type>::next()
{
	if (!p || !p->getNext()) {
		throw "Выход за пределы стакка!";
	}
	p = p->getNext()->getNext();
	return *this;
}

