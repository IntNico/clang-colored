#include "clang_colored.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET "\033[0m"
#define MAX_ANSI_LEN 128
#define MAX_OUTPUT_LEN 1024

static ColoredString *set_fg(ColoredString *cs, fg_color color) {
    cs->fg = color;
    return cs;
}

static ColoredString *set_bg(ColoredString *cs, bg_color color) {
    cs->bg = color;
    return cs;
}

static ColoredString *apply_style(ColoredString *cs, style_flag flag) {
    cs->styles |= flag;
    return cs;
}

static ColoredString *fn_black(ColoredString *cs)     { return set_fg(cs, FG_BLACK); }
static ColoredString *fn_red(ColoredString *cs)       { return set_fg(cs, FG_RED); }
static ColoredString *fn_green(ColoredString *cs)     { return set_fg(cs, FG_GREEN); }
static ColoredString *fn_yellow(ColoredString *cs)    { return set_fg(cs, FG_YELLOW); }
static ColoredString *fn_blue(ColoredString *cs)      { return set_fg(cs, FG_BLUE); }
static ColoredString *fn_magenta(ColoredString *cs)   { return set_fg(cs, FG_MAGENTA); }
static ColoredString *fn_cyan(ColoredString *cs)      { return set_fg(cs, FG_CYAN); }
static ColoredString *fn_white(ColoredString *cs)     { return set_fg(cs, FG_WHITE); }

static ColoredString *fn_bright_black(ColoredString *cs)   { return set_fg(cs, FG_BRIGHT_BLACK); }
static ColoredString *fn_bright_red(ColoredString *cs)     { return set_fg(cs, FG_BRIGHT_RED); }
static ColoredString *fn_bright_green(ColoredString *cs)   { return set_fg(cs, FG_BRIGHT_GREEN); }
static ColoredString *fn_bright_yellow(ColoredString *cs)  { return set_fg(cs, FG_BRIGHT_YELLOW); }
static ColoredString *fn_bright_blue(ColoredString *cs)    { return set_fg(cs, FG_BRIGHT_BLUE); }
static ColoredString *fn_bright_magenta(ColoredString *cs) { return set_fg(cs, FG_BRIGHT_MAGENTA); }
static ColoredString *fn_bright_cyan(ColoredString *cs)    { return set_fg(cs, FG_BRIGHT_CYAN); }
static ColoredString *fn_bright_white(ColoredString *cs)   { return set_fg(cs, FG_BRIGHT_WHITE); }

static ColoredString *fn_on_black(ColoredString *cs)     { return set_bg(cs, BG_BLACK); }
static ColoredString *fn_on_red(ColoredString *cs)       { return set_bg(cs, BG_RED); }
static ColoredString *fn_on_green(ColoredString *cs)     { return set_bg(cs, BG_GREEN); }
static ColoredString *fn_on_yellow(ColoredString *cs)    { return set_bg(cs, BG_YELLOW); }
static ColoredString *fn_on_blue(ColoredString *cs)      { return set_bg(cs, BG_BLUE); }
static ColoredString *fn_on_magenta(ColoredString *cs)   { return set_bg(cs, BG_MAGENTA); }
static ColoredString *fn_on_cyan(ColoredString *cs)      { return set_bg(cs, BG_CYAN); }
static ColoredString *fn_on_white(ColoredString *cs)     { return set_bg(cs, BG_WHITE); }

static ColoredString *fn_on_bright_black(ColoredString *cs)   { return set_bg(cs, BG_BRIGHT_BLACK); }
static ColoredString *fn_on_bright_red(ColoredString *cs)     { return set_bg(cs, BG_BRIGHT_RED); }
static ColoredString *fn_on_bright_green(ColoredString *cs)   { return set_bg(cs, BG_BRIGHT_GREEN); }
static ColoredString *fn_on_bright_yellow(ColoredString *cs)  { return set_bg(cs, BG_BRIGHT_YELLOW); }
static ColoredString *fn_on_bright_blue(ColoredString *cs)    { return set_bg(cs, BG_BRIGHT_BLUE); }
static ColoredString *fn_on_bright_magenta(ColoredString *cs) { return set_bg(cs, BG_BRIGHT_MAGENTA); }
static ColoredString *fn_on_bright_cyan(ColoredString *cs)    { return set_bg(cs, BG_BRIGHT_CYAN); }
static ColoredString *fn_on_bright_white(ColoredString *cs)   { return set_bg(cs, BG_BRIGHT_WHITE); }

static ColoredString *fn_bold(ColoredString *cs)          { return apply_style(cs, STYLE_BOLD); }
static ColoredString *fn_dim(ColoredString *cs)           { return apply_style(cs, STYLE_DIM); }
static ColoredString *fn_italic(ColoredString *cs)        { return apply_style(cs, STYLE_ITALIC); }
static ColoredString *fn_underline(ColoredString *cs)     { return apply_style(cs, STYLE_UNDERLINE); }
static ColoredString *fn_blink(ColoredString *cs)         { return apply_style(cs, STYLE_BLINK); }
static ColoredString *fn_reversed(ColoredString *cs)      { return apply_style(cs, STYLE_REVERSED); }
static ColoredString *fn_strikethrough(ColoredString *cs) { return apply_style(cs, STYLE_STRIKETHROUGH); }

static ColoredString *fn_clear(ColoredString *cs) {
    cs->fg = FG_NONE;
    cs->bg = BG_NONE;
    cs->styles = 0;
    return cs;
}

static const char *fn_print(ColoredString *cs) {
    char ansi_codes[MAX_ANSI_LEN];
    ansi_codes[0] = '\0';

    int has_code = 0;
    char seq[MAX_ANSI_LEN];
    seq[0] = '\0';

    strcat(seq, "\033[");

    if (cs->styles & STYLE_BOLD)          { if (has_code) strcat(seq, ";"); strcat(seq, "1");  has_code = 1; }
    if (cs->styles & STYLE_DIM)           { if (has_code) strcat(seq, ";"); strcat(seq, "2");  has_code = 1; }
    if (cs->styles & STYLE_ITALIC)        { if (has_code) strcat(seq, ";"); strcat(seq, "3");  has_code = 1; }
    if (cs->styles & STYLE_UNDERLINE)     { if (has_code) strcat(seq, ";"); strcat(seq, "4");  has_code = 1; }
    if (cs->styles & STYLE_BLINK)         { if (has_code) strcat(seq, ";"); strcat(seq, "5");  has_code = 1; }
    if (cs->styles & STYLE_REVERSED)      { if (has_code) strcat(seq, ";"); strcat(seq, "7");  has_code = 1; }
    if (cs->styles & STYLE_STRIKETHROUGH) { if (has_code) strcat(seq, ";"); strcat(seq, "9");  has_code = 1; }

    char num[8];

    if (cs->fg != FG_NONE) {
        if (has_code) strcat(seq, ";");
        snprintf(num, sizeof(num), "%d", (int)cs->fg);
        strcat(seq, num);
        has_code = 1;
    }

    if (cs->bg != BG_NONE) {
        if (has_code) strcat(seq, ";");
        snprintf(num, sizeof(num), "%d", (int)cs->bg);
        strcat(seq, num);
        has_code = 1;
    }

    strcat(seq, "m");

    if (!has_code) {
        snprintf(cs->output, MAX_OUTPUT_LEN, "%s", cs->str);
    } else {
        snprintf(cs->output, MAX_OUTPUT_LEN, "%s%s%s", seq, cs->str, ANSI_RESET);
    }

    return cs->output;
}

static void fn_free(ColoredString *cs) {
    free(cs->str);
    free(cs);
}

ColoredString *colored(const char *str) {
    ColoredString *cs = malloc(sizeof(ColoredString));

    cs->str = strdup(str);
    cs->fg = FG_NONE;
    cs->bg = BG_NONE;
    cs->styles = 0;

    cs->black          = fn_black;
    cs->red            = fn_red;
    cs->green          = fn_green;
    cs->yellow         = fn_yellow;
    cs->blue           = fn_blue;
    cs->magenta        = fn_magenta;
    cs->cyan           = fn_cyan;
    cs->white          = fn_white;

    cs->bright_black   = fn_bright_black;
    cs->bright_red     = fn_bright_red;
    cs->bright_green   = fn_bright_green;
    cs->bright_yellow  = fn_bright_yellow;
    cs->bright_blue    = fn_bright_blue;
    cs->bright_magenta = fn_bright_magenta;
    cs->bright_cyan    = fn_bright_cyan;
    cs->bright_white   = fn_bright_white;

    cs->on_black          = fn_on_black;
    cs->on_red            = fn_on_red;
    cs->on_green          = fn_on_green;
    cs->on_yellow         = fn_on_yellow;
    cs->on_blue           = fn_on_blue;
    cs->on_magenta        = fn_on_magenta;
    cs->on_cyan           = fn_on_cyan;
    cs->on_white          = fn_on_white;

    cs->on_bright_black   = fn_on_bright_black;
    cs->on_bright_red     = fn_on_bright_red;
    cs->on_bright_green   = fn_on_bright_green;
    cs->on_bright_yellow  = fn_on_bright_yellow;
    cs->on_bright_blue    = fn_on_bright_blue;
    cs->on_bright_magenta = fn_on_bright_magenta;
    cs->on_bright_cyan    = fn_on_bright_cyan;
    cs->on_bright_white   = fn_on_bright_white;

    cs->bold          = fn_bold;
    cs->dim           = fn_dim;
    cs->italic        = fn_italic;
    cs->underline     = fn_underline;
    cs->blink         = fn_blink;
    cs->reversed      = fn_reversed;
    cs->strikethrough = fn_strikethrough;

    cs->clear = fn_clear;
    cs->print = fn_print;
    cs->free  = fn_free;

    return cs;
}