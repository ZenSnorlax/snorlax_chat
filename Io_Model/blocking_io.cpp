#include <fstream>
#include <iostream>

int main() {
    std::ifstream file("example.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    return 0;
}
