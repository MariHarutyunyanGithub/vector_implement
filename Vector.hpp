#ifndef VECTOR_H
#define VECTOR_H
#include <utility>
#include <stdexcept> 


template <typename T>
Vector<T>::Vector(const Vector<T>& oth)
			:m_cap{oth.m_cap}
			,m_size{oth.m_size}
			,m_buf{}
{
	if(oth.empty()){
		m_buf = new T[m_cap];
		for (std::size_t i = 0; i < m_size; ++i){
			m_buf[i] = oth.m_buf[i];
		}
	}
}

template <typename T>
void Vector<T>::push_back(const T& val)
{
	if(this->empty()){
		m_buf = new T[m_cap];
		m_buf[m_size++] = val;
	}else{
		if (m_size < m_cap){
			m_buf[m_size++] = val;
		}else{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(std::size_t i = 0; i < m_size; ++i){
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			m_buf[m_size++] = val;
		}
	}
}

template <typename T>
void Vector<T>::push_back(T&& val)
{
	if(this->empty()){
		m_buf = new T[m_cap];
		m_buf[m_size++] = std::move(val);
	}else{
		if (m_size < m_cap){
			m_buf[m_size++] = std::move(val);
		}else{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(std::size_t i = 0; i < m_size; ++i){
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			m_buf[m_size++] = std::move(val);
		}
	}
}

template <typename T>
void Vector<T>::pop_back()
{
	if(!this->empty()){
		--m_size;
	}
}

template <typename T>
void Vector<T>::insert(std::size_t pos, const T& val)
{
	if (this->empty()){
		m_buf = new T[m_cap];
		m_buf[0] = val;
	}else{
		if(m_size != m_cap){
			for (std::size_t i = m_size - 1; i >= pos; --i){
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = val;
			++m_size;
		}else{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for (std::size_t i = 0; i < pos; ++i){
				tmp[i] = m_buf[i];
			}
			tmp[pos] = val;
			for (std::size_t i = m_size; i > pos; --i){
				tmp[i] = m_buf[i - 1];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

template <typename T>
void Vector<T>::insert(std::size_t pos, T&& val)
{
	if (this->empty()){
		m_buf = new T[m_cap];
		m_buf[0] = std::move(val);
	}else{
		if(m_size != m_cap){
			for (std::size_t i = m_size - 1; i >= pos; --i){
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = std::move(val);
			++m_size;
		}else{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for (std::size_t i = 0; i < pos; ++i){
				tmp[i] = m_buf[i];
			}
			tmp[pos] = std::move(val);
			for (std::size_t i = m_size; i > pos; --i){
				tmp[i] = m_buf[i - 1];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

template <typename T>
bool Vector<T>::empty() const{
	return !m_buf;
}

template <typename T>
std::size_t Vector<T>::size() const
{
	return m_size;
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
	return m_cap;
}

template <typename T>
void Vector<T>::clear()
{
	if (!this->empty()){
		delete[]m_buf;
		m_cap = 1;
		m_size = 0;
	}
}

template <typename T>
void Vector<T>::resize(std::size_t cap)
{
	if (m_cap < cap){
		m_cap = cap;
	}else{
		T* tmp = new T[m_cap];
		for (std::size_t i = 0; i < m_size; ++i){
			tmp[i] = m_buf[i];
		}
		delete[]m_buf;
		m_buf = tmp;
		tmp = nullptr;
	}
}

template <typename T>
void Vector<T>::erase(std::size_t pos)
{
	if (!this->empty()){
		for (std::size_t i = m_size - 1; i >= pos; ++i){
			m_buf[i - 1] = m_buf[i];
		}
		--m_size;
	}
}

template <typename T>
T& Vector<T>::at(std::size_t index)
{
	if (index >= m_size){
		throw std::out_of_range(" ");
	}
	return m_buf[index];
}

template <typename T>
const T& Vector<T>::at(std::size_t index) const
{
	if (index >= m_size){
		throw std::out_of_range(" ");
	}
	return m_buf[index];
}

template <typename T>
T& Vector<T>::operator[](std::size_t index)
{
	return m_buf[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
	return m_buf[index];
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
	if (!this->empty()){
		if (m_size != m_cap){
			m_cap = m_size;
			T* tmp = new T[m_cap];
			for (size_t i = 0; i < m_size; ++i){
				tmp[i] = m_buf[i];
			}
			delete[]m_buf;
			m_buf = tmp;
			tmp = nullptr;
		}
	}
}
Vector<bool>::reference::reference(std::size_t* pt, std::size_t ind):
						ptr{pt},
						index{ind},
						val{}
{
	val = ptr[index/bit_count] & (1 << (index % bit_count));
}

void Vector<bool>::reference::flip()
{
	ptr[index/bit_count] ^= (1 << (index % bit_count));
	val != false;
}

Vector<bool>::reference::reference (const reference& oth):
					ptr{oth.ptr},
					index{oth.index},
					val{oth.val}{}

Vector<bool>::reference::reference(const Vector<bool>::reference&& oth):
					index{oth.index},
					val{oth.val}{}


Vector<bool>::reference& Vector<bool>::reference::operator=(const Vector<bool>::reference& oth)
{
	if (val != oth.val){
		this->flip();
	}
	return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=(const Vector<bool>::reference&& oth)
{
	if (val != oth.val){
		this->flip();
	}
	return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=(bool val)
{
	if(this->val != val){
		this->flip();
	}
	return *this;
}

Vector<bool>::reference::operator bool() const
{
	return val;
}

Vector<bool>::Vector(const Vector<bool>& oth):
				m_cap{oth.m_cap},
				m_size{oth.m_size}
{
	m_buf= new std::size_t[m_cap/bit_count];
	for(int i = 0; i < (m_cap/bit_count); ++i){
		m_buf[i] = oth.m_buf[i];
	}
}

Vector<bool>::Vector(std::initializer_list<bool>init):
				m_cap{},
				m_size{},
				m_buf{}
{
	if (init.size()){
		while (m_cap < init.size()){
			m_cap += bit_count;
		}
	}
	m_buf = new std::size_t[m_cap/bit_count];
	std::size_t bit = 1;
	int i = 0;
	for (auto it = init.begin(); it != init.end(); ++ it, ++i){
		if (*it){
			m_buf[i/bit_count] |= (1 << i % bit_count);
		}
		bit <<= 1;
	}
}

Vector<bool>::Vector(std::size_t count):
		m_cap{},
		m_size{count},
		m_buf{}
{
	if (count){
		while(m_cap < count){
			m_cap += bit_count;
		}
		m_buf = new std::size_t[m_cap / bit_count];
	}
}

Vector<bool>::Vector(std::size_t count, bool val):
				m_cap{},
				m_size{count},
				m_buf{}
{
	if (count){
		while (m_cap < count){
			m_cap += bit_count;
		}
		m_buf = new std::size_t[m_cap / bit_count];
		if (val){
			std::size_t bit = 1;
			for (int i = 0; i < m_size; ++i){
				m_buf[i / bit_count] |= bit;
			}
			bit <<= 1;
		}
	}
}

void Vector<bool>::insert(std::size_t pos,const bool val)
{
	if (this->empty()){
		m_cap = bit_count;
		m_buf = new std::size_t[1];
		m_buf[m_size++] = val;
		return;
	}
	if (m_size == m_cap){
		m_cap += bit_count;
		std::size_t* ptr = new std::size_t[m_cap / bit_count];
		for (int i = 0; i < (m_size / bit_count); ++i){
			ptr[i] = m_buf[i];
		}
		delete[]m_buf;
		m_buf = ptr;
		ptr = nullptr;
	}
	for (std::size_t i = m_size; i > pos; --i){
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[pos] = val;
	++m_size;
}

void Vector<bool>::erase(std::size_t pos)
{
	if (this->empty()){
		return;
	}
	for (std::size_t i = m_size; i > pos; --i){
		(*this)[i - 1] = (*this)[i];
	}
	--m_size;
}

Vector<bool>& Vector<bool>::operator[](std::size_t pos)
{
	return Vector<bool>::reference(m_buf, pos);
}

const Vector<bool>::reference Vector<bool> operator[](std::size_t pos)
{
	return Vector<bool>::reference(m_buf, pos);
}

void Vector<bool>::push_back(bool val)
{
	if (this->empty()){
		m_cap = bit_count;
		m_buf = new std::size_t[1];
		(*this)[m_size++] = val;
		return;
	}
	if (m_size == m_cap){
		m_cap += bit_count;
		std::size_t* ptr = new std::size_t[m_cap / bit_count];
		for (int i = 0; i < (m_size / bit_count); ++i){
			ptr[i] = m_buf[i];
		}
		delete[]m_buf;
		m_buf = ptr;
		ptr = nullptr;
	}
	(*this)[m_size++] = val;
}

void Vector<bool>::pop_back()
{
	(*this)[m_size--] = false;
}
#endif