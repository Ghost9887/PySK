#include "common.h"
#include "dio.h"

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cout << "Usage: ./dio [file_name]" << '\n';
    }
    else if (argc == 2) {
        Dio::run_file(argv[1]);
    }else {
        Dio::run_prompt();
    }
    return 0;
}
