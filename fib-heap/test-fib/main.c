#include "parser.h"

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("usage:%s [query_list]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    print_result(execute_ll(parse(argv[1])));
}
