#include <iostream>
#include <fstream>
#include <sstream>
#include "dio.h"

void run_file(const char *file_path) {
    std::string source;
    std::fstream file(file_path);

    std::stringstream buffer;
    buffer << file.rdbuf();
    source = buffer.str();
    Dio::run(source);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        run_file(argv[1]);
    }else {
        std::cerr << "Vyuzitie: dio [cesta]" << '\n';
        exit(64);
    }
    return 0;
}
