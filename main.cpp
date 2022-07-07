
#include <iostream>

using namespace std;


template<typename T>
class Vector
{
	T* first;
	T* last;
	T* end_;
	int capacity;

	void extend()
	{
		if ((end_ - last) < 2)
		{
			T* tmp{ new T[size() + capacity] };
			memcpy(tmp, first, sizeof(T*) * size());
			end_ = tmp + size() + capacity;
			last = tmp + size();
			T* to_delete = first;
			first = tmp;
			delete to_delete;
		}
	}

	void extend(int new_size)
	{
		T* tmp{ new T[new_size + capacity] };
		memcpy(tmp, first, sizeof(T*) * size());
		end_ = tmp + new_size + capacity;
		last = tmp + new_size + 1;
		T* to_delete = first;
		first = tmp;
		delete to_delete;
	}

	template<class Iter>  // класс итератор
	class NodeIterator
	{
		friend class Vector;
	public:
		typedef Iter iterator_type;
		typedef std::input_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

		iterator_type* value;

	private:
		NodeIterator(Iter* p) : value{ p } { } //закрытый конструктор

	public:
		NodeIterator(const NodeIterator& it) : value{ it.value } {} // конструктор копирования 

		bool operator !=(NodeIterator const& other) const
		{
			return value != other.value;
		}
		bool operator ==(NodeIterator const& other) const
		{
			return value == other.value;
		}
		typename NodeIterator::reference operator*() const
		{
			return *value;
		}
		NodeIterator& operator++()
		{
			if (value)
			{
				value++;
				return *this;
			}
		}
	};
public:
	Vector() : capacity{ 10 }
	{
		first = new T[capacity];
		last = first;
		end_ = first + capacity;
	}
	Vector(int capacity_) : capacity{ capacity_ }
	{
		first = new T;
		last = first;
		end_ = first + capacity;
	}

	int size() { return last - first; }


	void resize(int new_size)
	{
		if (new_size > size())
			extend(new_size - 1);
		else
		{
			last -= size() - new_size;
		}

	}


	void insert(T data, int index)
	{
		if (index >= size() || index < 0)
			throw logic_error("Out of range");
		else
			first[index] = data;
	}

	void push_back(T data)
	{
		*last = data;
		last++;
		extend();
	}

	void pop_back()
	{
		last--;
	}

	T& at(size_t index)
	{
		if (index >= size() || index < 0)
			throw logic_error("Out of range");
		else
		{
			return first[index];
		}
	}

	T& operator[](size_t index) { return at(index); }


	typedef NodeIterator<T> iterator;
	typedef NodeIterator<const T> const_iterator;
	iterator begin()
	{
		return first;
	}

	iterator end()
	{
		return last;
	}

	const_iterator begin() const
	{
		return first;
	}

	const_iterator end() const
	{
		return last;
	}
};



int main()
{
	Vector<int> test;
	test.resize(15);
	for (auto& item : test)
		item = 999;
	for (auto& item : test)
		cout << item << " ";
	cout << endl;
}

