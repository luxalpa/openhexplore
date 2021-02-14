#pragma once

#include <cstdint>

#define assert_struct_size(x, y) static_assert(sizeof(x) == (y), "Improper struct size")

#define HEXP_CALLPROC(address)					(((void(*)())address)())
#define HEXP_CALLFUNC(address, returnType)		(((returnType(*)())address)())

/**
* x86 register structure, only used for easy interop to Locomotion code.
*/
#pragma pack(push, 1)
struct registers
{
    union
    {
        int32_t eax;
        int16_t ax;
        struct
        {
            int8_t al;
            int8_t ah;
        };
    };
    union
    {
        int32_t ebx;
        int16_t bx;
        struct
        {
            int8_t bl;
            int8_t bh;
        };
    };
    union
    {
        int32_t ecx;
        int16_t cx;
        struct
        {
            int8_t cl;
            int8_t ch;
        };
    };
    union
    {
        int32_t edx;
        int16_t dx;
        struct
        {
            int8_t dl;
            int8_t dh;
        };
    };
    union
    {
        int32_t esi;
        int16_t si;
    };
    union
    {
        int32_t edi;
        int16_t di;
    };
    union
    {
        int32_t ebp;
        int16_t bp;
    };

    registers();
};
assert_struct_size(registers, 7 * 4);
#pragma pack(pop)

#ifdef USE_MMAP
    #if defined(PLATFORM_64BIT)
        #define GOOD_PLACE_FOR_DATA_SEGMENT ((uintptr_t)0x200000000)
    #elif defined(PLATFORM_32BIT)
        #define GOOD_PLACE_FOR_DATA_SEGMENT ((uintptr_t)0x09000000)
    #else
        #error "Unknown platform"
    #endif
#else
    #define GOOD_PLACE_FOR_DATA_SEGMENT ((uintptr_t)0x8A4000)
#endif

#define ADDR(address, type)     ((type*)(address))
#define ARR(address, type, size)     (*reinterpret_cast<type(*)[size]>((type*)(address)))
#define GLOB(address, type)      (*((type*)(address)))

/**
* Returns the flags register
*
* Flags register is as follows:
* 0bSZ0A_0P0C_0000_0000
* S = Signed flag
* Z = Zero flag
* C = Carry flag
* A = Adjust flag
* P = Parity flag
* All other bits are undefined.
*/
int32_t HEXP_CALLPROC_X(int32_t address, int32_t _eax, int32_t _ebx, int32_t _ecx, int32_t _edx, int32_t _esi, int32_t _edi, int32_t _ebp);
int32_t HEXP_CALLPROC_X(int32_t address, const registers &registers);
int32_t HEXP_CALLPROC_X(int32_t address);

/**
 * Returns the flags register
 *
 * Flags register is as follows:
 * 0bSZ0A_0P0C_0000_00000
 * S = Signed flag
 * Z = Zero flag
 * C = Carry flag
 * A = Adjust flag
 * P = Parity flag
 * All other bits are undefined.
 */
int32_t HEXP_CALLFUNC_X(int32_t address, int32_t *_eax, int32_t *_ebx, int32_t *_ecx, int32_t *_edx, int32_t *_esi, int32_t *_edi, int32_t *_ebp);
int32_t HEXP_CALLFUNC_X(int32_t address, registers &registers);

template<typename T, uint32_t TAddress>
struct hexp_global
{
    void operator=(T rhs)
    {
        GLOB(TAddress, T) = rhs;
    }

    operator T()
    {
        return GLOB(TAddress, T);
    }

    T* operator &() {
        return (T*)TAddress;
    }
};

constexpr uintptr_t remap_address(uintptr_t locoAddress)
{
    return GOOD_PLACE_FOR_DATA_SEGMENT - 0x008A4000 + locoAddress;
}

template<uint32_t TAddress, typename T>
constexpr T& addr()
{
    return *((T*)remap_address(TAddress));
}

/**
* Returns the flags register
*
* Flags register is as follows:
* 0bSZ0A_0P0C_0000_0000
* S = Signed flag
* Z = Zero flag
* C = Carry flag
* A = Adjust flag
* P = Parity flag
* All other bits are undefined.
*/
int32_t call(int32_t address);
int32_t call(int32_t address, registers& registers);

template<typename T, uintptr_t TAddress>
struct loco_global
{
public:
    typedef T type;
    typedef type* pointer;
    typedef type& reference;
    typedef const type& const_reference;

private:
    pointer _Myptr;

public:
    loco_global()
    {
        _Myptr = &(addr<TAddress, T>());
    }

    operator reference()
    {
        return addr<TAddress, T>();
    }

    loco_global& operator=(const_reference v)
    {
        addr<TAddress, T>() = v;
        return *this;
    }

    loco_global& operator+=(const_reference v)
    {
        addr<TAddress, T>() += v;
        return *this;
    }

    loco_global& operator|=(const_reference v)
    {
        addr<TAddress, T>() |= v;
        return *this;
    }

    loco_global& operator&=(const_reference v)
    {
        addr<TAddress, T>() &= v;
        return *this;
    }

    loco_global& operator^=(const_reference v)
    {
        addr<TAddress, T>() ^= v;
        return *this;
    }

    loco_global& operator-=(const_reference v)
    {
        addr<TAddress, T>() -= v;
        return *this;
    }

    loco_global& operator++()
    {
        addr<TAddress, T>()++;
        return *this;
    }

    T operator++(int)
    {
        reference ref = addr<TAddress, T>();
        T temp = ref;
        ref++;
        return temp;
    }

    loco_global& operator--()
    {
        addr<TAddress, T>()--;
        return *this;
    }

    T operator--(int)
    {
        reference ref = addr<TAddress, T>();
        T temp = ref;
        ref--;
        return temp;
    }

    reference operator*()
    {
        return addr<TAddress, T>();
    }

    pointer operator->()
    {
        return &(addr<TAddress, T>());
    }

    constexpr size_t size() const
    {
        return sizeof(T);
    }
};

template<typename T>
struct loco_global_iterator
{
private:
    T* _ptr;

public:
    loco_global_iterator(T* p)
            : _ptr(p)
    {
    }
    loco_global_iterator& operator++()
    {
        ++_ptr;
        return *this;
    }
    loco_global_iterator operator++(int)
    {
        auto temp = *this;
        ++_ptr;
        return temp;
    }
    loco_global_iterator& operator--()
    {
        --_ptr;
        return *this;
    }
    loco_global_iterator operator--(int)
    {
        auto temp = *this;
        --_ptr;
        return temp;
    }
    bool operator==(const loco_global_iterator& rhs)
    {
        return _ptr == rhs._ptr;
    }
    bool operator!=(const loco_global_iterator& rhs)
    {
        return _ptr != rhs._ptr;
    }
    T& operator*()
    {
        return *_ptr;
    }
};

template<typename T, size_t TCount, uintptr_t TAddress>
struct loco_global<T[TCount], TAddress>
{
public:
    typedef T type;
    typedef type* pointer;
    typedef type& reference;
    typedef const type& const_reference;
    typedef loco_global_iterator<T> iterator;

private:
    pointer _Myfirst;
    pointer _Mylast;

public:
    loco_global()
    {
        _Myfirst = get();
        _Mylast = _Myfirst + TCount;
    }

    operator pointer()
    {
        return get();
    }

    pointer get() const
    {
        return reinterpret_cast<pointer>(&addr<TAddress, type>());
    }

    reference operator[](int idx)
    {
#ifndef NDEBUG
        if (idx < 0 || static_cast<size_t>(idx) >= size())
            {
                throw std::out_of_range("loco_global: bounds check violation!");
            }
#endif
        return get()[idx];
    }

    constexpr size_t size() const
    {
        return TCount;
    }

    iterator begin() const
    {
        return iterator(&addr<TAddress, T>());
    }

    iterator end() const
    {
        const pointer ptrEnd = (&addr<TAddress, T>()) + TCount;
        return iterator(ptrEnd);
    }
};