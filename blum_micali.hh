#ifndef BLUM_MICALI_HH
#define BLUM_MICALI_HH
#include <array>
#include <cstdint>

#include <gmp.h>

class BlumMicaliGenerator {
public:
    // The following implement the interface of a
    // UniformRandomBitGenerator
    using result_type = int;
    static constexpr result_type min()
    {
        return 0;
    }
    static constexpr result_type max()
    {
        return 1;
    }

    result_type operator()();

    using SeedType = std::array<std::uint8_t, 2281 / 8 + 1>;

    explicit BlumMicaliGenerator(const SeedType &seed);
    BlumMicaliGenerator(const BlumMicaliGenerator &other);
    BlumMicaliGenerator &operator=(const BlumMicaliGenerator &other);
    ~BlumMicaliGenerator();
private:
    mpz_t x;
    mpz_t p;
    mpz_t cutoff;
    mpz_t five;
};
#endif
