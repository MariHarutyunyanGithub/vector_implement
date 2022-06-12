#include <initializer_list>
template <typename T>
class Vector 
{
public:
Vector();
Vector(const Vector&);
Vector(Vector&&);
Vector(std::size_t);
Vector(std::initializer_list<T>);
Vector(std::size_t, T);
~Vector();

Vector& operator=(const Vector&);
void push_back(const T&);
void push_back(T&&);
void pop_back();
void insert(std::size_t pos, const T& val);
void insert(std::size_t, T&&);
bool empty() const;
std::size_t size() const;
std::size_t capacity() const;
void clear();
void resize(std::size_t);
void erase(std::size_t);
T& at(std::size_t);
const T& at(std::size_t) const;
T& operator[](std::size_t);
const T& operator[](std::size_t) const;
void shrink_to_fit();
std::size_t get_cap()const
{
	return m_cap;
}
std::size_t get_size()const
{
	return m_size;
}

private:
std::size_t m_cap;
std::size_t m_size;
T* m_buf;
};

enum{bit_count = 8*sizeof(std::size_t)};
template < >
class Vector <bool>
{
    public:
        Vector();
        Vector(const Vector&);
        Vector(Vector&&);
        Vector(std::initializer_list<bool>);
        Vector(std::size_t);
        Vector(std::size_t, bool);
        ~Vector(){};

        Vector& operator=(const Vector&);
        void push_back(const Vector<bool>&);
        void push_back(Vector<bool>&&);
        void pop_back();
        void insert(std::size_t pos, const bool val);
        void insert(std::size_t, Vector<bool>&&);
        bool empty() const;
        std::size_t size() const;
        std::size_t capacity() const;
        void clear();
        void resize(std::size_t);
        void erase(std::size_t);
        Vector<bool>& at(std::size_t);
        const Vector<bool>& at(std::size_t) const;
        Vector<bool>& operator[](std::size_t);
        const Vector<bool>& operator[](std::size_t) const;
        void shrink_to_fit();

        class reference
        {
            public:
                reference();
                reference(std::size_t*,std::size_t);
                reference(const reference&);
                reference(reference&&);
                reference(const reference&&);
                reference& operator=(const reference&);
                reference& operator=(const reference&&);
                reference& operator=(bool);
                reference& operator[](std::size_t);
                const reference& operator[](std::size_t) const;
                operator bool()const;
                void flip();

            private:
                std::size_t* ptr;
                std::size_t index;
                bool val;
        };

    private:
        std::size_t m_cap;
        std::size_t m_size;
        std::size_t* m_buf;

};
#include "Vector.hpp"