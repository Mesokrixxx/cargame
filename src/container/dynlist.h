#pragma once

#include "memory/mallocator.h"
#include "math/util.h"
#include <string.h>

#define DYNLIST_MIN_CAPACITY 4

template <typename T>
class Dynlist {
public:
	Dynlist() = default;
	Dynlist(Allocator& allocator)
		: _allocator(allocator) {}
	Dynlist(Allocator& allocator, u64 capacity)
		: _allocator(allocator) { reserve(capacity); }
	Dynlist(Allocator& allocator, const T *data, u64 n)
		: _allocator(allocator) { set(data, n); }
	template <u64 N> Dynlist(Allocator& allocator, const T (&data)[N])
		: _allocator(allocator) { set(data); }
	Dynlist(Dynlist&& other);
	Dynlist& operator=(const Dynlist& other);
	Dynlist& operator=(Dynlist&& other);
	~Dynlist();

	Dynlist(u64 capacity)
		: Dynlist(g_mallocator, capacity) {}
	Dynlist(const T *data, u64 n)
		: Dynlist(g_mallocator, data, n) {}
	template <u64 N> Dynlist(const T (&data)[N])
		: Dynlist(g_mallocator, data) {}
	Dynlist(const Dynlist& other)
		: Dynlist(other._allocator, other.data(), other.size()) {}
	
	template <u64 N> Dynlist& operator=(const T (&data)[N]) 
		{ set(data, N); return *this; }

	T& operator[](u64 i) { return data()[i]; }
	const T& operator[](u64 i) const { return data()[i]; }

	void clear();
	void reserve(u64 capacity);
	
	virtual void set(const T *data, u64 n);
	void set(const Dynlist& other) { set(other.data(), other.size()); }
	void set(Dynlist&& other) { Dynlist<T>::operator=((Dynlist&&)other); }
	template <u64 N> void set(const T (&data)[N]) { set(data, N); }
	
	virtual void pushback(const T *data, u64 n);
	void pushback(const T& x) { pushback(&x, 1); }
	void pushback(const Dynlist& other) { pushback(other.data(), other.size()); }
	template <u64 N> void pushback(const T (&data)[N]) { pushback(data, N); }

	u64 size() const { return _size; }
	u64 capacity() const { return _capacity; }
	T *data() { return _data; }
	const T *data() const { return _data; }

	void setSize(u64 size) { _size = size; }

protected:
	void _copyDataImpl(T *dst, const T *src, u64 n);

private:
	Allocator& _allocator = g_mallocator;
	u64 _size = 0;
	u64 _capacity = 0;
	T *_data = nullptr;

	void _destroyInternal();
};

template <typename T>
Dynlist<T>::Dynlist(Dynlist&& other)
: _allocator(other._allocator), _size(other._size), _capacity(other._capacity), _data(other._data) {
	other._size = 0;
	other._capacity = 0;
	other._data = nullptr;
}

template <typename T>
Dynlist<T>& Dynlist<T>::operator=(const Dynlist& other) {
	if (this != &other) {
		set(other);
	}
	return *this;
}

template <typename T>
Dynlist<T>& Dynlist<T>::operator=(Dynlist&& other) {
	if (this != &other) {
		if (&_allocator == &other._allocator) {
			_destroyInternal();
			_size = other._size;
			_capacity = other._capacity;
			_data = other._data;

			other._size = 0;
			other._capacity = 0;
			other._data = nullptr;
		}
		else
			set(other);
	}
	return *this;
}

template <typename T>
Dynlist<T>::~Dynlist() {
	_destroyInternal();
}

template <typename T>
void Dynlist<T>::clear() {
	if (!types::trivially_destructible<T>()) {
		for (u64 i = 0; i < _size; i++)
			_data[i].~T();
	}
	_size = 0;
}

template <typename T>
void Dynlist<T>::reserve(u64 capacity) {
	capacity = math::roundupPow2(capacity, 2);
	if (_capacity >= capacity)
		return ;

	if (_capacity) {
		while (_capacity < capacity)
			_capacity *= 2;
	}
	else {
		_capacity = 
			capacity > DYNLIST_MIN_CAPACITY ?
				capacity : DYNLIST_MIN_CAPACITY;
	}

	T *oData = _data;
	_data = (T *)_allocator.allocMem(sizeof(T) * _capacity);
	if (!oData)
		return ;
	
	_copyDataImpl(_data, oData, _size);
	if (!types::trivially_destructible<T>()) {
		for (u64 i = 0; i < _size; i++)
			oData[i].~T();
	}
	_allocator.freeMem(oData);
}

template <typename T>
void Dynlist<T>::set(const T *data, u64 n) {
	clear();
	reserve(n);
	_copyDataImpl(_data, data, n);
	_size = n;
}

template <typename T>
void Dynlist<T>::pushback(const T *data, u64 n) {
	reserve(_size + n);
	_copyDataImpl(_data + _size, data, n);
	_size += n;
}

template <typename T>
void Dynlist<T>::_copyDataImpl(T *dst, const T *src, u64 n) {
	if (!types::trivially_copyable<T>()) {
		for (u64 i = 0; i < n; i++)
			new (&dst[i]) T(src[i]);
	}
	else
		memcpy(dst, src, sizeof(T) * n);
}

template <typename T>
void Dynlist<T>::_destroyInternal() {
	clear();
	_allocator.freeMem(_data);
	_data = nullptr;
	_capacity = 0;
}
