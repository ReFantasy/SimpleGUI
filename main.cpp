#include "gui.h"
#include "iostream"
#include "random"

template <typename T, typename Distribution = std::uniform_real_distribution<T>>
T RandomNumber(const T &lo = 0, const T &hi = 1)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    Distribution dist(lo, hi);
    return dist(rng);
}

int main(int argc, char *argv[])
{
    GUI gui{};
    gui.Show();

    return 0;
}