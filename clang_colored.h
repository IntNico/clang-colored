#ifndef CLANG_COLORED_H
#define CLANG_COLORED_H

#define MAX_OUTPUT_LEN 1024

typedef enum {
    FG_NONE          = -1,
    FG_BLACK         = 30,
    FG_RED           = 31,
    FG_GREEN         = 32,
    FG_YELLOW        = 33,
    FG_BLUE          = 34,
    FG_MAGENTA       = 35,
    FG_CYAN          = 36,
    FG_WHITE         = 37,
    FG_BRIGHT_BLACK  = 90,
    FG_BRIGHT_RED    = 91,
    FG_BRIGHT_GREEN  = 92,
    FG_BRIGHT_YELLOW = 93,
    FG_BRIGHT_BLUE   = 94,
    FG_BRIGHT_MAGENTA= 95,
    FG_BRIGHT_CYAN   = 96,
    FG_BRIGHT_WHITE  = 97,
} fg_color;

typedef enum {
    BG_NONE          = -1,
    BG_BLACK         = 40,
    BG_RED           = 41,
    BG_GREEN         = 42,
    BG_YELLOW        = 43,
    BG_BLUE          = 44,
    BG_MAGENTA       = 45,
    BG_CYAN          = 46,
    BG_WHITE         = 47,
    BG_BRIGHT_BLACK  = 100,
    BG_BRIGHT_RED    = 101,
    BG_BRIGHT_GREEN  = 102,
    BG_BRIGHT_YELLOW = 103,
    BG_BRIGHT_BLUE   = 104,
    BG_BRIGHT_MAGENTA= 105,
    BG_BRIGHT_CYAN   = 106,
    BG_BRIGHT_WHITE  = 107,
} bg_color;

typedef enum {
    STYLE_BOLD          = 1 << 0,
    STYLE_DIM           = 1 << 1,
    STYLE_ITALIC        = 1 << 2,
    STYLE_UNDERLINE     = 1 << 3,
    STYLE_BLINK         = 1 << 4,
    STYLE_REVERSED      = 1 << 5,
    STYLE_STRIKETHROUGH = 1 << 6,
} style_flag;

typedef struct ColoredString ColoredString;

struct ColoredString {
    char        *str;
    fg_color     fg;
    bg_color     bg;
    int          styles;
    char         output[MAX_OUTPUT_LEN];

    ColoredString *(*black)(ColoredString *cs);
    ColoredString *(*red)(ColoredString *cs);
    ColoredString *(*green)(ColoredString *cs);
    ColoredString *(*yellow)(ColoredString *cs);
    ColoredString *(*blue)(ColoredString *cs);
    ColoredString *(*magenta)(ColoredString *cs);
    ColoredString *(*cyan)(ColoredString *cs);
    ColoredString *(*white)(ColoredString *cs);

    ColoredString *(*bright_black)(ColoredString *cs);
    ColoredString *(*bright_red)(ColoredString *cs);
    ColoredString *(*bright_green)(ColoredString *cs);
    ColoredString *(*bright_yellow)(ColoredString *cs);
    ColoredString *(*bright_blue)(ColoredString *cs);
    ColoredString *(*bright_magenta)(ColoredString *cs);
    ColoredString *(*bright_cyan)(ColoredString *cs);
    ColoredString *(*bright_white)(ColoredString *cs);

    ColoredString *(*on_black)(ColoredString *cs);
    ColoredString *(*on_red)(ColoredString *cs);
    ColoredString *(*on_green)(ColoredString *cs);
    ColoredString *(*on_yellow)(ColoredString *cs);
    ColoredString *(*on_blue)(ColoredString *cs);
    ColoredString *(*on_magenta)(ColoredString *cs);
    ColoredString *(*on_cyan)(ColoredString *cs);
    ColoredString *(*on_white)(ColoredString *cs);

    ColoredString *(*on_bright_black)(ColoredString *cs);
    ColoredString *(*on_bright_red)(ColoredString *cs);
    ColoredString *(*on_bright_green)(ColoredString *cs);
    ColoredString *(*on_bright_yellow)(ColoredString *cs);
    ColoredString *(*on_bright_blue)(ColoredString *cs);
    ColoredString *(*on_bright_magenta)(ColoredString *cs);
    ColoredString *(*on_bright_cyan)(ColoredString *cs);
    ColoredString *(*on_bright_white)(ColoredString *cs);

    ColoredString *(*bold)(ColoredString *cs);
    ColoredString *(*dim)(ColoredString *cs);
    ColoredString *(*italic)(ColoredString *cs);
    ColoredString *(*underline)(ColoredString *cs);
    ColoredString *(*blink)(ColoredString *cs);
    ColoredString *(*reversed)(ColoredString *cs);
    ColoredString *(*strikethrough)(ColoredString *cs);

    ColoredString  *(*clear)(ColoredString *cs);
    const char     *(*print)(ColoredString *cs);
    void            (*free)(ColoredString *cs);
};

ColoredString *colored(const char *str);

#endif