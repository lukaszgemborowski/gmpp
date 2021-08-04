#ifndef GMPP_INTEGER_HPP
#define GMPP_INTEGER_HPP

#include <gmp.h>
#include <stdexcept>
#include <type_traits>
#include <string>

namespace gmpp
{

struct invalid_integer_error : std::runtime_error
{
    invalid_integer_error(std::string const& value)
        : std::runtime_error{value}
    {}
};

class div_result;

class integer
{
public:
    integer() noexcept;
    integer(integer const& rhs) noexcept;
    integer(integer&& rhs) noexcept;

    // value-construction
    explicit integer(const char* str);
    integer(const char* str, int base);
    explicit integer(unsigned long int rhs) noexcept;
    explicit integer(signed long int rhs) noexcept;
    explicit integer(signed int rhs) noexcept;

    ~integer();

    // operations
    void add(integer const& other) noexcept;
    void sub(integer const& other) noexcept;
    void mul(integer const& other) noexcept;
    void neg() noexcept;
    // floor div
    void div_floor_quotient(integer const& other) noexcept;
    void div_floor_reminder(integer const& other) noexcept;
    div_result div_floor_qr(integer const& other) const noexcept;

    // ceil div
    void div_ceil_quotient(integer const& other) noexcept;
    void div_ceil_reminder(integer const& other) noexcept;
    div_result div_ceil_qr(integer const& other) const noexcept;

    // query
    bool is_negative() const noexcept;
    bool fits_ulong() const noexcept;
    bool fits_slong() const noexcept;
    bool fits_uint() const noexcept;
    bool fits_sint() const noexcept;
    bool fits_ushort() const noexcept;
    bool fits_sshort() const noexcept;

    template<class T>
    bool fits () const noexcept;

    int compare(integer const& other) const noexcept;

    std::string to_string() const;

private:
    mpz_t gmp_int_;

    // used for move to indicate that underlying data structed was freed
    bool freed_ = false;
};

template<class T>
bool integer::fits() const noexcept {
    if constexpr (std::is_same_v<T, unsigned long>) {
        return fits_ulong();
    } else if constexpr (std::is_same_v<T, signed long>) {
        return fits_slong();
    } else if constexpr (std::is_same_v<T, unsigned int>) {
        return fits_uint();
    } else if constexpr (std::is_same_v<T, signed int>) {
        return fits_sint();
    } else if constexpr (std::is_same_v<T, unsigned short>) {
        return fits_ushort();
    } else if constexpr (std::is_same_v<T, signed short>) {
        return fits_sshort();
    }

    return false;
}

struct div_result
{
    integer quotient;
    integer reminder;
};

inline integer operator+(integer a, integer const& b) {
    a.add(b); return a;
}

inline integer operator-(integer a, integer const& b) {
    a.sub(b); return a;
}

inline integer operator*(integer a, integer const& b) {
    a.mul(b); return a;
}

inline integer& operator++(integer& a) {
    a.add(integer{1});
    return a;
}

inline integer operator++(integer& a, int) {
    integer b{a};
    a.add(integer{1});
    return b;
}

inline integer& operator--(integer& a) {
    a.sub(integer{1});
    return a;
}

inline integer operator--(integer& a, int) {
    integer b{a};
    a.sub(integer{1});
    return b;
}

inline integer operator-(integer const& a) {
    integer b{a};
    b.neg();
    return b;
}

inline bool operator<(integer const& a, integer const& b) {
    return a.compare(b) < 0;
}

inline bool operator>(integer const& a, integer const& b) {
    return a.compare(b) > 0;
}

inline bool operator==(integer const& a, integer const& b) {
    return a.compare(b) == 0;
}

inline bool operator!=(integer const& a, integer const& b) {
    return a.compare(b) != 0;
}

inline div_result operator/(integer const &a, integer const& b) {
    return a.div_floor_qr(b);
}

inline integer quotient(div_result const& r) {
    return r.quotient;
}

inline integer reminder(div_result const& r) {
    return r.reminder;
}

namespace literals
{
inline integer operator"" _bi(unsigned long long int value) {
    return integer{static_cast<unsigned long int>(value)};
}
}

} // namespace gmpp

#endif // GMPP_INTEGER_HPP