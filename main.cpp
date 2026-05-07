#include "../inc/format_variadic.h"

int main() {
    std::string test = Format("Pizza is {}", "poopy");
    std::cout << test << std::endl;
}