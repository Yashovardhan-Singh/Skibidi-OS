#pragma  once

typedef enum {
    FG_BLACK        = 0,
    FG_BLUE         = 1,
    FG_GREEN        = 2,
    FG_CYAN         = 3,
    FG_RED          = 4,
    FG_MAGENTA      = 5,
    FG_BROWN        = 6,
    FG_LIGHT_GRAY   = 7,
    FG_DARK_GRAY    = 8,
    FG_LIGHT_BLUE   = 9,
    FG_LIGHT_GREEN  = 10,
    FG_LIGHT_CYAN   = 11,
    FG_LIGHT_RED    = 12,
    FG_LIGHT_MAGENTA= 13,
    FG_YELLOW       = 14,
    FG_WHITE        = 15
} FgColor;

// Enum for background colors (3-bit values: 0-7)
typedef enum {
    BG_BLACK        = 0,
    BG_BLUE         = 1,
    BG_GREEN        = 2,
    BG_CYAN         = 3,
    BG_RED          = 4,
    BG_MAGENTA      = 5,
    BG_BROWN        = 6,
    BG_LIGHT_GRAY   = 7
} BgColor;
