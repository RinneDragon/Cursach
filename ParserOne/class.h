#pragma once
#include <cstring>

using namespace std;

template <class T>
class DynArr {
protected:
	T* data;
	size_t size;
	size_t count = 0;
public:
	DynArr() 
	{ 
		data = new T[1];
		size = 1; 
	}
	DynArr(size_t size) 
	{
		this->size = size;
		data = new T[size];
	}
	DynArr(const DynArr &obj)
	{
		if (data != nullptr) delete[] data;

		size = obj.size;
		count = obj.count;
		data = new T[size];
		memcpy(data, obj.data, size);
	}
	DynArr(const DynArr &&obj)
	{
		this->size = obj.count + 1;
		this->count = obj.count;
		if (this->data != nullptr) delete[] data;
		this->data = new T[this->size];
		memmove(this->data, obj.data, this->size);		
	}
	DynArr& operator=(DynArr const& obj)
	{
		if (this != &obj)
		{
			if (this->size != obj.size)
			{
				delete[] this->data;
				this->size = obj.count + 1;
				this->count = obj.count;
				memcpy(this->data, obj.data, this->size);
			}
			else
			{
				memcpy(this->data, obj.data, this->size);
			}
		}
		return *this;
	} 
	DynArr& operator=(DynArr const&& obj)
	{
		if (this != &obj)
		{
			if (this->size != obj.size)
			{
				delete[] this->data;
				this->size = obj.count + 1;
				this->count = obj.count;
				memmove(this->data, obj.data, this->size);
			}
			else
			{
				memmove(this->data, obj.data, this->size);
			}
		}
		return *this;
	}
	~DynArr()
	{
		delete[] data;
	}
	size_t getSize() const { return size; }
	size_t getCount() const { return count; }
	void resize(size_t size) 
	{
		if (this->size == size) return;
		T* temp = this->data;
		if (size < this->size) 
		{
			this->data = new T[size];
			memcpy(this->data, temp, size);
			this->size = size;
		}
		else 
		{
			auto nsize = this->size;
			while (nsize < size) nsize *= 2;

			this->data = new T[nsize];
			memcpy(this->data, temp, this->size);
			this->size = nsize;
		}
		delete temp;
	}
	void push_back(T el) 
	{
		if (count < size)
		{
			data[count] = el;
			count++;
		}
		else if (count == size)
		{
			resize(size + 1);
			data[count] = el;
			count++;
		}
	}
	T getAt(size_t pos) 
	{		 
		if (pos <= count) 
		{
			return data[pos];
		}
	}	
	T getEnd()
	{
		return data[count-1];		
	}

};

class MyString : public DynArr<char> {
public:
	MyString() : DynArr<char>() {}
	MyString(size_t size) : DynArr<char>(size) {}
	MyString(const MyString& obj) : DynArr<char>(obj) {}
	MyString(const MyString&& obj) : DynArr<char>(obj) {}

	MyString& operator=(MyString const& obj)
	{
		if (this != &obj)
		{
			if (this->size != obj.size)
			{
				delete[] this->data;
				this->size = obj.count + 1;
				this->count = obj.count;
				memcpy(this->data, obj.data, this->size);
			}
			else
			{
				memcpy(this->data, obj.data, this->size);
			}
		}
		return *this;
	}
	MyString& operator=(MyString const&& obj)
	{
		if (this != &obj)
		{
			if (this->size != obj.size)
			{
				delete[] this->data;
				this->size = obj.count + 1;
				this->count = obj.count;
				memmove(this->data, obj.data, this->size);
			}
			else
			{
				memmove(this->data, obj.data, this->size);
			}
		}
		return *this;
	}
	
	char* getData() { return data; }
};

template <class T>
class Stack {
private:
	struct Node 
	{
		T el;
		Node* prev;
		~Node() {
			if (prev != nullptr) delete prev;
		}
	};
	Node* top;
public:
	Stack() { top = nullptr; }
	~Stack() 
	{
		if (top != nullptr) delete top;
	}
	void push(T el)	
	{		
		Node* temp = top;
		top = new Node;
		top->el = el;
		top-> prev = temp;
	}
	bool isEmpty() { return top == nullptr; }
	T getTop() { return top->el; }
	T pop()
	{
		//мы создаём указатель на ноду вершины, чтобы потом очистить там память
		Node* temp = top;
		T res = top->el;
		top = top->prev;
		//чтобы не зациклить удаление, предыдущему элементу задаём нулевой указатель
		temp->prev = nullptr;
		delete temp;

		return res;
	}

};

template <class T1, class T2>
class Either
{	
	T1 left; 
	T2 right; 
	bool empty = false; 
	bool isl = false; 
	bool isr = false; 

public:
	Either() { }
	bool isEmpty() const { return empty; }
	bool isLeft()  const { return isl; }
	bool isRight() const { return isr; }
	
	static Either<T1, T2> Empty() { return Either(); }
	static Either<T1, T2> Left(T1 data) {
		Either res;
		res.empty = false;
		res.isl = true;
		res.left = data;
		return res;
	}
	static Either<T1, T2> Right(T2 data) {
		Either res;
		res.empty = false;
		res.isr = true;
		res.right = data;
		return res;
	}

	T1 getLeft() { return left; }
	T2 getRight() { return right; }
};

enum class Priority { None = 0, First = 1, Second = 2};
Priority getPrior(char data)
{
	if ((data == '+') || (data == '-')) return Priority::Second;
	if ((data == '/') || (data == '*')) return Priority::First;
	if ((data == '(') || (data == ')')) return Priority::None;
}
