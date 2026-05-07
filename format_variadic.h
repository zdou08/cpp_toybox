#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename Arg, typename... Args>
void printVariadic(Arg&& arg, Args&&... args) {
    std::cout << "Args remaining: " << std::endl;
    std::cout << arg << std::endl;
    ((std::cout << args << std::endl), ...);
}

inline std::string Format_Setup(std::string& format, const size_t index) {
    auto currentIndex = static_cast<int>(format.find("{", index));
    auto inputIndex = static_cast<int>(format.find("{", currentIndex));
    auto last = format.size();
    if (currentIndex <= last && inputIndex <= last) {
        auto last = format.size();
        format.replace(currentIndex, last - currentIndex, "");
    }
    return format;
}

template <typename T, typename... Args>
inline std::string Format_Setup(
    std::string& format,
    const size_t index,
    T&& value,
    Args... args) {
    printVariadic(value, std::forward<Args>(args)...);
    std::string stringReplacement = (std::ostringstream{} << value).str();
    auto last = format.size();
    size_t currentIndex = format.find("{", index);
    size_t inputIndex = format.find("}", currentIndex);
    size_t newIndex = format.find("{", currentIndex + 1);

    if (newIndex < inputIndex) {
        return Format_Setup(format, ++currentIndex, value, std::forward<Args>(args)...);
    }

    if (currentIndex <= last && inputIndex <= last) {
        size_t charReplace = inputIndex - currentIndex + 1;
        format.replace(currentIndex, charReplace, stringReplacement);
        return Format_Setup(format, currentIndex, std::forward<Args>(args)...);
    }
    else {
        return Format_Setup(format, inputIndex);
    }
}

template <typename... Args>
inline std::string Format(std::string format, Args &&...args) {
    return Format_Setup(format, 0, std::forward<Args>(args)...);
}