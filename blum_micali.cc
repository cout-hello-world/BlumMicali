#include "blum_micali.hh"

#include <gmp.h>

constexpr BlumMicaliGenerator::SeedType Pi =
#include "pi.inc"

BlumMicaliGenerator::BlumMicaliGenerator(const SeedType &seed)
{
    SeedType xored;
    for (SeedType::size_type i = 0; i != seed.size(); ++i) {
        xored[i] = (seed[i] ^ Pi[i]);
    }

    mpz_init(x);
    mpz_import(x, seed.size(), -1, sizeof(seed[0]), 0, 0, seed.data());
    mpz_init(p);
    mpz_ui_pow_ui(p, 2, 2281);
    mpz_mod(x, x, p);
    mpz_sub_ui(p, p, 1);
    if (mpz_cmp(x, p) == 0) {
        mpz_clears(x, p, NULL);
        throw;
    }

    mpz_init(cutoff);
    mpz_tdiv_q_ui(cutoff, p, 2);

    mpz_init_set_ui(five, 5);
}

BlumMicaliGenerator::result_type BlumMicaliGenerator::operator()()
{
    mpz_powm(x, five, x, p);
    return mpz_cmp(x, cutoff) <= 0;
}

BlumMicaliGenerator::BlumMicaliGenerator(const BlumMicaliGenerator &other)
{
    mpz_init_set(x, other.x);
    mpz_init_set(p, other.p);
    mpz_init_set(cutoff, other.cutoff);
    mpz_init_set(five, other.five);
}

BlumMicaliGenerator &BlumMicaliGenerator::operator=(const BlumMicaliGenerator &other)
{
    mpz_set(x, other.x);
    mpz_set(p, other.p);
    mpz_set(cutoff, other.cutoff);
    mpz_set(five, other.five);
    return *this;
}

BlumMicaliGenerator::~BlumMicaliGenerator()
{
    mpz_clears(x, p, cutoff, five, NULL);
}
