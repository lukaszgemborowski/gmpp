#include "gmpp/integer.hpp"
#include <cstring>

namespace gmpp
{

integer::integer() noexcept
{
    mpz_init(gmp_int_);
}

integer::integer(integer const& rhs) noexcept
{
    mpz_init_set(gmp_int_, rhs.gmp_int_);
}

integer::integer(integer&& rhs) noexcept
{
    std::memcpy(&gmp_int_, &rhs.gmp_int_, sizeof(mpz_t));
    rhs.freed_ = true; // rhs is no longer valid
}

integer::~integer()
{
    if (!freed_) mpz_clear(gmp_int_);
}

integer::integer(const char* str) 
{
    if(mpz_init_set_str(gmp_int_, str, 10) == -1) {
        throw invalid_integer_error(str);
    }
}

integer::integer(const char* str, int base)
{
    if(mpz_init_set_str(gmp_int_, str, base) == -1) {
        throw invalid_integer_error(str);
    }
}

integer::integer(unsigned long int rhs) noexcept
{
    mpz_init_set_ui(gmp_int_, rhs);
}


integer::integer(signed long int rhs) noexcept
{
    mpz_init_set_si(gmp_int_, rhs);
}

integer::integer(signed int rhs) noexcept
{
    mpz_init_set_si(gmp_int_, rhs);
}

void integer::add(integer const& other) noexcept
{
    mpz_add(gmp_int_, gmp_int_, other.gmp_int_);
}

void integer::sub(integer const& other) noexcept
{
    mpz_sub(gmp_int_, gmp_int_, other.gmp_int_);
}

void integer::mul(integer const& other) noexcept
{
    mpz_mul(gmp_int_, gmp_int_, other.gmp_int_);
}

void integer::neg() noexcept
{
    mpz_neg(gmp_int_, gmp_int_);
}

void integer::div_floor_quotient(integer const& other) noexcept
{
    mpz_fdiv_q(gmp_int_, gmp_int_, other.gmp_int_);
}

void integer::div_floor_reminder(integer const& other) noexcept
{
    mpz_fdiv_r(gmp_int_, gmp_int_, other.gmp_int_);
}

div_result integer::div_floor_qr(integer const& other) const noexcept
{
    div_result result;

    mpz_fdiv_qr(
        result.quotient.gmp_int_,
        result.reminder.gmp_int_,
        gmp_int_,
        other.gmp_int_
    );

    return result;
}

void integer::div_ceil_quotient(integer const& other) noexcept
{
    mpz_cdiv_q(gmp_int_, gmp_int_, other.gmp_int_);
}

void integer::div_ceil_reminder(integer const& other) noexcept
{
    mpz_cdiv_r(gmp_int_, gmp_int_, other.gmp_int_);
}

div_result integer::div_ceil_qr(integer const& other) const noexcept
{
    div_result result;

    mpz_cdiv_qr(
        result.quotient.gmp_int_,
        result.reminder.gmp_int_,
        gmp_int_,
        other.gmp_int_
    );

    return result;
}

bool integer::fits_ulong() const noexcept
{
    return mpz_fits_ulong_p(gmp_int_);
}

bool integer::fits_slong() const noexcept
{
    return mpz_fits_slong_p(gmp_int_);
}

bool integer::fits_uint() const noexcept
{
    return mpz_fits_uint_p(gmp_int_);
}

bool integer::fits_sint() const noexcept
{
    return mpz_fits_sint_p(gmp_int_);
}

bool integer::fits_ushort() const noexcept
{
    return mpz_fits_ushort_p(gmp_int_);
}

bool integer::fits_sshort() const noexcept
{
    return mpz_fits_sshort_p(gmp_int_);
}

int integer::compare(integer const& other) const noexcept
{
    return mpz_cmp(gmp_int_, other.gmp_int_);
}

bool integer::is_negative() const noexcept
{
    return compare(integer{0}) < 0;
}

std::string integer::to_string() const
{
    bool const neg = is_negative();
    std::string result(static_cast<std::string::size_type>(mpz_sizeinbase(gmp_int_, 10) + (neg?1:0)),'\0');
    mpz_get_str(&result[0], 10, gmp_int_);
    return result;
}

} // namespace gmpp