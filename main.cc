#include <iostream>
#include <random>

#include "blum_micali.hh"

int main()
{
    BlumMicaliGenerator::SeedType seed = {0};
    BlumMicaliGenerator g(seed);
    std::uniform_int_distribution<> dist(1, 6);
    while (true) {
        std::cout << "Press enter to roll! " << std::flush;
        std::cin.get();
        std::cout << "You rolled a " << dist(g) << '\n' << std::endl;
    }
}
