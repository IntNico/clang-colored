#include <stdio.h>
#include "clang_colored.h"

int main(void) {
    ColoredString *cs;

    cs = colored("Hello, World!");
    printf("%s\n", cs->red(cs)->bold(cs)->print(cs));
    cs->free(cs);

    cs = colored("Success!");
    printf("%s\n", cs->green(cs)->bold(cs)->print(cs));
    cs->free(cs);

    cs = colored("Warning: low disk space");
    printf("%s\n", cs->yellow(cs)->italic(cs)->print(cs));
    cs->free(cs);

    cs = colored("Error: segmentation fault");
    printf("%s\n", cs->bright_red(cs)->bold(cs)->underline(cs)->print(cs));
    cs->free(cs);

    cs = colored("INFO");
    printf("%s\n", cs->white(cs)->on_blue(cs)->bold(cs)->print(cs));
    cs->free(cs);

    cs = colored("rainbow text");
    printf("%s\n", cs->bright_magenta(cs)->on_bright_black(cs)->underline(cs)->bold(cs)->print(cs));
    cs->free(cs);

    cs = colored("strikethrough deleted text");
    printf("%s\n", cs->dim(cs)->strikethrough(cs)->print(cs));
    cs->free(cs);

    cs = colored("cleared then recolored");
    cs->red(cs)->bold(cs)->underline(cs);
    cs->clear(cs);
    cs->cyan(cs)->italic(cs);
    printf("%s\n", cs->print(cs));
    cs->free(cs);

    return 0;
}