#include "Menu.h"
#include <iostream>
#include <exception>
#include <filesystem>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT "."
#endif

int main() {
    try {
        std::filesystem::current_path(PROJECT_ROOT);

        Menu menu;
        menu.ejecutar();
    } catch (const std::exception &error) {
        std::cerr << "Error fatal del sistema: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
