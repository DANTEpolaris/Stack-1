#include <iostream>

template <typename T> 
class stack
{
public: 
	stack();                        //noexc
	stack(const stack&);            //noexc
	~stack();                       //noexc
	size_t count() const;           //noexc
	void push(T const &);           
	T& top(const stack&);           //noexc
	void pop();                     //+
	stack& operator=(const stack&); //+
private:
	T * array_;
	size_t array_size_;
	size_t count_;
}; 

template<typename T>
T* copy_mas(const T *p1, size_t c, size_t s)
{
	T *p2 = new T[s];
	try
	{ 
		copy(p1, p1 + c, p2); 
	}
	catch (...)
	{ 
		delete[] p2; 
		throw; 
	}
	return p2;
}

template <typename T>
stack<T>::stack() noexcept : array_(nullptr), array_size_(0), count_(0){};

template <typename T>
stack<T>::stack(const stack<T>& x) noexcept : array_size_(x.array_size_), count_(x.count_)
{
	array_ = new T[array_size_];
	for (int i = 0; i < count_; i++) array_[i] = x.array_[i];
}

template <typename T>
stack<T>::~stack() noexcept
{
	delete[] array_;
}

template <typename T>
size_t stack<T>::count() noexcept const 
{
	return count_;
}

template <typename T>
void stack<T>::push(T const &a)
{
	if (count_ == array_size_)
	{
		T *p = copy_mas(array_, count_, array_size_*2 + (count_ == 0));
		delete [] array_;
		array_=p;
		array_size_ =array_size_*2+(count_==0);
	}
	array_[count_] = a;
	++count_;
}

template <typename T>
T& stack<T>::top(const stack<T>& x) noexcept
{
    return  x.array_[x.count];
}

template <typename T>
void stack<T>::pop()
{
    if (count_ == 0) throw("stack is empty");
	else {
		array_[count_]=0;
        count_--;
	}
}

}

template<typename T>
stack<T>& stack<T>::operator=(const stack& b){
	if (this != &b){
		T *p = array_;
		array_ = copy_mas(b.array_, b.count_, b.array_size_);
		delete[] p;
		count_ = b.count_;
		array_size_ = b.array_size_;
	}
	return *this;
}
